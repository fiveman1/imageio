#include "imageio/iimage.h"

#define STB_IMAGE_IMPLEMENTATION
#include "imageio/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "imageio/stb_image_write.h"

namespace imageio {

void IImage::SaveAs(const string &filename) const {
    auto image = unique_ptr<uchar[]>(new uchar[width * height * 4]);
    auto i = image.get() - 1;
    Color pixel;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixel = GetPixel(x, y);
            *(++i) = pixel.Red();
            *(++i) = pixel.Green();
            *(++i) = pixel.Blue();
            *(++i) = pixel.Alpha();
        }
    }
    stbi_write_png(filename.c_str(), width, height, 4, image.get(), width*4);
}

void IImage::Load(const string &filename) {
    int components;
    uchar* image = stbi_load(filename.c_str(), &width, &height, &components, STBI_rgb_alpha);
    LoadFromSTBI(image);
}

void IImage::LoadFromString(const string &str) {
    LoadFromString(reinterpret_cast<const uchar*>(str.c_str()), static_cast<int>(str.length()));
}

void IImage::LoadFromString(const char *str, int length) {
    LoadFromString(reinterpret_cast<const uchar*>(str), length);
}

void IImage::LoadFromString(const uchar* str, int length) {
    int components;
    auto image = stbi_load_from_memory(str, length, &width, &height, &components, STBI_rgb_alpha);
    LoadFromSTBI(image);
}

void IImage::LoadFromSTBI(uchar *data) {
    ResizeInternal();
    float red, green, blue, alpha;
    int len = width * height;
    int temp;
    for (int i = 0; i < len; ++i) {
        temp = i * 4;
        red = static_cast<float>(data[temp]) / 255.0f;
        green = static_cast<float>(data[temp + 1]) / 255.0f;
        blue = static_cast<float>(data[temp + 2]) / 255.0f;
        alpha = static_cast<float>(data[temp + 3]) / 255.0f;
        SetPixel(i % width, i / width, Color(red, green, blue, alpha));
    }
    stbi_image_free(data);
}

void IImage::CopyFrom(const IImage &image) {
    Resize(image);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            SetPixel(x, y, image.GetPixel(x, y));
        }
    }
}

void IImage::operator*=(const Color &color) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            SetPixel(x, y, GetPixel(x, y) * color);
        }
    }
}

void IImage::operator*=(float n) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            SetPixel(x, y, GetPixel(x, y) * n);
        }
    }
}

void IImage::Convolve(IImage &output, const Matrix &kernel) {
    Resize(output);
    Convolve(0, GetWidth(), 0, GetHeight(), output, kernel);
}

void IImage::Convolve(int startx, int endx, int starty, int endy, IImage &output,
                      const Matrix &kernel) const {
    int size = kernel.GetRows();
    int r = size / 2;
    Color curr;
    int c1, r1;
    for (int y = starty; y < endy; ++y) {
        for (int x = startx; x < endx; ++x) {
            curr = Color(0.0f, 0.0f, 0.0f, 1.0f);
            for (int row = 0; row < size; ++row) {
                for (int col = 0; col < size; ++col) {
                    c1 = clamp(x + col - r, 0, width - 1);
                    r1 = clamp(y + row - r, 0, height - 1);
                    curr += GetPixel(c1, r1) * kernel(col, row);
                }
            }
            output.SetPixel(x, y, curr);
        }
    }
}

void IImage::Resize(int w, int h) {
    width = w;
    height = h;
    ResizeInternal();
}

void IImage::Resize(const IImage &image) {
    Resize(image.GetWidth(), image.GetHeight());
}

void IImage::Normalize() {
    float maxR = 0.0f;
    float maxG = 0.0f;
    float maxB = 0.0f;
    Color pixel;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixel = GetPixel(x, y);
            if (pixel.R > maxR) maxR = pixel.R;
            if (pixel.G > maxG) maxG = pixel.G;
            if (pixel.B > maxB) maxB = pixel.B;
        }
    }

    *this *= Color(1.0f / maxR, 1.0f / maxG, 1.0f / maxB, 1.0f);
}

}
