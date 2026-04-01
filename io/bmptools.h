#pragma once

#include <fstream>
#include <string>
#include <string_view>
#include "image.h"

class BMPTools {
public:
    void CheckIfValid(std::ifstream& istr);
    BMPTools(std::string_view read_path, std::string_view write_path);
    BMPImage LoadBMP();
    void SaveBMP(BMPImage& image);

private:
    int padding_;
    std::string read_path_;
    std::string write_path_;
};