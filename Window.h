#pragma once

#include "MyWinHeader.h"
#include "WindowException.h"

class Window
{
private:
	HWND windowHandle;

public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator= (const Window&) = delete;

	static LRESULT CALLBACK InitialMessageHandler(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept;
	static LRESULT CALLBACK HandleMessageAdapter(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept;

	LRESULT HandleMsg(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept;

private:
	class WindowClass
	{
	public:
		static const char* GetWindowClassName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:

		WindowClass() noexcept;
		~WindowClass();

		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;

		static constexpr const char* wndClassName = "MyWindow";
		static WindowClass instance;
		static HINSTANCE hInst;
	};
};

#define WINDOW_EXCEPTION(hr) WindowException(__LINE__,__FILE__,hr)
