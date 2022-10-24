cmake_minimum_required(VERSION 3.13)
project(test_base)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} test.cpp ../src/matrix.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)

add_test(
        NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
)