#ifndef SAMPLE_THREADED_FILTER_H
#define SAMPLE_THREADED_FILTER_H

#include "imageio/threaded_filter.h"

using namespace imageio;

// Creating your own ThreadedFilter class is more complicated than Filter, but not by much.
// Read the documentation for ThreadedFilter if anything here is not clear.
class MyFilter : public ThreadedFilter {
public:
    // 1 input, 1 output
    MyFilter() : ThreadedFilter(1, 1) {}

protected:

    void Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) override {
        // Setup is called before ApplyToRegion is called
        // Outputs are assumed to be empty images, resize them first
        // pick 1 or 2
        // 1. resize image to have same dimensions as input (does not copy pixels over)
        outputs[0]->Resize(*inputs[0]);

        // 2. copy image to output
        // outputs[0]->CopyFrom(*inputs[0]);
    }

    void ApplyToRegion(int startX, int endX, int startY, int endY, const std::vector<IImage *> &inputs,
                       const std::vector<IImage *> &outputs) override {
        // Do not modify any of the inputs
        const IImage& input = *inputs[0];
        IImage& output = *outputs[0];

        // loop over pixels
        // do NOT modify any output pixels outside of the provided range
        // take note of startX, endX, startY, endY
        for (int x = startX; x < endX; ++x) {
            for (int y = startY; y < endY; ++y) {
                // do stuff
                // Color pixel = input.GetPixel(x, y) etc...
            }
        }
    }



    void Cleanup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) override {
        // This is called after all ApplyToRegion threads are done
        // If there is something you need to do to the output after all the threads are done do it here
        // outputs[0]->Normalize() for example
    }
};

#endif //SAMPLE_THREADED_FILTER_H
