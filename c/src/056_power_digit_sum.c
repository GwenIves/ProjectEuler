/*
 * Find the maximum of digit sums in the powers a^b for 0 < a,b < N
 */

#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	int max_digits_sum = 0;

	for (int a = 1; a < N; a++) {
		bignum_t * power = bignum_get (1);

		for (int b = 1; b <= N; b++) {
			bignum_t * new_power = bignum_mult (power, a);

			int sum = bignum_digits_sum (new_power);

			if (sum > max_digits_sum)
				max_digits_sum = sum;

			bignum_delete (power);
			power = new_power;
		}
	}

	printf ("%d\n", max_digits_sum);

	return 0;
}
