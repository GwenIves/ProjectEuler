#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

#include <stdbool.h>
#include "linked_list.h"

typedef struct {
	long factor;
	int power;
} factor_t;

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):-(a))
#define ROUND(a) ((a)>0?(int)(a+0.5):(int)(a-0.5))

#define DIGITS_COUNT	10

bool * eratosthenes_sieve (size_t);
bool is_prime (int, bool *, size_t);
bool is_prime_long (long, bool *, size_t, int *, size_t);
size_t prime_count_inverse (size_t);

linked_list_t * factorise (long);
int factors_count (long);

long proper_divisors_sum (long);
int divisors_count (long);
long gcd (long, long);

int make_palindrome (int, int, bool);
bool is_palindrome (int, int);
bool is_permutation (int, int);

long concatenate (int, int);

bool pandigital_test_and_set_digits (char *, int);
bool pandigital_test_digits (char *, size_t);

bool next_permutation (char *);
bool prev_permutation (char *);

long next_fibonacci_num ();
long next_triangle_num ();
long next_pentagonal_num ();
long next_hexagonal_num ();
long next_collatz_num (long);

bool is_triangle (long);
bool is_pentagonal (long);

long arithmetic_sequence_sum (long, long, long);

#endif
