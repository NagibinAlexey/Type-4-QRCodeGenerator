#include <gtest/gtest.h>
#include "numericConverter.h"

class NumericTestSuite : public ::testing::Test {
protected:
    std::string str_ = "8675309";
};

TEST_F(NumericTestSuite, Size_7) {
    EXPECT_EQ(QR::numericToBitString(str_), "110110001110000100101001");
}

TEST_F(NumericTestSuite, Size_8) {
    str_ = "86753010";
    EXPECT_EQ(QR::numericToBitString(str_), "110110001110000100100001010");
}

TEST_F(NumericTestSuite, Size_9) {
    str_ = "867530867";
    EXPECT_EQ(QR::numericToBitString(str_), "110110001110000100101101100011");
}

TEST_F(NumericTestSuite, TwoLeadingZeros) {
    str_ = "8670019";
    EXPECT_EQ(QR::numericToBitString(str_), "110110001100011001");
}

TEST_F(NumericTestSuite, OneLeadingZero) {
    str_ = "8670109";
    EXPECT_EQ(QR::numericToBitString(str_), "110110001100010101001");
}
