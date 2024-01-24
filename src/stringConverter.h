#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <bitset>
#include "domain.h"

namespace QR {
    class stringConverter {
    public:
        explicit stringConverter(std::string string, int version = 4, ErrorCorLevel level = L);
        virtual ~stringConverter() = default;
        void print();
        std::string getFullBitString();
        [[nodiscard]] QRGeneratorInfo getQRInfo() const;

    private:
        QRGeneratorInfo info_{};
        std::string data_;
        int capacity_;

        std::string generateFullBitString();

        std::string generateBinaryData();
        int calculateCapacity();
    };
} //namespace QR
