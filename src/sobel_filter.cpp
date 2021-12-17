#include "imageio/sobel_filter.h"

namespace imageio {

void SobelFilter::ApplyToRegion(int startX, int endX, int startY, int endY, const std::vector<IImage *> &inputs,
                                const std::vector<IImage *> &outputs) {
    const IImage& input = *inputs[0];
    IImage& intensity = *outputs[0];
    IImage& direction = *outputs[1];
    int size = kernelX.GetRows();
    int r = size / 2;
    float curr, ix, iy, intens, direc;
    int c1, r1;
    int width = input.GetWidth();
    int height = input.GetHeight();
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            ix = 0.0f;
            iy = 0.0f;
            for (int row = 0; row < size; ++row) {
                for (int col = 0; col < size; ++col) {
                    c1 = Util::clamp(x + col - r, 0, width - 1);
                    r1 = Util::clamp(y + row - r, 0, height - 1);
                    curr = input.GetGreyscale(c1, r1);
                    ix += curr * kernelX(col, row);
                    iy += curr * kernelY(col, row);
                }
            }
            intens = std::sqrt(ix * ix + iy * iy);
            direc = std::atan2(iy, ix) / Util::pi;
            if (direc < 0) direc += 1.0f;
            intensity.SetGreyscale(x, y, intens);
            direction.SetGreyscale(x, y, direc);
        }
    }
}

void SobelFilter::Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) {
    outputs[0]->Resize(*inputs[0]);
    outputs[1]->Resize(*inputs[0]);
}

void SobelFilter::Cleanup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) {
    outputs[0]->Normalize();
}

}
