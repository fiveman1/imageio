#include "imageio/canny_edge_detect.h"

// Include definition below to track time the filters take
// #define CANNY_DEBUG

#ifdef CANNY_DEBUG
#include <iostream>
#include <chrono>
using namespace std::chrono;
#endif

namespace imageio {

CannyEdgeDetect::CannyEdgeDetect(float low, float high) {
    composite_filter.AddFilter(new GreyScaleFilter(), &ImageHelper::CreateGreyscaleImage);
    composite_filter.AddFilter(new GaussianFilter(5, 1.4f), &ImageHelper::CreateGreyscaleImage);
    composite_filter.AddFilter(new SobelFilter(), &ImageHelper::CreateGreyscaleImage);
    composite_filter.AddFilter(new NonMaxSuppressionFilter(), &ImageHelper::CreateGreyscaleImage);
    composite_filter.AddFilter(new DoubleThresholdFilter(low, high, 0.1f, 1.0f), &ImageHelper::CreateGreyscaleImage);
    composite_filter.AddFilter(new HysteresisFilter(0.1f, 1.0f), &ImageHelper::CreateGreyscaleImage);
}

void CannyEdgeDetect::ApplyInternal(const vector<IImage *> &inputs, const vector<IImage *> &outputs) {
#ifdef CANNY_DEBUG
    auto total_start = high_resolution_clock::now();
    composite_filter.Apply(inputs, outputs);
    auto total_end = high_resolution_clock::now();
    auto time = duration_cast<microseconds>(total_end - total_start).count();
    std::cout << "TOTAL TIME TAKEN (ms): " << time / 1000.0f << std::endl;
#else
    composite_filter.Apply(inputs, outputs);
#endif
}

}
