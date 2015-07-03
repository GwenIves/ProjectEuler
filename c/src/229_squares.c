/*
 * Find how many numbers n, n < N can be represented as sums:
 *   a^2 + b^2
 *   c^2 + 2 * d^2
 *   e^2 + 3 * f^2
 *   g^2 + 7 * h^2
 * for some integers a, b, c, d, e, f, g, h
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

#define	REP1		1
#define	REP2		2
#define	REP3		4
#define	REP4		8
#define	ALL_REPS	15

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

	int limit_i = sqrt (N);

	unsigned char * squares = x_calloc (N, 1);

	for (int i = 1; i <= limit_i; i++) {
		int i2 = i * i;
		int rem = N - 1 - i2;

		int j = 1;
		int limit_j = sqrt (rem / 7);

		for (; j <= limit_j; j++) {
			int j2 = j * j;

			squares[i2 + j2] |= REP1;
			squares[i2 + 2 * j2] |= REP2;
			squares[i2 + 3 * j2] |= REP3;
			squares[i2 + 7 * j2] |= REP4;
		}

		limit_j = sqrt (rem / 3);

		for (; j <= limit_j; j++) {
			int j2 = j * j;

			squares[i2 + j2] |= REP1;
			squares[i2 + 2 * j2] |= REP2;
			squares[i2 + 3 * j2] |= REP3;
		}

		limit_j = sqrt (rem / 2);

		for (; j <= limit_j; j++) {
			int j2 = j * j;

			squares[i2 + j2] |= REP1;
			squares[i2 + 2 * j2] |= REP2;
		}

		limit_j = sqrt (rem);

		for (; j <= limit_j; j++) {
			int j2 = j * j;

			squares[i2 + j2] |= REP1;
		}
	}

	int count = 0;

	for (int i = 1; i < N; i++)
		if (squares[i] == ALL_REPS)
			count++;

	printf ("%d\n", count);

	free (squares);

	return 0;
}
