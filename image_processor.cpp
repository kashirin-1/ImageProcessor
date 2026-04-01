#include "bmptools.h"
#include "filters_applier.h"
#include "parser.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        std::vector<std::pair<Filters, std::vector<float>>> arguments;
        BMPTools tool = ParseArguments(argc, argv, arguments);
        BMPImage image = tool.LoadBMP();
        ApplyFilters(arguments, image);
        tool.SaveBMP(image);
    } catch (const std::runtime_error& e) {
        std::cout << "Произошла ошибка: " << e.what() << std::endl;
    }
    return 0;
}