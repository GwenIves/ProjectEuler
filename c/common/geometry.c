#include "geometry.h"

int point_line_cmp (const line_equation_t * eq, const point_t * p) {
	return eq->a * p->x + eq->b * p->y + eq->c;
}

line_equation_t get_line_equation (const point_t * a, const point_t * b) {
	line_equation_t eq;

	eq.a = b->y - a->y;
	eq.b = a->x - b->x;
	eq.c = -a->x * eq.a - a->y * eq.b;

	return eq;
}
