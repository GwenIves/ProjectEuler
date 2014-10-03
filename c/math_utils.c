#include <stdlib.h>
#include <math.h>
#include "utils.h"

char * eratosthenes_sieve (int size) {
	char * sieve = x_malloc (size);

	for (int i = 2; i < size; i++)
		sieve[i] = 1;

	int upper_limit = sqrt (size);
	for (int i = 2; i < upper_limit; i++)
		if (sieve[i])
			for (int j = i * i; j < size; j += i)
				sieve[j] = 0;

	return sieve;
}
