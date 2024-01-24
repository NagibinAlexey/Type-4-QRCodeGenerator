#pragma once

#include <string>
#include <bitset>

namespace QR {

    inline std::string byteToBitString(std::string& source) {
        std::string result;
        for (const char& c : source) {
            result.append(std::bitset<8>(c).to_string());
        }
        return result;
    }

} //namespace QR
