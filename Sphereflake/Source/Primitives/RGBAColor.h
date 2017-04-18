#pragma once

namespace Primitive
{
	class CRGBAColor
	{
	public:
		CRGBAColor(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, float alpha = 1.0f);
		~CRGBAColor();

		void	SetRGB(Uint8 r, Uint8 g, Uint8 b);
		void	SetAlpha(float alpha);

		Uint8&	R();
		Uint8&	G();
		Uint8&	B();
		float&	A();

		Uint8	GetRed() const;
		Uint8	GetGreen() const;
		Uint8	GetBlue() const;

	private:
		Uint8	fRed;
		Uint8	fGreen;
		Uint8	fBlue;
		float	fAlpha;
	};
};