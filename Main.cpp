#include "MyWinHeader.h"

#include <string>
#include <sstream>

#include "Window.h"
#include "WindowFactory.h"

LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM w, LPARAM l);

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE pInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	auto wnd = WindowFactory::Instance.GenerateWindow(800, 300, "My first custom window");
	auto wnd2 = WindowFactory::Instance.GenerateWindow(656, 30, "om window");
	wnd.Show();
	wnd2.Show();

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