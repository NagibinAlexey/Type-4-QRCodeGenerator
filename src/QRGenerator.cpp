#include "QRGenerator.h"
#include "analyzer.h"
#include "alphanumericConverter.h"
#include "numericConverter.h"

namespace QR {
    void QRGenerator::print() {
        std::cout << generateBinaryData() << std::endl;
        std::cout << generateFullBitString() << std::endl;
    }

    QRGenerator::QRGenerator(std::string string, int version, ErrorCorLevel level) : data_(std::move(string)), corLevel(level) {
        mode_ = QR::analyze(data_);
        try {
            minimum_version_ = QR::getMinQRCodeVersion(data_, level, mode_);
        }
        catch (const std::out_of_range& e) {}

#ifdef DEBUG
        std::cout << "QRCode minimum version = " <<  minimum_version_ << std::endl;
#endif

        if (version < minimum_version_) {
            throw std::out_of_range("This QRCode version is too small");
        }
        version_ = version;
        capacity_ = getCapacity();

#ifdef DEBUG
        std::cout << "String to encode = " << data_ << std::endl;
        std::cout << "Mode - " << QR::ModeMap[mode_] << std::endl;
        std::cout << "Capacity = " << capacity_ << std::endl;
#endif
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

        while (full_binary_data_.size() < capacity_) {
            full_binary_data_.append("11101100");
            if (full_binary_data_.size() < capacity_) {
                full_binary_data_.append("00010001");
            }
        }
        return full_binary_data_;
    }

    std::string QRGenerator::generateBinaryData() {
        if (mode_ == QR::Numeric) {
            return numericToBitString(data_);
        }
        else if (mode_ == QR::Alphanumeric) {
            return alphanumericToBitString(data_);
        }
        return alphanumericToBitString(data_);
    }

    void QRGenerator::setCapacity(int capacity) {
        capacity_ = capacity;
    }

    int QRGenerator::getCapacity() {
        switch (corLevel) {
            case L:
                if (version_ == 1) return 19 * 8;
                else if (version_ == 2) return 34 * 8;
                else if (version_ == 3) return 55 * 8;
                else return 80 * 8;
            case M:
                if (version_ == 1) return 16 * 8;
                else if (version_ == 2) return 28 * 8;
                else if (version_ == 3) return 44 * 8;
                else return 64 * 8;
            case Q:
                if (version_ == 1) return 13 * 8;
                else if (version_ == 2) return 22 * 8;
                else if (version_ == 3) return 34 * 8;
                else return 48 * 8;
            case H:
                if (version_ == 1) return 9 * 8;
                else if (version_ == 2) return 16 * 8;
                else if (version_ == 3) return 26 * 8;
                else return 36 * 8;
        }
    }

    int QRGenerator::getQRCodeVersion() const {
        return version_;
    }

    std::string QRGenerator::getFullBitString() {
        return generateFullBitString();
    }
} //namespace QR

