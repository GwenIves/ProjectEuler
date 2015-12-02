/*
 * Find the sum of all positive integers that cannot be represented as a sum of two abundant numbers
 */

#include <stdio.h>
#include "math_utils.h"

#define KNOWN_UPPER_LIMIT	28123

int main (void) {
	long abundant_nums[KNOWN_UPPER_LIMIT];

	size_t abundant_count = 0;

	for (long i = 1; i <= KNOWN_UPPER_LIMIT; i++)
		if (proper_divisors_sum (i) > i)
			abundant_nums[abundant_count++] = i;

	bool candidates[KNOWN_UPPER_LIMIT + 1];

	for (size_t i = 1; i <= KNOWN_UPPER_LIMIT; i++)
		candidates[i] = true;

	for (size_t i = 0; i < abundant_count; i++)
		for (size_t j = i; j < abundant_count; j++) {
			long abundant_sum = abundant_nums[i] + abundant_nums[j];

			if (abundant_sum <= KNOWN_UPPER_LIMIT)
				candidates[abundant_sum] = false;
		}

	long sum = 0;

	for (size_t i = 1; i <= KNOWN_UPPER_LIMIT; i++)
		if (candidates[i])
			sum += i;

	printf ("%ld\n", sum);

	return 0;
}
