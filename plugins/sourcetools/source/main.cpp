//============ Copyright � 2020 Brett Anthony. All rights reserved. ============
///
/// This work is licensed under the terms of the MIT license.
/// For a copy, see <https://opensource.org/licenses/MIT>.
//==============================================================================
/// @file main.cpp
/// @brief entry point for the plugin.
//==============================================================================

#include "c4d_plugin.h"
#include "c4d_resource.h"

#include "vtf/vtfloader.h"
#include "smd/smdloader.h"
#include "qc/qcloader.h"

#include "c4dst_error.h"

Bool PluginStart()
{
	// VTF Loader
	if ( !VTFLoaderData::RegisterPlugin() )
	{
		LogError( "Failed to register VTF loader." );
		return false;
	}

	// SMD Loader
	if ( !SMDLoaderData::RegisterPlugin() )
	{
		LogError( "Failed to register SMD loader." );
		return false;
	}
	
	// QC Loader
	if ( !QCLoaderData::RegisterPlugin() )
	{
		LogError( "Failed to register QC loader." );
		return false;
	}

	return true;
}

void PluginEnd()
{
}

Bool PluginMessage(Int32 id, void *data)
{
	switch ( id )
	{
		case C4DPL_INIT_SYS:
		{
			if ( g_resource.Init() == false )
			{
				LogError( "Failed to load resources." );
				return false;
			}
		}
	}

	return true;
}