#include <assert.h>
#include <stdio.h>
#include "geometry.h"

static void point_line_cmp_test (void);
static void get_line_equation_test (void);

int main (void) {
	point_line_cmp_test ();
	get_line_equation_test ();

	printf ("All geometry tests passed\n");

	return 0;
}

static void point_line_cmp_test (void) {
	line_equation_t eq = {.a = 2, .b = 3, .c = 4};

	point_t p1 = {.x = 1, .y = -2};
	point_t p2 = {.x = 2, .y = -2};
	point_t p3 = {.x = -1, .y = -2};

	assert (point_line_cmp (&eq, &p1) == 0);
	assert (point_line_cmp (&eq, &p2) > 0);
	assert (point_line_cmp (&eq, &p3) < 0);
}

static void get_line_equation_test (void) {
	point_t a1 = {.x = 3, .y = 1};
	point_t b1 = {.x = 1, .y = 2};

	line_equation_t eq = get_line_equation (&a1, &b1);

	assert (eq.a == 1);
	assert (eq.b == 2);
	assert (eq.c == -5);

	point_t a2 = {.x = 3, .y = 1};
	point_t b2 = {.x = 1, .y = 1};

	eq = get_line_equation (&a2, &b2);

	assert (eq.a == 0);
	assert (eq.b == 2);
	assert (eq.c == -2);

	point_t a3 = {.x = 1, .y = 1};
	point_t b3 = {.x = 1, .y = 2};

	eq = get_line_equation (&a3, &b3);

	assert (eq.a == 1);
	assert (eq.b == 0);
	assert (eq.c == -1);
}
