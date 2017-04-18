#pragma once

#include "Primitives/Sphere.h"

using namespace Primitive;

typedef std::vector<TShapeArray>		TShape2DArray;
typedef TShapeArray::iterator			TShapeIt;

class CSphereflake
{
public:
	CSphereflake(Uint8 detailLevel, double radius, Uint8 rings = 12, Uint8 sectors = 12);
	~CSphereflake();

	void			Draw();

	CMatrix			GetMatrix() const;
	void			SetMatrix(const CMatrix& mat);

	CRGBAColor		GetColor() const;
	void			SetColor(const CRGBAColor& col);

private:
	bool	Init();
	
	void	GenerateDistrSpheres(IShapePtr pSphere
								, TShapeIt& it
								, Uint8 spheresCnt
								, double radiusRatio
								, double latitude
								, double longtitude);

private:
	const Uint8	fSpheresForLevel;

	Uint8		fLevel;
	Uint8		fRings;
	Uint8		fSectors;

	/// Geometry ///
	double			fRadius;
	TShape2DArray	fSpheres;

	/// Transformations ///
	CMatrix	fMatrix;

	/// Attributes ///
	CRGBAColor	fColor;
};