/*
 * Find the sum of all strong, right truncatable Harshad primes under N
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"
#include "euler_utils.h"
#include "linked_list.h"

static void add_new_rth (linked_list_t *, long);
static bool is_strong_rth (long, const int *, size_t);
static long sum_primes (linked_list_t *, const int *, size_t, long);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	long N = atol (argv[1]);

	if (N < 10) {
		printf ("0\n");
		return 0;
	}

	long sum = 0;

	size_t primes_count = 0;
	int * primes = primes_under (NULL, sqrt (N) + 1, &primes_count);

	/*
	 * Iteratively construct all right truncatable Harshad numbers one digit order at a time
	 * Then, for all that are also strong, append a least significant digit and test for primeness
	 */

	linked_list_t * right_truncatable_harshads = linked_list_create ();

	long * l_ptr = linked_list_add_empty (right_truncatable_harshads, long);
	*l_ptr = 0;

	int max_order = integer_log10 (N) - 1;

	for (int order = 0; order <= max_order; order++) {
		linked_list_t * new_harshads = linked_list_create ();

		while ((l_ptr = linked_list_next (right_truncatable_harshads, long)) != NULL)
			add_new_rth (new_harshads, *l_ptr);

		sum += sum_primes (new_harshads, primes, primes_count, N);

		linked_list_free (right_truncatable_harshads);
		right_truncatable_harshads = new_harshads;
	}

	printf ("%ld\n", sum);

	linked_list_free (right_truncatable_harshads);
	free (primes);

	return 0;
}

static long sum_primes (linked_list_t * rth, const int * primes, size_t primes_count, long limit) {
	long sum = 0;

	long * l_ptr = NULL;

	while ((l_ptr = linked_list_next (rth, long)) != NULL) {
		if (!is_strong_rth (*l_ptr, primes, primes_count))
			continue;

		for (int last_digit = 1; last_digit <= 9; last_digit += 2) {
			long prime = *l_ptr * 10 + last_digit;

			if (prime >= limit)
				break;

			if (is_prime_long (prime, NULL, 0, primes, primes_count))
				sum += prime;
		}
	}

	return sum;
}

static bool is_strong_rth (long n, const int * primes, size_t primes_count) {
	long div = n / digits_sum (n);

	return is_prime_long (div, NULL, 0, primes, primes_count);
}

static void add_new_rth (linked_list_t * list, long rth) {
	int digit_sum = digits_sum (rth);

	for (int last_digit = rth > 0 ? 0 : 1; last_digit <= 9; last_digit++) {
		long new_rth = rth * 10 + last_digit;

		if (new_rth % (digit_sum + last_digit) == 0)
			linked_list_add_copy (list, &new_rth, long);
	}
}
