#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <bitset>
#include "domain.h"

namespace QR {
    class QRGenerator {
    public:
        explicit QRGenerator(std::ifstream& stream, ErrorCorLevel level = H);
        explicit QRGenerator(std::string string, ErrorCorLevel level = H);
        virtual ~QRGenerator() = default;
        void print();
        std::string getFullBitString() {
            return generateFullBitString();
        };

    private:
        std::string data_;
        Mode mode_;
        ErrorCorLevel corLevel;
        int capacity_;

        std::string generateFullBitString();

        std::string generateBinaryData();
        int getCapacity();
    };
} //namespace QR
