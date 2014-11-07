#include <assert.h>
#include <stdio.h>
#include "bignum.h"

static void bignum_get_int_test ();
static void bignum_get_str_test ();
static void bignum_mult_test ();
static void bignum_add_test ();
static void bignum_cmp_test ();

int main () {
	bignum_get_int_test ();
	bignum_get_str_test ();
	bignum_mult_test ();
	bignum_add_test ();
	bignum_cmp_test ();

	printf ("All bignum tests passed\n");

	return 0;
}

static void bignum_get_int_test () {
	bignum_t * num = bignum_get (876543210);

	for (size_t i = 0; i < num->used; i++)
		assert (num->digits[i] == i);

	bignum_delete (num);
}

static void bignum_get_str_test () {
	bignum_t * num = bignum_get ("9876543210");

	for (size_t i = 0; i < num->used; i++)
		assert (num->digits[i] == i);

	bignum_delete (num);
}

static void bignum_mult_test () {
	bignum_t * a = bignum_get ("123456");
	bignum_t * b = bignum_get ("456789");
	bignum_t * b_neg = bignum_get ("-456789");

	bignum_t * c_known = bignum_get ("56393342784");
	bignum_t * c_known_neg = bignum_get ("-56393342784");

	bignum_t * c = bignum_mult (a, b);
	bignum_t * c_neg = bignum_mult (a, b_neg);

	assert (!bignum_cmp (c, c_known));
	assert (!bignum_cmp (c_neg, c_known_neg));

	bignum_delete (a);
	bignum_delete (b);
	bignum_delete (b_neg);
	bignum_delete (c);
	bignum_delete (c_neg);
	bignum_delete (c_known);
	bignum_delete (c_known_neg);
}

static void bignum_add_test () {
	bignum_t * a = bignum_get ("123456789");
	bignum_t * b = bignum_get ("234567890");
	bignum_t * b_neg = bignum_get ("-234567890");

	bignum_t * c_known = bignum_get ("358024679");
	bignum_t * c_known_neg = bignum_get ("-111111101");

	bignum_t * c = bignum_add (a, b);
	bignum_t * c_neg = bignum_add (a, b_neg);

	assert (!bignum_cmp (c, c_known));
	assert (!bignum_cmp (c_neg, c_known_neg));

	bignum_delete (a);
	bignum_delete (b);
	bignum_delete (b_neg);
	bignum_delete (c);
	bignum_delete (c_neg);
	bignum_delete (c_known);
	bignum_delete (c_known_neg);
}

static void bignum_cmp_test () {
	bignum_t * a = bignum_get ("123456789");
	bignum_t * b = bignum_get ("234567890");
	bignum_t * c = bignum_get ("-234567890");

	assert (bignum_cmp (b, a) == 1);
	assert (bignum_cmp (a, a) == 0);
	assert (bignum_cmp (c, a) == -1);

	bignum_delete (a);
	bignum_delete (b);
	bignum_delete (c);
}
