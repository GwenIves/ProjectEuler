#!/bin/env bash

DATA_DIR=../../shared/data

report_C ()
{
	(
		cd c

		make build > /dev/null 2>&1

		if [ $? -ne 0 ]
		then
			echo "Build failed for C code"
			exit 1
		fi

		LOC=$(wc -l src/*.c common/*.c common/include/*.h tests/*.c | tail -1 | awk '{print $1;}')

		cd tests

		COMMANDS="grep \\\$REFERENCE test_all.sh | cut -f2 -d\( | cut -f1 -d\)"

		COUNT=$(eval "$COMMANDS" | wc -l)

		echo "Running $COUNT C language solutions ($LOC lines of code)"

		time eval "$COMMANDS" | while read p; do eval "$p"; done > /dev/null

		echo
	)
}


report_C
