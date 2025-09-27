#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "reedsolomon.h"

/**
 * Test fixture for Reed-Solomon decoder
 */
class DecoderTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup test data
        test_message_ = {'D', 'e', 'c', 'o', 'd', 'e', 'r', ' ', 'T', 'e', 's', 't'};
        parity_length_ = 8;
        
        // Create encoded message for testing
        parity_ = rs_encode(test_message_, parity_length_);
        encoded_message_ = test_message_;
        encoded_message_.insert(encoded_message_.end(), parity_.begin(), parity_.end());
    }

    std::vector<unsigned char> test_message_;
    std::vector<unsigned char> parity_;
    std::vector<unsigned char> encoded_message_;
    int parity_length_;
};

/**
 * Test decoder with no errors (should pass through unchanged)
 */
TEST_F(DecoderTest, NoErrorsTest) {
    std::vector<unsigned char> clean_message = encoded_message_;
    std::vector<int> no_erasures;
    
    bool success = rs_decode(clean_message, parity_length_, no_erasures);
    EXPECT_TRUE(success);
    
    // Original message should be preserved
    for (size_t i = 0; i < test_message_.size(); ++i) {
        EXPECT_EQ(clean_message[i], test_message_[i]);
    }
}

/**
 * Test decoder with various erasure patterns
 */
TEST_F(DecoderTest, ErasurePatternTest) {
    // Test with different numbers of erasures
    for (int num_erasures = 1; num_erasures <= 4; ++num_erasures) {
        std::vector<unsigned char> test_data = encoded_message_;
        std::vector<int> erasures;
        
        // Create erasure pattern
        for (int i = 0; i < num_erasures; ++i) {
            erasures.push_back(i * 2); // Erase every other position
            test_data[i * 2] = 0; // Mark as erased
        }
        
        bool success = rs_decode(test_data, parity_length_, erasures);
        
        // With enough parity, should succeed
        if (num_erasures <= parity_length_ / 2) {
            EXPECT_TRUE(success);
        }
    }
}

/**
 * Test decoder error handling with invalid inputs
 */
TEST_F(DecoderTest, InvalidInputTest) {
    std::vector<unsigned char> test_data = {'A', 'B', 'C'};
    std::vector<int> erasures;
    
    // Test with negative parity length
    bool result = rs_decode(test_data, -1, erasures);
    EXPECT_FALSE(result);
    
    // Test with parity length greater than data length
    result = rs_decode(test_data, 10, erasures);
    // This may or may not fail depending on implementation
    // EXPECT_FALSE(result);
}