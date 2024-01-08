#include <gtest/gtest.h>
#include "analyzer.h"

class AnalyzeTestSuite : public ::testing::Test {
protected:
    std::string str_;
};

TEST_F(AnalyzeTestSuite, Numeric) {
    EXPECT_EQ(QR::Numeric, QR::analyze("1234567890"));
}

TEST_F(AnalyzeTestSuite, Alphanumeric) {
    EXPECT_EQ(QR::Alphanumeric, QR::analyze("1234567890 TEST"));
}

TEST_F(AnalyzeTestSuite, Byte) {
    EXPECT_EQ(QR::Byte, QR::analyze("0189 TEST abcxyz"));
}




