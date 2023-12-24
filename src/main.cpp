#include <iostream>
#include "QRGenerator.h"
#include "ErCorCodewordsGenerator.h"
#include "GF256.h"
#include "QRMatrix.h"
#include <jpeglib.h>

void createJPEG(const char* filename, unsigned char* image, int width, int height, int quality) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE* outfile = fopen(filename, "wb");
    if (!outfile) {
        std::cout << "failed to open" << std::endl;
        return;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, true);

    jpeg_start_compress(&cinfo, true);

    JSAMPROW row_pointer;

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer = &image[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
        jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);

    jpeg_destroy_compress(&cinfo);
}

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

        const char* filename = "image.jpg";
        unsigned char* image = new unsigned char[33*33*3];

        for (int i = 0; i < 33*33*3; ++i) {
            image[i] = (i % 2) * 255;
        }

        createJPEG(filename, image, 33, 33, 90);
        delete[] image;
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