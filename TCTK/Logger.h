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
		Strings::TimeString ts = Strings::getTime();
		path = Strings::replace(filepath.c_str(), "$H", ts.Hours.c_str());
		path = Strings::replace(path.c_str(), "$M", ts.Minutes.c_str());
		path = Strings::replace(path.c_str(), "$S", ts.Seconds.c_str());
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

	TCTKError::C_Error Write(std::string message, std::string format = "[$H-$M-$S]: %s\n")
	{
		TCTKError::C_Error err;
		std::string write;
		Strings::TimeString ts = Strings::getTime();
		write = Strings::replace(format.c_str(), "$H", ts.Hours.c_str());
		write = Strings::replace(write.c_str(), "$M", ts.Minutes.c_str());
		write = Strings::replace(write.c_str(), "$S", ts.Seconds.c_str());
		write = Strings::sprintf(write.c_str(), message.c_str());

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

	void Deinit()
	{
		delete &logger;
	}
}

#define LOG_START try\
{\
	try\
	{
#define LOG_END }catch (std::exception_ptr & ex)\
{\
	std::rethrow_exception(ex);\
}\
}\
catch(std::exception& e)\
{\
Logging::Write(Strings::sprintf("An exception has occured in function (%s): %s", __func__, e.what())); \
}

#endif