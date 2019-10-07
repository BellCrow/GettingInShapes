#pragma once
#include "Rhombus.h"
#include <chrono>

class TriangleWobbler
{
public:
	TriangleWobbler(Rhombus& triangle, float maxHeight, float maxWidth);

	void Tick();

private:
	std::chrono::time_point<std::chrono::system_clock> m_lastUpdate;
	Rhombus& m_triangle;
	float m_maxHeight;
	float m_maxWidth;
};

