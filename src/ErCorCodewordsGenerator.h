#pragma once
#include "domain.h"
#include <string>
#include <vector>
#include <iostream>
#include <bitset>

namespace QR {
    class ECCGenerator final {
    public:
        explicit ECCGenerator(const std::string& fullBitString, int version, ErrorCorLevel corLevel);
        ~ECCGenerator() = default;

        std::vector<int> calcErrCorCodewords(std::vector<int> mp_in_block);
        std::string generateFinalMessage();

        void print() {
            for (const auto coef : mp) {
                std::cout << coef << " ";
            }
        }
        void setGp(std::vector<int> gp_) { gp = std::move(gp_); };

    private:
        ErrorCorInfo err_cor_info;
        std::vector<int> gp;
        std::vector<int> mp;
    };

    namespace utility {
        inline ErrorCorInfo calcInfo(ErrorCorLevel corLevel) {
            ErrorCorInfo corInfo;
            switch (corLevel) {
                case L :
                    corInfo = {L, 1, 20, 80};
                    break;
                case M:
                    corInfo = {M, 2, 18, 32};
                    break;
                case Q:
                    corInfo = {Q, 2, 26, 29};
                    break;
                case H:
                    corInfo = {H, 4, 16, 9};
                    break;
            }
            return corInfo;
        }

        inline std::vector<int> findGen(ErrorCorLevel corLevel) {
            switch (corLevel) {
                case L :
                    return generator_polynomial20;
                case M:
                    return generator_polynomial18;
                case Q:
                    return generator_polynomial26;
                case H:
                    return generator_polynomial16;
            }
            return std::vector<int>{};
        }
    }
} //namespace QR