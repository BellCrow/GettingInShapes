#include "MyWin.h"


#include <string>
#include <sstream>

LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM w, LPARAM l);

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE pInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	const auto pClassName = "GettingInShapes";

	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	wndClass.style = CS_OWNDC;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = pClassName;

	RegisterClassEx(&wndClass);

	auto windowHandle = CreateWindowEx(
		0,
		pClassName,
		"GettingInShapeWindow",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(windowHandle, SW_SHOW);

	MSG msg = { 0 };

	BOOL result = { 0 };
	while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0 && msg.message != WM_QUIT) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msg.message == WM_QUIT)
	{
		return msg.wParam;
	}

	return EXIT_SUCCESS;
}

LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM w, LPARAM l)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0x1337);
		break;
	case WM_KEYDOWN:
		if (w == 'F')
		{
			SetWindowText(wnd, "LOL");
		}
		break;
	case WM_KEYUP:
		if (w == 'F')
		{
			SetWindowText(wnd, "LOL or is it?");
		}
		break;
	case WM_CHAR:

		break;

	case WM_MOUSEMOVE:
	{
		POINTS pt = MAKEPOINTS(l);
		std::ostringstream s;
		s << "(" << pt.x << "/" << pt.y << ")";

		SetWindowText(wnd, s.str().c_str());

	}
	break;
	}
	return DefWindowProc(wnd, msg, w, l);
}