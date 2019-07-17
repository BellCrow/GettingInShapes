#pragma once
#include "KeyboardEventType.h"

class KeyboardMessage
{
	KeyboardEventType m_eventType;
	int m_keyCode;

public:
	KeyboardMessage(KeyboardEventType eventType,int keyCode);
	~KeyboardMessage();
	KeyboardEventType GetEventType() const;
	int GetKeyCode() const;
};

