#include "MessageSource.h"

int MessageSource::MessageLoop()
{
	BOOL result = { 0 };
	MSG msg = { 0 };
	while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0 && msg.message != WM_QUIT)
	{
		if (msg.message == WM_QUIT)
		{
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		PublishMessage(WindowMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam));
	}
	if (msg.message == WM_QUIT)
	{
		PublishMessage(WindowMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam));
	}
	return (int)msg.wParam;
}

void MessageSource::Subscribe(IMessageReceiver* messageReceiver)
{
	m_messageReceiver.push_back(messageReceiver);
}

void MessageSource::Subscribe(std::function<void(WindowMessage)> messageHandler)
{
	m_lambdas.push_back(messageHandler);
}

void MessageSource::PublishMessage(WindowMessage windowMessage)
{
	for (auto receiver : m_messageReceiver)
	{
		receiver->HandleWindowMessage(windowMessage);
	}
		
	for (auto receiver : m_lambdas)
	{
		receiver(windowMessage);
	}
}
