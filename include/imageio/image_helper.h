#ifndef IMAGEIO_IMAGE_HELPER_H
#define IMAGEIO_IMAGE_HELPER_H

#include <string>

#include "iimage.h"
#include "greyscale_image.h"
#include "image.h"

namespace imageio {

using std::string;

/**
 * @namespace Static helper methods to use with IImage.
 */
namespace ImageHelper {

    /**
     * @brief Creates a *new* image from a file by opening it.
     * @param filename: must be a .png
     * @param img: A derived IImage, a clone will be made of this image and then
     * the image will be loaded onto that clone and returned. The default uses the Image class.
     * @return A *new* image. Will have the same type as the provided img.
     *
     * @example
     * @code IImage* image = ImageHelper::FromFile("image.png");
     * IImage* image = ImageHelper::FromFile("image2.png", MyImage());
     */
    static IImage* FromFile(const string& filename, const IImage& img = Image()) {
        auto clone = img.Clone();
        clone->Load(filename);
        return clone;
    }

    /**
     * @brief Creates a *new* image from a string (this string should be encoded as an image).
     * @param str: the string
     * @param img: A derived IImage, a clone will be made of this image and then
     * the image will be loaded onto that clone and returned. The default uses the Image class.
     */
    static IImage* FromString(const std::string& str, const IImage& img = Image()) {
        auto clone = img.Clone();
        clone->LoadFromString(str);
        return clone;
    }

    /**
     * @brief Creates a *new* image from a string (this string should be encoded as an image).
     * @param str: the string
     * @param length: length of the string
     * @param img: A derived IImage, a clone will be made of this image and then
     * the image will be loaded onto that clone and returned. The default uses the Image class.
     */
    static IImage* FromString(const char* str, int length, const IImage& img = Image()) {
        auto clone = img.Clone();
        clone->LoadFromString(str, length);
        return clone;
    }

    /**
     * @brief Creates a *new* image from a string (this string should be encoded as an image).
     * @param str: the string
     * @param length: length of the string
     * @param img: A derived IImage, a clone will be made of this image and then
     * the image will be loaded onto that clone and returned. The default uses the Image class.
     */
    static IImage* FromString(const uchar* str, int length, const IImage& img = Image()) {
        auto clone = img.Clone();
        clone->LoadFromString(str, length);
        return clone;
    }

    /**
     * @brief Create a *new* Image. Can be used as a factory.
     * @return a *new* image
     */
    static IImage* CreateImage() {
        return new Image();
    }

    /**
     * @brief Create a *new* GreyscaleImage. Can be used as a factory.
     * @return a *new* greyscale image
     */
    static IImage* CreateGreyscaleImage() {
        return new GreyscaleImage();
    }

}

}

#endif //IMAGEIO_IMAGE_HELPER_H
