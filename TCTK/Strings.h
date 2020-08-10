#pragma once

#ifndef TCTK_STRING
#define TCTK_STRING

#include "pch.h"
#include "DLLDefinitions.h"

namespace Strings
{
	TCTK_DLL template<typename... Rest> std::string string_sprintf(const char* format, Rest... args)
	{
		int length = std::snprintf(nullptr, 0, format, args...);
		assert(length >= 0);
		char* buf = new char[length + 1];
		std::snprintf(buf, length + 1, format, args...);
		std::string str(buf);
		delete[] buf;
		return str;
	}

	TCTK_DLL std::string* getTimeFormatted()
	{
		time_t currentTime = std::time(NULL);
		int hour = std::localtime(&currentTime)->tm_hour;
		int minute = std::localtime(&currentTime)->tm_min;
		int second = std::localtime(&currentTime)->tm_sec;
		std::string strHour = std::to_string(hour);
		if (hour < 10)
		{
			strHour.insert(0, "0");
		}

		std::string strMinute = std::to_string(minute);
		if (minute < 10)
		{
			strMinute.insert(0, "0");
		}

		std::string strSecond = std::to_string(second);
		if (second < 10)
		{
			strSecond.insert(0, "0");
		}
		std::string ret[] = { strHour, strMinute, strSecond };
		return ret;
	}
}
#endif