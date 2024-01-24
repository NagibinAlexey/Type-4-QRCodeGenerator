#include <iostream>
#include "analyzer.h"
#include "QRGenerator.h"

int start_program() {

    std::string user_string;
    std::cout << "Write a message to generate a QR code: " << std::endl;
    std::getline(std::cin, user_string);
    QR::Mode mode = QR::analyze(user_string);
    if (mode == QR::Kanji) {
        std::cout << "Sorry, some characters are not supported" << std::endl;
        return 1;
    }

    std::cout << "Select the degree of data recovery: " << std::endl;
    std::cout << "L -             Recovers 7% of data " << std::endl;
    std::cout << "M -             Recovers 15% of data " << std::endl;
    std::cout << "Q -             Recovers 25% of data " << std::endl;
    std::cout << "H -             Recovers 30% of data " << std::endl;

    QR::ErrorCorLevel corLevel;
    std::string corLevel_string;
    std::cin >> corLevel_string;
    while (!(corLevel_string == "L" || corLevel_string == "M" || corLevel_string == "Q" || corLevel_string == "H")) {
        std::cout << "Please enter correct data" << std::endl;
        std::cin >> corLevel_string;
    }
    if (corLevel_string == "L") { corLevel = QR::ErrorCorLevel::L; }
    else if (corLevel_string == "M") { corLevel = QR::ErrorCorLevel::M; }
    else if (corLevel_string == "Q") { corLevel = QR::ErrorCorLevel::Q; }
    else if (corLevel_string == "H") { corLevel = QR::ErrorCorLevel::H; }

    int minQRCodeVersion;
    minQRCodeVersion = QR::getMinQRCodeVersion(user_string, corLevel, mode);

    int QRCodeVersion;
    std::cout << "Select QR Code version from " << minQRCodeVersion << " to 4 from a smaller size to a larger one" << std::endl;
    std::cin >> QRCodeVersion;
    while (!(QRCodeVersion >= minQRCodeVersion && QRCodeVersion <= 4)) {
        std::cout << "Please enter correct data" << std::endl;
        std::cin >> QRCodeVersion;
    }

    QR::generate(user_string, QRCodeVersion, corLevel);
    std::cout << "Done!" << std::endl;

    return 0;
}
