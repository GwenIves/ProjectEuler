/*
 * Find M ^^ N mod MOD
 */

// FIXME: Unfortunately, this solution works only accidentaly, and has to be reworked

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

#define MOD	100000000

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <M> <N>\n", argv[0]);
		return 1;
	}

	int M = atoi (argv[1]);
	int N = atoi (argv[2]);

	if (M < 0 || N < 0)
		return 1;

	int result = 1;

	for (int i = N; i >= 1; i--)
		result = mod_pow (M, result, MOD);

	printf ("%d\n", result);

	return 0;
}
