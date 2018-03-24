#include "c4d_help.h"
#include "operatingsystem.h"
#include "c4d_general.h"

Bool RegisterPluginHelpDelegate(Int32 pluginId, PluginHelpDelegate delegate)
{
	// Register delegate in the help system.
	return C4DOS.Ge->RegisterPluginHelpDelegate(pluginId, delegate);
}

void OpenHelpBrowser(const String& opType, const String& baseType, const String& group, const String& property)
{
	// Open the help browser for the indicated topic.
	C4DOS.Ge->OpenHelpBrowser(opType, baseType, group, property);
}
