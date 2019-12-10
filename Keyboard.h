#pragma once
#include "KeyboardMessage.h"
#include "IKeyboardEventReceiver.h"
#include "MessageSource.h"

#include <vector>
#include <memory>

class Keyboard
{
public:
	static const int MaxKeys = 255;

	

	Keyboard(MessageSource* messageSource);
	~Keyboard();

	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
	bool IsKeyDown(int keyCode) const;
	void Reset() noexcept;
	void Subscribe(const std::shared_ptr<IKeyboardEventReceiver>);
	void Subscribe(std::function<void(KeyboardMessage)>);

private:

	std::vector<std::shared_ptr<IKeyboardEventReceiver>> m_keyboardEventSubscriber;
	std::vector<std::function<void(KeyboardMessage)>> m_keyboardEventLambdas;
	MessageSource* m_messageSource;
	bool m_keys[MaxKeys];
	void CheckKeyCode(int keyCode) const;
	void FireEvent(const KeyboardMessage&);
	void Handlemessage(WindowMessage windowMessage);
};

