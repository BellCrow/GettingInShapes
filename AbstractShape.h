#pragma once
#include "RenderTriangle.h"

#include <vector>
#include <string>

class AbstractShape
{
public:
	virtual void SetHeight(float) = 0;
	virtual void SetWidth(float) = 0;
	virtual void SetPosition(Point) = 0;

	const std::vector<RenderTriangle>& GetTriangles() const { return m_triangles; }
	const float& GetHeight() const { return m_height; }
	const float& GetWidth() const { return m_width; }
	const Point& GetPosition() const { return m_position; }
	const std::string& GetName() const { return m_name; }
protected:
	float m_height;
	float m_width;
	Point m_position;
	std::string m_name;
	std::vector<RenderTriangle> m_triangles;
};

