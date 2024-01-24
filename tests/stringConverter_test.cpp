#include <gtest/gtest.h>
#include "stringConverter.h"

QR::stringConverter generator("HELLO WORLD", 1, QR::ErrorCorLevel::M);

class stringConverterTestSuite : public ::testing::Test {
protected:
    QR::stringConverter& generator_ = generator;
};

TEST_F(stringConverterTestSuite, FullBitString) {
    EXPECT_EQ(generator_.getFullBitString(), "00100000010110110000101101111000110100010111001011011100010011010100001101000000111011000001000111101100000100011110110000010001");
}
