#include "imageio/double_threshold_filter.h"

namespace imageio {

void DoubleThresholdFilter::ApplyToRegion(int startx, int endx, int starty, int endy, const vector<IImage *> &inputs,
                                          const vector<IImage *> &outputs) {
    const IImage& input = *inputs[0];
    IImage& output = *outputs[0];
    float high_threshold = max * high;
    float low_threshold = high_threshold * low;
    float thres;
    for (int y = starty; y < endy; ++y) {
        for (int x = startx; x < endx; ++x) {
            thres = input.GetGreyscale(x, y);
            if (thres >= high_threshold) {
                output.SetGreyscale(x, y, high_color);
            } else if (thres >= low_threshold) {
                output.SetGreyscale(x, y, low_color);
            } else {
                output.SetGreyscale(x, y, 0.0f);
            }
        }
    }
}

void DoubleThresholdFilter::Setup(const vector<IImage *> &inputs, const vector<IImage *> &outputs) {
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
