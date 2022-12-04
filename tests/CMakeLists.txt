cmake_minimum_required(VERSION 3.13)
project(testing)

set(SANITIZE_FLAGS "-fsanitize=address,undefined \
                    -fno-sanitize-recover=all \
                    -fsanitize-undefined-trap-on-error")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZE_FLAGS} -fprofile-arcs -ftest-coverage -O0")

# GTEST FETCH BEGIN
#[[include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)]]
# GTEST FETCH END

include_directories(${SET_INCLUDE_DIRS})

# GTEST tests
set(MY_TESTS "my_tests.out")
find_package(GTest REQUIRED)
add_executable(${MY_TESTS} test.cpp)

target_include_directories(${MY_TESTS} PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(${MY_TESTS} GTest::gtest_main)

add_test(
        NAME ${MY_TESTS}
        COMMAND ${MY_TESTS}
)


# NOT GTEST tests
set(BASE_TESTS "base_tests.out")
add_executable(${BASE_TESTS} test_set.cpp)

add_test(
        NAME ${BASE_TESTS}
        COMMAND ${BASE_TESTS}
)
