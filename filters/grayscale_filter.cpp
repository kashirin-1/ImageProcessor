#include "grayscale_filter.h"
#include <stdexcept>

const float REDCOEFF = 0.299f;
const float GREENCOEFF = 0.587f;
const float BLUECOEFF = 0.114f;

GrayscaleFilter::GrayscaleFilter(std::vector<float> args) {
    if (!args.empty()) {
        throw std::runtime_error("Too many args for Grayscale Filter");
    }
}

void GrayscaleFilter::Apply(BMPImage& image) {
    DIBHeader image_dib_headers = image.GetDibHeaders();
    int width = image_dib_headers.width;
    int height = abs(image_dib_headers.height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel pix = image.GetPixel(x, y);
            pix.blue = pix.green = pix.red = REDCOEFF * pix.red + GREENCOEFF * pix.green + BLUECOEFF * pix.blue;
            image.SetPixel(x, y, pix);
        }
    }
}