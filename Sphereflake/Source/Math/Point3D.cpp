#include "StdAfx.h"

#include "Point3D.h"
#include "MathUtils.h"

using namespace Math;

CPoint3D::CPoint3D(double _x, double _y, double _z)
	: x(_x)
	, y(_y)
	, z(_z)
{
}

CPoint3D::CPoint3D(const CPoint2D& pt)
	: x(pt.x)
	, y(pt.y)
	, z(0.0)
{
}

CPoint3D::~CPoint3D()
{
}

void CPoint3D::SetPoint(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}

bool CPoint3D::operator==(const CPoint3D& pt) const
{
	return this->Equal(pt, Math::kEpsilon);
}

bool CPoint3D::operator!=(const CPoint3D& pt) const
{
	return !((*this) == pt);
}

CPoint3D CPoint3D::operator+(const CPoint3D& pt) const
{
	return CPoint3D(x + pt.x, y + pt.y, z + pt.z);
}

CPoint3D& CPoint3D::operator+=(const CPoint3D& pt)
{
	x += pt.x;
	y += pt.y;
	z += pt.z;

	return *this;
}

CPoint3D& CPoint3D::operator-=(const CPoint3D& pt)
{
	x -= pt.x;
	y -= pt.y;
	z -= pt.z;

	return *this;
}

CPoint3D CPoint3D::operator-(const CPoint3D& pt) const
{
	return CPoint3D(x - pt.x, y - pt.y, z - pt.z);
}

CPoint3D CPoint3D::operator*(double scalar) const
{
	return CPoint3D(x * scalar, y * scalar, z * scalar);
}

CPoint3D CPoint3D::operator/(double scalar) const
{
	return CPoint3D(x / scalar, y / scalar, z / scalar);
}

bool CPoint3D::Equal(const CPoint3D& pt, double eps) const
{
	return Math::Equal(x, pt.x, eps)
		&& Math::Equal(y, pt.y, eps)
		&& Math::Equal(z, pt.z, eps);
}

double CPoint3D::DistanceTo(const CPoint3D& pt) const
{
	double _x = x - pt.x;
	double _y = y - pt.y;
	double _z = z - pt.z;

	return sqrt(_x*_x + _y*_y + _z*_z);
}