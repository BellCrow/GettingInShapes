#pragma once
#include "Triangle.h"
#include <chrono>

class TriangleWobbler
{
public:
	TriangleWobbler(Triangle& triangle, float maxHeight, float maxWidth);

	void Tick();

private:
	std::chrono::time_point<std::chrono::system_clock> m_lastUpdate;
	Triangle& m_triangle;
	float m_maxHeight;
	float m_maxWidth;
};

