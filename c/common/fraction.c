#include <stdlib.h>
#include "fraction.h"
#include "math_utils.h"

fraction_t fraction_get (unsigned long nom, unsigned long denom) {
	fraction_t f;

	f.nominator = nom;
	f.denominator = denom;

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

	fraction_reduce (&c);

	return c;
}
