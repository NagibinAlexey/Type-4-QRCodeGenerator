#pragma once
#include "domain.h"
#include <string>
#include <bitset>
#include <iostream>

namespace QR{
    class FormatStringGenerator final {
    public:
        explicit FormatStringGenerator(ErrorCorLevel corLevel, int maskNumber = 1);
        ~FormatStringGenerator() = default;
        std::string getFormatString() { return format_string_; }

    private:
        ErrorCorLevel corLevel_;
        int maskNumber_;
        const std::string gp_{"10100110111"};
        std::string format_string_;

        void addErCorBit();
        void addMaskPatternBit();
        std::string calcErCorBits();
    };

} // QR

