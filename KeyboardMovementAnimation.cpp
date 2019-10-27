#include "KeyboardMovementAnimation.h"

KeyboardMovementAnimation::KeyboardMovementAnimation(AbstractShape* shape)
{
	m_shape = shape;
}

void KeyboardMovementAnimation::HandleKeyboardEvent(const KeyboardMessage& keyboardMessage)
{
	if (m_newPoint != nullptr)
	{
		return;
	}
	float moveDistance = 0.1f;
	if (keyboardMessage.GetEventType() == KeyDownEvent)
	{
		auto shapePos = m_shape->GetPosition();
		if (keyboardMessage.IsWKey())
		{
			m_newPoint = new Point(shapePos.x, shapePos.y + moveDistance);
		}
		
		if (keyboardMessage.IsAKey())
		{
			m_newPoint = new Point(shapePos.x - moveDistance, shapePos.y);
		}
		
		if (keyboardMessage.IsSKey())
		{
			m_newPoint = new Point(shapePos.x, shapePos.y - moveDistance);
		}
		
		if (keyboardMessage.IsDKey())
		{
			m_newPoint = new Point(shapePos.x + moveDistance, shapePos.y);
		}
	}
}

void KeyboardMovementAnimation::Tick()
{
	if(m_newPoint == nullptr)
	{
		return;
	}
	m_shape->SetPosition(*m_newPoint);
	delete m_newPoint;
	m_newPoint = nullptr;
}
