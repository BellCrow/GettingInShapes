#pragma once
#include "Point.h"
#include <DirectXMath.h>

class Camera
{
public:

	Camera();
	void SetCenterPosition(Point point);
	void SetCenterPositionX(float position);
	void SetCenterPositionY(float position);
	
	Point GetCenterPosition() const;
	
	const DirectX::XMMATRIX GetViewMatrix();
	const DirectX::XMMATRIX GetProjectionMatrix();

private:
	Point m_position;
	DirectX::XMMATRIX m_viewProjection;
};

