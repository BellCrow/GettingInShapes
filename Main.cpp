#include "MyWinHeader.h"
#include "Rhombus.h"
#include "Window.h"
#include "Keyboard.h"
#include "KeyboardWindowConnector.h"
#include "WindowToKeyboardPipe.h"

#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include "SceneBoard.h"
#include "Triangle.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE pInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	try
	{
		Window wnd(800, 300, "My first custom window");
		
		SceneBoard sb = SceneBoard(wnd.GetWindowHandle());
		AbstractShape* t = new Triangle(Point(0, 0), 1, 1);
		AbstractShape* t2 = new Triangle(Point(0.3, 0.3), 0.2f, 0.4f);
		sb.AddShape(t);
		sb.AddShape(t2);
		sb.AddShape(new Triangle(Point(-0.3, 0.3), 0.4f, 0.2f));
		MSG msg = { 0 };

		BOOL result = { 0 };
		
		while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0 && msg.message != WM_QUIT)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			sb.Render();
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