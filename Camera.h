#pragma once
#include "Point.h"
#include <DirectXMath.h>

class Camera
{
public:

	Camera();
	void SetCenterPosition(Point point);
	void SetLookAtPosition(Point point);
	Point GetCenterPosition() const;
	
	const DirectX::XMMATRIX GetViewMatrix();
	const DirectX::XMMATRIX GetProjectionMatrix();

private:
	Point m_cameraPosition;
	Point m_cameraLookAtPosition;

	DirectX::XMMATRIX m_viewProjection;
};

