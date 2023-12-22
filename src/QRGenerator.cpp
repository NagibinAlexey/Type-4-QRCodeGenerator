#include "QRGenerator.h"
#include "analyzer.h"

namespace QR {
    void QRGenerator::print() {
        std::cout << "Mode - " << mode_ << std::endl;
        std::cout << data_ << std::endl;
        std::cout << "Capacity = " << capacity_ << std::endl;
        std::cout << generateFullBitString() << std::endl;
    }

    QRGenerator::QRGenerator(std::ifstream &stream, ErrorCorLevel level) : data_((std::istreambuf_iterator<char>(stream)),
                                                                std::istreambuf_iterator<char>()), corLevel(level) {
        mode_ = QR::analyze(data_);
        capacity_ = getCapacity();
    }

    QRGenerator::QRGenerator(std::string string, ErrorCorLevel level) : data_(std::move(string)), corLevel(level) {
        mode_ = QR::analyze(data_);
        capacity_ = getCapacity();
    }

    std::string QRGenerator::generateFullBitString() {
        std::string full_binary_data_;
        full_binary_data_.reserve(capacity_);

        int char_count = static_cast<int>(data_.size());

        std::string mode_indicator;
        switch (mode_) {
            case Numeric :
                mode_indicator = "0001";
                mode_indicator.append(std::bitset<10>(char_count).to_string());
                break;
            case Alphanumeric :
                mode_indicator = "0010";
                mode_indicator.append(std::bitset<9>(char_count).to_string());
                break;
            case Byte :
                mode_indicator = "0100";
                mode_indicator.append(std::bitset<8>(char_count).to_string());
                break;
            case Kanji :
                mode_indicator = "1000";
                mode_indicator.append(std::bitset<8>(char_count).to_string());
                break;
        }

        full_binary_data_.append(mode_indicator);
        full_binary_data_.append(generateBinaryData());

        int empty_data = capacity_ - static_cast<int>(full_binary_data_.size());
        if (empty_data >= 4) {
            full_binary_data_.append("0000");
            while (full_binary_data_.size() % 8 != 0) {
                full_binary_data_.push_back('0');
            }
        } else {
            while (full_binary_data_.size() != capacity_) {
                full_binary_data_.push_back('0');
            }
        }

        while (full_binary_data_.size() != capacity_) {
            full_binary_data_.append("11101100");
            full_binary_data_.append("00010001");
        }
        return full_binary_data_;
    }

    std::string QRGenerator::generateBinaryData() {
        std::string binary_data_;
        std::bitset<8> binary;
        for (char c : data_) {
            binary = c;
            binary_data_.append(binary.to_string());
        }
        return binary_data_;
    }

    int QRGenerator::getCapacity() {
        switch (corLevel) {
            case L:
                return 80 * 8;
            case M:
                return 64 * 8;
            case Q:
                return 48 * 8;
            case H:
                return 36 * 8;
        }
    }
} //namespace QR

