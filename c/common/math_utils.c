#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils.h"
#include "math_utils.h"

static void set_digits (char *, int);

// Returns an Eratosthenes sieve checkable from 2 (inclusive) to size (non-inclusive)
bool * eratosthenes_sieve (size_t size) {
	if (size < 3)
		return NULL;

	bool * sieve = x_malloc (size * sizeof (bool));

	for (size_t i = 2; i < size; i++)
		sieve[i] = true;

	size_t upper_limit = sqrt (size);
	for (size_t i = 2; i <= upper_limit; i++)
		if (sieve[i])
			for (size_t j = i * i; j < size; j += i)
				sieve[j] = false;

	return sieve;
}

// Determines if a number is prime by divisor checking, the caller must guarantee the primes sieve contains entries at least up to sqrt (num) inclusive
int is_prime (bool * primes, int num) {
	if (num < 2)
		return 0;

	int limit = sqrt (num);

	for (int i = 2; i <= limit; i++)
		if (primes[i] && num % i == 0)
			return 0;

	return 1;
}

linked_list_t * factorise (long num) {
	if (num < 0)
		num = -num;

	unsigned long upper_limit = sqrt (num);
	unsigned long factor = 2;

	linked_list_t * factors = linked_list_create ();

	while (num != 1) {
		if (num % factor == 0) {
			unsigned int power = 0;

			while (num % factor == 0) {
				num /= factor;
				power++;
			}

			upper_limit = sqrt (num);

			factor_t * f = linked_list_add_empty (factors, factor_t);

			f->factor = factor;
			f->power = power;
		}

		if (num == 1)
			break;
		else if (++factor > upper_limit) {
			factor_t * f = linked_list_add_empty (factors, factor_t);

			f->factor = num;
			f->power = 1;

			break;
		}
	}

	return factors;
}

int factors_count (long num) {
	linked_list_t * factors = factorise (num);

	int count = 0;

	while (linked_list_next (factors, factor_t))
		count++;

	linked_list_free (factors);

	return count;
}

// Returns the sum of all positive proper divisors of num including 1
long proper_divisors_sum (long num) {
	if (num < 0)
		num = -num;

	long sum = 1;

	long upper_limit = sqrt (num);

	for (long i = 2; i <= upper_limit; i++)
		if (num % i == 0) {
			long div = num / i;

			if (i == div)
				sum += i;
			else
				sum += i + div;
		}

	return sum;
}

// Returns the count of all positive divisors of num including 1 and num
int divisors_count (long num) {
	if (num < 0)
		num = -num;

	if (num <= 1)
		return 1;

	int count = 1;

	linked_list_t * factors = factorise (num);

	factor_t * f = NULL;

	while ((f = linked_list_next (factors, factor_t)) != NULL)
		count *= f->power + 1;

	linked_list_free (factors);

	return count;
}

long gcd (long val_a, long val_b) {
	long a = MAX (ABS (val_a), ABS (val_b));
	long b = MIN (ABS (val_a), ABS (val_b));

	while (b > 0) {
		long rem = a % b;

		a = b;
		b = rem;
	}

	return a;
}

int is_palindrome (int num, int base) {
	if (num < 0)
		num = -num;

	int orig_num = num;
	int rev_num = 0;

	while (num > 0) {
		rev_num *= base;
		rev_num += num % base;
		num /= base;
	}

	return rev_num == orig_num;
}

int is_permutation (int a, int b) {
	char digits[DIGITS_COUNT];

	for (size_t i = 0; i < DIGITS_COUNT; i++)
		digits[i] = 0;

	set_digits (digits, a);
	set_digits (digits, b);

	for (size_t i = 0; i < DIGITS_COUNT; i++)
		if (digits[i] == 1)
			return 0;

	return 1;
}

static void set_digits (char * digits, int num) {
	if (num < 0)
		num = -num;

	while (num > 0) {
		size_t digit = num % 10;
		num /= 10;

		digits[digit] += 1;
	}
}

/*
 * This function can be used for part-wise pandigital checking
 * Call for different values giving the same digits mask
 * Will immeditaly return failure should value contain digits already encountered previously
 * Use panditital_test_digits () to perform a final validation of the mask
 */
int pandigital_test_and_set_digits (char * digits, int value) {
	if (value < 0)
		value = -value;

	while (value > 0) {
		size_t digit = value % 10;
		value /= 10;

		if (digit == 0)
			return 0;
		else if (digits[digit])
			return 0;
		else
			digits[digit] = 1;
	}

	return 1;
}

// Test if the digit mask is 1..N pandigital
int pandigital_test_digits (char * digits, size_t N) {
	for (size_t i = 1; i <= N; i++)
		if (digits[i] == 0)
			return 0;

	for (size_t i = N + 1; i < DIGITS_COUNT; i++)
		if (digits[i] == 1)
			return 0;

	return 1;
}

/*
 * Inplace produce the next lexicographically ordered permutation of a given sequence and return 1
 * Returns 0 and leaves the sequence unchanged when given the already largest possible sequence
 *
 * 1. Find the least significant digit to increase, the one with a less significant and larger digit
 * 2. Swap it with the smallest larger, less significant digit, thus increasing the lexicographical value as little as possible
 * 3. Reverse all the less significant digits, changing them to increasing order, thus starting to permute the tail from the lowest possible value
 */
int next_permutation (char * seq) {
	size_t len = strlen (seq);

	int first_digit_to_increase = -1;

	for (int i = len - 1; i > 0; i--)
		if (seq[i - 1] < seq[i]) {
			first_digit_to_increase = i - 1;
			break;
		}

	if (first_digit_to_increase < 0)
		return 0;

	for (int i = len - 1; i > 0; i--)
		if (seq[i] > seq[first_digit_to_increase]) {
			swap (seq, i, first_digit_to_increase);
			break;
		}

	int i = first_digit_to_increase + 1;
	int j = len - 1;

	while (i < j) {
		swap (seq, i, j);
		i++;
		j--;
	}

	return 1;
}

int prev_permutation (char * seq) {
	size_t len = strlen (seq);

	int first_digit_to_decrease = -1;

	for (int i = len - 1; i > 0; i--)
		if (seq[i - 1] > seq[i]) {
			first_digit_to_decrease = i - 1;
			break;
		}

	if (first_digit_to_decrease < 0)
		return 0;

	for (int i = len - 1; i > 0; i--)
		if (seq[i] < seq[first_digit_to_decrease]) {
			swap (seq, i, first_digit_to_decrease);
			break;
		}

	int i = first_digit_to_decrease + 1;
	int j = len - 1;

	while (i < j) {
		swap (seq, i, j);
		i++;
		j--;
	}

	return 1;
}

unsigned long next_triangle_num () {
	static unsigned long last_index = 0;
	static unsigned long last_num = 0;

	last_num += last_index + 1;
	last_index++;

	return last_num;
}

unsigned long next_pentagonal_num () {
	static unsigned long last_index = 0;
	static unsigned long last_num = 0;

	last_num += 3 * last_index + 1;
	last_index++;

	return last_num;
}

unsigned long next_hexagonal_num () {
	static unsigned long last_index = 0;
	static unsigned long last_num = 0;

	last_num += 4 * last_index + 1;
	last_index++;

	return last_num;
}

unsigned long next_collatz_num (unsigned long x) {
	if (x % 2 == 0)
		return x / 2;
	else
		return x * 3 + 1;
}

// If val is pentagonal there is a positive integer n solving n * (3n - 1) = 2 * val
bool is_pentagonal (unsigned long val) {
	unsigned long discrim = 1 + 24 * val;
	unsigned long larger_root = ROUND ((1 + sqrt (discrim)) / 6);
	unsigned long recomputed_val = larger_root * (3 * larger_root - 1) / 2;

	return val == recomputed_val;
}

// If val is triangular there is a positive integer n solving n * (n + 1) = 2 * val
bool is_triangle (unsigned long val) {
	unsigned long discrim = 1 + 8 * val;
	unsigned long larger_root = ROUND ((-1 + sqrt (discrim)) / 2);
	unsigned long recomputed_val = larger_root * (larger_root + 1) / 2;

	return val == recomputed_val;
}

// Sum an arithmetic sequence from start (inclusive) to end (non-inclusive)
long arithmetic_sequence_sum (long start, long end, long step) {
	if (end <= start)
		return 0;

	long count = 1 + (end - start - 1) / step;
	long last = start + (count - 1) * step;

	return count * (start + last) / 2;
}
