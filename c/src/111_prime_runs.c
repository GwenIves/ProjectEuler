/*
 * Find the sum of all N-digit primes with maximal runs of any digit
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

static long get_run_sum (char, size_t, int, int *, size_t);
static void fill_candidate (char *, char, size_t, int *, size_t);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	size_t primes_count = 0;
	int * primes = primes_under (NULL, sqrt (power (10, N)) + 1, &primes_count);

	long sum = 0;

	for (char run_digit = '0'; run_digit <= '9'; run_digit++)
		for (int run_len = N; run_len >= 1; run_len--) {
			long run_sum = get_run_sum (run_digit, run_len, N, primes, primes_count);

			if (run_sum > 0) {
				sum += run_sum;
				break;
			}
		}

	free (primes);

	printf ("%ld\n", sum);

	return 0;
}

static long get_run_sum (char run_digit, size_t run_len, int N, int * primes, size_t primes_count) {
	long sum = 0;

	char candidate[N + 1];
	candidate[N] = '\0';

	size_t rest_len = N - run_len;

	int rest_digits[rest_len];

	for (size_t i = 0; i < rest_len; i++)
		rest_digits[i] = 0;

	do {
		fill_candidate (candidate, run_digit, run_len, rest_digits, rest_len);

		do {
			if (candidate[0] == '0')
				continue;

			long candidate_num = atol (candidate);

			if (is_prime_long (candidate_num, NULL, 0, primes, primes_count))
				sum += candidate_num;
		} while (next_permutation (candidate));
	} while (next_number_non_decreasing (rest_digits, rest_len, 10));

	return sum;
}

static void fill_candidate (char * candidate, char run_digit, size_t run_len, int * rest_digits, size_t rest_len) {
	size_t i = 0;
	size_t j = 0;

	int run_val = run_digit - '0';

	while (i < rest_len && rest_digits[i] <= run_val)
		candidate[j++] = rest_digits[i++] + '0';

	for (size_t k = 0; k < run_len; k++)
		candidate[j++] = run_digit;

	while (i < rest_len)
		candidate[j++] = rest_digits[i++] + '0';
}
