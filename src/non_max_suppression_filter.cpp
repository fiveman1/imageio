#include "imageio/non_max_suppression_filter.h"

namespace imageio {

void NonMaxSuppressionFilter::Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) {
    outputs[0]->CopyFrom(*inputs[0]);
}

void NonMaxSuppressionFilter::ApplyToRegion(int startX, int endX, int startY, int endY, const std::vector<IImage *> &inputs,
                                            const std::vector<IImage *> &outputs) {
    const IImage& intensity = *inputs[0];
    const IImage& direction = *inputs[1];
    IImage& output = *outputs[0];

    float angle, ity, q, r;
    startX = std::max(startX, 1);
    startY = std::max(startY, 1);
    endX = std::min(endX, intensity.GetWidth() - 1);
    endY = std::min(endY, intensity.GetHeight() - 1);
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
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
