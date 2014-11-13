#include <stdlib.h>
#include "fraction.h"
#include "math_utils.h"

fraction_t fraction_get (int nom, int denom) {
	fraction_t f;

	f.nominator = ABS (nom);
	f.denominator = ABS (denom);
	f.sign = (nom < 0) ^ (denom < 0);

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
