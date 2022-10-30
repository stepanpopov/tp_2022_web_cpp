cd ./build && ctest -V -R

# lcov -t "tests/tests_logic" -o coverage.info -c -d logic/
# genhtml -o report coverage.info
