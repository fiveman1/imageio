#ifndef SAMPLE_FILTER_H
#define SAMPLE_FILTER_H

#include "imageio/filter.h"

using namespace imageio;

// Creating your own Filter class is simple. Just override ApplyInternal().
class MyFilter : public Filter {
public:
    // 1 input, 1 output
    MyFilter() : Filter(1, 1) {}

protected:
    void ApplyInternal(const vector<IImage *> &inputs, const vector<IImage *> &outputs) override {
        // Do not modify any of the inputs
        // Outputs are assumed to be empty images, resize them first
        const IImage& input = *inputs[0];
        IImage& output = *outputs[0];

        // pick 1 or 2
        // 1. resize image to have same dimensions as input (does not copy pixels over)
        output.Resize(input);

        // 2. copy image to output
        // output.CopyFrom(input);

        // loop over pixels
        for (int x = 0; x < input.GetWidth(); ++x) {
            for (int y = 0; y < input.GetHeight(); ++x) {
                // do stuff
                // Color pixel = input.GetPixel(x, y) etc...
            }
        }
    }
};

#endif //SAMPLE_FILTER_H
