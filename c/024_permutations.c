/*
 * Find the N-th permutation of the digits 0..9, lexicographically ordered
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap_chars (char *, int, int);
static int next_permutation (char *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	char sequence[11] = "0123456789";

	do {
		N--;

		if (N <= 0) {
			printf ("%s\n", sequence);
			break;
		}
	} while (next_permutation (sequence));

	return 0;
}

static void swap_chars (char * seq, int a, int b) {
	char t = seq[a];
	seq[a] = seq[b];
	seq[b] = t;
}

/*
 * Inplace produce the next lexicographically ordered permutation of a given sequence and return 1
 * Returns 0 and leaves the sequence unchanged when given the already largest possible sequence
 *
 * 1. Find the least significant digit to increase, the one with a less significant and larger digit
 * 2. Swap it with the smallest larger, less significant digit, thus increasing the lexicographical value as little as possible
 * 3. Reverse all the less significant digits, changing them to increasing order, thus starting to permute the tail from the lowest possible value
 */
static int next_permutation (char * seq) {
	size_t len = strlen (seq);

	int first_digit_to_increase = -1;

	for (int i = len - 1; i > 0; i--)
		if (seq[i - 1] < seq[i]) {
			first_digit_to_increase = i - 1;
			break;
		}

	if (first_digit_to_increase < 0)
		return 0;

	for (int i = len - 1; i > 0; i--)
		if (seq[i] > seq[first_digit_to_increase]) {
			swap_chars (seq, i, first_digit_to_increase);
			break;
		}

	int i = first_digit_to_increase + 1;
	int j = len - 1;

	while (i < j) {
		swap_chars (seq, i, j);
		i++;
		j--;
	}

	return 1;
}
