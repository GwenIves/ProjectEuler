/*
 * Find the nominator of the largest fraction less than 3/7 among all proper fractions with denominators less than or equal to N
 */

#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

#define TARGET_NOM	3
#define TARGET_DENOM	7

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	fraction_t result = fraction_get (0, 1);

	for (int denom = 1; denom <= N; denom++) {
		int nom = (denom * TARGET_NOM - 1) / TARGET_DENOM;

		fraction_t f = fraction_get (nom, denom);

		if (fraction_cmp (&f, &result) > 0)
			result = f;
	}

	printf ("%d\n", result.nominator);

	return 0;
}
