#ifndef IMAGEIO_COMPOSITE_FILTER_H
#define IMAGEIO_COMPOSITE_FILTER_H

#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

#include "filter.h"
#include "image.h"
#include "image_helper.h"

namespace imageio {

/**
 * @class A composite filter class. This is a filter made up of multiple filters.
 * It calls them in succession. This will set the number of inputs and outputs of itself
 * dynamically based on the filters you add.
 */
class CompositeFilter : public Filter {

public:

    /**
     * @brief Add a Filter to this CompositeFilter. These filters will be ran in the same order
     * they were given to AddFilter().
     * @param filter: A *new* Filter. The composite filter will manage the pointer for you!
     * @throws runtime_error: if the filter you add doesn't have the same number of inputs as the previous has outputs.
     *
     * @example
     * @code CompositeFilter compositeFilter;
     * compositeFilter.AddFilter( new MyFilter() );
     */
    virtual void AddFilter(Filter* filter) {
        AddFilter(filter, &ImageHelper::CreateImage);
    }

    /**
     * @brief Add a Filter to this CompositeFilter. These filters will be ran in the same order
     * they were given to AddFilter(). You can also specify a type of image to use for the given filter by supplying
     * an image factory.
     * @param filter: A *new* Filter. The composite filter will manage the pointer for you!
     * @param image_factory: A function that returns a *new* IImage. Will be used with the corresponding Filter.
     * @throws runtime_error: if the filter you add doesn't have the same number of inputs as the previous has outputs.
     *
     * @example
     * @code CompositeFilter compositeFilter;
     * compositeFilter.AddFilter( new MyFilter(),
     *                            []() { return new MyImage(); } );
     */
    virtual void AddFilter(Filter* filter, const std::function<IImage*()>& image_factory);

    /**
     * @brief Applies each filter in succession to the provided inputs/outputs.
     * @param inputs: variable number of inputs
     * @param outputs: variable number of outputs
     * @throws runtime_error: if there are no filters added to this composite filter
     */
    void Apply(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) override;

protected:

    std::vector<std::pair<std::unique_ptr<Filter>, std::function<IImage*()>>> filters;

    void ApplyInternal(const std::vector<IImage *> &inputs, const std::vector<IImage *> &outputs) override;

};

}

#endif //IMAGEIO_COMPOSITE_FILTER_H
