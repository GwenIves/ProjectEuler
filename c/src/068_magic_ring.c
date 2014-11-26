/*
 * Find the maximum "magic" pentagon ring
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "math_utils.h"

#define SIZE		5
#define MAX_LEN		6 * SIZE
#define TARGET_LEN	16

static bool is_magic (char *);
static char * get_representation (char *, size_t);
static int char_value (char);

/*
 * The pentagon is represented by the digits array
 * Indices 0 .. SIZE - 1 hold the outer ring
 * Indices SIZE .. 2 * SIZE - 1 hold the inner ring with index i connected to i + SIZE
 */

int main () {
	char representation[TARGET_LEN + 1] = "";

	char digits[] = "123456789A";

	do {
		if (is_magic (digits)) {
			char * r_ptr = get_representation (digits, TARGET_LEN);

			if (r_ptr && strcmp (r_ptr, representation) > 0)
				strcpy (representation, r_ptr);
		}
	} while (next_permutation (digits));

	printf ("%s\n", representation);

	return 0;
}

// A pentagon is magic if all its defining triples (see comments for get_representation ()) have the same sum
static bool is_magic (char * digits) {
	int sums[SIZE];

	for (size_t i = 0; i < SIZE; i++) {
		sums[i] = char_value (digits[i]) + char_value (digits[i + SIZE]) + char_value (digits[((i + 1) % SIZE) + SIZE]);

		if (i > 0 && sums[i] != sums[i - 1])
			return false;
	}

	return true;
}

/*
 * The canonical representation is a concatenation of all triples i, j, k
 * where i is an outer ring vertex, j the inner ring vertex connected to i, and k the inner ring vertex clockwise from j
 * The starting triple is the one with minimal i
 */

static char * get_representation (char * digits, size_t len) {
	static char representation[MAX_LEN + 1];

	representation[0] = '\0';

	size_t min = 0;

	for (size_t i = 1; i < SIZE; i++)
		if (char_value (digits[i]) < char_value (digits[min]))
			min = i;

	for (size_t i = min; i < min + SIZE; i++) {
		size_t j = i % SIZE;

		char buf[7];

		sprintf (buf, "%d%d%d", char_value (digits[j]), char_value (digits[j + SIZE]), char_value (digits[((j + 1) % SIZE) + SIZE]));

		strcat (representation, buf);
	}

	if (strlen (representation) == len)
		return representation;
	else
		return NULL;
}

static int char_value (char chr) {
	if (chr <= '9')
		return chr - '0';
	else
		return chr - 'A' + 10;
}
