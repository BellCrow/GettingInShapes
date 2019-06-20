#include "Window.h"

Window::Window(int width, int heigth, const char * name) {

	RECT wr = { 0 };
	wr.left = 100;
	wr.top = 100;

	wr.bottom = wr.top + heigth;
	wr.right = wr.left + width;

	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false);

	windowHandle = CreateWindow(
		WindowClass::GetWindowClassName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);
	ShowWindow(windowHandle, SW_SHOWDEFAULT);
}

Window::~Window() {
	DestroyWindow(windowHandle);
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



//STATIC WINDOW CLASS

HINSTANCE Window::WindowClass::hInst;
Window::WindowClass Window::WindowClass::instance;

const char * Window::WindowClass::GetWindowClassName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return hInst;
}

Window::WindowClass::WindowClass()noexcept
{
	hInst = GetModuleHandle(nullptr);


	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	wndClass.style = CS_OWNDC;
	wndClass.hInstance = GetInstance();
	wndClass.lpfnWndProc = Window::InitialMessageHandler;
	wndClass.lpszClassName = GetWindowClassName();

	RegisterClassEx(&wndClass);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, hInst);
}
