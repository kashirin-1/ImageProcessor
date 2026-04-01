#pragma once

#include "base_filters.h"

class BlurFilter : public Filter {
public:
    explicit BlurFilter(std::vector<float> args);

    void Apply(BMPImage& image) override;

private:
    float sigma_;
};