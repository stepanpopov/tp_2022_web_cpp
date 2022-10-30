#include "exceptions.h"
#include "matrix.h"

namespace tp {
    Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols),
                                               elements(rows * cols, 0) {
        if (rows == 0 || cols == 0) {
            throw InvalidMatrixSize(*this);
        }

        if (rows * cols >= MATRIX_MAX_SIZE) {
            throw InvalidMatrixSize(*this);
        }
    }

    Matrix::Matrix(const std::initializer_list<double> &init_list, size_t rows, size_t cols) :
            Matrix(rows, cols) {
        if (init_list.size() > rows * cols) {
            throw InvalidMatrixSize(*this);
        }

        elements = init_list;
    }

    Matrix &Matrix::operator=(const std::initializer_list<double> &init_list) {
        rows = 1;
        cols = init_list.size();
        elements = init_list;
        return *this;
    }

    Matrix::Matrix(const std::vector<double> &vec) : rows(1), cols(vec.size()), elements(vec) {}

    size_t Matrix::get_rows() const {
        return (this->rows);
    }

    size_t Matrix::get_cols() const {
        return (this->cols);
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= this->rows || j >= this->cols) {
            throw OutOfRange(i, j, *this);
        }
        return this->elements[i * cols + j];
    }

    double &Matrix::operator()(size_t i, size_t j) {
        if (i >= this->rows || j >= this->cols) {
            throw OutOfRange(i, j, *this);
        }
        return this->elements[i * cols + j];
    }

    std::vector<double> Matrix::get_col(size_t ind) const {
        std::vector<double> col(rows, 0);
        for (size_t i = 0; i < rows; ++i) {
            col[i] = (*this)(i, ind);
        }
        return col;
    }

    std::vector<double> Matrix::get_row(size_t ind) const {
        std::vector<double> row(cols, 0);
        for (size_t j = 0; j < cols; ++j) {
            row[j] = (*this)(ind, j);
        }
        return row;
    }

    std::vector<double> Matrix::get_diagonal(int k) const {
        std::vector<double> diagonal;
        for (size_t i = k; i < std::min(cols, rows); ++i) {
            diagonal.push_back((*this)(i - k, i));
        }
        return diagonal;
    }

    bool Matrix::operator==(const Matrix &rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            return false;
        }

        bool cmp_flag = true;
        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                if (std::abs((*this)(i, j) - rhs(i, j)) > K_EPSILON) {
                    cmp_flag = false;
                    break;
                }
            }
            if (!cmp_flag) {
                break;
            }
        }
        return cmp_flag;
    }

    bool Matrix::operator!=(const Matrix &rhs) const {
        return !(*this == rhs);
    }

    Matrix Matrix::operation(const Matrix &lhs, const Matrix &rhs,
                             std::function<double(double, double)> oper) {
        if (lhs.rows != rhs.rows || lhs.cols != rhs.cols) {
            throw DimensionMismatch(lhs, rhs);
        }

        Matrix matrix_res(lhs.rows, lhs.cols);
        for (size_t i = 0; i < lhs.rows; ++i) {
            for (size_t j = 0; j < lhs.cols; ++j) {
                matrix_res(i, j) = oper(lhs(i, j), rhs(i, j));
            }
        }
        return matrix_res;
    }

    Matrix Matrix::operator+(const Matrix &rhs) const {
        return Matrix::operation(*this, rhs, std::plus<double>());
    }

    Matrix Matrix::operator-(const Matrix &rhs) const {
        return Matrix::operation(*this, rhs, std::minus<double>());
    }

    Matrix Matrix::operator*(const Matrix &rhs) const {
        if (this->cols != rhs.rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix matrix_mul(this->rows, rhs.cols);

        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < rhs.cols; ++j) {
                matrix_mul(i, j) = 0;
                for (size_t k = 0; k < this->cols; ++k) {
                    matrix_mul(i, j) += (*this)(i, j) * rhs(i, j);
                }
            }
        }
        return matrix_mul;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix matrix_scal(this->rows, this->cols);
        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                matrix_scal(i, j) = (*this)(i, j) * val;
            }
        }
        return matrix_scal;
    }

    Matrix Matrix::transp() const {
        Matrix matrix_transp(this->cols, this->rows);
        for (size_t i = 0; i < matrix_transp.rows; ++i) {
            for (size_t j = 0; j < matrix_transp.cols; ++j) {
                matrix_transp(i, j) = (*this)(i, j);
            }
        }
        return matrix_transp;
    }

    Matrix operator*(double val, const Matrix &matrix) {
        return matrix * val;
    }

    double Matrix::det() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }
        return determinant_of_matrix(elements, rows);
    }

    double Matrix::determinant_of_matrix(const std::vector<double> &matrix, size_t n) const {
        double determinant = 0;
        if (n == 1) {
            return matrix[0];
        }
        if (n == 2) {
            return (matrix[0] * matrix[rows + 1]) - (matrix[1] * matrix[rows]);
        }

        int sign = 1;
        for (size_t i = 0; i < n; ++i) {
            std::vector<double> minor = minor_matrix(matrix, 0, i, n);
            determinant += sign * matrix[i] * determinant_of_matrix(minor, n - 1);
            sign = -sign;
        }
        return determinant;
    }

    std::vector<double> Matrix::minor_matrix(const std::vector<double> &mat,
                                             size_t p, size_t q, size_t n) const {
        std::vector<double> temp(rows *rows);
        size_t i = 0, j = 0;
        for (size_t row = 0; row < n; ++row) {
            for (size_t col = 0; col < n; ++col) {
                if (row != p && col != q) {
                    temp[i * rows + j] = mat[row * rows + col];
                    j++;
                    if (j == n - 1) {
                        j = 0;
                        i++;
                    }
                }
            }
        }
        return temp;
    }

    std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        os << std::setprecision(OUT_PRECISION);
        os << matrix.rows << ' ' << matrix.cols << std::endl;
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << matrix(i, j) << ' ';
            }
            os << std::endl;
        }
        return os;
    }

}  // namespace tp
