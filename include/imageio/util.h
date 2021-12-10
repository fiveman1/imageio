#ifndef IMAGEIO_UTIL_H
#define IMAGEIO_UTIL_H

namespace imageio {

/**
 * @namespace Contains various helper methods and constants.
 */
namespace Util {

    constexpr float pi = 3.141592653589793238462643383279502884f;
    constexpr float eps = 0.00000001f;

    /**
     * @brief Clamps val between lo and hi.
     * @tparam T: must be eligible for comparisons
     * @param val: the value to be clamped
     * @param lo: the low/min
     * @param hi: the high/max
     * @return result of the clamp
     */
    template<typename T>
    constexpr T clamp(T val, T lo, T hi) {
        return val < lo ? lo : val > hi ? hi : val;
    }

    /**
     * @brief Squares x by multiplying it by itself.
     * @tparam T: must be eligible for multiplication
     * @param x: the value to square
     * @return the square of x
     */
    template<typename T>
    constexpr T square(T x) {
        return x * x;
    }

    /**
     * @brief Returns whether val is between low and high.
     * @tparam T: must be eligible for comparisons
     * @param low: low/min
     * @param val: value
     * @param high: high/max
     * @return whether val is between low and high
     */
    template<typename T>
    constexpr bool between(T low, T val, T high) {
        return low <= val and val < high;
    }

}

}

#endif //IMAGEIO_UTIL_H
