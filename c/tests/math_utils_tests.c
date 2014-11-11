#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math_utils.h"

static void max_test ();
static void min_test ();
static void abs_test ();
static void round_test ();
static void eratosthenes_sieve_test ();
static void is_prime_test ();
static void prime_count_inverse_test ();
static void factorise_test ();
static void factors_count_test ();
static void proper_divisors_sum_test ();
static void divisors_count_test ();
static void gcd_test ();
static void make_palindrome_test ();
static void is_palindrome_test ();
static void is_permutation_test ();
static void pandigital_test_and_set_digits_test ();
static void pandigital_test_digits_test ();
static void next_permutation_test ();
static void prev_permutation_test ();
static void next_triangle_num_test ();
static void next_pentagonal_num_test ();
static void next_hexagonal_num_test ();
static void next_collatz_num_test ();
static void next_fibonacci_num_test ();
static void is_triangle_test ();
static void is_pentagonal_test ();
static void arithmetic_sequence_sum_test ();

int main () {
	max_test ();
	min_test ();
	abs_test ();
	round_test ();
	eratosthenes_sieve_test ();
	is_prime_test ();
	prime_count_inverse_test ();
	factorise_test ();
	factors_count_test ();
	proper_divisors_sum_test ();
	divisors_count_test ();
	gcd_test ();
	make_palindrome_test ();
	is_palindrome_test ();
	is_permutation_test ();
	pandigital_test_and_set_digits_test ();
	pandigital_test_digits_test ();
	next_permutation_test ();
	prev_permutation_test ();
	next_triangle_num_test ();
	next_pentagonal_num_test ();
	next_hexagonal_num_test ();
	next_collatz_num_test ();
	next_fibonacci_num_test ();
	is_triangle_test ();
	is_pentagonal_test ();
	arithmetic_sequence_sum_test ();

	printf ("All math util tests passed\n");

	return 0;
}

static void max_test () {
	assert (MAX (1, 2) == 2);
}

static void min_test () {
	assert (MIN (1, 2) == 1);
}

static void abs_test () {
	assert (ABS (1) == 1);
	assert (ABS (-1) == 1);
}

static void round_test () {
	assert (ROUND (3) == 3);
	assert (ROUND (3.4) == 3);
	assert (ROUND (3.5) == 4);

	assert (ROUND (-3) == -3);
	assert (ROUND (-3.4) == -3);
	assert (ROUND (-3.5) == -4);
}

static void eratosthenes_sieve_test () {
	static const int primes_under = 1000000;

	bool * sieve = eratosthenes_sieve (primes_under);

	int count = 0;

	for (int i = 2; i < primes_under; i++)
		if (sieve[i])
			count++;

	assert (count == 78498);

	free (sieve);
}

static void is_prime_test () {
	bool * sieve = eratosthenes_sieve (798);

	assert (!is_prime (sieve, 797 * 797));
	assert (is_prime (sieve, 336533));

	free (sieve);
}

static void prime_count_inverse_test () {
	assert (prime_count_inverse (5) == 100);
	assert (prime_count_inverse (10000) == 1000000);
}

static void factorise_test () {
	linked_list_t * factors = factorise (28);

	factor_t * factor = linked_list_next (factors, factor_t);

	assert (factor != NULL);
	assert (factor->factor == 7);
	assert (factor->power == 1);

	factor = linked_list_next (factors, factor_t);

	assert (factor != NULL);
	assert (factor->factor == 2);
	assert (factor->power == 2);

	factor = linked_list_next (factors, factor_t);
	assert (factor == NULL);

	linked_list_free (factors);
}

static void factors_count_test () {
	assert (factors_count (330) == 4);
}

static void proper_divisors_sum_test () {
	assert (proper_divisors_sum (1) == 1);
	assert (proper_divisors_sum (2) == 1);
	assert (proper_divisors_sum (9) == 4);
	assert (proper_divisors_sum (-9) == 4);
}

static void divisors_count_test () {
	assert (divisors_count (1) == 1);
	assert (divisors_count (2) == 2);
	assert (divisors_count (9) == 3);
	assert (divisors_count (-9) == 3);
}

static void gcd_test () {
	assert (gcd (3, 5) == 1);
	assert (gcd (12, 60) == 12);
	assert (gcd (90, 12) == 6);
	assert (gcd (-90, 12) == 6);
}

static void make_palindrome_test () {
	assert (make_palindrome (123, 10, true) == 12321);
	assert (make_palindrome (123, 10, false) == 123321);
}

static void is_palindrome_test () {
	assert (is_palindrome (12344321, 10));
	assert (is_palindrome (1234321, 10));
	assert (is_palindrome (-1234321, 10));
	assert (!is_palindrome (12345321, 10));
}

static void is_permutation_test () {
	assert (is_permutation (12345, 32415));
	assert (!is_permutation (12345, 32615));
}

static void pandigital_test_and_set_digits_test () {
	char digits[DIGITS_COUNT];

	memset (digits, 0, DIGITS_COUNT);

	assert (pandigital_test_and_set_digits (digits, 123));
	assert (pandigital_test_and_set_digits (digits, 456));
	assert (!pandigital_test_and_set_digits (digits, 678));
}

static void pandigital_test_digits_test () {
	char digits[DIGITS_COUNT] = {0, 1, 1, 1, 1, 1, 1, 0, 0, 0};

	assert (!pandigital_test_digits (digits, 5));
	assert (pandigital_test_digits (digits, 6));
	assert (!pandigital_test_digits (digits, 7));
}

static void next_permutation_test () {
	char permutation[DIGITS_COUNT];

	strcpy (permutation, "123456987");

	assert (next_permutation (permutation));
	assert (!strcmp (permutation, "123457689"));

	strcpy (permutation, "987654321");

	assert (!next_permutation (permutation));
	assert (!strcmp (permutation, "987654321"));
}

static void prev_permutation_test () {
	char permutation[DIGITS_COUNT];

	strcpy (permutation, "987654123");

	assert (prev_permutation (permutation));
	assert (!strcmp (permutation, "987653421"));

	strcpy (permutation, "123456789");

	assert (!prev_permutation (permutation));
	assert (!strcmp (permutation, "123456789"));
}

static void next_triangle_num_test () {
	unsigned long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_triangle_num ();

	assert (num == 55);
}

static void next_pentagonal_num_test () {
	unsigned long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_pentagonal_num ();

	assert (num == 145);
}

static void next_hexagonal_num_test () {
	unsigned long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_hexagonal_num ();

	assert (num == 190);
}

static void next_fibonacci_num_test () {
	unsigned long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_fibonacci_num ();

	assert (num == 89);
}

static void next_collatz_num_test () {
	assert (next_collatz_num (13) == 40);
	assert (next_collatz_num (16) == 8);
}

static void is_triangle_test () {
	assert (is_triangle (406));
	assert (!is_triangle (326));
}

static void is_pentagonal_test () {
	assert (is_pentagonal (782));
	assert (!is_pentagonal (426));
}

static void arithmetic_sequence_sum_test () {
	assert (arithmetic_sequence_sum (1, 101, 1) == 5050);
	assert (arithmetic_sequence_sum (1, 101, 2) == 2500);
}
