#include "WindowMessage.h"

WindowMessage::WindowMessage(HWND handle, UINT msg, WPARAM w, LPARAM l)
	:
	m_handle(handle),
	m_msg(msg),
	m_w(w),
	m_l(l)
{}

WindowMessage::~WindowMessage(){}

HWND WindowMessage::GetHandle() const noexcept
{
	return m_handle;
}

UINT WindowMessage::GetMessageType() const noexcept
{
	return m_msg;
}

WPARAM WindowMessage::GetWParam() const noexcept
{
	return m_w;
}

LPARAM WindowMessage::GetLParam() const noexcept
{
	return m_l;
}
