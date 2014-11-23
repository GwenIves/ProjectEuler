/*
 * Find the number of combinations of representing N as a sum of at least two numbers
 */

#include <stdio.h>
#include <stdlib.h>
#include "euler_utils.h"
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int values[N - 1];

	for (int i = 0; i < array_len (values); i++)
		values[i] = i + 1;

	printf ("%d\n", count_representation_combinations (values, array_len (values) - 1, N, NULL));

	return 0;
}
