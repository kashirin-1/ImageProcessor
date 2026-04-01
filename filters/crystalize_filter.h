#pragma once

#include "image.h"
#include "base_filters.h"
#include "headers.h"
#include <random>

int GetRandom(int min, int max);

class CrystalizeFilter : public Filter {
public:
    explicit CrystalizeFilter(std::vector<float> args);
    explicit CrystalizeFilter(int size);
    void Apply(BMPImage& image) override;

private:
    int cell_size_;
};