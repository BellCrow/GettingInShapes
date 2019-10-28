#pragma once
#include <memory>
#include "AbstractShape.h"
#include "AbstractAnimation.h"

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
};

