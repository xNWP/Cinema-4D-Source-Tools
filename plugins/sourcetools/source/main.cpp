//============ Copyright © 2020 Brett Anthony. All rights reserved. ============
///
/// This work is licensed under the terms of the MIT license.
/// For a copy, see <https://opensource.org/licenses/MIT>.
//==============================================================================
/// @file main.cpp
/// @brief entry point for the plugin.
//==============================================================================

#include "c4d.h"

#include "vtf/vtfloader.h"

Bool PluginStart()
{
	// VTF Loader
	if (!VTFLoaderData::RegisterPlugin())
		return false;

	return true;
}

void PluginEnd()
{
}

Bool PluginMessage(Int32 id, void *data)
{
	return false;
}