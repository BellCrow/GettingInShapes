#pragma once
#include "Keyboard.h"
#include "Camera.h"
#include "SmartPointer.h"

class CameraControl
{
public:
	CameraControl(sp<Keyboard> keyboard, sp<Camera> camera);

private:
	void HandleKeyboardEvent(KeyboardMessage keyboardMessage);
	sp<Keyboard> m_keyBoard;
	sp<Camera> m_camera;
};

