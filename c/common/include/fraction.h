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
fraction_t fraction_mult (fraction_t *, fraction_t *);
int fraction_cmp (fraction_t *, fraction_t *);

#endif
