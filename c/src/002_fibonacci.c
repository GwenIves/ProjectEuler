/*
 * Find the sum of all even Fibonacci numbers not exceeding N
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	long N = atol (argv[1]);

	long sum = 0;

	while (true) {
		long fib = next_fibonacci_num ();

		if (fib > N)
			break;

		if (fib % 2 == 0)
			sum += fib;
	}

	printf ("%ld\n", sum);

	return 0;
}
