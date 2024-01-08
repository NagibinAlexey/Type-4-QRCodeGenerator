#include <gtest/gtest.h>
#include "ErCorCodewordsGenerator.h"
#include <iostream>

QR::ECCGenerator ecc_generator("00100000010110110000101101111000110100010111001011011100010011010100001101000000111011000001000111101100000100011110110000010001", QR::ErrorCorLevel::L);

class ECCGeneratorTestSuite : public ::testing::Test {
protected:
    QR::ECCGenerator& generator_ = ecc_generator;
};

TEST_F(ECCGeneratorTestSuite, ECC) {
    std::vector<int> mp = {32,91,11,120,209,114,220,77,67,64,236,17,236,17,236,17};
    std::vector<int> ecc = {196,35,39,119,235,215,231,226,93,23};
    generator_.setGp(QR::generator_polynomial10);
    EXPECT_EQ(generator_.calcErrCorCodewords(mp), ecc);
}
