#include "KeyboardMessage.h"

KeyboardMessage::KeyboardMessage(KeyboardEventType eventType, int keyCode):
	m_eventType(eventType),
	m_keyCode(keyCode)
{}

KeyboardMessage::~KeyboardMessage()
{}

KeyboardEventType KeyboardMessage::GetEventType() const
{
	return m_eventType;
}

int KeyboardMessage::GetKeyCode() const
{
	return m_keyCode;
}
