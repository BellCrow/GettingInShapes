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
#include "MessageSource.h"
#include "CameraControl.h"

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
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	try
	{
		Window wnd(1024, 768, "My first custom window");
		MessageSource msSource = MessageSource();
		
		Keyboard keyBoard = Keyboard(&msSource);
		Camera camera = Camera();
		
		CameraControl controller = CameraControl(&keyBoard, &camera);
		SceneBoard sb = SceneBoard(wnd.GetWindowHandle());

		AbstractShape* shape = new Rhombus(Point(0,0),200,100, Color(1.0f, Rand(), Rand(), Rand()));
		sb.AddShape(shape);
		
		shape = new Triangle(Point(100,-100),200,100, Color(1.0f, Rand(), Rand(), Rand()));
		sb.AddShape(shape);
		
		
		bool continueRender = true;
		std::thread renderThread = std::thread([&continueRender, &sb, &camera]()
			{
				while (continueRender)
				{
					sb.Tick();
					sb.Render(&camera);
				}
			});
		
		msSource.Subscribe([&continueRender](WindowMessage mes) {
			if (mes.GetMessageType() == WM_QUIT)
			{
				continueRender = false;
			}
			});
		auto messageResult = msSource.MessageLoop();
		renderThread.join();
		return static_cast<int>(messageResult);
	}
	catch (const std::exception & e)
	{
		MessageBox(nullptr, e.what(), "Exception :'(", MB_OK | MB_ICONEXCLAMATION);
	}

	return EXIT_SUCCESS;


}
