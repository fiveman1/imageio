#ifndef IMAGEIO_FILTER_H
#define IMAGEIO_FILTER_H

#include <vector>

#include "greyscale_image.h"
#include "iimage.h"
#include "image.h"

namespace imageio {

/**
 * @class An abstract filter. Takes a variable number of inputs as arguments and produces a variable
 * number of outputs by applying a filter to the inputs. You must specify the number of inputs and outputs
 * when you construct the filter. This should usually be done by the derived class. The defaults are 1 input, 1 output.
 */
class Filter {
public:

    /**
     * @brief Constructs the filter. Make sure to call this if you don't have the default 1:1 inputs to outputs.
     * @param n_inputs: number of inputs
     * @param n_outputs: number of outputs
     */
    explicit Filter(int n_inputs = 1, int n_outputs = 1) : num_inputs(n_inputs), num_outputs(n_outputs) {}

    virtual ~Filter() = default;

    /**
     * @brief Applies the filter to the inputs and produces the results in the outputs.
     * The input and output vectors must be filled the appropriate amount of images before use.
     * @param inputs: variable amount of inputs
     * @param outputs: variable amount of outputs
     * @throws runtime_error: if the number of inputs/outputs don't match the specified inputs/outputs
     * this filter has.
     */
    virtual void Apply(const std::vector<IImage*>& inputs, const std::vector<IImage*>& outputs) {
        if (inputs.size() != GetInputs()) {
            throw std::runtime_error("Input vector does not have correct number of images!");
        } else if (outputs.size() != GetOutputs()) {
            throw std::runtime_error("Output vector does not have correct number of images!");
        }
        ApplyInternal(inputs, outputs);
    }

    /**
     * @return The number of inputs this filter uses.
     */
    virtual int GetInputs() const { return num_inputs; }

    /**
     * @return The number of outputs this filter uses.
     */
    virtual int GetOutputs() const { return num_outputs; }

protected:
    /**
     * @brief Classes that override Filter must implement ApplyInternal. This is called every time
     * Apply is called.
     * @param inputs: variable amount of inputs
     * @param outputs: variable amount of outputs
     */
    virtual void ApplyInternal(const std::vector<IImage*>& inputs, const std::vector<IImage*>& outputs) = 0;

    int num_inputs, num_outputs;

};

}

#endif //IMAGEIO_FILTER_H
