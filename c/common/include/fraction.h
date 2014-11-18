#ifndef FRACTION_H_
#define FRACTION_H_

#include <stdbool.h>

typedef struct {
	int nominator;
	int denominator;
	bool sign;
} fraction_t;

fraction_t fraction_get (int, int);
void fraction_reduce (fraction_t *);
fraction_t fraction_mult (fraction_t *, fraction_t *);
int fraction_cmp (fraction_t *, fraction_t *);

#endif
