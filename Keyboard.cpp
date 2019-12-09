#include "Keyboard.h"
#include <functional>

Keyboard::Keyboard(MessageSource* messageSource)
{
	m_messageSource = messageSource;
	std::function<void(WindowMessage)> function = std::bind(&Keyboard::Handlemessage, this, std::placeholders::_1);
	m_messageSource->Subscribe(function);
	Reset();
}

Keyboard::~Keyboard(){}

void Keyboard::KeyDown(int keyCode)
{
	CheckKeyCode(keyCode);
	m_keys[keyCode] = true;
	KeyboardMessage message = KeyboardMessage(KeyboardEventType::KeyDownEvent, keyCode);
	FireEvent(message);
}

void Keyboard::CheckKeyCode(int keyCode) const
{
	if (MaxKeys <= keyCode)
	{
		throw std::exception("Illegal keycode detected");
	}
}

void Keyboard::FireEvent(const KeyboardMessage& keyboardEvent)
{
	for (auto eventSubscriber : m_keyboardEventSubscriber)
	{
		eventSubscriber->HandleKeyboardEvent(keyboardEvent);
	}
	
	for (auto eventSubscriber : m_keyboardEventLambdas)
	{
		eventSubscriber(keyboardEvent);
	}
}

void Keyboard::Handlemessage(WindowMessage windowMessage)
{
	if (windowMessage.GetMessageType() == WM_KEYDOWN)
	{
		KeyDown(((int)windowMessage.GetWParam()));
	}
	else if (windowMessage.GetMessageType() == WM_KEYUP)
	{
		KeyUp(((int)windowMessage.GetWParam()));
	}
}

void Keyboard::KeyUp(int keyCode)
{
	CheckKeyCode(keyCode);
	m_keys[keyCode] = false;
	KeyboardMessage message = KeyboardMessage(KeyboardEventType::KeyUpEvent, keyCode);
	FireEvent(message);
}

bool Keyboard::IsKeyDown(int keyCode) const
{
	CheckKeyCode(keyCode);
	return m_keys[keyCode];
}

void Keyboard::Reset() noexcept
{
	for (size_t i = 0; i < MaxKeys; i++)
	{
		m_keys[i] = false;
	}
}

void Keyboard::Subscribe(const std::shared_ptr<IKeyboardEventReceiver> eventReceiver)
{
	m_keyboardEventSubscriber.push_back(eventReceiver);
}

void Keyboard::Subscribe(std::function<void(KeyboardMessage)> eventReceiver)
{
	m_keyboardEventLambdas.push_back(eventReceiver);
}
