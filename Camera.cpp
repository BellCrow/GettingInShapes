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

const DirectX::XMMATRIX Camera::GetViewMatrix()
{
	auto cameraPos = GetCenterPosition();

	auto eyePos = DirectX::XMVectorSet(cameraPos.x, cameraPos.y, -100, 1);
	auto lookAtPoint = DirectX::XMVectorSet(cameraPos.x, cameraPos.y, 0, 1);
	auto upVector = DirectX::XMVectorSet(0, 1, 0, 1);

	auto viewMatrix = DirectX::XMMatrixLookAtLH(eyePos, lookAtPoint, upVector);
	
	return viewMatrix;
}

const DirectX::XMMATRIX Camera::GetProjectionMatrix()
{
	auto projectionMatrix = DirectX::XMMatrixOrthographicLH(1024, 768, 0.1, 10000);
	return projectionMatrix;
}
