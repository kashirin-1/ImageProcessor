#include "base_filters.h"
#include <stdexcept>

void MatrixFilter::Apply(BMPImage& image) {
    DIBHeader image_dib_headers = image.GetDibHeaders();
    int width = image_dib_headers.width;
    int height = abs(image_dib_headers.height);
    if (matrix_.empty()) {
        throw std::runtime_error("filter matrix is empty");
    }
    int shift_x = width_ / 2;
    int shift_y = heigth_ / 2;
    std::vector<Pixel> pixel_data = image.GetImage();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel current_pix = image.GetPixel(x, y);
            float blue_sum = 0.0f;
            float green_sum = 0.0f;
            float red_sum = 0.0f;
            for (int i = 0; i < heigth_; i++) {
                for (int j = 0; j < width_; j++) {
                    int current_x = Clamp(x + (shift_x - j), 0, width - 1);
                    int current_y = Clamp(y + (shift_y - i), 0, height - 1);
                    Pixel current_pixel = pixel_data[current_y * width + current_x];
                    blue_sum += matrix_[i * width_ + j] * current_pixel.blue;
                    green_sum += matrix_[i * width_ + j] * current_pixel.green;
                    red_sum += matrix_[i * width_ + j] * current_pixel.red;
                }
            }
            current_pix.blue = std::min(1.0f, std::max(0.0f, blue_sum));
            current_pix.green = std::min(1.0f, std::max(0.0f, green_sum));
            current_pix.red = std::min(1.0f, std::max(0.0f, red_sum));
            image.SetPixel(x, y, current_pix);
        }
    }
}