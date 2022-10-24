cmake_minimum_required(VERSION 3.0)
project(matrix VERSION 1.0.0 LANGUAGES CXX)

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

add_executable(matrix.out ./src/main.cpp ./src/matrix.cpp)

enable_testing()
add_subdirectory(tests)
