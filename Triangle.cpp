#include "Triangle.h"

Triangle::Triangle(Point center, float width, float height, Color color)
	:AbstractShape(center, width, height, color)
{

}

void Triangle::SetHeight(float a_height)
{
	m_height = a_height;
	m_isDirty = true;
}

void Triangle::SetWidth(float a_width)
{
	m_width = a_width;
	m_isDirty = true;
}

void Triangle::SetPosition(Point a_center)
{
	m_position = a_center;
	m_isDirty = true;
}

void Triangle::SetColor(Color color)
{
	m_color = color;
}

int Triangle::GetTriangleCount()
{
	return 1;
}

void Triangle::CalculateRenderData()
{
	if (m_triangles == nullptr)
	{
		m_triangles = new RenderTriangle[1];
	}
	
	Point a = Point(- 1, - 0.5);
	Point b = Point(0, 0.5);
	Point c = Point(1, - 0.5);
	m_triangles[0] = RenderTriangle(a, b, c);
}

