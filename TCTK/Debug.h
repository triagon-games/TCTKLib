#pragma once
#ifndef TCTK_DEBUG
#define TCTK_DEBUG

#include "pch.h"
#include "DLLDefinitions.h"
#include "Strings.h"

namespace DEBUG
{
	TCTK_DLL void printVerboseDebug(std::string p, uint8_t verbosityLevel)
	{
#	ifdef _DEBUG
		if (DEBUG_VERBOSITY_LEVEL >= verbosityLevel)
		{
			std::printf(p.c_str());
		}
#	endif
	}

	TCTK_DLL void printFormattedVerboseDebug(std::string p, uint8_t verbosityLevel)
	{
#	ifdef _DEBUG
		if (DEBUG_VERBOSITY_LEVEL >= verbosityLevel)
		{
			std::printf("[%s:%s:%s]: %s", Strings::getTimeFormatted()[0].c_str(), Strings::getTimeFormatted()[1].c_str(), Strings::getTimeFormatted()[2].c_str(), p.c_str());
		}
#	endif
	}
}

#endif // !TCTK_DEBUG
