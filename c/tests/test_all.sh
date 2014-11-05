#!/bin/env bash

./utils_tests || exit 1
./math_utils_tests || exit 1

echo "All tests passed"
exit 0
