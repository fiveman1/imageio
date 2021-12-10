#ifndef IMAGEIO_CANNY_EDGE_DETECT_H
#define IMAGEIO_CANNY_EDGE_DETECT_H

#include "composite_filter.h"
#include "double_threshold_filter.h"
#include "filter.h"
#include "hysteresis_filter.h"
#include "image_helper.h"
#include "gaussian_filter.h"
#include "greyscale_filter.h"
#include "greyscale_image.h"
#include "non_max_suppression_filter.h"
#include "sobel_filter.h"

namespace imageio {

/**
 * @class Canny edge detection. Detects edges from images.
 */
class CannyEdgeDetect : public Filter {

public:
    /**
     * @brief Use the low and high thresholds to set the sensitivity of the edge detection.
     * @param low: low threshold
     * @param high: high threshold
     */
    explicit CannyEdgeDetect(float low = 0.1f, float high = 0.3f);

protected:
    void ApplyInternal(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) override;

    CompositeFilter composite_filter;

};

}

#endif //IMAGEIO_CANNY_EDGE_DETECT_H
