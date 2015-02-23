/*
 * Two segment clocks are calculating a sequence of digit sums starting from primes between M and N
 * On transitions, one clock turns off an entire display, then redraws
 * The second one turns on/off individual segments as needed
 * Calculate the difference of segment switches required by the two clocks
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "euler_utils.h"

static int transition_difference (int, int);

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <M> <N>\n", argv[0]);
		return 1;
	}

	int M = atoi (argv[1]);
	int N = atoi (argv[2]);

	if (M < 0 || N < 3 || N <= M)
		return 1;

	long total_diff = 0;

	bool * sieve = eratosthenes_sieve (N);

	for (int i = M; i < N; i++) {
		if (!sieve[i])
			continue;

		int from = i;

		while (from >= 10) {
			int to = digits_sum (from);

			total_diff += transition_difference (from, to);

			from = to;
		}
	}

	printf ("%ld\n", total_diff);

	free (sieve);

	return 0;
}

#define TURNED_OFF	10

// Not generally applicable, assumes from >= to
static int transition_difference (int from, int to) {
	static const int transition_costs[11][11] = {
		{ 0, 4, 3, 3, 4, 3, 2, 2, 1, 2, 6 },
		{ 4, 0, 5, 3, 2, 5, 6, 2, 5, 4, 2 },
		{ 3, 5, 0, 2, 5, 4, 3, 5, 2, 3, 5 },
		{ 3, 3, 2, 0, 3, 2, 3, 3, 2, 1, 5 },
		{ 4, 2, 5, 3, 0, 3, 4, 2, 3, 2, 4 },
		{ 3, 5, 4, 2, 3, 0, 1, 3, 2, 1, 5 },
		{ 2, 6, 3, 3, 4, 1, 0, 4, 1, 2, 6 },
		{ 2, 2, 5, 3, 2, 3, 4, 0, 3, 2, 4 },
		{ 1, 5, 2, 2, 3, 2, 1, 3, 0, 1, 7 },
		{ 2, 4, 3, 1, 2, 1, 2, 2, 1, 0, 6 },
		{ 6, 2, 5, 5, 4, 5, 6, 4, 7, 6, 0 }
	};

	int clock_a = 0;
	int clock_b = 0;

	while (to > 0) {
		int from_digit = from % 10;
		int to_digit = to % 10;

		from /= 10;
		to /= 10;

		clock_a += transition_costs[from_digit][TURNED_OFF];
		clock_a += transition_costs[TURNED_OFF][to_digit];

		clock_b += transition_costs[from_digit][to_digit];
	}

	return clock_a - clock_b;
}
