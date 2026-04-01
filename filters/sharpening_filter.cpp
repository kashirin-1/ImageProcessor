#include "sharpening_filter.h"
#include <stdexcept>

const int CENTERCOEFF = 5;

Sharpening::Sharpening(std::vector<float> arguments) {
    if (!arguments.empty()) {
        throw std::runtime_error("Too many args for Sharpening Filter");
    }
    heigth_ = 3;
    width_ = 3;
    matrix_ = {0, -1, 0, -1, CENTERCOEFF, -1, 0, -1, 0};
}