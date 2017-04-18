#pragma once

#include "Primitives/IShape.h"
#include "GL/freeglut.h"

namespace Render
{
	//////////////////////////////////////////////////////////////////////
	/// Keyboard keys ///
	const unsigned char kEscape = 27;

	//////////////////////////////////////////////////////////////////////
	/// Camera actions factors ///
	const double	kZoomFactor = 1.5;
	const double	kMoveFactor = 0.0001;

	//////////////////////////////////////////////////////////////////////
	struct GLRendererData
	{
		/// Initial position of the GL window ///
		int fStartX;
		int fStartY;

		/// Initial size of the GL window ///
		int fHeight;
		int fWidth;

		/// Initial light data ///
		bool	fEnableLighting;
		float	fLightPosition[3];
		float	fLightType; // << 0.0f for directional
							// << 1.0f for positional

		/// Initial camera perspective ///
		double	fViewAngle;
		double	fNearZ;
		double	fFarZ;

		/// Memory management ///
		bool	fMemoryCleaning;
		int		fCriticalObjectsCount;

		/// Command input data ///
		int		fArgc;
		char**	fArgv;
	};

	///////////////////////////////////////////////////////////////////
	class CGLRenderer
	{
		SINGELTON(CGLRenderer);
	public:
		~CGLRenderer();

		void	Init(const GLRendererData& data);
		void	Render();

	/// GL callbacks ///
	protected:
		static void		DrawScene();
		static void		OnMouseClick(int button, int state, int x, int y);
		static void		OnMouseMove(int x, int y);
		static void		OnKeyboardClick(unsigned char c, int x, int y);
		static void		OnWindowsReshape(int width, int height);

	private:
		static void		DrawShape(IShapePtr pShape);

	private:
		bool	fInit;
	};
}