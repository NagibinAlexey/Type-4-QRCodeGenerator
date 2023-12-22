#include "ErCorCodewordsGenerator.h"
#include "GF256.h"

namespace QR {

    ECCGenerator::ECCGenerator(const std::string& fullBitString, ErrorCorLevel corLevel) {
        err_cor_info = QR::utility::calcInfo(corLevel);
        gp = QR::utility::findGen(corLevel);
        for (int i = 0; i < fullBitString.size() - 1; i += 8) {
            mp.push_back(std::stoi(fullBitString.substr(i, 8), nullptr, 2));
        }
    }

    std::vector<int> ECCGenerator::calcErrCorCodewords(std::vector<int> mp_in_block) {
        std::vector<int> current_gp = gp;
        std::vector<int> prev_step_gp;

        int multiplier = GF256::intToLog[mp_in_block[0]];
        for (auto& coef : current_gp) {
            coef = GF256::logToInt[(GF256::intToLog[coef] + multiplier) % 255];
        }
        while (current_gp.size() != mp_in_block.size()) {
            current_gp.push_back(0);
        }
        for (int i = 0; i < current_gp.size(); ++i) {
            current_gp[i] = mp_in_block[i] ^ current_gp[i];
        }
        current_gp.erase(current_gp.begin());

        int counter = static_cast<int>(mp_in_block.size() - 1);
        while (counter != 0) {
            prev_step_gp = current_gp;
            current_gp = gp;

            multiplier = GF256::intToLog[prev_step_gp[0]];
            for (auto &coef: current_gp) {
                coef = GF256::logToInt[(GF256::intToLog[coef] + multiplier) % 255];
            }
            while (current_gp.size() <= prev_step_gp.size()) {
                current_gp.push_back(0);
            }
            for (int i = 0; i < current_gp.size(); ++i) {
                current_gp[i] = prev_step_gp[i] ^ current_gp[i];
            }
            current_gp.erase(current_gp.begin());
            --counter;
        }

        return {current_gp.begin(), current_gp.begin() + err_cor_info.ecc_per_block_};
    }

    std::string ECCGenerator::generateFinalMessage() {
        std::string binary_message;
        std::vector<int> result;
        std::vector<std::vector<int>> messages_in_blocks;
        std::vector<std::vector<int>> errors_in_blocks;
        int blocks_count = err_cor_info.blocks_count_;
        int block_size = static_cast<int>(mp.size()) / blocks_count;
        for (int block_index = 0; block_index < blocks_count; ++block_index) {
            std::vector<int> mp_in_block(mp.begin() + block_index * block_size, mp.begin() + block_index * block_size + block_size);
            errors_in_blocks.push_back(calcErrCorCodewords(mp_in_block));
            messages_in_blocks.push_back(std::move(mp_in_block));
        }

        for (int i = 0; i < messages_in_blocks[0].size(); ++i) {
            for (int block_index = 0; block_index < blocks_count; ++block_index) {
                result.push_back(messages_in_blocks[block_index][i]);
            }
        }
        for (int i = 0; i < errors_in_blocks[0].size(); ++i) {
            for (int block_index = 0; block_index < blocks_count; ++block_index) {
                result.push_back(errors_in_blocks[block_index][i]);
            }
        }

        std::bitset<8> binary;
        for (int n : result) {
            binary = n;
            binary_message.append(binary.to_string());
        }
        binary_message.append("0000000");
        std::cout << "message length = " << binary_message.size() << std::endl;
        return binary_message;
    }

} //namespace QR