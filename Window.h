#pragma once

#include "MyWinHeader.h"
#include <exception>

class Window
{
private :
	HWND m_windowHandle;
	
public:
	Window(HWND windowHandle);
	~Window();
	Window(const Window&);
	Window& operator= (const Window&) = delete;

	void Show() noexcept;
	
	void SetWindowHandle(HWND windowHandle);

	static LRESULT CALLBACK HandleMessageAdapter(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept;

	LRESULT HandleMsg(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept;
};

