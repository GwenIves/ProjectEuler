#include <math.h>
#include "linked_list.h"
#include "bignum.h"
#include "euler_utils.h"
#include "math_utils.h"
#include "utils.h"

/*
 * Computes the number of proper reduced fractions in the Stern-Brocot tree with denominators <= max_denominator and values between and excluding above and below
 * Both above and below must be nodes of some Stern-Brocot tree
 */
long stern_brocot_count (long max_denominator, const fraction_t * above, const fraction_t * below) {
	fraction_t mediant = fraction_get_ (above->nominator + below->nominator, above->denominator + below->denominator, false);

	if (mediant.denominator > max_denominator)
		return 0;
	else
		return stern_brocot_count (max_denominator, above, &mediant) + stern_brocot_count (max_denominator, &mediant, below) + 1;
}

int euclid_pythagorean_triple_perim (int m, int n) {
	int a = 0;
	int b = 0;
	int c = 0;

	if (euclid_pythagorean_triple (m, n, &a, &b, &c))
		return a + b + c;
	else
		return 0;
}

/*
 * Iteratively computes sqrt (num) using a digit-by-digit method to the requested number of digits
 * Returns a dynamically allocated string that should be freed by the caller
 *
 * 1. Bring down the most significant remaining pair of digits from num, or 00 if none, and append to the remainder
 * 2. Find the largest x, such that x * (20p + x) <= remainder, where p is the sqrt determined so far, ignoring the decimal point
 * 3. x is the new digit of sqrt, subtract the product from 2. from the remainder
 */
char * calculate_sqrt (int num, size_t digits_to_calculate) {
	size_t size = log10 (num) + digits_to_calculate + 3;

	char * sqrt = x_malloc (size);
	size_t index = 0;
	size_t digits = 0;

	linked_list_t * digit_pairs = linked_list_create ();

	while (num > 0) {
		int * p_ptr = linked_list_add_empty (digit_pairs, int);

		*p_ptr = num % 100;
		num /= 100;
	}

	bignum_t * const20 = bignum_get (20);
	bignum_t * remainder = bignum_get (0);
	bignum_t * sqrt_so_far = bignum_get (0);

	while (digits < digits_to_calculate) {
		remainder = bignum_mult_to (remainder, 100);

		if (digit_pairs) {
			int * p_ptr = linked_list_next (digit_pairs, int);

			if (p_ptr)
				remainder = bignum_add_to (remainder, bignum_get (*p_ptr));
			else {
				sqrt[index++] = '.';
				linked_list_free (digit_pairs);
				digit_pairs = NULL;
			}
		}

		int x = 1;
		bignum_t * y = bignum_get (0);
		bignum_t * p20 = bignum_mult (const20, sqrt_so_far);

		while (true) {
			bignum_t * bx = bignum_get (x);
			bignum_t * y_next = bignum_add (p20, bx);
			y_next = bignum_mult_to (y_next, bx);

			bignum_delete (bx);

			if (bignum_cmp (y_next, remainder) > 0) {
				bignum_delete (y_next);
				break;
			}

			bignum_delete (y);
			y = y_next;

			x++;
		}

		x--;

		sqrt[index++] = x + '0';

		sqrt_so_far = bignum_mult_to (sqrt_so_far, 10);
		sqrt_so_far = bignum_add_to (sqrt_so_far, bignum_get (x));

		remainder = bignum_add_to (remainder, bignum_mult (y, -1));

		bignum_delete (y);
		bignum_delete (p20);

		if (bignum_is_digit (remainder, 0))
			break;

		digits++;
	}

	sqrt[index] = '\0';

	bignum_delete (const20);
	bignum_delete (remainder);
	bignum_delete (sqrt_so_far);

	return sqrt;
}

/*
 * Returns how many combinations exist of representing "sum" as a summation of values from the "values" array
 * using elements up to the "max_value" index
 */
int count_representation_combinations_ (const int * values, size_t max_value, int sum, int ** cache) {
	int combinations = 0;
	bool allocated_cache = false;

	if (cache == NULL) {
		allocated_cache = true;
		cache = allocate_matrix (max_value + 1, sum + 1, -1);
	}

	if (cache[max_value][sum] == -1) {
		// One representation using only max_value coins
		if (sum > 0 && sum % values[max_value] == 0)
			combinations++;

		if (max_value > 0) {
			int remaining_sum = sum;
			size_t next_max_value = max_value - 1;

			while (remaining_sum > 0) {
				while (next_max_value > 0 && values[next_max_value] > remaining_sum)
					next_max_value--;

				combinations += count_representation_combinations_ (values, next_max_value, remaining_sum, cache);
				remaining_sum -= values[max_value];
			}
		}

		cache[max_value][sum] = combinations;
	} else
		combinations = cache[max_value][sum];

	if (allocated_cache)
		free_matrix (cache, max_value + 1);

	return combinations;
}
