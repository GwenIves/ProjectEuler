#include <assert.h>
#include <stdio.h>
#include "date_utils.h"

static void is_leap_year_test ();

int main () {
	is_leap_year_test ();

	printf ("All date util tests passed\n");

	return 0;
}

static void is_leap_year_test () {
	assert (is_leap_year (2000) == 1);
	assert (is_leap_year (1900) == 0);
	assert (is_leap_year (1904) == 1);
	assert (is_leap_year (1903) == 0);
}
