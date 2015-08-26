#include <math.h>
#include "linked_list.h"
#include "bignum.h"
#include "euler_utils.h"
#include "math_utils.h"
#include "utils.h"

static void extend_repunit (int *, int *, int, int);
static bool is_repunit (int);
static long p114_count_arrangements_aux (int, int, long *);

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

long euclid_pythagorean_triple_perim (int m, int n) {
	long a = 0;
	long b = 0;
	long c = 0;

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

// "set" should be sorted in increasing order
bool is_special_sum_set (const int * set, size_t size) {
	if (size < 2)
		return true;

	/*
	 * Establish whether for all non-empty, disjoint subsets A, B, |A| > |B| => S(A) > S(B)
	 * Should this property hold for all A, B where A contains x smallest items and B
	 * x - 1 largest items from the set, then it holds for all required subsets
	 */
	int sum_smallest = set[0];
	int sum_largest = 0;

	for (size_t i = 1, j = size - 1; i < j; i++, j--) {
		sum_smallest += set[i];
		sum_largest += set[j];

		if (sum_smallest <= sum_largest)
			return false;
	}

	/*
	 * Establish whether for all non-empty, disjoint subsets A, B, S(A) != S(B)
	 * Since we have already established that non-empty, disjoint subsets of different
	 * magnitudes have different sums, we only need to check subsets of the same magnitude here
	 */
	for (size_t i = 2; i <= size / 2; i++) {
		char subsets_mask[size + 1];

		for (size_t j = 0; j < i; j++)
			subsets_mask[j] = '2';

		for (size_t j = i; j < i + i; j++)
			subsets_mask[j] = '1';

		for (size_t j = i + i; j < size; j++)
			subsets_mask[j] = '0';

		subsets_mask[size] = '\0';

		do {
			int sum1 = 0;
			int sum2 = 0;

			for (size_t j = 0; j < size; j++)
				if (subsets_mask[j] == '1')
					sum1 += set[j];
				else if (subsets_mask[j] == '2')
					sum2 += set[j];

			if (sum1 == sum2)
				return false;
		} while (prev_permutation (subsets_mask));
	}

	return true;
}

int digits_sum (long n) {
	if (n < 0)
		n = -n;

	int sum = 0;

	while (n > 0) {
		sum += n % 10;
		n /= 10;
	}

	return sum;
}

long evaluate_factorisation (const int * factors, const int * powers, size_t count) {
	long val = 1;

	for (size_t i = 0; i < count; i++)
		val *= power (factors[i], powers[i]);

	return val;
}

/*
 * Find the shortest repunit that is a multiple of 'divisor'
 *
 * Keep determining a quotient longhand division style walking through the
 * repunit digits until the remainder is 0
 */
int get_repunit_len (int divisor) {
	if (divisor % 2 == 0 || divisor % 5 == 0)
		return 0;
	else if (is_repunit (divisor))
		return integer_log10 (divisor) + 1;

	int last_divisor_digit = divisor % 10;

	int repunit = 1;
	int prev_repunit = -1;
	int len = 1;

	while (repunit % divisor != 0) {
		int quotient_digit = mult_digits[repunit % 10][last_divisor_digit];
		int product = quotient_digit * divisor;

		if (repunit < product) {
			extend_repunit (&repunit, &len, product, prev_repunit);
			prev_repunit = repunit;
		}

		repunit -= product;

		repunit /= 10;
		prev_repunit /= 10;
	}

	return len;
}

static void extend_repunit (int * cur_repunit, int * len, int product, int prev_repunit) {
	int order = 1;
	int extension = 1;

	if (prev_repunit < 0)
		while (order <= *cur_repunit)
			order *= 10;
	else
		while (prev_repunit > 0) {
			prev_repunit /= 10;
			order *= 10;
		}

	int repunit = order;

	while (repunit + *cur_repunit < product) {
		order *= 10;
		repunit += order;
		extension++;
	}

	*cur_repunit += repunit;
	*len += extension;
}

static bool is_repunit (int num) {
	switch (num) {
		case 1:
		case 11:
		case 111:
		case 1111:
		case 11111:
		case 111111:
		case 1111111:
		case 11111111:
		case 111111111:
		case 1111111111:
			return true;
		default:
			return false;
	}
}

/*
 * Specialised routines useful for a series of related problems
 * but of little general interest.
 *
 * All exported names are of the form:
 * p<Euler problem number>_<function_name>
 *
 * See comments in the referenced problems for more details
 */

long p114_count_arrangements (int size, int min_block) {
	long cache[size + 2];

	for (int i = 0; i < size + 2; i++)
		cache[i] = -1;

	return p114_count_arrangements_aux (size + 1, min_block, cache);
}

/*
 * We are going to calculate the count recursively noting that:
 *   Rows shorter than min_block can only be filled in one way - all gaps
 *   Longer rows can be formed by either appending a gap or a block of
 *   any size plus a gap to a shorter row
 * The algorithm will place one unnecessary gap in the last step, so
 * the size passed to the initial call should be one above the required size
 */
static long p114_count_arrangements_aux (int size, int min_block, long * cache) {
	if (size < min_block)
		return 1;
	else if (cache[size] != -1)
		return cache[size];
	else {
		long count = p114_count_arrangements_aux (size - 1, min_block, cache);

		for (int block_size = min_block + 1; block_size <= size; block_size++)
			count += p114_count_arrangements_aux (size - block_size, min_block, cache);

		cache[size] = count;

		return count;
	}
}
