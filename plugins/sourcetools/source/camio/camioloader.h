#pragma once

#include <c4d_filterdata.h>

#define ID_CAMIOLOADER 1000001 // TODO: Test ID, replace with registered ID for release!!!

namespace st::camio
{
	class LoaderData : public SceneLoaderData
	{
		static NodeData* Create();

	public:
		Bool Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size) override;
		FILEERROR Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt) override;
		//Bool Init(GeListNode* node) override;
		//Bool GetDEnabling(GeListNode* node, const DescID& id, const GeData& data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc) override;
		//Bool GetDParameter(GeListNode* node, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags) override;

		static Bool RegisterPlugin();
	};
}