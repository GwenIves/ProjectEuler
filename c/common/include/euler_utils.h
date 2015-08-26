#ifndef EULER_UTILS_H_
#define EULER_UTILS_H_

#include <stdlib.h>
#include "fraction.h"

#define count_representation_combinations(v,m,s) count_representation_combinations_ (v,m,s,NULL)

long euclid_pythagorean_triple_perim (int, int);
long stern_brocot_count (long, const fraction_t *, const fraction_t *);
int count_representation_combinations_ (const int *, size_t, int, int **);
char * calculate_sqrt (int, size_t);
bool is_special_sum_set (const int *, size_t);
int digits_sum (long);
long evaluate_factorisation (const int *, const int *, size_t);
int get_repunit_len (int);
long p114_count_arrangements (int, int);

#endif
