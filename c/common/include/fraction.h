#ifndef FRACTION_H_
#define FRACTION_H_

#include <stdbool.h>

#define fraction_get(n,d)	fraction_get_(n,d,true)

typedef struct {
	int nominator;
	int denominator;
	bool sign;
} fraction_t;

fraction_t fraction_get_ (int, int, bool);
void fraction_reduce (fraction_t *);
fraction_t fraction_add (const fraction_t *, const fraction_t *);
fraction_t fraction_sub (const fraction_t *, const fraction_t *);
fraction_t fraction_mult (const fraction_t *, const fraction_t *);
fraction_t fraction_div (const fraction_t *, const fraction_t *);
fraction_t fraction_invert (const fraction_t *);
int fraction_cmp (const fraction_t *, const fraction_t *);

#endif
