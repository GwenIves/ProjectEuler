/*
 * Find the 3 most likely squares to end a turn on in a game of Monopoly played with a pair of N-sided dice
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SQUARES_COUNT	40
#define CARDS_COUNT	16
#define TOP_SQUARES	3
#define SIM_STEPS	100000

enum positions {START = 0, A1, CC1, A2, T1, R1, B1, CH1, B2, B3,
		JAIL = 10, C1, U1, C2, C3, R2, D1, CC2, D2, D3,
		FP = 20, E1, CH2, E2, E3, R3, F1, F2, U2, F3,
		GO_TO_JAIL = 30, G1, G2, CC3, G3, R4, CH3, H1, T2, H2};

enum cc_cards {CC_GO = 0, CC_JAIL};
enum ch_cards {CH_GO = 0, CH_JAIL, CH_C1, CH_E3, CH_H2, CH_R1, CH_NEXT_R1, CH_NEXT_R2, CH_NEXT_U, CH_BACK3};

static int get_most_frequent (int *, int);
static void shuffle_cards (int *, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 2)
		return 1;

	int end_turn_positions[SQUARES_COUNT] = { 0 };
	int ch_cards[CARDS_COUNT];
	int cc_cards[CARDS_COUNT];

	shuffle_cards (ch_cards, CARDS_COUNT);
	shuffle_cards (cc_cards, CARDS_COUNT);

	int cc_deck_top = 0;
	int ch_deck_top = 0;

	int position = START;
	int doubles_count = 0;

	for (size_t i = 0; i < SIM_STEPS; i++) {
		int die1 = (rand () % N) + 1;
		int die2 = (rand () % N) + 1;

		position += die1 + die2;
		position %= SQUARES_COUNT;

		if (die1 == die2)
			doubles_count++;
		else
			doubles_count = 0;

		if (doubles_count == 3) {
			doubles_count = 0;
			position = JAIL;
		}

		if (position == CH1 || position == CH2 || position == CH3) {
			int ch_card = ch_cards[ch_deck_top++];

			ch_deck_top %= CARDS_COUNT;

			if (ch_card == CH_GO)
				position = START;
			else if (ch_card == CH_JAIL)
				position = JAIL;
			else if (ch_card == CH_C1)
				position = C1;
			else if (ch_card == CH_E3)
				position = E3;
			else if (ch_card == CH_H2)
				position = H2;
			else if (ch_card == CH_R1)
				position = R1;
			else if (ch_card == CH_NEXT_R1 || ch_card == CH_NEXT_R2) {
				if (position == CH1)
					position = R2;
				else if (position == CH2)
					position = R3;
				else
					position = R4;
			} else if (ch_card == CH_NEXT_U) {
				if (position == CH2)
					position = U2;
				else
					position = U1;
			} else if (ch_card == CH_BACK3) {
				position -= 3;
			}
		}

		if (position == CC1 || position == CC2 || position == CC3) {
			int cc_card = cc_cards[cc_deck_top++];

			cc_deck_top %= CARDS_COUNT;

			if (cc_card == CC_GO)
				position = START;
			else if (cc_card == CC_JAIL)
				position = JAIL;
		}

		if (position == GO_TO_JAIL)
			position = JAIL;

		end_turn_positions[position] += 1;
	}

	for (size_t i = 0; i < TOP_SQUARES; i++) {
		int f = get_most_frequent (end_turn_positions, SQUARES_COUNT);

		printf ("%02d", f);
		end_turn_positions[f] = 0;
	}

	printf ("\n");

	return 0;
}

static void shuffle_cards (int * deck, int count) {
	for (int i = 0; i < count; i++) {
		bool duplicate = true;
		int new_card = 0;

		while (duplicate) {
			new_card = rand () % count;
			duplicate = false;

			for (int j = 0; j < i; j++)
				if (deck[j] == new_card) {
					duplicate = true;
					break;
				}
		}

		deck[i] = new_card;
	}
}

static int get_most_frequent (int * frequencies, int size) {
	int most_frequent = 0;

	for (int i = 1; i < size; i++)
		if (frequencies[i] > frequencies[most_frequent])
			most_frequent = i;

	return most_frequent;
}
