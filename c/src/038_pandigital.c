/*
 * Find the largest N-digit pandigital concatenation of all products of an integer with consecutive integers 1..M, where M > 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	char digits[DIGITS_COUNT];
	char concat[DIGITS_COUNT];

	int upper_limit = pow (10, N / 2 + 1);

	int max = 0;

	for (int i = 1; i <= upper_limit; i++) {
		memset (digits, 0, DIGITS_COUNT);
		concat[0] = '\0';

		int mult = 1;

		while (true) {
			int result = i * mult;

			if (!pandigital_test_and_set_digits (digits, result))
				break;
			else {
				char new_digits[DIGITS_COUNT];
				sprintf (new_digits, "%d", result);
				strcat (concat, new_digits);
			}

			if (pandigital_test_digits (digits, N)) {
				int new_val = atoi (concat);

				if (new_val > max && mult > 1)
					max = new_val;

				break;
			}

			mult++;
		}
	}

	printf ("%d\n", max);

	return 0;
}
