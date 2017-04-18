#pragma once

using namespace Math;

class CCamera
{
	SINGELTON(CCamera);

public:
	~CCamera();

	void	Set(double pitch, double yaw, double zoom, const CPoint3D& focus);

	/// Camera actions ///
	void	Rotate(const CPoint2D& oldPos, const CPoint2D& newPos, double factor = 1.0);
	void	Move(const CPoint2D& oldPos, const CPoint2D& newPos, double xFac = 1.0, double yFac = 1.0);
	void	Zoom(bool zoom, double factor = 1.0);

	/// Camera data ///
	double		GetPitch() const;
	double		GetYaw() const;
	double		GetZoom() const;
	CPoint3D	GetCameraFocus() const;

private:
	double		fPitch;
	double		fYaw;
	double		fZoom;

	CPoint3D	fFocus;
};