#ifndef IMAGEIO_GREYSCALE_FILTER_H
#define IMAGEIO_GREYSCALE_FILTER_H

#include "threaded_filter.h"

namespace imageio {

/**
 * @class Greyscale filter. Turns a color image into a greyscale image.
 */
class GreyScaleFilter : public ThreadedFilter {

protected:
    void ApplyToRegion(int startX, int endX, int startY, int endY, const std::vector<IImage *> &inputs,
                       const std::vector<IImage *> &outputs) override;

    void Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) override;

};

}

#endif //IMAGEIO_GREYSCALE_FILTER_H
