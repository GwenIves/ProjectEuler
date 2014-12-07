#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils.h"
#include "math_utils.h"

static void set_digits (char *, int);
static bool mr_test (long, long, long, int);

// Returns an Eratosthenes sieve checkable from 2 (inclusive) to size (non-inclusive)
bool * eratosthenes_sieve (size_t size) {
	if (size < 3)
		return NULL;

	bool * sieve = allocate_array (size, (bool) true);

	sieve[0] = false;
	sieve[1] = false;

	// Deal with even composites separately, then sieve only odds with a step of 2
	for (size_t i = 4; i < size; i += 2)
		sieve[i] = false;

	size_t upper_limit = sqrt (size);
	for (size_t i = 3; i <= upper_limit; i += 2)
		if (sieve[i])
			for (size_t j = i * i; j < size; j += i)
				sieve[j] = false;

	return sieve;
}

// Determines if a number is prime by divisor checking, the caller must guarantee the primes sieve contains entries at least up to sqrt (num) inclusive
bool is_prime (int num, bool * primes, size_t primes_size) {
	if (num < 2)
		return false;
	else if (num <= 3)
		return true;
	else if (num < primes_size)
		return primes[num];
	else if (num % 2 == 0)
		return false;

	int limit = sqrt (num);

	for (int i = 3; i <= limit; i += 2)
		if (primes[i] && num % i == 0)
			return false;

	return true;
}

/*
 * Primeness check for long integers.
 * sieve used as an optimisation for checking under sieve_size, can be NULL, in which case set sieve_size to 0
 * primes[primes_size] are used for divisor checking, only required if num > MILLER_RABIN_DETERMINISTIC_LIMIT
 * in which case the caller must guarantee that the array holds all primes up to and including sqrt (num)
 * Can be NULL otherwise
 */
bool is_prime_long (long num, bool * sieve, size_t sieve_size, int * primes, size_t primes_size) {
	if (num < 2)
		return false;
	else if (num <= 3)
		return true;
	else if (num < sieve_size)
		return sieve[num];
	else if (num % 2 == 0)
		return false;
	else if (num < MILLER_RABIN_DETERMINISTIC_LIMIT)
		return miller_rabin (num);

	long limit = sqrt (num);

	for (size_t i = 0; primes[i] <= limit && i < primes_size; i++)
		if (num % primes[i] == 0)
			return false;

	return true;
}

/*
 * num must be odd >= 3. Represent num as s * 2^r + 1 then check for random bases a, 0 < a < num
 * whether a^s (mod num) == 1 or a^(2^j * s) (mod num) == -1 for some j, 0 < j < r
 * A prime will pass the check for all bases.
 * The limit constants are the smallest composites that successfully pass checks using first k prime bases
 *
 * Returns whether num is prime for num < MILLER_RABIN_DETERMINISTIC_CHECK
 * In other cases returns false for composites and probably true for primes
 */
bool miller_rabin (long num) {
	long s = num;
	long r = 0;

	do {
		s >>= 1;
		r++;
	} while (!(s & 1));

	if (num < 2047L)
		return mr_test (num, r, s, 1);
	else if (num < 1373653L)
		return mr_test (num, r, s, 2);
	else if (num <  25326001L)
		return mr_test (num, r, s, 3);
	else if (num <  3215031751L)
		return mr_test (num, r, s, 4);
	else if (num <  2152302898747L)
		return mr_test (num, r, s, 5);
	else if (num <  3474749660383L)
		return mr_test (num, r, s, 6);
	else
		return mr_test (num, r, s, 7);
}

static bool mr_test (long num, long r, long s, int tests) {
	static int primes[] = {2, 3, 5, 7, 11, 13, 17};

	const long minus1_mod_num = num - 1;

	if (tests > array_len (primes))
		tests = array_len (primes);

	for (int test = 0; test < tests; test++) {
		int a = primes[test];

		long x = mod_pow (a, s, num);

		if (x == 1 || x == minus1_mod_num)
			continue;

		long y = x;
		long j = 1;

		for (j = 1; j < r; j++) {
			y = (y * y) % num;

			if (y == minus1_mod_num)
				break;
		}

		if (j >= r)
			return false;
	}

	return true;
}

// Returns an approximation of the inverse prime counting function - to be used for sizing the Eratosthenes sieve in iterative solutions
// The result is guaranteed to be an upper bound of the true result for the inverse under 10^7
size_t prime_count_inverse (size_t prime_count) {
	if (prime_count < 25)
		return 100;
	else if (prime_count < 168)
		return 1000;
	else if (prime_count < 1229)
		return 10000;
	else if (prime_count < 9592)
		return 100000;
	else if (prime_count < 78498)
		return 1000000;
	else if (prime_count < 664579)
		return 10000000;
	else
		return 100000000;
}

linked_list_t * factorise (long num) {
	if (num < 0)
		num = -num;

	long upper_limit = sqrt (num);
	long factor = 2;

	linked_list_t * factors = linked_list_create ();

	while (num != 1) {
		if (num % factor == 0) {
			int power = 0;

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

long factors_to_value (linked_list_t * factors) {
	long value = 1;

	factor_t * f = NULL;

	while ((f = linked_list_next (factors, factor_t)) != NULL)
		value *= power (f->factor, f->power);

	return value;
}

long factors_to_totient (linked_list_t * factors) {
	long totient = 1;

	factor_t * f = NULL;

	while ((f = linked_list_next (factors, factor_t)) != NULL) {
		totient *= power (f->factor, f->power - 1);
		totient *= f->factor - 1;
	}

	return totient;
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

	if (num <= 1)
		return 1;

	long sum = 1;

	linked_list_t * factors = factorise (num);

	factor_t * f = NULL;

	// The divisor sum is equal to a product of sums of all prime factors' powers
	while ((f = linked_list_next (factors, factor_t)) != NULL) {
		long factor_contrib = 0;
		long power = 1;

		for (int i = 0; i <= f->power; i++) {
			factor_contrib += power;
			power *= f->factor;
		}

		sum *= factor_contrib;
	}

	linked_list_free (factors);

	return sum - num;
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

// Seed abc can generate two palindromes: abccba and abcba, odd_len controls which one is returned
int make_palindrome (int seed, int base, bool odd_len) {
	int palindrome = seed;

	if (odd_len)
		seed /= base;

	while (seed > 0) {
		palindrome *= base;
		palindrome += seed % base;

		seed /= base;
	}

	return palindrome;
}

bool is_palindrome (long num, int base) {
	if (num < 0)
		num = -num;

	return num == reverse (num, base);
}

bool is_permutation (int a, int b) {
	char digits_a[DIGITS_COUNT];
	char digits_b[DIGITS_COUNT];

	memset (digits_a, 0, DIGITS_COUNT);
	memset (digits_b, 0, DIGITS_COUNT);

	set_digits (digits_a, a);
	set_digits (digits_b, b);

	for (size_t i = 0; i < DIGITS_COUNT; i++)
		if (digits_a[i] != digits_b[i])
			return false;

	return true;
}

static void set_digits (char * digits, int num) {
	if (num < 0)
		num = -num;

	while (num > 0) {
		int digit = num % 10;
		num /= 10;

		digits[digit] += 1;
	}
}

bool is_increasing (int num) {
	int prev_digit = num % 10;

	while (num > 0) {
		int digit = num % 10;

		if (digit > prev_digit)
			return false;

		prev_digit = digit;
		num /= 10;
	}

	return true;
}

bool is_decreasing (int num) {
	int prev_digit = num % 10;

	while (num > 0) {
		int digit = num % 10;

		if (digit < prev_digit)
			return false;

		prev_digit = digit;
		num /= 10;
	}

	return true;
}

bool is_bouncy (int num) {
	return (!is_increasing (num) && !is_decreasing (num));
}

long reverse (long num, int base) {
	long rev = 0;

	while (num > 0) {
		int digit = num % base;
		num /= base;

		rev *= base;
		rev += digit;
	}

	return rev;
}

// Concatenate two positive integers
long concatenate (int a, int b) {
	int b_orig = b;

	long result = a;

	while (b > 0) {
		result *= 10;
		b /= 10;
	}

	return result + b_orig;
}

bool is_pandigital (long num, size_t size) {
	char digits[DIGITS_COUNT];

	memset (digits, 0, DIGITS_COUNT);

	if (!pandigital_test_and_set_digits (digits, num))
		return false;
	else
		return pandigital_test_digits (digits, size);
}

/*
 * This function can be used for part-wise pandigital checking
 * Call for different values giving the same digits mask
 * Will immeditaly return failure should value contain digits already encountered previously
 * Use panditital_test_digits () to perform a final validation of the mask
 */
bool pandigital_test_and_set_digits (char * digits, long value) {
	if (value < 0)
		value = -value;

	while (value > 0) {
		int digit = value % 10;
		value /= 10;

		if (digit == 0)
			return false;
		else if (digits[digit])
			return false;
		else
			digits[digit] = 1;
	}

	return true;
}

// Test if the digit mask is 1..N pandigital
bool pandigital_test_digits (char * digits, size_t N) {
	for (size_t i = 1; i <= N; i++)
		if (digits[i] == 0)
			return false;

	for (size_t i = N + 1; i < DIGITS_COUNT; i++)
		if (digits[i] == 1)
			return false;

	return true;
}

/*
 * Inplace produce the next lexicographically ordered permutation of a given sequence and return true
 * Returns 0 and leaves the sequence unchanged when given the already largest possible sequence
 *
 * 1. Find the least significant digit to increase, the one with a less significant and larger digit
 * 2. Swap it with the smallest larger, less significant digit, thus increasing the lexicographical value as little as possible
 * 3. Reverse all the less significant digits, changing them to increasing order, thus starting to permute the tail from the lowest possible value
 */
bool next_permutation (char * seq) {
	size_t len = strlen (seq);

	int first_digit_to_increase = -1;

	for (int i = len - 1; i > 0; i--)
		if (seq[i - 1] < seq[i]) {
			first_digit_to_increase = i - 1;
			break;
		}

	if (first_digit_to_increase < 0)
		return false;

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

	return true;
}

bool prev_permutation (char * seq) {
	size_t len = strlen (seq);

	int first_digit_to_decrease = -1;

	for (int i = len - 1; i > 0; i--)
		if (seq[i - 1] > seq[i]) {
			first_digit_to_decrease = i - 1;
			break;
		}

	if (first_digit_to_decrease < 0)
		return false;

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

	return true;
}

long next_fibonacci_num () {
	static long f1 = 0;
	static long f2 = 1;

	long f = f1 + f2;

	f1 = f2;
	f2 = f;

	return f;
}

long next_triangle_num () {
	static long last_index = 0;
	static long last_num = 0;

	last_num += last_index + 1;
	last_index++;

	return last_num;
}

long next_square_num () {
	static long last_index = 0;

	last_index++;

	return last_index * last_index;
}

long next_pentagonal_num () {
	static long last_index = 0;
	static long last_num = 0;

	last_num += 3 * last_index + 1;
	last_index++;

	return last_num;
}

/*
 * If reset == false, returns the next generalised pentagonal number
 * If reset == true, returns 0 and the next function call will start from the sequence's beginning
 */
int next_generalised_pentagonal_num (bool reset) {
	static int index = 1;

	if (reset) {
		index = 1;
		return 0;
	}

	int num = index * (3 * index - 1) / 2;

	if (index > 0)
		index = -index;
	else
		index = -index + 1;

	return num;
}

long next_hexagonal_num () {
	static long last_index = 0;
	static long last_num = 0;

	last_num += 4 * last_index + 1;
	last_index++;

	return last_num;
}

long next_heptagonal_num () {
	static long last_index = 0;
	static long last_num = 0;

	last_num += 5 * last_index + 1;
	last_index++;

	return last_num;
}

long next_octagonal_num () {
	static long last_index = 0;
	static long last_num = 0;

	last_num += 6 * last_index + 1;
	last_index++;

	return last_num;
}

long next_collatz_num (long x) {
	if (x % 2 == 0)
		return x / 2;
	else
		return x * 3 + 1;
}

int next_digits_factorial_num (int value) {
	static const int factorials[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

	int next = 0;

	while (value > 0) {
		int digit = value % 10;
		value /= 10;

		next += factorials[digit];
	}

	return next;
}

// If val is pentagonal there is a positive integer n solving n * (3n - 1) = 2 * val
bool is_pentagonal (long val) {
	long discrim = 1 + 24 * val;
	long larger_root = ROUND ((1 + sqrt (discrim)) / 6);
	long recomputed_val = larger_root * (3 * larger_root - 1) / 2;

	return val == recomputed_val;
}

// If val is triangular there is a positive integer n solving n * (n + 1) = 2 * val
bool is_triangle (long val) {
	long discrim = 1 + 8 * val;
	long larger_root = ROUND ((-1 + sqrt (discrim)) / 2);
	long recomputed_val = larger_root * (larger_root + 1) / 2;

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

long mod_pow (long num, long pow, long mod) {
	if (num == 0)
		return 0;
	else if (pow == 0)
		return 1;

	long result = 1;

	long power_mask = 1;

	while (power_mask < pow)
		power_mask <<= 1;

	while (power_mask > 0) {
		result = (result * result) % mod;

		if (power_mask & pow)
			result = (result * num) % mod;

		power_mask >>= 1;
	}

	return result;
}

long power (long num, long pow) {
	if (num == 0)
		return 0;
	else if (pow == 0)
		return 1;

	long result = 1;

	long power_mask = 1;

	while (power_mask < pow)
		power_mask <<= 1;

	while (power_mask > 0) {
		result = result * result;

		if (power_mask & pow)
			result = result * num;

		power_mask >>= 1;
	}

	return result;
}

/*
 * Generates a Pythagorean triplet using the Euclid's algorithm with seeds m and n, m > n
 * If m, n generate a primitive triplet, returns true and sets a, b, c to the triplet's values
 * Otherwise, returns false and leaves a, b, c unchanged
 */
bool euclid_pythagorean_triple (int m, int n, int * a, int * b, int * c) {
	if (gcd (m, n) > 1)
		return false;
	else if ((m - n) % 2 == 0)
		return false;

	int m2 = m * m;
	int n2 = n * n;

	*a = m2 - n2;
	*b = 2 * m * n;
	*c = m2 + n2;

	return true;
}

bool is_perfect_square (long num) {
	int last_digit = num % 10;

	if (last_digit == 2 || last_digit == 3 || last_digit == 7 || last_digit == 8)
		return false;

	long root = ROUND (sqrt (num));

	return (root * root == num);
}
