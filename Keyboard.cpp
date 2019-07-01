#include "Keyboard.h"
#include "MyException.h"


Keyboard::Keyboard()
{
	for (size_t i = 0; i < MaxKeys; i++)
	{
		m_keys[i] = false;
	}
}


Keyboard::~Keyboard()
{
}

void Keyboard::KeyDown(int keyCode)
{
	if (MaxKeys <= keyCode)
	{
		throw BaseException()
	}
}

void Keyboard::KeyUp(int keyCode)
{
}

bool Keyboard::IsKeyDown(int keyCode) const
{
	return false;
}

void Keyboard::Reset() noexcept
{
}
