#include "blur_filter.h"
#include <stdexcept>
#include <cmath>

const float GAUSSIANDENOMINATOR = 2.0f;

BlurFilter::BlurFilter(std::vector<float> args) {
    if (args.empty()) {
        throw std::runtime_error("Not enough args for Blur Filter");
    }
    if (args.size() > 1) {
        throw std::runtime_error("Too many args for Blur Filter");
    }
    sigma_ = args[0];
}

void BlurFilter::Apply(BMPImage& image) {
    int radius = ceil(3 * sigma_);
    std::vector<float> kernel(2 * radius + 1);
    float sum = 0.0f;
    for (int i = -radius; i <= radius; i++) {
        kernel[i + radius] =
            expf(static_cast<float>(-i) * static_cast<float>(i) / (GAUSSIANDENOMINATOR * sigma_ * sigma_));
        sum += kernel[i + radius];
    }
    for (auto& el : kernel) {
        el /= sum;
    }

    DIBHeader image_dib_headers = image.GetDibHeaders();
    int width = image_dib_headers.width;
    int height = abs(image_dib_headers.height);
    std::vector<Pixel> data = image.GetImage();
    std::vector<Pixel> tmp(height * width);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float blue = 0.0f;
            float green = 0.0f;
            float red = 0.0f;
            for (int i = -radius; i <= radius; i++) {
                int current_x = Clamp(x + i, 0, width - 1);
                Pixel pix = data[width * y + current_x];
                blue += kernel[radius + i] * pix.blue;
                green += kernel[radius + i] * pix.green;
                red += kernel[radius + i] * pix.red;
            }
            tmp[width * y + x] = {blue, green, red};
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float blue = 0.0f;
            float green = 0.0f;
            float red = 0.0f;
            for (int i = -radius; i <= radius; i++) {
                int current_y = Clamp(y + i, 0, height - 1);
                Pixel pix = tmp[width * current_y + x];
                blue += kernel[radius + i] * pix.blue;
                green += kernel[radius + i] * pix.green;
                red += kernel[radius + i] * pix.red;
            }
            image.SetPixel(x, y, {blue, green, red});
        }
    }
}