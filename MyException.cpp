#include "MyException.h"
#include <sstream>

BaseException::BaseException(int lineNumber, const char * fileName) noexcept:
	line(lineNumber),
	file(fileName)
{}

BaseException::~BaseException()
{
}

const char * BaseException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl <<
		ToString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char * BaseException::GetType() const noexcept
{
	return "BaseException";
}

int BaseException::GetLine() const noexcept
{
	return line;
}

const std::string & BaseException::GetFile() const noexcept
{
	return file;
}

std::string BaseException::ToString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line << std::endl;
	return oss.str();
}
