#include "error.h"

#include "maxon/logger.h"
#include "c4d.h"

static const maxon::Id loggerid("com.thatnwp.xNWP.sourcetoolslogger");
class LoggerImpl;
static LoggerImpl* g_instance;

class LoggerImpl
{
	maxon::LoggerRef _logger;

public:
	static void Write(const String& msg)
	{
		if (g_instance == nullptr)
		{
			g_instance = new LoggerImpl;
			g_instance->_logger = maxon::LoggerRef::Create().UncheckedGetValue();
			g_instance->_logger.AddLoggerType(maxon::TARGETAUDIENCE::ALL, maxon::LoggerTypes::Application()).UncheckedGetValue();
			g_instance->_logger.SetName("Source Tools"_s);
			maxon::Loggers::Insert(loggerid, g_instance->_logger).UncheckedGetValue();
			const maxon::Int32 BFM_REBUILDCONSOLETREE = 334295845;
			SpecialEventAdd(BFM_REBUILDCONSOLETREE);
		}

		g_instance->_logger.Write(maxon::TARGETAUDIENCE::ALL, msg, maxon::SourceLocation::NullValue()).UncheckedGetValue();
	}
};

void st::iLog(const String& msg)
{
	LoggerImpl::Write(msg);
}

void st::iLogError(const String& msg, const char* FILE, const char* FUNC, UInt LINE)
{
	String m = "ERROR: "_s; m += msg;
	m += "\nFILE: "_s; m += FILE;
	m += "\nFUNC: "_s; m += FUNC;
	m += "\nLINE: "_s; m += maxon::ToString(LINE, nullptr);

	st::iLog(m);
}

void st::iLogErrorWhat(const String& WHAT, const char* FILE, const char* FUNC, UInt LINE)
{
	String m = "ERRORWHAT: "_s; m += WHAT;
	m += "\nFILE: "_s; m += FILE;
	m += "\nFUNC: "_s; m += FUNC;
	m += "\nLINE: "_s; m += maxon::ToString(LINE, nullptr);

	st::iLog(m);
}
