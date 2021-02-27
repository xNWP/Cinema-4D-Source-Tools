#include "c4d_plugin.h"
#include "c4d_resource.h"

#include "vtf/vtfloader.h"
#include "smd/smdloader.h"
#include "qc/qcloader.h"
#include "vmt/vmtloader.h"
#include "camio/camioloader.h"

#include "error.h"

#define SOURCETOOLS_VERSION_MAJOR 0
#define SOURCETOOLS_VERSION_MINOR 90
#define SOURCETOOLS_VERSION_TAG "dev"

Bool PluginStart()
{
	using namespace st;

	// VTF Loader
	if (!vtf::LoaderData::RegisterPlugin())
	{
		LogError("Failed to register VTF loader.");
		return false;
	}

	// SMD Loader
	if (!smd::LoaderData::RegisterPlugin())
	{
		LogError("Failed to register SMD loader.");
		return false;
	}
	
	// QC Loader
	if (!qc::LoaderData::RegisterPlugin())
	{
		LogError("Failed to register QC loader.");
		return false;
	}

	// VMT Loader
	if (!vmt::LoaderData::RegisterPlugin())
	{
		LogError("Failed to register VMT loader.");
		return false;
	}

	// CamIO Loader
	if (!camio::LoaderData::RegisterPlugin())
	{
		LogError("Failed to register CamIO Loader.");
		return false;
	}

	Log("Loaded all sourcetools modules.");
	String VersionMessage = "Version: "_s + maxon::ToString(SOURCETOOLS_VERSION_MAJOR, nullptr)
		+ "."_s + maxon::ToString(SOURCETOOLS_VERSION_MINOR, nullptr) +
		maxon::ToString(SOURCETOOLS_VERSION_TAG, nullptr);
	#ifdef _DEBUG
		VersionMessage += "-debug";
	#endif
	#ifdef ST_PROFILING
		VersionMessage += "-profiling";
	#endif
	Log(VersionMessage);

	return true;
}

void PluginEnd()
{
}

Bool PluginMessage(Int32 id, void *data)
{
	switch (id)
	{
		case C4DPL_INIT_SYS:
		{
			if (g_resource.Init() == false)
			{
				LogError("Failed to load resources.");
				return false;
			}
		}
	}

	return true;
}