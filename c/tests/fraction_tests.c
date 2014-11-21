#include <assert.h>
#include <stdio.h>
#include "fraction.h"

static void fraction_get_test ();
static void fraction_reduce_test ();
static void fraction_mult_test ();
static void fraction_cmp_test ();
static void stern_brocot_count_test ();

int main () {
	fraction_get_test ();
	fraction_reduce_test ();
	fraction_mult_test ();
	fraction_cmp_test ();
	stern_brocot_count_test ();

	printf ("All fraction tests passed\n");

	return 0;
}

static void fraction_get_test () {
	fraction_t f = fraction_get (10, 20);

	assert (f.nominator == 1);
	assert (f.denominator == 2);
	assert (!f.sign);

	f = fraction_get (10, -20);

	assert (f.nominator == 1);
	assert (f.denominator == 2);
	assert (f.sign);

	f = fraction_get_ (10, 20, false);

	assert (f.nominator == 10);
	assert (f.denominator == 20);
	assert (!f.sign);
}

static void fraction_reduce_test () {
	fraction_t f = fraction_get (240, 360);
	fraction_reduce (&f);

	assert (f.nominator == 2);
	assert (f.denominator == 3);
}

static void fraction_mult_test () {
	fraction_t a = fraction_get (240, 360);
	fraction_t b = fraction_get (600, 840);

	fraction_t f = fraction_mult (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 10);
	assert (f.denominator == 21);
	assert (!f.sign);

	a = fraction_get (-240, 360);
	b = fraction_get (600, 840);

	f = fraction_mult (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 10);
	assert (f.denominator == 21);
	assert (f.sign);
}

static void fraction_cmp_test () {
	fraction_t a = fraction_get (251, 918);
	fraction_t b = fraction_get (252, 918);
	fraction_t c = fraction_get (-253, 918);
	fraction_t d = fraction_get (-254, 918);

	assert (fraction_cmp (&a, &b) < 0);
	assert (fraction_cmp (&b, &c) > 0);
	assert (fraction_cmp (&c, &d) > 0);
}

static void stern_brocot_count_test () {
	fraction_t above = fraction_get (0, 1);
	fraction_t below = fraction_get (1, 1);

	assert (stern_brocot_count (2, &above, &below) == 1);
	assert (stern_brocot_count (8, &above, &below) == 21);
}
