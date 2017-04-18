#pragma once

#include "IShape.h"

namespace Primitive
{
	class CCube : public IShape
	{
	public:
					CCube(double edgeLength);
		virtual		~CCube();

	public:
		virtual void	Draw() override;

	private:
		double	fEdgeLength;
	};
}