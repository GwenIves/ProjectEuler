/*
 * Find how many ways a row of N tiles can be filled using blocks of size 1, 2, 3 and 4
 * Sizes larger than 1 cannot be mixed
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

	for (int block_size = 2; block_size <= MAX_BLOCK; block_size++)
		for (int block_count = 1; block_count <= N / block_size; block_count++) {
			int blocks_of_size_one = N - block_size * block_count;

			int block_counts[] = {block_count, blocks_of_size_one};

			combinations += permutations_count (block_counts, 2);
		}

	printf ("%ld\n", combinations);

	return 0;
}
