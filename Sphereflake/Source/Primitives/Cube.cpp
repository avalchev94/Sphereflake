#include "StdAfx.h"

#include "Cube.h"

using namespace Primitive;

CCube::CCube(double edgeLength)
	: IShape(EType::Cube, EFace::Quad)
	, fEdgeLength(edgeLength)
{
}

CCube::~CCube()
{
}

void CCube::Draw()
{
	if (fEdgeLength <= 0 || fDrawn)
	{
		return;
	}

	///@note Create the arrays for storing the cube's data.
	fIndicesCount	= 24;
	fVerticesCount	= 24;

	///@note Allocate the needed memory.
	this->Allocate();

	///@note Get the half of the edge length. We will draw the cube in the (0,0,0).
	const double halfEdge = fEdgeLength / 2.0;

	fPoints[0].SetPoint( -halfEdge,	+halfEdge, +halfEdge );
	fPoints[1].SetPoint( +halfEdge, +halfEdge, +halfEdge );
	fPoints[2].SetPoint( +halfEdge, +halfEdge, -halfEdge );
	fPoints[3].SetPoint( -halfEdge,	+halfEdge, -halfEdge );
	for ( Uint8 i = 0; i < 4; ++i ) 
		fNormals[i].SetPoint(0.0, 1.0, 0.0);

	fPoints[4].SetPoint( -halfEdge, +halfEdge, -halfEdge );
	fPoints[5].SetPoint( +halfEdge, +halfEdge, -halfEdge );
	fPoints[6].SetPoint( +halfEdge, -halfEdge, -halfEdge );
	fPoints[7].SetPoint( -halfEdge, -halfEdge, -halfEdge );
	for ( Uint8 i = 4; i < 8; ++i )
		fNormals[i].SetPoint(0.0, 0.0, -1.0);

	fPoints[8].SetPoint( +halfEdge, +halfEdge, -halfEdge );
	fPoints[9].SetPoint( +halfEdge, +halfEdge, +halfEdge );
	fPoints[10].SetPoint( +halfEdge, -halfEdge, +halfEdge );
	fPoints[11].SetPoint( +halfEdge, -halfEdge, -halfEdge );
	for ( Uint8 i = 8; i < 12; ++i )
		fNormals[i].SetPoint(1.0, 0.0, 0.0);

	fPoints[12].SetPoint( -halfEdge, +halfEdge, +halfEdge );
	fPoints[13].SetPoint( -halfEdge, +halfEdge, -halfEdge );
	fPoints[14].SetPoint( -halfEdge, -halfEdge, -halfEdge );
	fPoints[15].SetPoint( -halfEdge, -halfEdge, +halfEdge );
	for ( Uint8 i = 12; i < 16; ++i )
		fNormals[i].SetPoint(-1.0, 0.0, 0.0);

	fPoints[16].SetPoint( +halfEdge, +halfEdge, +halfEdge );
	fPoints[17].SetPoint( -halfEdge, +halfEdge, +halfEdge );
	fPoints[18].SetPoint( -halfEdge, -halfEdge, +halfEdge );
	fPoints[19].SetPoint( +halfEdge, -halfEdge, +halfEdge );
	for ( Uint8 i = 16; i < 20; ++i )
		fNormals[i].SetPoint(0.0, 0.0, 1.0);

	fPoints[20].SetPoint( +halfEdge, -halfEdge, -halfEdge );
	fPoints[21].SetPoint( +halfEdge, -halfEdge, +halfEdge );
	fPoints[22].SetPoint( -halfEdge, -halfEdge, +halfEdge );
	fPoints[23].SetPoint( -halfEdge, -halfEdge, -halfEdge );
	for ( Uint8 i = 20; i < 24; ++i )
		fNormals[i].SetPoint(0.0, -1.0, 0.0);

	///@note Generate the indices. Every row represents two triangles.
	TVertIndex indices[] = 
	{
		0,  1,  2,  3,  // Top
		4,  5,  6,  7,  // Front
		8,  9,  10, 11, // Right
		12, 13, 14, 15, // Left
		16, 17, 18, 19, // Back
		20, 21, 22, 23  // Bottom
	};
	memcpy(fIndices, indices, sizeof(indices));

	///@note Call the base draw method.
	IShape::Draw();
}