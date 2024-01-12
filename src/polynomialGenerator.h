#pragma once

#include <vector>
#include "GF256.h"
#include <cmath>
#include <iostream>

namespace QR {
    inline std::vector<int> multiplyPolynomials(std::vector<int>& first, std::vector<int>& second) {
        std::vector<int> result(first.size() + 1);
        std::vector<std::vector<int>> pows(first.size() + 1);
        for (int i = 0; i < first.size(); ++i) {
            pows[i].push_back(first[i] + second[0]);
            pows[i+1].push_back(first[i] + second[1]);
        }

        for (int i = 0; i < first.size(); ++i) {
            if (pows[i][0] > 255) {
                pows[i][0] = (pows[i][0] % 256) + std::floor(pows[i][0] / 256);
            }
        }
        for (int i = 1; i < first.size() - 1; ++i) {
            if (pows[i][1] > 255) {
                pows[i][1] = (pows[i][0] % 256) + std::floor(pows[i][0] / 256);
            }
        }

        result[0] = pows[0][0];
        result[first.size()] = pows[first.size()][0];
        for (int i = 1; i < first.size(); ++i) {
            result[i] = GF256::intToLog[GF256::logToInt[pows[i][0]] ^ GF256::logToInt[pows[i][1]]];
        }

        return result;
    }

    inline std::vector<int> generatePolynomial(int base) {
        std::vector<int> polynomial(base);
        std::vector<int> current_polynomial{0,0};

        for (int j = 1; j < base; ++j) {
            std::vector<int> first_polynomial = current_polynomial;
            std::vector<int> second_polynomial{0,j};
            current_polynomial = multiplyPolynomials(first_polynomial, second_polynomial);
        }

        // convert from Exponent to Integers
        for (int& value : current_polynomial) {
            value = GF256::logToInt[value];
        }

        return current_polynomial;
    }

} //namespace QR
