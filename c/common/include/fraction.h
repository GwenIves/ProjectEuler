#ifndef FRACTION_H_
#define FRACTION_H_

#include <stdbool.h>

typedef struct {
	long nominator;
	long denominator;
	bool sign;
} fraction_t;

fraction_t fraction_get (long, long);
void fraction_reduce (fraction_t *);
fraction_t fraction_mult (fraction_t *, fraction_t *);

#endif
