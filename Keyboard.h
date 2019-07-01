#pragma once
#include <bitset>

class Keyboard
{
	static const int MaxKeys = 255;
	bool m_keys[MaxKeys];
public:
	Keyboard();
	~Keyboard();

	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
	bool IsKeyDown(int keyCode) const;
	void Reset() noexcept;
};

