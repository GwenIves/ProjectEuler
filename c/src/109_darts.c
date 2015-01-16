/*
 * Find how many ways a player can checkout in a game of darts with a score under N
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define SECTIONS_COUNT	63
#define DOUBLES_COUNT	21

static int all_sections[SECTIONS_COUNT];
static int double_sections[DOUBLES_COUNT];

static void initialise (void);
static int darts_combinations (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	initialise ();

	int combinations = 0;

	for (int i = 1; i < N; i++)
		combinations += darts_combinations (i);

	printf ("%d\n", combinations);

	return 0;
}

static void initialise (void) {
	size_t section = 0;
	size_t double_section = 0;

	for (int i = 1; i <= 20; i++) {
		all_sections[section++] = i;
		all_sections[section++] = i * 2;
		all_sections[section++] = i * 3;

		double_sections[double_section++] = i * 2;
	}

	all_sections[section++] = 25;
	all_sections[section++] = 50;

	// Less than 3 shots needed, shot not taken
	all_sections[section++] = 0;

	double_sections[double_section++] = 50;

	qsort (all_sections, SECTIONS_COUNT, sizeof (int), int_cmp);
}

static int darts_combinations (int checkout) {
	int combinations = 0;

	for (size_t i = 0; i < DOUBLES_COUNT; i++) {
		if (double_sections[i] > checkout)
			break;

		for (size_t j = 0; j < SECTIONS_COUNT; j++) {
			int sum2 = double_sections[i] + all_sections[j];

			if (sum2 > checkout)
				break;

			for (size_t k = j; k < SECTIONS_COUNT; k++) {
				int sum3 = sum2 + all_sections[k];

				if (sum3 == checkout) {
					combinations++;
				} else if (sum3 > checkout)
					break;
			}

		}
	}

	return combinations;
}
