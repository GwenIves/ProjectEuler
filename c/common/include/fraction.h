#ifndef FRACTION_H_
#define FRACTION_H_

typedef struct {
	long nominator;
	long denominator;
	int sign;
} fraction_t;

fraction_t fraction_get (long, long);
void fraction_reduce (fraction_t *);
fraction_t fraction_mult (fraction_t *, fraction_t *);

#endif
