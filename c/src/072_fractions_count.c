/*
 * Find how many reduced proper fractions a/b exist for b less than or equal to N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	// For each denominator there is exactly Totient (denominator) reduced proper fractions
	int * totients = get_totients_under (N + 1);

	long count = 0;

	for (int i = 2; i <= N; i++)
		count += totients[i];

	printf ("%ld\n", count);

	free (totients);

	return 0;
}
