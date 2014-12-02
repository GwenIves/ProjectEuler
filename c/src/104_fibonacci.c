/*
 * Find the first term in the Fibonacci series whose first and last N digits are 1 to N pandigital
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1 || N > 9)
		return 1;
	else if (N == 1) {
		printf ("1\n");
		return 0;
	}

	long mod = power (10, N);
	double log_sqrt_5 = log10 (sqrt (5));

	int term = 1;

	long fib1 = 1;
	long fib2 = 0;

	while (true) {
		long fib_tail = (fib1 + fib2) % mod;
		term++;

		fib2 = fib1;
		fib1 = fib_tail;

		if (!is_pandigital (fib_tail, N))
			continue;

		/*
		 * Use the closed-form expression for the Fibonacci series terms
		 * F(n) = (Golden ratio^n - Golden ratio conjugate^n) / sqrt (5)
		 * The conjugate powers decrease rapidly and can be safely ignored
		 * even for n == 8 which is the first term with a pandigital tail (N == 2)
		 *
		 * We can then take the logarithm of the closed-form expression
		 * to find the first N digits of F(n)
		 */

		double log_fib = log10 (GOLDEN_RATIO) * term - log_sqrt_5;

		log_fib -= (long) log_fib;
		log_fib += N - 1;

		long fib_head = pow (10, log_fib);

		if (is_pandigital (fib_head, N))
			break;
	}

	printf ("%d\n", term);

	return 0;
}
