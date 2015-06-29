#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void * x_malloc (size_t size) {
	void * mem = malloc (size);

	if (!mem) {
		fprintf (stderr, "Unable to allocate memory\n");
		exit (EXIT_FAILURE);
	}

	return mem;
}

void * x_calloc (size_t count, size_t size) {
	void * mem = calloc (count, size);

	if (!mem) {
		fprintf (stderr, "Unable to allocate memory\n");
		exit (EXIT_FAILURE);
	}

	return mem;
}

void * x_realloc (void * ptr, size_t size) {
	void * mem = realloc (ptr, size);

	if (size > 0 && !mem) {
		fprintf (stderr, "Unable to allocate memory\n");
		exit (EXIT_FAILURE);
	}

	return mem;
}

ssize_t x_getline (char ** line, FILE * file) {
	size_t allocated = 0;

	ssize_t len = getline (line, &allocated, file);

	if (len == -1) {
		free (*line);
		return -1;
	} else if ((*line)[len - 1] == '\n') {
		(*line)[--len] = '\0';
	}

	return len;
}

int * copy_int (int num) {
	int * i_ptr = x_malloc (sizeof (int));

	*i_ptr = num;

	return i_ptr;
}

long * copy_long (long num) {
	long * l_ptr = x_malloc (sizeof (long));

	*l_ptr = num;

	return l_ptr;
}

void swap_chars (char * seq, size_t a, size_t b) {
	char t = seq[a];
	seq[a] = seq[b];
	seq[b] = t;
}

int string_cmp (const void * a, const void * b) {
	return strcmp (* (char **) a, * (char **) b);
}

int char_cmp (const void * a, const void * b) {
	char aa = * ((char *) a);
	char bb = * ((char *) b);

	return aa - bb;
}

int int_cmp (const void * a, const void * b) {
	int aa = * ((int *) a);
	int bb = * ((int *) b);

	return aa - bb;
}

int long_cmp (const void * a, const void * b) {
	long aa = * ((long *) a);
	long bb = * ((long *) b);

	if (aa > bb)
		return 1;
	else if (aa < bb)
		return -1;
	else
		return 0;
}

int ** load_matrix (int * rows_out, int * columns_out) {
	int rows = 0;
	int columns = 0;

	if (scanf ("%d %d", &rows, &columns) != 2)
		return NULL;
	else if (rows <= 0 || columns <= 0)
		return NULL;

	int ** matrix = x_malloc (rows * sizeof (int *));

	for (int i = 0; i < rows; i++) {
		matrix[i] = x_malloc (columns * sizeof (int));

		for (int j = 0; j < columns; j++) {
			int value = 0;

			if (scanf ("%d", &value) != 1) {
				free_matrix (matrix, i);
				return NULL;
			}

			matrix[i][j] = value;

			(void) fgetc (stdin);
		}
	}

	*rows_out = rows;
	*columns_out = columns;

	return matrix;
}

int ** load_triangle (int * rows_out) {
	int rows = 0;

	if (scanf ("%d", &rows) != 1)
		return NULL;
	else if (rows <= 0)
		return NULL;

	int ** triangle = x_malloc (rows * sizeof (int *));

	for (int i = 0; i < rows; i++) {
		triangle[i] = x_malloc ((i + 1) * sizeof (int));

		for (int j = 0; j < i + 1; j++) {
			int value = 0;

			if (scanf ("%d", &value) != 1) {
				free_matrix (triangle, i);
				return NULL;
			}

			triangle[i][j] = value;
		}
	}

	*rows_out = rows;

	return triangle;
}

int ** load_square (int * rows_out) {
	int rows = 0;
	int columns = 0;

	int ** matrix = load_matrix (&rows, &columns);

	if (rows != columns) {
		free_matrix (matrix, rows);
		return NULL;
	} else {
		*rows_out = rows;
		return matrix;
	}
}

int * csv_parse_int (FILE * f, size_t * size) {
	char * line = NULL;

	if (x_getline (&line, f) == -1) {
		*size = 0;
		return NULL;
	}

	size_t commas = 0;

	for (char * l = line; *l; l++)
		if (*l == ',')
			commas++;

	*size = commas + 1;
	int * values = x_malloc (*size * sizeof (int));

	char * l = line;

	for (size_t i = 0; i <= commas ; i++) {
		values[i] = atoi (l);

		l = strchr (l, ',');

		if (l)
			l++;
	}

	free (line);

	return values;
}

int ** allocate_matrix_int (size_t rows, size_t columns, int init_value) {
	int ** matrix = x_malloc (rows * sizeof (int *));

	for (size_t i = 0; i < rows; i++) {
		matrix[i] = x_malloc (columns * sizeof (int));

		for (size_t j = 0; j < columns; j++)
			matrix[i][j] = init_value;
	}

	return matrix;
}

bool ** allocate_matrix_bool (size_t rows, size_t columns, bool init_value) {
	bool ** matrix = x_malloc (rows * sizeof (bool *));

	for (size_t i = 0; i < rows; i++) {
		matrix[i] = x_malloc (columns * sizeof (bool));

		for (size_t j = 0; j < columns; j++)
			matrix[i][j] = init_value;
	}

	return matrix;
}

int * allocate_array_int (size_t size, int init_value) {
	int * array = x_malloc (size * sizeof (int));

	for (size_t i = 0; i < size; i++)
		array[i] = init_value;

	return array;
}

long * allocate_array_long (size_t size, long init_value) {
	long * array = x_malloc (size * sizeof (long));

	for (size_t i = 0; i < size; i++)
		array[i] = init_value;

	return array;
}

bool * allocate_array_bool (size_t size, bool init_value) {
	bool * array = x_malloc (size * sizeof (bool));

	for (size_t i = 0; i < size; i++)
		array[i] = init_value;

	return array;
}

void free_matrix_int (int ** matrix, size_t rows) {
	free_array (matrix, rows);
	free (matrix);
}

void free_matrix_bool (bool ** matrix, size_t rows) {
	free_array (matrix, rows);
	free (matrix);
}

int sum_array_int (const int * a, size_t size) {
	int sum = 0;

	for (size_t i = 0; i < size; i++)
		sum += a[i];

	return sum;
}
