#include "bmptools.h"
#include "headers.h"
#include "image.h"

const int BITSPERPIXEL = 24;
const int BYTESPERPIXEL = 8;
const float MAXCOLORVALUE = 255.0f;
const int ROWALLIGNMENT = 32;
const int ROWPADDING = 31;
const int ROWBYTES = 4;
const uint16_t BMPSIGNATURE = 0x4D42;

BMPTools::BMPTools(std::string_view read_path, std::string_view write_path)
    : read_path_(read_path), write_path_(write_path){};

void BMPTools::CheckIfValid(std::ifstream& istr) {
    if (!istr) {
        throw std::runtime_error("Failed to read pixel data");
    }
}

BMPImage BMPTools::LoadBMP() {
    std::ifstream istr(read_path_, std::ios::binary);
    BMPHeader bmp_header;
    DIBHeader dib_header;
    CheckIfValid(istr);
    istr.read(reinterpret_cast<char*>(&bmp_header), sizeof(bmp_header));
    CheckIfValid(istr);
    istr.read(reinterpret_cast<char*>(&dib_header), sizeof(dib_header));
    CheckIfValid(istr);
    if (bmp_header.signature != BMPSIGNATURE) {
        throw std::runtime_error("Format is not supported");
    }

    if (dib_header.compression != 0) {
        throw std::runtime_error("there is compression, cannot work with it");
    }

    if (dib_header.bits_per_pixel != BITSPERPIXEL) {
        throw std::runtime_error("bits_per_pixel are not 24, cannot work with it");
    }

    int bytes_per_pixel = dib_header.bits_per_pixel / BYTESPERPIXEL;
    int row_size = ((dib_header.bits_per_pixel * dib_header.width + ROWPADDING) / ROWALLIGNMENT) * ROWBYTES;
    padding_ = row_size - dib_header.width * bytes_per_pixel;
    bool direction = dib_header.height > 0;
    int height = abs(dib_header.height);

    std::vector<Pixel> pixel_data(height * dib_header.width);

    for (int y = 0; y < height; y++) {
        int row = direction ? height - y - 1 : y;
        for (int x = 0; x < dib_header.width; x++) {
            uint8_t bgr[3];
            CheckIfValid(istr);
            istr.read(reinterpret_cast<char*>(&bgr), 3);
            CheckIfValid(istr);
            Pixel pix{static_cast<float>(bgr[0]) / MAXCOLORVALUE, static_cast<float>(bgr[1]) / MAXCOLORVALUE,
                      static_cast<float>(bgr[2]) / MAXCOLORVALUE};
            pixel_data[row * dib_header.width + x] = pix;
        }
        istr.seekg(padding_, std::ios::cur);
    }
    return BMPImage(bmp_header, dib_header, pixel_data);
}

void BMPTools::SaveBMP(BMPImage& image) {
    image.UpdateHeaders();
    std::ofstream ostr(write_path_, std::ios::binary);
    if (!ostr) {
        throw std::runtime_error("Failed to open file for writing");
    }
    BMPHeader bmp_header = image.GetBmpHeaders();
    DIBHeader dib_header = image.GetDibHeaders();
    ostr.write(reinterpret_cast<char*>(&bmp_header), sizeof(bmp_header));
    ostr.write(reinterpret_cast<char*>(&dib_header), sizeof(dib_header));
    int width = dib_header.width;
    int height = abs(dib_header.height);
    bool direction = dib_header.height > 0;

    int row_size = ((BITSPERPIXEL * width + ROWPADDING) / ROWALLIGNMENT) * ROWBYTES;
    int padding = row_size - width * 3;

    for (int y = 0; y < height; y++) {
        int row = direction ? height - y - 1 : y;
        for (int x = 0; x < width; x++) {
            Pixel pix = image.GetPixel(x, row);
            uint8_t bgr[3] = {static_cast<uint8_t>(pix.blue * MAXCOLORVALUE),
                              static_cast<uint8_t>(pix.green * MAXCOLORVALUE),
                              static_cast<uint8_t>(pix.red * MAXCOLORVALUE)};
            ostr.write(reinterpret_cast<char*>(&bgr), 3);
        }
        for (int i = 0; i < padding; ++i) {
            ostr.put('\0');
        }
    }
}