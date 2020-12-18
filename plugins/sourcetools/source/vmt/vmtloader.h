#pragma once

#include "vmtformat.h"

#include "c4d_filterdata.h"

#define ID_VMTLOADER		1056375

class VMTLoaderData : public SceneLoaderData
{
	static NodeData* Create();

public:
	struct Settings
	{
		std::vector<Filename> cdmaterials;
		maxon::String BitmapExtension = "vtf"_s;
	};

	Bool Identify( BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size ) override;
	FILEERROR Load( BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt ) override;

	static Material* CreateVMT( const ValveMaterialType& vmt, const Settings& config );

	static Bool RegisterPlugin();
};