#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "math_utils.h"
#include "utils.h"

static void max_test (void);
static void min_test (void);
static void abs_test (void);
static void round_test (void);
static void eratosthenes_sieve_test (void);
static void primes_under_test (void);
static void miller_rabin_test (void);
static void is_prime_test (void);
static void is_prime_long_test (void);
static void prime_count_inverse_test (void);
static void get_totients_under_test (void);
static void totient_sum_test (void);
static void factorise_test (void);
static void factors_to_value_test (void);
static void factors_to_totient_test (void);
static void factors_count_test (void);
static void proper_divisors_sum_test (void);
static void divisors_count_test (void);
static void gcd_test (void);
static void make_palindrome_test (void);
static void is_palindrome_test (void);
static void is_permutation_test (void);
static void is_increasing_test (void);
static void is_decreasing_test (void);
static void is_bouncy_test (void);
static void concatenate_test (void);
static void reverse_test (void);
static void is_pandigital_test (void);
static void pandigital_test_and_set_digits_test (void);
static void pandigital_test_digits_test (void);
static void next_number_test (void);
static void next_number_non_decreasing_test (void);
static void permutations_count_test (void);
static void next_permutation_test (void);
static void prev_permutation_test (void);
static void next_triangle_num_test (void);
static void next_square_num_test (void);
static void next_pentagonal_num_test (void);
static void next_generalised_pentagonal_num_test (void);
static void next_hexagonal_num_test (void);
static void next_heptagonal_num_test (void);
static void next_octagonal_num_test (void);
static void next_collatz_num_test (void);
static void next_fibonacci_num_test (void);
static void next_digits_factorial_num_test (void);
static void is_triangle_test (void);
static void is_pentagonal_test (void);
static void arithmetic_sequence_sum_test (void);
static void mod_pow_test (void);
static void power_test (void);
static void euclid_pythagorean_triple_test (void);
static void integer_sqrt_test (void);
static void integer_log10_test (void);
static void factorial_test (void);

int main (void) {
	max_test ();
	min_test ();
	abs_test ();
	round_test ();
	eratosthenes_sieve_test ();
	primes_under_test ();
	miller_rabin_test ();
	is_prime_test ();
	is_prime_long_test ();
	prime_count_inverse_test ();
	get_totients_under_test ();
	totient_sum_test ();
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
	next_number_test ();
	next_number_non_decreasing_test ();
	permutations_count_test ();
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
	integer_sqrt_test ();
	integer_log10_test ();
	factorial_test ();

	printf ("All math util tests passed\n");

	return 0;
}

static void max_test (void) {
	assert (MAX (1, 2) == 2);
}

static void min_test (void) {
	assert (MIN (1, 2) == 1);
}

static void abs_test (void) {
	assert (ABS (1) == 1);
	assert (ABS (-1) == 1);
}

static void round_test (void) {
	assert (ROUND (3) == 3);
	assert (ROUND (3.4) == 3);
	assert (ROUND (3.5) == 4);

	assert (ROUND (-3) == -3);
	assert (ROUND (-3.4) == -3);
	assert (ROUND (-3.5) == -4);
}

static void eratosthenes_sieve_test (void) {
	static const size_t limit = 1000000;

	bool * sieve = eratosthenes_sieve (limit);

	size_t count = 0;

	for (size_t i = 2; i < limit; i++)
		if (sieve[i])
			count++;

	assert (count == 78498);

	free (sieve);
}

static void primes_under_test (void) {
	static const size_t limit = 1000000;

	bool * sieve = eratosthenes_sieve (limit);

	size_t primes_count = 0;
	int * primes = primes_under (sieve, limit, &primes_count);

	assert (primes_count == 78498);

	free (sieve);
	free (primes);

	primes = primes_under (NULL, limit, &primes_count);

	assert (primes_count == 78498);

	free (primes);
}

static void miller_rabin_test (void) {
	static const int primes_under = 1000000;

	bool * sieve = eratosthenes_sieve (primes_under);

	for (int i = 3; i < primes_under; i++)
		assert (miller_rabin (i) == sieve[i]);

	free (sieve);
}

static void is_prime_test (void) {
	static const int primes_under = 798;

	bool * sieve = eratosthenes_sieve (primes_under);

	assert (!is_prime (797 * 797, sieve, primes_under));
	assert (is_prime (336533, sieve, primes_under));

	free (sieve);
}

static void is_prime_long_test (void) {
	static const int primes_under = 18481074;

	bool * sieve = eratosthenes_sieve (primes_under);
	int * primes = x_malloc (primes_under * sizeof (int));
	size_t primes_count = 0;

	for (int i = 2; i < primes_under; i++)
		if (sieve[i])
			primes[primes_count++] = i;

	// Through Eratosthenes sieve (num < primes_under)
	assert (!is_prime_long (635209, sieve, primes_under, NULL, 0));
	assert (is_prime_long (336533L, sieve, primes_under, NULL, 0));

	// Through determinist Miller-Rabin (primes_under >= num < MILLER_RABIN_DETERMINISTIC_LIMIT)
	assert (is_prime_long (20786669, sieve, primes_under, NULL, 0));
	assert (!is_prime_long (20786671, sieve, primes_under, NULL, 0));

	// Through divisor checking (MILLER_RABIN_DETERMINISTIC_LIMIT <= num)
	assert (is_prime_long (341550071728361L, sieve, primes_under, primes, primes_count));
	assert (!is_prime_long (MILLER_RABIN_DETERMINISTIC_LIMIT, sieve, primes_under, primes, primes_count));

	free (sieve);
	free (primes);
}

static void prime_count_inverse_test (void) {
	assert (prime_count_inverse (5) == 100);
	assert (prime_count_inverse (10000) == 1000000);
}

static void get_totients_under_test (void) {
	int * totients = get_totients_under (21);

	assert (totients[1] == 1);
	assert (totients[2] == 1);
	assert (totients[3] == 2);
	assert (totients[4] == 2);
	assert (totients[5] == 4);
	assert (totients[10] == 4);
	assert (totients[11] == 10);
	assert (totients[19] == 18);
	assert (totients[20] == 8);

	free (totients);
}

static void totient_sum_test (void) {
	assert (totient_sum (0) == 0);
	assert (totient_sum (1) == 1);
	assert (totient_sum (10) == 32);
	assert (totient_sum (100) == 3044);
}

static void factorise_test (void) {
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

static void factors_to_value_test (void) {
	linked_list_t * factors = factorise (97);

	assert (factors_to_value (factors) == 97);

	linked_list_free (factors);

	factors = factorise (56);

	assert (factors_to_value (factors) == 56);

	linked_list_free (factors);
}

static void factors_to_totient_test (void) {
	linked_list_t * factors = factorise (97);

	assert (factors_to_totient (factors) == 96);

	linked_list_free (factors);

	factors = factorise (56);

	assert (factors_to_totient (factors) == 24);

	linked_list_free (factors);
}

static void factors_count_test (void) {
	assert (factors_count (330) == 4);
}

static void proper_divisors_sum_test (void) {
	assert (proper_divisors_sum (1) == 1);
	assert (proper_divisors_sum (2) == 1);
	assert (proper_divisors_sum (9) == 4);
	assert (proper_divisors_sum (-9) == 4);
}

static void divisors_count_test (void) {
	assert (divisors_count (1) == 1);
	assert (divisors_count (2) == 2);
	assert (divisors_count (9) == 3);
	assert (divisors_count (-9) == 3);
}

static void gcd_test (void) {
	assert (gcd (3, 5) == 1);
	assert (gcd (12, 60) == 12);
	assert (gcd (90, 12) == 6);
	assert (gcd (-90, 12) == 6);
}

static void make_palindrome_test (void) {
	assert (make_palindrome (123, 10, true) == 12321);
	assert (make_palindrome (123, 10, false) == 123321);
}

static void is_palindrome_test (void) {
	assert (is_palindrome (12344321, 10));
	assert (is_palindrome (1234321, 10));
	assert (is_palindrome (-1234321, 10));
	assert (!is_palindrome (12345321, 10));
}

static void is_permutation_test (void) {
	assert (is_permutation (12345, 32415));
	assert (!is_permutation (12345, 32615));
}

static void is_increasing_test (void) {
	assert (is_increasing (124468));
	assert (!is_increasing (124768));
}

static void is_decreasing_test (void) {
	assert (is_decreasing (66420));
	assert (!is_decreasing (66720));
}

static void is_bouncy_test (void) {
	assert (is_bouncy (155349));
	assert (!is_bouncy (1559));
	assert (!is_bouncy (553));
}

static void concatenate_test (void) {
	assert (concatenate (12345, 678910) == 12345678910L);
}

static void reverse_test (void) {
	assert (reverse (14825, 10) == 52841);
}

static void is_pandigital_test (void) {
	assert (is_pandigital (728456139, 9));
	assert (is_pandigital (12345, 5));
	assert (!is_pandigital (7284561391L, 9));
	assert (!is_pandigital (12345, 6));
}

static void pandigital_test_and_set_digits_test (void) {
	char digits[DIGITS_COUNT];

	memset (digits, 0, DIGITS_COUNT);

	assert (pandigital_test_and_set_digits (digits, 123));
	assert (pandigital_test_and_set_digits (digits, 456));
	assert (!pandigital_test_and_set_digits (digits, 678));
}

static void pandigital_test_digits_test (void) {
	char digits[DIGITS_COUNT] = {0, 1, 1, 1, 1, 1, 1, 0, 0, 0};

	assert (!pandigital_test_digits (digits, 5));
	assert (pandigital_test_digits (digits, 6));
	assert (!pandigital_test_digits (digits, 7));
}

static void next_number_test (void) {
	int num[] = {1, 2, 8};

	assert (next_number (num, 3, 10));

	assert (num[0] == 1);
	assert (num[1] == 2);
	assert (num[2] == 9);

	assert (next_number (num, 3, 10));

	assert (num[0] == 1);
	assert (num[1] == 3);
	assert (num[2] == 0);

	int max_num[] = {9, 9, 9};

	assert (!next_number (max_num, 3, 10));
}

static void next_number_non_decreasing_test (void) {
	int num[] = {1, 2, 8};

	assert (next_number_non_decreasing (num, 3, 10));

	assert (num[0] == 1);
	assert (num[1] == 2);
	assert (num[2] == 9);

	assert (next_number_non_decreasing (num, 3, 10));

	assert (num[0] == 1);
	assert (num[1] == 3);
	assert (num[2] == 3);

	int max_num[] = {9, 9, 9};

	assert (!next_number_non_decreasing (max_num, 3, 10));
}

static void permutations_count_test (void) {
	int item_counts1[] = {5};

	assert (permutations_count (item_counts1, 1) == 1);

	int item_counts2[] = {5, 4};

	assert (permutations_count (item_counts2, 2) == 126);

	int item_counts3[] = {5, 4, 3};

	assert (permutations_count (item_counts3, 3) == 27720);
}

static void next_permutation_test (void) {
	char permutation[DIGITS_COUNT];

	strcpy (permutation, "123456987");

	assert (next_permutation (permutation));
	assert (!strcmp (permutation, "123457689"));

	strcpy (permutation, "987654321");

	assert (!next_permutation (permutation));
	assert (!strcmp (permutation, "987654321"));
}

static void prev_permutation_test (void) {
	char permutation[DIGITS_COUNT];

	strcpy (permutation, "987654123");

	assert (prev_permutation (permutation));
	assert (!strcmp (permutation, "987653421"));

	strcpy (permutation, "123456789");

	assert (!prev_permutation (permutation));
	assert (!strcmp (permutation, "123456789"));
}

static void next_triangle_num_test (void) {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_triangle_num ();

	assert (num == 55);
}

static void next_square_num_test (void) {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_square_num ();

	assert (num == 100);
}

static void next_pentagonal_num_test (void) {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_pentagonal_num ();

	assert (num == 145);
}

static void next_generalised_pentagonal_num_test (void) {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_generalised_pentagonal_num (false);

	assert (num == 40);

	num = next_generalised_pentagonal_num (true);

	for (size_t i = 0; i < 10; i++)
		num = next_generalised_pentagonal_num (false);

	assert (num == 40);
}

static void next_hexagonal_num_test (void) {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_hexagonal_num ();

	assert (num == 190);
}

static void next_heptagonal_num_test (void) {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_heptagonal_num ();

	assert (num == 235);
}

static void next_octagonal_num_test (void) {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_octagonal_num ();

	assert (num == 280);
}

static void next_fibonacci_num_test (void) {
	long num = 0;

	for (size_t i = 0; i < 10; i++)
		num = next_fibonacci_num ();

	assert (num == 89);
}

static void next_collatz_num_test (void) {
	assert (next_collatz_num (13) == 40);
	assert (next_collatz_num (16) == 8);
}

static void next_digits_factorial_num_test (void) {
	assert (next_digits_factorial_num (169) == 363601);
}

static void is_triangle_test (void) {
	assert (is_triangle (406));
	assert (!is_triangle (326));
}

static void is_pentagonal_test (void) {
	assert (is_pentagonal (782));
	assert (!is_pentagonal (426));
}

static void arithmetic_sequence_sum_test (void) {
	assert (arithmetic_sequence_sum (1, 101, 1) == 5050);
	assert (arithmetic_sequence_sum (1, 101, 2) == 2500);
}

static void mod_pow_test (void) {
	assert (mod_pow (0, 10, 1) == 0);
	assert (mod_pow (10, 0, 1) == 1);
	assert (mod_pow (3, 10, 60000) == 59049);
	assert (mod_pow (3, 10, 50000) == 9049);
}

static void power_test (void) {
	assert (power (0, 10) == 0);
	assert (power (10, 0) == 1);
	assert (power (3, 10) == 59049);
}

static void euclid_pythagorean_triple_test (void) {
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

static void integer_sqrt_test (void) {
	assert (integer_sqrt (1) == 1);
	assert (integer_sqrt (625) == 25);
	assert (integer_sqrt (624) == -1);
}

static void integer_log10_test (void) {
	assert (integer_log10 (0) == 0);
	assert (integer_log10 (9) == 0);
	assert (integer_log10 (10) == 1);
	assert (integer_log10 (99) == 1);
	assert (integer_log10 (100) == 2);
}

static void factorial_test (void) {
	assert (factorial (0) == 1);
	assert (factorial (1) == 1);
	assert (factorial (2) == 2);
	assert (factorial (10) == 3628800);
}
