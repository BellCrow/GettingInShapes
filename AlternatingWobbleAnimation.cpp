#include "AlternatingWobbleAnimation.h"
#include "TimeHelper.h"

#include <sstream>


AlternatingWobbleAnimation::AlternatingWobbleAnimation(
	AbstractShape* shape,
	float periodTime,
	float minWidth,
	float maxWidth,
	float minHeight,
	float maxHeight) :

	m_shape(shape),
	m_periodTime(periodTime),
	m_minWidth(minWidth),
	m_maxWidth(maxWidth),
	m_minHeight(minHeight),
	m_maxHeight(maxHeight)
{
	m_lastTick = TimeHelper::GetTimeInMs();
	m_animationState = AnimationState::ChangingWidth;
	m_animationSine = new SinusWave(periodTime, minWidth, maxWidth);
}

void AlternatingWobbleAnimation::Tick()
{
	if (m_animationSine->IsExhausted())
	{
		m_animationState = m_animationState == AnimationState::ChangingWidth ? AnimationState::ChangingHeight : AnimationState::ChangingWidth;
		delete m_animationSine;
		float minValue = m_animationState == AnimationState::ChangingWidth ? m_minWidth : m_minHeight;
		float maxValue = m_animationState == AnimationState::ChangingWidth ? m_maxWidth : m_maxHeight;
		m_animationSine = new SinusWave(m_periodTime, minValue, maxValue);
		m_lastTick = TimeHelper::GetTimeInMs();
	}
	auto time = TimeHelper::GetTimeInMs();
	auto msSinceLastTick =  time - m_lastTick;
	m_animationSine->Tick(msSinceLastTick);
	m_lastTick = time;
	if (m_animationState == AnimationState::ChangingWidth)
	{
		auto value = m_animationSine->GetValue();
		m_shape->SetHeight(value);
	}
	else
	{
		auto value = m_animationSine->GetValue();
		m_shape->SetWidth(value);
	}
}


