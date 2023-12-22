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

    static std::vector<int> generator_polynomial10 = {1,216,194,159,111,199,94,95,113,157,193};
    static std::vector<int> generator_polynomial16 = {1,59,13,104,189,68,209,30,8,163,65,41,229,98,50,36,59};
    static std::vector<int> generator_polynomial18 = {1,239,251,183,113,149,175,199,215,240,220,73,82,173,75,32,67,217,146};
    static std::vector<int> generator_polynomial20 = {1,152,185,240,5,61,111,6,220,112,180,150,36,187,22,228,198,121,121,165,174};
    static std::vector<int> generator_polynomial26 = {1,246,51,183,4,136,98,199,152,77,56,206,24,145,40,209,117,233,42,135,68,70,144,146,77,43,94};

    struct Module {
        bool value = false;
        bool function_pattern = false;
    };

} //namespace QR
