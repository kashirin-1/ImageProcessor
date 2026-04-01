#pragma once

#include "image.h"
#include "help_functions.h"

class Filter {
public:
    virtual ~Filter() = default;
    virtual void Apply(BMPImage& image) = 0;
};

class MatrixFilter : public Filter {
public:
    void Apply(BMPImage& image) override;

protected:
    int heigth_;
    int width_;
    std::vector<float> matrix_;
};