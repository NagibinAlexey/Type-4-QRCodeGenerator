#include <gtest/gtest.h>
#include "ErCorCodewordsGenerator.h"

QR::QRGenerator gen_1("HELLO WORLD", 1,QR::ErrorCorLevel::M);

class ECCGeneratorTestSuite : public ::testing::Test {
protected:
    QR::QRGenerator& generator = gen_1;
};

TEST_F(ECCGeneratorTestSuite, MP) {
    QR::ECCGenerator ecc_generator(generator);
    std::vector<int> mp = {32,91,11,120,209,114,220,77,67,64,236,17,236,17,236,17};
    EXPECT_EQ(ecc_generator.getMP(), mp);
}

TEST_F(ECCGeneratorTestSuite, ECC) {
    QR::ECCGenerator ecc_generator(generator);
    std::vector<int> mp = ecc_generator.getMP();
    std::vector<int> ecc = {196,35,39,119,235,215,231,226,93,23};
    EXPECT_EQ(ecc_generator.calcErrCorCodewords(mp), ecc);
}
