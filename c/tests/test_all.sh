#!/bin/env bash

echo "Running library unit tests"

./utils_tests || exit 1
./linked_list_tests || exit 1
./hash_table_tests || exit 1
./math_utils_tests || exit 1
./euler_utils_tests || exit 1
./date_utils_tests || exit 1
./fraction_tests || exit 1
./continued_fraction_tests || exit 1
./bignum_tests || exit 1
./geometry_tests || exit 1

echo "Running program tests"

../../shared/scripts/test_solutions.sh || exit 1

echo "All tests passed"
exit 0
