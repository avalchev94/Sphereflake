#include "StdAfx.h"

#include "RGBAColor.h"

using namespace Primitive;

CRGBAColor::CRGBAColor(Uint8 r, Uint8 g, Uint8 b, float a)
	: fRed(r)
	, fGreen(g)
	, fBlue(b)
	, fAlpha(a)
{
}

CRGBAColor::~CRGBAColor()
{
}

void CRGBAColor::SetRGB(Uint8 r, Uint8 g, Uint8 b)
{
	fRed = r;
	fGreen = g;
	fBlue = b;
}

void CRGBAColor::SetAlpha(float alpha)
{
	fAlpha = alpha > 1.0f ? 1.0f : alpha;
}

Uint8& CRGBAColor::R()
{
	return fRed;
}

Uint8& CRGBAColor::G()
{
	return fGreen;
}

Uint8& CRGBAColor::B()
{
	return fBlue;
}

float& CRGBAColor::A()
{
	return fAlpha;
}

Uint8 CRGBAColor::GetRed() const
{
	return fRed;
}

Uint8 CRGBAColor::GetGreen() const
{
	return fGreen;
}

Uint8 CRGBAColor::GetBlue() const
{
	return fBlue;
}