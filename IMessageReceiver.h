#pragma once
#include "WindowMessage.h"
class IMessageReceiver
{
	IMessageReceiver() = delete;

public:
	virtual void HandleWindowMessage(WindowMessage windowMessage) = 0;
};

