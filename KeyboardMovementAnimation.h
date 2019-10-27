#pragma once
#include "AbstractAnimation.h"
#include "AbstractShape.h"
#include "IKeyboardEventReceiver.h"

class KeyboardMovementAnimation : public IKeyboardEventReceiver, public AbstractAnimation
{
public:
	KeyboardMovementAnimation(AbstractShape* shape);

	// Inherited via IKeyboardEventReceiver
	virtual void HandleKeyboardEvent(const KeyboardMessage&) override;

	// Inherited via AbstractAnimation
	virtual void Tick() override;
private:
	AbstractShape* m_shape;
	Point* m_newPoint;
};

