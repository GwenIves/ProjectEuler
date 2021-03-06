/*
 * Find the number of distinct powers a^b for all a, b between 2 and N inclusive
 */

#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 2)
		return 1;

	bignum_t * powers[(N - 1) * (N - 1)];
	size_t powers_count = 0;

	bool * primes = eratosthenes_sieve (N + 1);

	for (int a = 2; a <= N; a++) {
		bignum_t * power = NULL;

		for (int b = 2; b <= N; b++) {
			bignum_t * new_power = NULL;

			if (!power)
				new_power = bignum_get (a * a);
			else
				new_power = bignum_mult (power, a);

			if (b == 2)
				bignum_delete (power);

			int duplicate_at = -1;

			// Powers of a prime base cannot be duplicates
			if (!primes[a])
				for (size_t i = 0; i < powers_count; i++)
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
	}

	printf ("%d\n", (int) powers_count);

	bignum_free_array (powers, powers_count);
	free (primes);

	return 0;
}
