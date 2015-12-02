/*
 * Find out how many unhappy numbers exist under N
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

static int next_value (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 1)
		return 1;

	int count = 0;

	int * unhappy = x_malloc (N * sizeof (int));

	for (int i = 1; i < N; i++) {
		int chain = i;

		while (true) {
			chain = next_value (chain);

			if (chain < i) {
				unhappy[i] = unhappy[chain];
				break;
			} else if (chain == 1) {
				unhappy[i] = 0;
				break;
			} else if (chain == 89) {
				unhappy[i] = 1;
				break;
			}
		}

		count += unhappy[i];
	}

	printf ("%d\n", count);

	free (unhappy);

	return 0;
}

static int next_value (int num) {
	static int squares[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
	int value = 0;

	while (num > 0) {
		value += squares[num % 10];
		num /= 10;
	}

	return value;
}
