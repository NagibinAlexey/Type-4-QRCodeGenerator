#pragma once
#include "domain.h"
#include <string>
#include <stdexcept>

namespace QR {
    inline bool isNumeric(const char& c) {
        return c >= '0' && c <= '9';
    }

    inline bool isAlphanumeric(const char& c) {
        return (c >= 'A' && c <= 'Z') || c == '$' || c == '%' || c == '*' || c == '+'
                                        || c == '-' || c == '.' || c == '/' || c == ':' || c == ' ';
    }

    inline Mode analyze(const std::string& input) {
        bool byte_ = false;
        bool alpha_ = false;
        for (const char& c : input) {
            if (c - '0' > 127) return Kanji;
            else if (!isNumeric(c) && !isAlphanumeric(c) && (c - '0' <= 127)) byte_ = true;
            else if (isAlphanumeric(c)) alpha_ = true;
        }

        if (byte_) return Byte;
        else if (alpha_) return Alphanumeric;

        return Numeric;
    }

    inline int getMinQRCodeVersion(const std::string& input, ErrorCorLevel level, Mode mode) {
        size_t char_count = input.size();
        switch (level) {
            case L: {
                if (mode == Numeric) {
                        if (char_count <= 41) return 1;
                        else if (char_count <= 77) return 2;
                        else if (char_count <= 127) return 3;
                        else if (char_count <= 187) return 4;
                        else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Alphanumeric) {
                    if (char_count <= 25) return 1;
                    else if (char_count <= 47) return 2;
                    else if (char_count <= 77) return 3;
                    else if (char_count <= 114) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Byte) {
                    if (char_count <= 17) return 1;
                    else if (char_count <= 32) return 2;
                    else if (char_count <= 53) return 3;
                    else if (char_count <= 78) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Kanji) {
                    if (char_count <= 10) return 1;
                    else if (char_count <= 20) return 2;
                    else if (char_count <= 32) return 3;
                    else if (char_count <= 48) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
            }
            case M: {
                if (mode == Numeric) {
                    if (char_count <= 34) return 1;
                    else if (char_count <= 63) return 2;
                    else if (char_count <= 101) return 3;
                    else if (char_count <= 149) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Alphanumeric) {
                    if (char_count <= 20) return 1;
                    else if (char_count <= 38) return 2;
                    else if (char_count <= 61) return 3;
                    else if (char_count <= 90) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Byte) {
                    if (char_count <= 14) return 1;
                    else if (char_count <= 26) return 2;
                    else if (char_count <= 42) return 3;
                    else if (char_count <= 62) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Kanji) {
                    if (char_count <= 8) return 1;
                    else if (char_count <= 16) return 2;
                    else if (char_count <= 26) return 3;
                    else if (char_count <= 38) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
            }
            case Q: {
                if (mode == Numeric) {
                    if (char_count <= 27) return 1;
                    else if (char_count <= 48) return 2;
                    else if (char_count <= 77) return 3;
                    else if (char_count <= 111) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Alphanumeric) {
                    if (char_count <= 16) return 1;
                    else if (char_count <= 29) return 2;
                    else if (char_count <= 47) return 3;
                    else if (char_count <= 67) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Byte) {
                    if (char_count <= 11) return 1;
                    else if (char_count <= 20) return 2;
                    else if (char_count <= 32) return 3;
                    else if (char_count <= 46) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Kanji) {
                    if (char_count <= 7) return 1;
                    else if (char_count <= 12) return 2;
                    else if (char_count <= 20) return 3;
                    else if (char_count <= 28) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
            }
            case H: {
                if (mode == Numeric) {
                    if (char_count <= 17) return 1;
                    else if (char_count <= 34) return 2;
                    else if (char_count <= 58) return 3;
                    else if (char_count <= 82) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Alphanumeric) {
                    if (char_count <= 10) return 1;
                    else if (char_count <= 20) return 2;
                    else if (char_count <= 35) return 3;
                    else if (char_count <= 50) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Byte) {
                    if (char_count <= 7) return 1;
                    else if (char_count <= 14) return 2;
                    else if (char_count <= 24) return 3;
                    else if (char_count <= 34) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
                if (mode == Kanji) {
                    if (char_count <= 4) return 1;
                    else if (char_count <= 8) return 2;
                    else if (char_count <= 15) return 3;
                    else if (char_count <= 21) return 4;
                    else { throw std::out_of_range("This string length is not supported"); }
                }
            }
        }
        return 4;
    }
} //namespace QR
