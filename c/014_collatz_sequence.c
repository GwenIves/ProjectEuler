/*
 * Find the starting number under N that produces the longest Collatz sequence
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static unsigned long collatz (unsigned long);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	int * lengths = x_malloc (N * sizeof (int));

	int starting_num = 0;
	int max_length = 0;

	lengths[1] = 1;

	for (int i = 2; i < N; i++) {
		int steps = 0;
		unsigned long next = i;

		while (next >= i) {
			steps++;
			next = collatz (next);
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

static unsigned long collatz (unsigned long x) {
	if (x % 2 == 0)
		return x / 2;
	else
		return x * 3 + 1;
}
