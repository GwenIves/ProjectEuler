/*
 * Find how many hexadecimal numbers up to N digits long exist that contain 0, 1 and A at least once
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

	if (N < 1)
		return 1;

	long count = 0;

	/*
	 * For each length, fix the leading digit
	 * Then count all possible suffixes and subtract numbers that do not contain any one of the required digits
	 * Lastly, we need to compensate for multiple countings of numbers without any pairs and triples of the required digits
	 */

	for (int length = 3; length <= N; length++) {
		// Leading 1 or A
		count += 2 * (power (16, length - 1) - 2 * power (15, length - 1) + power (14, length - 1));

		// Any leading digit except 0, 1 or A
		if (length > 3)
			count += 13 * (power (16, length - 1) - 3 * power (15, length - 1) + 3 * power (14, length - 1) - power (13, length - 1));
	}

	printf ("%lX\n", count);

	return 0;
}
