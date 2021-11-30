#ifndef IMAGEIO_SOBEL_FILTER_H
#define IMAGEIO_SOBEL_FILTER_H

#include <cmath>

#include "greyscale_image.h"
#include "matrix.h"
#include "threaded_filter.h"
#include "util.h"

namespace imageio {

using std::sqrt;
using std::atan2;
using Util::pi;

/**
 * @class Sobel filter. Creates an intensity and direction gradient from a greyscale image.
 */
class SobelFilter : public ThreadedFilter {

public:
    SobelFilter() : ThreadedFilter(1, 2) {}

protected:
    void ApplyToRegion(int startx, int endx, int starty, int endy, const vector<IImage *> &inputs,
                       const vector<IImage *> &outputs) override;

    void Setup(const vector<IImage *> &inputs, const vector<IImage *> &outputs) override;

    void Cleanup(const vector<IImage *> &inputs, const vector<IImage *> &outputs) override;

private:
    Matrix kernelX  { { 1, 0, -1 },
                      { 2, 0, -2 },
                      { 1, 0, -1 } };

    Matrix kernelY  { { 1, 2, 1 },
                      { 0, 0, 0 },
                      { -1, -2, -1 } };
};

}

#endif //IMAGEIO_SOBEL_FILTER_H
