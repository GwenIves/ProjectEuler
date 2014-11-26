/*
 * Find the largest palindrome product of two N-digit numbers
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

	if (N < 1)
		return 1;

	int start = pow (10, N - 1);
	int stop = pow (10, N) - 1;
	int max_product = 0;

	for (int i = start; i <= stop; i++)
		for (int j = i; j <= stop; j++) {
			int product = i * j;

			if (product > max_product && is_palindrome (product, 10))
				max_product = product;
		}

	printf ("%d\n", max_product);

	return 0;
}
