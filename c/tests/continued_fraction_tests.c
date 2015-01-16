#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "continued_fraction.h"

static void cf_expand_sqrt_continued_fraction_test (void);
static void cf_sqrt_steps_identical_test (void);
static void cf_evaluate_test (void);

int main (void) {
	cf_expand_sqrt_continued_fraction_test ();
	cf_sqrt_steps_identical_test ();
	cf_evaluate_test ();

	printf ("All continued fraction tests passed\n");

	return 0;
}

static void cf_expand_sqrt_continued_fraction_test (void) {
	cf_sqrt_step_t frac;

	frac.num = 23;
	frac.step = 0;

	cf_expand_sqrt_continued_fraction (&frac);

	assert (frac.a == 4);
	assert (frac.step == 1);

	cf_expand_sqrt_continued_fraction (&frac);

	assert (frac.a == 1);
	assert (frac.step == 2);

	cf_expand_sqrt_continued_fraction (&frac);

	assert (frac.a == 3);
	assert (frac.step == 3);
}

static void cf_sqrt_steps_identical_test (void) {
	cf_sqrt_step_t frac;

	frac.num = 8;
	frac.step = 0;

	cf_expand_sqrt_continued_fraction (&frac);
	cf_expand_sqrt_continued_fraction (&frac);

	cf_sqrt_step_t saved;

	memcpy (&saved, &frac, sizeof (frac));

	cf_expand_sqrt_continued_fraction (&frac);

	assert (!cf_sqrt_steps_identical (&frac, &saved));

	cf_expand_sqrt_continued_fraction (&frac);

	assert (cf_sqrt_steps_identical (&frac, &saved));
}

static void cf_evaluate_test (void) {
	linked_list_t * coefficients = linked_list_create ();

	int * c_ptr = NULL;

	c_ptr = linked_list_add_empty (coefficients, int);
	*c_ptr = 1;
	c_ptr = linked_list_add_empty (coefficients, int);
	*c_ptr = 2;
	c_ptr = linked_list_add_empty (coefficients, int);
	*c_ptr = 2;

	cf_convergent_t convergent = cf_evaluate (coefficients);

	bignum_t * nom_ref = bignum_get (7);
	bignum_t * denom_ref = bignum_get (5);

	assert (!bignum_cmp (nom_ref, convergent.nominator));
	assert (!bignum_cmp (denom_ref, convergent.denominator));

	bignum_delete (nom_ref);
	bignum_delete (denom_ref);
	bignum_delete (convergent.nominator);
	bignum_delete (convergent.denominator);

	linked_list_free (coefficients);
}
