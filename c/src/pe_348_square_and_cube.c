/*
 * Find the sum of the first N palindromes that can be represented
 * as a sum of a square and a cube in exactly M ways
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static int next_palindrome (void);

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <M> <N>\n", argv[0]);
		return 1;
	}

	int M = atoi (argv[1]);
	int N = atoi (argv[2]);

	if (N < 1 || M < 1)
		return 1;

	int sum = 0;
	int count = 0;

	while (true) {
		int palindrome = next_palindrome ();

		int ways_to_represent = 0;

		for (int i = 1;; i++) {
			int i3 = i * i * i;

			if (i3 > palindrome)
				break;

			if (integer_sqrt (palindrome - i3) != -1)
				ways_to_represent++;
		}

		if (ways_to_represent == M) {
			sum += palindrome;

			if (++count == N)
				break;
		}
	}

	printf ("%d\n", sum);

	return 0;
}

static int next_palindrome (void) {
	static int seed = 1;
	static int next_order = 10;
	static bool odd = true;

	if (seed == next_order) {
		if (odd) {
			seed = next_order / 10;
			odd = false;
		} else {
			odd = true;
			next_order *= 10;
		}
	}

	return make_palindrome (seed++, 10, odd);
}
