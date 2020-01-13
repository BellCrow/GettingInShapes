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

const XMMATRIX* AbstractShape::GetModelmatrix() {
	if (m_isDirty)
	{
		m_modelMatrix = {};
		auto scaleMatrix = DirectX::XMMatrixScaling(m_width, m_height, m_depth);
		auto translationMatrix = DirectX::XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
		auto rotationMatrix = 
			DirectX::XMMatrixRotationRollPitchYaw(
				DirectX::XM_PIDIV4 / 2,
				-DirectX::XM_PIDIV4/2,
				0);
		m_modelMatrix = rotationMatrix * scaleMatrix * translationMatrix;
		m_isDirty = false;
	}
	return &m_modelMatrix;
}
