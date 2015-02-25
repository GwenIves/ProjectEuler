/*
 * Consider a sliding game played on an m x n grid filled with colored tokens and a gap.
 * At the start of the game, there is a red token in the top left corner, a gap in
 * the bottom right corner and blue tokens everywhere else. The goal of the game is
 * to move the red token to the bottom right corner
 * Find how many grids exist, such that the minimum number of moves required to solve them
 * is a prime square for some prime under N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 3)
		return 1;

	/*
	 * Consider a grid m x n, m <= n
	 * To solve the game in the minimum number of moves, we need to do the following:
	 *
	 * 1. Position the gap to the right and down of the red token - (m - 2) + (n - 2) moves
	 * 2. By repeatedly switching the token and the gap, move the red token to the bottom row
	 *    The first switch will take 5 moves, the subsequent (m - 2) switches 6
	 * 3. If the grid is not square, repeatedly move the token to the right
	 *    The first shift will take 3 moves, the subsequent (n - m - 1) shifts 5
	 *
	 * Summing these, we can derive a constant time formula for m, n:
	 * m < n: 2m + 6n - 13
	 * m = n: 2m + 6n - 11 = 8m - 11
	 *
	 * Looking at the equation for the case m = n modulo 8, we see that it will never equal a square
	 * and this case can be disregarded
	 *
	 * Note that the square must be odd in order for solutions to exist
	 * So, for each prime p, skipping 2, we have 2m + 6n - 13 = p^2, divide by 2 and set k = (p^2 + 13) / 2
	 * m + 3n = k
	 *
	 * As m < n, the limiting value for n = k / 4 and we simply count how many multiples of 3
	 * exist in the range. If k == 0 (mod 4) we need to remove the case when m == n, and if k == 3 (mod 4)
	 * there is a potential room for one more n. Finally, double the count to compensate for rotated grids
	 */

	bool * sieve = eratosthenes_sieve (N);

	long count = 0;

	for (long i = 3; i < N; i++) {
		if (!sieve[i])
			continue;

		long solutions = 0;

		long k = (i * i + 13) / 2;

		switch (k % 4) {
			case 0:
				solutions = (k / 4 - 1) / 3;
				break;
			case 3:
				solutions = (k / 4 + 1) / 3;
				break;
			default:
				solutions = (k / 4) / 3;
				break;
		}

		count += solutions + solutions;
	}

	printf ("%ld\n", count);

	free (sieve);

	return 0;
}
