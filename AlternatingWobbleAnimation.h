#pragma once
#include "MyWinHeader.h"
#include "AbstractAnimation.h"
#include "AbstractShape.h"
#include <chrono>
#include "SinusWave.h"

class AlternatingWobbleAnimation:public AbstractAnimation
{
public:
	AlternatingWobbleAnimation(AbstractShape* shape, float periodTime, float minWidth, float maxWidth, float minHeight, float maxHeight);
	// Inherited via AbstractAnimation
	void Tick() override;

private:
	enum class AnimationState
	{
		ChangingWidth,
		ChangingHeight
	};
private:
	AbstractShape* m_shape;
	float m_periodTime;
	float m_minWidth;
	float m_maxWidth;
	float m_minHeight;
	float m_maxHeight;
	long long m_lastTick;
	SinusWave* m_animationSine;
	AnimationState m_animationState;
};

