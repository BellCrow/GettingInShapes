#include "Triangle.h"

Triangle::Triangle(Point center, float width, float height, Color color)
	:AbstractShape(center, width, height,0, color){}

int Triangle::GetTriangleCount()
{
	return 1;
}

void Triangle::CalculateRenderData()
{
	auto rawTrianglePointer = new RenderTriangle[1];
	if (m_triangles == nullptr)
	{
		m_triangles = std::shared_ptr<RenderTriangle[]>(new RenderTriangle[1]);
	}
	
	Point a = Point(- 1, - 0.5, 0);
	Point b = Point(0, 0.5, 0);
	Point c = Point(1, - 0.5, 0);
	rawTrianglePointer[0] = RenderTriangle(a, b, c);
}

int Triangle::GetWireframeLineCount()
{
	return -1;
}

