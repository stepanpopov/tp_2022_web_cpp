#include <iostream>
#include "matrix.h"

int main() {
    tp::Matrix mat({1, 2, 11, 4, 5, 6, 7, 8, 10}, 3, 3);

    std::cout << mat.det() << std::endl;

    return 0;
}
