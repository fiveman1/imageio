#ifndef IMAGEIO_GREYSCALE_FILTER_H
#define IMAGEIO_GREYSCALE_FILTER_H

#include "threaded_filter.h"

namespace imageio {

/**
 * @class Greyscale filter. Turns a color image into a greyscale image.
 */
class GreyScaleFilter : public ThreadedFilter {

protected:
    void ApplyToRegion(int startx, int endx, int starty, int endy, const vector<IImage *> &inputs,
                       const vector<IImage *> &outputs) override;

    void Setup(const vector<IImage *> &inputs, const vector<IImage *> &outputs) override;

};

}

#endif //IMAGEIO_GREYSCALE_FILTER_H
