#pragma once

#include <string>
#include <bitset>
#include <unordered_map>

namespace QR {

    inline std::unordered_map<char, int> InitializeTableOfAlpha() {
        std::unordered_map<char, int> TableOfAlpha;
        char current_char = '0';
        for (int i = 0; i <= 9; ++i) {
            TableOfAlpha[current_char] = i;
        }
        current_char = 'A';
        int i = 10;
        while (current_char <= 'Z') {
            TableOfAlpha[current_char] = i;
            ++current_char;
            ++i;
        }
        TableOfAlpha[' '] = 36;
        TableOfAlpha['$'] = 37;
        TableOfAlpha['%'] = 38;
        TableOfAlpha['*'] = 39;
        TableOfAlpha['+'] = 40;
        TableOfAlpha['-'] = 41;
        TableOfAlpha['.'] = 42;
        TableOfAlpha['/'] = 43;
        TableOfAlpha[':'] = 44;

        return TableOfAlpha;
    }

    static auto TableOfAlpha = InitializeTableOfAlpha();

    inline std::string alphanumericToBitString(std::string& source) {
        std::string result;
        for (int i = 0; i < source.size(); i = i + 2) {
            int current_number;
            if (i != source.size() - 1) {
                current_number = 45 * (TableOfAlpha[source[i]]) + TableOfAlpha[source[i + 1]];
                result.append(std::bitset<11>(current_number).to_string());
            } else {
                current_number = TableOfAlpha[source[i]];
                result.append(std::bitset<6>(current_number).to_string());
            }
        }
        return result;
    }
} //namespace QR
