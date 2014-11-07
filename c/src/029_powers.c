/*
 * Find the number of distinct powers a^b for all a, b between 2 and N inclusive
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "bignum.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 2)
		return 1;

	bignum_t ** powers = x_malloc ((N - 1) * (N - 1) * sizeof (bignum_t *));
	int powers_count = 0;

	for (int a = 2; a <= N; a++) {
		bignum_t * power = NULL;
		bignum_t * base = bignum_get (a);

		for (int b = 2; b <= N; b++) {
			bignum_t * new_power = NULL;
			
			if (power)
				new_power = bignum_mult (power, base);
			else
				new_power = bignum_mult (base, base);

			int duplicate_at = -1;

			for (int i = 0; i < powers_count; i++)
				if (bignum_cmp (powers[i], new_power) == 0) {
					duplicate_at = i;
					break;
				}

			if (duplicate_at == -1) {
				powers[powers_count++] = new_power;
				power = new_power;
			} else {
				bignum_delete (new_power);
				power = powers[duplicate_at];
			}
		}

		bignum_delete (base);
	}

	printf ("%d\n", powers_count);

	for (int i = 0; i < powers_count; i++)
		bignum_delete (powers[i]);

	return 0;
}
