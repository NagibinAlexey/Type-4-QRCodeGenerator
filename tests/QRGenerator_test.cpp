#include <gtest/gtest.h>
#include "QRGenerator.h"

QR::QRGenerator generator("HELLO WORLD", QR::ErrorCorLevel::L);

class QRGeneratorTestSuite : public ::testing::Test {
protected:
    QR::QRGenerator& generator_ = generator;
};

TEST_F(QRGeneratorTestSuite, FullBitString) {
    generator_.setCapacity(104);
    EXPECT_EQ(generator.getFullBitString(), "00100000010110110000101101111000110100010111001011011100010011010100001101000000111011000001000111101100");
}
