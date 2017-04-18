#include "StdAfx.h"

#include "Matrix.h"

using namespace Math;

CMatrix::CMatrix()
{
	///@note Set identity matrix by default.
	this->SetIdentity();
}

CMatrix::~CMatrix()
{
}

bool CMatrix::operator==(const CMatrix& mat) const
{
#define EQUAL(n) Equal(fMat[n][0], mat.fMat[n][0]) \
			  && Equal(fMat[n][1], mat.fMat[n][1]) \
			  && Equal(fMat[n][2], mat.fMat[n][2])

	return EQUAL(0) && EQUAL(1) && EQUAL(2) && EQUAL(3);
}

void CMatrix::SetIdentity()
{
	///@note Set the identity matrix
	/// 1 0 0
	/// 0 1 0
	/// 0 0 1
	/// 0 0 0

	fMat[0][0] = 1; fMat[0][1] = 0; fMat[0][2] = 0;
	fMat[1][0] = 0; fMat[1][1] = 1; fMat[1][2] = 0;
	fMat[2][0] = 0; fMat[2][1] = 0; fMat[2][2] = 1;
	fMat[3][0] = 0; fMat[3][1] = 0; fMat[3][2] = 0;
}

bool CMatrix::IsIdentity() const
{
	///@note By default the newly created matrix is identity.
	CMatrix identityMatrix;
	return *this == identityMatrix;
}

void CMatrix::SetUVec(const CPoint3D& uVec)
{
	fMat[0][0] = uVec.x;
	fMat[0][1] = uVec.y;
	fMat[0][2] = uVec.z;
}

void CMatrix::SetVVec(const CPoint3D& vVec)
{
	fMat[1][0] = vVec.x;
	fMat[1][1] = vVec.y;
	fMat[1][2] = vVec.z;
}

void CMatrix::SetWVec(const CPoint3D& wVec)
{
	fMat[2][0] = wVec.x;
	fMat[2][1] = wVec.y;
	fMat[2][2] = wVec.z;
}

void CMatrix::SetOffset(const CPoint3D& offset)
{
	fMat[3][0] = offset.x;
	fMat[3][1] = offset.y;
	fMat[3][2] = offset.z;
}

CPoint3D CMatrix::GetUVec() const
{
	return CPoint3D(fMat[0][0], fMat[0][1], fMat[0][2]);
}

CPoint3D CMatrix::GetVVec() const
{
	return CPoint3D(fMat[1][0], fMat[1][1], fMat[1][2]);
}

CPoint3D CMatrix::GetWVec() const
{
	return CPoint3D(fMat[2][0], fMat[2][1], fMat[2][2]);
}

CPoint3D CMatrix::GetOffset() const
{
	return CPoint3D(fMat[3][0], fMat[3][1], fMat[3][2]);
}

void CMatrix::RotateX(double angleDeg)
{
	double ang	= angleDeg * kRadiansPerDegree;
	double c	= cos(ang);
	double s	= sin(ang);
	
	double m10 = fMat[1][0] * c + fMat[2][0] * s;
	double m11 = fMat[1][1] * c + fMat[2][1] * s;
	double m12 = fMat[1][2] * c + fMat[2][2] * s;
			   
	double m20 = - fMat[1][0] * s + fMat[2][0] * c;
	double m21 = - fMat[1][1] * s + fMat[2][1] * c;
	double m22 = - fMat[1][2] * s + fMat[2][2] * c;

	fMat[1][0] = m10;
	fMat[1][1] = m11;
	fMat[1][2] = m12;
			   
	fMat[2][0] = m20;
	fMat[2][1] = m21;
	fMat[2][2] = m22;
}

void CMatrix::RotateY(double angleDeg)
{
	double ang	= angleDeg * kRadiansPerDegree;
	double c	= cos(ang);
	double s	= sin(ang);

	double m00 = fMat[0][0] * c - fMat[2][0] * s;
	double m01 = fMat[0][1] * c - fMat[2][1] * s;
	double m02 = fMat[0][2] * c - fMat[2][2] * s;
			   
	double m20 = fMat[0][0] * s + fMat[2][0] * c;
	double m21 = fMat[0][1] * s + fMat[2][1] * c;
	double m22 = fMat[0][2] * s + fMat[2][2] * c;
			   
	fMat[0][0] = m00;
	fMat[0][1] = m01;
	fMat[0][2] = m02;
			   
	fMat[2][0] = m20;
	fMat[2][1] = m21;
	fMat[2][2] = m22;
}

void CMatrix::RotateZ(double angleDeg)
{
	double ang	= angleDeg * kRadiansPerDegree;
	double c	= cos(ang);
	double s	= sin(ang);

	double m00	= fMat[0][0] * c + fMat[1][0] * s;
	double m01	= fMat[0][1] * c + fMat[1][1] * s;
	double m02	= fMat[0][2] * c + fMat[1][2] * s;

	fMat[1][0] = -fMat[0][0] * s + fMat[1][0] * c;
	fMat[1][1] = -fMat[0][1] * s + fMat[1][1] * c;
	fMat[1][2] = -fMat[0][2] * s + fMat[1][2] * c;
	 				  
	fMat[0][0] = m00;
	fMat[0][1] = m01;
	fMat[0][2] = m02;
}

void CMatrix::Translate(double x, double y, double z)
{
	fMat[3][0] += x;
	fMat[3][1] += y;
	fMat[3][2] += z;
}

void CMatrix::Translate(const CPoint3D& pt)
{
	this->Translate(pt.x, pt.y, pt.z);
}

/// Point transformation ///
CPoint3D CMatrix::operator*(const CPoint3D& pt) const
{
	CPoint3D trPt;
	trPt.x = pt.x * fMat[0][0] + pt.y * fMat[1][0] + pt.z * fMat[2][0] + fMat[3][0];
	trPt.y = pt.x * fMat[0][1] + pt.y * fMat[1][1] + pt.z * fMat[2][1] + fMat[3][1];
	trPt.z = pt.x * fMat[0][2] + pt.y * fMat[1][2] + pt.z * fMat[2][2] + fMat[3][2];

	return trPt;
}

CMatrix CMatrix::operator*(const CMatrix& mat) const
{
	///@note Normal matrix multiplication: row*col
	CMatrix trMat;
	trMat.fMat[0][0] = mat.fMat[0][0] * fMat[0][0] + mat.fMat[1][0] * fMat[0][1] + mat.fMat[2][0] * fMat[0][2];
	trMat.fMat[0][1] = mat.fMat[0][1] * fMat[0][0] + mat.fMat[1][1] * fMat[0][1] + mat.fMat[2][1] * fMat[0][2];
	trMat.fMat[0][2] = mat.fMat[0][2] * fMat[0][0] + mat.fMat[1][2] * fMat[0][1] + mat.fMat[2][2] * fMat[0][2];
	trMat.fMat[1][0] = mat.fMat[0][0] * fMat[1][0] + mat.fMat[1][0] * fMat[1][1] + mat.fMat[2][0] * fMat[1][2];
	trMat.fMat[1][1] = mat.fMat[0][1] * fMat[1][0] + mat.fMat[1][1] * fMat[1][1] + mat.fMat[2][1] * fMat[1][2];
	trMat.fMat[1][2] = mat.fMat[0][2] * fMat[1][0] + mat.fMat[1][2] * fMat[1][1] + mat.fMat[2][2] * fMat[1][2];
	trMat.fMat[2][0] = mat.fMat[0][0] * fMat[2][0] + mat.fMat[1][0] * fMat[2][1] + mat.fMat[2][0] * fMat[2][2];
	trMat.fMat[2][1] = mat.fMat[0][1] * fMat[2][0] + mat.fMat[1][1] * fMat[2][1] + mat.fMat[2][1] * fMat[2][2];
	trMat.fMat[2][2] = mat.fMat[0][2] * fMat[2][0] + mat.fMat[1][2] * fMat[2][1] + mat.fMat[2][2] * fMat[2][2];
	
	///@note <ultiply like normal matrix multiplication and after that add the offset.
	trMat.fMat[3][0] = mat.fMat[0][0] * fMat[3][0] + mat.fMat[1][0] * fMat[3][1] + mat.fMat[2][0] * fMat[3][2] + mat.fMat[3][0];
	trMat.fMat[3][1] = mat.fMat[0][1] * fMat[3][0] + mat.fMat[1][1] * fMat[3][1] + mat.fMat[2][1] * fMat[3][2] + mat.fMat[3][1];
	trMat.fMat[3][2] = mat.fMat[0][2] * fMat[3][0] + mat.fMat[1][2] * fMat[3][1] + mat.fMat[2][2] * fMat[3][2] + mat.fMat[3][2];

	return trMat;
}