#include "MyException.h"
#include <sstream>

BaseException::BaseException(int lineNumber, const char * fileName) noexcept :
	m_line(lineNumber),
	m_file(fileName)
{}

BaseException::~BaseException()
{}

const char * BaseException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl <<
		ToString();
	m_whatBuffer = oss.str();
	return m_whatBuffer.c_str();
}

const char * BaseException::GetType() const noexcept
{
	return "BaseException";
}

int BaseException::GetLine() const noexcept
{
	return m_line;
}

const std::string & BaseException::GetFile() const noexcept
{
	return m_file;
}

std::string BaseException::ToString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << m_file << std::endl
		<< "[Line] " << m_line << std::endl;
	return oss.str();
}