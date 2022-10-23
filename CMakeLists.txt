cmake_minimum_required(VERSION 3.0)
project(matrix VERSION 1.0.0 LANGUAGES CXX)

# include
include_directories(include)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")

add_executable(matrix.out ./src/main.cpp ./src/matrix.cpp)
