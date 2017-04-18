#include "StdAfx.h"

#include "Sphere.h"

using namespace Primitive;

CSphere::CSphere(double radius, Uint8 rings, Uint8 sectors)
	: IShape(EType::Sphere, EFace::Quad)
	, fRadius(radius)
	, fRings(rings)
	, fSectors(sectors)
{
}

CSphere::~CSphere()
{
}

double CSphere::GetRadius()
{
	return fRadius;
}

void CSphere::Draw()
{
	if ( fSectors <= 0 || fRings <= 0 || fRadius <= 0.0 || fDrawn )
	{
		return;
	}

	///@note Allocate memory for the geometry data.
	fVerticesCount = fRings * fSectors * 3;
	fIndicesCount = fRings * fSectors * 4;

	this->Allocate();

	const double R = 1.0 / (fRings - 1);
	const double S = 1.0 / (fSectors - 1);
	
	///@note Calculate the points and the normals.
	CPoint3D* p = &fPoints[0];
	CPoint3D* n = &fNormals[0];
	
	for (Uint16 r = 0; r < fRings; ++r)
	{
		for (Uint16 s = 0; s < fSectors; ++s) 
		{
			const double x = cos(2.0 * kPI * s * S) * sin(kPI * r * R);
			const double y = sin(-kPI_2 + kPI * r * R);
			const double z = sin(2.0 * kPI * s * S) * sin(kPI * r * R);
	
			///@note Set the points.
			p->x = x * fRadius;
			p->y = y * fRadius;
			p->z = z * fRadius;

			///@note Set the normals.
	        n->x = x;
	        n->y = y;
	        n->z = z;

			++p;
			++n;
		}
	}
	
	///@note Add the indices.
	TVertIndex* i = &fIndices[0];

	for (Uint16 r = 0; r < fRings; ++r)
	{
		for(Uint16 s = 0; s < fSectors; ++s)
		{
			*i++ = (r + 1) * fSectors + (s + 1);
			*i++ = (r + 1) * fSectors + s;
			*i++ = r * fSectors + s;
			*i++ = r * fSectors + (s + 1);
		}
	}

	///@note Call the base draw method.
	IShape::Draw();
}