#include "Rhombus.h"
#include "Vertex.h"
#include <DirectXMath.h>

Rhombus::Rhombus(Point pos, float width, float height, Color color):
	AbstractShape(pos,width,height,color)
{
	m_triangles = new RenderTriangle[2];
}

Rhombus::~Rhombus(){}

void Rhombus::SetHeight(float a_height)
{
	m_height = a_height;
	m_isDirty = true;
}

void Rhombus::SetWidth(float a_width)
{
	m_width = a_width;
	m_isDirty = true;
}

void Rhombus::SetPosition(Point a_position)
{
	m_position = a_position;
	m_isDirty = true;
}

int Rhombus::GetTriangleCount()
{
	return 2;
}

void Rhombus::CalculateRenderData()
{
	float w2 = m_width / 2;
	float h2 = m_height / 2;

	Point a(- 1, 0);
	Point b(0, 0.5);
	Point c(1, 0);
	Point d(0, - 0.5);

	m_triangles[0] = RenderTriangle(b, d, a);
	m_triangles[1] = RenderTriangle(b, c, d);
		
}

void Rhombus::SetColor(Color color)
{
	m_color = color;
}
