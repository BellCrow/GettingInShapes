#pragma once
#include "Window.h"
#include "Keyboard.h"

class KeyboardWindowConnector
{
	Keyboard& m_keyboard; 
	Window& m_window;

	void HandleWindowMessage(const WindowMessage& message);

public:
	KeyboardWindowConnector(Keyboard& keyboard,Window& window);
	~KeyboardWindowConnector();
};

