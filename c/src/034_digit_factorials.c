/*
 * Find the sum of all numbers that are equal to the sum of their digits' factorials
 */

#include <stdio.h>
#include "math_utils.h"

#define FACT9	362880

int main () {
	int lowest_pow10 = 10;
	int max_representable = FACT9;

	while (lowest_pow10 <= max_representable) {
		lowest_pow10 *= 10;
		max_representable += FACT9;
	}

	int sum = 0;

	for (int i = 10; i <= max_representable; i++)
		if (i == next_digits_factorial_num (i))
			sum += i;

	printf ("%d\n", sum);

	return 0;
}
