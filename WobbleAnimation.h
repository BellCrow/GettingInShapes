#pragma once
#include <memory>
#include "AbstractShape.h"
#include "AbstractAnimation.h"

enum AnimationState
{
	ChangingWidth = 0,
	ChangingHeight = 1
};

class WobbleAnimation:public AbstractAnimation
{
public:
	WobbleAnimation(AbstractShape* shape, float periodTime, float minWidth, float maxWidth, float minHeight, float maxHeight);
	void Tick();

private:
	AbstractShape* m_shape;
	float m_periodTime;
	float m_minWidth;
	float m_maxWidth;
	float m_minHeight;
	float m_maxHeight;
	AnimationState m_animationState;
};

