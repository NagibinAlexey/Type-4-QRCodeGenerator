#include "domain.h"
#include <algorithm>
#include "stringConverter.h"
#include "FormatStringGenerator.h"

namespace QR {
    namespace utility {

        void addFormatString(stringConverter& qrGenerator, std::vector<std::vector<QR::Module>>& matrix, int maskNumber) {
            QR::FormatStringGenerator fsg(qrGenerator.getQRInfo().corLevel, maskNumber);
            std::string fs = fsg.getFormatString();
            int modules_per_side = utility::getMatrixSize(qrGenerator.getQRInfo().version);

            for (int row = modules_per_side - 1, i = 0; row > modules_per_side - 8; --row, ++i) {
                matrix[row][8].value = !(fs[i] - '0');
            }
            for (int col = modules_per_side - 8, i = 7; col < modules_per_side; ++col, ++i) {
                matrix[8][col].value = !(fs[i] - '0');
            }
            for (int col = 0; col < 6; ++col) {
                matrix[8][col].value = !(fs[col] - '0');
            }
            matrix[8][7].value = !(fs[6] - '0');
            matrix[8][8].value = !(fs[7] - '0');
            matrix[7][8].value = !(fs[8] - '0');
            for (int row = 5, i = 9; row >= 0; --row, ++i) {
                matrix[row][8].value = !(fs[i] - '0');
            }
        }

        int horizontalPenalty1(std::vector<std::vector<QR::Module>>& matrix) {
            int penalty = 0;
            for (auto& row : matrix) {
                int counter = 0;
                for (int i = 0, j = 0; j < matrix[0].size(); ++j) {
                    if (row[j].value == row[i].value) {
                        ++counter;
                        if (counter == 5) {
                            penalty += 3;
                        }
                        else if (counter > 5) {
                            ++penalty;
                        }
                    }
                    else {
                        counter = 1;
                        i = j;
                    }
                }
            }
            return penalty;
        }

        int verticalPenalty1(std::vector<std::vector<QR::Module>>& matrix) {
            int penalty = 0;
            for (int col = 0; col < matrix[0].size(); ++col) {
                int counter = 0;
                for (int i = 0, j = 0; j < matrix.size(); ++j) {
                    if (matrix[j][col].value == matrix[i][col].value) {
                        ++counter;
                        if (counter == 5) {
                            penalty += 3;
                        }
                        else if (counter > 5) {
                            ++penalty;
                        }
                    }
                    else {
                        counter = 1;
                        i = j;
                    }
                }
            }
            return penalty;
        }

        int calculatePenalty1(std::vector<std::vector<QR::Module>>& matrix) {
            return horizontalPenalty1(matrix) + verticalPenalty1(matrix);
        }

        int calculatePenalty2(std::vector<std::vector<QR::Module>> &matrix) {
            int penalty = 0;
            for (int row = 0; row < matrix.size() - 1; ++row) {
                for (int col = 0; col < matrix[0].size() - 1; ++col) {
                    if (matrix[row][col].value == matrix[row + 1][col].value && matrix[row][col].value == matrix[row][col + 1].value && matrix[row][col].value == matrix[row + 1][col + 1].value) {
                        penalty += 3;
                    }
                }
            }
            return penalty;
        }

        int calculatePenalty3(std::vector<std::vector<QR::Module>>& matrix) {
            int penalty = 0;
            std::vector<bool> pattern1 = {false,true,false,false,false,true,false,true,true,true,true};
            std::vector<bool> pattern2 = {true,true,true,true,false,true,false,false,false,true,false};

            // horizontal search
            for (int row = 0; row < matrix.size(); ++row) {
                for (int col = 0; col < matrix[0].size() - 10; ++col) {
                    std::vector<bool> pattern(11);
                    for (int n = 0; n < 11; ++n) {
                        pattern[n] = matrix[row][col + n].value;
                    }
                    if (pattern == pattern1 || pattern == pattern2) {
                        penalty += 40;
                    }
                }
            }

            // vertical search
            for (int col = 0; col < matrix[0].size(); ++col) {
                for (int row = 0; row < matrix.size() - 10; ++row) {
                    std::vector<bool> pattern(11);
                    for (int n = 0; n < 11; ++n) {
                        pattern[n] = matrix[row + n][col].value;
                    }
                    if (pattern == pattern1 || pattern == pattern2) {
                        penalty += 40;
                    }
                }
            }

            return penalty;
        }

        int calculatePenalty4(std::vector<std::vector<QR::Module>>& matrix) {
            int penalty = 0;
            int total_cells = matrix.size() * matrix[0].size();
            int dark_cells = 0;
            for (const auto& row : matrix) {
                for (const auto& item : row) {
                    dark_cells += !item.value;
                }
            }
            double percent_of_dark = (1.0 * dark_cells / total_cells) * 100;
            int prev_multiple_five =  5 * (static_cast<int>(percent_of_dark) / 5);
            int next_multiple_five = prev_multiple_five + 5;

            penalty = std::min(std::abs(prev_multiple_five - 50) / 5, std::abs(next_multiple_five - 50) / 5);

            return penalty;
        }

        int calculateTotalPenalty(stringConverter& qrGenerator, std::vector<std::vector<QR::Module>>& matrix, int maskNumber) {
            addFormatString(qrGenerator, matrix, maskNumber);
            return calculatePenalty1(matrix) + calculatePenalty2(matrix) + calculatePenalty3(matrix) +
                    calculatePenalty4(matrix);
        }

    } //namespace utility

} //namespace QR
