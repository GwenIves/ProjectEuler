#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "bignum.h"
#include "math_utils.h"
#include "utils.h"

static void ensure_allocation (bignum_t *);
static int bignum_magnitude_cmp (bignum_t *, bignum_t *);
static bignum_t * bignum_sub_aux (bignum_t *, bignum_t *);
static void bignum_init (bignum_t *);

bignum_t * bignum_get_int (int value) {
	bignum_t * num = x_malloc (sizeof (bignum_t));

	bignum_init (num);

	if (value < 0) {
		value = -value;
		num->sign = true;
	}

	do {
		ensure_allocation (num);
		num->digits[num->used++] = value % 10;

		value /= 10;
	} while (value != 0);

	return num;
}

bignum_t * bignum_get_str (char * value) {
	bignum_t * num = x_malloc (sizeof (bignum_t));

	bignum_init (num);

	while (isblank (*value))
		value++;

	if (*value == '-')
		num->sign = true;

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
		return bignum_get (0);
	}

	return num;
}

void bignum_delete (bignum_t * num) {
	if (num) {
		free (num->digits);
		free (num);
	}
}

void bignum_print (bignum_t * num) {
	if (num->sign)
		printf ("-");

	for (int i = num->used - 1; i >= 0; i--)
		printf ("%d", (int) num->digits[i]);

	printf ("\n");
}

int bignum_digits_sum (bignum_t * num) {
	int sum = 0;

	for (size_t i = 0; i < num->used; i++)
		sum += num->digits[i];

	return sum;
}

bignum_t * bignum_reverse (bignum_t * num) {
	bignum_t * rev = x_malloc (sizeof (bignum_t));

	bignum_init (rev);

	rev->allocated = num->used;
	rev->used = num->used;
	rev->digits = x_malloc (rev->allocated);

	for (size_t i = 0; i < num->used; i++)
		rev->digits[i] = num->digits[num->used - 1 - i];

	return rev;
}

// Calculates num^pow for num, pow >= 0, if truncate >= 0, then calculate only truncate least-significant digits
bignum_t * bignum_pow (int num, int pow, int truncate) {
	if (num == 0)
		return bignum_get (0);
	else if (pow == 0)
		return bignum_get (1);

	bignum_t * result = bignum_get (1);

	int power_mask = 1;

	while (power_mask < pow)
		power_mask <<= 1;

	while (power_mask > 0) {
		if (power_mask & pow) {
			result = bignum_mult_to (result, result);
			result = bignum_mult_to (result, num);
		} else {
			result = bignum_mult_to (result, result);
		}

		if (truncate >= 0)
			result->used = MIN (truncate, result->used);

		power_mask >>= 1;
	}

	return result;
}

bignum_t * bignum_mult_int_to (bignum_t * a, int b) {
	bignum_t * c = bignum_mult (a, b);

	bignum_delete (a);

	return c;
}

bignum_t * bignum_mult_bignum_to (bignum_t * a, bignum_t * b) {
	bignum_t * c = bignum_mult (a, b);

	bignum_delete (a);

	return c;
}

bignum_t * bignum_mult_int (bignum_t * a, int b) {
	bignum_t * bb = bignum_get (b);

	bignum_t * c = bignum_mult (a, bb);

	bignum_delete (bb);

	return c;
}

bignum_t * bignum_mult_bignum (bignum_t * a, bignum_t * b) {
	bignum_t * c = bignum_get (0);

	if (bignum_is_digit (a, 0) || bignum_is_digit (b, 0))
		return c;

	c->sign = a->sign ^ b->sign;

	int carry = 0;

	for (size_t i = 0; i < b->used; i++) {
		for (size_t j = 0; j < a->used; j++) {
			if (c->used <= i + j) {
				ensure_allocation (c);
				c->digits[c->used++] = 0;
			}

			int partial_mult = c->digits[i + j] + b->digits[i] * a->digits[j] + carry;

			c->digits[i + j] = partial_mult % 10;
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

bignum_t * bignum_add_to_ (bignum_t * a, bignum_t * b, bool clear_flag) {
	bignum_t * c = bignum_add (a, b);

	bignum_delete (a);

	if (clear_flag)
		bignum_delete (b);

	return c;
}

bignum_t * bignum_add (bignum_t * a, bignum_t * b) {
	bignum_t * c = bignum_get (0);

	if ((a->sign ^ b->sign) == false) {
		c->sign = a->sign;
	} else {
		int cmp = bignum_magnitude_cmp (a, b);

		if (cmp > 0) {
			bignum_delete (c);
			c = bignum_sub_aux (a, b);

			if (a->sign)
				c->sign = true;
		} else if (cmp < 0) {
			bignum_delete (c);
			c = bignum_sub_aux (b, a);

			if (b->sign)
				c->sign = true;
		}

		return c;
	}

	size_t used = MAX (a->used, b->used);

	if (used == 0)
		return c;
	else
		c->used = 0;

	int carry = 0;
	int partial_sum = 0;

	for (size_t i = 0; i < used; i++) {
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

bool bignum_is_digit (bignum_t * num, int digit) {
	if (digit >= 0) {
		if (!num->sign && num->used == 1 && num->digits[0] == digit)
			return true;
	} else {
		if (num->sign && num->used == 1 && num->digits[0] == -digit)
			return true;
	}

	return false;
}

int bignum_cmp (bignum_t * a, bignum_t * b) {
	if (b->sign && !a->sign)
		return 1;
	else if (a->sign && !b->sign)
		return -1;
	else
		return bignum_magnitude_cmp (a, b);
}

bool bignum_is_palindrome (bignum_t * num) {
	for (size_t i = 0; i < num->used / 2; i++)
		if (num->digits[i] != num->digits[num->used - 1 - i])
			return false;

	return true;
}

/*
 * Subtraction helper, calculates |a| - |b|
 * |a| must be larger than |b|
 * Signs should be handled by the caller
 */
static bignum_t * bignum_sub_aux (bignum_t * a, bignum_t * b) {
	bignum_t * c = bignum_get (0);
	c->used = 0;

	int carry = 0;

	for (size_t i = 0; i < a->used; i++) {
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

static void bignum_init (bignum_t * num) {
	num->digits = NULL;
	num->sign = false;
	num->allocated = 0;
	num->used = 0;
}
