#include <gtest/gtest.h>
#include "polynomialGenerator.h"

class PolynomialGeneratorTestSuite : public ::testing::Test {
protected:
    std::vector<int> polinomial_18 = {1, 239, 251, 183, 113, 149, 175, 199, 215, 240, 220, 73, 82, 173, 75, 32, 67, 217, 146};
};

TEST_F(PolynomialGeneratorTestSuite, generate_polinomial_18) {
    EXPECT_EQ(QR::generatePolynomial(18), polinomial_18);
}
