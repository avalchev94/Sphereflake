#pragma once

#include "Point3D.h"

namespace Math
{
	class CMatrix
	{
	public:
		CMatrix();
		~CMatrix();

		bool	operator==(const CMatrix& mat) const;

		void	SetIdentity();
		bool	IsIdentity() const;

		void	SetUVec(const CPoint3D& uVec);
		void	SetVVec(const CPoint3D& vVec);
		void	SetWVec(const CPoint3D& wVec);
		void	SetOffset(const CPoint3D& pt);
		
		CPoint3D		GetUVec() const;
		CPoint3D		GetVVec() const;
		CPoint3D		GetWVec() const;
		CPoint3D		GetOffset() const;

		/// Math ///
		void		RotateX(double angleDeg);
		void		RotateY(double angleDeg);
		void		RotateZ(double angleDeg);

		void		Translate(double x, double y, double z);
		void		Translate(const CPoint3D& pt);

		CPoint3D	operator*(const CPoint3D& point) const;
		CMatrix		operator*(const CMatrix& matrix) const;

	public:
		double		fMat[4][3];
	};

	///////////////////////////////////////////////////////////////////
	/// a00 a01 a02  <- uVec										///
	/// a10 a11 a12  <- vVec										///
	/// a20 a21 a22  <- wVec										///
	/// a30 a31 a32  <- offset from the origin of the world matrix  ///
	///////////////////////////////////////////////////////////////////
}