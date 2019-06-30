#include "WindowMessage.h"

WindowMessage::WindowMessage(HWND handle, UINT msg, WPARAM w, LPARAM l)
	:
	m_handle(handle),
	m_msg(msg),
	m_w(w),
	m_l(l)
{}

WindowMessage::WindowMessage(const WindowMessage & message)
	:
	m_handle(message.m_handle),
	m_msg(message.m_msg),
	m_w(message.m_w),
	m_l(message.m_l)
{}

WindowMessage::~WindowMessage() {}

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
