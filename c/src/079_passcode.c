/*
 * Find all possible passcodes with the shortest possible length that contain all numeric subsequences read from stdin
 * Digits cannot repeat in the passcode
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "math_utils.h"
#include "linked_list.h"

static linked_list_t * read_subsequences (void);
static void find_passcodes (const char * prefix, linked_list_t *);

int main (void) {
	linked_list_t * subsequences = read_subsequences ();

	char passcode[DIGITS_COUNT + 1];
	passcode[0] = '\0';

	find_passcodes (passcode, subsequences);

	linked_list_free (subsequences);

	return 0;
}

// Recursively build up prefix using all possible topological sortings of the subsequences
static void find_passcodes (const char * prefix, linked_list_t * subsequences) {
	char passcode[DIGITS_COUNT + 1];

	strcpy (passcode, prefix);

	bool is_first[DIGITS_COUNT + 1];
	bool is_next[DIGITS_COUNT + 1];

	for (size_t i = 0; i < DIGITS_COUNT; i++) {
		is_first[i] = false;
		is_next[i] = false;
	}

	char * subsequence = NULL;

	while ((subsequence = linked_list_next (subsequences, char)) != NULL) {
		bool first_found = false;

		while (*subsequence) {
			if (!strchr (passcode, *subsequence)) {
				int digit = *subsequence - '0';

				if (!first_found) {
					first_found = true;

					is_first[digit] = true;
				} else
					is_next[digit] = true;
			}

			subsequence++;
		}
	}

	size_t len = strlen (passcode);

	size_t possible_continuations = 0;
	size_t digits_remaining = 0;

	for (size_t i = 0; i < DIGITS_COUNT; i++) {
		if (is_first[i] && !is_next[i]) {
			possible_continuations++;

			passcode[len] = '0' + i;
			passcode[len + 1] = '\0';

			find_passcodes (passcode, subsequences);
		} else if (is_first[i] || is_next[i])
			digits_remaining++;
	}

	if (possible_continuations == 0 && digits_remaining == 0)
		printf ("%s\n", passcode);
}

static linked_list_t * read_subsequences (void) {
	linked_list_t * list = linked_list_create ();

	char * line = NULL;

	while (x_getline (&line, stdin) != -1) {
		char * l = NULL;

		bool duplicate = false;

		while ((l = linked_list_next (list, char)) != NULL)
			if (!strcmp (l, line)) {
				duplicate = true;
				linked_list_stop_iteration (list);
				break;
			}

		if (!duplicate)
			linked_list_add (list, line);
		else
			free (line);
	}

	return list;
}
