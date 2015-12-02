#!/bin/env bash

SHARED=../../shared
DATA_DIR=${SHARED}/data
SCRIPTS_DIR=${SHARED}/scripts

EXECUTABLES="grep \\\$REFERENCE ${SCRIPTS_DIR}/test_solutions.sh | cut -f2 -d\\\" | cut -f1 -d' '"
COMMANDS="grep \\\$REFERENCE ${SCRIPTS_DIR}/test_solutions.sh | cut -f2 -d\\\""

get_count ()
{
	count=0

	for executable in $(eval "$EXECUTABLES")
	do
		if [ -f $executable ]
		then
			((count++))
		fi
	done

	echo $count
}

# Parameters: <Language> <LOC>
do_report ()
{
	cd tests

	echo "Running $(get_count) $1 language solutions ($2 lines of code)"

	time eval "$COMMANDS" | while read p; do eval "$p"; done > /dev/null 2>&1

	echo
}

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

		do_report C $LOC
	)
}

report_Python ()
{
	(
		cd python

		LOC=$(wc -l src/* common/*.py tests/*.py | tail -1 | awk '{print $1;}')

		do_report Python $LOC
	)
}

report_Python
report_C
