#include "Rhombus.h"
#include "Vertex.h"
#include <DirectXMath.h>

Rhombus::Rhombus(Point pos, float width, float height, Color color):
	AbstractShape(pos,width,height,color)
{
	m_triangles = new RenderTriangle[2];
}

Rhombus::~Rhombus()
{
	delete m_triangles;
}

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

	Point a(m_position.x - w2, m_position.y);
	Point b(m_position.x, m_position.y + h2);
	Point c(m_position.x + w2, m_position.y);
	Point d(m_position.x, m_position.y - h2);

	m_triangles[0] = RenderTriangle(b, d, a);
	m_triangles[1] = RenderTriangle(b, c, d);

	m_modelMatrix = { };
	m_modelMatrix = DirectX::XMMatrixTranslation(m_position.x, m_position.y, 0);
}

void Rhombus::SetColor(Color color)
{
	m_color = color;
}
