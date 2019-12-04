#include "Camera.h"

Camera::Camera()
{
	m_viewProjection = {};
}

void Camera::SetCenterPosition(Point position)
{
	m_position = position;
}

void Camera::SetCenterPositionX(float position)
{
	m_position = Point(position, m_position.y);
}

void Camera::SetCenterPositionY(float position)
{
	m_position = Point(m_position.x, position);
}

Point Camera::GetCenterPosition() const
{
	return m_position;
}

const DirectX::XMMATRIX Camera::GetViewProjectionMatrix()
{
	auto eyePos = DirectX::XMVectorSet(0, 0, -10, 1);
	auto lookAtPoint = DirectX::XMVectorSet(0, 0, 0, 1);
	auto upVector = DirectX::XMVectorSet(0, 1, 0, 1);

	auto viewMatrix = DirectX::XMMatrixLookAtLH(eyePos, lookAtPoint, upVector);

	auto projectionMatrix = DirectX::XMMatrixOrthographicLH(800, 600, -1, 10000);

	return  viewMatrix * projectionMatrix;
}
