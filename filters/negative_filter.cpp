#include "negative_filter.h"
#include <stdexcept>

NegativeFilter::NegativeFilter(std::vector<float> arguments) {
    if (!arguments.empty()) {
        throw std::runtime_error("Too many args for Negative Filter");
    }
}

void NegativeFilter::Apply(BMPImage& image) {
    DIBHeader image_dib_headers = image.GetDibHeaders();
    int width = image_dib_headers.width;
    int height = abs(image_dib_headers.height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel pix = image.GetPixel(x, y);
            pix.blue = 1 - pix.blue;
            pix.green = 1 - pix.green;
            pix.red = 1 - pix.red;
            image.SetPixel(x, y, pix);
        }
    }
}