#include "TriangleWobbler.h"
#include <math.h>
#include <time.h>
#include <sstream>

TriangleWobbler::TriangleWobbler(Rhombus& triangle, float maxHeight, float maxWidth):
	m_triangle( triangle),
	m_maxHeight( maxHeight),
	m_maxWidth( maxWidth)
{}

void TriangleWobbler::Tick()
{
	auto timeValue = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	auto sinTime = fabs(sin(timeValue * 0.001));
	m_triangle.SetHeight(sinTime * m_maxHeight);
	m_triangle.SetWidth(sinTime * m_maxWidth);
	m_triangle.RenderTriangleFrame();
}
