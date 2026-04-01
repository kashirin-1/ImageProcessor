#include "help_functions.h"

int Clamp(int v, int lo, int hi) {
    return std::min(hi, std::max(lo, v));
}