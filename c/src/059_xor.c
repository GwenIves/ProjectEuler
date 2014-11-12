/*
 * Find the sum of ASCII values in a text that has been encrypted with a XOR function
 * The encrypted text is read from stdin as a list of comma separated integeres and is known to contain common English words
 * The password must be formed by N lowercase ASCII characters
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

#define COMMON_WORDS_THRESHOLD	10
#define LONGEST_COMMON_WORD	4

#define COMMON_WORD	1
#define OTHER_WORD	-1

static char * common_words[] = {"the", "be", "to", "of", "and", "a", "in", "that", "have", "I"};

static bool next_password (unsigned int *, int);
static int check_letter (unsigned int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	unsigned int password[N];

	memset (password, 0, N);

	while (next_password (password, N)) {
		unsigned int encrypted = 0;

		size_t password_cursor = 0;

		int common_words_count = 0;
		int other_words_count = 0;

		unsigned int sum = 0;

		while (scanf ("%u", &encrypted) > 0) {
			unsigned int decrypted = encrypted ^ password[password_cursor++];

			sum += decrypted;

			if (password_cursor >= N)
				password_cursor = 0;

			if (!isprint (decrypted)) {
				common_words_count = 0;
				break;
			}

			int word = check_letter (decrypted);

			if (word == COMMON_WORD)
				common_words_count++;
			else if (word == OTHER_WORD)
				other_words_count++;

			if (fgetc (stdin) == EOF)
				break;
		}

		if (common_words_count * COMMON_WORDS_THRESHOLD > other_words_count) {
			printf ("%u\n", sum);
			break;
		}

		fseek (stdin, 0, SEEK_SET);
	}

	return 0;
}

static bool next_password (unsigned int * password, int len) {
	if (password[0] == 0) {
		for (size_t i = 0; i < len; i++)
			password[i] = 'a';
	} else {
		size_t i = 0;

		for (i = 0; i < len; i++)
			if (password[i] < 'z') {
				password[i]++;
				break;
			} else
				password[i] = 'a';

		if (i >= len)
			return false;
	}

	return true;
}

static int check_letter (unsigned int letter) {
	static char word[LONGEST_COMMON_WORD + 1];
	static int word_index = 0;
	static int word_len = 0;

	if (isspace (letter)) {
		int word_type = OTHER_WORD;

		if (word_len <= word_index) {

			word[word_index] = '\0';

			for (size_t i = 0; i < array_len (common_words); i++)
				if (!strcmp (word, common_words[i])) {
					word_type = COMMON_WORD;
					break;
				}
		}

		word_index = 0;
		word_len = 0;
		word[0] = '\0';

		return word_type;
	} else {
		if (word_index <= LONGEST_COMMON_WORD)
			word[word_index++] = letter;

		word_len++;

		return 0;
	}
}
