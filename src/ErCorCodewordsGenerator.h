#pragma once

#include "domain.h"
#include "polynomialGenerator.h"
#include "QRGenerator.h"
#include <string>
#include <vector>
#include <iostream>
#include <bitset>

namespace QR {
    class ECCGenerator final {
    public:
        explicit ECCGenerator(QRGenerator& qrGenerator);
        ~ECCGenerator() = default;

        std::vector<int> calcErrCorCodewords(std::vector<int> mp_in_block);
        std::string generateFinalMessage();

        [[nodiscard]] std::vector<int> getMP() const { return mp; }

    private:
        ErrorCorInfo err_cor_info;
        std::vector<int> gp;
        std::vector<int> mp;
        int remainderBits = 7;
    };

    namespace utility {
        inline ErrorCorInfo calcInfo(int version, ErrorCorLevel corLevel) {
            ErrorCorInfo corInfo;
                if (corLevel == QR::ErrorCorLevel::L) {
                        if (version == 1)
                            corInfo = {L, 1, 7, 19};
                        else if (version == 2)
                            corInfo = {L, 1, 10, 34};
                        else if (version == 3)
                            corInfo = {L, 1, 15, 55};
                        else if (version == 4)
                            corInfo = {L, 1, 20, 80};
                }
                else if (corLevel == QR::ErrorCorLevel::M) {
                        if (version == 1)
                            corInfo = {M, 1, 10, 16};
                        else if (version == 2)
                            corInfo = {M, 1, 16, 28};
                        else if (version == 3)
                            corInfo = {M, 1, 26, 44};
                        else if (version == 4)
                            corInfo = {M, 2, 18, 32};
                }
                else if (corLevel == QR::ErrorCorLevel::Q) {
                        if (version == 1)
                            corInfo = {Q, 1, 13, 13};
                        else if (version == 2)
                            corInfo = {Q, 1, 22, 22};
                        else if (version == 3)
                            corInfo = {Q, 2, 18, 17};
                        else if (version == 4)
                            corInfo = {Q, 2, 26, 24};
                }
                else if (corLevel == QR::ErrorCorLevel::H) {
                        if (version == 1)
                            corInfo = {H, 1, 17, 9};
                        else if (version == 2)
                            corInfo = {H, 1, 28, 16};
                        else if (version == 3)
                            corInfo = {H, 2, 22, 13};
                        else if (version == 4)
                            corInfo = {H, 4, 16, 9};
                }
            return corInfo;
        }
    }

} //namespace QR