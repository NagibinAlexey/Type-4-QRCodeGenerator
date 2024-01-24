#include "QRGenerator.h"

namespace QR {

    void generate(std::string& string, int version, ErrorCorLevel level) {
        QR::stringConverter dataConverter(string, version, level);
        QR::ECCGenerator eccGenerator(dataConverter);
        std::string fm = eccGenerator.generateFinalMessage();
        QR::QRMatrix matrix(dataConverter, fm);

        QR::renderer renderer(matrix);
        renderer.renderQRCode("QRCode.jpg", 90);
    }

} // QR