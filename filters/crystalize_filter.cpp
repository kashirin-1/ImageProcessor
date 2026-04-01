#include "crystalize_filter.h"
#include <stdexcept>

int GetRandom(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

CrystalizeFilter::CrystalizeFilter(std::vector<float> args) {
    if (args.empty()) {
        throw std::runtime_error("Not enough args for Crystalize Filter");
    }
    if (args.size() > 1) {
        throw std::runtime_error("Too many args for Crystalize Filter");
    }
    cell_size_ = static_cast<int>(args[0]);
}

CrystalizeFilter::CrystalizeFilter(int size) : cell_size_(size){};

void CrystalizeFilter::Apply(BMPImage& image) {
    DIBHeader image_dib_headers = image.GetDibHeaders();
    int width = image_dib_headers.width;
    int height = abs(image_dib_headers.height);

    struct Point {
        int x = 0;
        int y = 0;
    };

    int cols = (width + cell_size_ - 1) / cell_size_;
    int rows = (height + cell_size_ - 1) / cell_size_;

    std::vector<std::vector<Point>> points(rows, std::vector<Point>(cols));

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            int p_x = std::min(cell_size_ * x + GetRandom(0, cell_size_ - 1), width - 1);
            int p_y = std::min(cell_size_ * y + GetRandom(0, cell_size_ - 1), height - 1);
            points[y][x] = {p_x, p_y};
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int min_dist = std::numeric_limits<int>::max();
            Point current_point{};
            int cell_x = x / cell_size_;
            int cell_y = y / cell_size_;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = cell_x + dx;
                    int ny = cell_y + dy;
                    if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) {
                        continue;
                    }
                    Point p = points[ny][nx];
                    int dist = (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
                    if (dist < min_dist) {
                        min_dist = dist;
                        current_point = p;
                    }
                }
            }
            image.SetPixel(x, y, image.GetPixel(current_point.x, current_point.y));
        }
    }
}