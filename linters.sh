#!/usr/bin/env bash

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN cppcheck"
cppcheck src --enable=all --inconclusive --error-exitcode=1 -I include --suppress=missingIncludeSystem


print_header "RUN cpplint"
cpplint --extensions=cpp src/* include/*

print_header "SUCCESS"
