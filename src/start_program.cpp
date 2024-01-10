#include <iostream>
#include "QRGenerator.h"
#include "ErCorCodewordsGenerator.h"
#include "FormatStringGenerator.h"
#include "renderer.h"

int start_program() {

    QR::QRGenerator generator("HELLO WORLD", 4,QR::ErrorCorLevel::L);
    //generator.print();
    QR::ECCGenerator eccGenerator(generator.getFullBitString(), generator.getQRCodeVersion(),QR::ErrorCorLevel::L);
    //eccGenerator.print();
    //std::cout << std::endl;
    std::string fm = eccGenerator.generateFinalMessage();
    for (auto c : fm) {
        std::cout << c;
    }
    std::cout << std::endl;
    QR::QRMatrix matrix(fm);
    matrix.print();

    //QR::renderer renderer(matrix);
    //renderer.renderQRCode("QRCode.jpg", 90);

    //QR::generatePolynomial(18);

    return 0;
}
