#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>

#define swap(A,I,J) _Generic((A), \
	char *: swap_chars)(A,I,J)

void * x_malloc (size_t);
void * x_calloc (size_t, size_t);
void * x_realloc (void *, size_t);

void swap_chars (char *, size_t, size_t);

#endif
