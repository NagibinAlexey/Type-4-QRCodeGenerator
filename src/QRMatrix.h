#pragma once
#include "domain.h"
#include "FormatStringGenerator.h"
#include "QRGenerator.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

namespace QR {
    class QRMatrix {
    public:
        explicit QRMatrix(QRGenerator& qrGenerator, const std::string& binary_data);
        virtual ~QRMatrix() = default;
        void print() const;
        int getModulesCount() const { return modules_per_side_; };
        std::vector<std::vector<QR::Module>> getMatrixData() const { return matrix_; };

    private:
        QRGenerator& qrGenerator_;
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
        void addFormatString(QRGenerator& qrGenerator, std::vector<std::vector<QR::Module>>& matrix, int maskNumber);
        void placeDataBits();
        void upwardPlacement(int& col, int& data_index);
        void downwardPlacement(int& col, int& data_index);
        int findOptimalMask(std::vector<std::vector<QR::Module>>& matrix);
        void applyMaskPattern(std::vector<std::vector<QR::Module>>& matrix, int maskNumber);
    };

} //namespace QR

