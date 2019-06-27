#pragma once
#include "MyWinHeader.h"
#include "MyException.h"

class WindowException: public BaseException
{
public:
	WindowException(int line, const char* file, HRESULT hr) noexcept;
	~WindowException();
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept override;
	std::string GetErrorString() const noexcept;

private:
	static std::string TranslateError(HRESULT error) noexcept;
	HRESULT m_hr;
};

#define WINDOW_EXCEPTION(hr) WindowException(__LINE__, __FILE__, hr)

