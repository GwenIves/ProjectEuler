#ifndef CONTINUED_FRACTION_H_
#define CONTINUED_FRACTION_H_

#include <stdbool.h>
#include "bignum.h"
#include "linked_list.h"

/*
 * Consider sqrt (num) as a continued fraction a_0 + 1 / (a_1 + 1 / (a_2 + ... ) ... )
 * The structure holds a_{step} and a representation of the remainder as 1 / (b / (sqrt (num) + c))
 * This can be expanded into a_{step + 1} by the cf_expand_sqrt_continued_fraction () function
 */
typedef struct {
	int num;
	int root_floor;
	int step;
	int a;
	int b;
	int c;
} cf_sqrt_step_t;

typedef struct {
	bignum_t * nominator;
	bignum_t * denominator;
} cf_convergent_t;

bool cf_expand_sqrt_continued_fraction (cf_sqrt_step_t *);
bool cf_sqrt_steps_identical (const cf_sqrt_step_t *, const cf_sqrt_step_t *);

cf_convergent_t cf_evaluate (linked_list_t *);

#endif
