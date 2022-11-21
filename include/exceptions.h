#pragma once // NOLINT

#include <exception>
#include <string>

#include "set.h"

namespace tp {
    class MatrixException : public std::exception {
    public:
        explicit MatrixException(const std::string &msg)
                : m_msg(msg) {}

        const char *what() const

        noexcept override{
                return m_msg.c_str();
        }

    private:
        std::string m_msg;
    };

    class InvalidMatrixSize : public MatrixException {
    public:
        explicit InvalidMatrixSize(const Matrix &matrix)
                : MatrixException("Invalid matrix size: rows = " +
                                  std::to_string(matrix.get_rows()) +
                                  ", cols = " +
                                  std::to_string(matrix.get_cols())) {
        }
    };


    class InvalidMatrixStream : public MatrixException {
    public:
        InvalidMatrixStream()
                : MatrixException("Error occurred while reading from stream") {}
    };

    class OutOfRange : public MatrixException {
    public:
        OutOfRange(size_t i, size_t j, const Matrix &matrix)
                : MatrixException(
                "Indexes (" + std::to_string(i) + ", " + std::to_string(j) + ") are out of range. Matrix size is [" +
                std::to_string(matrix.get_rows()) + ", " + std::to_string(matrix.get_cols()) + "]"
        ) {}
    };

    class DimensionMismatch : public MatrixException {
    public:
        DimensionMismatch(const Matrix &m1, const Matrix &m2)
                : MatrixException(
                "M1[" + std::to_string(m1.get_rows()) + ", " + std::to_string(m1.get_cols()) + "] and M2[" +
                std::to_string(m2.get_rows()) + ", " + std::to_string(m2.get_cols()) + "] are not compatible"
        ) {}

        explicit DimensionMismatch(const Matrix &m)
                : MatrixException(
                "M[" + std::to_string(m.get_rows()) + ", " + std::to_string(m.get_cols()) + "] isn't square matrix"
        ) {}
    };

    class SingularMatrix : public MatrixException {
    public:
        SingularMatrix()
                : MatrixException("Singular matrix") {}
    };
}  // namespace tp
