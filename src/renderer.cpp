#include "renderer.h"

namespace QR {
    void renderer::createJPEG(const char *filename, unsigned char *image, int width, int height, int quality) {
        struct jpeg_compress_struct cinfo;
        struct jpeg_error_mgr jerr;

        FILE* outfile = fopen(filename, "wb");
        if (!outfile) {
            fprintf(stderr, "Error");
            return;
        }

        std::cout << "test1" << std::endl;

        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_compress(&cinfo);
        jpeg_stdio_dest(&cinfo, outfile);

        std::cout << "test2" << std::endl;

        cinfo.image_width = width;
        cinfo.image_height = height;
        cinfo.input_components = 3;
        cinfo.in_color_space = JCS_RGB;

        std::cout << "test3" << std::endl;

        jpeg_set_defaults(&cinfo);
        jpeg_set_quality(&cinfo, quality, TRUE);

        jpeg_start_compress(&cinfo, TRUE);

        JSAMPROW row_pointer;

        std::cout << "test4" << std::endl;

        while (cinfo.next_scanline < cinfo.image_height) {
            row_pointer = &image[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
            jpeg_write_scanlines(&cinfo, &row_pointer, 1);
        }

        std::cout << "test5" << std::endl;

        jpeg_finish_compress(&cinfo);

        std::cout << "test6" << std::endl;

        fclose(outfile);

        jpeg_destroy_compress(&cinfo);
        std::cout << "test7" << std::endl;
    }

    void renderer::renderQRCode(const char* filename, int quality) {
        int modules_count = matrix_.getModulesCount();
        int qr_full_size = 3 * (modules_count + 0) * (modules_count + 0) * module_size_ * module_size_;
        auto image = new unsigned char[qr_full_size];
        for (int i = 0; i < qr_full_size; ++i) {
            image[i] = 255;
        }

        auto matrix_data = matrix_.getMatrixData();
        int counter = 0;
        for (const auto& row : matrix_data) {
            for (int module_size_row = 0; module_size_row < module_size_; ++module_size_row) {
                for (const auto &module: row) {
                    for (int comp = 0; comp < 3 * module_size_; ++comp) {
                        image[counter] = static_cast<int>(module.value) * 255;
                        ++counter;
                    }
                }
            }
        }

        std::cout << "test8" << std::endl;
        createJPEG(filename, image, (modules_count + 0) * module_size_ , (modules_count + 0)* module_size_ , quality);
        delete[] image;
    }

} // QR