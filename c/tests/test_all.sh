#!/bin/env bash

# Library unit tests

echo "Running library unit tests"

./utils_tests || exit 1
./linked_list_tests || exit 1
./math_utils_tests || exit 1
./euler_utils_tests || exit 1
./date_utils_tests || exit 1
./fraction_tests || exit 1
./continued_fraction_tests || exit 1
./bignum_tests || exit 1
./geometry_tests || exit 1

# Project main () tests

assert ()
{
	if [ -z "$1" ]
	then
		echo "Invalid assertion at $3"
		exit 1
	elif [ "$1" != "$2" ]
	then
		echo "Assertion failed at $3"
		exit 1
	fi
}

assert_blank ()
{
	result=$(eval $1)

	if [ $? == 127 ]
	then
		echo "Invalid assertion at $2"
		exit 1
	elif [ ! -z "$result" ]
	then
		echo "Assertion failed at $2"
		exit 1
	fi
}

assert_fail ()
{
	eval $1 > /dev/null 2>&1 

	result=$?

	if [ $result == 127 -o $result == 139 ]
	then
		echo "Invalid assertion at $2"
		exit 1
	elif [ $result == 0 ]
	then
		echo "Assertion failed at $2"
		exit 1
	fi
}

echo "Running program tests"

# The blank reference variable is a marker for use by an external performance report script,

assert "$(../src/001_multiples -1)" 0 $LINENO
assert "$(../src/001_multiples 0)" 0 $LINENO
assert "$(../src/001_multiples 10)" 23 $LINENO
assert "$(../src/001_multiples 1000)" 233168 $LINENO $REFERENCE

assert "$(../src/002_fibonacci -1)" 0 $LINENO
assert "$(../src/002_fibonacci 0)" 0 $LINENO
assert "$(../src/002_fibonacci 4000000)" 4613732 $LINENO $REFERENCE

assert "$(../src/003_prime_factor -1)" 0 $LINENO
assert "$(../src/003_prime_factor 0)" 0 $LINENO
assert "$(../src/003_prime_factor 13195)" 29 $LINENO
assert "$(../src/003_prime_factor 600851475143)" 6857 $LINENO $REFERENCE

assert_fail "../src/004_palindrome 0" $LINENO
assert "$(../src/004_palindrome 2)" 9009 $LINENO
assert "$(../src/004_palindrome 3)" 906609 $LINENO $REFERENCE

assert_fail "../src/005_multiple 0" $LINENO
assert "$(../src/005_multiple 10)" 2520 $LINENO
assert "$(../src/005_multiple 20)" 232792560 $LINENO $REFERENCE

assert_fail "../src/006_square_difference 0" $LINENO
assert "$(../src/006_square_difference 10)" 2640 $LINENO
assert "$(../src/006_square_difference 100)" 25164150 $LINENO $REFERENCE

assert_fail "../src/007_prime 0" $LINENO
assert "$(../src/007_prime 6)" 13 $LINENO
assert "$(../src/007_prime 10001)" 104743 $LINENO $REFERENCE

assert_fail "../src/008_series 0 < data/008_series.in" $LINENO
assert_fail "../src/008_series 1 < /dev/null" $LINENO
assert "$(../src/008_series 4 < data/008_series.in)" 5832 $LINENO
assert "$(../src/008_series 13 < data/008_series.in)" 23514624000 $LINENO $REFERENCE

assert_blank "../src/009_pythagorean_triplet -1" $LINENO
assert_blank "../src/009_pythagorean_triplet 0" $LINENO
assert "$(../src/009_pythagorean_triplet 1000)" 31875000 $LINENO $REFERENCE

assert "$(../src/010_primes_sum -1)" 0 $LINENO
assert "$(../src/010_primes_sum 0)" 0 $LINENO
assert "$(../src/010_primes_sum 10)" 17 $LINENO
assert "$(../src/010_primes_sum 2000000)" 142913828922 $LINENO $REFERENCE

assert_fail "../src/011_grid_product 0 < data/011_grid.in" $LINENO
assert_fail "../src/011_grid_product 1 < /dev/null" $LINENO
assert "$(../src/011_grid_product 4 < data/011_grid.in)" 70600674 $LINENO $REFERENCE

assert_fail "../src/012_triangular_number -1" $LINENO
assert "$(../src/012_triangular_number 0)" 1 $LINENO
assert "$(../src/012_triangular_number 5)" 28 $LINENO
assert "$(../src/012_triangular_number 500)" 76576500 $LINENO $REFERENCE

assert "$(../src/013_large_sum < /dev/null)" 0 $LINENO
assert "$(../src/013_large_sum < data/013_nums.in)" 5537376230390876637302048746832985971773659831892672 $LINENO $REFERENCE

assert_fail "../src/014_collatz_sequence 1" $LINENO
assert "$(../src/014_collatz_sequence 1000000)" 837799 $LINENO $REFERENCE

assert_fail "../src/015_lattice_paths 0" $LINENO
assert "$(../src/015_lattice_paths 3)" 6 $LINENO
assert "$(../src/015_lattice_paths 21)" 137846528820 $LINENO $REFERENCE

assert_fail "../src/016_power_digit_sum -1" $LINENO
assert "$(../src/016_power_digit_sum 0)" 1 $LINENO
assert "$(../src/016_power_digit_sum 15)" 26 $LINENO
assert "$(../src/016_power_digit_sum 1000)" 1366 $LINENO $REFERENCE

assert_fail "../src/017_number_letters 1000000" $LINENO
assert "$(../src/017_number_letters -1)" "minus one" $LINENO
assert "$(../src/017_number_letters 0)" "zero" $LINENO
assert "$(../src/017_number_letters 123456)" "one hundert twenty three thousand four hundert and fifty six" $LINENO $REFERENCE

assert_fail "../src/018_maximum_path < /dev/null" $LINENO
assert "$(../src/018_maximum_path < data/018_triangle.in)" 1074 $LINENO $REFERENCE

assert_fail "../src/019_day_count -1" $LINENO
assert_fail "../src/019_day_count 7" $LINENO
assert "$(../src/019_day_count 6)" 171 $LINENO $REFERENCE

assert_fail "../src/020_factorial 0" $LINENO
assert "$(../src/020_factorial 10)" 27 $LINENO
assert "$(../src/020_factorial 100)" 648 $LINENO $REFERENCE

assert_fail "../src/021_amicable_numbers 0" $LINENO
assert "$(../src/021_amicable_numbers 10000)" 31626 $LINENO $REFERENCE

assert_fail "../src/022_name_scoring < /dev/null" $LINENO
assert "$(../src/022_name_scoring < data/022_names.in)" 871198282 $LINENO $REFERENCE

assert "$(../src/023_non_abundant)" 4179871 $LINENO $REFERENCE

assert_fail "../src/024_permutations 0" $LINENO
assert "$(../src/024_permutations 1000000)" 2783915460 $LINENO $REFERENCE
assert "$(../src/024_permutations 3628800)" 9876543210 $LINENO
assert_fail "../src/024_permutations 3628801" $LINENO

assert_fail "../src/025_fibonacci 0" $LINENO
assert "$(../src/025_fibonacci 1)" 1 $LINENO
assert "$(../src/025_fibonacci 3)" 12 $LINENO
assert "$(../src/025_fibonacci 1000)" 4782 $LINENO $REFERENCE

assert_fail "../src/026_recurring_cycles 0" $LINENO
assert "$(../src/026_recurring_cycles 1000)" 983 $LINENO $REFERENCE

assert_fail "../src/027_quadratic_primes 1" $LINENO
assert "$(../src/027_quadratic_primes 42)" -41 $LINENO
assert "$(../src/027_quadratic_primes 1000)" -59231 $LINENO $REFERENCE

assert_fail "../src/028_number_spiral 0" $LINENO
assert_fail "../src/028_number_spiral 2" $LINENO
assert "$(../src/028_number_spiral 5)" 101 $LINENO
assert "$(../src/028_number_spiral 1001)" 669171001 $LINENO $REFERENCE

assert_fail "../src/029_powers 1" $LINENO
assert "$(../src/029_powers 5)" 15 $LINENO
assert "$(../src/029_powers 100)" 9183 $LINENO $REFERENCE

assert "$(../src/030_digit_powers -1)" 0 $LINENO
assert "$(../src/030_digit_powers 0)" 0 $LINENO
assert "$(../src/030_digit_powers 4)" 19316 $LINENO
assert "$(../src/030_digit_powers 5)" 443839 $LINENO $REFERENCE

assert_fail "../src/031_coins 0" $LINENO
assert "$(../src/031_coins 200)" 73682 $LINENO $REFERENCE

assert_fail "../src/032_pandigital 0" $LINENO
assert_fail "../src/032_pandigital 10" $LINENO
assert "$(../src/032_pandigital 9)" 45228 $LINENO $REFERENCE

assert_fail "../src/033_digit_cancelling 0" $LINENO
assert "$(../src/033_digit_cancelling 2)" 100 $LINENO $REFERENCE

assert "$(../src/034_digit_factorials)" 40730 $LINENO $REFERENCE

assert "$(../src/035_circular_primes -1)" 0 $LINENO
assert "$(../src/035_circular_primes 0)" 0 $LINENO
assert "$(../src/035_circular_primes 100)" 13 $LINENO
assert "$(../src/035_circular_primes 1000000)" 55 $LINENO $REFERENCE

assert_fail "../src/036_palindromes 0" $LINENO
assert "$(../src/036_palindromes 1000000)" 872187 $LINENO $REFERENCE

assert "$(../src/037_truncatable_primes)" 748317 $LINENO $REFERENCE

assert_fail "../src/038_pandigital 0" $LINENO
assert_fail "../src/038_pandigital 10" $LINENO
assert "$(../src/038_pandigital 9)" 932718654 $LINENO $REFERENCE

assert_fail "../src/039_triangles -1" $LINENO
assert_fail "../src/039_triangles 0" $LINENO
assert_fail "../src/039_triangles 2" $LINENO
assert "$(../src/039_triangles 1000)" 840 $LINENO $REFERENCE

assert_fail "../src/040_champernowne -1" $LINENO
assert_fail "../src/040_champernowne 0" $LINENO
assert "$(../src/040_champernowne 1)" 1 $LINENO
assert "$(../src/040_champernowne 6)" 210 $LINENO $REFERENCE

assert_fail "../src/041_pandigital_prime 0" $LINENO
assert_fail "../src/041_pandigital_prime 10" $LINENO
assert "$(../src/041_pandigital_prime 7)" 7652413 $LINENO $REFERENCE

assert "$(../src/042_triangle_words < /dev/null)" 0 $LINENO
assert "$(../src/042_triangle_words < data/042_words.in)" 162 $LINENO $REFERENCE

assert "$(../src/043_substrings)" 16695334890 $LINENO $REFERENCE

assert "$(../src/044_pentagon_numbers)" 5482660 $LINENO $REFERENCE

assert_fail "../src/045_geometric_numbers 0" $LINENO
assert "$(../src/045_geometric_numbers 1)" 1 $LINENO
assert "$(../src/045_geometric_numbers 2)" 40755 $LINENO
assert "$(../src/045_geometric_numbers 3)" 1533776805 $LINENO $REFERENCE

assert "$(../src/046_goldbach)" 5777 $LINENO $REFERENCE

assert_fail "../src/047_prime_factors 0" $LINENO
assert "$(../src/047_prime_factors 1)" 2 $LINENO
assert "$(../src/047_prime_factors 2)" 14 $LINENO
assert "$(../src/047_prime_factors 3)" 644 $LINENO
assert "$(../src/047_prime_factors 4)" 134043 $LINENO $REFERENCE

assert_fail "../src/048_self_powers 0" $LINENO
assert "$(../src/048_self_powers 1000)" 9110846700 $LINENO $REFERENCE

assert_fail "../src/049_permutations 0" $LINENO
assert "$(../src/049_permutations 4)" 296962999629 $LINENO $REFERENCE

assert_fail "../src/050_prime_sum 2" $LINENO
assert "$(../src/050_prime_sum 100)" 41 $LINENO
assert "$(../src/050_prime_sum 1000)" 953 $LINENO
assert "$(../src/050_prime_sum 1000000)" 997651 $LINENO $REFERENCE

assert_fail "../src/051_prime_families 0" $LINENO
assert_fail "../src/051_prime_families 11" $LINENO
assert "$(../src/051_prime_families 6)" 13 $LINENO
assert "$(../src/051_prime_families 7)" 56003 $LINENO
assert "$(../src/051_prime_families 8)" 121313 $LINENO $REFERENCE

assert_fail "../src/052_multiples_permutations 0" $LINENO
assert "$(../src/052_multiples_permutations 1)" 1 $LINENO
assert "$(../src/052_multiples_permutations 2)" 125874 $LINENO
assert "$(../src/052_multiples_permutations 6)" 142857 $LINENO $REFERENCE

assert_fail "../src/053_selections 0" $LINENO
assert "$(../src/053_selections 22)" 0 $LINENO
assert "$(../src/053_selections 100)" 4075 $LINENO $REFERENCE

assert "$(../src/054_poker < /dev/null)" 0 $LINENO
assert "$(../src/054_poker < data/054_hands.in)" 376 $LINENO $REFERENCE

assert_fail "../src/055_lychrel 1" $LINENO
assert "$(../src/055_lychrel 200)" 1 $LINENO
assert "$(../src/055_lychrel 10000)" 249 $LINENO $REFERENCE

assert_fail "../src/056_power_digit_sum 0" $LINENO
assert "$(../src/056_power_digit_sum 100)" 972 $LINENO $REFERENCE

assert_fail "../src/057_square_root 0" $LINENO
assert "$(../src/057_square_root 7)" 0 $LINENO
assert "$(../src/057_square_root 8)" 1 $LINENO
assert "$(../src/057_square_root 1000)" 153 $LINENO $REFERENCE

assert_fail "../src/058_number_spiral -1" $LINENO
assert_fail "../src/058_number_spiral 101" $LINENO
assert "$(../src/058_number_spiral 65)" 3 $LINENO
assert "$(../src/058_number_spiral 10)" 26241 $LINENO $REFERENCE

assert_fail "../src/059_xor 0 < /dev/null" $LINENO
assert_blank "../src/059_xor 1 < /dev/null" $LINENO
assert "$(../src/059_xor 3 < data/059_encrypted.in)" 107359 $LINENO $REFERENCE

assert_fail "../src/060_prime_pairs 1" $LINENO
assert "$(../src/060_prime_pairs 4)" 792 $LINENO
assert "$(../src/060_prime_pairs 5)" 26033 $LINENO $REFERENCE

assert_fail "../src/061_cyclical_polygonals 3" $LINENO
assert "$(../src/061_cyclical_polygonals 4)" 28684 $LINENO $REFERENCE

assert_fail "../src/062_cubic_permutations 0" $LINENO
assert "$(../src/062_cubic_permutations 3)" 41063625 $LINENO
assert "$(../src/062_cubic_permutations 5)" 127035954683 $LINENO $REFERENCE

assert "$(../src/063_powers)" 49 $LINENO $REFERENCE

assert_fail "../src/064_irrational_fractions 0" $LINENO
assert "$(../src/064_irrational_fractions 13)" 4 $LINENO
assert "$(../src/064_irrational_fractions 10000)" 1322 $LINENO $REFERENCE

assert_fail "../src/065_e 0" $LINENO
assert "$(../src/065_e 10)" 17 $LINENO
assert "$(../src/065_e 100)" 272 $LINENO $REFERENCE

assert_fail "../src/066_pell 0" $LINENO
assert "$(../src/066_pell 7)" 5 $LINENO
assert "$(../src/066_pell 1000)" 661 $LINENO $REFERENCE

# Problem 67 can be solved reusing the code for problem 18
assert "$(../src/018_maximum_path < data/067_triangle.in)" 7273 $LINENO $REFERENCE

assert "$(../src/068_magic_ring)" 6531031914842725 $LINENO $REFERENCE

assert_fail "../src/069_totient 0" $LINENO
assert "$(../src/069_totient 10)" 6 $LINENO
assert "$(../src/069_totient 1000000)" 510510 $LINENO $REFERENCE

assert_fail "../src/070_totient_permutations 1" $LINENO
assert "$(../src/070_totient_permutations 10000000)" 8319823 $LINENO $REFERENCE

assert_fail "../src/071_ordered_fractions 0" $LINENO
assert "$(../src/071_ordered_fractions 8)" 2 $LINENO
assert "$(../src/071_ordered_fractions 1000000)" 428570 $LINENO $REFERENCE

assert_fail "../src/072_fractions_count 0" $LINENO
assert "$(../src/072_fractions_count 8)" 21 $LINENO
assert "$(../src/072_fractions_count 1000000)" 303963552391 $LINENO $REFERENCE

assert_fail "../src/073_fractions_range 0" $LINENO
assert "$(../src/073_fractions_range 8)" 3 $LINENO
assert "$(../src/073_fractions_range 12000)" 7295372 $LINENO $REFERENCE

assert_fail "../src/074_digit_factorials 1" $LINENO
assert "$(../src/074_digit_factorials 1000000)" 402 $LINENO $REFERENCE

assert_fail "../src/075_triangles 2" $LINENO
assert "$(../src/075_triangles 1500000)" 161667 $LINENO $REFERENCE

assert_fail "../src/076_summations 0" $LINENO
assert "$(../src/076_summations 5)" 6 $LINENO
assert "$(../src/076_summations 100)" 190569291 $LINENO $REFERENCE

assert_fail "../src/077_prime_summations 0" $LINENO
assert "$(../src/077_prime_summations 5)" 10 $LINENO
assert "$(../src/077_prime_summations 5000)" 71 $LINENO $REFERENCE

assert_fail "../src/078_partitions 0" $LINENO
assert "$(../src/078_partitions 1000000)" 55374 $LINENO $REFERENCE

assert_blank "../src/079_passcode < /dev/null" $LINENO
assert "$(../src/079_passcode < data/079_subsequences.in)" 73162890 $LINENO $REFERENCE

assert_blank "../src/080_square_roots 0" $LINENO
assert "$(../src/080_square_roots 2)" 475 $LINENO
assert "$(../src/080_square_roots 100)" 40886 $LINENO $REFERENCE

assert_fail "../src/081_minimum_path < /dev/null" $LINENO
assert "$(../src/081_minimum_path < data/081_matrix.in)" 427337 $LINENO $REFERENCE

assert_fail "../src/082_minimum_path < /dev/null" $LINENO
assert "$(../src/082_minimum_path < data/081_matrix.in)" 260324 $LINENO $REFERENCE

assert_fail "../src/083_minimum_path < /dev/null" $LINENO
assert "$(../src/083_minimum_path < data/081_matrix.in)" 425185 $LINENO $REFERENCE

assert_fail "../src/084_monopoly 1" $LINENO
assert "$(../src/084_monopoly 6)" 102400 $LINENO
assert "$(../src/084_monopoly 4)" 101524 $LINENO $REFERENCE

assert_fail "../src/085_rectangles 0" $LINENO
assert "$(../src/085_rectangles 18)" 6 $LINENO
assert "$(../src/085_rectangles 2000000)" 2772 $LINENO $REFERENCE

assert "$(../src/086_cuboids -1)" 1 $LINENO
assert "$(../src/086_cuboids 0)" 3 $LINENO
assert "$(../src/086_cuboids 2000)" 100 $LINENO
assert "$(../src/086_cuboids 1000000)" 1818 $LINENO $REFERENCE

assert_fail "../src/087_prime_powers 0" $LINENO
assert "$(../src/087_prime_powers 50)" 4 $LINENO
assert "$(../src/087_prime_powers 50000000)" 1097343 $LINENO $REFERENCE

assert_fail "../src/088_product_sum_numbers 1" $LINENO
assert "$(../src/088_product_sum_numbers 12)" 61 $LINENO
assert "$(../src/088_product_sum_numbers 12000)" 7587457 $LINENO $REFERENCE

assert "$(../src/089_roman_numerals < /dev/null)" 0 $LINENO
assert "$(../src/089_roman_numerals < data/089_numerals.in)" 743 $LINENO $REFERENCE

assert "$(../src/090_cube_pairs)" 1217 $LINENO $REFERENCE

assert_fail "../src/091_triangles -1" $LINENO
assert "$(../src/091_triangles 0)" 0 $LINENO
assert "$(../src/091_triangles 2)" 14 $LINENO
assert "$(../src/091_triangles 50)" 14234 $LINENO $REFERENCE

assert_fail "../src/092_unhappy 1" $LINENO
assert "$(../src/092_unhappy 10000000)" 8581146 $LINENO $REFERENCE

assert_fail "../src/093_expressions 3" $LINENO
assert "$(../src/093_expressions 9)" 1258 $LINENO $REFERENCE

assert "$(../src/094_triangles -1)" 0 $LINENO
assert "$(../src/094_triangles 17)" 16 $LINENO
assert "$(../src/094_triangles 1000000000)" 518408346 $LINENO $REFERENCE

assert_fail "../src/095_amicable_chains 0" $LINENO
assert "$(../src/095_amicable_chains 284)" 220 $LINENO
assert "$(../src/095_amicable_chains 1000000)" 14316 $LINENO $REFERENCE

assert "$(../src/096_sudoku < /dev/null)" 0 $LINENO
assert "$(../src/096_sudoku < data/096_sudoku.in)" 24702 $LINENO $REFERENCE

assert "$(../src/097_non_mersenne_prime)" 8739992577 $LINENO $REFERENCE

assert "$(../src/098_squares < /dev/null)" 0 $LINENO
assert "$(../src/098_squares < data/042_words.in)" 18769 $LINENO $REFERENCE

assert_blank "../src/099_exponentials < /dev/null" $LINENO
assert "$(../src/099_exponentials < data/099_values.in)" 709 $LINENO $REFERENCE

assert "$(../src/102_triangles < /dev/null)" 0 $LINENO
assert "$(../src/102_triangles < data/102_triangles.in)" 228 $LINENO $REFERENCE

assert_fail "../src/104_fibonacci 0" $LINENO
assert_fail "../src/104_fibonacci 10" $LINENO
assert "$(../src/104_fibonacci 2)" 8 $LINENO
assert "$(../src/104_fibonacci 9)" 329468 $LINENO $REFERENCE

assert_fail "../src/107_spanning_tree < /dev/null" $LINENO
assert "$(../src/107_spanning_tree < data/107_network.in)" 259679 $LINENO $REFERENCE

assert_fail "../src/109_darts 0" $LINENO
assert "$(../src/109_darts 100)" 38182 $LINENO $REFERENCE
assert "$(../src/109_darts 171)" 42336 $LINENO

assert_fail "../src/111_prime_runs 0" $LINENO
assert "$(../src/111_prime_runs 4)" 273700 $LINENO
assert "$(../src/111_prime_runs 10)" 612407567715 $LINENO $REFERENCE

assert_fail "../src/112_bouncy_numbers -1" $LINENO
assert_fail "../src/112_bouncy_numbers 100" $LINENO
assert "$(../src/112_bouncy_numbers 50)" 538 $LINENO
assert "$(../src/112_bouncy_numbers 90)" 21780 $LINENO
assert "$(../src/112_bouncy_numbers 99)" 1587000 $LINENO $REFERENCE

assert_fail "../src/119_digit_power_sum 0" $LINENO
assert "$(../src/119_digit_power_sum 2)" 512 $LINENO
assert "$(../src/119_digit_power_sum 10)" 614656 $LINENO
assert "$(../src/119_digit_power_sum 30)" 248155780267521 $LINENO $REFERENCE

assert_fail "../src/124_radicals 1 0" $LINENO
assert_fail "../src/124_radicals 0 10" $LINENO
assert_fail "../src/124_radicals 11 10" $LINENO
assert "$(../src/124_radicals 4 10)" 8 $LINENO
assert "$(../src/124_radicals 6 10)" 9 $LINENO
assert "$(../src/124_radicals 10000 100000)" 21417 $LINENO $REFERENCE

assert_fail "../src/125_palindromic_sums 0" $LINENO
assert "$(../src/125_palindromic_sums 1000)" 4164 $LINENO
assert "$(../src/125_palindromic_sums 100000000)" 2906969179 $LINENO $REFERENCE

assert "$(../src/145_reversible -1)" 0 $LINENO
assert "$(../src/145_reversible 0)" 0 $LINENO
assert "$(../src/145_reversible 1000)" 120 $LINENO
assert "$(../src/145_reversible 1000000000)" 608720 $LINENO $REFERENCE

assert_fail "../src/173_squares 0" $LINENO
assert "$(../src/173_squares 100)" 41 $LINENO
assert "$(../src/173_squares 1000000)" 1572729 $LINENO $REFERENCE

assert_fail "../src/174_squares 0" $LINENO
assert "$(../src/174_squares 10)" 209566 $LINENO $REFERENCE

assert_fail "../src/179_divisors 2" $LINENO
assert "$(../src/179_divisors 3)" 1 $LINENO
assert "$(../src/179_divisors 15)" 2 $LINENO
assert "$(../src/179_divisors 10000000)" 986262 $LINENO $REFERENCE

assert "$(../src/187_semiprimes -1)" 0 $LINENO
assert "$(../src/187_semiprimes 4)" 0 $LINENO
assert "$(../src/187_semiprimes 30)" 10 $LINENO
assert "$(../src/187_semiprimes 100000000)" 17427258 $LINENO $REFERENCE

assert_fail "../src/203_square_free 0" $LINENO
assert "$(../src/203_square_free 8)" 105 $LINENO
assert "$(../src/203_square_free 51)" 34029210557338 $LINENO $REFERENCE

assert "$(../src/205_dice_game)" 0.5731441 $LINENO $REFERENCE

assert "$(../src/206_square 625)" 25 $LINENO
assert "$(../src/206_square 1_2_3_4_5_6_7_8_9_0)" 1389019170 $LINENO $REFERENCE

assert_fail "../src/357_prime_generation 1" $LINENO
assert "$(../src/357_prime_generation 100000000)" 1739023853137 $LINENO $REFERENCE

echo "All tests passed"
exit 0
