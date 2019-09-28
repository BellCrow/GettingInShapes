#include "WindowToKeyboardPipe.h"

WindowToKeyboardPipe::WindowToKeyboardPipe(Keyboard& keyboard):_keyboard(keyboard)
{}

void WindowToKeyboardPipe::HandleWindowEvent(const WindowMessage& message)
{
	if (message.GetMessageType() == WM_KEYDOWN)
	{
		_keyboard.KeyDown(message.GetWParam());
	}
	if (message.GetMessageType() == WM_KEYUP)
	{
		_keyboard.KeyUp(message.GetWParam());
	}
}
