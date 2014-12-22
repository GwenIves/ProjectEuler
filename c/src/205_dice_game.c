/*
 * Find the victory probability when rolling 9 4-sided against 6 6-sided dice
 */

#include <stdio.h>
#include "math_utils.h"

#define DICE_A		9
#define SIDES_A		4
#define DICE_B		6
#define SIDES_B		6

static void fill_roll_counts (int *, int, int);
static int get_roll_counts (int, int, int);

int main () {
	int max_roll_a = DICE_A * SIDES_A;
	int max_roll_b = DICE_B * SIDES_B;

	int roll_counts_a[max_roll_a];
	int roll_counts_b[max_roll_b];

	fill_roll_counts (roll_counts_a, DICE_A, SIDES_A);
	fill_roll_counts (roll_counts_b, DICE_B, SIDES_B);

	long winning_rolls = 0;;

	for (size_t i = 0; i < max_roll_b; i++) {
		int sum = 0;

		for (size_t j = i + 1; j < max_roll_a; j++)
			sum += roll_counts_a[j];

		winning_rolls += roll_counts_b[i] * sum;
	}

	long all_rolls = power (SIDES_A, DICE_A) * power (SIDES_B, DICE_B);

	printf ("%.7f\n", winning_rolls / (double) all_rolls);

	return 0;
}

static void fill_roll_counts (int * counts, int dice, int sides) {
	int max_roll = dice * sides;

	for (int i = 0; i < max_roll; i++)
		counts[i] = get_roll_counts (i + 1, dice, sides);
}

static int get_roll_counts (int sum, int dice, int sides) {
	if (sum <= 0)
		return 0;

	if (dice == 1) {
		if (sum > sides)
			return 0;
		else
			return 1;
	} else {
		int count = 0;

		for (int side = 1; side <= sides; side++)
			count += get_roll_counts (sum - side, dice - 1, sides);

		return count;
	}
}
