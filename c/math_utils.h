#ifndef _MATH_UTILS_H
#define _MATH_UTILS_H

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):-(a))
#define ROUND(a) ((int)(a+0.5))

#define DIGITS_COUNT	10

char * eratosthenes_sieve (int);
int is_prime (char *, int);

int divisors_sum (int);
int gcd (int, int);
int is_palindrome (int, int);

int pandigital_test_and_set_digits (char *, int);
int pandigital_test_digits (char *, int);

int next_permutation (char *);
int prev_permutation (char *);

#endif
