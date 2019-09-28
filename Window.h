#pragma once

#include "MyWinHeader.h"
#include "WindowException.h"
#include "WindowMessage.h"
#include "IWindowMessageReceiver.h"
#include <memory>
#include <vector>

class Window
{
private :
	HWND m_windowHandle;
	std::vector<std::shared_ptr<IWindowMessageReceiver>> _subscribers;

	void FireEvent(const WindowMessage&);
public:
	Window(int width, int height, const char* name);
	~Window()noexcept;
	Window(const Window&) = delete;
	Window& operator= (const Window&) = delete;

	static LRESULT CALLBACK InitialMessageHandler(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept;
	static LRESULT CALLBACK HandleMessageAdapter(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept;

	LRESULT HandleMsg(HWND handle, UINT msg, WPARAM w, LPARAM l) noexcept;

	void SetTitle(const char* title) const;
	void Subscribe(std::shared_ptr<IWindowMessageReceiver>);
private:
	class WindowClass
	{
	public:
		static const char* GetWindowClassName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:

		WindowClass();
		~WindowClass() noexcept;

		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;

		static constexpr const char* wndClassName = "MyWindow";
		static WindowClass instance;
		static HINSTANCE hInst;
	};
};


