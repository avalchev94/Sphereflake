#include "StdAfx.h"

#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddShape(IShapePtr pShape)
{
	if ( pShape )
	{
		fShapes.push_back(pShape);
	}
}

void Scene::ForEachShape(TCallback callback) const
{
	for (IShapePtr ptr : fShapes)
	{
		callback(ptr);
	}
}

size_t Scene::GetShapesCount() const
{
	return fShapes.size();
}