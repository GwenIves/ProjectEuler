/*
 * Find the sum of all multiples of 3 and 5 less than N
 */

#include <stdio.h>
#include <stdlib.h>

static unsigned long sum_of_multiples (int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 0) {
		printf ("0\n");
		return 0;
	}

	unsigned long sum3 = sum_of_multiples (3, N);
	unsigned long sum5 = sum_of_multiples (5, N);
	unsigned long sum15 = sum_of_multiples (15, N);

	printf ("%lu\n", sum3 + sum5 - sum15);

	return 0;
}

static unsigned long sum_of_multiples (int mult, int less_than) {
	int multiples_count = (less_than - 1) / mult;
	unsigned long series_sum = (1 + multiples_count) * multiples_count / 2; 
	
	return mult * series_sum;
}
