#include <iostream>

#include "gtest/gtest.h"

#include "matrix.h"

TEST(MatrixTest, returnTest) {
    tp::Matrix matr(4,5);
    ASSERT_EQ(matr.get_rows(), 4);
}


