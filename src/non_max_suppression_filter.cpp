#include "imageio/non_max_suppression_filter.h"

namespace imageio {

void NonMaxSuppressionFilter::Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) {
    outputs[0]->CopyFrom(*inputs[0]);
}

void NonMaxSuppressionFilter::ApplyToRegion(int startx, int endx, int starty, int endy, const std::vector<IImage *> &inputs,
                                            const std::vector<IImage *> &outputs) {
    const IImage& intensity = *inputs[0];
    const IImage& direction = *inputs[1];
    IImage& output = *outputs[0];

    float angle, ity, q, r;
    startx = std::max(startx, 1);
    starty = std::max(starty, 1);
    endx = std::min(endx, intensity.GetWidth() - 1);
    endy = std::min(endy, intensity.GetHeight() - 1);
    for (int y = starty; y < endy; ++y) {
        for (int x = startx; x < endx; ++x) {
            angle = direction.GetGreyscale(x, y) * 180.0f;
            if (Util::between(22.5f, angle, 67.5f)) {
                q = intensity.GetGreyscale(x - 1, y - 1);
                r = intensity.GetGreyscale(x + 1, y + 1);
            } else if (Util::between(67.5f, angle, 112.5f)) {
                q = intensity.GetGreyscale(x, y + 1);
                r = intensity.GetGreyscale(x, y - 1);
            } else if (Util::between(112.5f, angle, 157.5f)) {
                q = intensity.GetGreyscale(x - 1, y + 1);
                r = intensity.GetGreyscale(x + 1, y - 1);
            } else {
                q = intensity.GetGreyscale(x + 1, y);
                r = intensity.GetGreyscale(x - 1, y);
            }
            ity = intensity.GetGreyscale(x, y);
            if (ity >= q and ity >= r) {
                output.SetGreyscale(x, y, ity);
            } else {
                output.SetGreyscale(x, y, 0);
            }
        }
    }
}

}
