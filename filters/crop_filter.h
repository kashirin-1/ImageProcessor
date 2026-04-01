#pragma once

#include "image.h"
#include "base_filters.h"
#include "headers.h"

class CropFilter : public Filter {
public:
    explicit CropFilter(std::vector<float> args);
    CropFilter(int width, int height);
    void Apply(BMPImage& image) override;

private:
    int width_;
    int height_;
};