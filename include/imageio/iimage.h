#ifndef IMAGEIO_IIMAGE_H
#define IMAGEIO_IIMAGE_H

#include <memory>
#include <string>
#include <vector>

#include "color.h"
#include "matrix.h"
#include "util.h"

/**
 * @namespace Contains all the classes and methods for the imageio library.
 */
namespace imageio {

/**
 * @class An abstract image class. Represents an image of RGBA values.
 */
class IImage {

public:

    /**
     * @brief Construct a blank image with a given width and height.
     * @param width: width of image
     * @param height: height of image
     * @note Underlying classes must call and implement this constructor. This constructor will:
     * initialize width and height to the provided variables. Derived classes should use
     * the width and height attributes to allocate space for their underlying data implementation.
     */
    explicit IImage(int width, int height) : width(width), height(height) {}

    virtual ~IImage() = default;

    /**
     * @brief Creates a *new* clone of an image. Functionally identical to a copy of said image.
     * @return The clone/copy as *new* ptr.
     */
    virtual IImage* Clone() const = 0;

    /**
     * @return The width of the image.
     */
    virtual int GetWidth() const { return width; };

    /**
     * @return The height of the image.
     */
    virtual int GetHeight() const { return height; };

    /**
     * @brief Returns the RGBA values of the pixel at (x, y).
     * @param x: x index
     * @param y: y index
     * @return Color/RGBA at (x, y)
     */
    virtual Color GetPixel(int x, int y) const = 0;

    /**
     * @brief Sets the pixel at (x, y) to the new pixel provided.
     * @param x: x index
     * @param y: y index
     * @param color: the new pixel
     */
    virtual void SetPixel(int x, int y, const Color& color) = 0;

    /**
     * @brief Returns the greyscale threshold value of the pixel at (x, y).
     * Use this iff you know the image is a greyscale image.
     * @param x: x index
     * @param y: y index
     * @return: greyscale threshold at (x, y)
     */
    virtual float GetGreyscale(int x, int y) const = 0;

    /**
     * @brief Sets the pixel at (x, y) to the greyscale threshold.
     * Uses an alpha of 1 (no transparency).
     * @param x: x index
     * @param y: y index
     * @param greyscale: greyscale threshold to use
     */
    virtual void SetGreyscale(int x, int y, float greyscale) = 0;

    /**
     * @brief Multiply every pixel in the image across RGB values. Does not modify alpha values, only RGB.
     * @param color: the RGB color, will multiply each RGB value respectively by the RGB values provided.
     */
    virtual void operator*=(const Color& color);

    /**
     * @brief Multiply every pixel in the image by a scalar. Does not modify alpha values, only RGB.
     * @param n: scalar
     */
    virtual void operator*=(float n);

    /**
     * @brief Resize the image.
     * @param width: new width
     * @param height: new height
     */
    virtual void Resize(int width, int height);

    /**
     * @brief Resizes an image using the width and height of another image.
     * This DOES NOT copy anything from that image.
     * @param image: image to resize to according to dimensions
     */
    virtual void Resize(const IImage& image);

    /**
     * @brief Load an image into this image object.
     * @param filename: The image filename/filepath to load.
     */
    virtual void Load(const std::string& filename);

    /**
     * @brief Save the image into the given filename. Filename must be a .png.
     * @param filename: filename/filepath to save file to.
     */
    virtual void SaveAs(const std::string& filename) const;

    /**
     * @brief Load an image from a string (this string should be encoded as an image).
     * @param str: the string
     */
    virtual void LoadFromString(const std::string& str);

    /**
     * @brief Load an image from a char string (this string should be encoded as an image).
     * @param str: the string
     * @param length: length of the string
     */
    virtual void LoadFromString(const char* str, int length);

    /**
     * @brief Load an image from an unsigned char string (this string should be encoded as an image).
     * @param str: the string
     * @param length: length of the string
     */
    virtual void LoadFromString(const uchar* str, int length);

    /**
     * @brief Copy another image into this image. This will modify the width and height to match
     * the other image. Functionally equivalent to a copy constructor/operator.
     * @param image: the image to copy from.
     */
    virtual void CopyFrom(const IImage& image);

    /**
     * @brief Convolve an image using the given kernel, put the results in output. It is assumed that the kernel
     * is a square matrix with an odd number of cols/rows. This will resize the output for you.
     * @param output: the output image (result of the convolution)
     * @param kernel: kernel matrix
     */
    virtual void Convolve(IImage& output, const Matrix& kernel);

    /**
     * @brief Convolve an image using the given kernel, put the results in output. It is assumed that the kernel
     * is a square matrix with an odd number of cols/rows. Only operates from [startX, endX), [startY, endY).
     * This is thread-safe. You MUST resize the output image to have the same dimensions as this image before calling
     * this or it will cause problems.
     * @param startX: the starting x coordinate (inclusive)
     * @param endX: the ending x coordinate (exclusive)
     * @param startY: the starting y coordinate (inclusive)
     * @param endY: the ending y coordinate (exclusive)
     * @param output: the output image (result of the convolution)
     * @param kernel: kernel matrix
     */
    virtual void Convolve(int startX, int endX, int startY, int endY, IImage& output, const Matrix& kernel) const;

    /**
     * @brief Normalize the image by dividing each pixels value by the largest RGB values in the image. Does so IN PLACE.
     */
    virtual void Normalize();

protected:
    int width, height;

    /**
     * @brief Resize the underlying data to support width x height amount of pixels. The width and height members
     * have already been set before this function is called.
     */
    virtual void ResizeInternal() = 0;

    /**
     * @brief Loads an image from an array created by stbi_load or stbi_laod_from_memory.
     * This will free the memory. Width/height must be set before calling this.
     * @param data: unsigned char array created by stbi_load or stbi_laod_from_memory
     */
    virtual void LoadFromSTBI(uchar* data);

};

}

#endif //IMAGEIO_IIMAGE_H
