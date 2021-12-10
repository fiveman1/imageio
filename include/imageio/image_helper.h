#ifndef IMAGEIO_IMAGE_HELPER_H
#define IMAGEIO_IMAGE_HELPER_H

#include <string>

#include "iimage.h"
#include "greyscale_image.h"
#include "image.h"

namespace imageio {

/**
 * @namespace Static helper methods to use with IImage.
 */
namespace ImageHelper {

    /**
     * @brief Creates a *new* image from a file by opening it.
     * @tparam ImageT: The type of the underlying image (default: Image)
     * @param filename: must be a .png
     * @return A *new* image. Will have the same type as the provided img.
     *
     * @example
     * @code IImage* image = ImageHelper::FromFile("image.png");
     * IImage* image = ImageHelper::FromFile<MyImageClass>("image2.png");
     */
    template<class ImageT = Image>
    static IImage* FromFile(const std::string& filename) {
        auto img = new ImageT;
        img->Load(filename);
        return img;
    }

    /**
     * @brief Creates a *new* image from a string (this string should be encoded as an image).
     * @tparam ImageT: The type of the underlying image (default: Image)
     * @param str: the string
     */
    template<class ImageT = Image>
    static IImage* FromString(const std::string& str) {
        auto img = new ImageT;
        img->LoadFromString(str);
        return img;
    }

    /**
     * @brief Creates a *new* image from a string (this string should be encoded as an image).
     * @tparam ImageT: The type of the underlying image (default: Image)
     * @param str: the string
     * @param length: length of the string
     */
    template<class ImageT = Image>
    static IImage* FromString(const char* str, int length) {
        auto img = new ImageT;
        img->LoadFromString(str, length);
        return img;
    }

    /**
     * @brief Creates a *new* image from a string (this string should be encoded as an image).
     * @tparam ImageT: The type of the underlying image (default: Image)
     * @param str: the string
     * @param length: length of the string
     */
    template<class ImageT = Image>
    static IImage* FromString(const uchar* str, int length) {
        auto img = new ImageT;
        img->LoadFromString(str, length);
        return img;
    }

    /**
     * @brief Create a *new* Image. Can be used as a factory.
     * @tparam ImageT: The type of the underlying image (default: Image)
     * @return a *new* image
     */
    template<class ImageT = Image>
    static IImage* CreateImage() {
        return new ImageT;
    }

}

}

#endif //IMAGEIO_IMAGE_HELPER_H
