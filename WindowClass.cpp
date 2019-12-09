#include "WindowClass.h"
#include "Window.h"
#include <exception>
#include <ostream>
#include "ErrorTranslator.h"
#include <strstream>

HINSTANCE WindowClass::hInst;
WindowClass WindowClass::instance;

const char* WindowClass::GetWindowClassName() noexcept
{
	return wndClassName;
}

HINSTANCE WindowClass::GetInstance() noexcept
{
	return hInst;
}

WindowClass::WindowClass()
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

	if (RegisterClassEx(&wndClass) == 0)
	{
		std::strstream str; 
		str << "Error registering windowclass" << std::endl << ErrorTranslator::TranslateError(GetLastError());
		throw std::exception(str.str());
	}
}

WindowClass::~WindowClass() noexcept
{
	UnregisterClass(wndClassName, hInst);
}