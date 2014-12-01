/*
 * Find all the integral square roots of a wildcard numeric string ('_' represents any digit)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define WILDCARD	'_'

static bool matches_pattern (long, char *, char *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	char * pattern = argv[1];

	int digits = strlen (pattern);
	char * tail_ptr = pattern + digits - 1;

	int step = 0;

	switch (*tail_ptr) {
		case '0':
			step = 10;
			break;
		case '5':
			step = 5;
			break;
		case '1':
		case '2':
		case '4':
		case '6':
		case '9':
		case WILDCARD:
		default:
			step = 1;
			break;
		case '3':
		case '7':
		case '8':
			return 0;
	}

	long lower_limit = 0;
	long upper_limit = 0;

	if (pattern[0] == WILDCARD) {
		lower_limit = sqrt (pow (10, digits - 1));
		upper_limit = sqrt (pow (10, digits));
	} else {
		lower_limit = sqrt ((pattern[0] - '0') * pow (10, digits - 1));
		upper_limit = sqrt ((pattern[0] - '0' + 1) * pow (10, digits - 1));

		lower_limit /= step;
		lower_limit *= step;
	}

	for (long i = lower_limit; i <= upper_limit; i += step)
		if (matches_pattern (i * i, pattern, tail_ptr))
			printf ("%ld\n", i);

	return 0;
}

// Compares num > 0 against a wildcard pattern
static bool matches_pattern (long num, char * pattern, char * tail_ptr) {
	while (tail_ptr >= pattern) {
		if (num == 0)
			return false;

		int digit = num % 10;
		num /= 10;

		if (*tail_ptr != WILDCARD && *tail_ptr != (digit + '0'))
			return false;

		tail_ptr--;
	}

	return num == 0;
}
