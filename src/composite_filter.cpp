#include "imageio/composite_filter.h"

namespace imageio {

void CompositeFilter::AddFilter(Filter* filter, const function<IImage*()>& image_factory) {
    filters.emplace_back(unique_ptr<Filter>(filter), image_factory);
    if (filters.size() == 1) {
        num_inputs = filter->GetInputs();
    }
    num_outputs = filter->GetOutputs();
    if (filters.size() > 1 and filter->GetInputs() != filters[filters.size() - 2].first->GetOutputs()) {
        throw std::runtime_error("Tried to add filter whose number of inputs don't match the previous filter's number of outputs!");
    }
}

void CompositeFilter::Apply(const vector<IImage *> &inputs, const vector<IImage *> &outputs) {
    if (filters.empty()) {
        throw std::runtime_error("Tried to apply composite filter with no filters added!");
    }
    Filter::Apply(inputs, outputs);
}

void CompositeFilter::ApplyInternal(const vector<IImage *> &inputs, const vector<IImage *> &outputs) {
    // Create images, skip the last filter
    vector<unique_ptr<IImage>> images;
    for (int i = 0; i < filters.size() - 1; ++i) {
        Filter& filter = *filters[i].first;
        auto& image_factory = filters[i].second;
        for (int j = 0; j < filter.GetOutputs(); ++j) {
            images.emplace_back(image_factory());
        }
    }
    // Loop over each filter (except the last), copy image pointers from the images we just created
    // and give them to filter.Apply()
    vector<IImage*> ins(inputs); // The first input vector uses the original input vector
    int idx = 0;
    for (int i = 0; i < filters.size() - 1; ++i) {
        Filter& filter = *filters[i].first;
        int n_out = filter.GetOutputs();
        vector<IImage*> outs(n_out);
        for (int j = 0; j < n_out; ++j) {
            outs[j] = images[idx++].get();
        }
        filter.Apply(ins, outs);
        ins = std::move(outs); // Move images from output back to input for next iteration
    }
    // Call the last filter so the outputs go into the original output vector
    filters.back().first->Apply(ins, outputs);
}

}
