#include <gtest/gtest.h>
#include "byteConverter.h"

class ByteTestSuite : public ::testing::Test {
protected:
    std::string str_ = "Hello, world!";
};

TEST_F(ByteTestSuite, HelloWorld) {
    EXPECT_EQ("01001000011001010110110001101100011011110010110000100000011101110110111101110010011011000110010000100001", QR::byteToBitString(str_));
}
