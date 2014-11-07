/*
 * Find the largest product of N consecutive digits in a numeric series read from stdin
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	char * series = NULL;
	ssize_t series_size = x_getline (&series, stdin); 

	if (series_size == -1)
		return 1;

	unsigned long prev_product = 0;
	unsigned long max_product = 0;

	for (size_t i = 0; i <= series_size - N; i++) {
		unsigned long product = 0;

		if (i == 0 || series[i - 1] == '0') {
			for (size_t j = 0; j < N; j++) {
				int digit = series[i + j] - '0';

				if (j == 0)
					product = digit;
				else
					product *= digit;
			}
		} else {
			int left_digit = series[i - 1] - '0';
			int right_digit = series[i + N - 1] - '0';

			product = prev_product / left_digit * right_digit;
		}

		if (product > max_product)
			max_product = product;

		prev_product = product;
	}

	printf ("%lu\n", max_product);

	free (series);

	return 0;
}
