#ifndef IMAGEIO_GREYSCALE_IMAGE_H
#define IMAGEIO_GREYSCALE_IMAGE_H

#include "iimage.h"

namespace imageio {

/**
 * @class Greyscale image. Use this iff the image you are working with is known to be
 * a greyscale image. Offers improved performance over normal Image in this case. Implementation
 * uses floats to represent pixels, assumes that RGB are all equal and alpha is 1.
 */
class GreyscaleImage : public IImage {

public:

    explicit GreyscaleImage(int width = 0, int height = 0) : IImage(width, height), array(width * height) {};

    IImage* Clone() const override;

    Color GetPixel(int x, int y) const override;

    void SetPixel(int x, int y, const Color &color) override;

    float GetGreyscale(int x, int y) const override;

    void SetGreyscale(int x, int y, float greyscale) override;

    void operator*=(const Color &color) override;

    void operator*=(float n) override;

    void Convolve(int startx, int endx, int starty, int endy, IImage &output, const Matrix &kernel) const override;

    void Normalize() override;

protected:

    std::vector<float> array;

    void ResizeInternal() override;

    static constexpr int at(int col, int row, int cols);

};

}

#endif //IMAGEIO_GREYSCALE_IMAGE_H
