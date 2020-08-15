#pragma once

#include "pch.h"
#include "Configuration.h"
#include "DLLDefinitions.h"
#include "Strings.h"

namespace TCTKError
{
	struct C_Error
	{
	public:
		int16_t code = 0;
		std::string func_name;
		std::string message;
		C_Error() {}
		C_Error(int16_t c, std::string n, std::string m)
		{
			code = c;
			func_name = n;
			message = m;
		}
	};

	C_Error Throw(int16_t _code, std::string _func_name, std::string _message = "")
	{
		return C_Error(_code, _func_name, _message);
	}


}