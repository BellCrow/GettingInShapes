#include "MyWinHeader.h"

#include <string>
#include <sstream>

#include "Window.h"

LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM w, LPARAM l);

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE pInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Window wnd(800, 300, "My first custom window");
	Window wnd2(800, 300, "My second custom window");

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