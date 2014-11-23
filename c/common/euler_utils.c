#include "euler_utils.h"
#include "math_utils.h"
#include "utils.h"

static int ** crc_allocate_cache (size_t, size_t);
static void crc_free_cache (int **, size_t);

/*
 * Computes the number of proper reduced fractions in the Stern-Brocot tree with denominators <= max_denominator and values between and excluding above and below
 * Both above and below must be nodes of some Stern-Brocot tree
 */
long stern_brocot_count (long max_denominator, fraction_t * above, fraction_t * below) {
	fraction_t mediant = fraction_get_ (above->nominator + below->nominator, above->denominator + below->denominator, false);

	if (mediant.denominator > max_denominator)
		return 0;
	else
		return stern_brocot_count (max_denominator, above, &mediant) + stern_brocot_count (max_denominator, &mediant, below) + 1;
}

/*
 * Generates a Pythagorean triplet using the Euclid's algorithm with seeds m and n, m > n
 * If m, n generate a primitive triplet, returns the triplet's sum (triangle perimeter)
 * Otherwise, returns 0
 */
int euclid_pythagorean_triple_perim (int m, int n) {
	if (gcd (m, n) > 1)
		return 0;
	else if ((m - n) % 2 == 0)
		return 0;

	int m2 = m * m;
	int n2 = n * n;

	int a = m2 - n2;
	int b = 2 * m * n;
	int c = m2 + n2;

	return a + b + c;
}

/*
 * Returns how many combinations exist of representing "sum" as a summation of values from the "values" array
 * using elements up to the "max_value" index
 */
int count_representation_combinations (int * values, int max_value, int sum, int ** cache) {
	int combinations = 0;
	bool allocated_cache = false;

	if (cache == NULL) {
		allocated_cache = true;
		cache = crc_allocate_cache (max_value + 1, sum + 1);
	}

	if (cache[max_value][sum] == -1) {
		// One representation using only max_value coins
		if (sum > 0 && sum % values[max_value] == 0)
			combinations++;

		if (max_value > 0) {
			int remaining_sum = sum;

			while (remaining_sum > 0) {
				combinations += count_representation_combinations (values, max_value - 1, remaining_sum, cache);
				remaining_sum -= values[max_value];
			}
		}

		cache[max_value][sum] = combinations;
	} else
		combinations = cache[max_value][sum];

	if (allocated_cache)
		crc_free_cache (cache, max_value + 1);

	return combinations;
}

static int ** crc_allocate_cache (size_t rows, size_t columns) {
	int ** cache = x_malloc (rows * sizeof (int *));

	for (size_t i = 0; i < rows; i++) {
		cache[i] = x_malloc (columns * sizeof (int));

		for (size_t j = 0; j < columns; j++)
			cache[i][j] = -1;
	}

	return cache;
}

static void crc_free_cache (int ** cache, size_t rows) {
	free_array (cache, rows);
	free (cache);
}
