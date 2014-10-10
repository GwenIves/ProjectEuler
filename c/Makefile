#Definitions

ALL_C := $(wildcard *.c)

ALL_DEPS := $(subst .c,.d,$(ALL_C))
ALL_EXE :=

CFLAGS := --pedantic -Wall -std=gnu99 -O3 -Werror
LDFLAGS :=

#Top level targets

.PHONY: build
build:

.PHONY: clean
clean:
	@echo "Deleting all executables"
	@rm -f $(ALL_EXE) 2>/dev/null
	@echo "Deleteing all object files"
	@rm -f *.o 2>/dev/null
	@echo "Deleteing all generated dependency files"
	@rm -f $(ALL_DEPS)

#Dependency generation

INCLUDE_DEPS := $(if $(findstring $(MAKECMDGOALS),clean),N,Y)

# $(call make-dependencies,source-file,object-file,depend-file)
define make-dependencies
  $(CC) -x c           \
        -MM            \
        -MF $3         \
        -MP            \
        -MT $2         \
        $(CFLAGS)      \
        $1
endef

ifeq "$(INCLUDE_DEPS)" "Y"
  -include $(ALL_DEPS)
endif

#Compilation rules

%.d: %.c
	$(call make-dependencies, $<,$(subst .d,.o,$@),$@)

############### Invidual binaries object constituents

bignum.o: utils.o
math_utils.o: utils.o
fraction.o: math_utils.o

ALL_EXE += 001_multiples
ALL_EXE += 002_fibonacci

003_prime_factor: LDFLAGS += -lm
ALL_EXE += 003_prime_factor

004_palindrome: LDFLAGS += -lm
004_palindrome: math_utils.o utils.o
ALL_EXE += 004_palindrome

005_multiple: LDFLAGS += -lm
005_multiple: math_utils.o utils.o
ALL_EXE += 005_multiple

ALL_EXE += 006_square_difference

007_prime: LDFLAGS += -lm
007_prime: math_utils.o utils.o
ALL_EXE += 007_prime

ALL_EXE += 008_series
ALL_EXE += 009_pythagorean_triplet

010_primes_sum: LDFLAGS += -lm
010_primes_sum: math_utils.o utils.o
ALL_EXE += 010_primes_sum

011_grid_product: LDFLAGS += -lm
011_grid_product: math_utils.o utils.o
ALL_EXE += 011_grid_product

012_triangular_number: LDFLAGS += -lm
012_triangular_number: utils.o math_utils.o
ALL_EXE += 012_triangular_number

013_large_sum: bignum.o utils.o
ALL_EXE += 013_large_sum

014_collatz_sequence: utils.o
ALL_EXE += 014_collatz_sequence

015_lattice_paths: utils.o
ALL_EXE += 015_lattice_paths

016_power_digit_sum: bignum.o utils.o
ALL_EXE += 016_power_digit_sum

ALL_EXE += 017_number_letters

018_maximum_path: LDFLAGS += -lm
018_maximum_path: math_utils.o utils.o
ALL_EXE += 018_maximum_path

ALL_EXE += 019_day_count

020_factorial: bignum.o utils.o
ALL_EXE += 020_factorial

021_amicable_numbers: LDFLAGS += -lm
021_amicable_numbers: utils.o math_utils.o
ALL_EXE += 021_amicable_numbers

022_name_scoring: utils.o
ALL_EXE += 022_name_scoring

023_non_abundant: LDFLAGS += -lm
023_non_abundant: math_utils.o utils.o
ALL_EXE += 023_non_abundant

024_permutations: LDFLAGS += -lm
024_permutations: utils.o math_utils.o
ALL_EXE += 024_permutations

025_fibonacci: bignum.o utils.o
ALL_EXE += 025_fibonacci

026_recurring_cycles: utils.o
ALL_EXE += 026_recurring_cycles

027_quadratic_primes: LDFLAGS += -lm
027_quadratic_primes: utils.o math_utils.o
ALL_EXE += 027_quadratic_primes

ALL_EXE += 028_number_spiral

029_powers: bignum.o utils.o
ALL_EXE += 029_powers

030_digit_powers: LDFLAGS += -lm
ALL_EXE += 030_digit_powers

ALL_EXE += 031_coins

032_pandigital: LDFLAGS += -lm
032_pandigital: utils.o math_utils.o
ALL_EXE += 032_pandigital

033_digit_cancelling: LDFLAGS += -lm
033_digit_cancelling: utils.o fraction.o math_utils.o
ALL_EXE += 033_digit_cancelling

ALL_EXE += 034_digit_factorials

035_circular_primes: LDFLAGS += -lm
035_circular_primes: math_utils.o utils.o
ALL_EXE += 035_circular_primes

036_palindromes: LDFLAGS += -lm
036_palindromes: math_utils.o utils.o
ALL_EXE += 036_palindromes

037_truncatable_primes: LDFLAGS += -lm
037_truncatable_primes: math_utils.o utils.o
ALL_EXE += 037_truncatable_primes

038_pandigital: LDFLAGS += -lm
038_pandigital: math_utils.o utils.o
ALL_EXE += 038_pandigital

ALL_EXE += 039_triangles
ALL_EXE += 040_champernowne

041_pandigital_prime: LDFLAGS += -lm
041_pandigital_prime: utils.o math_utils.o
ALL_EXE += 041_pandigital_prime

ALL_EXE += 042_triangle_words

043_substrings: LDFLAGS += -lm
043_substrings: utils.o math_utils.o
ALL_EXE += 043_substrings

044_pentagon_numbers: LDFLAGS += -lm
ALL_EXE += 044_pentagon_numbers

045_geometric_numbers: LDFLAGS += -lm
045_geometric_numbers: utils.o math_utils.o
ALL_EXE += 045_geometric_numbers

046_goldbach: LDFLAGS += -lm
046_goldbach: utils.o math_utils.o
ALL_EXE += 046_goldbach

047_prime_factors: LDFLAGS += -lm
ALL_EXE += 047_prime_factors

048_self_powers: bignum.o utils.o
ALL_EXE += 048_self_powers

049_permutations: LDFLAGS += -lm
049_permutations: utils.o math_utils.o
ALL_EXE += 049_permutations

build:  $(ALL_EXE)
