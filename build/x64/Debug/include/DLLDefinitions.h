#pragma once

#ifdef _DLL_EXPORT
#	define TCTK_DLL __declspec(dllexport)
#else
#	ifndef _LIB
#		define TCTK_DLL __declspec(dllimport)
#	else
#		define TCTK_DLL
#	endif
#endif