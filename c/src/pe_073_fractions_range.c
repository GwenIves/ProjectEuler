/*
 * Find how many reduced proper fractions with denominators less than or equal to N lie between 1/3 and 1/2
 */

#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"
#include "euler_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	fraction_t above = fraction_get (1, 3);
	fraction_t below = fraction_get (1, 2);

	printf ("%ld\n", stern_brocot_count (N, &above, &below));

	return 0;
}
