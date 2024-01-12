#pragma once
#include <string>
#include <vector>

namespace QR {
    enum Mode {
        Numeric,
        Alphanumeric,
        Byte,
        Kanji
    };

    static std::string ModeMap[] = { "Numeric", "Alphanumeric","Byte", "Kanji" };

    enum ErrorCorLevel {
        L,                 //Recovers 7% of data
        M,                 //Recovers 15% of data
        Q,                 //Recovers 25% of data
        H                  //Recovers 30% of data
    };

    struct ErrorCorInfo {
        ErrorCorLevel level = L;
        int blocks_count_ = 1;      // Number of Error Correction Blocks
        int ecc_per_block_ = 20;     // Error Correction Codewords per Block
        int dc_per_block_ = 80;      // Data Codewords per Block
    };

    struct Module {
        bool value = false;
        bool function_pattern = false;
    };

    struct QRGeneratorInfo {
        Mode mode;
        ErrorCorLevel corLevel;
        int version;
        int minimum_version;
    };

} //namespace QR
