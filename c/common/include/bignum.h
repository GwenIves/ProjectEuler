#ifndef BIGNUM_H_
#define BIGNUM_H_

#include <stdlib.h>
#include <stdbool.h>

#define bignum_get(X) _Generic((X), \
	int: bignum_get_int, \
	const char *: bignum_get_str)(X)

#define bignum_mult(X,Y) _Generic((Y), \
	int: bignum_mult_int, \
	bignum_t *: bignum_mult_bignum)(X,Y)

#define bignum_mult_to(X,Y) _Generic((Y), \
	int: bignum_mult_int_to, \
	bignum_t *: bignum_mult_bignum_to)(X,Y)

#define bignum_add_to(A,B) bignum_add_to_ (A,B,true)

#define bignum_free_array(A,L) for (size_t i = 0; i < L; i++) { bignum_delete (A[i]); }

typedef struct {
	char * digits;
	bool sign;
	size_t allocated;
	size_t used;
} bignum_t;

bignum_t * bignum_get_int (int);
bignum_t * bignum_get_str (const char *);

void bignum_delete (bignum_t *);
void bignum_print (bignum_t *);

bool bignum_is_palindrome (bignum_t *);

int bignum_cmp (bignum_t *, bignum_t *);
bool bignum_is_digit (bignum_t *, int);

int bignum_digits_sum (bignum_t *);

bignum_t * bignum_mult_bignum (bignum_t *, bignum_t *);
bignum_t * bignum_mult_int (bignum_t *, int);
bignum_t * bignum_mult_bignum_to (bignum_t *, bignum_t *);
bignum_t * bignum_mult_int_to (bignum_t *, int);

bignum_t * bignum_add (bignum_t *, bignum_t *);
bignum_t * bignum_add_to_ (bignum_t *, bignum_t *, bool);

bignum_t * bignum_pow (int, int, int);
bignum_t * bignum_reverse (bignum_t *);

#endif
