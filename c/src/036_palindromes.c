/*
 * Find the sum of all numbers under N that are palindromes both in base 10 and base 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

static void sum_two_base_palindromes (int *, int, int, bool);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int sum = 0;

	int upper_limit = power (10, (int) log10 (N) / 2);

	for (int seed = 1; seed < upper_limit; seed++) {
		sum_two_base_palindromes (&sum, N, seed, true);
		sum_two_base_palindromes (&sum, N, seed, false);
	}

	printf ("%d\n", sum);

	return 0;
}

static void sum_two_base_palindromes (int * sum, int under, int seed, bool odd_len) {
	int palindrome10 = make_palindrome (seed, 10, odd_len);

	if (palindrome10 >= under)
		return;

	// Even numbers cannot be binary palindromes
	if (palindrome10 % 2 == 0)
		return;

	if (is_palindrome (palindrome10, 2))
		*sum += palindrome10;
}
