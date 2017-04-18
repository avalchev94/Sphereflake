#include "StdAfx.h"

#include "Sphereflake.h"
#include "Scene.h"

CSphereflake::CSphereflake(Uint8 detailLevel, double radius, Uint8 rings, Uint8 sectors)
	: fLevel(detailLevel)
	, fRings(rings)
	, fSectors(sectors)
	, fSpheresForLevel(9)
	, fRadius(radius)
	, fSpheres()
	, fMatrix() // identity
{
}

CSphereflake::~CSphereflake()
{
}

CMatrix CSphereflake::GetMatrix() const
{
	return fMatrix;
}

void CSphereflake::SetMatrix(const CMatrix& mat)
{
	fMatrix = mat;
}

CRGBAColor CSphereflake::GetColor() const
{
	return fColor;
}

void CSphereflake::SetColor(const CRGBAColor& col)
{
	fColor = col;
}

bool CSphereflake::Init()
{
	if (fLevel <= 0)
	{
		return false;
	}

	fSpheres.resize(fLevel);

	///@note Level 1 has 1 sphere.
	fSpheres[0].resize(1);

	///@note Resize the rest levels by multipling the previous count by the spheresForLevel.
	for (Uint8 lvl = 1; lvl < fLevel; ++lvl)
	{
		const size_t prevLvl = fSpheres[lvl - 1].size();

		fSpheres[lvl].resize(prevLvl * fSpheresForLevel);
	}

	return true;
}

void CSphereflake::Draw()
{
	if (!this->Init())
	{
		return;
	}

	///@note Draw the sphere for level 1.
	IShapePtr baseSphere(new CSphere(fRadius, fRings, fSectors));
	baseSphere->SetMatrix(fMatrix);

	fSpheres[0][0] = baseSphere;

	///@note Making a loop traversing each I lvl and generating spheres for I+1 lvl.
	for (Uint8 lvl = 0; lvl < fLevel - 1; ++lvl)
	{
		///@note Get the iterator for the next level array.
		TShapeIt it = fSpheres[lvl+1].begin();

		///@note For each sphere of level I ....
		for (IShapePtr pSphere : fSpheres[lvl])
		{
			this->GenerateDistrSpheres(pSphere		/// << sphere to generate for
									  , it			/// << next level iterator
									  , 6			/// << count of the spheres to generate
									  , 1.0/3.0		/// << radius of the new spheres will be 1/3 smaller
									  , 0.0			/// << at latitude 0, a.k.a equator
									  , 0.0);		/// << start from 0 longtitude

			this->GenerateDistrSpheres(pSphere		/// << sphere to generate for
									  , it			/// << next level iterator
									  , 3			/// << 3 spheres to generate
									  , 1.0/3.0		/// << 1/3 smaller radius
									  , 60.0		/// << 60 north latitude
									  , 30.0);		/// << start from 30 longtitude
		}
	}

	///@note Draw the spheres and add them to the scene.
	Scene& scene = Scene::GetInstance();

	CRGBAColor col = fColor;

	for (auto& level : fSpheres)
	{
		for (auto& pSphere : level)
		{
			pSphere->SetColor(col);
			scene.AddShape(pSphere);
		}

		///@note Generate some random color to easily
		/// distinguish the different levels.
		col.SetRGB(rand() % 255, rand() % 255, rand() % 255);
	}
}

void CSphereflake::GenerateDistrSpheres(IShapePtr pSphere
									  , TShapeIt& it
									  , Uint8 spheresCnt
									  , double radiusRatio
									  , double latitude
									  , double longtitude)
{
	if (spheresCnt <= 0)
	{
		return;
	}

	///@note Get the old radius. Using it, calculate the new spheres' radius.
	const double oldR = std::static_pointer_cast<CSphere>(pSphere)->GetRadius();
	const double newR = oldR * radiusRatio;

	///@note Calculate the distribution value. 
	const double distributionAng = 360.0 / spheresCnt;

	///@note Get the sphere matrix. We will use it later.
	const CMatrix matrix = pSphere->GetMatrix();

	///@note Finally draw the spheres.
	double startAng = longtitude;
	for (Uint8 i = 0; i < spheresCnt; ++i)
	{
		///@note Create the sphere and get the new matrix. It is identity by default.
		IShapePtr newSphere(new CSphere(newR, fRings, fSectors));
		CMatrix newMatrix = newSphere->GetMatrix();

		///@note Calculate the point for the newly created sphere.
		CPoint3D offset;
		offset.x = (oldR+newR) * cos(latitude*kRadiansPerDegree) * cos(startAng*kRadiansPerDegree);
		offset.z = (oldR+newR) * cos(latitude*kRadiansPerDegree) * sin(startAng*kRadiansPerDegree);
		offset.y = (oldR+newR) * sin(latitude*kRadiansPerDegree);

		///@note Translate the new matrix with the offset.
		newMatrix.Translate(offset);

		///@note Rotate in order "connection" point between the two spheres to be south pole.
		newMatrix.RotateY(-startAng);
		newMatrix.RotateZ(latitude - 90);

		///@note Finally, multiply the matrices and we have the correct position. 
		newSphere->SetMatrix(newMatrix*matrix);

		///@note Find place
		*it++ = newSphere;

		///@note Increase the angle.
		startAng += distributionAng;
	}
}