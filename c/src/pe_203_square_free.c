/*
 * Find the sum of all distinct square-free numbers in the first N rows of the Pascal's triangle
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "math_utils.h"
#include "hash_table.h"
#include "utils.h"

static bool is_square_free (long, const int *, size_t);
static int * get_prime_squares (int, size_t *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	size_t primes_count = 0;
	int * prime_squares = get_prime_squares (N, &primes_count);

	hash_table_t * square_frees = hash_table_create (1000);

	long current_row[N];
	long prev_row[N];

	prev_row[0] = 0;

	long sum = 0;

	for (int i = 0; i < N; i++) {
		current_row[0] = 1;
		current_row[i] = 1;

		for (int j = 1; j < i; j++)
			current_row[j] = prev_row[j - 1] + prev_row[j];

		memcpy (prev_row, current_row, (i + 1) * sizeof (long));

		for (int j = 0; j <= i / 2; j++) {
			long value = current_row[j];

			if (is_square_free (value, prime_squares, primes_count)) {
				if (hash_table_insert (square_frees, value, copy_int (value)))
					sum += value;
			}
		}
	}

	printf ("%ld\n", sum);

	hash_table_free (square_frees);
	free (prime_squares);

	return 0;
}

static bool is_square_free (long num, const int * squares, size_t squares_count) {
	for (size_t i = 0; i < squares_count; i++)
		if (squares[i] > num)
			break;
		else if (num % squares[i] == 0)
			return false;

	return true;
}

static int * get_prime_squares (int max_triangle_row, size_t * count) {
	// The largest number on the N-th row is C_N,k = N! / (k! * (N - k)!)
	// It cannot have a divisor above N
	int limit = MAX (2, sqrt (max_triangle_row));

	int * prime_squares = primes_under (NULL, limit + 1, count);

	for (size_t i = 0; i < *count; i++)
		prime_squares[i] *= prime_squares[i];

	return prime_squares;
}
