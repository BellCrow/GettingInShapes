#include "WindowMessage.h"

WindowMessage::WindowMessage(HWND handle, UINT msg, WPARAM w, LPARAM l)
	:
	m_handle(handle),
	m_msg(msg),
	m_w(w),
	m_l(l)
{}

WindowMessage::~WindowMessage(){}
