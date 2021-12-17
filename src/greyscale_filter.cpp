#include "imageio/greyscale_filter.h"

namespace imageio {

void GreyScaleFilter::ApplyToRegion(int startX, int endX, int startY, int endY, const std::vector<IImage *> &inputs,
                                    const std::vector<IImage *> &outputs) {
    const IImage& input = *inputs[0];
    IImage& output = *outputs[0];
    for (int i = startX; i < endX; ++i) {
        for (int j = startY; j < endY; ++j) {
            output.SetGreyscale(i, j, input.GetPixel(i, j).GetLuminance());
        }
    }
}

void GreyScaleFilter::Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) {
    outputs[0]->Resize(*inputs[0]);
}

}
