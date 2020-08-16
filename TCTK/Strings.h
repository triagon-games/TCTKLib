#pragma once

#ifndef TCTK_STRING
#define TCTK_STRING

#include "pch.h"
#include "DLLDefinitions.h"
#include <assert.h>
#define _CRT_SECURE_NO_WARNINGS

namespace Strings
{
	struct TimeString
	{
	public:
		std::string Hours;
		std::string Minutes;
		std::string Seconds;
		TimeString(std::string h, std::string m, std::string s)
		{
			Hours = h;
			Minutes = m;
			Seconds = s;
		}
	};
	TCTK_DLL template<typename... Rest> std::string sprintf(const char* format, Rest... args)
	{
		int length = std::snprintf(nullptr, 0, format, args...);
		assert(length >= 0);
		char* buf = new char[length + 1];
		std::snprintf(buf, length + 1, format, args...);
		std::string str(buf);
		delete[] buf;
		return str;
	}

	TCTK_DLL std::string replace(const char* _string, const char* _token, const char* _replacement)
	{
		std::string ret(_string);
		std::string token(_token);
		std::string replacement(_replacement);
		if (token._Equal(replacement.c_str())) return ret;
		int offset = 0;
		int start_pos = (int)ret.find(token.c_str(), offset);
		while (start_pos != -1)
		{
			ret.replace(start_pos, token.size(), replacement.c_str());
			offset += start_pos + (int)replacement.size();
			start_pos = (int)ret.find(token.c_str(), offset);
		}
		return ret;
	}

	TCTK_DLL TimeString getTime()
	{
		time_t currentTime = std::time(NULL);
		struct tm buf;
		localtime_s(&buf, &currentTime);
		int hour = buf.tm_hour;
		int minute = buf.tm_min;
		int second = buf.tm_sec;
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
		return TimeString(strHour, strMinute, strSecond);
	}
}
#endif