#pragma once

#include <memory>
#include <vector>
#include "RGBAColor.h"

namespace Primitive
{
	using namespace Math;
	
	//////////////////////////////////////////////////////////////////
	typedef Uint32 TVertIndex;

	///////////////////////////////////////////////////////////////////
	enum class EType
	{
		Rectangle,
		Cube,
		Sphere
	};

	enum class EFace
	{
		Triangle,
		Quad
	};
	
	///////////////////////////////////////////////////////////////////
	class IShape
	{
		DISALLOW_COPY(IShape)
	public:
						IShape(const EType& type, const EFace& face);
		virtual			~IShape();

		EType			GetType() const;
		EFace			GetFaceType() const;

		/// Geometry ///
		const CPoint3D*		GetPoints() const;
		const CPoint3D*		GetNormals() const;
		const TVertIndex*	GetIndices() const;

		TVertIndex			GetVerticesCount() const;
		TVertIndex			GetIndicesCount() const;

		/// Transformations ///
		Math::CMatrix	GetMatrix() const;
		void			SetMatrix(const Math::CMatrix& mat);

		/// Attributes ///
		CRGBAColor		GetColor() const;
		void			SetColor(const CRGBAColor& col);

	/// Virtual methods ///
	public:
		virtual void	Draw();
		virtual void	Clean();

	protected:
		void			Allocate();
		void			SetDrawn(bool drawn);

	protected:
		EType			fType;
		EFace			fFaceType;
		bool			fDrawn;

		/// Geometry ///
		CPoint3D*		fPoints;  // The point and \  forms one
		CPoint3D*		fNormals; // the normal    /  vertex.

		TVertIndex*		fIndices;

		TVertIndex		fVerticesCount;
		TVertIndex		fIndicesCount;

		/// Transformations ///
		Math::CMatrix	fMatrix;

		/// Attributes ///
		CRGBAColor		fColor;
	};

	typedef std::shared_ptr<IShape>	IShapePtr;
	typedef std::vector<IShapePtr>  TShapeArray;
}