/*
 * Find the sum of maximal remainders of dividing (a - 1)^n + (a + 1)^n by a^2 for all a, 3 <= a <= N
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

static int max_remainder (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 3)
		return 1;

	int sum = 0;

	for (int a = 3; a <= N; a++)
		sum += max_remainder (a);

	printf ("%d\n", sum);

	return 0;
}

static int max_remainder (int a) {
	linked_list_t * remainders = linked_list_create ();

	int a_less_1 = a - 1;
	int a_plus_1 = a + 1;
	int mod = a * a;

	int power_1 = a_less_1;
	int power_2 = a_plus_1;

	int max = (power_1 + power_2) % mod;

	while (true) {
		int new_power_1 = (power_1 * a_less_1) % mod;
		int new_power_2 = (power_2 * a_plus_1) % mod;

		bool encountered_before = false;

		int * p_ptr = NULL;

		while ((p_ptr = linked_list_next (remainders, int)) != NULL)
			if (p_ptr[0] == new_power_1 && p_ptr[1] == new_power_2) {
				encountered_before = true;

				linked_list_stop_iteration (remainders);
				break;
			}

		if (encountered_before)
			break;

		power_1 = new_power_1;
		power_2 = new_power_2;

		int sum = (power_1 + power_2) % mod;

		if (sum > max)
			max = sum;

		p_ptr = linked_list_add_empty_array (remainders, 2, int);
		p_ptr[0] = power_1;
		p_ptr[1] = power_2;
	}

	linked_list_free (remainders);

	return max;
}
