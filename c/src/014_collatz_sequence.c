/*
 * Find the starting number under N that produces the longest Collatz sequence
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 1)
		return 1;

	int * lengths = x_malloc (N * sizeof (int));;

	int starting_num = 1;
	int max_length = 0;

	lengths[1] = 1;

	for (int i = 2; i < N; i++) {
		int steps = 0;
		long next = i;

		while (next >= i) {
			steps++;
			next = next_collatz_num (next);
		}

		lengths[i] = steps + lengths[next];

		if (lengths[i] > max_length) {
			starting_num = i;
			max_length = lengths[i];
		}
	}

	printf ("%d\n", starting_num);

	free (lengths);

	return 0;
}
