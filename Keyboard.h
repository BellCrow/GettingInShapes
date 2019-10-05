#pragma once
#include "KeyboardMessage.h"
#include "IKeyboardEventReceiver.h"


#include <vector>
#include <memory>

class Keyboard
{
public:
	static const int MaxKeys = 255;

	std::vector<std::shared_ptr<IKeyboardEventReceiver>> _keyboardEventSubscriber;

	Keyboard();
	~Keyboard();

	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
	bool IsKeyDown(int keyCode) const;
	void Reset() noexcept;
	void Subscribe(const std::shared_ptr<IKeyboardEventReceiver>);
private:
	bool m_keys[MaxKeys];
	void CheckKeyCode(int keyCode) const;
	void FireEvent(const KeyboardMessage&);
};

