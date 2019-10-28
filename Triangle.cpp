#include "Triangle.h"

Triangle::Triangle(Point center, float width, float height, Color color)
	:AbstractShape(center, width, height, color)
{
	m_triangles = new RenderTriangle[1];
	CalculateTriangles();
}

void Triangle::SetHeight(float a_height)
{
	m_height = a_height;
	CalculateTriangles();
}

void Triangle::SetWidth(float a_width)
{
	m_width = a_width;
	CalculateTriangles();
}

void Triangle::SetPosition(Point a_center)
{
	m_position = a_center;
	CalculateTriangles();
}

void Triangle::CalculateTriangles()
{
	float w2 = m_width / 2;
	float h2 = m_height / 2;
	Point a = Point(m_position.x - w2, m_position.y - h2);
	Point b = Point(m_position.x, m_position.y + h2);
	Point c = Point(m_position.x + w2, m_position.y - h2);
	m_triangles[0] = RenderTriangle(a, b, c);
}

void Triangle::SetColor(Color color)
{
	m_color = color;
}

int Triangle::GetTriangleCount()
{
	return 1;
}

