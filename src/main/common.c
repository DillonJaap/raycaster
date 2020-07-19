#include <math.h>
#include "common.h"

int max(int a, int b)
{
	return (a < b) ? a : b;
}

int get_mid_point(int a, int b)
{
	return (int) (a > b) ? (a - b) / 2.0 + b: (b - a) / 2.0 + a;
}

// true modulo operator (not remainder)
double modulo(double a, double b)
{
	double result = fmod(a, b);
	return result >= 0 ? result : result + b;
}
