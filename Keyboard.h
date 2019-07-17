#pragma once
#include <boost/signals2.hpp>
#include "KeyboardMessage.h"
class Keyboard
{
public:
	static const int MaxKeys = 255;
	boost::signals2::signal<void(KeyboardMessage)> KeyBoardEvent;

	Keyboard();
	~Keyboard();

	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
	bool IsKeyDown(int keyCode) const;
	void Reset() noexcept;
private:
	bool m_keys[MaxKeys];
	void CheckKeyCode(int keyCode) const;
};

