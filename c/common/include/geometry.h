#ifndef GEOMETRY_H_
#define GEOMETRY_H_

typedef struct {
	int x;
	int y;
} point_t;

typedef struct {
	point_t a;
	point_t b;
	point_t c;
} triangle_t;

typedef struct {
	int a;
	int b;
	int c;
} line_equation_t;

line_equation_t get_line_equation (const point_t *, const point_t *);
int point_line_cmp (const line_equation_t *, const point_t *);

#endif
