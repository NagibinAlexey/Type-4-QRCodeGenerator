#include "FormatStringGenerator.h"
#include <iostream>

namespace QR {
    FormatStringGenerator::FormatStringGenerator(ErrorCorLevel corLevel, int maskNumber) : corLevel_(corLevel), maskNumber_(maskNumber), format_string_({}) {
        addErCorBit();
        addMaskPatternBit();
        format_string_.append(calcErCorBits());
        format_string_ = (std::bitset<15>(std::stoi(format_string_, nullptr, 2)) ^ std::bitset<15>(std::stoi("101010000010010", nullptr, 2))).to_string();
    }

    void FormatStringGenerator::addErCorBit() {
        switch (corLevel_) {
            case L: {
                format_string_.append("01");
                break;
            }
            case M: {
                format_string_.append("00");
                break;
            }
            case Q: {
                format_string_.append("11");
                break;
            }
            case H: {
                format_string_.append("10");
                break;
            }
        }
    }

    void FormatStringGenerator::addMaskPatternBit() {
        format_string_.append(std::bitset<3>(maskNumber_).to_string());
    }

    std::string FormatStringGenerator::calcErCorBits() {
        std::string str_ = format_string_;
        str_.append("0000000000");
        if (corLevel_ != M) {
            str_ = str_.substr(str_.find_first_of('1'), str_.size());
        } else {
            str_ = str_.substr(1, str_.size());
        }
        std::cout << str_ << std::endl;
        while (str_.size() >= 11) {
            std::string temp_gp = gp_;
            if (temp_gp.size() < str_.size()) {
                temp_gp.append(std::string((str_.size() - temp_gp.size()), '0'));
            }
            str_ = std::bitset<15>((std::stoi(str_, nullptr, 2) ^ std::stoi(temp_gp, nullptr, 2))).to_string();
            std::cout << str_ << std::endl;
            if (corLevel_ != M) {
                str_ = str_.substr(str_.find_first_of('1'), str_.size());
            } else {
                //str_ = str_.substr(4, str_.size());
            }
        }
        str_ = std::bitset<10>(std::stoi(str_, nullptr, 2)).to_string();
        return str_;
    }

} // QR