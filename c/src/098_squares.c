/*
 * Find the largest square number given by digital substitutions in words read from stdin
 * for which a square anagram word exists in the same list of input words
 * stdin words should be in double quotes and separated by a single comma
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "math_utils.h"
#include "utils.h"
#include "linked_list.h"

typedef struct {
	char * word;
	char * sorted_word;
	size_t length;
} word_t;

static linked_list_t * load_words (void);
static void free_words (linked_list_t *);
static linked_list_t * get_anagrams (const word_t *, linked_list_t *);
static bool next_substitution (int *, const word_t *);
static bool are_anagrams (const word_t *, const word_t *);
static int get_substitution_value (const int *, const word_t *);
static int words_cmp (const void *, const void *);

int main (void) {
	linked_list_t * words = load_words ();

	word_t * w_ptr = NULL;

	int max_square = 0;

	while ((w_ptr = linked_list_next (words, word_t)) != NULL) {
		linked_list_t * anagrams = get_anagrams (w_ptr, words);

		if (!anagrams)
			continue;

		int substitution[LETTERS_COUNT];

		if (next_substitution (substitution, w_ptr)) {
			do {
				word_t * a_ptr = NULL;

				while ((a_ptr = linked_list_next (anagrams, word_t)) != NULL) {
					int value = get_substitution_value (substitution, a_ptr);

					if (value != -1 && integer_sqrt (value) != -1) {
						if (value > max_square)
							max_square = value;

						value = get_substitution_value (substitution, w_ptr);

						if (value > max_square)
							max_square = value;
					}
				}
			} while (next_substitution (substitution, NULL));
		}

		linked_list_free (anagrams);
	}

	free_words (words);

	printf ("%d\n", max_square);

	return 0;
}

static linked_list_t * load_words (void) {
	char word[100 + 1];

	linked_list_t * words = linked_list_create ();

	while (scanf ("\"%100[^\"]\"", word) > 0) {
		for (size_t i = 0; word[i] != '\0'; i++)
			word[i] = tolower (word[i]);

		word_t * w_ptr = x_malloc (sizeof ( word_t));

		w_ptr->length = strlen (word);
		w_ptr->word = strdup (word);

		w_ptr->sorted_word = strdup (w_ptr->word);
		qsort (w_ptr->sorted_word, w_ptr->length, 1, char_cmp);

		linked_list_add_sorted (words, w_ptr, words_cmp, false);

		if (fgetc (stdin) == EOF)
			break;
	}

	return words;
}

static void free_words (linked_list_t * words) {
	word_t * w_ptr = NULL;

	while ((w_ptr = linked_list_next (words, word_t)) != NULL) {
		free (w_ptr->word);
		free (w_ptr->sorted_word);
	}

	linked_list_free (words);
}

static linked_list_t * get_anagrams (const word_t * word, linked_list_t * words) {
	linked_list_t * anagrams = NULL;

	list_node_t * saved_cursor = words->cursor;

	word_t * a_ptr = NULL;

	while ((a_ptr = linked_list_next (words, word_t)) != NULL)
		if (a_ptr->length > word->length)
			break;
		else if (are_anagrams (word, a_ptr)) {
			if (!anagrams)
				anagrams = linked_list_create ();

			linked_list_add_copy (anagrams, a_ptr, word_t);
		}

	words->cursor = saved_cursor;

	return anagrams;
}

static bool are_anagrams (const word_t * a, const word_t * b) {
	return strcmp (a->sorted_word, b->sorted_word) == 0;
}

static int get_substitution_value (const int * substitution, const word_t * word) {
	char * str = word->word;

	int value = 0;

	for (size_t i = 0; str[i] != '\0'; i++) {
		int letter = str[i] - 'a';

		value *= 10;
		value += substitution[letter];

		if (i == 0 && value == 0)
			return -1;
	}

	return value;
}

static bool next_substitution (int * substitution_out, const word_t * word_in) {
	static char * word = NULL;
	static size_t len = 0;

	static int low_square = 0;
	static int high_square = 0;
	static int current_sqrt = 0;

	if (word_in != NULL) {
		word = word_in->word;
		len = word_in->length;

		low_square = power (DIGITS_COUNT, len - 1);
		high_square = low_square * DIGITS_COUNT - 1;
		current_sqrt = sqrt (low_square);
	}

	while (true) {
		int square = current_sqrt * current_sqrt;
		current_sqrt++;

		if (square < low_square)
			continue;
		else if (square > high_square)
			break;

		int substitution[LETTERS_COUNT];

		for (size_t i = 0; i < LETTERS_COUNT; i++)
			substitution[i] = -1;

		bool digit_taken[DIGITS_COUNT];

		for (size_t i = 0; i < DIGITS_COUNT; i++)
			digit_taken[i] = false;

		bool valid_substitution = true;

		for (int i = len - 1; i >= 0; i--) {
			int digit = square % 10;
			square /= 10;

			int letter = word[i] - 'a';

			if (substitution[letter] == digit)
				continue;
			else if (substitution[letter] != -1 || digit_taken[digit]) {
				valid_substitution = false;
				break;
			} else {
				digit_taken[digit] = true;
				substitution[letter] = digit;
			}
		}

		if (valid_substitution) {
			for (size_t i = 0; i < LETTERS_COUNT; i++)
				substitution_out[i] = substitution[i];

			return true;
		}
	}

	return false;
}

static int words_cmp (const void * a, const void * b) {
	word_t * aa = (word_t *) a;
	word_t * bb = (word_t *) b;

	return aa->length - bb->length;
}
