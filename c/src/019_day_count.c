/*
 * Find how many specified days (0 = Monday .. 6 = Sunday) fell on the first of the month during the 20th century
 */

#include <stdio.h>
#include <stdlib.h>
#include "date_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < MONDAY || N > SUNDAY)
		return 1;

	int count = 0;
	int day = TUESDAY; // 1st January 1901 was Tuesday
	int year = 1901;

	for (int month = 0; month < MONTHS_IN_YEAR * YEARS_IN_CENTURY; month++) {
		if (day == N)
			count++;

		if (month && month % MONTHS_IN_YEAR == 0)
			year++;

		day += days_in_month[month % MONTHS_IN_YEAR];

		if (month % MONTHS_IN_YEAR == 1 && is_leap_year (year))
			day++;

		day %= DAYS_IN_WEEK;
	}

	printf ("%d\n", count);

	return 0;
}
