/*
 * Find the smallest positive number that can be divided into piles in x number of ways such that N divides x
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "math_utils.h"
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	long modulo = 1;

	while (N > modulo)
		modulo *= 10;

	int allocated = 1;
	long * partitions = x_malloc (allocated * sizeof (long));

	partitions[0] = 1;

	/*
	 * Using the Euler's recurrence formula for the partition function p(x)
	 * p(x) = p(x - 1) + p(x - 2) - p(x - 5) - p(x - 7) + ...
	 * where the constants in the subtractions are generalised pentagonal numbers
	 */

	int num = 1;

	while (true) {
		if (num >= allocated) {
			allocated *= 10;
			partitions = x_realloc (partitions, allocated * sizeof (long));
		}

		partitions[num] = 0;

		int pentagonal_index = 0;
		int index_count = 0;

		next_generalised_pentagonal_num (true);

		while ((pentagonal_index = next_generalised_pentagonal_num (false)) <= num) {
			index_count++;

			if (index_count % 4 == 1 || index_count % 4 == 2)
				partitions[num] += partitions[num - pentagonal_index];
			else
				partitions[num] -= partitions[num - pentagonal_index];

			partitions[num] %= modulo;
		}

		if (partitions[num] % N == 0) {
			printf ("%d\n", num);
			break;
		}

		num++;
	}

	free (partitions);

	return 0;
}
