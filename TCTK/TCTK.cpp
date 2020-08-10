// TCTK.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "Logger.h"

// TODO: This is an example of a library function
void fnTCTK()
{
	Logging::Init();
	LOG_START
		throw(std::exception("Example exception"));
	LOG_END
}
