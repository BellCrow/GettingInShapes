#pragma once
#include "MyWinHeader.h"

class WindowClass
{
public:
	static const char* GetWindowClassName() noexcept;
	static HINSTANCE GetInstance() noexcept;

private:

	static WindowClass WindowClassInstance;

	WindowClass();
	~WindowClass() noexcept;

	WindowClass(const WindowClass&) = delete;
	WindowClass& operator=(const WindowClass&) = delete;

	static constexpr const char* wndClassName = "MyWindow";
	static WindowClass instance;
	static HINSTANCE hInst;
};

