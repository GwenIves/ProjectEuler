#!/bin/env bash

# Library unit tests

./utils_tests || exit 1
./math_utils_tests || exit 1
./fraction_tests || exit 1
./bignum_tests || exit 1

# Project main () tests

assert ()
{
	if [ -z $1 ]
	then
		echo "Invalid assertion at $3"
		exit 1
	elif [ $1 != $2 ]
	then
		echo "Assertion failed at $3"
		exit 1
	fi
}

assert_blank ()
{
	if [ ! -z $1 ]
	then
		echo "Invalid assertion at $2"
		exit 1
	fi
}

assert_fail ()
{
	eval $1 > /dev/null
	assert $? 1 $2
}

assert "$(../src/001_multiples -1)" 0 $LINENO
assert "$(../src/001_multiples 0)" 0 $LINENO
assert "$(../src/001_multiples 10)" 23 $LINENO
assert "$(../src/001_multiples 1000)" 233168 $LINENO

assert "$(../src/002_fibonacci -1)" 0 $LINENO
assert "$(../src/002_fibonacci 0)" 0 $LINENO
assert "$(../src/002_fibonacci 4000000)" 4613732 $LINENO

assert "$(../src/003_prime_factor -1)" 0 $LINENO
assert "$(../src/003_prime_factor 0)" 0 $LINENO
assert "$(../src/003_prime_factor 13195)" 29 $LINENO
assert "$(../src/003_prime_factor 600851475143)" 6857 $LINENO

assert_fail "../src/004_palindrome 0" $LINENO
assert "$(../src/004_palindrome 2)" 9009 $LINENO
assert "$(../src/004_palindrome 3)" 906609 $LINENO

assert_fail "../src/005_multiple 0" $LINENO
assert "$(../src/005_multiple 10)" 2520 $LINENO
assert "$(../src/005_multiple 20)" 232792560 $LINENO

assert_fail "../src/006_square_difference 0" $LINENO
assert "$(../src/006_square_difference 10)" 2640 $LINENO
assert "$(../src/006_square_difference 100)" 25164150 $LINENO

assert_fail "../src/007_prime 0" $LINENO
assert "$(../src/007_prime 6)" 13 $LINENO
assert "$(../src/007_prime 10001)" 104743 $LINENO

assert_fail "../src/008_series 0 < data/008_series.in" $LINENO
assert "$(../src/008_series 4 < data/008_series.in)" 5832 $LINENO
assert "$(../src/008_series 13 < data/008_series.in)" 23514624000 $LINENO

assert_blank "$(../src/009_pythagorean_triplet -1)" $LINENO
assert_blank "$(../src/009_pythagorean_triplet 0)" $LINENO
assert "$(../src/009_pythagorean_triplet 1000)" 31875000 $LINENO

assert "$(../src/010_primes_sum -1)" 0 $LINENO
assert "$(../src/010_primes_sum 0)" 0 $LINENO
assert "$(../src/010_primes_sum 10)" 17 $LINENO
assert "$(../src/010_primes_sum 2000000)" 142913828922 $LINENO

assert_fail "../src/011_grid_product 0 < data/011_grid.in" $LINENO
assert "$(../src/011_grid_product 4 < data/011_grid.in)" 70600674 $LINENO

assert_fail "../src/012_triangular_number -1" $LINENO
assert "$(../src/012_triangular_number 0)" 1 $LINENO
assert "$(../src/012_triangular_number 5)" 28 $LINENO
assert "$(../src/012_triangular_number 500)" 76576500 $LINENO

echo "All tests passed"
exit 0
