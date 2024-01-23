#include "QRMatrix.h"
#include "penalty_calculation.cpp"

namespace QR {
    QRMatrix::QRMatrix(QRGenerator& qrGenerator, const std::string& binary_data) : qrGenerator_(qrGenerator), binary_data_(binary_data) {
        modules_per_side_ = utility::getMatrixSize(qrGenerator.getQRInfo().version);
        std::vector<std::vector<QR::Module>> matrix(modules_per_side_, std::vector<QR::Module>(modules_per_side_));
        matrix_ = (std::move(matrix));
        addFinderPatterns();
        addSeparators();
        if (qrGenerator.getQRInfo().version != 1) {
            addAlignmentPatterns();
        }
        addTimingPatterns();
        addDarkModule();
        reserveFormatInfoArea();
        placeDataBits();

        int optimal_mask_pattern = findOptimalMask(matrix_);
        applyMaskPattern(matrix_,optimal_mask_pattern);
        addFormatString(qrGenerator, matrix_,optimal_mask_pattern);
    };

    void QRMatrix::addFinderPattern(std::pair<int, int> top_left_index) {
        for (int row = top_left_index.first; row < top_left_index.first + 7; ++row) {
            for (int col = top_left_index.second; col < top_left_index.second + 7; ++col) {
                matrix_[row][col].function_pattern = true;
            }
        }
        for (int row = top_left_index.first + 1; row < top_left_index.first + 6; ++row) {
            matrix_[row][top_left_index.second + 1].value = true;
            matrix_[row][top_left_index.second + 5].value = true;
        }
        for (int col = top_left_index.second + 2; col < top_left_index.second + 5; ++col) {
            matrix_[top_left_index.first + 1][col].value = true;
            matrix_[top_left_index.first + 5][col].value = true;
        }
    }

    void QRMatrix::addFinderPatterns() {
        addFinderPattern({0,0});
        addFinderPattern({modules_per_side_ - 7,0});
        addFinderPattern({0,modules_per_side_ - 7});
    }

    void QRMatrix::addSeparators() {
        for (int row = 0; row < 8; ++row) {
            matrix_[row][7].function_pattern = true;
            matrix_[row][7].value = true;
            matrix_[row][modules_per_side_ - 8].function_pattern = true;
            matrix_[row][modules_per_side_ - 8].value = true;
        }
        for (int row = modules_per_side_ - 7; row < modules_per_side_; ++row) {
            matrix_[row][7].function_pattern = true;
            matrix_[row][7].value = true;
        }
        for (int col = 0; col < 8; ++col) {
            matrix_[7][col].function_pattern = true;
            matrix_[7][col].value = true;
            matrix_[modules_per_side_ - 8][col].function_pattern = true;
            matrix_[modules_per_side_ - 8][col].value = true;
        }
        for (int col = modules_per_side_ - 7; col < modules_per_side_; ++col) {
            matrix_[7][col].function_pattern = true;
            matrix_[7][col].value = true;
        }
    }

    void QRMatrix::addAlignmentPatterns() {
        for (int row = modules_per_side_ - 9; row < modules_per_side_ - 4; ++row) {
            for (int col = modules_per_side_ - 9; col < modules_per_side_ - 4; ++col) {
                matrix_[row][col].function_pattern = true;
            }
        }
        for (int row = modules_per_side_ - 8; row < modules_per_side_ - 5; ++row) {
            matrix_[row][modules_per_side_ - 8].value = true;
            matrix_[row][modules_per_side_ - 6].value = true;
        }
        matrix_[modules_per_side_ - 8][modules_per_side_ - 7].value = true;
        matrix_[modules_per_side_ - 6][modules_per_side_ - 7].value = true;
    }

    void QRMatrix::addTimingPatterns() {
        for (int row = 8; row < modules_per_side_ - 8; ++row) {
            matrix_[row][6].function_pattern = true;
            if (row % 2 != 0) {
                matrix_[row][6].value = true;
            }
        }
        for (int col = 8; col < modules_per_side_ - 8; ++col) {
            matrix_[6][col].function_pattern = true;
            if (col % 2 != 0) {
                matrix_[6][col].value = true;
            }
        }
    }

    void QRMatrix::addDarkModule() {
        matrix_[modules_per_side_ - 8][8].function_pattern = true;
    }

    void QRMatrix::reserveFormatInfoArea() {
        for (int row = 0; row < 9; ++row) {
            matrix_[row][8].function_pattern = true;
        }
        for (int row = modules_per_side_ - 7; row < modules_per_side_; ++row) {
            matrix_[row][8].function_pattern = true;
        }
        for (int col = 0; col < 8; ++col) {
            matrix_[8][col].function_pattern = true;
        }
        for (int col = modules_per_side_ - 8; col < modules_per_side_; ++col) {
            matrix_[8][col].function_pattern = true;
        }
    }

    void QRMatrix::addFormatString(QRGenerator& qrGenerator, std::vector<std::vector<QR::Module>>& matrix, int maskNumber) {
        QR::FormatStringGenerator fsg(qrGenerator.getQRInfo().corLevel, maskNumber);
        std::string fs = fsg.getFormatString();
        int modules_per_side = utility::getMatrixSize(qrGenerator.getQRInfo().version);

        for (int row = modules_per_side - 1, i = 0; row > modules_per_side - 8; --row, ++i) {
            matrix[row][8].value = fs[i] - '0';
        }
        for (int col = modules_per_side - 8, i = 7; col < modules_per_side; ++col, ++i) {
            matrix[8][col].value = fs[i] - '0';
        }
        for (int col = 0; col < 6; ++col) {
            matrix[8][col].value = fs[col] - '0';
        }
        matrix[8][7].value = fs[6] - '0';
        matrix[8][8].value = fs[7] - '0';
        matrix[7][8].value = fs[8] - '0';
        for (int row = 5, i = 9; row >= 0; --row, ++i) {
            matrix[row][8].value = fs[i] - '0';
        }
    }

    void QRMatrix::upwardPlacement(int& col, int& data_index) {
        for (int row = modules_per_side_ - 1; row >= 0; --row) {
            if (!matrix_[row][col].function_pattern) {
                matrix_[row][col].value = !(binary_data_[data_index] - '0');
                ++data_index;
            }
            if (!matrix_[row][col - 1].function_pattern) {
                matrix_[row][col - 1].value = !(binary_data_[data_index]- '0');
                ++data_index;
            }
        }
        col -= 2;
    }

    void QRMatrix::downwardPlacement(int& col, int& data_index) {
        for (int row = 0; row < modules_per_side_; ++row) {
            if (!matrix_[row][col].function_pattern) {
                matrix_[row][col].value = !(binary_data_[data_index] - '0');
                ++data_index;
            }
            if (!matrix_[row][col - 1].function_pattern) {
                matrix_[row][col - 1].value = !(binary_data_[data_index] - '0');
                ++data_index;
            }
        }
        col -= 2;
    }

    void QRMatrix::placeDataBits() {
        int data_index = 0;
        int col = modules_per_side_ - 1;
        while (col > 6) {
            upwardPlacement(col, data_index);
            if (col > 6) {
                downwardPlacement(col, data_index);
            }
        }
        --col;
        downwardPlacement(col, data_index);
        upwardPlacement(col, data_index);
        downwardPlacement(col, data_index);
    }

    void QRMatrix::applyMaskPattern(std::vector<std::vector<QR::Module>>& matrix, int maskNumber) {
        if (maskNumber == 0) {
            for (int row = 0; row < matrix.size(); ++row) {
                for (int col = 0; col < matrix[0].size(); ++col) {
                    if (!matrix[row][col].function_pattern && (row + col) % 2 == 0) {
                        matrix[row][col].value = !matrix[row][col].value;
                    }
                }
            }
        }
        else if (maskNumber == 1) {
            for (int row = 0; row < matrix.size(); ++row) {
                if (row % 2 == 0) {
                    for (int col = 0; col < matrix[0].size(); ++col) {
                        if (!matrix[row][col].function_pattern) {
                            matrix[row][col].value = !matrix[row][col].value;
                        }
                    }
                }
            }
        }
        else if (maskNumber == 2) {
            for (auto & row : matrix) {
                for (int col = 0; col < matrix[0].size(); ++col) {
                    if (!row[col].function_pattern && col % 3 == 0) {
                        row[col].value = !row[col].value;
                    }
                }
            }
        }
        else if (maskNumber == 3) {
            for (int row = 0; row < matrix.size(); ++row) {
                for (int col = 0; col < matrix[0].size(); ++col) {
                    if (!matrix[row][col].function_pattern && (row + col) % 3 == 0) {
                        matrix[row][col].value = !matrix[row][col].value;
                    }
                }
            }
        }
        else if (maskNumber == 4) {
            for (int row = 0; row < matrix.size(); ++row) {
                for (int col = 0; col < matrix[0].size(); ++col) {
                    if (!matrix[row][col].function_pattern && static_cast<int>(std::floor(row / 2) + std::floor(col / 3)) % 2 == 0) {
                        matrix[row][col].value = !matrix[row][col].value;
                    }
                }
            }
        }
        else if (maskNumber == 5) {
            for (int row = 0; row < matrix.size(); ++row) {
                for (int col = 0; col < matrix[0].size(); ++col) {
                    if (!matrix[row][col].function_pattern && ((row * col) % 2) + ((row * col) % 3) == 0) {
                        matrix[row][col].value = !matrix[row][col].value;
                    }
                }
            }
        }
        else if (maskNumber == 6) {
            for (int row = 0; row < matrix.size(); ++row) {
                for (int col = 0; col < matrix[0].size(); ++col) {
                    if (!matrix[row][col].function_pattern && (((row * col) % 2) + ((row * col) % 3)) % 2 == 0) {
                        matrix[row][col].value = !matrix[row][col].value;
                    }
                }
            }
        }
        else if (maskNumber == 7) {
            for (int row = 0; row < matrix.size(); ++row) {
                for (int col = 0; col < matrix[0].size(); ++col) {
                    if (!matrix[row][col].function_pattern && (((row + col) % 2) + ((row * col) % 3)) % 2 == 0) {
                        matrix[row][col].value = !matrix[row][col].value;
                    }
                }
            }
        }
    }

    int QRMatrix::findOptimalMask(std::vector<std::vector<QR::Module>>& matrix) {
        std::vector<int> total_penalties(8);
        for (int mask_pattern = 0; mask_pattern < 8; ++mask_pattern) {
            std::vector<std::vector<QR::Module>> temp_matrix = matrix;
            applyMaskPattern(temp_matrix, mask_pattern);
            total_penalties[mask_pattern] = QR::utility::calculateTotalPenalty(qrGenerator_, temp_matrix, mask_pattern);
        }
        int optimal_mask = 0;
        int min_penalty = total_penalties[0];

        for (int mask_pattern = 0; mask_pattern < 8; ++mask_pattern) {
#ifdef DEBUG
            std::cout << "Mask pattern = " << mask_pattern << " penalties = " << total_penalties[mask_pattern] << std::endl;
#endif
            if (total_penalties[mask_pattern] < min_penalty) {
                min_penalty = total_penalties[mask_pattern];
                optimal_mask = mask_pattern;
            }
        }
#ifdef DEBUG
        std::cout << "Optimal mask pattern = " << optimal_mask << " penalties = " << total_penalties[optimal_mask] << std::endl;
#endif
        return optimal_mask;
    }

    void QRMatrix::print() const {
        for (const auto &row: matrix_) {
            for (const auto &module: row) {
                std::cout << module.value + module.function_pattern * 2 << "  ";
            }
            std::cout << std::endl;
        }
    }
} //namespace QR

