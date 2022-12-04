cmake_minimum_required(VERSION 3.0)
project(set VERSION 1.0.0 LANGUAGES CXX)


file(GLOB SET_INCLUDE_DIRS include)

set(CMAKE_CXX_STANDARD 17)

set(SANITIZE_FLAGS "-fsanitize=address,undefined \
                    -fno-sanitize-recover=all \
                    -fsanitize-undefined-trap-on-error")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ${SANITIZE_FLAGS}")

include_directories(${SET_INCLUDE_DIRS})
add_executable(set.out ./src/main.cpp)

enable_testing()
add_subdirectory(tests)
