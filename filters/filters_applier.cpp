#include "filters_applier.h"
#include <functional>
#include <memory>
#include <unordered_map>
#include <stdexcept>

void ApplyFilters(std::vector<std::pair<Filters, std::vector<float>>>& filters, BMPImage& image) {

    using Factory = std::function<std::unique_ptr<Filter>(const std::vector<float>&)>;

    const std::unordered_map<Filters, Factory> factory_map = {
        {Filters::CROP, [](const auto& args) { return std::make_unique<CropFilter>(args); }},
        {Filters::GRAYSCALE, [](const auto& args) { return std::make_unique<GrayscaleFilter>(args); }},
        {Filters::NEGATIVE, [](const auto& args) { return std::make_unique<NegativeFilter>(args); }},
        {Filters::SHARPENING, [](const auto& args) { return std::make_unique<Sharpening>(args); }},
        {Filters::EDGEDETECTION, [](const auto& args) { return std::make_unique<EdgeDetection>(args); }},
        {Filters::BLUR, [](const auto& args) { return std::make_unique<BlurFilter>(args); }},
        {Filters::CRYSTALIZE, [](const auto& args) { return std::make_unique<CrystalizeFilter>(args); }},
    };

    for (const auto& [filter, arguments] : filters) {
        auto it = factory_map.find(filter);
        if (it == factory_map.end()) {
            throw std::runtime_error("Unkown filter");
        }
        it->second(arguments)->Apply(image);
    }
}