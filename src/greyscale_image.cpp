#include "imageio/greyscale_image.h"

#include "imageio/stb_image.h"
#include "imageio/stb_image_write.h"

namespace imageio {

IImage* GreyscaleImage::Clone() const {
    return new GreyscaleImage(*this);
}

Color GreyscaleImage::GetPixel(int x, int y) const {
    float temp = array[at(x, y, width)];
    return Color(temp, temp, temp, 1.0f);
}

void GreyscaleImage::SetPixel(int x, int y, const Color &color) {
    array[at(x, y, width)] = color.R;
}

float GreyscaleImage::GetGreyscale(int x, int y) const {
    return array[at(x, y, width)];
}

void GreyscaleImage::SetGreyscale(int x, int y, float greyscale) {
    array[at(x, y, width)] = greyscale;
}

constexpr int GreyscaleImage::at(int col, int row, int cols) {
    return col + row * cols;
}

void GreyscaleImage::operator*=(const Color &color) {
    *this *= color.R;
}

void GreyscaleImage::operator*=(float n) {
    for (auto& pixel : array) {
        pixel *= n;
    }
}

void GreyscaleImage::Convolve(int startx, int endx, int starty, int endy, IImage &output, const Matrix &kernel) const {
    int size = kernel.GetRows();
    int r = size / 2;
    float curr;
    int c1, r1;
    for (int y = starty; y < endy; ++y) {
        for (int x = startx; x < endx; ++x) {
            curr = 0.0f;
            for (int row = 0; row < size; ++row) {
                for (int col = 0; col < size; ++col) {
                    c1 = clamp(x + col - r, 0, width - 1);
                    r1 = clamp(y + row - r, 0, height - 1);
                    curr += GetGreyscale(c1, r1) * kernel(col, row);
                }
            }
            output.SetGreyscale(x, y, curr);
        }
    }
}

void GreyscaleImage::Normalize() {
    float max = 0.0f;
    for (auto pixel : array) {
        if (pixel > max) max = pixel;
    }
    *this *= (1.0f / max);
}

void GreyscaleImage::ResizeInternal() {
    array.resize(width * height);
}

}
