#!/bin/env bash


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

		cd tests

		COMMANDS="grep \\\$REFERENCE test_all.sh | cut -f2 -d\( | cut -f1 -d\)"

		COUNT=$(eval "$COMMANDS" | wc -l)

		echo "Running $COUNT C language solutions"

		time eval "$COMMANDS" | while read p; do eval "$p"; done > /dev/null 2>&1

		echo
	)
}


report_C
