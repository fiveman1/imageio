#ifndef IMAGEIO_MATRIX_H
#define IMAGEIO_MATRIX_H

#include <algorithm>
#include <initializer_list>
#include <vector>

namespace imageio {

/**
 * @class Represents a column-major matrix of floats.
 */
class Matrix {

public:
    /**
     * @brief Constructor a matrix using cols x rows (column-major).
     * @param cols: number of columns
     * @param rows: number of rows
     * @param default_value: what to populate the matrix with initially
     */
    explicit Matrix(int cols = 0, int rows = 0, float default_value = 0.0f);

    /**
     * @brief Construct a matrix using an initializer list. Blindly assumes that
     * each row has the same size.
     * @example Matrix mat = { {0.0, 1.0}, {-1.0, 3.5} }
     * @param list: initializer list, which is a list of rows
     */
    Matrix(const std::initializer_list<std::vector<float>>& list);

    /**
     * @return number of columns
     */
    int GetCols() const { return cols; }

    /**
     * @return number of rows
     */
    int GetRows() const { return rows; }

    /**
     * @brief Gets the value at (col, row)
     * @param col: column
     * @param row: row
     * @return value at (col, row)
     */
    float operator()(int col, int row) const {
        return array[at(col, row, cols)];
    }

    /**
     * @brief Set the value of (col, row) to val
     * @param col: column
     * @param row: row
     * @param val: new value
     */
    void Set(int col, int row, float val) {
        array[at(col, row, cols)] = val;
    }

    /**
     * @brief Normalize the matrix IN PLACE by summing every value
     * then dividing each value by the sum. Ensures that the items in the matrix add up to exactly 1.
     */
    void Normalize();

private:

    static constexpr int at(int col, int row, int cols) {
        return col + row * cols;
    }

    int cols, rows;
    std::vector<float> array;
};

}

#endif //IMAGEIO_MATRIX_H
