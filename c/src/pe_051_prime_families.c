/*
 * Find the smallest prime that is a member of a prime family of size N, produced by replacing a portion of the number with the same digit
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static int primes_family_size (const bool *, int, size_t);
static int replace_digits (const char *, const char *, int);
static void fill_digit_mask (char *, size_t, size_t);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0 || N > DIGITS_COUNT)
		return 1;

	int limit = 1000;

	int prime = 2;
	size_t prime_digits = 1;
	int next_digit_at = 10;

	while (true) {
		bool * primes = eratosthenes_sieve (limit);

		while (prime < limit) {
			if (primes[prime] && (N == primes_family_size (primes, prime, prime_digits))) {
				printf ("%d\n", prime);

				free (primes);
				return 0;
			}

			if (++prime == next_digit_at) {
				prime_digits++;
				next_digit_at *= 10;
			}
		}

		limit *= 10;
		free (primes);
	}

	return 0;
}

static int primes_family_size (const bool * primes, int prime, size_t prime_digits) {
	char prime_str[prime_digits + 1];
	sprintf (prime_str, "%d", prime);

	int max_size = 0;

	for (size_t digits_to_mask = 1; digits_to_mask <= prime_digits; digits_to_mask++) {
		char digit_mask[prime_digits + 1];

		fill_digit_mask (digit_mask, prime_digits, digits_to_mask);

		do {
			int family_size = 0;
			bool generating_prime_member = false;

			for (int digit = 0; digit < DIGITS_COUNT; digit++) {
				if (digit == 0 && digit_mask[0] == '1')
					continue;

				int generated_num = replace_digits (prime_str, digit_mask, digit);

				if (primes[generated_num]) {
					family_size++;

					if (generated_num == prime)
						generating_prime_member = true;
				}
			}

			if (family_size > max_size && generating_prime_member)
				max_size = family_size;
		} while (prev_permutation (digit_mask));
	}

	return max_size;
}

static void fill_digit_mask (char * mask, size_t size, size_t masked_size) {
	for (size_t i = 0; i < size; i++)
		if (i < masked_size)
			mask[i] = '1';
		else
			mask[i] = '0';

	mask[size] = '\0';
}

static int replace_digits (const char * digits, const char * mask, int replacement) {
	int result = 0;

	for (size_t i = 0; digits[i] != '\0'; i++) {
		result *= 10;

		if (mask[i] == '1')
			result += replacement;
		else
			result += digits[i] - '0';
	}

	return result;
}
