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

        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_compress(&cinfo);
        jpeg_stdio_dest(&cinfo, outfile);

        cinfo.image_width = width;
        cinfo.image_height = height;
        cinfo.input_components = 3;
        cinfo.in_color_space = JCS_RGB;

        jpeg_set_defaults(&cinfo);
        jpeg_set_quality(&cinfo, quality, TRUE);

        jpeg_start_compress(&cinfo, TRUE);

        JSAMPROW row_pointer;

        while (cinfo.next_scanline < cinfo.image_height) {
            row_pointer = &image[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
            jpeg_write_scanlines(&cinfo, &row_pointer, 1);
        }

        jpeg_finish_compress(&cinfo);

        fclose(outfile);

        jpeg_destroy_compress(&cinfo);
    }

    void renderer::renderQRCode(const char* filename, int quality) {
        int modules_count = matrix_.getModulesCount();
        auto color_matrix = matrixToColorArray();

        createJPEG(filename, color_matrix, (modules_count + 8) * module_size_ , (modules_count + 8) * module_size_ , quality);
    }

    unsigned char* renderer::matrixToColorArray() {
        int modules_count = matrix_.getModulesCount();
        int qr_full_size = 3 * (modules_count + 8) * (modules_count + 8) * module_size_ * module_size_; //with quiet zone: a 4-module-wide area of light modules.
        auto color_matrix = new unsigned char[qr_full_size];
        for (int i = 0; i < qr_full_size; ++i) {
            color_matrix[i] = 255;
        }
        int start_data = 3 * module_size_ * module_size_ * (modules_count + 8) * 4 + 3 * module_size_ * 4;

        auto matrix_data = matrix_.getMatrixData();
        int counter = 0;

        for (int row = 0; row < matrix_data.size(); ++row) {
            for (int module_size_row = 0; module_size_row < module_size_; ++module_size_row) {
                for (int col = 0; col < matrix_data[0].size(); ++col) {
                    for (int comp = 0; comp < 3 * module_size_; ++comp) {
                        color_matrix[start_data + counter] = static_cast<int>(matrix_data[row][col].value) * 255;
                        ++counter;
                    }
                }
                counter += 3 * module_size_ * 8;
            }
        }
        return color_matrix;
    }

} // QR