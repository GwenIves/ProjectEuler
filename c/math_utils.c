#include <stdlib.h>
#include <math.h>
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
