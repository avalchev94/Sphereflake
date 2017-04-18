#pragma once

#include "IShape.h"

namespace Primitive
{
	class CRect : public IShape
	{
	public:
				CRect(double width, double height);
		virtual ~CRect();

	public:
		virtual void Draw() override;

	private:
		double	fWidth;
		double	fHeight;
	};
}