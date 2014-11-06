#ifndef BIGNUM_H_
#define BIGNUM_H_

typedef struct {
	char * digits;
	char sign;
	size_t allocated;
	size_t used;
} bignum_t;

bignum_t * get_bignum_int (int);
bignum_t * get_bignum_str (char *);

void delete_bignum (bignum_t *);
void print_bignum (bignum_t *);

int bignum_cmp (bignum_t *, bignum_t *);

bignum_t * bignum_mult (bignum_t *, bignum_t *);
bignum_t * bignum_add (bignum_t *, bignum_t *);

#endif
