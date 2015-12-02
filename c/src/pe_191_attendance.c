/*
 * Consider ternary attendance strings of digits A (absent), L (late) and O (on-time)
 * Find how many such strings of length N exist such that the person wasn't absent
 * for more than 3 consecutive days or late more than once
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

	long count = 0;

	/*
	 * Consider first how many binary strings of A and O exist with at most 2 consecutive A
	 * When constructing a string of length n, we can:
	 *    Take a string of length n - 1 and append O
	 *    Take a string of length n - 2 and append OA
	 *    Take a string of length n - 3 and append OAA
	 * Given that there are 2/4/7 valid strings of length 1/2/3, the count is the Tribonacci sequence
	 *
	 * Then we simply consider one string with no late attendence and all pairs of shorter strings
	 * separated by exactly one late attendance
	 */

	count += tribonacci_num (N);

	for (int late_day = 1; late_day <= N; late_day++)
		count += tribonacci_num (N - late_day) * tribonacci_num (late_day - 1);

	printf ("%ld\n", count);

	return 0;
}
