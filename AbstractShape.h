#pragma once
#include <vector>
#include <string>
#include <memory>
#include <array>
#include <DirectXMath.h>

#include "RenderTriangle.h"
#include "Color.h"

using namespace DirectX;

class AbstractShape
{
public:

	AbstractShape(Point position, float width, float height, Color color) {
		m_position = position;
		m_width = width;
		m_height = height;
		m_color = color;
		m_triangles = nullptr;
		m_isDirty = true;
		m_modelMatrix = {};
	}

	~AbstractShape() {
		delete[] m_triangles;
	}
	virtual void SetHeight(float) = 0;
	virtual void SetWidth(float) = 0;
	virtual void SetPosition(Point) = 0;
	virtual void SetColor(Color) = 0;
	virtual int GetTriangleCount() = 0;
	

	const float& GetHeight() const { return m_height; }
	const float& GetWidth() const { return m_width; }
	const Point& GetPosition() const { return m_position; }
	const Color& GetColor() const { return m_color; }
	

	const RenderTriangle* GetTriangles() {
		if (m_isDirty)
		{
			CalculateRenderData();
			m_isDirty = false;
		}
		return m_triangles;
	}
	const XMMATRIX* GetModelmatrix() {
		if (m_isDirty)
		{
			CalculateRenderData();

			m_modelMatrix = { };
			auto scaleMatrix = DirectX::XMMatrixScaling(m_width, m_height, 1);

			auto translationMatrix = DirectX::XMMatrixTranslation(m_position.x, m_position.y, 0);
			m_modelMatrix = scaleMatrix * translationMatrix;

			m_isDirty = false;
		}
		return &m_modelMatrix;
	}

protected:
	virtual void CalculateRenderData() = 0;
	bool m_isDirty;
	Color m_color;
	float m_height;
	float m_width;
	Point m_position;
	std::string m_name;
	RenderTriangle* m_triangles;
	XMMATRIX m_modelMatrix;
};

