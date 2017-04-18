#include "StdAfx.h"

#include "IShape.h"

using namespace Primitive;

IShape::IShape(const EType& type, const EFace& face)
	: fType(type)
	, fFaceType(face)
	, fDrawn(false)
	, fPoints(nullptr)
	, fNormals(nullptr)
	, fIndices(nullptr)
	, fVerticesCount(0)
	, fIndicesCount(0)
	, fMatrix()
	, fColor()
{
}

IShape::~IShape()
{
	this->Clean();
}

EType IShape::GetType() const
{
	return fType;
}

EFace IShape::GetFaceType() const
{
	return fFaceType;
}

const CPoint3D* IShape::GetPoints() const
{
	return fPoints;
}

const CPoint3D* IShape::GetNormals() const
{
	return fNormals;
}

const TVertIndex* IShape::GetIndices() const
{
	return fIndices;
}

TVertIndex IShape::GetVerticesCount() const
{
	return fVerticesCount;
}

TVertIndex IShape::GetIndicesCount() const
{
	return fIndicesCount;
}

Math::CMatrix IShape::GetMatrix() const
{
	return fMatrix;
}

void IShape::SetMatrix(const Math::CMatrix& mat)
{
	fMatrix = mat;
}

CRGBAColor IShape::GetColor() const
{
	return fColor;
}

void IShape::SetColor(const CRGBAColor& col)
{
	fColor = col;
}

void IShape::Draw()
{
	this->SetDrawn(true);
}

void IShape::Allocate()
{
	if (fDrawn)
	{
		return;
	}

	try
	{
		if (fVerticesCount > 0)
		{
			fPoints = new CPoint3D[fVerticesCount];
			fNormals = new CPoint3D[fVerticesCount];
		}

		if (fIndicesCount > 0)
		{
			fIndices = new TVertIndex[fIndicesCount];
		}
	}
	catch(std::bad_alloc ex)
	{
		printf("Error: %s", ex.what());
		exit(1);
	}
}

void IShape::SetDrawn(bool drawn)
{
	fDrawn = drawn;
}

void IShape::Clean()
{
	///@note Delete the dynamic allocated memory.
	if (fPoints)
	{
		delete[] fPoints;
	}

	if (fNormals)
	{
		delete[] fNormals;
	}

	if (fIndices)
	{
		delete[] fIndices;
	}

	///@note Reset the counters.
	fVerticesCount	= 0;
	fIndicesCount	= 0;

	///@note Turn off the flag.
	this->SetDrawn(false);
}