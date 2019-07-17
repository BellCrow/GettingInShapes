#pragma once
#include "MyException.h"
class KeyboardException : public BaseException
{
	int m_keyCode;
	mutable std::string m_whatBuffer;
public:
	KeyboardException(int line, const char* file, int keyCode);
	~KeyboardException();

	const char* what() const noexcept override;
	const char * GetType() const noexcept;
};

