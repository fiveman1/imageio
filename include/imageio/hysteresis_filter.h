#ifndef IMAGEIO_HYSTERESIS_FILTER_H
#define IMAGEIO_HYSTERESIS_FILTER_H

#include <cstdlib>

#include "threaded_filter.h"
#include "util.h"

namespace imageio {

/**
 * @class Hysteresis filter. Determines if weak pixels should be included or excluded based on
 * the strength of its neighbors.
 */
class HysteresisFilter : public ThreadedFilter {

public:
    /**
     * @brief low_color and high_color should be the same as what's used in DoubleThreshold.
     * @param low_color: weak pixel value
     * @param high_color: strong pixel value
     */
    HysteresisFilter(float low_color, float high_color) : low_color(low_color), high_color(high_color) {}

protected:
    void ApplyToRegion(int startx, int endx, int starty, int endy, const std::vector<IImage *> &inputs,
                       const std::vector<IImage *> &outputs) override;

    void Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) override;

private:
    float low_color;
    float high_color;

    bool CheckStrongNeighbors(int x, int y, const IImage& image) const;

};

}

#endif //IMAGEIO_HYSTERESIS_FILTER_H
