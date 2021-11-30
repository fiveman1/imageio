#ifndef IMAGEIO_NON_MAX_SUPPRESSION_FILTER_H
#define IMAGEIO_NON_MAX_SUPPRESSION_FILTER_H

#include <cmath>

#include "threaded_filter.h"
#include "util.h"

namespace imageio {

using std::max;
using std::min;
using Util::between;

/**
 * @class Non max suppression filter. Uses an intensity and direction image to
 * perform gradient magnitude thresholding.
 */
class NonMaxSuppressionFilter : public ThreadedFilter {

public:
    NonMaxSuppressionFilter() : ThreadedFilter(2, 1) {}

protected:
    void ApplyToRegion(int startx, int endx, int starty, int endy, const vector<IImage *> &inputs,
                       const vector<IImage *> &outputs) override;

    void Setup(const vector<IImage *> &inputs, const vector<IImage *> &outputs) override;

};

}

#endif //IMAGEIO_NON_MAX_SUPPRESSION_FILTER_H
