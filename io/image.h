#pragma once

#include "headers.h"
#include <vector>

class BMPImage {
public:
    BMPImage(BMPHeader bmp_header, DIBHeader dib_header, std::vector<Pixel> image);

    BMPImage(BMPHeader bmp_header, DIBHeader dib_header);
    BMPHeader GetBmpHeaders() const;
    DIBHeader GetDibHeaders() const;
    Pixel GetPixel(int x, int y) const;
    void SetPixel(int x, int y, Pixel pix);
    const std::vector<Pixel>& GetImage() const;
    void UpdateHeaders();

private:
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    std::vector<Pixel> image_;
};