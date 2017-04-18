#pragma once

#include "Point2D.h"

namespace Math
{
	class CPoint3D
	{
	public:
		CPoint3D(double _x = 0.0, double _y = 0.0, double _z = 0.0);
		CPoint3D(const CPoint2D& pt);
		~CPoint3D();

	public:
		void		SetPoint(double x, double y, double z = 0.0);

		bool		operator==(const CPoint3D& pt) const;
		bool		operator!=(const CPoint3D& pt) const;

		CPoint3D	operator+(const CPoint3D& pt) const;
		CPoint3D&	operator+=(const CPoint3D& pt);
		CPoint3D&	operator-=(const CPoint3D& pt);
		CPoint3D	operator-(const CPoint3D& pt) const;
		CPoint3D	operator*(double scalar) const;
		CPoint3D	operator/(double scalar) const;

		bool		Equal(const CPoint3D& pt, double eps) const;
		double		DistanceTo(const CPoint3D& pt) const;

	// easy access
	public:
		double x, y, z;
	};
}