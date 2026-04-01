#include "image.h"
#include <cstdlib>

const int BITSPERPIXEL = 24;
const int ROWALLIGNMENT = 32;
const int ROWPADDING = 31;
const int ROWBYTES = 4;

BMPImage::BMPImage(BMPHeader bmp_header, DIBHeader dib_header, std::vector<Pixel> image)
    : bmp_header_(bmp_header), dib_header_(dib_header), image_(image){};

BMPImage::BMPImage(BMPHeader bmp_header, DIBHeader dib_header)
    : bmp_header_(bmp_header),
      dib_header_(dib_header),
      image_(abs(dib_header.height) * dib_header.width, {0.0f, 0.0f, 0.0f}){};

BMPHeader BMPImage::GetBmpHeaders() const {
    return bmp_header_;
}

DIBHeader BMPImage::GetDibHeaders() const {
    return dib_header_;
}

Pixel BMPImage::GetPixel(int x, int y) const {
    return image_[y * dib_header_.width + x];
}
void BMPImage::SetPixel(int x, int y, Pixel pix) {
    image_[y * dib_header_.width + x] = pix;
}
const std::vector<Pixel>& BMPImage::GetImage() const {
    return image_;
}

void BMPImage::UpdateHeaders() {
    int width = dib_header_.width;
    int height = abs(dib_header_.height);
    int row_size = ((BITSPERPIXEL * width + ROWPADDING) / ROWALLIGNMENT) * ROWBYTES;
    int pixel_data_size = row_size * height;

    bmp_header_.file_size = bmp_header_.data_offset + pixel_data_size;
    dib_header_.image_size = pixel_data_size;
}
