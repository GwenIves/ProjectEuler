/*
 * Find the sum of all even Fibonacci numbers not exceeding N
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	long N = atol (argv[1]);

	long sum = 0;
	long fib1 = 1;
	long fib2 = 1;

	while (1) {
		long fib = fib1 + fib2;

		if (fib > N)
			break;

		if (fib % 2 == 0)
			sum += fib;

		fib1 = fib2;
		fib2 = fib;
	}

	printf ("%ld\n", sum);

	return 0;
}
