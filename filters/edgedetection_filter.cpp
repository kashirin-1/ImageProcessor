#include "edgedetection_filter.h"
#include "grayscale_filter.h"
#include <stdexcept>

EdgeDetection::EdgeDetection(std::vector<float> arguments) {
    if (arguments.empty()) {
        throw std::runtime_error("Not enough args for EdgeDetection");
    }
    if (arguments.size() > 1) {
        throw std::runtime_error("Too many args for EdgeDetection");
    }
    heigth_ = 3;
    width_ = 3;
    matrix_ = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    threshold_ = arguments[0];
}

void EdgeDetection::Apply(BMPImage& image) {
    GrayscaleFilter new_filter({});
    new_filter.Apply(image);
    MatrixFilter::Apply(image);
    DIBHeader image_dib_headers = image.GetDibHeaders();
    int width = image_dib_headers.width;
    int height = abs(image_dib_headers.height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel pix = image.GetPixel(x, y);
            if (pix.blue > threshold_) {
                image.SetPixel(x, y, {1.0f, 1.0f, 1.0f});
            } else {
                image.SetPixel(x, y, {0.0f, 0.0f, 0.0f});
            }
        }
    }
}