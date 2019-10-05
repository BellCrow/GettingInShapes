#include "KeyboardWindowConnector.h"

KeyboardWindowConnector::KeyboardWindowConnector(const Window& window):_window(window){}

void KeyboardWindowConnector::HandleKeyboardEvent(const KeyboardMessage& message)
{
	if (message.GetEventType() == KeyDownEvent)
	{
		_window.SetTitle("Pressed");
	}
	else
	{
		_window.SetTitle("Not pressed");
	}
}
