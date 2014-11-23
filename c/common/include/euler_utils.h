#ifndef EULER_UTILS_H_
#define EULER_UTILS_H_

#include "fraction.h"

int euclid_pythagorean_triple_perim (int, int);
long stern_brocot_count (long, fraction_t *, fraction_t *);
int count_representation_combinations (int *, int, int, int **);

#endif
