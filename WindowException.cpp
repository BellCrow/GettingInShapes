#include "WindowException.h"
#include <sstream>


WindowException::WindowException(int line, const char * file, HRESULT hr) noexcept:
	BaseException(line,file),
	m_hr(hr)
{}

WindowException::~WindowException()
{
}

const char * WindowException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "Description:" << TranslateError(m_hr) << std::endl
		<< ToString() << std::endl;
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char * WindowException::GetType() const noexcept
{
	return "WindowException";
}

std::string WindowException::GetErrorString() const noexcept
{
	return TranslateError(m_hr);
}

std::string WindowException::TranslateError(HRESULT error) noexcept
{
	char* messageBuffer = nullptr;

	auto result = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&messageBuffer),0, nullptr);
	if (result == 0)
	{
		return "Unknown error occured";
	}

	std::string errorString = messageBuffer;
	LocalFree(messageBuffer);

	return errorString;
}
