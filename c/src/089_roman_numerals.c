/*
 * Find how many characters can be saved by rewriting Roman numerals in their minimal form
 * Numerals are read from stdin one per line
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static int roman_digit_value (char);
static int roman_to_arabic (char *);
static char * arabic_to_roman (int);

int main (void) {
	char * line = NULL;
	ssize_t len = 0;

	int savings = 0;

	while ((len = x_getline (&line, stdin)) != -1) {
		char * minimal_representation = arabic_to_roman (roman_to_arabic (line));

		if (minimal_representation)
			savings += len - (int) strlen (minimal_representation);

		free (minimal_representation);
		free (line);
	}

	printf ("%d\n", savings);

	return 0;
}

static char * arabic_to_roman (int arabic) {
	char * roman = NULL;
	size_t allocated = 0;
	size_t used = 0;

	while (arabic > 0) {
		if (used + 1 >= allocated) {
			allocated += 10;
			roman = x_realloc (roman, allocated);
		}

		if (arabic >= 1000) {
			roman[used++] = 'M';
			arabic -= 1000;
		} else if (arabic >= 900) {
			roman[used++] = 'C';
			arabic += 100;
		} else if (arabic >= 500) {
			roman[used++] = 'D';
			arabic -= 500;
		} else if (arabic >= 400) {
			roman[used++] = 'C';
			arabic += 100;
		} else if (arabic >= 100) {
			roman[used++] = 'C';
			arabic -= 100;
		} else if (arabic >= 90) {
			roman[used++] = 'X';
			arabic += 10;
		} else if (arabic >= 50) {
			roman[used++] = 'L';
			arabic -= 50;
		} else if (arabic >= 40) {
			roman[used++] = 'X';
			arabic += 10;
		} else if (arabic >= 10) {
			roman[used++] = 'X';
			arabic -= 10;
		} else if (arabic >= 9) {
			roman[used++] = 'I';
			arabic++;
		} else if (arabic >= 5) {
			roman[used++] = 'V';
			arabic -= 5;
		} else if (arabic >= 4) {
			roman[used++] = 'I';
			arabic++;
		} else {
			roman[used++] = 'I';
			arabic--;
		}
	}

	roman[used] = '\0';

	return roman;
}

static int roman_to_arabic (char * roman) {
	int arabic = 0;
	int prev_digit = 0;

	char * tail_ptr = roman + strlen (roman) - 1;

	while (tail_ptr >= roman) {
		int digit = roman_digit_value (*tail_ptr);

		if (digit >= prev_digit)
			arabic += digit;
		else
			arabic -= digit;

		prev_digit = digit;
		tail_ptr--;
	}

	return arabic;
}

static int roman_digit_value (char digit) {
	switch (digit) {
		case 'I':
			return 1;
		case 'V':
			return 5;
		case 'X':
			return 10;
		case 'L':
			return 50;
		case 'C':
			return 100;
		case 'D':
			return 500;
		case 'M':
			return 1000;
		default:
			return 0;
	}
}
