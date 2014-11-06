/*
 * Find the sum of all positive integers that cannot be represented as a sum of two abundant numbers
 */

#include <stdio.h>
#include "math_utils.h"

#define KNOWN_UPPER_LIMIT	 28123

int main () {
	int abundant_nums[KNOWN_UPPER_LIMIT];

	size_t abundant_count = 0;

	for (int i = 1; i <= KNOWN_UPPER_LIMIT; i++)
		if (proper_divisors_sum (i) > i)
			abundant_nums[abundant_count++] = i;

	char candidates[KNOWN_UPPER_LIMIT + 1];

	for (int i = 1; i <= KNOWN_UPPER_LIMIT; i++)
		candidates[i] = 1;

	for (int i = 0; i < abundant_count; i++)
		for (int j = i; j < abundant_count; j++) {
			int abundant_sum = abundant_nums[i] + abundant_nums[j];

			if (abundant_sum <= KNOWN_UPPER_LIMIT)
				candidates[abundant_sum] = 0;
		}

	unsigned long sum = 0;

	for (int i = 1; i <= KNOWN_UPPER_LIMIT; i++)
		if (candidates[i])
			sum += i;

	printf ("%lu\n", sum);

	return 0;
}
