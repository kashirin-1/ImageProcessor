#include "crop_filter.h"
#include <stdexcept>

CropFilter::CropFilter(std::vector<float> args) {
    if (args.size() < 2) {
        throw std::runtime_error("Not enough args for Crop Filter");
    }
    if (args.size() > 2) {
        throw std::runtime_error("Too many args for Crop Filter");
    }
    width_ = static_cast<int>(args[0]);
    height_ = static_cast<int>(args[1]);
}

CropFilter::CropFilter(int width, int height) : width_(width), height_(height){};

void CropFilter::Apply(BMPImage& image) {
    DIBHeader image_dib_headers = image.GetDibHeaders();
    int width = std::min(width_, image_dib_headers.width);
    int height = std::min(height_, abs(image_dib_headers.height));
    image_dib_headers.height = height * (image_dib_headers.height > 0 ? 1 : -1);
    image_dib_headers.width = width;
    BMPImage result(image.GetBmpHeaders(), image_dib_headers);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            result.SetPixel(x, y, image.GetPixel(x, y));
        }
    }
    image = result;
}