#pragma once
#include "domain.h"
#include <string>

namespace QR {
    bool isNumeric(const char& c) {
        return c >= '0' && c <= '9';
    }

    bool isAlphanumeric(const char& c) {
        return (c >= 'A' && c <= 'Z') || c == '$' || c == '%' || c == '*' || c == '+'
                                        || c == '-' || c == '.' || c == '/' || c == ':' || c == ' ';
    }

    Mode analyze(const std::string& input) {
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
} //namespace QR
