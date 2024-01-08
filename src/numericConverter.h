#pragma once

#include <string>
#include <bitset>

namespace QR {
    inline std::string numericToBitString(std::string& source) {
        std::string result;
        for (int i = 0; i < source.size(); i = i + 3) {
            if (i <= source.size() - 3) {
                int three_size_number = (source[i] - '0') * 100 + (source[i + 1] - '0') * 10 + (source[i + 2] - '0');
                if (source[i] == '0' && source[i + 1] == '0') {
                    result.append(std::bitset<4>(three_size_number).to_string());
                }
                else if (source[i] == '0') {
                    result.append(std::bitset<7>(three_size_number).to_string());
                }
                else {
                    result.append(std::bitset<10>(three_size_number).to_string());
                }
            }
            else if (i == source.size() - 2) {
                int two_size_number = (source[i] - '0') * 10 + (source[i + 1] - '0');
                if (source[i] == '0') {
                    result.append(std::bitset<4>(two_size_number).to_string());
                }
                else {
                    result.append(std::bitset<7>(two_size_number).to_string());
                }
            }
            else {
                result.append(std::bitset<4>(source[i] - '0').to_string());
            }
        }
        return result;
    }
} //namespace QR

