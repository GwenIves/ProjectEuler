#ifndef FRACTION_H_
#define FRACTION_H_

typedef struct {
	unsigned long nominator;
	unsigned long denominator;
} fraction_t;

fraction_t fraction_get (unsigned long, unsigned long);
void fraction_reduce (fraction_t *);
fraction_t fraction_mult (fraction_t *, fraction_t *);

#endif
