#include <iostream>
#include "QRGenerator.h"
#include "ErCorCodewordsGenerator.h"
#include "FormatStringGenerator.h"
#include "renderer.h"

int start_program() {

    QR::QRGenerator generator("HELLO WORLD", 2,QR::ErrorCorLevel::Q);
    QR::ECCGenerator eccGenerator(generator);
    std::string fm = eccGenerator.generateFinalMessage();
    QR::QRMatrix matrix(generator, fm);

    QR::renderer renderer(matrix);
    renderer.renderQRCode("QRCode.jpg", 90);

    return 0;
}
