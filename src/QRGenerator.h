#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <bitset>
#include "domain.h"

namespace QR {
    class QRGenerator {
    public:
        explicit QRGenerator(std::string string, int version = 4, ErrorCorLevel level = L);
        virtual ~QRGenerator() = default;
        void print();
        [[nodiscard]] int getQRCodeVersion() const;
        std::string getFullBitString();
        void setCapacity(int capacity);

    private:
        std::string data_;
        Mode mode_;
        ErrorCorLevel corLevel;
        int capacity_;
        int version_;
        int minimum_version_;

        std::string generateFullBitString();

        std::string generateBinaryData();
        int getCapacity();
    };
} //namespace QR
