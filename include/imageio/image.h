#ifndef IMAGEIO_IMAGE_H
#define IMAGEIO_IMAGE_H

#include <stdexcept>
#include <vector>

#include "iimage.h"

namespace imageio {

/**
 * @class Represents a standard RGBA image. Implementation uses Color objects (RGBA) to represent images.
 */
class Image : public IImage {

public:

    explicit Image(int width = 0, int height = 0) : IImage(width, height), array(width * height) {};

    IImage* Clone() const override;

    Color GetPixel(int x, int y) const override;

    void SetPixel(int x, int y, const Color &color) override;

    float GetGreyscale(int x, int y) const override;

    void SetGreyscale(int x, int y, float greyscale) override;

    void operator*=(const Color &color) override;

    void operator*=(float n) override;

protected:

    std::vector<Color> array;

    void ResizeInternal() override;

    static constexpr int at(int col, int row, int cols) {
        return col + row * cols;
    }

};

}

#endif //IMAGEIO_IMAGE_H
