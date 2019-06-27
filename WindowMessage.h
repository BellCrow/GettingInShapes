#pragma once
#include "MyWinHeader.h"

class WindowMessage
{
private:
	HWND m_handle;
	UINT m_msg; 
	WPARAM m_w; 
	LPARAM m_l;

public:
	WindowMessage(HWND handle, UINT msg, WPARAM w, LPARAM l);
	~WindowMessage();
};

