#include "imageio/image_processor.h"

// Include or remove this definition to enable some debugging messages
// #define IMGPROCSS_DEBUG

#ifdef IMGPROCSS_DEBUG
#include <iostream>
#endif

namespace imageio {

TaskObserver::~TaskObserver() {
    ImageProcessor::Instance().OnDestroy(this);
}

bool TaskObserver::RunFilter(Filter *filter, const vector<IImage *> &inputs) {
    return ImageProcessor::Instance().RunFilter(filter, inputs, this);
}

ImageProcessor &ImageProcessor::Instance() {
    static ImageProcessor instance;
    return instance;
}

bool ImageProcessor::RunFilter(Filter *filter, const vector<IImage *> &inputs, TaskObserver *observer) {
    vector<TaskObserver*> observers(1);
    observers[0] = observer;
    return RunFilter(filter, inputs, observers);
}

bool ImageProcessor::RunFilter(Filter *filter, const vector<IImage *> &inputs, const vector<TaskObserver *> &observers) {
    vector<unique_ptr<IImage>> inputs_unique;
    for (auto input : inputs) {
        inputs_unique.emplace_back(input);
    }
    auto f = unique_ptr<Filter>(filter);
    return RunFilter(f, inputs_unique, observers);
}

void ImageProcessor::AddToQueue(TaskObserver *observer, const vector<shared_ptr<IImage>> &outputs) {
    const lock_guard<mutex> lock(mtx);
    queue.emplace(observer, outputs);
}

void ImageProcessor::Update() {
    const lock_guard<mutex> lock(mtx);
    while (not queue.empty()) {
#ifdef IMGPROCSS_DEBUG
        std::cout << "FOUND COMPLETED TASK!" << std::endl;
#endif
        auto pair = queue.front();
        auto observer = pair.first;
        auto outputs = pair.second;
        if (observer_set.count(observer)) {
            observer->Notify(outputs);
            observer_set.erase(observer);
        }
#ifdef IMGPROCSS_DEBUG
        else {
            std::cout << "SKIPPING DELETED OBSERVER!" << std::endl;
        }
#endif
        queue.pop();
    }
}

void ImageProcessor::OnDestroy(TaskObserver *observer) {
    const lock_guard<mutex> lock(mtx);
#ifdef IMGPROCSS_DEBUG
    std::cout << "ERASING OBSERVER (" << observer << ")" << std::endl;
#endif
    observer_set.erase(observer);
}

bool ImageProcessor::RunFilter(unique_ptr<Filter> &filter, vector<unique_ptr<IImage>> &inputs,
                               const vector<TaskObserver *> &observers) {
    const lock_guard<mutex> lock(mtx);
    for (auto observer : observers) {
        if (observer_set.count(observer)) {
            return false;
        }
    }
    for (auto observer : observers) {
        observer_set.insert(observer);
    }
    thread thread(&ImageProcessor::RunFilterTask, this, std::move(filter), std::move(inputs), observers);
    thread.detach();
    return true;
}

void ImageProcessor::RunFilterTask(const unique_ptr<Filter> &filter, const vector<unique_ptr<IImage>> &inputs,
                                   const vector<TaskObserver *> &observers) {
    vector<IImage*> outputs;
    for (int i = 0; i < filter->GetOutputs(); ++i) {
        outputs.push_back(new Image());
    }
    vector<IImage*> temp;
    for (const auto& input : inputs) {
        temp.push_back(input.get());
    }
    filter->Apply(temp, outputs);
    vector<shared_ptr<IImage>> outputs_shared;
    for (auto output : outputs) {
        outputs_shared.emplace_back(output);
    }
    for (auto observer : observers) {
        AddToQueue(observer, outputs_shared);
    }
}

}
