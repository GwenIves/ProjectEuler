/*
 * Find the integers 1 <= a < b < c < d <= N that produce the longest sequence of integer values
 * given by arithmetic expressions using the integers as operands, operators +, -, *, / and parentheses
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utils.h"
#include "math_utils.h"
#include "linked_list.h"
#include "fraction.h"

#define OPERAND_COUNT	4
#define OPERATOR_COUNT	(OPERAND_COUNT - 1)

enum operators {PLUS = 0, MINUS, MULTIPLY, DIVIDE};
enum eval_errors {DIV_BY_ZERO = 1};

// Global variable set by evaluate () upon error
static int g_evaluate_errno = 0;

static bool next_set (int *, size_t, size_t);
static linked_list_t * get_all_values (const int *);
static int get_sequence_length (linked_list_t *);
static void evaluate_all (const char *, const int *, linked_list_t *);
static fraction_t evaluate (fraction_t, int, fraction_t);
static void store_result (linked_list_t *, fraction_t);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < OPERAND_COUNT)
		return 1;
	else if (N > CHAR_MAX) {
		/*
		 * Operands downcast to chars for processing by next_permutation ()
		 * Extend next_permutatation () to handle arbitrary integer arrays if larger N needed
		 */
		return 1;
	}

	int max_length = 0;
	int max_len_operands[OPERAND_COUNT];

	int operands[OPERAND_COUNT];

	while (next_set (operands, OPERAND_COUNT, N)) {
		linked_list_t * values = get_all_values (operands);

		int sequence_length = get_sequence_length (values);

		linked_list_free (values);

		if (sequence_length > max_length) {
			max_length = sequence_length;

			for (size_t i = 0; i < OPERAND_COUNT; i++)
				max_len_operands[i] = operands[i];
		}
	}

	for (size_t i = 0; i < OPERAND_COUNT; i++)
		printf ("%d", max_len_operands[i]);

	printf ("\n");

	return 0;
}

static void store_result (linked_list_t * list, fraction_t result) {
	if (g_evaluate_errno > 0) {
		g_evaluate_errno = 0;
		return;
	} else if (result.sign)
		return;
	else if (result.nominator == 0)
		return;
	else if (result.denominator != 1)
		return;

	int * i_ptr = x_malloc (sizeof (int));
	*i_ptr = result.nominator;

	linked_list_add_sorted (list, i_ptr, int_cmp, true);
}

static fraction_t evaluate (fraction_t a, int op, fraction_t b) {
	switch (op) {
		case PLUS:
			return fraction_add (&a, &b);
		case MINUS:
			return fraction_sub (&a, &b);
		case MULTIPLY:
			return fraction_mult (&a, &b);
		case DIVIDE:
			if (b.nominator != 0)
				return fraction_div (&a, &b);

			g_evaluate_errno = DIV_BY_ZERO;
			// Fallthrough
		default:
			return fraction_get_ (0, 1, false);
	}
}

static void evaluate_all (const char * operands, const int * operators, linked_list_t * results) {
	const int * op = operators;

	fraction_t a[OPERAND_COUNT];

	for (size_t i = 0; i < OPERAND_COUNT; i++)
		a[i] = fraction_get_ (operands[i], 1, false);

	store_result (results, evaluate (evaluate (evaluate (a[0], op[0], a[1]), op[1], a[2]), op[2], a[3]));
	store_result (results, evaluate (evaluate (a[0], op[0], a[1]), op[1], evaluate (a[2], op[2], a[3])));
	store_result (results, evaluate (evaluate (a[0], op[0], evaluate (a[1], op[1], a[2])), op[2], a[3]));
	store_result (results, evaluate (a[0], op[0], evaluate (evaluate (a[1], op[1], a[2]), op[2], a[3])));
	store_result (results, evaluate (a[0], op[0], evaluate (a[1], op[1], evaluate (a[2], op[2], a[3]))));
}

static linked_list_t * get_all_values (const int * operand_set) {
	linked_list_t * results = linked_list_create ();

	char operands[OPERAND_COUNT + 1];

	for (size_t i = 0; i < OPERAND_COUNT; i++)
		operands[i] = operand_set[i];

	operands[OPERAND_COUNT] = '\0';

	do {
		int operators[OPERATOR_COUNT];

		for (size_t i = 0; i < OPERATOR_COUNT; i++)
			operators[i] = PLUS;

		do {
			evaluate_all (operands, operators, results);
		} while (next_number (operators, OPERATOR_COUNT, DIVIDE + 1));
	} while (next_permutation (operands));

	return results;
}

static int get_sequence_length (linked_list_t * results) {
	int expected_result = 1;
	int * i_ptr = NULL;

	while ((i_ptr = linked_list_next (results, int)) != NULL)
		if (*i_ptr != expected_result++) {
			linked_list_stop_iteration (results);
			break;
		}

	return expected_result - 1;
}

static bool next_set (int * set, size_t set_size, size_t element_max) {
	static char * set_mask = NULL;

	if (set_mask == NULL) {
		set_mask = x_malloc (element_max + 1);

		for (size_t i = 0; i < set_size; i++)
			set_mask[i] = '1';

		for (size_t i = set_size; i < element_max; i++)
			set_mask[i] = '0';

		set_mask[element_max] = '\0';
	} else if (!prev_permutation (set_mask)) {
		free (set_mask);
		set_mask = NULL;

		return false;
	}

	size_t j = 0;

	for (size_t i = 0; i < set_size; i++) {
		while (set_mask[j] == '0')
			j++;

		set[i] = j + 1;

		j++;
	}

	return true;
}
