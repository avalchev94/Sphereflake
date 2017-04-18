#pragma once

namespace Math
{
	class CPoint2D
	{
	public:
		CPoint2D(double _x = 0.0, double _y = 0.0);
		~CPoint2D();

	public:
		void		SetPoint(double x, double y);

		bool		operator==(const CPoint2D& pt) const;
		bool		operator!=(const CPoint2D& pt) const;

		CPoint2D	operator+(const CPoint2D& pt) const;
		CPoint2D	operator-(const CPoint2D& pt) const;
		CPoint2D	operator*(double scalar) const;
		CPoint2D	operator/(double scalar) const;

		double		Magnitude() const;
		bool		Equal(const CPoint2D& pt, double eps) const;
		double		DistanceTo(const CPoint2D& pt) const;

	// easy access
	public:
		double x, y;
	};
}