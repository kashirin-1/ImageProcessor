#pragma once

#include "image.h"
#include "base_filters.h"
#include "headers.h"

class NegativeFilter : public Filter {
public:
    explicit NegativeFilter(std::vector<float> args);
    void Apply(BMPImage& image) override;

private:
};