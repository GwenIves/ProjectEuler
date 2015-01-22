#include <math.h>
#include "continued_fraction.h"

bool cf_expand_sqrt_continued_fraction (cf_sqrt_step_t * f) {
	if (f->step == 0) {
		f->root_floor = sqrt (f->num);

		f->a = f->root_floor;
		f->b = 1;
		f->c = -f->root_floor;
	} else {
		int denom = (f->num - f->c * f->c) / f->b;

		// num is rational, fraction finite
		if (denom == 0)
			return false;

		int a = (f->root_floor - f->c) / denom;
		int c = -f->c - a * denom;

		f->a = a;
		f->b = denom;
		f->c = c;
	}

	f->step++;

	return true;
}

bool cf_sqrt_steps_identical (const cf_sqrt_step_t * f1, const cf_sqrt_step_t * f2) {
	if (f1->a != f2->a)
		return false;
	else if (f1->b != f2->b)
		return false;
	else if (f1->c != f2->c)
		return false;

	return true;
}

cf_convergent_t cf_evaluate (linked_list_t * coefficients) {
	bignum_t * nominator = bignum_get (0);
	bignum_t * denominator = bignum_get (1);

	int * c_ptr = NULL;

	while ((c_ptr = linked_list_next (coefficients, int)) != NULL) {
		nominator = bignum_add_to (nominator, bignum_mult (denominator, *c_ptr));

		bignum_t * t = nominator;
		nominator = denominator;
		denominator = t;
	}

	cf_convergent_t convergent;

	convergent.nominator = denominator;
	convergent.denominator = nominator;

	return convergent;
}
