#pragma once
#include "domain.h"
#include "FormatStringGenerator.h"
#include "QRGenerator.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

namespace QR {
    class QRMatrix final {
    public:
        explicit QRMatrix(QRGenerator& qrGenerator, const std::string& binary_data);
        ~QRMatrix() = default;
        void print() const;
        int getModulesCount() const { return modules_per_side_; };
        std::vector<std::vector<QR::Module>> getMatrixData() const { return matrix_; };

    private:
        ErrorCorLevel corLevel_;
        const std::string& binary_data_;
        int modules_per_side_;
        std::vector<std::vector<QR::Module>> matrix_;

    private:
        void addFinderPattern(std::pair<int, int> top_left_index);
        void addFinderPatterns();
        void addSeparators();
        void addAlignmentPatterns();
        void addTimingPatterns();
        void addDarkModule();
        void reserveFormatInfoArea();
        void addFormatString();
        void placeDataBits();
        void upwardPlacement(int& col, int& data_index);
        void downwardPlacement(int& col, int& data_index);
        int findOptimalMask(std::vector<std::vector<QR::Module>>& matrix);
        void applyMaskPattern(std::vector<std::vector<QR::Module>>& matrix, int maskNumber);
    };

    namespace utility {
        inline int getMatrixSize(int version) {
            switch (version) {
                case 1:
                    return 21;
                case 2:
                    return 25;
                case 3:
                    return 29;
                case 4:
                    return 33;
            }
            return 33;
        }
    }
} //namespace QR

