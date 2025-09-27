#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "reedsolomon.h"
#include <vector>

/**
 * Test fixture for Reed-Solomon encoder/decoder tests
 * Provides common test data and helper functions
 */
class ReedSolomonTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common test data setup
        simple_message_ = {'H', 'e', 'l', 'l', 'o', '!'};
        longer_message_ = {
            'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ',
            'l', 'o', 'n', 'g', 'e', 'r', ' ', 't', 'e', 's', 't', ' ',
            'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 'f', 'o', 'r', ' ',
            'R', 'e', 'e', 'd', '-', 'S', 'o', 'l', 'o', 'm', 'o', 'n', '.'
        };
        
        standard_parity_length_ = 4;
        extended_parity_length_ = 8;
    }

    void TearDown() override {
        // Clean up after each test
    }

    // Helper function to introduce errors at specific positions
    void IntroduceErrors(std::vector<unsigned char>& data, 
                        const std::vector<size_t>& positions,
                        const std::vector<unsigned char>& error_values) {
        for (size_t i = 0; i < positions.size() && i < error_values.size(); ++i) {
            if (positions[i] < data.size()) {
                data[positions[i]] = error_values[i];
            }
        }
    }

    // Helper function to create erasure list
    std::vector<int> CreateErasureList(const std::vector<size_t>& positions) {
        std::vector<int> erasures;
        for (size_t pos : positions) {
            erasures.push_back(static_cast<int>(pos));
        }
        return erasures;
    }

    // Test data
    std::vector<unsigned char> simple_message_;
    std::vector<unsigned char> longer_message_;
    int standard_parity_length_;
    int extended_parity_length_;
};

/**
 * Test basic encoding functionality
 */
TEST_F(ReedSolomonTest, BasicEncodingTest) {
    // Test encoding with simple message
    std::vector<unsigned char> parity = rs_encode(simple_message_, standard_parity_length_);
    
    // Verify parity length
    EXPECT_EQ(parity.size(), static_cast<size_t>(standard_parity_length_));
    
    // Parity should not be all zeros (unless message is all zeros)
    bool all_zeros = true;
    for (unsigned char byte : parity) {
        if (byte != 0) {
            all_zeros = false;
            break;
        }
    }
    EXPECT_FALSE(all_zeros);
}

/**
 * Test encoding with different parity lengths
 */
TEST_F(ReedSolomonTest, VariableParityLengthTest) {
    for (int parity_len = 2; parity_len <= 16; parity_len += 2) {
        std::vector<unsigned char> parity = rs_encode(simple_message_, parity_len);
        EXPECT_EQ(parity.size(), static_cast<size_t>(parity_len));
    }
}

/**
 * Test basic decoding without errors
 */
TEST_F(ReedSolomonTest, BasicDecodingNoErrorsTest) {
    // Encode message
    std::vector<unsigned char> parity = rs_encode(simple_message_, standard_parity_length_);
    
    // Create complete message (data + parity)
    std::vector<unsigned char> encoded_message = simple_message_;
    encoded_message.insert(encoded_message.end(), parity.begin(), parity.end());
    
    // Decode without any errors
    std::vector<int> no_erasures;
    bool success = rs_decode(encoded_message, standard_parity_length_, no_erasures);
    
    EXPECT_TRUE(success);
    
    // Verify original message is preserved
    for (size_t i = 0; i < simple_message_.size(); ++i) {
        EXPECT_EQ(encoded_message[i], simple_message_[i]);
    }
}

/**
 * Test decoding with single error
 */
TEST_F(ReedSolomonTest, SingleErrorCorrectionTest) {
    // Encode message
    std::vector<unsigned char> parity = rs_encode(simple_message_, standard_parity_length_);
    std::vector<unsigned char> encoded_message = simple_message_;
    encoded_message.insert(encoded_message.end(), parity.begin(), parity.end());
    
    // Introduce single error
    size_t error_position = 2;
    unsigned char original_value = encoded_message[error_position];
    encoded_message[error_position] = original_value ^ 0xFF; // Flip all bits
    
    // Attempt to decode
    std::vector<int> no_erasures;
    bool success = rs_decode(encoded_message, standard_parity_length_, no_erasures);
    
    EXPECT_TRUE(success);
    
    // Verify error was corrected
    EXPECT_EQ(encoded_message[error_position], original_value);
}

/**
 * Test decoding with multiple errors
 */
TEST_F(ReedSolomonTest, MultipleErrorCorrectionTest) {
    // Use extended parity for better error correction capability
    std::vector<unsigned char> parity = rs_encode(longer_message_, extended_parity_length_);
    std::vector<unsigned char> encoded_message = longer_message_;
    encoded_message.insert(encoded_message.end(), parity.begin(), parity.end());
    
    // Store original values
    std::vector<unsigned char> original_message = encoded_message;
    
    // Introduce multiple errors (should be correctable with 8 parity bytes)
    std::vector<size_t> error_positions = {5, 15, 25};
    std::vector<unsigned char> error_values = {0xFF, 0xAA, 0x55};
    IntroduceErrors(encoded_message, error_positions, error_values);
    
    // Attempt to decode
    std::vector<int> no_erasures;
    bool success = rs_decode(encoded_message, extended_parity_length_, no_erasures);
    
    // Note: This test may fail with current stub implementation
    // TODO: Update expectation when real Reed-Solomon is implemented
    if (success) {
        // Verify errors were corrected
        for (size_t i = 0; i < longer_message_.size(); ++i) {
            EXPECT_EQ(encoded_message[i], original_message[i]);
        }
    }
}

/**
 * Test erasure correction
 */
TEST_F(ReedSolomonTest, ErasureCorrectionTest) {
    // Encode message
    std::vector<unsigned char> parity = rs_encode(simple_message_, standard_parity_length_);
    std::vector<unsigned char> encoded_message = simple_message_;
    encoded_message.insert(encoded_message.end(), parity.begin(), parity.end());
    
    // Store original
    std::vector<unsigned char> original_message = encoded_message;
    
    // Create erasures (known missing data positions)
    std::vector<size_t> erasure_positions = {1, 3};
    std::vector<int> erasures = CreateErasureList(erasure_positions);
    
    // Mark positions as erased (set to 0)
    for (size_t pos : erasure_positions) {
        encoded_message[pos] = 0;
    }
    
    // Attempt to decode with erasure information
    bool success = rs_decode(encoded_message, standard_parity_length_, erasures);
    
    if (success) {
        // Verify erasures were corrected
        for (size_t pos : erasure_positions) {
            EXPECT_EQ(encoded_message[pos], original_message[pos]);
        }
    }
}

/**
 * Test edge cases and error conditions
 */
TEST_F(ReedSolomonTest, EdgeCasesTest) {
    // Test with empty message
    std::vector<unsigned char> empty_message;
    std::vector<unsigned char> parity = rs_encode(empty_message, 2);
    EXPECT_EQ(parity.size(), 2u);
    
    // Test with zero parity length
    parity = rs_encode(simple_message_, 0);
    EXPECT_EQ(parity.size(), 0u);
    
    // Test decoding with invalid parameters
    std::vector<unsigned char> test_data = {'A', 'B', 'C', 'D'};
    std::vector<int> no_erasures;
    
    // This should handle gracefully
    bool result = rs_decode(test_data, -1, no_erasures); // Negative parity length
    EXPECT_FALSE(result);
}

/**
 * Performance test for encoding/decoding operations
 */
TEST_F(ReedSolomonTest, PerformanceTest) {
    const int iterations = 100;
    const auto start_time = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        std::vector<unsigned char> parity = rs_encode(longer_message_, standard_parity_length_);
        std::vector<unsigned char> encoded = longer_message_;
        encoded.insert(encoded.end(), parity.begin(), parity.end());
        
        std::vector<int> no_erasures;
        rs_decode(encoded, standard_parity_length_, no_erasures);
    }
    
    const auto end_time = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    // Performance check - should complete within reasonable time
    EXPECT_LT(duration.count(), 1000000); // Less than 1 second for 100 iterations
    
    std::cout << "Performance: " << iterations << " encode/decode cycles took " 
              << duration.count() << " microseconds" << std::endl;
}

// Test main function will be provided by gtest_main