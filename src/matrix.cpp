#include "imageio/matrix.h"

namespace imageio {

Matrix::Matrix(int cols, int rows, float default_value) : cols(cols), rows(rows) {
    array = std::vector<float>(cols * rows, default_value);
}

Matrix::Matrix(const std::initializer_list<std::vector<float>> &list) : cols(list.begin()->size()), rows(list.size()) {
    array = std::vector<float>(cols * rows);
    int idx = 0;
    for (const auto& row : list) {
        std::copy(row.begin(), row.end(), array.begin() + idx);
        idx += cols;
    }
}

void Matrix::Normalize() {
    float sum = 0.0f;
    for (float i : array) {
        sum += i;
    }

    sum = 1.0f / sum;

    for (float& i : array) {
        i *= sum;
    }
}

}
