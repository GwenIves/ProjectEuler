/*
 * Find the prize fund size for a game of chance played by drawing colored discs
 * out of a bag for N turns. A player wins if at the end of the game he has
 * drawn more blue discs than red ones. Discs are returned to the bag after
 * being drawn. At the start of the game, there is one red and one blue disc
 * in the bag, and one new red disc is added after each turn.
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

	if (N < 1)
		return 1;

	/*
	 * Find the probability of winning
	 * On turn t, there will be 1 blue disc and t red discs
	 * Permute over all winning draw-sequences and sum their probabilities
	 */
	long nominator = 0;
	long denominator = factorial (N + 1);

	for (int blue_discs = N / 2 + 1; blue_discs <= N; blue_discs++) {
		char drawn_on_turn[N + 1];
		drawn_on_turn[N] = '\0';

		for (int turn = 0; turn < N; turn++)
			if (turn < blue_discs)
				drawn_on_turn[turn] = '1';
			else
				drawn_on_turn[turn] = '0';

		do {
			long nom = 1;

			for (int turn = 0; turn < N; turn++) {
				int red_discs = turn + 1;

				if (drawn_on_turn[turn] == '0')
					nom *= red_discs;
			}

			nominator += nom;
		} while (prev_permutation (drawn_on_turn));
	}

	printf ("%ld\n", denominator / nominator);

	return 0;
}
