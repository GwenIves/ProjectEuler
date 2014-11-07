#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>
#include <stdio.h>

#define swap(A,I,J) _Generic((A), \
	char *: swap_chars)(A,I,J)

void * x_malloc (size_t);
void * x_calloc (size_t, size_t);
void * x_realloc (void *, size_t);

ssize_t x_getline (char **, FILE *);

void swap_chars (char *, size_t, size_t);

int string_cmp (const void *, const void *);

#endif
