/*
 * Find how many games of Nim with starting heap sizes of n, 2n, 3n, 0 < n <= 2^N
 * are non-winnable for the player making the opening move
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

	if (N < 0)
		return 1;

	/*
	 * The game of Nim can be won iff xor of the heap sizes is non-zero
	 * (for details see the proof by C. L. Bouton, also on Wikipedia)
	 *
	 * Then we are looking for all n such that n xor 2n xor 3n == 0
	 *
	 * Consider binary representations of n. Should there be a string
	 * of consecutive 1 bits in n, then there will be a carry in the sum
	 * 3n = n + 2n and the xor will necessarily be non-zero.
	 *
	 * On the other hand, without consecutive 1 bits, 2n will be shifted
	 * one bit to the left and 3n will be the sum of n + 2n with no carry.
	 * Between the three numbers, every bit position will have none or exactly one
	 * pair of 1 bits and the xor will be 0.
	 *
	 * Let the number of such binary representations with at most m bits be Nim (m)
	 * Then Nim (m) = Nim (m - 1) + Nim (m - 2), because we can take all the strings
	 * up to one bit shorter as they are and strings up to two bits shorter with
	 * "1" and enough "0"s prepended.
	 *
	 * Nim (1) = 1 and Nim (2) = 2
	 * Consequently Nim () is the Fibonacci sequence
	 */

	for (int i = 0; i < N; i++)
		next_fibonacci_num ();

	printf ("%ld\n", next_fibonacci_num ());

	return 0;
}
