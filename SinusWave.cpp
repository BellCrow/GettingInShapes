#include "SinusWave.h"
#include <exception>
#include <math.h>

SinusWave::SinusWave(float periodLenghtMs, float minValue, float maxValue)
{
	m_periodLenghtMs = periodLenghtMs;
	m_minValue = minValue;
	m_maxValue = maxValue - minValue;
	//start at the min value
	m_currentTimePointMs = 0;
}

void SinusWave::Tick(float elapsedMs)
{
	if (IsExhausted())
	{
		throw std::exception("Cannot tick on an exhausted sine wave generator");
	}
	m_currentTimePointMs += elapsedMs;
	if (IsExhausted())
	{
		m_currentTimePointMs = m_periodLenghtMs;
	}
}

float SinusWave::GetValue()
{
	return sinf(MapAnimationTimeToPi(m_currentTimePointMs)) * m_maxValue + m_minValue;
}

bool SinusWave::IsExhausted()
{
	return m_currentTimePointMs >= m_periodLenghtMs;
}

float SinusWave::MapAnimationTimeToPi(float value)
{
	return (value / m_periodLenghtMs) * 3.1415926f;
}
