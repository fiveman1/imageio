#include "imageio/color.h"

namespace imageio {

Color::Color(float r, float g, float b, float a)  : R(r), G(g), B(b), A(a) {}

float Color::GetLuminance() const {
    return 0.2126f*R + 0.7152f*G + 0.0722f*B;
}

uchar Color::Red() const {
    return static_cast<uchar>(clamp(R, 0.0f, 1.0f) * 255);
}

uchar Color::Green() const {
    return static_cast<uchar>(clamp(G, 0.0f, 1.0f) * 255);
}

uchar Color::Blue() const {
    return static_cast<uchar>(clamp(B, 0.0f, 1.0f) * 255);
}

uchar Color::Alpha() const {
    return static_cast<uchar>(clamp(A, 0.0f, 1.0f) * 255);
}

void Color::operator*=(const Color &rhs) {
    R *= rhs.R;
    G *= rhs.G;
    B *= rhs.B;
}

void Color::operator*=(float n) {
    R *= n;
    G *= n;
    B *= n;
}

void Color::operator/=(const Color &rhs) {
    R /= rhs.R;
    G /= rhs.G;
    B /= rhs.B;
}

void Color::operator/=(float n) {
    *this *= (1.0f / n);
}

Color Color::operator+(const Color &rhs) const {
    return Color(R + rhs.R, G + rhs.G, B + rhs.B, 1.0f);
}

Color Color::operator+(float n) const {
    return Color(R + n, G + n, B + n, 1.0f);
}

void Color::operator+=(const Color &rhs) {
    R += rhs.R;
    G += rhs.G;
    B += rhs.B;
}

void Color::operator+=(float n) {
    R += n;
    G += n;
    B += n;
}

Color Color::operator*(const Color &rhs) const {
    return Color(R * rhs.R, G * rhs.G, B * rhs.B, 1.0f);
}

Color Color::operator*(float n) const {
    return Color(R * n, G * n, B * n, 1.0f);
}

Color Color::operator/(const Color &rhs) const {
    return Color(R / rhs.R, G / rhs.G, B / rhs.B, 1.0f);
}

Color Color::operator/(float n) const {
    return *this * (1.0f / n);
}

}
