#include "imageio/sobel_filter.h"

namespace imageio {

void SobelFilter::ApplyToRegion(int startx, int endx, int starty, int endy, const vector<IImage *> &inputs,
                                const vector<IImage *> &outputs) {
    const IImage& input = *inputs[0];
    IImage& intensity = *outputs[0];
    IImage& direction = *outputs[1];
    int size = kernelX.GetRows();
    int r = size / 2;
    float curr, ix, iy, intens, direc;
    int c1, r1;
    int width = input.GetWidth();
    int height = input.GetHeight();
    for (int y = starty; y < endy; ++y) {
        for (int x = startx; x < endx; ++x) {
            ix = 0.0f;
            iy = 0.0f;
            for (int row = 0; row < size; ++row) {
                for (int col = 0; col < size; ++col) {
                    c1 = clamp(x + col - r, 0, width - 1);
                    r1 = clamp(y + row - r, 0, height - 1);
                    curr = input.GetGreyscale(c1, r1);
                    ix += curr * kernelX(col, row);
                    iy += curr * kernelY(col, row);
                }
            }
            intens = sqrt(ix * ix + iy * iy);
            direc = atan2(iy, ix) / pi;
            if (direc < 0) direc += 1.0f;
            intensity.SetGreyscale(x, y, intens);
            direction.SetGreyscale(x, y, direc);
        }
    }
}

void SobelFilter::Setup(const vector<IImage *> &inputs, const vector<IImage *> &outputs) {
    outputs[0]->Resize(*inputs[0]);
    outputs[1]->Resize(*inputs[0]);
}

void SobelFilter::Cleanup(const vector<IImage *> &inputs, const vector<IImage *> &outputs) {
    outputs[0]->Normalize();
}

}
