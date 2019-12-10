#include "CameraControl.h"

CameraControl::CameraControl(Keyboard* keyboard, Camera* camera)
{
	m_keyBoard = keyboard;
	m_camera = camera;
	m_keyBoard->Subscribe(std::bind(&CameraControl::HandleKeyboardEvent, this, std::placeholders::_1));	
}

void CameraControl::HandleKeyboardEvent(KeyboardMessage keyboardMessage)
{
	float moveAmount = 10.0f;
	if (keyboardMessage.GetEventType() == KeyboardEventType::KeyDownEvent)
	{
		Point currentCameraPos = m_camera->GetCenterPosition();
		Point newCameraPos = {};
		if (keyboardMessage.IsWKey())
		{
			newCameraPos = Point(currentCameraPos.x, currentCameraPos.y + moveAmount);
		}
		else if (keyboardMessage.IsAKey())
		{
			newCameraPos = Point(currentCameraPos.x - moveAmount, currentCameraPos.y);
		}
		else if (keyboardMessage.IsSKey())
		{
			newCameraPos = Point(currentCameraPos.x , currentCameraPos.y - moveAmount);
		}
		else if (keyboardMessage.IsDKey())
		{
			newCameraPos = Point(currentCameraPos.x + moveAmount, currentCameraPos.y);
		}
		m_camera->SetCenterPosition(newCameraPos);
	}
}
