#include "Cuboid.h"

int Cuboid::GetTriangleCount()
{
	return 12;
}

int Cuboid::GetWireframeLineCount()
{
	return 12;
}
void Cuboid::CalculateRenderData()
{
	CreateTriangles();

	CreateWireFrameLines();
}

void Cuboid::CreateWireFrameLines()
{
	m_wireframeLines = std::shared_ptr<RenderLine[]>(new RenderLine[12]);

	float unitSizeHalf = 0.5f;
	float s = unitSizeHalf;
	auto a = Point(-s, s, -s);
	auto b = Point(s, s, -s);
	auto c = Point(-s, -s, -s);
	auto d = Point(s, -s, -s);

	auto e = Point(-s, s, s);
	auto f = Point(s, s, s);
	auto g = Point(-s, -s, s);
	auto h = Point(s, -s, s);

	int i = 0;
	//front
	m_wireframeLines[i++] = RenderLine(a, b);
	m_wireframeLines[i++] = RenderLine(b, d);
	m_wireframeLines[i++] = RenderLine(d, c);
	m_wireframeLines[i++] = RenderLine(c, a);

	////sides
	m_wireframeLines[i++] = RenderLine(a,e);
	m_wireframeLines[i++] = RenderLine(b,f);
	m_wireframeLines[i++] = RenderLine(d,h);
	m_wireframeLines[i++] = RenderLine(c,g);

	////back
	m_wireframeLines[i++] = RenderLine(e, f);
	m_wireframeLines[i++] = RenderLine(f, h);
	m_wireframeLines[i++] = RenderLine(h, g);
	m_wireframeLines[i++] = RenderLine(g,e);
}

void Cuboid::CreateTriangles()
{
	float unitSizeHalf = 0.5f;
	float s = unitSizeHalf;
	m_triangles = std::shared_ptr<RenderTriangle[]>(new RenderTriangle[12]);

	//create the points for the unit cube, that then gets scaled by the matrices
	auto a = Point(-s, s, -s);
	auto b = Point(s, s, -s);
	auto c = Point(-s, -s, -s);
	auto d = Point(s, -s, -s);

	auto e = Point(s, -s, s);
	auto f = Point(s, s, s);
	auto g = Point(-s, s, s);
	auto h = Point(-s, -s, s);

	int iter = 0;
	m_triangles[iter++] = RenderTriangle(a, b, c);
	m_triangles[iter++] = RenderTriangle(b, d, c);
	m_triangles[iter++] = RenderTriangle(b, f, d);
	m_triangles[iter++] = RenderTriangle(f, g, d);
	m_triangles[iter++] = RenderTriangle(f, e, h);
	m_triangles[iter++] = RenderTriangle(f, h, g);
	m_triangles[iter++] = RenderTriangle(e, a, h);
	m_triangles[iter++] = RenderTriangle(a, c, h);
	m_triangles[iter++] = RenderTriangle(e, a, f);
	m_triangles[iter++] = RenderTriangle(f, a, b);
	m_triangles[iter++] = RenderTriangle(c, d, h);
	m_triangles[iter++] = RenderTriangle(h, d, g);
}


