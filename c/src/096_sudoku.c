/*
 * Sudoku solver
 *
 * For the purposes of the Euler project problem, read sudoku games from stdin
 * and output the sum of the 3 digit numbers in the top left corner of their solutions
 * The stdin format should be a concatenation of:
 * A single line containing "Grid <num>", followed by 9 lines containing 9 starting
 * digits each (0 means blank)
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

#define DIGITS	3

enum solution_status {SOLVED = 0, NO_SOLUTION, NON_DEDUCIBLE};

static bool read_game (int[9][9]);
static int solve (int[9][9]);
static int solve_by_deduction (int[9][9], size_t *, size_t *);
static void find_possible_placements (int[9][9], bool *, size_t, size_t);
static void copy_game (int[9][9], int[9][9]);

int main () {
	int sum = 0;

	int game[9][9];

	while (read_game (game)) {
		if (solve (game) != SOLVED)
			return 1;

		int corner_num = 0;

		for (size_t i = 0; i < DIGITS; i++) {
			corner_num *= 10;
			corner_num += game[0][i];
		}

		sum += corner_num;

	}

	printf ("%d\n", sum);

	return 0;
}

static int solve (int game[9][9]) {
	size_t min_row = 0;
	size_t min_column = 0;

	int status = solve_by_deduction (game, &min_row, &min_column);

	if (status != NON_DEDUCIBLE)
		return status;

	int saved_game[9][9];

	copy_game (saved_game, game);

	bool possible_placements[10];

	find_possible_placements (game, possible_placements, min_row, min_column);

	for (size_t i = 1; i <= 9; i++)
		if (possible_placements[i]) {
			game[min_row][min_column] = i;

			if (solve (game) == SOLVED)
				return SOLVED;
			else
				copy_game (game, saved_game);
		}

	return NO_SOLUTION;
}

static int solve_by_deduction (int game[9][9], size_t * min_row, size_t * min_column) {
	size_t blank_count = 0;
	bool solving = false;

	int min_solutions = -1;
	size_t min_i = 0;
	size_t min_j = 0;

	do {
		blank_count = 0;
		solving = false;

		min_solutions = -1;

		for (size_t i = 0; i < 9; i++)
			for (size_t j = 0; j < 9; j++) {
				if (game[i][j] != 0)
					continue;

				bool possible_placements[10];

				find_possible_placements (game, possible_placements, i, j);

				int possible_count = 0;
				size_t possible_at = 0;

				for (size_t k = 1; k <= 9; k++)
					if (possible_placements[k]) {
						possible_count++;
						possible_at = k;
					}

				if (possible_count == 0)
					return NO_SOLUTION;
				else if (possible_count == 1) {
					game[i][j] = possible_at;
					solving = true;
				} else {
					blank_count++;

					if (min_solutions == -1 || possible_count < min_solutions) {
						min_solutions = possible_count;
						min_i = i;
						min_j = j;
					}
				}
			}
	} while (blank_count > 0 && solving);

	if (blank_count == 0)
		return SOLVED;
	else {
		*min_row = min_i;
		*min_column = min_j;

		return NON_DEDUCIBLE;
	}
}

static void find_possible_placements (int game[9][9], bool * possible, size_t row, size_t column) {
	for (size_t i = 1; i <= 9; i++)
		possible[i] = true;

	for (size_t i = 0; i < 9; i++)
		possible[game[row][i]] = false;

	for (size_t i = 0; i < 9; i++)
		possible[game[i][column]] = false;

	size_t i_start = (row / 3) * 3;
	size_t j_start = (column / 3) * 3;

	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
			possible[game[i_start + i][j_start + j]] = false;
}

static bool read_game (int game[9][9]) {
	char * line = NULL;

	if (x_getline (&line, stdin) == -1)
		return false;

	free (line);

	for (size_t i = 0; i < 9; i++) {
		if (x_getline (&line, stdin) == -1)
			return false;
		else if (strlen (line) != 9) {
			free (line);
			return false;
		}

		for (size_t j = 0; j < 9; j++) {
			int val = line[j] - '0';

			if (val < 0 || val > 9) {
				free (line);
				return false;
			} else
				game[i][j] = val;
		}

		free (line);
	}

	return true;
}

static void copy_game (int dst[9][9], int src[9][9]) {
	for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
			dst[i][j] = src[i][j];
}
