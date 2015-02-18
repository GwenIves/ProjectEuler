/*
 * Find how many ways a row of N tiles can be filled using blocks of size 1, 2, 3 and 4
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

#define MAX_BLOCK	4

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	long combinations = 0;

	int block_counts[MAX_BLOCK] = {0};

	do {
		int larger_blocks_total_size = 0;

		for (size_t i = 1; i < MAX_BLOCK; i++)
			larger_blocks_total_size += (i + 1) * block_counts[i];

		if (larger_blocks_total_size > N)
			continue;
		else
			block_counts[0] = N - larger_blocks_total_size;

		combinations += permutations_count (block_counts, MAX_BLOCK);
	} while (next_number (block_counts + 1, MAX_BLOCK - 1, N / 2 + 1));

	printf ("%ld\n", combinations);

	return 0;
}
