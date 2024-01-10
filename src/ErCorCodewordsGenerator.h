#pragma once

#include "domain.h"
#include "polynomialGenerator.h"
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
        inline ErrorCorInfo calcInfo(int version, ErrorCorLevel corLevel) {
            ErrorCorInfo corInfo;
            switch (corLevel) {
                case L:
                    switch (version) {
                        case 1:
                            corInfo = {L, 1, 7, 19};
                            break;
                        case 2:
                            corInfo = {L, 1, 10, 34};
                            break;
                        case 3:
                            corInfo = {L, 1, 15, 55};
                            break;
                        case 4:
                            corInfo = {L, 1, 20, 80};
                            break;
                    }
                case M:
                    switch (version) {
                        case 1:
                            corInfo = {M, 1, 10, 16};
                            break;
                        case 2:
                            corInfo = {M, 1, 16, 28};
                            break;
                        case 3:
                            corInfo = {M, 1, 26, 44};
                            break;
                        case 4:
                            corInfo = {M, 2, 18, 32};
                            break;
                    }
                case Q:
                    switch (version) {
                        case 1:
                            corInfo = {Q, 1, 13, 13};
                            break;
                        case 2:
                            corInfo = {Q, 1, 22, 22};
                            break;
                        case 3:
                            corInfo = {Q, 2, 18, 17};
                            break;
                        case 4:
                            corInfo = {Q, 2, 26, 24};
                            break;
                    }
                case H:
                    switch (version) {
                        case 1:
                            corInfo = {H, 1, 17, 9};
                            break;
                        case 2:
                            corInfo = {H, 1, 28, 16};
                            break;
                        case 3:
                            corInfo = {H, 2, 22, 13};
                            break;
                        case 4:
                            corInfo = {H, 4, 16, 9};
                            break;
                    }
            }
            return corInfo;
        }

        inline std::vector<int> findGen(int version, ErrorCorLevel corLevel) {
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