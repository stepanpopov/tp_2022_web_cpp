cmake_minimum_required(VERSION 3.13)
project(testing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

# GTEST FETCH BEGIN
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
find_package(GTest REQUIRED)
# GTEST FETCH END

include_directories(../include)

# GTEST tests
add_executable(${PROJECT_NAME} test.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${GTEST_INCLUDE_DIRS} ../include)
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)


# NOT GTEST tests
set(BASE_TESTS "base_tests")
# target_include_directories(${BASE_TESTS} PUBLIC ../include)
add_executable(${BASE_TESTS} test_set.cpp)

add_test(
        NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
)

add_test(
        NAME ${BASE_TESTS}
        COMMAND ${BASE_TESTS}
)
