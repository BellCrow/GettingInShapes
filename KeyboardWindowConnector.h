#pragma once

#include "Window.h"
#include "Keyboard.h"

class KeyboardWindowConnector
{
public:
	KeyboardWindowConnector(Keyboard& keyboard,Window& window);
	~KeyboardWindowConnector();
	
        KeyboardWindowConnector( const KeyboardWindowConnector & rhs ) = delete;
	KeyboardWindowConnector( KeyboardWindowConnector && rhs ) = delete;
        KeyboardWindowConnector &operator = ( const KeyboardWindowConnector & rhs ) = delete;

private:
	void HandleWindowMessage(const WindowMessage& message);
	
private:
	Keyboard& m_keyboard; 
	Window& m_window;
};

