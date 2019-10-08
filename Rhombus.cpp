#include "Rhombus.h"
#include "Vertex.h"

Rhombus::Rhombus(Point pos, float width, float height, Color color):
	AbstractShape(pos,width,height,color)
{
	CalculateTriangles();
}

void Rhombus::SetHeight(float a_height)
{
	m_height = a_height;
	CalculateTriangles();
}

void Rhombus::SetWidth(float a_width)
{
	m_width = a_width;
	CalculateTriangles();
}

void Rhombus::SetPosition(Point a_position)
{
	m_position = a_position;
	CalculateTriangles();
}

void Rhombus::CalculateTriangles()
{
	m_triangles.clear();
	float w2 = m_width / 2 ;
	float h2 = m_height / 2;

	Point a(m_position.x - w2, m_position.y);
	Point b(m_position.x, m_position.y + h2);
	Point c(m_position.x + w2, m_position.y);
	Point d(m_position.x, m_position.y - h2);

	m_triangles.push_back(RenderTriangle(b,d,a));
	m_triangles.push_back(RenderTriangle(b,c, d));
}

void Rhombus::SetColor(Color color)
{
	m_color = color;
}
