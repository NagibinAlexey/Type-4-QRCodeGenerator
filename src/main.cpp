#include <iostream>
#include "QRGenerator.h"
#include "ErCorCodewordsGenerator.h"
#include "GF256.h"
#include "QRMatrix.h"

int main(int argc, char** argv) {

    if (argc == 1) {
        QR::QRGenerator generator("HELLO WORLD", QR::ErrorCorLevel::L);
        QR::ECCGenerator eccGenerator(generator.getFullBitString(), QR::ErrorCorLevel::L);
        eccGenerator.print();
        std::cout << std::endl;
        std::string fm = eccGenerator.generateFinalMessage();
        for (auto c : fm) {
            std::cout << c;
        }
        std::cout << std::endl;
        QR::QRMatrix matrix(fm,10);
        matrix.print();
    } else {
        std::string filename = argv[1];

        std::ifstream stream(filename, std::ios::binary);
        if (!stream.is_open())
            std::cout << "failed to open " << filename << '\n';
        else {
            QR::QRGenerator generator(stream);
            generator.print();
        }
    }

    return 0;
}