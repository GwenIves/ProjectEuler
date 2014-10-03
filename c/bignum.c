#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "bignum.h"
#include "math_utils.h"
#include "utils.h"

static void ensure_allocation (bignum_t *);
static int bignum_magnitude_cmp (bignum_t *, bignum_t *);
static bignum_t * bignum_sub_aux (bignum_t *, bignum_t *);

bignum_t * get_bignum_int (int value) {
	bignum_t * num = x_malloc (sizeof (bignum_t));

	num->digits = NULL;
	num->sign = 0;
	num->allocated = 0;
	num->used = 0;

	if (value < 0) {
		value *= -1;
		num->sign = 1;
	}

	do {
		ensure_allocation (num);
		num->digits[num->used++] = value % 10;

		value /= 10;
	} while (value != 0);

	return num;
}

bignum_t * get_bignum_str (char * value) {
	bignum_t * num = x_malloc (sizeof (bignum_t));

	num->digits = NULL;
	num->sign = 0;
	num->allocated = 0;
	num->used = 0;

	while (isblank (*value))
		value++;

	if (*value == '-')
		num->sign = 1;

	char * tail_ptr = NULL;

	if (!*value)
		tail_ptr = value;
	else
		tail_ptr = value + strlen (value) - 1;

	while (isspace (*tail_ptr) && tail_ptr > value)
		tail_ptr--;

	while (isdigit (*tail_ptr) && tail_ptr >= value) {
		ensure_allocation (num);
		num->digits[num->used++] = *tail_ptr - '0';

		tail_ptr--;
	}

	if (num->allocated == 0) {
		free (num);
		return get_bignum_int (0);
	}

	return num;
}

void delete_bignum (bignum_t * num) {
	free (num->digits);
	free (num);
}

void print_bignum (bignum_t * num) {
	if (num->sign)
		printf ("-");

	for (int i = num->used - 1; i >= 0; i--)
		printf ("%d", (int) num->digits[i]);

	printf ("\n");
}

bignum_t * bignum_mult (bignum_t * a, bignum_t * b) {
	bignum_t * c = get_bignum_int (0);

	c->sign = a->sign ^ b->sign;

	char carry = 0;

	for (int i = 0; i < b->used; i++) {
		for (int j = 0; j < a->used; j++) {
			int partial_mult = b->digits[i] * a->digits[j] + carry;

			if (c->used <= i + j) {
				ensure_allocation (c);
				c->digits[c->used++] = 0;
			}

			c->digits[i + j] += partial_mult % 10;
			carry = partial_mult / 10;
		}

		if (carry) {
			if (c->used <= i + a->used) {
				ensure_allocation (c);
				c->digits[c->used++] = 0;
			}

			c->digits[i + a->used] = carry;
			carry = 0;
		}
	}

	if (carry) {
		if (c->used <= b->used + a->used - 1) {
			ensure_allocation (c);
			c->digits[c->used++] = 0;
		}

		c->digits[b->used + a->used - 1] = carry;
	}

	return c;
}

bignum_t * bignum_add (bignum_t * a, bignum_t * b) {
	bignum_t * c = get_bignum_int (0);

	if ((a->sign ^ b->sign) == 0) {
		c->sign = a->sign;
	} else {
		int cmp = bignum_magnitude_cmp (a, b);

		if (cmp > 0) {
			delete_bignum (c);
			c = bignum_sub_aux (a, b);

			if (a->sign)
				c->sign = 1;
		} else if (cmp < 0) {
			delete_bignum (c);
			c = bignum_sub_aux (b, a);

			if (b->sign)
				c->sign = 1;
		}

		return c;
	}

	int used = MAX (a->used, b->used);

	if (used == 0)
		return c;
	else
		c->used = 0;

	int carry = 0;
	int partial_sum = 0;

	for (int i = 0; i < used; i++) {
		ensure_allocation (c);

		partial_sum = 0;

		if (a->used > i)
			partial_sum += a->digits[i];

		if (b->used > i)
			partial_sum += b->digits[i];

		partial_sum += carry;

		c->digits[c->used++] = partial_sum % 10;
		carry = partial_sum / 10;
	}

	if (carry) {
		ensure_allocation (c);
		c->digits[c->used++] = carry;
	}

	return c;
}

/*
 * Subtraction helper, calculates |a| - |b|
 * |a| must be larger than |b|
 * Signs should be handled by the caller
 */
static bignum_t * bignum_sub_aux (bignum_t * a, bignum_t * b) {
	bignum_t * c = get_bignum_int (0);
	c->used = 0;

	int carry = 0;

	for (int i = 0; i < a->used; i++) {
		int partial_sub = 0;

		ensure_allocation (c);

		partial_sub = a->digits[i];

		if (b->used > i)
			partial_sub -= b->digits[i];

		partial_sub += carry;

		if (partial_sub < 0) {
			partial_sub += 10;
			carry = -1;
		} else {
			carry = partial_sub / 10;
			partial_sub %= 10;
		}

		c->digits[c->used++] = partial_sub;
	}

	for (int i = c->used - 1; i >= 0; i--)
		if (c->digits[i] == 0)
			c->used--;
		else
			break;

	return c;
}

static void ensure_allocation (bignum_t * num) {
	if (num->allocated <= num->used) {
		num->allocated++;
		num->allocated *= 2;

		num->digits = x_realloc (num->digits, num->allocated);
	}

}

static int bignum_magnitude_cmp (bignum_t * a, bignum_t * b) {
	if (a->used > b->used)
		return 1;
	else if (a->used < b->used)
		return -1;
	else {
		for (int i = a->used - 1; i >= 0; i--) {
			int diff = a->digits[i] - b->digits[i];
			
			if (diff)
				return diff;
		}

		return 0;
	}
}
