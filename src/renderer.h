#pragma once
#include <cstddef>
#include <wchar.h>
#include <jpeglib.h>
#include <string>
#include <iostream>
#include "QRMatrix.h"

namespace QR {

    class renderer {
    public:
        explicit renderer(const QRMatrix& matrix, int module_size = 10) : matrix_(matrix), module_size_(module_size) {};
        void renderQRCode(const char* filename, int quality);

    private:
        const QRMatrix& matrix_;
        int module_size_;
        static void createJPEG(const char *filename, unsigned char *image, int width, int height, int quality);
    };

} // QR
