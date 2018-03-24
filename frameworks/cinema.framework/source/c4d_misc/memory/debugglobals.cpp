#if !defined(__API_INTERN__) && !defined(USE_API_MAXON)

#include "ge_math.h"
#include "debugglobals.h"
#include "c4d_general.h"
#include <time.h>

#ifdef MAXON_TARGET_OSX
	#include <assert.h>
	#include <unistd.h>
	#include <sys/sysctl.h>
#elif defined(MAXON_TARGET_WINDOWS)
	#include "windows_include.h"
#endif
#include <stdio.h>
#include <stdarg.h>

namespace maxon
{

class System
{
public:
	static OUTPUT GetConsoleOutputType()
	{
		return OUTPUT_DIAGNOSTIC|OUTPUT_WARNING|OUTPUT_CRITICAL|OUTPUT_NOLINEBREAK;
	}

	static void	_ConsoleOutputC4D(const Char* s)
	{
		::GeDebugOut("%s", s);
	}
};

inline Int sprintf_safe(Char *_DstBuf, Int _MaxCount, const Char * _Format, ...)
{
	if (_MaxCount <= 0) return 0;

	va_list arp;
	va_start(arp, _Format);
	Int res = vsnprintf(_DstBuf, (size_t)_MaxCount, _Format, arp);
	if (res<0 || res >= _MaxCount)
	{
		if (res < 0) CriticalStop();
		_DstBuf[_MaxCount-1] = 0;
		res = _MaxCount-1;
	}

	va_end(arp);
	return res;
}

static void _DebugHeader(Int line, const Char* file)
{
	time_t rawtime;
	time(&rawtime);
	struct tm* timeinfo = localtime(&rawtime);

	Char timestring[64], dst[1024];
	strftime(timestring, 63, "%H:%M:%S", timeinfo);

	sprintf_safe(dst, 1023, " [%s %s L%d]", timestring, file, line);
	System::_ConsoleOutputC4D(dst);
}

static OUTPUT g_enabledOutput = OUTPUT_DIAGNOSTIC|OUTPUT_WARNING|OUTPUT_CRITICAL|OUTPUT_NOLINEBREAK;

void _ConsoleOutputC4D(OUTPUT flags, const Char* str, Int line, const Char* file)
{
	if (!(g_enabledOutput & flags & (OUTPUT_DIAGNOSTIC | OUTPUT_WARNING | OUTPUT_CRITICAL)))
		return;

	if (flags & OUTPUT_WARNING)
		System::_ConsoleOutputC4D("WARNING: ");
	else if (flags & OUTPUT_CRITICAL)
		System::_ConsoleOutputC4D("CRITICAL: ");

	System::_ConsoleOutputC4D(str);

	if (flags & OUTPUT_HEADER)
		_DebugHeader(line, file);

	if (!(flags & OUTPUT_NOLINEBREAK))
		System::_ConsoleOutputC4D("\n");
}

void _ConsoleOutputC4D(OUTPUT flags, const Char* fmt, Int line, const volatile Char* file, ...)
{
	if (g_enabledOutput & OUTPUT_NOLINEBREAK) // detect first use
		g_enabledOutput = System::GetConsoleOutputType();

	if (!(g_enabledOutput & flags & (OUTPUT_DIAGNOSTIC|OUTPUT_WARNING|OUTPUT_CRITICAL)))
		return;

	Char t[2048];

	va_list arp;
	va_start(arp, file);

	#ifdef MAXON_TARGET_WINDOWS
		_vsnprintf(t, 2046, fmt, arp);
	#else
		vsnprintf(t, 2046, fmt, arp);
	#endif

	if (flags&OUTPUT_WARNING)
		System::_ConsoleOutputC4D("WARNING: ");
	else if (flags&OUTPUT_CRITICAL)
		System::_ConsoleOutputC4D("CRITICAL: ");

	System::_ConsoleOutputC4D(t);

	if (flags&OUTPUT_HEADER)
		_DebugHeader(line, const_cast<Char*>(file));

	if (!(flags&OUTPUT_NOLINEBREAK))
		System::_ConsoleOutputC4D("\n");

	va_end(arp);
}

#ifdef MAXON_TARGET_OSX
// Returns true if the current process is being debugged (either
// running under the debugger or has a debugger attached post facto).
Bool DebuggerC4D::IsPresent()
{
	int								junk;
	int								mib[4];
	struct kinfo_proc info;
	size_t						size;

	// Initialize the flags so that, if sysctl fails for some bizarre
	// reason, we get a predictable result.

	info.kp_proc.p_flag = 0;

	// Initialize mib, which tells sysctl the info we want, in this case
	// we're looking for information about a specific process ID.

	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PID;
	mib[3] = getpid();

	// Call sysctl.

	size = SIZEOF(info);
	junk = sysctl(mib, SIZEOF(mib) / SIZEOF(*mib), &info, &size, nullptr, 0);
	assert(junk == 0);

	// We're being debugged if the P_TRACED flag is set.

	return (info.kp_proc.p_flag & P_TRACED) != 0;
}

Bool g_isDebuggerPresent = DebuggerC4D::IsPresent();

#elif defined(MAXON_TARGET_WINDOWS)

Bool DebuggerC4D::IsPresent()
{
	return IsDebuggerPresent() != 0;
}

Bool g_isDebuggerPresent = DebuggerC4D::IsPresent();

#else

Bool g_isDebuggerPresent = false;

#endif

Bool g_enableDebugBreak = true;
Bool g_enableParallelFor = true;

} // namespace maxon
#endif
