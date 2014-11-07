/*
 * Find the sum of all numbers under N that are palindromes both in base 10 and base 2
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	unsigned long sum = 0;

	for (int i = 1; i < N; i++)
		if (is_palindrome (i, 10) && is_palindrome (i, 2))
			sum += i;

	printf ("%lu\n", sum);

	return 0;
}
