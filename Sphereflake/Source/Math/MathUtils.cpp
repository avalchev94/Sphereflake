#include "MathUtils.h"

namespace Math
{
	bool Equal(double a, double b, double eps)
	{
		return abs(b - a) < eps;
	}

	bool Greater(double a, double b, double eps)
	{
		return (a > b) && !Equal(a, b, eps);
	}

	bool Lesser(double a, double b, double eps)
	{
		return (a < b) && !Equal(a, b, eps);
	}

	bool GreatEqual(double a, double b, double eps)
	{
		return a >= b || Equal(a, b, eps);
	}

	bool LessEqual(double a, double b, double eps)
	{
		return a <= b || Equal(a, b, eps);
	}
}