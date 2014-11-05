#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):-(a))
#define ROUND(a) ((a)>0?(int)(a+0.5):(int)(a-0.5))

#define DIGITS_COUNT	10

char * eratosthenes_sieve (int);
int is_prime (char *, int);

int divisors_sum (int);
int gcd (int, int);

int is_palindrome (int, int);
int is_permutation (int, int);

int pandigital_test_and_set_digits (char *, int);
int pandigital_test_digits (char *, int);

int next_permutation (char *);
int prev_permutation (char *);

unsigned long next_triangle_num ();
unsigned long next_pentagonal_num ();
unsigned long next_hexagonal_num ();

#endif