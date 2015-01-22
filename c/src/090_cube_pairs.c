/*
 * Find how many distinct pairs of 6-sided dice exist that can display all one and two digit squares
 */

#include <stdio.h>
#include <string.h>
#include "math_utils.h"

static bool pair_qualifies (const char *, const char *);
static bool die_contains_face (const char *, int);

int main (void) {
	int count = 0;

	char die1[DIGITS_COUNT + 1] = "0000111111";

	do {
		char die2[DIGITS_COUNT + 1];

		strcpy (die2, die1);

		do {
			if (pair_qualifies (die1, die2))
				count++;
		} while (next_permutation (die2));
	} while (next_permutation (die1));

	printf ("%d\n", count);

	return 0;
}

static bool pair_qualifies (const char * die1, const char * die2) {
	for (int i = 1; i < 10; i++) {
		int square = i * i;

		int digit1 = square % 10;
		int digit2 = square / 10;

		if (die_contains_face (die1, digit1) && die_contains_face (die2, digit2))
			continue;
		else if (die_contains_face (die1, digit2) && die_contains_face (die2, digit1))
			continue;
		else
			return false;
	}

	return true;
}

static bool die_contains_face (const char * die, int face) {
	if (die[face] == '1')
		return true;
	else if (face == 6 && die[9] == '1')
		return true;
	else if (face == 9 && die[6] == '1')
		return true;
	else
		return false;
}
