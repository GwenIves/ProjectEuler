#ifndef EULER_UTILS_H_
#define EULER_UTILS_H_

#include <stdlib.h>
#include "fraction.h"

#define count_representation_combinations(v,m,s) count_representation_combinations_ (v,m,s,NULL)

int euclid_pythagorean_triple_perim (int, int);
long stern_brocot_count (long, fraction_t *, fraction_t *);
int count_representation_combinations_ (int *, size_t, int, int **);

#endif
