#pragma once
#include "Point.h"
struct RenderLine
{
public:
	RenderLine()
	{
		m_start = Point(0.0f,0.0f,0.0f);
		m_end = Point(0.0f,0.0f,0.0f);
	}
	RenderLine(Point start, Point end )
	{
		m_start = start;
		m_end = end;
	}
	const Point& GetStart() const
	{
		return m_start;
	}
	
	const Point& GetEnd() const
	{
		return m_end;
	}
private:
	Point m_start;
	Point m_end;
};