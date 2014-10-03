/*
 * Find the difference between the sum of the squares of the first N natural numbers and the square of the sum
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	unsigned long sum_of_squares = 0;
	unsigned long square_of_sum = 0;

	for (int i = 1; i <= N; i++) {
		sum_of_squares += i * i;
		square_of_sum += i;
	}

	square_of_sum *= square_of_sum;

	printf ("%lu\n", square_of_sum - sum_of_squares);

	return 0;
}
