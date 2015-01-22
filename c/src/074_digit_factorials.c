/*
 * Find how many chains of "number -> sum of its digits' factorials" starting under N have a length of 60
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"
#include "math_utils.h"

#define CHAIN_LENGTH	60

static bool is_a_cycle (const int *, size_t, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 1)
		return 1;

	int count = 0;

	int * past_values = x_malloc (sizeof (int));
	int * chain_lengths = x_malloc (N * sizeof (int));

	size_t allocated = 1;
	size_t used = 0;

	for (int i = 1; i < N; i++) {
		int value = i;

		used = 0;

		while (value >= i && !is_a_cycle (past_values, used, value)) {
			if (used >= allocated) {
				allocated *= 2;
				past_values = x_realloc (past_values, allocated * sizeof (int));
			}

			past_values[used++] = value;
			value = next_digits_factorial_num (value);
		}

		if (value < i)
			used += chain_lengths[value];

		chain_lengths[i] = used;

		if (used == CHAIN_LENGTH)
			count++;
	}

	printf ("%d\n", count);

	free (past_values);
	free (chain_lengths);

	return 0;
}

static bool is_a_cycle (const int * past_values, size_t count, int value) {
	for (size_t i = 0; i < count; i++)
		if (past_values[i] == value)
			return true;

	return false;
}
