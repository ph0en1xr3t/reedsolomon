#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "reedsolomon.h"

/**
 * Test fixture for Reed-Solomon encoder
 */
class EncoderTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup test data
        test_data_ = {'E', 'n', 'c', 'o', 'd', 'e', 'r', ' ', 'T', 'e', 's', 't'};
    }

    std::vector<unsigned char> test_data_;
};

/**
 * Test encoder with various input sizes
 */
TEST_F(EncoderTest, VariableInputSizeTest) {
    for (size_t size = 1; size <= 100; ++size) {
        std::vector<unsigned char> data(size, 0x42); // Fill with 'B'
        std::vector<unsigned char> parity = rs_encode(data, 4);
        EXPECT_EQ(parity.size(), 4u);
    }
}

/**
 * Test encoder determinism (same input should produce same output)
 */
TEST_F(EncoderTest, DeterminismTest) {
    std::vector<unsigned char> parity1 = rs_encode(test_data_, 6);
    std::vector<unsigned char> parity2 = rs_encode(test_data_, 6);
    
    EXPECT_EQ(parity1, parity2);
}

/**
 * Test encoder with different parity lengths
 */
TEST_F(EncoderTest, ParityLengthVariationTest) {
    for (int parity_len = 1; parity_len <= 32; ++parity_len) {
        std::vector<unsigned char> parity = rs_encode(test_data_, parity_len);
        EXPECT_EQ(parity.size(), static_cast<size_t>(parity_len));
    }
}