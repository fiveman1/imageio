#include "imageio/gaussian_filter.h"

namespace imageio {

GaussianFilter::GaussianFilter(int size, float sigma) : sigma(sigma), size(size) {
    kernel = Matrix(size, size);
    int r = size / 2;
    int i, j;
    float i2, j2;
    float sigma_sqr = Util::square(sigma);
    float normal = 0.5f / (Util::pi * sigma_sqr);
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            i = row - r;
            j = col - r;
            i2 = static_cast<float>(Util::square(i));
            j2 = static_cast<float>(Util::square(j));
            kernel.Set(col, row, normal * static_cast<float>(std::exp((i2 + j2) * -0.5f / sigma_sqr)));
        }
    }
    kernel.Normalize();
}

void GaussianFilter::Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) {
    outputs[0]->Resize(*inputs[0]);
}

void GaussianFilter::ApplyToRegion(int startx, int endx, int starty, int endy, const std::vector<IImage *> &inputs,
                                   const std::vector<IImage *> &outputs) {
    inputs[0]->Convolve(startx, endx, starty, endy, *outputs[0], kernel);
}

}