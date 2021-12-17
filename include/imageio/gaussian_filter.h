#ifndef IMAGEIO_GAUSSIAN_FILTER_H
#define IMAGEIO_GAUSSIAN_FILTER_H

#include <cmath>

#include "matrix.h"
#include "threaded_filter.h"
#include "util.h"

namespace imageio {

/**
 * @class Gaussian blur filter. Uses a gaussian/normal distribution to apply a blurring effect to an image.
 */
class GaussianFilter : public ThreadedFilter {

public:

    /**
     * @brief Use size to control the size of the kernel matrix (3 for 3x3 matrix, 5 for 5x5, etc.)
     * Larger values lead to higher accuracy at the cost of performance. The sigma controls the standard deviation
     * used in the normal distribution. A higher value provides a blurrier image.
     * @param size: size of kernel matrix
     * @param sigma: standard dev used in normal distribution
     */
    explicit GaussianFilter(int size = 5, float sigma = 1.4f);

    /**
     * @return The sigma used for this Gaussian filter.
     */
    float GetSigma() const { return sigma; }

protected:
    void ApplyToRegion(int startX, int endX, int startY, int endY, const std::vector<IImage *> &inputs,
                       const std::vector<IImage *> &outputs) override;

    void Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) override;

private:
    Matrix kernel;
    float sigma;
    int size;
};

}

#endif //IMAGEIO_GAUSSIAN_FILTER_H
