#pragma once

#ifndef TCTK_LOGGER
#define TCTK_LOGGER
#include "pch.h"
#include "DLLDefinitions.h"
#include "Strings.h"
#include "Error.h"


namespace Logging
{
	std::ofstream logger;
	
	TCTKError::C_Error InitLogger(std::string)
}

#endif