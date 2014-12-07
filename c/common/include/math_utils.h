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
#define MILLER_RABIN_DETERMINISTIC_LIMIT	341550071728321L
#define GOLDEN_RATIO	1.6180339887498949025257388711906969547271728515625

bool * eratosthenes_sieve (size_t);
bool miller_rabin (long);
bool is_prime (int, bool *, size_t);
bool is_prime_long (long, bool *, size_t, int *, size_t);
size_t prime_count_inverse (size_t);

linked_list_t * factorise (long);
int factors_count (long);
long factors_to_value (linked_list_t *);
long factors_to_totient (linked_list_t *);

long proper_divisors_sum (long);
int divisors_count (long);
long gcd (long, long);

int make_palindrome (int, int, bool);
bool is_palindrome (long, int);
bool is_permutation (int, int);

bool is_increasing (int);
bool is_decreasing (int);
bool is_bouncy (int);

long concatenate (int, int);
long reverse (long, int);

bool is_pandigital (long, size_t);
bool pandigital_test_and_set_digits (char *, long);
bool pandigital_test_digits (char *, size_t);

bool next_permutation (char *);
bool prev_permutation (char *);

long next_fibonacci_num ();
long next_triangle_num ();
long next_square_num ();
long next_pentagonal_num ();
int next_generalised_pentagonal_num (bool);
long next_hexagonal_num ();
long next_heptagonal_num ();
long next_octagonal_num ();
long next_collatz_num (long);
int next_digits_factorial_num (int);

bool is_triangle (long);
bool is_pentagonal (long);

long arithmetic_sequence_sum (long, long, long);

long mod_pow (long, long, long);
long power (long, long);

bool euclid_pythagorean_triple (int, int, int *, int *, int *);

bool is_perfect_square (long);

#endif
