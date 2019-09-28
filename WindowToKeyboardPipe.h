#pragma once
#include "IWindowMessageReceiver.h"
#include "Keyboard.h"

class WindowToKeyboardPipe : public IWindowMessageReceiver
{
public:
	WindowToKeyboardPipe(Keyboard&);
	// Inherited via IWindowMessageReceiver
	virtual void HandleWindowEvent(const WindowMessage&) override;
private:
	Keyboard& _keyboard;
};

