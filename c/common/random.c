#include <stdlib.h>
#include "random.h"

int next_lfg (int offset) {
	static int previous_values[55];
	static size_t cursor = 0;

	static int i = 1;

	int next_val = 0;

	if (i <= 55) {
		next_val = (100003L + i * (-200003L + 300007L * i * i)) % LFG_MOD - offset;
	} else {
		size_t i_24 = (cursor + 31) % 55;
		size_t i_55 = cursor;

		next_val = (previous_values[i_24] + previous_values[i_55] + 1000000) % LFG_MOD - offset;
	}

	previous_values[cursor++] = next_val;

	if (cursor >= 55)
		cursor = 0;

	i++;

	return next_val;
}

int next_lcg (void) {
	static int t = 0;

	t = (615949L * t + 797807) % LCG_MOD;

	return t - LCG_OFFSET;
}
