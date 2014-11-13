#include <assert.h>
#include <stdio.h>
#include "bignum.h"

static void bignum_get_int_test ();
static void bignum_get_str_test ();
static void bignum_mult_test ();
static void bignum_mult_to_test ();
static void bignum_add_test ();
static void bignum_add_to_test ();
static void bignum_pow_test ();
static void bignum_cmp_test ();
static void bignum_is_palindrome_test ();
static void bignum_reverse_test ();
static void bignum_digits_sum_test ();

int main () {
	bignum_get_int_test ();
	bignum_get_str_test ();
	bignum_mult_test ();
	bignum_mult_to_test ();
	bignum_add_test ();
	bignum_add_to_test ();
	bignum_pow_test ();
	bignum_cmp_test ();
	bignum_is_palindrome_test ();
	bignum_reverse_test ();
	bignum_digits_sum_test ();

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

	bignum_t * c_known = bignum_get ("56393342784");
	bignum_t * c_known_neg = bignum_get ("-56393342784");

	bignum_t * c = bignum_mult (a, b);
	bignum_t * c_neg = bignum_mult (a, -456789);

	assert (!bignum_cmp (c, c_known));
	assert (!bignum_cmp (c_neg, c_known_neg));

	bignum_delete (a);
	bignum_delete (b);
	bignum_delete (c);
	bignum_delete (c_neg);
	bignum_delete (c_known);
	bignum_delete (c_known_neg);
}

static void bignum_mult_to_test () {
	bignum_t * a = bignum_get ("123456789");
	bignum_t * a_ref = bignum_get ("56296295784");

	a = bignum_mult_to (a, 456);

	assert (!bignum_cmp (a, a_ref));

	bignum_delete (a);
	bignum_delete (a_ref);
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

static void bignum_add_to_test () {
	bignum_t * a = bignum_get ("12345678");
	bignum_t * a_ref = bignum_get ("23456789");

	a = bignum_add_to (a, bignum_get ("11111111"));

	assert (!bignum_cmp (a, a_ref));

	bignum_delete (a);
	bignum_delete (a_ref);
}

static void bignum_pow_test () {
	bignum_t * a_ref = bignum_get (0);
	bignum_t * b_ref = bignum_get (1);
	bignum_t * c_ref = bignum_get ("1073741824");
	bignum_t * c_trunc_ref = bignum_get ("41824");
	bignum_t * d_ref = bignum_get ("32768");

	bignum_t * a = bignum_pow (0, 1, -1);
	bignum_t * b = bignum_pow (10, 0, -1);
	bignum_t * c = bignum_pow (2, 30, -1);
	bignum_t * c_trunc = bignum_pow (2, 30, 5);
	bignum_t * d = bignum_pow (2, 15, -1);

	assert (!bignum_cmp (a, a_ref));
	assert (!bignum_cmp (b, b_ref));
	assert (!bignum_cmp (c, c_ref));
	assert (!bignum_cmp (c_trunc, c_trunc_ref));
	assert (!bignum_cmp (d, d_ref));

	bignum_delete (a);
	bignum_delete (b);
	bignum_delete (c);
	bignum_delete (c_trunc);
	bignum_delete (d);

	bignum_delete (a_ref);
	bignum_delete (b_ref);
	bignum_delete (c_ref);
	bignum_delete (c_trunc_ref);
	bignum_delete (d_ref);
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
static void bignum_is_palindrome_test () {
	bignum_t * a = bignum_get ("12345678987654321");
	bignum_t * b = bignum_get ("123456789987654321");
	bignum_t * c = bignum_get ("1234567897654321");

	assert (bignum_is_palindrome (a));
	assert (bignum_is_palindrome (b));
	assert (!bignum_is_palindrome (c));

	bignum_delete (a);
	bignum_delete (b);
	bignum_delete (c);
}

static void bignum_reverse_test () {
	bignum_t * a = bignum_get ("123456");
	bignum_t * b = bignum_reverse (a);
	bignum_t * b_ref = bignum_get ("654321");

	assert (!bignum_cmp (b, b_ref));

	bignum_delete (a);
	bignum_delete (b);
	bignum_delete (b_ref);
}
static void bignum_digits_sum_test () {
	bignum_t * a = bignum_get ("123456789987654321");

	assert (bignum_digits_sum (a) == 90);

	bignum_delete (a);
}
