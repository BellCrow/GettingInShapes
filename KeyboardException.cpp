#include "KeyboardException.h"
#include <sstream>


KeyboardException::KeyboardException(int line, const char* file, int keycode):
	BaseException(line,file),
	m_keyCode(keycode)
{}

KeyboardException::~KeyboardException()
{}

const char * KeyboardException::what() const noexcept
{
	std::stringstream oss;
	oss << GetType() << std::endl
		<< "Exception in keyboard class" << std::endl
		<< "Keycode: " << m_keyCode;
	m_whatBuffer = oss.str();
	return m_whatBuffer.c_str();
}

const char * KeyboardException::GetType() const noexcept
{
	return "KeyboardException";
}
