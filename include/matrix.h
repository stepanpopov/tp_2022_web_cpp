#pragma once // NOLINT

#include <functional>
#include <istream>
#include <limits>
#include <vector>
#include <initializer_list>

namespace tp {
    static constexpr double kEpsilon = std::numeric_limits<double>::epsilon();
    static const int outPrecision = 20;

    class Matrix {
    public:
        explicit Matrix(size_t rows = 0, size_t cols = 0);

        Matrix(const std::initializer_list<double> &init_list);

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

        void sub_matrix(const std::vector<double> &mat,
                        std::vector<double> &temp,
                        size_t p, size_t q, size_t n) const;
    };

    Matrix operator*(double val, const Matrix &matrix);

    std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
}  // namespace tp
