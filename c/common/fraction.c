#include <stdlib.h>
#include "fraction.h"
#include "math_utils.h"

fraction_t fraction_get_ (int nom, int denom, bool should_reduce) {
	fraction_t f;

	f.nominator = ABS (nom);
	f.denominator = ABS (denom);
	f.sign = (nom < 0) ^ (denom < 0);

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

fraction_t fraction_mult (fraction_t * a, fraction_t * b) {
	fraction_t c;

	c.denominator = a->denominator * b->denominator;
	c.nominator = a->nominator * b->nominator;
	c.sign = a->sign ^ b->sign;

	fraction_reduce (&c);

	return c;
}

int fraction_cmp (fraction_t * a, fraction_t * b) {
	if (a->sign ^ b->sign)
		return b->sign ? 1 : -1;

	int aa = a->nominator * b->denominator;
	int bb = b->nominator * a->denominator;

	if (!a->sign)
		return aa - bb;
	else
		return bb - aa;
}
