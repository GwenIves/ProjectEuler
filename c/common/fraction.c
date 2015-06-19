#include <stdlib.h>
#include "fraction.h"
#include "math_utils.h"

fraction_t fraction_get_ (int nom, int denom, bool should_reduce) {
	fraction_t f;

	f.nominator = ABS (nom);
	f.denominator = ABS (denom);
	f.sign = (nom < 0) != (denom < 0);

	if (should_reduce)
		fraction_reduce (&f);

	return f;
}

void fraction_reduce (fraction_t * f) {
	int factor = gcd (f->nominator, f->denominator);

	if (factor) {
		f->nominator /= factor;
		f->denominator /= factor;
	}
}

fraction_t fraction_add (const fraction_t * a, const fraction_t * b) {
	fraction_t c;

	c.denominator = a->denominator * b->denominator;

	int a_contrib = a->nominator * b->denominator;
	int b_contrib =	b->nominator * a->denominator;

	if (a->sign != b->sign) {
		if (a_contrib > b_contrib) {
			c.nominator = a_contrib - b_contrib;
			c.sign = a->sign;
		} else {
			c.nominator = b_contrib - a_contrib;
			c.sign = b->sign;
		}
	} else {
		c.nominator = a_contrib + b_contrib;
		c.sign = a->sign;
	}

	fraction_reduce (&c);

	return c;
}

fraction_t fraction_sub (const fraction_t * a, const fraction_t * b) {
	fraction_t b_neg = {.nominator = b->nominator, .denominator = b->denominator, .sign = !b->sign};

	return fraction_add (a, &b_neg);
}

fraction_t fraction_mult (const fraction_t * a, const fraction_t * b) {
	fraction_t c;

	c.denominator = a->denominator * b->denominator;
	c.nominator = a->nominator * b->nominator;
	c.sign = a->sign != b->sign;

	fraction_reduce (&c);

	return c;
}

// The caller must ensure b != 0
fraction_t fraction_div (const fraction_t * a, const fraction_t * b) {
	fraction_t b_inv = {.nominator = b->denominator, .denominator = b->nominator, .sign = b->sign};

	return fraction_mult (a, &b_inv);
}

fraction_t fraction_invert (const fraction_t * a) {
	fraction_t inv = fraction_get_ (a->denominator, a->nominator, false);
	inv.sign = a->sign;

	return inv;
}

int fraction_cmp (const fraction_t * a, const fraction_t * b) {
	if (a->sign != b->sign)
		return b->sign ? 1 : -1;

	int aa = a->nominator * b->denominator;
	int bb = b->nominator * a->denominator;

	if (!a->sign)
		return aa - bb;
	else
		return bb - aa;
}
