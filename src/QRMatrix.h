#pragma once
#include "domain.h"
#include "FormatStringGenerator.h"
#include <iostream>
#include <string>
#include <vector>

namespace QR {
    class QRMatrix {
    public:
        explicit QRMatrix(const std::string& binary_data, int modules_per_side = 33);
        virtual ~QRMatrix() = default;
        void print() const;
        int getModulesCount() const { return modules_per_side_; };
        std::vector<std::vector<QR::Module>> getMatrixData() const { return matrix_; };

    private:
        ErrorCorLevel corLevel_;
        const std::string& binary_data_;
        int modules_per_side_;
        std::vector<std::vector<QR::Module>> matrix_;

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
        void applyMaskPattern(int maskNumber = 1);
    };
} //namespace QR

