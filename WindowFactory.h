#pragma once
#include "MyWinHeader.h"
#include "Window.h"

class WindowFactory
{
	WindowFactory() noexcept;
	~WindowFactory() noexcept;

	HINSTANCE hInst;
	static LRESULT CALLBACK InitialMessageHandler(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept;

	static constexpr const char* WindowClassName = "ShapesWindowClass";
public:
	
	static WindowFactory Instance;
	Window GenerateWindow(int width, int heigth, const char * name);
};

