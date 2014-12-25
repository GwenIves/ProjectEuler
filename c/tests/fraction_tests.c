#include <assert.h>
#include <stdio.h>
#include "fraction.h"

static void fraction_get_test ();
static void fraction_reduce_test ();
static void fraction_add_test ();
static void fraction_sub_test ();
static void fraction_mult_test ();
static void fraction_div_test ();
static void fraction_cmp_test ();

int main () {
	fraction_get_test ();
	fraction_reduce_test ();
	fraction_add_test ();
	fraction_sub_test ();
	fraction_mult_test ();
	fraction_div_test ();
	fraction_cmp_test ();

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

static void fraction_add_test () {
	fraction_t a = fraction_get (2, 4);
	fraction_t b = fraction_get (2, 6);

	fraction_t f = fraction_add (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 5);
	assert (f.denominator == 6);
	assert (!f.sign);

	a = fraction_get (-2, 4);
	b = fraction_get (-2, 6);

	f = fraction_add (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 5);
	assert (f.denominator == 6);
	assert (f.sign);

	a = fraction_get (2, 4);
	b = fraction_get (-2, 6);

	f = fraction_add (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 1);
	assert (f.denominator == 6);
	assert (!f.sign);

	a = fraction_get (-2, 4);
	b = fraction_get (2, 6);

	f = fraction_add (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 1);
	assert (f.denominator == 6);
	assert (f.sign);
}

static void fraction_sub_test () {
	fraction_t a = fraction_get (2, 4);
	fraction_t b = fraction_get (2, 6);

	fraction_t f = fraction_sub (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 1);
	assert (f.denominator == 6);
	assert (!f.sign);

	a = fraction_get (-2, 4);
	b = fraction_get (-2, 6);

	f = fraction_sub (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 1);
	assert (f.denominator == 6);
	assert (f.sign);

	a = fraction_get (2, 4);
	b = fraction_get (-2, 6);

	f = fraction_sub (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 5);
	assert (f.denominator == 6);
	assert (!f.sign);

	a = fraction_get (-2, 4);
	b = fraction_get (2, 6);

	f = fraction_sub (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 5);
	assert (f.denominator == 6);
	assert (f.sign);
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

static void fraction_div_test () {
	fraction_t a = fraction_get (240, 360);
	fraction_t b = fraction_get (840, 600);

	fraction_t f = fraction_div (&a, &b);
	fraction_reduce (&f);

	assert (f.nominator == 10);
	assert (f.denominator == 21);
	assert (!f.sign);

	a = fraction_get (-240, 360);
	b = fraction_get (840, 600);

	f = fraction_div (&a, &b);
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
