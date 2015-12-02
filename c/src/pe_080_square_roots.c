/*
 * Find the sum of the first 100 digits in the irrational square roots of the first N integers
 */

#include <stdio.h>
#include <stdlib.h>
#include "euler_utils.h"

#define DIGITS	100

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	int integral_sqrt = 1;

	int digits_sum = 0;

	for (int n = 1; n <= N; n++) {
		if (n == integral_sqrt * integral_sqrt) {
			integral_sqrt++;
			continue;
		}

		char * sqrt_str = calculate_sqrt (n, DIGITS);

		for (char * d_ptr = sqrt_str; *d_ptr; d_ptr++)
			if (*d_ptr != '.')
				digits_sum += *d_ptr - '0';

		free (sqrt_str);
	}

	printf ("%d\n", digits_sum);

	return 0;
}
