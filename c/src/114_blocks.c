/*
 * Find how many ways a row of size N can be filled using blocks of a minimum size 3
 * such that no two blocks are next to each other
 */

#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE	3

static long count_arrangements (int);
static long count_arrangements_aux (int, long *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	printf ("%ld\n", count_arrangements (N));

	return 0;
}

static long count_arrangements (int size) {
	long cache[size + 2];

	for (int i = 0; i < size + 2; i++)
		cache[i] = -1;

	return count_arrangements_aux (size + 1, cache);
}

/*
 * We are going to calculate the count recursively noting that:
 *   Rows shorter than MIN_SIZE can only be filled in one way - all gaps
 *   Longer rows can be formed by either appending a gap or a block of
 *   any size plus a gap to a shorter row
 * The algorithm will place one unnecessary gap in the last step, so
 * the size passed to the initial call should be one above the required size
 */
static long count_arrangements_aux (int size, long * cache) {
	if (size < MIN_SIZE)
		return 1;
	else if (cache[size] != -1)
		return cache[size];
	else {
		long count = count_arrangements_aux (size - 1, cache);

		for (int block_size = MIN_SIZE + 1; block_size <= size; block_size++)
			count += count_arrangements_aux (size - block_size, cache);

		cache[size] = count;

		return count;
	}
}
