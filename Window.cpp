#include "Window.h"


Window::Window(HWND windowHandle) 
{
	m_windowHandle = windowHandle;
}

Window::~Window() 
{
	DestroyWindow(m_windowHandle);
}

Window::Window(const Window & other)
{
	m_windowHandle = other.m_windowHandle;
}

void Window::Show() noexcept
{
	ShowWindow(m_windowHandle, SW_SHOWDEFAULT);
}

void Window::SetWindowHandle(HWND windowHandle)
{
	if (m_windowHandle != nullptr)
	{
		throw std::exception("Cannot set the window handle of a window object twice");
	}
	m_windowHandle = windowHandle;
}

LRESULT Window::HandleMessageAdapter(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept
{
	Window* windowClassPtr = reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA));
	return windowClassPtr->HandleMsg(handle, msg, w, l);
}

LRESULT Window::HandleMsg(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;

	case WM_KEYDOWN:
		if (w == 'F')
		{
			SetWindowText(handle, "LOL");
		}
		break;
	case WM_KEYUP:
		if (w == 'F')
		{
			SetWindowText(handle, "LOL or is it?");
		}
		break;
	
	}
	return DefWindowProc(handle, msg, w, l);
}