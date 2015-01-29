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

#define allocate_array(S,I) _Generic((I), \
	int: allocate_array_int, \
	bool: allocate_array_bool)(S,I)

#define array_len(A) (sizeof(A)/sizeof((A)[0]))

#define free_array(A,L) for (size_t i = 0; i < L; i++) { free ((A)[i]); }

#define LETTERS_COUNT	26

void * x_malloc (size_t);
void * x_calloc (size_t, size_t);
void * x_realloc (void *, size_t);

ssize_t x_getline (char **, FILE *);

int * copy_int (int);
long * copy_long (long);

void swap_chars (char *, size_t, size_t);

int string_cmp (const void *, const void *);
int char_cmp (const void *, const void *);
int int_cmp (const void *, const void *);
int long_cmp (const void *, const void *);

int ** load_matrix (int *, int *);
int ** load_triangle (int *);
int ** load_square (int *);

int ** allocate_matrix_int (size_t, size_t, int);
bool ** allocate_matrix_bool (size_t, size_t, bool);

int * allocate_array_int (size_t, int);
bool * allocate_array_bool (size_t, bool);

void free_matrix_int (int **, size_t);
void free_matrix_bool (bool **, size_t);

#endif
