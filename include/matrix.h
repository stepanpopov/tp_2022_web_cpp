#pragma once // NOLINT

#include <functional>
#include <limits>
#include <vector>
#include <initializer_list>
#include <iomanip>
#include <iostream>

namespace tp {
    static constexpr double K_EPSILON = std::numeric_limits<double>::epsilon();
    static const int OUT_PRECISION = 20;
    static const int MATRIX_MAX_SIZE = 10000;

    class Matrix {
    public:
        explicit Matrix(size_t rows = 1, size_t cols = 1);

        explicit Matrix(const std::initializer_list<double> &init_list, size_t rows, size_t cols);

        Matrix &operator=(const std::initializer_list<double> &init_list);

        explicit Matrix(const std::vector<double> &vec);

        Matrix(const Matrix &rhs) = default;

        Matrix &operator=(const Matrix &rhs) = default;

        ~Matrix() = default;

        size_t get_rows() const;

        size_t get_cols() const;

        double operator()(size_t i, size_t j) const;

        double &operator()(size_t i, size_t j);

        std::vector<double> get_col(size_t ind) const;

        std::vector<double> get_row(size_t ind) const;

        std::vector<double> get_diagonal(int k = 0) const;

        bool operator==(const Matrix &rhs) const;

        bool operator!=(const Matrix &rhs) const;

        Matrix operator+(const Matrix &rhs) const;

        Matrix operator-(const Matrix &rhs) const;

        Matrix operator*(const Matrix &rhs) const;

        Matrix operator*(double val) const;

        friend
        Matrix operator*(double val, const Matrix &matrix);

        Matrix transp() const;

        double det() const;

        friend
        std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

    private:
        size_t rows;
        size_t cols;
        std::vector<double> elements;

        static Matrix operation(const Matrix &lhs, const Matrix &rhs,
                                std::function<double(double, double)> oper);

        double determinant_of_matrix(const std::vector<double> &matrix,
                                     size_t n) const;

        std::vector<double> minor_matrix(const std::vector<double> &mat,
                                         size_t p, size_t q, size_t n) const;
    };

    Matrix operator*(double val, const Matrix &matrix);

    std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
}  // namespace tp
