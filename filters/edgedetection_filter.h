#pragma once

#include "base_filters.h"

class EdgeDetection : public MatrixFilter {
public:
    explicit EdgeDetection(std::vector<float> arguments);
    void Apply(BMPImage& image) override;

private:
    float threshold_;
};