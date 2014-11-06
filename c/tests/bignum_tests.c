#include <assert.h>
#include <stdio.h>
#include "bignum.h"

static void get_bignum_int_test ();
static void get_bignum_str_test ();
static void bignum_mult_test ();
static void bignum_add_test ();
static void bignum_cmp_test ();

int main () {
	get_bignum_int_test ();
	get_bignum_str_test ();
	bignum_mult_test ();
	bignum_add_test ();
	bignum_cmp_test ();

	printf ("All bignum tests passed\n");

	return 0;
}

static void get_bignum_int_test () {
	bignum_t * num = get_bignum_int (876543210);

	for (int i = 0; i < num->used; i++)
		assert (num->digits[i] == i);

	delete_bignum (num);
}

static void get_bignum_str_test () {
	bignum_t * num = get_bignum_str ("9876543210");

	for (int i = 0; i < num->used; i++)
		assert (num->digits[i] == i);

	delete_bignum (num);
}

static void bignum_mult_test () {
	bignum_t * a = get_bignum_str ("123456");
	bignum_t * b = get_bignum_str ("456789");
	bignum_t * b_neg = get_bignum_str ("-456789");

	bignum_t * c_known = get_bignum_str ("56393342784");
	bignum_t * c_known_neg = get_bignum_str ("-56393342784");

	bignum_t * c = bignum_mult (a, b);
	bignum_t * c_neg = bignum_mult (a, b_neg);

	assert (!bignum_cmp (c, c_known));
	assert (!bignum_cmp (c_neg, c_known_neg));

	delete_bignum (a);
	delete_bignum (b);
	delete_bignum (b_neg);
	delete_bignum (c);
	delete_bignum (c_neg);
	delete_bignum (c_known);
	delete_bignum (c_known_neg);
}

static void bignum_add_test () {
	bignum_t * a = get_bignum_str ("123456789");
	bignum_t * b = get_bignum_str ("234567890");
	bignum_t * b_neg = get_bignum_str ("-234567890");

	bignum_t * c_known = get_bignum_str ("358024679");
	bignum_t * c_known_neg = get_bignum_str ("-111111101");

	bignum_t * c = bignum_add (a, b);
	bignum_t * c_neg = bignum_add (a, b_neg);

	assert (!bignum_cmp (c, c_known));
	assert (!bignum_cmp (c_neg, c_known_neg));

	delete_bignum (a);
	delete_bignum (b);
	delete_bignum (b_neg);
	delete_bignum (c);
	delete_bignum (c_neg);
	delete_bignum (c_known);
	delete_bignum (c_known_neg);
}

static void bignum_cmp_test () {
	bignum_t * a = get_bignum_str ("123456789");
	bignum_t * b = get_bignum_str ("234567890");
	bignum_t * c = get_bignum_str ("-234567890");

	assert (bignum_cmp (b, a) == 1);
	assert (bignum_cmp (a, a) == 0);
	assert (bignum_cmp (c, a) == -1);

	delete_bignum (a);
	delete_bignum (b);
	delete_bignum (c);
}
