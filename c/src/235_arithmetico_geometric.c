/*
 * Consider the arithmetico-geometric sequence u(k) = (900 - 3k) * r^(k-1)
 * and its sum between 1 and n inclusive, s(n)
 * Find the value of r for which s(5,000) = -600,000,000,000
 */

#include <stdio.h>
#include <math.h>
#include "math_utils.h"

#define EPS	0.0000000000001
#define VAL	-600000000000
#define N	5000

static double value (double, double, double);

int main (void) {
	/*
	 * Use the equation for the sum of an arithmetico-geometric sequence
	 * The function is continuous in (-inf, 1) and (1, inf)
	 * Plot the function (eg. using gnuplot) to see that the desired value is somewhere in (1,2)
	 * Then, use the simple bisection method to find the root
	 */

	double a = 1.0 + EPS;
	double b = 2.0;

	while (true) {
		double c = (a + b) / 2;
		double span = b - a;
		double fa = value (a, N, VAL);
		double fc = value (c, N, VAL);

		if (ABS (fc) < EPS || span < EPS) {
			printf ("%.12f\n", c);
			return 0;
		} else if (fa * fc > 0)
			a = c;
		else
			b = c;
	}
}

static double value (double x, double n, double val) {
	double a = 897.0;
	double d = -3.0;

	double f = a + d * x * (1 - pow (x, n - 1)) / (1 - x) - (a + d * (n - 1)) * pow (x, n);
	f /= 1 - x;

	return f - val;
}
