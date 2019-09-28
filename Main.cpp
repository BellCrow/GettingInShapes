#include "MyWinHeader.h"

#include <string>
#include <sstream>

#include "Window.h"
#include "Keyboard.h"
#include "KeyboardWindowConnector.h"
#include "WindowToKeyboardPipe.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE pInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	try
	{
		Window wnd(800, 300, "My first custom window");
		Keyboard keyboard;
		auto connector = std::make_shared<KeyboardWindowConnector>(wnd);
		keyboard.Subscribe(connector);

		auto connector2 = std::make_shared<WindowToKeyboardPipe>(keyboard);
		wnd.Subscribe(connector2);
		
		MSG msg = { 0 };

		BOOL result = { 0 };

		while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0 && msg.message != WM_QUIT) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}
	}
	catch (const WindowException& e)
	{
		MessageBox(nullptr, e.what(), "Window exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Unknown exception :'(", MB_OK | MB_ICONEXCLAMATION);
	}
	
	return EXIT_SUCCESS;
}