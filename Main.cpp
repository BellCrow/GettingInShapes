#include "MyWinHeader.h"
#include "Rhombus.h"
#include "Window.h"
#include "Keyboard.h"
#include "KeyboardWindowConnector.h"
#include "WindowToKeyboardPipe.h"
#include "SceneBoard.h"
#include "Triangle.h"
#include "Rhombus.h"
#include "AlternatingWobbleAnimation.h"
#include "SinusWave.h"
#include "TimeHelper.h"


#include <sstream>
#include <string>
#include <iostream>
#include <thread>


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
				
		auto rhombus = new Rhombus(Point(0.0f, 0.5f), .3f, 2.0f, Color(1.0, 0.2f, .7f, .9f));
		sb.AddShape(rhombus);

		auto animation = new AlternatingWobbleAnimation(rhombus, 5000, 0.1, 1.0f, 0.1, 1.0f);
		sb.AddAnimation(animation);


		MSG msg = { 0 };

		BOOL result = { 0 };
		bool continueRender = true;
		std::thread renderThread = std::thread([&continueRender, &sb]()
			{
				while (continueRender)
				{
					sb.Tick();
					sb.Render();
				}
			});

		while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0 && msg.message != WM_QUIT)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			continueRender = false;
			renderThread.join();
			return static_cast<int>(msg.wParam);
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