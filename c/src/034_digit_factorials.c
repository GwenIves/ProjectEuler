/*
 * Find the sum of all numbers that are equal to the sum of their digits' factorials
 */

#include <stdio.h>
#include "math_utils.h"

int main () {
	int digit_factorials[DIGITS_COUNT];

	digit_factorials[0] = 1;

	for (int i = 1; i < DIGITS_COUNT; i++)
		digit_factorials[i] = i * digit_factorials[i - 1];

	int lowest_pow10 = 1;
	int max_representable = digit_factorials[DIGITS_COUNT - 1];

	while (lowest_pow10 < max_representable) {
		lowest_pow10 *= 10;
		max_representable += digit_factorials[DIGITS_COUNT - 1];
	}

	unsigned long sum = 0;

	for (int i = 10; i <= max_representable; i++) {
		int digits_sum = 0;
		int num = i;

		while (num > 0) {
			int digit = num % 10;

			digits_sum += digit_factorials[digit];

			num /= 10;
		}

		if (digits_sum == i)
			sum += i;
	}

	printf ("%lu\n", sum);

	return 0;
}
