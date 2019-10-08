#pragma once
#include <chrono>

class TimeHelper
{
public:
	static long long GetTimeInMs()
	{
		auto value = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		auto ret = value.count();
		return ret;
	}
};

