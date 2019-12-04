#include "WobbleAnimation.h"
#include <chrono>


WobbleAnimation::WobbleAnimation(AbstractShape* shape, float periodTime, float minWidth, float maxWidth, float minHeight, float maxHeight):
m_shape (shape),
m_periodTime (periodTime),
m_minWidth (minWidth),
m_maxWidth (maxWidth),
m_minHeight (minHeight),
m_maxHeight (maxHeight)
{}

void WobbleAnimation::Tick()
{
	auto timeValue = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	auto sinTime = (float)fabs(sin(timeValue * 0.001));
	m_shape->SetHeight(sinTime * m_maxHeight);
	m_shape->SetWidth(sinTime * m_maxWidth);
}
