#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils.h"
#include "math_utils.h"

char * eratosthenes_sieve (int size) {
	char * sieve = x_malloc (size);

	for (int i = 2; i < size; i++)
		sieve[i] = 1;

	int upper_limit = sqrt (size);
	for (int i = 2; i < upper_limit; i++)
		if (sieve[i])
			for (int j = i * i; j < size; j += i)
				sieve[j] = 0;

	return sieve;
}

int is_prime (char * primes, int num) {
	int limit = sqrt (num);

	for (int i = 2; i <= limit; i++)
		if (primes[i] && num % i == 0)
			return 0;

	return 1;
}

int divisors_sum (int num) {
	int sum = 1;

	int upper_limit = sqrt (num);

	for (int i = 2; i <= upper_limit; i++)
		if (num % i == 0) {
			int div = num / i;

			if (i == div)
				sum += i;
			else
				sum += i + div;
		}

	return sum;
}

int gcd (int val_a, int val_b) {
	int a = MAX (val_a, val_b);
	int b = MIN (val_a, val_b);

	while (b > 0) {
		int rem = a % b;

		a = b;
		b = rem;
	}

	return a;
}

int is_palindrome (int num, int base) {
	int orig_num = num;
	int rev_num = 0;

	while (num > 0) {
		rev_num *= base;
		rev_num += num % base;
		num /= base;
	}

	return rev_num == orig_num;
}

int pandigital_test_and_set_digits (char * digits, int value) {
	while (value > 0) {
		int digit = value % 10;
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

int pandigital_test_digits (char * digits, int N) {
	for (int i = 1; i <= N; i++)
		if (digits[i] == 0)
			return 0;

	for (int i = N + 1; i < DIGITS_COUNT; i++)
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
			swap_chars (seq, i, first_digit_to_increase);
			break;
		}

	int i = first_digit_to_increase + 1;
	int j = len - 1;

	while (i < j) {
		swap_chars (seq, i, j);
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
			swap_chars (seq, i, first_digit_to_decrease);
			break;
		}

	int i = first_digit_to_decrease + 1;
	int j = len - 1;

	while (i < j) {
		swap_chars (seq, i, j);
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
