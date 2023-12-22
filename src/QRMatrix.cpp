#include "QRMatrix.h"

namespace QR {
    QRMatrix::QRMatrix(const std::string& binary_data, int module_size) : binary_data_(binary_data), module_size_(module_size) {
        std::vector<std::vector<QR::Module>> matrix(modules_per_side_, std::vector<QR::Module>(modules_per_side_));
        matrix_ = (std::move(matrix));
        addFinderPatterns();
        addSeparators();
        addAlignmentPatterns();
        addTimingPatterns();
        addDarkModule();
        reserveFormatInfoArea();
        int temp = 0;
        for (auto v : matrix_) {
            for (auto e : v) {
                if (!e.function_pattern) ++temp;
            }
        }
        std::cout << "cells for data = " << temp << std::endl;

        placeDataBits();
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
        for (int row = 0; row <= modules_per_side_ - 1; ++row) {
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
            downwardPlacement(col, data_index);
        }
        --col;
        downwardPlacement(col, data_index);
        upwardPlacement(col, data_index);
        downwardPlacement(col, data_index);
    }

    void QRMatrix::print() const {
        for (const auto& row : matrix_) {
            for (const auto& module : row) {
                std::cout << module.value + module.function_pattern * 2 << "  ";
            }
            std::cout << std::endl;
        }
    }

} //namespace QR

