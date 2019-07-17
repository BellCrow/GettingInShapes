#include "KeyboardWindowConnector.h"

void KeyboardWindowConnector::HandleWindowMessage(const WindowMessage & message)
{
	if (message.GetMessageType() == WM_KEYUP)
	{
		m_keyboard.KeyUp(message.GetWParam());
	}
	else if (message.GetMessageType() == WM_KEYDOWN)
	{
		m_keyboard.KeyDown(message.GetWParam());
	}
}

KeyboardWindowConnector::KeyboardWindowConnector(Keyboard & keyboard, Window & window) :
	m_keyboard(keyboard),
	m_window(window)
{
	m_window.MessageReceived.connect(boost::bind(&KeyboardWindowConnector::HandleWindowMessage,this,_1));
}

KeyboardWindowConnector::~KeyboardWindowConnector()
{
}
