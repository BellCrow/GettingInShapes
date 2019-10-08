#pragma once
#include "RenderTriangle.h"
#include "Color.h"

#include <vector>
#include <string>

class AbstractShape
{
public:

	AbstractShape(Point position, float width, float height, Color color) {
		m_position = position;
		m_width = width;
		m_height = height;
		m_color = color;
	}

	virtual void SetHeight(float) = 0;
	virtual void SetWidth(float) = 0;
	virtual void SetPosition(Point) = 0;
	virtual void SetColor(Color) = 0;

	const std::vector<RenderTriangle>& GetTriangles() const { return m_triangles; }
	const float& GetHeight() const { return m_height; }
	const float& GetWidth() const { return m_width; }
	const Point& GetPosition() const { return m_position; }
	const Color& GetColor() const { return m_color; }
	const std::string& GetName() const { return m_name; }

protected:
	Color m_color;
	float m_height;
	float m_width;
	Point m_position;
	std::string m_name;
	std::vector<RenderTriangle> m_triangles;
};

