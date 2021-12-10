#ifndef IMAGEIO_COLOR_H
#define IMAGEIO_COLOR_H

#include "util.h"

namespace imageio {

using uchar = unsigned char;

/**
 * @class Represents an RGBA pixel/color.
 */
class Color {
public:

    /**
     * @brief Construct using floats. Values between 0-1 are expected. A value of 0.0 has an RGB
     * value of 0, and a value of 1.0 has an RGB value of 255.
     * @param r: red
     * @param g: green
     * @param b: blue
     * @param a: alpha
     */
    explicit Color(float r=0.0f, float g=0.0f, float b=0.0f, float a=1.0f);

    /**
     * @return The luminance of this Color.
     */
    float GetLuminance() const;

    /**
     * @return The red value as an unsigned char.
     */
    uchar Red() const;

    /**
     * @return The green value as an unsigned char.
     */
    uchar Green() const;

    /**
     * @return The blue value as an unsigned char.
     */
    uchar Blue() const;

    /**
     * @return The alpha value as an unsigned char.
     */
    uchar Alpha() const;

    /**
     * @brief Multiply a Color by another, ignores alpha channel.
     * @param rhs: other color
     */
    void operator*=(const Color& rhs);

    /**
     * @brief Multiply a Color by a scalar, ignores alpha channel.
     * @param n: scalar
     */
    void operator*=(float n);

    /**
     * @brief Divide a Color by another, ignores alpha channel.
     * @param rhs: other color
     */
    void operator/=(const Color& rhs);

    /**
     * @brief Divide a Color by a scalar, ignores alpha channel.
     * @param n: scalar
     */
    void operator/=(float n);

    /**
     * @brief Add a Color to another, assumes alpha is 1.
     * @param rhs: other color
     * @return new color
     */
    Color operator+(const Color& rhs) const;

    /**
     * @brief Add a scalar to a Color, assumes alpha is 1.
     * @param n: scalar
     * @return new color
     */
    Color operator+(float n) const;

    /**
     * @brief Add a Color to another, ignores alpha.
     * @param rhs: other color
     */
    void operator+=(const Color& rhs);

    /**
     * @brief Add a scalar to a Color, ignores alpha.
     * @param n: scalar
     */
    void operator+=(float n);

    /**
     * @brief Multiply a Color by another, assumes alpha is 1.
     * @param rhs: other color
     * @return new color
     */
    Color operator*(const Color& rhs) const;

    /**
     * @brief Multiply a Color by a scalar, assumes alpha is 1.
     * @param n: scalar
     * @return new color
     */
    Color operator*(float n) const;

    /**
     * @brief Divide a Color by another, assumes alpha is 1.
     * @param rhs: other color
     * @return new color
     */
    Color operator/(const Color& rhs) const;

    /**
     * @brief Divide a Color by a scalar, assumes alpha is 1.
     * @param n: scalar
     * @return new color
    */
    Color operator/(float n) const;

    /**
     * @return An opaque version of this pixel.
     */
    Color Opaque() const;

    /**
     * @return A black pixel. RGBA: (0,0,0,255)
     */
    static Color Black();

    /**
     * @return A white pixel. RGBA: (255,255,255,255)
     */
    static Color White();

    float R,G,B,A;
};

}

#endif //IMAGEIO_COLOR_H
