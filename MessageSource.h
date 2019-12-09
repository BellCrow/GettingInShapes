#pragma once
#include "IMessageReceiver.h"
#include <vector>
#include <functional>

class MessageSource
{
public:
	int MessageLoop();
	void Subscribe(IMessageReceiver* messageReceiver);
	void Subscribe(std::function<void(WindowMessage)> messageHandler);
private:
	void PublishMessage(WindowMessage windowMessage);
	std::vector<IMessageReceiver*> m_messageReceiver;
	std::vector<std::function<void(WindowMessage)>> m_lambdas;
};

