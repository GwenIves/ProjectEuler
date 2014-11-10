/*
 * Find the number of wins by the first hand in poker games read from stdin
 * Each line of the input should hold 10 card specifications, 5 for the first and 5 for the second hand respectively
 * Card specification should be space separated and formed by a concatenation of a value and a suit
 * Valid values are 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A
 * Valid suits are H, C, S, D
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

#define HAND_SIZE	5

enum values {TWO = 0, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, VALUES_ENUM_SIZE_};
enum suits {HEARTS, CLUBS, SPADES, DIAMONDS};
enum hand_ranks {HIGH_CARD = 0, ONE_PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH};

typedef struct {
	int value;
	int suit;
} card_t;

typedef struct {
	card_t cards[HAND_SIZE];
	int rank;
	int rank_value;
} hand_t;

typedef struct {
	hand_t player1;
	hand_t player2;
} match_t;

static bool read_match (char *, match_t *);
static bool parse_card_spec (char *, card_t *);
static int rank_match (match_t *);
static void rank_hand (hand_t *);
static int value_cmp (const void *, const void *);

int main () {
	char * line = NULL;

	int count = 0;

	while (x_getline (&line, stdin) != -1) {
		match_t match;

		if (read_match (line, &match))
			if (rank_match (&match) > 0)
				count++;

		free (line);
	}

	printf ("%d\n", count);

	return 0;
}

static int rank_match (match_t * match) {
	hand_t * h1 = &match->player1;
	hand_t * h2 = &match->player2;

	rank_hand (h1);
	rank_hand (h2);

	if (h1->rank != h2->rank)
		return h1->rank - h2->rank;
	else if (h1->rank_value != h2->rank_value)
		return h1->rank_value - h2->rank_value;
	else {
		for (int i = HAND_SIZE - 1; i >= 0; i--)
			if (h1->cards[i].value != h2->cards[i].value)
				return h1->cards[i].value - h2->cards[i].value;
	}

	return 0;
}

static void rank_hand (hand_t * hand) {
	card_t * cards = hand->cards;

	hand->rank = 0;
	hand->rank_value = cards[HAND_SIZE - 1].value;

	qsort (cards, HAND_SIZE, sizeof (card_t), value_cmp);

	bool same_suit = true;
	bool straight = true;

	int max_same_value_count = 0;
	int pair_count = 0;

	int values[VALUES_ENUM_SIZE_] = {0};

	for (size_t i = 0; i < HAND_SIZE; i++)
		values[cards[i].value]++;

	for (int i = array_len (values) - 1; i >= 0; i--) {
		if (values[i] > max_same_value_count) {
			max_same_value_count = values[i];
			hand->rank_value = i;
		}

		if (values[i] == 2)
			pair_count++;
	}

	for (size_t i = 1; i < HAND_SIZE; i++) {
		if (cards[i].suit != cards[i - 1].suit)
			same_suit = false;

		if (cards[i].value != cards[i - 1].value + 1)
			straight = false;
	}

	if (same_suit && straight) {
		if (cards[0].value == TEN)
			hand->rank = ROYAL_FLUSH;
		else
			hand->rank = STRAIGHT_FLUSH;
	} else if (max_same_value_count == 4)
		hand->rank = FOUR_OF_A_KIND;
	else if (max_same_value_count == 3 && pair_count > 0)
		hand->rank = FULL_HOUSE;
	else if (same_suit)
		hand->rank = FLUSH;
	else if (straight)
		hand->rank = STRAIGHT;
	else if (max_same_value_count == 3)
		hand->rank = THREE_OF_A_KIND;
	else if (pair_count == 2)
		hand->rank = TWO_PAIRS;
	else if (pair_count == 1)
		hand->rank = ONE_PAIR;
	else
		hand->rank = HIGH_CARD;
}

static bool read_match (char * match_spec, match_t * match) {
	for (size_t i = 0; i < HAND_SIZE * 2; i++) {
		char * card_spec = NULL;

		if (i == 0)
			card_spec = strtok (match_spec, " ");
		else
			card_spec = strtok (NULL, " ");

		if (!card_spec)
			return false;

		card_t * card = NULL;

		if (i < HAND_SIZE)
			card = match->player1.cards + i;
		else
			card = match->player2.cards + (i - HAND_SIZE);

		if (!parse_card_spec (card_spec, card))
			return false;
	}

	return true;
}

static bool parse_card_spec (char * spec, card_t * card) {
	switch (spec[0]) {
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			card->value = TWO + spec[0] - '2';
			break;
		case 'T':
			card->value = TEN;
			break;
		case 'J':
			card->value = JACK;
			break;
		case 'Q':
			card->value = QUEEN;
			break;
		case 'K':
			card->value = KING;
			break;
		case 'A':
			card->value = ACE;
			break;
		default:
			return false;
	}

	switch (spec[1]) {
		case 'H':
			card->suit = HEARTS;
			break;
		case 'C':
			card->suit = CLUBS;
			break;
		case 'S':
			card->suit = SPADES;
			break;
		case 'D':
			card->suit = DIAMONDS;
			break;
		default:
			return false;
	}

	return spec[2] == '\0';
}

static int value_cmp (const void * a, const void * b) {
	card_t * ca = (card_t *) a;
	card_t * cb = (card_t *) b;

	return ca->value - cb->value;
}
