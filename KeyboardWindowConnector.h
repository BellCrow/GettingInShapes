#pragma once
#include "IKeyboardEventReceiver.h"
#include "Window.h"

class KeyboardWindowConnector : public IKeyboardEventReceiver
{
public:
	KeyboardWindowConnector(const Window&);
	// Inherited via IKeyboardEventReceiver
	virtual void HandleKeyboardEvent(const KeyboardMessage&) override;
private:
	const Window& _window;
};

