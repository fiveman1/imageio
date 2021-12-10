#include "imageio/image.h"

namespace imageio {

IImage* Image::Clone() const {
    return new Image(*this);
}

Color Image::GetPixel(int x, int y) const {
    return array[at(x, y, width)];
}

void Image::SetPixel(int x, int y, const Color &color) {
    array[at(x, y, width)] = color;
}

float Image::GetGreyscale(int x, int y) const {
    return array[at(x, y, width)].R;
}

void Image::SetGreyscale(int x, int y, float greyscale) {
    array[at(x, y, width)] = Color(greyscale, greyscale, greyscale, 1.0f);
}

void Image::operator*=(const Color &color) {
    for (auto& pixel : array) {
        pixel *= color;
    }
}

void Image::operator*=(float n) {
    for (auto& pixel : array) {
        pixel *= n;
    }
}

void Image::ResizeInternal() {
    array.resize(width * height);
}

}
