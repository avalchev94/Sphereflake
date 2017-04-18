#pragma once

#include "IShape.h"

namespace Primitive
{
	class CSphere : public IShape
	{
	public:
				CSphere(double radius, Uint8 rings = 12, Uint8 sectors = 12);
		virtual ~CSphere();

		double	GetRadius();

	public:
		virtual	void	Draw() override;

	private:
		double	fRadius;
		Uint8	fRings;
		Uint8	fSectors;
	};
}