#!/bin/env bash

DATA_DIR=../../shared/data

for p in *_tests
do
	valgrind -q --error-exitcode=1 --leak-check=full ./$p || exit 1
done > /dev/null

grep \\\$REFERENCE ../../shared/scripts/test_solutions.sh | cut -f2 -d\( | cut -f1 -d\) | \
while read p
do
	eval "valgrind -q --error-exitcode=1 --leak-check=full $p" || exit 1
done > /dev/null

echo "Verification successful"
exit 0
