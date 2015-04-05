/*
 * Find the sum of all x, where for every pair of consecutive primes p1, p2, 5 <= p1 < p2 <= N,
 * x is the smallest number such that p2 divides x and the last digits of x are formed by p1
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static long find_multiple (int, int);
static int get_multiplier (int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 7)
		return 1;

	size_t primes_count = 0;
	int * primes = primes_under (NULL, N + 1, &primes_count);

	long sum = 0;

	for (size_t i = 2; i < primes_count - 1; i++)
		sum += find_multiple (primes[i], primes[i + 1]);

	printf ("%ld\n", sum);

	free (primes);

	return 0;
}

static long find_multiple (int suffix, int divisor) {
	int mult = get_multiplier (suffix, divisor);

	return (long) mult * divisor;
}

/*
 * We know the divisor and the suffix of the multiple
 * We can then find the multiplier one digit at a time
 * In each step, determine the least significant unknown digit of the multiplier
 * and subtract the corresponding amount from the suffix
 * We only want the smallest multiple, the prefix is irrelevant and is set to the
 * smallest value so that suffix is kept positive
 *
 * mult_digits[a][b] gives the number b must to be multiplied with
 * so that the least significant digit of the result is a
 *
 * The divisor is guaranteed to be prime > 5, so must end in 1, 3, 7 or 9 - only these columns
 * then need to be filled in mult_digits[][]
 */
static int get_multiplier (int suffix_in, int divisor) {
	int order = 1;

	int multiple = 0;
	long suffix = suffix_in;

	int divisor_last_digit = divisor % 10;

	while (order <= suffix_in) {
		suffix /= order;
		int suffix_digit = suffix % 10;

		int multiple_digit = mult_digits[suffix_digit][divisor_last_digit];

		multiple += multiple_digit * order;

		suffix = suffix_in - (long) multiple * divisor;

		if (suffix < 0) {
			long higher_order = 1;

			while (higher_order <= -suffix)
				higher_order *= 10;

			suffix += higher_order;
		}

		order *= 10;
	}

	return multiple;
}
