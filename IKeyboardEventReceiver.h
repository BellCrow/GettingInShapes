#pragma once
#include "KeyboardMessage.h"

class IKeyboardEventReceiver
{
public:
	virtual void HandleKeyboardEvent(const KeyboardMessage&) = 0;
};

