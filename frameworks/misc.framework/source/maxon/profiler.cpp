#include "maxon/profiler.h"
#include "maxon/configuration.h"
#include "maxon/branch.h"

namespace maxon
{
MAXON_FEATURE_CONFIGURATION(g_enableInCodeProfiler, "dev_mesh", CONFIGURATION_CATEGORY::DEVELOPMENT, "Enable in-code profiler");
} // namespace maxon
