#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(C4DMISC_DEBUGGLOBALS_H__)
#define C4DMISC_DEBUGGLOBALS_H__

#include "../general.h"

namespace maxon
{

class DebuggerC4D
{
public:
	static Bool	IsPresent();
};

} // namespace maxon

#endif
