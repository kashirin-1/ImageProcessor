#include "image.h"
#include "filters_list.h"
#include "base_filters.h"
#include "crop_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharpening_filter.h"
#include "edgedetection_filter.h"
#include "blur_filter.h"
#include "crystalize_filter.h"

void ApplyFilters(std::vector<std::pair<Filters, std::vector<float>>>& filters, BMPImage& image);