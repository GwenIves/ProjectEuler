#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define swap(A,I,J) _Generic((A), \
	char *: swap_chars)(A,I,J)

#define allocate_matrix(R,C,I) _Generic((I), \
	int: allocate_matrix_int, \
	bool: allocate_matrix_bool)(R,C,I)

#define free_matrix(M,R) _Generic((M), \
	int**: free_matrix_int, \
	bool**: free_matrix_bool)(M,R)

#define array_len(A) (sizeof(A)/sizeof(A[0]))

#define free_array(A,L) for (size_t i = 0; i < L; i++) { free (A[i]); }

void * x_malloc (size_t);
void * x_calloc (size_t, size_t);
void * x_realloc (void *, size_t);

ssize_t x_getline (char **, FILE *);

void swap_chars (char *, size_t, size_t);

int string_cmp (const void *, const void *);
int char_cmp (const void *, const void *);

int ** load_matrix (int *, int *);
int ** load_triangle (int *);
int ** load_square (int *);

int ** allocate_matrix_int (size_t, size_t, int);
bool ** allocate_matrix_bool (size_t, size_t, bool);

void free_matrix_int (int **, int);
void free_matrix_bool (bool **, int);

#endif
