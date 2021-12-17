#ifndef IMAGEIO_THREADED_FILTER_H
#define IMAGEIO_THREADED_FILTER_H

#include <mutex>
#include <thread>

#include "filter.h"

namespace imageio {

/**
 * @class An abstract threaded filter. This class spawns multiple threads and divides the work among many threads
 * given equal sized regions to work with. This requires that the filter can work across different
 * regions of an image independent from one another. For example, canny edge detection does not use
 * this because it requires the results of other filters first before it can proceed. However, most filters
 * can be run multithreaded. Finally, the same filter cannot run two tasks at once, it will lock and the second would
 * wait until the first finishes. This means that if you need to apply the same filter to some images, create a new ThreadedFilter
 * for each image.
 */
class ThreadedFilter : public Filter {

public:
    /**
     * @brief Specify the amount of threads to use. The default is 4. threads_per_row^2
     * threads will be created, so the default spawns 16 total threads. The filter works by
     * dividing the image into equal sized rectangles and giving them to ApplyToRegion. One thread
     * is spawned for each region.
     * @param threads_per_row: the number of threads to use per row (also the same as threads per column).
     */
    explicit ThreadedFilter(int n_inputs = 1, int n_outputs = 1, int threads_per_row = 4)
        : Filter(n_inputs, n_outputs), thread_count(threads_per_row) {}

protected:

    /**
     * @brief Sets up threads and divides work to calls to ApplyToRegion().
     */
    void ApplyInternal(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) override;

    /**
     * @brief Apply the filter to every pixel between ( [startX, endX), [startY, endY) )
     * This function shall not change output pixels outside this range, or any other event
     * that could lead to a race condition. The start and end coordinates are guaranteed to be in
     * the range [ 0, width (x) or height (y) ] for x/y respectively. These coordinates are based on
     * the width/height of the first image in the input vector.
     * @param startX: the starting x coordinate (inclusive)
     * @param endX: the ending x coordinate (exclusive)
     * @param startY: the starting y coordinate (inclusive)
     * @param endY: the ending y coordinate (exclusive)
     * @param inputs: Filter inputs (do not modify these)
     * @param outputs: Filter outputs
     */
    virtual void ApplyToRegion(int startX, int endX, int startY, int endY,
                               const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) = 0;

    /**
     * @brief Do any setup required before any calls to ApplyToRegion are done here.
     * This would include: resizing the output, copying input to output, etc.
     * @param inputs: Filter inputs (do not modify these)
     * @param outputs: Filter outputs
     */
    virtual void Setup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) = 0;

    /**
     * @brief Perform any cleanup required here. This is called after all threads/all calls to ApplyToRegion
     * have finished.
     * @param inputs: Filter inputs (do not modify these)
     * @param outputs: Filter outputs
     */
    virtual void Cleanup(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) {}

    int thread_count;
    mutable std::mutex mtx;
};

}

#endif //IMAGEIO_THREADED_FILTER_H
