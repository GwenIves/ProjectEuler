/*
 * Find how many N-digit numbers exist such that no 3 consecutive digits have a sum greater than 9
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math_utils.h"
#include "euler_utils.h"

#define CONTROL_DIGITS	3
#define CONTROL_SUM	9

static long count_numbers (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	printf ("%ld\n", count_numbers (N));

	return 0;
}

/*
 * The array counts[seq] holds the number of possible numbers ending with the
 * sequence seq. It is initialized setting all allowed sequences (skipping leading zeros)
 * to 1 and then built by dynamic programming sequentially for each remaining digit.
 *
 * We only keep two copies of the array (current and new), swapping them at each pass
 * rather then create a new copy each time
 */
static long count_numbers (int digits) {
	int mod = power (10, CONTROL_DIGITS - 1);
	int min_seq = power (10, MIN (CONTROL_DIGITS, digits) - 1);
	int max_seq = min_seq * 10 - 1;

	int current = 0;
	int new = 1;

	long counts[2][max_seq + 1];

	memset (counts[current], 0, (max_seq + 1) * sizeof (counts[0][0]));
	memset (counts[new], 0, (max_seq + 1) * sizeof (counts[0][0]));

	for (int i = min_seq; i <= max_seq; i++)
		if (digits_sum (i) <= CONTROL_SUM)
			counts[current][i] = 1;

	for (int i = CONTROL_DIGITS + 1; i <= digits; i++) {
		long * c = counts[current];
		long * n = counts[new];

		current = (current + 1) % 2;
		new = (new + 1) % 2;

		memset (n, 0, (max_seq + 1) * sizeof (counts[0][0]));

		for (int seq = 0; seq <= max_seq; seq++) {
			int prefix = seq % mod;
			int prefix_sum = digits_sum (prefix);

			for (int new_digit = 0; new_digit <= 9 - prefix_sum; new_digit++) {
				int new_seq = prefix * 10 + new_digit;

				n[new_seq] += c[seq];
			}
		}
	}

	long count = 0;

	for (int seq = 0; seq <= max_seq; seq++)
		count += counts[current][seq];

	return count;
}
