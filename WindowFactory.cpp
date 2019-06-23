#include "MyWinHeader.h"
#include "WindowFactory.h"

WindowFactory WindowFactory::Instance;

WindowFactory::WindowFactory() noexcept
{
	hInst = GetModuleHandle(nullptr);

	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	wndClass.style = CS_OWNDC;
	wndClass.hInstance = hInst;
	wndClass.lpfnWndProc = InitialMessageHandler;
	wndClass.lpszClassName = WindowClassName;

	RegisterClassEx(&wndClass);
}

WindowFactory::~WindowFactory()
{
	UnregisterClass(WindowClassName, hInst);
}

LRESULT WindowFactory::InitialMessageHandler(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept
{
	return DefWindowProc(handle, msg, w, l);
}

Window WindowFactory::GenerateWindow(int width, int heigth, const char * name)
{
	RECT wr = { 0 };
	wr.left = 100;
	wr.top = 100;

	wr.bottom = wr.top + heigth;
	wr.right = wr.left + width;

	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false);
	
	HWND windowHandle = CreateWindow(
		WindowClassName, name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, hInst, nullptr);

	SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowHandle));
	SetWindowLongPtr(windowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Window::HandleMessageAdapter));

	return Window(windowHandle);
}
