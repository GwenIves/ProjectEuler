/*
 * Consider an alphabet of N characters and let p(n) be the number of strings
 * from the alphabet of length n, n <= N, such that no character occurs more than
 * once and exactly one character appears lexicographically after the character to
 * its left.
 * Find the maximum of p(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static long get_moves_count (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	long maximum = 0;

	/*
	 * For a string of length n, choose an alphabet and then find all conforming strings this way:
	 *  1. Start with a string sorted in descending order
	 *  2. Consider all 1 to (n - 1) tuples of characters from the string
	 *  3. Concatenate them and move them to any position to the left of the first character in the tuple
	 * Now there is exactly one pair of consecutive characters occuring in asceding order: the last
	 * character of the moved tuple and the character after it
	 */

	for (int length = 2; length <= N; length++) {
		long alphabet_choices = binomial_coefficient2 (N, length);
		long moves = get_moves_count (length);

		long strings_count = alphabet_choices * moves;

		if (strings_count > maximum)
			maximum = strings_count;
	}

	printf ("%ld\n", maximum);

	return 0;
}

static long get_moves_count (int size) {
	long moves = 0;

	for (int move_size = 1; move_size < size; move_size++)
		for (int position = 1; position <= size - move_size; position++)
			moves += binomial_coefficient2 (size - position, move_size);

	return moves;
}
