#ifndef BIGNUM_H_
#define BIGNUM_H_

#include <stdbool.h>

#define bignum_get(X) _Generic((X), \
	int: bignum_get_int, \
	char *: bignum_get_str)(X)

typedef struct {
	unsigned char * digits;
	bool sign;
	size_t allocated;
	size_t used;
} bignum_t;

bignum_t * bignum_get_int (int);
bignum_t * bignum_get_str (char *);

void bignum_delete (bignum_t *);
void bignum_print (bignum_t *);

int bignum_cmp (bignum_t *, bignum_t *);

bignum_t * bignum_mult (bignum_t *, bignum_t *);
bignum_t * bignum_add (bignum_t *, bignum_t *);

#endif
