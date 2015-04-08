#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "euler_utils.h"

static void stern_brocot_count_test (void);
static void euclid_pythagorean_triple_perim_test (void);
static void count_representation_combinations_test (void);
static void calculate_sqrt_test (void);
static void is_special_sum_set_test (void);
static void digits_sum_test (void);
static void evaluate_factorisation_test (void);
static void get_repunit_len_test (void);
static void p114_test (void);

int main (void) {
	stern_brocot_count_test ();
	euclid_pythagorean_triple_perim_test ();
	count_representation_combinations_test ();
	calculate_sqrt_test ();
	is_special_sum_set_test ();
	digits_sum_test ();
	evaluate_factorisation_test ();
	get_repunit_len_test ();
	p114_test ();

	printf ("All euler utils tests passed\n");

	return 0;
}

static void stern_brocot_count_test (void) {
	fraction_t above = fraction_get (0, 1);
	fraction_t below = fraction_get (1, 1);

	assert (stern_brocot_count (2, &above, &below) == 1);
	assert (stern_brocot_count (8, &above, &below) == 21);
}

static void euclid_pythagorean_triple_perim_test (void) {
	assert (euclid_pythagorean_triple_perim (9, 6) == 0);
	assert (euclid_pythagorean_triple_perim (9, 7) == 0);
	assert (euclid_pythagorean_triple_perim (2, 1) == 12);
}

static void count_representation_combinations_test (void) {
	int values[] = {1, 2, 3, 4};

	assert (count_representation_combinations (values, 3, 5) == 6);
}

static void calculate_sqrt_test (void) {
	char * sqrt_str = calculate_sqrt (2, 20);

	assert (!strcmp (sqrt_str, "1.4142135623730950488"));

	free (sqrt_str);
}

static void is_special_sum_set_test (void) {
	int set_1[] = {2, 3, 4};

	assert (is_special_sum_set (set_1, array_len (set_1)));

	int set_2[] = {2, 3, 6};

	assert (!is_special_sum_set (set_2, array_len (set_2)));

	int set_3[] = {42, 65, 75, 81, 84, 86, 87, 88};

	assert (!is_special_sum_set (set_3, array_len (set_3)));
}

static void digits_sum_test (void) {
	assert (digits_sum (0) == 0);
	assert (digits_sum (123456) == 21);
	assert (digits_sum (-123456) == 21);
}

static void evaluate_factorisation_test (void) {
	int factors[] = {2, 5, 7};
	int powers[] = {0, 0, 0};
	int powers2[] = {2, 3, 1};

	assert (evaluate_factorisation (factors, powers, 0) == 1);
	assert (evaluate_factorisation (factors, powers, 3) == 1);
	assert (evaluate_factorisation (factors, powers2, 3) == 3500);
}

static void get_repunit_len_test () {
	assert (get_repunit_len (98) == 0);
	assert (get_repunit_len (125) == 0);
	assert (get_repunit_len (111) == 3);
	assert (get_repunit_len (7) == 6);
	assert (get_repunit_len (41) == 5);
}

static void p114_test () {
	assert (p114_count_arrangements (9, 10) == 1);
	assert (p114_count_arrangements (10, 10) == 2);
	assert (p114_count_arrangements (29, 3) == 673135);
	assert (p114_count_arrangements (56, 10) == 880711);
}
