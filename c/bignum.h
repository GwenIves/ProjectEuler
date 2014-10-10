#ifndef _BIGNUM_H
#define _BIGNUM_H

typedef struct {
	char * digits;
	char sign;
	int allocated;
	int used;
	int significant;
} bignum_t;

bignum_t * get_bignum_int (int);
bignum_t * get_bignum_str (char *);

void delete_bignum (bignum_t *);
void print_bignum (bignum_t *);

int bignum_cmp (bignum_t *, bignum_t *);

bignum_t * bignum_mult (bignum_t *, bignum_t *);
bignum_t * bignum_add (bignum_t *, bignum_t *);

#endif
