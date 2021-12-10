#ifndef IMAGEIO_IMAGE_PROCESSOR_H
#define IMAGEIO_IMAGE_PROCESSOR_H

#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_set>
#include <utility>
#include <vector>

#include "filter.h"
#include "iimage.h"

namespace imageio {

using std::lock_guard;
using std::mutex;
using std::pair;
using std::shared_ptr;
using std::thread;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

/**
 * @class Filter task observer. Can creates tasks via RunFilter and can listen to them via Notify.
 *
 * @example
 * @code MyTaskObserver observer;
 * if (observer.RunFilter(new MyFilter, { ImageHelper::FromFile("image_to_process.png") } )) { ... }
 */
class TaskObserver {

public:

    /**
     * @brief Called when a filter task has completed. This contains the outputs of the task in the order
     * that the original filter created them.
     * @param outputs: outputs of filter task
     */
    virtual void Notify(const vector<shared_ptr<IImage>> &outputs) = 0;

    /**
     * @brief Use this to spawn a filter task (to run a filter concurrently in the background).
     * After the filter has completed, Notify() will be called with the outputs. Pointers given to this method
     * will be automatically managed, DO NOT try to use pointers after they have been given to this.
     * Additionally, this method will return true if that task could be run, false otherwise. If it returns false
     * no task will be created and this observer will not be notified. Tasks will not be run iff: the observer already
     * has a task running that has not been completed (the observer has not been notified yet).
     * @param filter: a *new* filter
     * @param inputs: a vector of *new* input images
     * @return true if the task could be run, false otherwise.
     */
    virtual bool RunFilter(Filter *filter, const vector<IImage *> &inputs);

    virtual ~TaskObserver();

};

/**
* @class Concurrent image processor class.
*/
class ImageProcessor {

public:

    /**
     * @return Singleton instance of ImageProcessor. Use this to access the image processor.
     *
     * @example
     * @code ImageProcessor::Instance().Update();
     */
    static ImageProcessor &Instance();

    /**
     * @brief Refer to TaskObserver::RunFilter()
     * @param filter: a *new* filter
     * @param inputs: a vector of *new* inputs
     * @param observer: the observer to be notified
     * @return true if task created, false otherwise
     */
    bool RunFilter(Filter *filter, const vector<IImage *> &inputs, TaskObserver *observer);

    /**
     * @brief Refer to TaskObserver::RunFilter()
     * @param filter: a *new* filter
     * @param inputs: a vector of *new* inputs
     * @param observers: a vector of observers to be notified
     * @return true if task created, false otherwise
     */
    bool RunFilter(Filter *filter, const vector<IImage *> &inputs, const vector<TaskObserver *> &observers);

    /**
     * @brief This checks for completed tasks and will notify observers with the completed tasks and outputs.
     * This is designed to be used in conjunction with an event loop, where the event loop calls Update() on each
     * iteration.
     */
    void Update();

    /**
     * @brief Meant for internal use. When observers are destroyed they call this.
     * @param observer: observer that is being destroyed.
     */
    void OnDestroy(TaskObserver *observer);

    ImageProcessor(const ImageProcessor &) = delete;

    ImageProcessor &operator=(const ImageProcessor &) = delete;

protected:

    ImageProcessor() = default;

    void AddToQueue(TaskObserver *observer, const vector<shared_ptr<IImage>> &outputs);

    bool RunFilter(unique_ptr<Filter> &filter, vector<unique_ptr<IImage>> &inputs,
                   const vector<TaskObserver *> &observers);

    void RunFilterTask(const unique_ptr<Filter> &filter, const vector<unique_ptr<IImage>> &inputs,
                       const vector<TaskObserver *> &observers);

    unordered_set<TaskObserver *> observer_set;
    std::queue<pair<TaskObserver *, vector<shared_ptr<IImage>>>> queue;
    mutable mutex mtx;
};

}

#endif //IMAGEIO_IMAGE_PROCESSOR_H
