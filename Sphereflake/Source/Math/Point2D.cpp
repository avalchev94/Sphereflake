#include "StdAfx.h"

#include "Point2D.h"
#include "MathUtils.h"

using namespace Math;

CPoint2D::CPoint2D(double _x, double _y)
	: x(_x)
	, y(_y)
{}

CPoint2D::~CPoint2D()
{
}

void CPoint2D::SetPoint(double _x, double _y)
{
	x = _x;
	y = _y;
}

bool CPoint2D::operator==(const CPoint2D& pt) const
{
	return this->Equal(pt, Math::kEpsilon);
}

bool CPoint2D::operator!=(const CPoint2D& pt) const
{
	return !((*this) == pt);
}

CPoint2D CPoint2D::operator+(const CPoint2D& pt) const
{
	return CPoint2D(x + pt.x, y + pt.y);
}

CPoint2D CPoint2D::operator-(const CPoint2D& pt) const
{
	return CPoint2D(x - pt.x, y - pt.y);
}

CPoint2D CPoint2D::operator*(double scalar) const
{
	return CPoint2D(x * scalar, y * scalar);
}

CPoint2D CPoint2D::operator/(double scalar) const
{
	return CPoint2D(x / scalar, y / scalar);
}

double CPoint2D::Magnitude() const
{
	return sqrt(x*x + y*y);
}

bool CPoint2D::Equal(const CPoint2D& pt, double eps) const
{
	return Math::Equal(x, pt.x, eps)
		&& Math::Equal(y, pt.y, eps);
}

double CPoint2D::DistanceTo(const CPoint2D& pt) const
{
	double _x = x - pt.x;
	double _y = y - pt.y;

	return sqrt(_x*_x + _y*_y);
}