#include "imageio/hysteresis_filter.h"

namespace imageio {

void HysteresisFilter::ApplyToRegion(int startx, int endx, int starty, int endy, const std::vector<IImage *> &inputs,
                                     const std::vector<IImage *> &outputs) {
    const IImage& input = *inputs[0];
    IImage& output = *outputs[0];
    float thres;
    for (int y = starty; y < endy; ++y) {
        for (int x = startx; x < endx; ++x) {
            thres = input.GetGreyscale(x, y);
            if (std::abs(thres - low_color) < Util::eps) {
                if (CheckStrongNeighbors(x, y, input)) {
                    output.SetGreyscale(x, y, 1.0f);
                } else {
                    output.SetGreyscale(x, y, 0.0f);
                }
            } else {
                output.SetGreyscale(x, y, thres);
            }
        }
    }
}

void HysteresisFilter::Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) {
    outputs[0]->Resize(*inputs[0]);
}

bool HysteresisFilter::CheckStrongNeighbors(int i, int j, const IImage& image) const {
    int width = image.GetWidth();
    int height = image.GetHeight();
    for (int y = j - 1; y <= j + 1; ++y) {
        for (int x = i - 1; x <= i + 1; ++x) {
            if (x >= 0 and x < width and y >= 0 and y < height and std::abs(image.GetGreyscale(x, y) - high_color) < Util::eps) {
                return true;
            }
        }
    }
    return false;
}

}
