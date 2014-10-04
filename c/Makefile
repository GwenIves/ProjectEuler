#Definitions

ALL_C := $(wildcard *.c)

ALL_DEPS := $(subst .c,.d,$(ALL_C))
ALL_EXE :=

CFLAGS := --pedantic -Wall -std=gnu99 -O3
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

ALL_EXE += 001_multiples
ALL_EXE += 002_fibonacci

003_prime_factor: LDFLAGS += -lm
ALL_EXE += 003_prime_factor

004_palindrome: LDFLAGS += -lm
ALL_EXE += 004_palindrome

005_multiple: LDFLAGS += -lm
005_multiple: 005_multiple.o math_utils.o utils.o
ALL_EXE += 005_multiple

ALL_EXE += 006_square_difference

007_prime: LDFLAGS += -lm
007_prime: 007_prime.o math_utils.o utils.o
ALL_EXE += 007_prime

ALL_EXE += 008_series
ALL_EXE += 009_pythagorean_triplet

010_primes_sum: LDFLAGS += -lm
010_primes_sum: 010_primes_sum.o math_utils.o utils.o
ALL_EXE += 010_primes_sum

011_grid_product: LDFLAGS += -lm
011_grid_product: 011_grid_product.o math_utils.o utils.o
ALL_EXE += 011_grid_product

012_triangular_number: LDFLAGS += -lm
ALL_EXE += 012_triangular_number

013_large_sum: 013_large_sum.o bignum.o utils.o
ALL_EXE += 013_large_sum

014_collatz_sequence: 014_collatz_sequence.o utils.o
ALL_EXE += 014_collatz_sequence

015_lattice_paths: 015_lattice_paths.o utils.o
ALL_EXE += 015_lattice_paths

016_power_digit_sum: 016_power_digit_sum.o bignum.o utils.o
ALL_EXE += 016_power_digit_sum

ALL_EXE += 017_number_letters

018_maximum_path: LDFLAGS += -lm
018_maximum_path: 018_maximum_path.o math_utils.o utils.o
ALL_EXE += 018_maximum_path

ALL_EXE += 019_day_count

020_factorial: 020_factorial.o bignum.o utils.o
ALL_EXE += 020_factorial

021_amicable_numbers: LDFLAGS += -lm
021_amicable_numbers: utils.o
ALL_EXE += 021_amicable_numbers

022_name_scoring: 022_name_scoring.o utils.o
ALL_EXE += 022_name_scoring

build:  $(ALL_EXE)
