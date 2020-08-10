#pragma once

#ifndef TCTK_LOGGER
#define TCTK_LOGGER
#include "pch.h"
#include "DLLDefinitions.h"
#include "Strings.h"
#include "Error.h"
#include <exception>

namespace Logging
{
	std::ofstream logger;
	
	TCTKError::C_Error Init(std::string filepath = "$H-$M-$S.log")
	{
		TCTKError::C_Error err;
		std::string path;
		std::string* time = Strings::getTime();
		path = Strings::replace(filepath.c_str(), "$H", time[0].c_str());
		path = Strings::replace(filepath.c_str(), "$M", time[1].c_str());
		path = Strings::replace(filepath.c_str(), "$S", time[2].c_str());
		logger.open(path.c_str());
		if (!logger.is_open())
		{
			err = TCTKError::Throw(1, __func__, "Could not create log file");
		}
		else
		{
			err = TCTKError::Throw(0, __func__, "Success");
		}
		return err;
	}

	TCTKError::C_Error Write(std::string message, std::string format = "[$D-$M-$S]: %s\n")
	{
		TCTKError::C_Error err;
		std::string write;
		std::string* time = Strings::getTime();
		write = Strings::replace(format.c_str(), "$H", time[0].c_str());
		write = Strings::replace(format.c_str(), "$M", time[1].c_str());
		write = Strings::replace(format.c_str(), "$S", time[2].c_str());
		write = Strings::sprintf(format.c_str(), message);

		logger.write(write.c_str(), write.size());
		if (logger.rdstate() != logger.goodbit)
		{
			switch (logger.rdstate())
			{
			case std::ifstream::failbit:
				err = TCTKError::Throw(1, __func__, "Logical error on i/o operation");
				break;
			case std::ifstream::badbit:
				err = TCTKError::Throw(2, __func__, "Read/writing error on i/o operation");
				break;
			case std::ifstream::eofbit:
				err = TCTKError::Throw(3, __func__, "End-of-File reached on input operation");
				break;
			default:
				err = TCTKError::Throw(-1, __func__, "An error has occured when reading/writing");
				break;
			}
		}
		else err = TCTKError::Throw(0, __func__, "Success");
		return err;
	}
}

#define LOG_START std::exception_ptr EXPTR; \
try{\
	try{
#define LOG_END }\
catch(std::exception_ptr& ex)\
{\
	std::rethrow_exception(ex);\
}}\
catch(std::exception& e)\
{\
Logging::Write(Strings::sprintf("An exception has occured: %s", e.what())); \
}

#endif