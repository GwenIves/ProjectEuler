#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

#include <stdbool.h>
#include "linked_list.h"

typedef struct {
	unsigned long factor;
	unsigned int power;
} factor_t;

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):-(a))
#define ROUND(a) ((a)>0?(int)(a+0.5):(int)(a-0.5))

#define DIGITS_COUNT	10

bool * eratosthenes_sieve (size_t);
int is_prime (bool *, int);

linked_list_t * factorise (long);

long proper_divisors_sum (long);
int divisors_count (long);
long gcd (long, long);

int is_palindrome (int, int);
int is_permutation (int, int);

int pandigital_test_and_set_digits (char *, int);
int pandigital_test_digits (char *, size_t);

int next_permutation (char *);
int prev_permutation (char *);

unsigned long next_triangle_num ();
unsigned long next_pentagonal_num ();
unsigned long next_hexagonal_num ();
unsigned long next_collatz_num (unsigned long);

long arithmetic_sequence_sum (long, long, long);

#endif
