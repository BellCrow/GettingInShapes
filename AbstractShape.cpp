#include "AbstractShape.h"

void AbstractShape::SetHeight(float a_height)
{
	m_height = a_height;
	m_isDirty = true;
}

void AbstractShape::SetWidth(float a_width)
{
	m_width = a_width;
	m_isDirty = true;
}

void AbstractShape::SetPosition(Point a_position)
{
	m_position = a_position;
	m_isDirty = true;
}

void AbstractShape::SetDepth(float depth)
{
	m_depth = depth;
	m_isDirty = true;
}

void AbstractShape::SetColor(Color color)
{
	m_color = color;
	CalculateRenderData();
}

void AbstractShape::SetXRotatation(float rotation)
{
	m_roll = rotation;
}

void AbstractShape::SetYRotatation(float rotation)
{
	m_pitch = rotation;
}

void AbstractShape::SetZRotatation(float rotation)
{
	m_yaw = rotation;
}

float AbstractShape::GetXRotatation()
{
	return m_roll;
}

float AbstractShape::GetYRotatation()
{
	return m_pitch;
}

float AbstractShape::GetZRotatation()
{
	return m_yaw;
}

const XMMATRIX* AbstractShape::GetModelmatrix() {
	if (m_isDirty)
	{
		m_modelMatrix = {};
		auto scaleMatrix = DirectX::XMMatrixScaling(m_width, m_height, m_depth);
		auto translationMatrix = DirectX::XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
		auto rotationMatrix = 
			DirectX::XMMatrixRotationRollPitchYaw(
				m_roll,
				m_pitch,
				m_yaw);
		m_modelMatrix = rotationMatrix * scaleMatrix * translationMatrix;
		m_isDirty = true;
	}
	return &m_modelMatrix;
}
