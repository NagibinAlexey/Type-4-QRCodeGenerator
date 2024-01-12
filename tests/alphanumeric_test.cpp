#include <gtest/gtest.h>
#include "alphanumericConverter.h"

class AlphanumericTestSuite : public ::testing::Test {
protected:
    std::string str_ = "HELLO WORLD";
};

TEST_F(AlphanumericTestSuite, HelloWorld) {
    EXPECT_EQ("0110000101101111000110100010111001011011100010011010100001101", QR::alphanumericToBitString(str_));
}