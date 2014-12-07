#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "math_utils.h"
#include "utils.h"

static void max_test ();
static void min_test ();
static void abs_test ();
static void round_test ();
static void eratosthenes_sieve_test ();
static void miller_rabin_test ();
static void is_prime_test ();
static void is_prime_long_test ();
static void prime_count_inverse_test ();
static void factorise_test ();
static void factors_to_value_test ();
static void factors_to_totient_test ();
static void factors_count_test ();
static void proper_divisors_sum_test ();
static void divisors_count_test ();
static void gcd_test ();
static void make_palindrome_test ();
static void is_palindrome_test ();
static void is_permutation_test ();
static void is_increasing_test ();
static void is_decreasing_test ();
static void is_bouncy_test ();
static void concatenate_test ();
static void reverse_test ();
static void is_pandigital_test ();
static void pandigital_test_and_set_digits_test ();
static void pandigital_test_digits_test ();
static void next_permutation_test ();
static void prev_permutation_test ();
static void next_triangle_num_test ();
static void next_square_num_test ();
static void next_pentagonal_num_test ();
static void next_generalised_pentagonal_num_test ();
static void next_hexagonal_num_test ();
static void next_heptagonal_num_test ();
static void next_octagonal_num_test ();
static void next_collatz_num_test ();
static void next_fibonacci_num_test ();
static void next_digits_factorial_num_test ();
static void is_triangle_test ();
static void is_pentagonal_test ();
static void arithmetic_sequence_sum_test ();
static void mod_pow_test ();
static void power_test ();
static void euclid_pythagorean_triple_test ();
static void is_perfect_square_test ();

int main () {
	max_test ();
	min_test ();
	abs_test ();
	round_test ();
	eratosthenes_sieve_test ();
	miller_rabin_test ();
	is_prime_test ();
	is_prime_long_test ();
	prime_count_inverse_test ();
	factorise_test ();
	factors_to_value_test ();
	factors_to_totient_test ();
	factors_count_test ();
	proper_divisors_sum_test ();
	divisors_count_test ();
	gcd_test ();
	make_palindrome_test ();
	is_palindrome_test ();
	is_permutation_test ();
	is_increasing_test ();
	is_decreasing_test ();
	is_bouncy_test ();
	concatenate_test ();
	reverse_test ();
	is_pandigital_test ();
	pandigital_test_and_set_digits_test ();
	pandigital_test_digits_test ();
	next_permutation_test ();
	prev_permutation_test ();
	next_triangle_num_test ();
	next_square_num_test ();
	next_pentagonal_num_test ();
	next_generalised_pentagonal_num_test ();
	next_hexagonal_num_test ();
	next_heptagonal_num_test ();
	next_octagonal_num_test ();
	next_collatz_num_test ();
	next_fibonacci_num_test ();
	next_digits_factorial_num_test ();
	is_triangle_test ();
	is_pentagonal_test ();
	arithmetic_sequence_sum_test ();
	mod_pow_test ();
	power_test ();
	euclid_pythagorean_triple_test ();
	is_perfect_square_test ();

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

static void miller_rabin_test () {
	static const int primes_under = 1000000;

	bool * sieve = eratosthenes_sieve (primes_under);

	for (int i = 3; i < primes_under; i++)
		assert (miller_rabin (i) == sieve[i]);

	free (sieve);
}

static void is_prime_test () {
	static const int primes_under = 798;

	bool * sieve = eratosthenes_sieve (primes_under);

	assert (!is_prime (797 * 797, sieve, primes_under));
	assert (is_prime (336533, sieve, primes_under));

	free (sieve);
}

static void is_prime_long_test () {
	static const int primes_under = 18481074;

	bool * sieve = eratosthenes_sieve (primes_under);
	int * primes = x_malloc (primes_under * sizeof (int));
	size_t primes_count = 0;

	for (size_t i = 2; i < primes_under; i++)
		if (sieve[i])
			primes[primes_count++] = i;

	// Through Eratosthenes sieve (num < primes_under)
	assert (!is_prime_long (635209, sieve, primes_under, primes, primes_count));
	assert (is_prime_long (336533L, sieve, primes_under, primes, primes_count));

	// Through determinist Miller-Rabin (primes_under >= num < MILLER_RABIN_DETERMINISTIC_LIMIT)
	assert (is_prime_long (20786669, sieve, primes_under, primes, primes_count));
	assert (!is_prime_long (20786671, sieve, primes_under, primes, primes_count));

	// Through divisor checking (MILLER_RABIN_DETERMINISTIC_LIMIT <= num)
	assert (is_prime_long (341550071728361L, sieve, primes_under, primes, primes_count));
	assert (!is_prime_long (MILLER_RABIN_DETERMINISTIC_LIMIT, sieve, primes_under, primes, primes_count));

	free (sieve);
	free (primes);
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

static void factors_to_value_test () {
	linked_list_t * factors = factorise (97);

	assert (factors_to_value (factors) == 97);

	linked_list_free (factors);

	factors = factorise (56);

	assert (factors_to_value (factors) == 56);

	linked_list_free (factors);
}

static void factors_to_totient_test () {
	linked_list_t * factors = factorise (97);

	assert (factors_to_totient (factors) == 96);

	linked_list_free (factors);

	factors = factorise (56);

	assert (factors_to_totient (factors) == 24);

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

static void is_increasing_test () {
	assert (is_increasing (124468));
	assert (!is_increasing (124768));
}

static void is_decreasing_test () {
	assert (is_decreasing (66420));
	assert (!is_decreasing (66720));
}

static void is_bouncy_test () {
	assert (is_bouncy (155349));
	assert (!is_bouncy (1559));
	assert (!is_bouncy (553));
}

static void concatenate_test () {
	assert (concatenate (12345, 678910) == 12345678910L);
}

static void reverse_test () {
	assert (reverse (14825, 10) == 52841);
}

static void is_pandigital_test () {
	assert (is_pandigital (728456139, 9));
	assert (is_pandigital (12345, 5));
	assert (!is_pandigital (7284561391L, 9));
	assert (!is_pandigital (12345, 6));
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
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_triangle_num ();

	assert (num == 55);
}

static void next_square_num_test () {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_square_num ();

	assert (num == 100);
}

static void next_pentagonal_num_test () {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_pentagonal_num ();

	assert (num == 145);
}

static void next_generalised_pentagonal_num_test () {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_generalised_pentagonal_num (false);

	assert (num == 40);

	num = next_generalised_pentagonal_num (true);

	for (size_t i = 0; i < 10; i++)
		num = next_generalised_pentagonal_num (false);

	assert (num == 40);
}

static void next_hexagonal_num_test () {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_hexagonal_num ();

	assert (num == 190);
}

static void next_heptagonal_num_test () {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_heptagonal_num ();

	assert (num == 235);
}

static void next_octagonal_num_test () {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_octagonal_num ();

	assert (num == 280);
}

static void next_fibonacci_num_test () {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_fibonacci_num ();

	assert (num == 89);
}

static void next_collatz_num_test () {
	assert (next_collatz_num (13) == 40);
	assert (next_collatz_num (16) == 8);
}

static void next_digits_factorial_num_test () {
	assert (next_digits_factorial_num (169) == 363601);
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

static void mod_pow_test () {
	assert (mod_pow (0, 10, 1) == 0);
	assert (mod_pow (10, 0, 1) == 1);
	assert (mod_pow (3, 10, 60000) == 59049);
	assert (mod_pow (3, 10, 50000) == 9049);
}

static void power_test () {
	assert (power (0, 10) == 0);
	assert (power (10, 0) == 1);
	assert (power (3, 10) == 59049);
}

static void euclid_pythagorean_triple_test () {
	int a = 0;
	int b = 0;
	int c = 0;

	assert (!euclid_pythagorean_triple (9, 6, &a, &b, &c));
	assert (!euclid_pythagorean_triple (9, 7, &a, &b, &c));

	assert (euclid_pythagorean_triple (2, 1, &a, &b, &c));

	assert (a == 3);
	assert (b == 4);
	assert (c == 5);
}

static void is_perfect_square_test () {
	assert (is_perfect_square (1));
	assert (is_perfect_square (625));
	assert (!is_perfect_square (624));
}
