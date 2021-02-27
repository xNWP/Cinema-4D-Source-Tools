#pragma once

#include "maxon/string.h"

namespace st
{
	void iLog(const maxon::String& msg);
	void iLogError(const maxon::String& msg, const char* FILE, const char* FUNC, unsigned int LINE);
	void iLogErrorWhat(const maxon::String& WHAT, const char* FILE, const char* FUNC, unsigned int LINE);
}

#define Log( MSG ) st::iLog(maxon::String(MSG))
#define LogError( MSG ) st::iLogError(maxon::String(MSG), __FILE__, __func__, __LINE__)
#define LogErrorWhat( WHAT ) st::iLogErrorWhat(maxon::String(WHAT.what()), __FILE__, __func__, __LINE__)