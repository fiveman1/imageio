#include "imageio/threaded_filter.h"

namespace imageio {

void ThreadedFilter::ApplyInternal(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) {
    std::lock_guard<std::mutex> lock(mtx);
    Setup(inputs, outputs);
    int width = inputs[0]->GetWidth();
    int height = inputs[0]->GetHeight();
    std::vector<std::thread> threads;
    threads.reserve(thread_count * thread_count);
    int startx, endx, starty, endy;
    // Divide the image into subregions
    // Image (thread_count = 4):
    // | X X X X |
    // | X X X X |
    // | X X X X |
    // | X X X X |
    // Each X is a threaded call to ApplyToRegion with the parameters
    // [startx, endx), [starty, endy) defining the region
    for (int i = 0; i < thread_count; ++i) {
        startx = (i * width) / thread_count;
        endx = ((i + 1) * width) / thread_count;
        for (int j = 0; j < thread_count; ++j) {
            starty = (j * height) / thread_count;
            endy = ((j + 1) * height) / thread_count;
            // Threads start as soon as they are added to the vector
            threads.emplace_back(&ThreadedFilter::ApplyToRegion, this, startx, endx, starty, endy, inputs, outputs);
        }
    }

    // Wait for each thread to finish before we exit the function
    for (auto& thread : threads) {
        thread.join();
    }

    Cleanup(inputs, outputs);
}

}
