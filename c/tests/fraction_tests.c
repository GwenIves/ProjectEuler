#include <assert.h>
#include <stdio.h>
#include "../common/include/fraction.h"

static void fraction_get_test ();
static void fraction_reduce_test ();
static void fraction_mult_test ();

int main () {
	fraction_get_test ();
	fraction_reduce_test ();
	fraction_mult_test ();

	printf ("All fraction tests passed\n");

	return 0;
}

static void fraction_get_test () {
	fraction_t f = fraction_get (1, 2);

	assert (f.nominator == 1);
	assert (f.denominator == 2);
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
}
