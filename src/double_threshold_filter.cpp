#include "imageio/double_threshold_filter.h"

namespace imageio {

void DoubleThresholdFilter::ApplyToRegion(int startX, int endX, int startY, int endY, const std::vector<IImage *> &inputs,
                                          const std::vector<IImage *> &outputs) {
    const IImage& input = *inputs[0];
    IImage& output = *outputs[0];
    float high_threshold = max * high;
    float low_threshold = high_threshold * low;
    float threshold;
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            threshold = input.GetGreyscale(x, y);
            if (threshold >= high_threshold) {
                output.SetGreyscale(x, y, high_color);
            } else if (threshold >= low_threshold) {
                output.SetGreyscale(x, y, low_color);
            } else {
                output.SetGreyscale(x, y, 0.0f);
            }
        }
    }
}

void DoubleThresholdFilter::Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) {
    const IImage& input = *inputs[0];
    IImage& output = *outputs[0];
    output.Resize(input);

    int width = input.GetWidth();
    int height = input.GetHeight();
    max = 0.0f;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float val = input.GetGreyscale(x, y);
            if (val > max) max = val;
        }
    }
}

}
