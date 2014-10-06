#ifndef _MATH_UTILS_H
#define _MATH_UTILS_H

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):-(a))

char * eratosthenes_sieve (int);

int divisors_sum (int);
int gcd (int, int);

#endif
