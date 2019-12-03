#include "MyWinHeader.h"
#include "Rhombus.h"
#include "Window.h"
#include "Keyboard.h"
#include "WindowToKeyboardPipe.h"
#include "SceneBoard.h"
#include "Triangle.h"
#include "Rhombus.h"
#include "AlternatingWobbleAnimation.h"
#include "SinusWave.h"
#include "TimeHelper.h"
#include "KeyboardMovementAnimation.h"

#include <random>
#include <sstream>
#include <string>
#include <iostream>
#include <thread>


float Rand(bool negative = true)
{
	auto value = (float)std::rand() / (float)RAND_MAX;
	return value * (negative && std::rand() % 2 == 0 ? 1 : -1);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE pInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	try
	{
		Window wnd(1024, 768, "My first custom window");
		Keyboard keyBoard = Keyboard();
		Camera camera = Camera();
		SceneBoard sb = SceneBoard(wnd.GetWindowHandle());

		auto shape = new Rhombus(Point(0,0), 1,1, Color(1.0f, Rand(), Rand(), Rand()));
		sb.AddShape(shape);
		

		MSG msg = { 0 };

		BOOL result = { 0 };
		bool continueRender = true;
		std::thread renderThread = std::thread([&continueRender, &sb, &camera]()
			{
				while (continueRender)
				{
					sb.Tick();
					sb.Render(&camera);
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
	catch (const WindowException & e)
	{
		MessageBox(nullptr, e.what(), "Window exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception & e)
	{
		MessageBox(nullptr, e.what(), "Unknown exception :'(", MB_OK | MB_ICONEXCLAMATION);
	}

	return EXIT_SUCCESS;
}