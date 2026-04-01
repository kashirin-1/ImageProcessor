#pragma once

#include "image.h"
#include "base_filters.h"
#include "headers.h"

class GrayscaleFilter : public Filter {
public:
    explicit GrayscaleFilter(std::vector<float> args);
    void Apply(BMPImage& image) override;

private:
};