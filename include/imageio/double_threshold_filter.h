#ifndef IMAGEIO_DOUBLE_THRESHOLD_FILTER_H
#define IMAGEIO_DOUBLE_THRESHOLD_FILTER_H

#include "threaded_filter.h"

namespace imageio {

/**
 * @class Double threshold filter. Filters out edge pixels with a weak gradient value and preserves
 * edge pixels with a high gradient value.
 */
class DoubleThresholdFilter : public ThreadedFilter {

public:
    /**
     * @brief Use the low and high tresholds to control sensitivity. The low_color and high_color determine
     * what to set the weak and strong pixels to respectively.
     * @param low: low threshold
     * @param high: high threshold
     * @param low_color: weak pixel value
     * @param high_color: strong pixel value
     */
    DoubleThresholdFilter(float low, float high, float low_color, float high_color) : low(low), high(high),
                                                            low_color(low_color), high_color(high_color) {}

protected:
    void ApplyToRegion(int startx, int endx, int starty, int endy, const std::vector<IImage *> &inputs,
                       const std::vector<IImage *> &outputs) override;

    void Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) override;

private:
    float low;
    float high;
    float low_color;
    float high_color;
    float max = 0;
};

}

#endif //IMAGEIO_DOUBLE_THRESHOLD_FILTER_H
