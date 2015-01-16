/*
 * Find how many combinatoric selections C_n,r (n above r) for 1 <= n <= N fall below 1,000,000
 */

#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"
#include "utils.h"

#define LIMIT	1000000

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	/*
	 * C_n,r = n!/r!(n - r)!
	 * We need to check when C_n,r > LIMIT ~ n!/r! > LIMIT * (n - r)!
	 * Precompute the right side of the inequality in factorials[] and the left side in cancelled_factorials[]
	 * Given that C_n,r == C_n,n-r we only need to consider r <= n /2
	 */

	bignum_t * factorials[N + 1];

	factorials[0] = bignum_get (LIMIT);

	for (size_t i = 1; i < array_len (factorials); i++)
		factorials[i] = bignum_mult (factorials[i - 1], (int) i);

	int count = 0;

	for (int n = 1; n <= N; n++) {
		bignum_t * cancelled_factorials[n + 1];

		cancelled_factorials[n] = bignum_get (1);

		for (int i = n - 1; i >= 0; i--)
			cancelled_factorials[i] = bignum_mult (cancelled_factorials[i + 1], i + 1);

		for (int r = 1; r <= n / 2 ; r++)
			if (bignum_cmp (cancelled_factorials[r], factorials[n - r]) > 0) {
				if (r + r == n)
					count++;
				else
					count += 2;
			}

		bignum_free_array (cancelled_factorials, array_len (cancelled_factorials));
	}

	bignum_free_array (factorials, array_len (factorials));

	printf ("%d\n", count);

	return 0;
}
