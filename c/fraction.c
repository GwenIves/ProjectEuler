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
	int len = MAX (f->denominator, f->nominator);

	if (!len)
		return;

	char * primes = eratosthenes_sieve (len + 1);

	for (int i = 2; i <= len; i++)
		if (primes[i]) {
			while (f->nominator % i == 0 && f->denominator % i == 0) {
				f->nominator /= i;
				f->denominator /= i;
			}
		}

	free (primes);
}

fraction_t fraction_mult (fraction_t * a, fraction_t * b) {
	fraction_t c;

	c.denominator = a->denominator * b->denominator;
	c.nominator = a->nominator * b->nominator;

	fraction_reduce (&c);

	return c;
}
