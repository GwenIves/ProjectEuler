/*
 * Find how many N-pandigital prime sets exist
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

#define count_sets_of_size(d,dl,set_size,s,sz) count_sets_of_size_ (d, dl, set_size, 0, s, sz)

static int count_sets (int);
static int count_sets_of_size_ (const char *, int, int, int, const bool *, int);

#define MAX_SIEVE_SIZE	10000000

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1 || N > 9)
		return 1;

	printf ("%d\n", count_sets (N));

	return 0;
}

static int count_sets (int N) {
	int count = 0;

	char digits[N + 1];

	for (int i = 0; i < N; i++)
		digits[i] = i + 1;

	digits[N] = '\0';

	// Above MAX_SIEVE_SIZE, the sieve's creation is too expensive, primeness determined by Miller-Rabin
	int sieve_size = MIN (MAX_SIEVE_SIZE, power (10, N));
	bool * sieve = eratosthenes_sieve (sieve_size);

	do {
		char last_digit = digits[N - 1];

		// The last number could not possibly be a prime
		if (last_digit == 2 || last_digit == 4 || last_digit == 6 || last_digit == 8)
			continue;

		for (int set_size = 1; set_size <= N; set_size++)
			count += count_sets_of_size (digits, N, set_size, sieve, sieve_size);
	} while (next_permutation (digits));

	free (sieve);

	return count;
}

static int count_sets_of_size_ (const char * digits, int digits_len, int set_size, int prev_member, const bool * sieve, int sieve_size) {
	int set_member = 0;

	if (set_size > 1) {
		int count = 0;

		for (int len = 1; len <= digits_len - set_size + 1; len++) {

			set_member *= 10;
			set_member += digits[len - 1];

			// Accept the set only in ascending order to avoid duplicates
			if (set_member < prev_member)
				continue;

			if (!is_prime_long (set_member, sieve, sieve_size, NULL, 0))
				continue;

			count += count_sets_of_size_ (digits + len, digits_len - len, set_size - 1, set_member, sieve, sieve_size);
		}

		return count;
	} else {
		for (int i = 0; i < digits_len; i++) {
			set_member *= 10;
			set_member += digits[i];
		}

		if (set_member < prev_member)
			return 0;

		if (!is_prime_long (set_member, sieve, sieve_size, NULL, 0))
			return 0;

		return 1;
	}
}
