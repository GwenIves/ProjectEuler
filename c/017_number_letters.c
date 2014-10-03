/*
 * Write out N (less than 1,000,000) in English letters
 */

#include <stdio.h>
#include <stdlib.h>

static const char * ones[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static const char * teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
static const char * tys[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

static void printout_number (int);
static void printout_number_under100 (int);
static void printout_number_under1000 (int, int);
static void printout_number_under1000000 (int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	printout_number (N);

	return 0;
}

static void printout_number (int N) {
	if (N < 1000000)
		printout_number_under1000000 (N, 1);

	printf ("\n");
}

static void printout_number_under100 (int N) {
	if (N < 10)
		printf ("%s", ones[N]);
	else if (N < 20)
		printf ("%s", teens[N - 10]);
	else if (N < 100) {
		if (N % 10)
			printf ("%s %s", tys[N / 10], ones[N % 10]);
		else
			printf ("%s", tys[N / 10]);
	}
}

static void printout_number_under1000 (int N, int separator) {
	if (N < 100)
		printout_number_under100 (N);
	else {
		printout_number_under100 (N / 100);
		printf (" hundert"); 

		if (N % 100) {
			if (separator)
				printf (" and ");
			else
				printf (" ");

			printout_number_under100 (N % 100);
		}
	}
}

static void printout_number_under1000000 (int N, int separator) {
	if (N < 1000)
		printout_number_under1000 (N, 1);
	else {
		printout_number_under1000 (N / 1000, 0);
		printf (" thousand");

		if (N % 1000) {
			if (separator && N % 1000 < 100)
				printf (" and ");
			else
				printf (" ");

			printout_number_under1000 (N % 1000, 1);
		}
	}
}
