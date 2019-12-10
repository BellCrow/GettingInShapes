#include "Window.h"
#include "WindowClass.h"
void Window::FireEvent(const WindowMessage& message)
{
	for (auto subscriber : _subscribers)
	{
		subscriber->HandleWindowEvent(message);
	}
}

Window::Window(int width, int heigth, const char * name)
{
	RECT wr = { 0 };
	wr.left = 100;
	wr.top = 100;

	wr.bottom = wr.top + heigth;
	wr.right = wr.left + width;

	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false) == FALSE)
	{
		throw std::exception("Error in adjust window rect");
	}

	m_windowHandle = CreateWindow(
		WindowClass::GetWindowClassName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);
	if (m_windowHandle == 0)
	{
		throw std::exception("Error in create window");
	}
	ShowWindow(m_windowHandle, SW_SHOWDEFAULT);
}

Window::~Window() noexcept
{
	DestroyWindow(m_windowHandle);
}

LRESULT Window::InitialMessageHandler(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(l);
		auto pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&HandleMessageAdapter));

		return pWnd->HandleMsg(handle, msg, w, l);
	}

	return DefWindowProc(handle, msg, w, l);
}

LRESULT Window::HandleMessageAdapter(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept
{
	Window* windowClassPtr = reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA));
	return windowClassPtr->HandleMsg(handle, msg, w, l);
}

LRESULT Window::HandleMsg(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept
{
	FireEvent(WindowMessage(handle, msg, w, l));
	if (msg == WM_CLOSE)
	{
		PostQuitMessage(0);
		return 0;
	}
		
	return DefWindowProc(handle, msg, w, l);
}

void Window::SetTitle(const char * title) const
{
	SetWindowText(m_windowHandle, title);
}

void Window::Subscribe(std::shared_ptr<IWindowMessageReceiver> subscriber)
{
	_subscribers.push_back(subscriber);
}

//STATIC WINDOW CLASS
