cmake_minimum_required(VERSION 3.0)
project(set VERSION 1.0.0 LANGUAGES CXX)

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

SET(SANITIZE_FLAGS "-fsanitize=address,undefined \
                    -fno-sanitize-recover=all \
                    -fsanitize-undefined-trap-on-error")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ${SANITIZE_FLAGS}")

add_executable(set.out ./src/main.cpp)  # ./src/test_set.cpp
# add_executable(set.out ./src/test_set.cpp)

# enable_testing()
# add_subdirectory(tests)
