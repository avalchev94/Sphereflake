#include "StdAfx.h"

#include "Rect.h"

using namespace Primitive;

CRect::CRect(double width, double height)
	: IShape(EType::Rectangle, EFace::Quad)
	, fWidth(width)
	, fHeight(height)
{
}

CRect::~CRect()
{
}

void CRect::Draw()
{
	///@note We need positive height and width.
	if (fWidth <= 0.0 || fHeight <= 0.0 || fDrawn)
	{
		return;
	}

	///@note We will separate the rect to two triangles.
	fVerticesCount = 4;
	fIndicesCount  = 4;

	this->Allocate();

	///@note Generate the verices.
	const double halfWidth = fWidth / 2;
	const double halfHeight = fHeight / 2;

	fPoints[0].SetPoint( -halfHeight, 0.0, +halfWidth );
	fPoints[1].SetPoint( +halfHeight, 0.0, +halfWidth );
	fPoints[2].SetPoint( +halfHeight, 0.0, -halfWidth );
	fPoints[3].SetPoint( -halfHeight, 0.0, -halfWidth );
	for (Uint8 i = 0; i < 4; ++i)
	{
		fNormals[i].SetPoint(0.0, 1.0, 0.0);
	}

	///@note Generate the faces.
	fIndices[0] = 0; fIndices[1] = 1;
	fIndices[3] = 3; fIndices[2] = 2;

	///@note Call the base draw method.
	IShape::Draw();
}