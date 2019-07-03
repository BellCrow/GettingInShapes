#include "Keyboard.h"
#include "KeyboardException.h"


Keyboard::Keyboard()
{
	Reset();
}


Keyboard::~Keyboard()
{
}

void Keyboard::KeyDown(int keyCode)
{
	CheckKeyCode(keyCode);
	m_keys[keyCode] = true;
	KeyBoardEvent(KeyboardMessage(KeyboardEventType::KeyDownEvent, keyCode));
}

void Keyboard::CheckKeyCode(int keyCode) const
{
	if (MaxKeys <= keyCode)
	{
		throw KeyboardException(__LINE__, __FILE__, keyCode);
	}
}

void Keyboard::KeyUp(int keyCode)
{
	CheckKeyCode(keyCode);
	m_keys[keyCode] = false;
	KeyBoardEvent(KeyboardMessage(KeyboardEventType::KeyUpEvent, keyCode));
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
