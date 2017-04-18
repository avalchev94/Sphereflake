#pragma once

#include "Primitives/IShape.h"

using namespace Primitive;

///////////////////////////////////////////////////////////////////////
typedef void(*TCallback)(IShapePtr);

///////////////////////////////////////////////////////////////////////
class Scene
{
	SINGELTON(Scene)
public:
	~Scene();

	void	AddShape(IShapePtr shape);
	void	ForEachShape(TCallback callback) const;

	size_t	GetShapesCount() const;

private:
	TShapeArray fShapes;
};