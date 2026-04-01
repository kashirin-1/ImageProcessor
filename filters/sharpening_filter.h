#pragma once

#include "base_filters.h"

class Sharpening : public MatrixFilter {
public:
    explicit Sharpening(std::vector<float> arguments);
};