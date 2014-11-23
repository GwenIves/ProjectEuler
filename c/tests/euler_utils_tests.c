#include <assert.h>
#include <stdio.h>
#include "euler_utils.h"

static void stern_brocot_count_test ();
static void euclid_pythagorean_triple_perim_test ();
static void count_representation_combinations_test ();

int main () {
	stern_brocot_count_test ();
	euclid_pythagorean_triple_perim_test ();
	count_representation_combinations_test ();

	printf ("All euler utils tests passed\n");

	return 0;
}

static void stern_brocot_count_test () {
	fraction_t above = fraction_get (0, 1);
	fraction_t below = fraction_get (1, 1);

	assert (stern_brocot_count (2, &above, &below) == 1);
	assert (stern_brocot_count (8, &above, &below) == 21);
}

static void euclid_pythagorean_triple_perim_test () {
	assert (euclid_pythagorean_triple_perim (9, 6) == 0);
	assert (euclid_pythagorean_triple_perim (9, 7) == 0);
	assert (euclid_pythagorean_triple_perim (2, 1) == 12);
}

static void count_representation_combinations_test () {
	int values[] = {1, 2, 3, 4};

	assert (count_representation_combinations (values, 3, 5, NULL) == 6);
}
