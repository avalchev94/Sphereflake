#pragma once

#include <math.h>

namespace Math
{
	/// Constants ///
	const double	kEpsilon = 0.001;
	const double	kPI	= 3.141592653589793239;
	const double	kPI_2 = kPI / 2.0;
	const double	kRadiansPerDegree = kPI / 180.0;
	const double	kDegreesPerRadian = 180.0 / kPI;

	/// Comparison doubles ///
	bool	Equal(double a, double b, double eps = kEpsilon);
	bool	Greater(double a, double b, double eps = kEpsilon);
	bool	Lesser(double a, double b, double eps = kEpsilon);
	bool	GreatEqual(double a, double b, double eps = kEpsilon);
	bool	LessEqual(double a, double b, double eps = kEpsilon);
}