#pragma once

#include "pch.h"
#include "Configuration.h"
#include "DLLDefinitions.h"

namespace TCTKError
{
	struct C_Error
	{
	public:
		int16_t code = 0;
		std::string func_name;
		std::string message;
	};
}