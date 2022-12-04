#!/usr/bin/bash

PROJECT_DIR=$(pwd)

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUNNING TESTS"
cd ./build && ctest -V -R

print_header "GENERATING COVERAGE INFO"
lcov -o coverage.info -c -d tests
lcov --remove coverage.info '/usr/*' "${PROJECT_DIR}/tests/*" -o filtered_coverage.info

print_header "COVERAGE REPORT"
genhtml -o report filtered_coverage.info
