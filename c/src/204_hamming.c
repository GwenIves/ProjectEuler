/*
 * Find how many generalised Hamming numbers of type 100 don't exceed N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

#define HAMMING_TYPE	100

static int count_hamming_numbers (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	printf ("%d\n", count_hamming_numbers (N));

	return 0;
}

static int count_hamming_numbers (int max) {
	size_t primes_count = 0;
	int * primes = primes_under (NULL, HAMMING_TYPE + 1, &primes_count);

	if (primes_count == 0 || max < 1)
		return 0;

	linked_list_t * hamming_numbers = linked_list_create ();

	int count = 1;

	long * l_ptr = linked_list_add_empty (hamming_numbers, long);
	*l_ptr = 1;

	for (size_t i = 0; i < primes_count; i++) {
		while ((l_ptr = linked_list_next (hamming_numbers, long)) != NULL) {
			long num = *l_ptr * primes[i];

			while (num <= max) {
				list_node_t * c = hamming_numbers->cursor;
				linked_list_add_copy (hamming_numbers, &num, long);
				hamming_numbers->cursor = c;

				count++;

				num *= primes[i];
			}
		}
	}

	linked_list_free (hamming_numbers);
	free (primes);

	return count;
}
