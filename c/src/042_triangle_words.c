/*
 * Find the number of words read from stdin, the sum of whose letters' values is a triangle number
 * Words on stdin should be in double quotes and separated by a single comma
 */

#include <stdio.h>
#include <ctype.h>
#include "math_utils.h"

int main () {
	char word[100 + 1];

	int count = 0;

	while (scanf ("\"%100[^\"]\"", word) > 0) {
		int word_value = 0;

		for (int i = 0; word[i] != 0; i++)
			word_value += tolower (word[i]) - 'a' + 1;

		if (is_triangle (word_value))
			count++;

		if (fgetc (stdin) == EOF)
			break;
	}

	printf ("%d\n", count);

	return 0;
}
