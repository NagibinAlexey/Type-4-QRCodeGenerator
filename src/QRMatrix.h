#pragma once
#include "domain.h"
#include <iostream>
#include <string>
#include <vector>

namespace QR {
    class QRMatrix {
    public:
        QRMatrix(const std::string& binary_data, int module_size);
        virtual ~QRMatrix() = default;
        void print() const;

    private:
        const std::string& binary_data_;
        int modules_per_side_ = 21; //33
        int module_size_;
        std::vector<std::vector<QR::Module>> matrix_;

        void addFinderPattern(std::pair<int, int> top_left_index);
        void addFinderPatterns();
        void addSeparators();
        void addAlignmentPatterns();
        void addTimingPatterns();
        void addDarkModule();
    };
} //namespace QR

