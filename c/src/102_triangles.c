/*
 * Find how many triangles read from stdin contain the origin of coordinates
 * The stdin format should be six comma-separated integers per line
 * giving A_x, A_y, B_x, B_y, C_x, C_y
 */

#include <stdio.h>
#include <stdbool.h>
#include "geometry.h"

static bool read_triangle (triangle_t *);
static bool contains_origin (const triangle_t *);
static bool in_one_halfplane (const line_equation_t *, const point_t *, const point_t *);
static bool verify (const point_t *, const point_t *, const point_t *);

int main (void) {
	triangle_t t;

	int count = 0;

	while (read_triangle (&t))
		if (contains_origin (&t))
			count++;

	printf ("%d\n", count);

	return 0;
}

static bool read_triangle (triangle_t * t) {
	return scanf ("%d,%d,%d,%d,%d,%d\n", &t->a.x, &t->a.y, &t->b.x, &t->b.y, &t->c.x, &t->c.y) == 6;
}

static bool contains_origin (const triangle_t * t) {
	const point_t * a = &t->a;
	const point_t * b = &t->b;
	const point_t * c = &t->c;

	if (!verify (a, b, c))
		return false;
	else if (!verify (b, c, a))
		return false;
	else if (!verify (c, a, b))
		return false;

	return true;
}

static bool verify (const point_t * a, const point_t * b, const point_t * c) {
	static point_t origin = {.x = 0, .y = 0};

	line_equation_t ab = get_line_equation (a, b);

	return in_one_halfplane (&ab, c, &origin);
}

static bool in_one_halfplane (const line_equation_t * eq, const point_t * a, const point_t * b) {
	int cmp_a = point_line_cmp (eq, a);
	int cmp_b = point_line_cmp (eq, b);

	if (cmp_a >= 0 && cmp_b >= 0)
		return true;
	else if (cmp_a < 0 && cmp_b < 0)
		return true;
	else
		return false;
}
