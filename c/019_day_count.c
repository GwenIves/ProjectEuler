/*
 * Find how many specified days (0 = Monday .. 6 = Sunday) fell on the first of the month during the 20th century
 */

#include <stdio.h>
#include <stdlib.h>

#define DAYS_IN_WEEK		7
#define MONTHS_IN_YEAR		12
#define YEARS_IN_CENTURY	100

static const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static int leap_year (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	int count = 0;
	int day = 1; // 1st January 1901 was Tuesday
	int year = 1901;

	for (int month = 0; month < MONTHS_IN_YEAR * YEARS_IN_CENTURY; month++) {
		if (day == N)
			count++;

		if (month && month % MONTHS_IN_YEAR == 0)
			year++;

		day += days_in_month[month % MONTHS_IN_YEAR];

		if (month % MONTHS_IN_YEAR == 1 && leap_year (year))
			day++;

		day %= DAYS_IN_WEEK;
	}

	printf ("%d\n", count);

	return 0;
}

static int leap_year (int year) {
	if (year % 400 == 0)
		return 1;
	else if (year % 100 == 0)
		return 0;
	else if (year % 4 == 0)
		return 1;
	else
		return 0;
}
