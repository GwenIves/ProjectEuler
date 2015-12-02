#!/bin/env bash

echo "Running library unit tests"

./math_utils_tests.py || exit 1

echo "Running program tests"

../../shared/scripts/test_solutions.sh || exit 1

echo "All tests passed"
exit 0
