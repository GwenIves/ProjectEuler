/*
 * Find the sum of all name scores calculated over a name list read from stdin
 * Names should be passed in quotes separated by a single comma
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

static int score_name (char *);
static char ** read_names (int *);
static void free_names (char **, int);

int main () {
	int names_count = 0;
	char ** names = NULL;
	
	if ((names = read_names (&names_count)) == NULL)
		return 1;

	qsort (names, names_count, sizeof (char *), string_cmp);

	long sum = 0;

	for (int i = 0; i < names_count; i++)
		sum += score_name (names[i]) * (i + 1);

	printf ("%ld\n", sum);

	free_names (names, names_count);

	return 0;
}

static int score_name (char * name) {
	int alpha_value = 0;

	while (*name) {
		alpha_value += tolower (*name) - 'a' + 1;
		name++;
	}

	return alpha_value;
}

static char ** read_names (int * count) {
	char buffer[100 + 1];

	char ** names = NULL;

	int allocated = 0;
	int used = 0;

	while (scanf ("\"%100[^\"]\"", buffer) > 0) {
		if (used >= allocated) {
			allocated++;
			allocated *= 2;

			names = x_realloc (names, allocated * sizeof (char *));
		}

		names[used++] = strdup (buffer);

		if (fgetc (stdin) == EOF)
			break;
	}

	*count = used;

	return names;
}

static void free_names (char ** names, int count) {
	free_array (names, count);
	free (names);
}
