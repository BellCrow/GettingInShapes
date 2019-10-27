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

bool KeyboardMessage::IsWKey() const noexcept
{
	return m_keyCode == 0x57;
}

bool KeyboardMessage::IsAKey() const noexcept
{
	return m_keyCode == 0x41;
}

bool KeyboardMessage::IsSKey() const noexcept
{
	return m_keyCode == 0x53;
}

bool KeyboardMessage::IsDKey() const noexcept
{
	return m_keyCode == 0x44;
}
