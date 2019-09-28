#pragma once
#include "WindowMessage.h"

class IWindowMessageReceiver
{
public:
	virtual void HandleWindowEvent(const WindowMessage&) = 0;
};