#include "Keyboard.h"
#include "KeyboardException.h"


Keyboard::Keyboard()
{
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
		throw KeyboardException(__LINE__, __FILE__, keyCode);
	}
}

void Keyboard::FireEvent(const KeyboardMessage& keyboardEvent)
{
	for (auto eventSubscriber : _keyboardEventSubscriber)
	{
		eventSubscriber->HandleKeyboardEvent(keyboardEvent);
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
	_keyboardEventSubscriber.push_back(eventReceiver);
}
