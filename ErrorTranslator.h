#pragma once
#include <string>
#include "MyWinHeader.h"

class ErrorTranslator
{
public:
	static std::string TranslateError(HRESULT error)
	{
		char* messageBuffer = nullptr;

		auto result = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&messageBuffer), 0, nullptr);

		if (result == 0)
		{
			return "Unknown error occured";
		}

		std::string errorString = messageBuffer;

		LocalFree(messageBuffer);

		return errorString;
	};
};

