#include "StdAfx.h"

#include "Camera.h"

CCamera::CCamera()
	: fPitch(0.0)
	, fYaw(0.0)
	, fZoom(0.0)
	, fFocus()
{
}

CCamera::~CCamera()
{
}

void CCamera::Set(double pitch, double yaw, double zoom, const CPoint3D& focus)
{
	fPitch = pitch;
	fYaw = yaw;
	fZoom = zoom;
	fFocus = focus;
}

void CCamera::Rotate(const CPoint2D& oldPosition, const CPoint2D& newPosition, double factor)
{
	const CPoint2D movementVec = (newPosition - oldPosition) * factor;
	
	fPitch += movementVec.x;
	fYaw += movementVec.y;		
}

void CCamera::Move(const CPoint2D& oldPos, const CPoint2D& newPos, double xFactor, double yFactor)
{
	const CPoint2D movementVec = (newPos - oldPos);

	fFocus.x -= movementVec.x * xFactor;
	fFocus.y += movementVec.y * yFactor;
}

void CCamera::Zoom(bool zoom, double factor)
{
	///@note Calculate the zoom value.
	double zoomValue = ( zoom ? -1.0 : 1.0 ) * factor;

	///@note Zoom
	fZoom += zoomValue;

	///@note Set some constraints.
	if ( fZoom < 0.0 )
	{
		fZoom = 0.0;
	}
}

CPoint3D CCamera::GetCameraFocus() const
{
	return fFocus;
}

double CCamera::GetPitch() const
{
	return fPitch;
}

double CCamera::GetYaw() const
{
	return fYaw;
}

double CCamera::GetZoom() const
{
	return fZoom;
}