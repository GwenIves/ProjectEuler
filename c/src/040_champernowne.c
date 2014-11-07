/*
 * Find the product of the digits in the Champernowne's constant's fractional part falling on the first N power of 10 numbered indexes
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 0)
		return 1;

	int num = 1;
	int num_digits = 1;
	int next_digit_at = 10;

	int index = 0;
	int next_index_at = 1;
	int indices_found = 0;

	int product = 1;

	while (indices_found < N) {
		index += num_digits;

		if (index >= next_index_at) {
			int num_containing_index = num;

			for (int i = index; i > next_index_at; i--)
				num_containing_index /= 10;

			product *= num_containing_index % 10;
			indices_found++;

			next_index_at *= 10;
		}


		if (++num == next_digit_at) {
			num_digits++;
			next_digit_at *= 10;
		}
	}

	printf  ("%d\n", product);

	return 0;
}
