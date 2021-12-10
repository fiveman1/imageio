#include "imageio/greyscale_filter.h"

namespace imageio {

void GreyScaleFilter::ApplyToRegion(int startx, int endx, int starty, int endy, const vector<IImage *> &inputs,
                                    const vector<IImage *> &outputs) {
    const IImage& input = *inputs[0];
    IImage& output = *outputs[0];
    for (int i = startx; i < endx; ++i) {
        for (int j = starty; j < endy; ++j) {
            output.SetGreyscale(i, j, input.GetPixel(i, j).GetLuminance());
        }
    }
}

void GreyScaleFilter::Setup(const vector<IImage *> &inputs, const vector<IImage *> &outputs) {
    outputs[0]->Resize(*inputs[0]);
}

}
