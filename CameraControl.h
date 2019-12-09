#pragma once
#include "Keyboard.h"
#include "Camera.h"

class CameraControl
{
public:
	CameraControl(Keyboard* keyboard, Camera* camera);

private:
	void HandleKeyboardEvent(KeyboardMessage keyboardMessage);
	Keyboard* m_keyBoard;
	Camera* m_camera;
};

