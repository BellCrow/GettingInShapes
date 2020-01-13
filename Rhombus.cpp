#include "Rhombus.h"
#include "Vertex.h"
#include <DirectXMath.h>

Rhombus::Rhombus(Point pos, float width, float height, float depth, Color color):
	AbstractShape(pos,width,height,depth,color)
{}

Rhombus::~Rhombus(){}


int Rhombus::GetTriangleCount()
{
	return 2;
}

void Rhombus::CalculateRenderData()
{
	auto rawTrianglePointer = new RenderTriangle[2];
	m_triangles = std::shared_ptr<RenderTriangle[]>(rawTrianglePointer);
	float w2 = m_width / 2;
	float h2 = m_height / 2;

	Point a(- 1, 0, 0);
	Point b(0, 0.5, 0);
	Point c(1, 0, 0);
	Point d(0, - 0.5, 0);

	rawTrianglePointer[0] = RenderTriangle(b, d, a);
	rawTrianglePointer[1] = RenderTriangle(b, c, d);
}

int Rhombus::GetWireframeLineCount()
{
	return -1;
}

