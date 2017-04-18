#include "StdAfx.h"

#include "Application.h"
#include "Primitives/IShape.h"
#include "Primitives/Cube.h"
#include "Primitives/Rect.h"
#include "Primitives/Sphere.h"
#include "Sphereflake.h"
#include "Scene.h"
#include "Camera.h"
#include "Render/GLRender.h"

CApplication::CApplication(int argc, char** argv)
	: fArgc(argc)
	, fArgv(argv)
{
}

CApplication::~CApplication()
{
}

int CApplication::OnExecute()
{
	///@note Init the camera position.
	CCamera::GetInstance().Set(0.0, 40.0, 30.0, CPoint3D(0, 0, 0));

	///@note Init the GL renderer.
	Render::GLRendererData data;

	/// Window size and position ///
	data.fStartX				= 10;
	data.fStartY				= 10;
	data.fWidth					= 1000;
	data.fHeight				= 600;
	/// Scene lighting ///
	data.fEnableLighting		= true;
	data.fLightPosition[0]		= 10.0f; 
	data.fLightPosition[1]		= 20.0f;
	data.fLightPosition[2]		= 10.0f;
	data.fLightType				= 0.0f; // << directional
	/// Perspective ///
	data.fViewAngle				= 60;
	data.fNearZ					= 0.1;
	data.fFarZ					= 1000.0;
	/// Memory management ///
	///@WARNING Turning memory cleaning TRUE will make you rendering really slower.
	/// However, you will be able to render more objects on the scene.
	data.fMemoryCleaning		= true;
	data.fCriticalObjectsCount	= 500000; // << memory clearing if objs count >= 500000.
	/// Command input ///
	data.fArgc					= fArgc;
	data.fArgv					= fArgv;

	Render::CGLRenderer::GetInstance().Init(data);

	///@note Draw some 3D shapes on the scene.
	Primitive::IShapePtr floor( new Primitive::CRect(100, 100) );
	Scene::GetInstance().AddShape(floor);

	CMatrix floorMat = floor->GetMatrix();
	floorMat.Translate(0, -7, 0);
	
	floor->SetMatrix(floorMat);
	floor->SetColor(CRGBAColor(153, 153, 153));

	///@note Draw the sphereflake.
	CSphereflake obj(5, 6.0, 20, 20);
	obj.SetColor(CRGBAColor(0,240,0));
	obj.Draw();

	///@note Finally render the shapes added to the scene.
	Render::CGLRenderer::GetInstance().Render();

	return 0;
}