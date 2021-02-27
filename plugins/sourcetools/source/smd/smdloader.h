#pragma once

#include "c4d_filterdata.h"
#include "smdformat.h"

#include <map>

#define ID_SMDLOADER		1054419

namespace st::smd
{
	class LoaderData : public SceneLoaderData
	{
		static NodeData* Create();

	public:
		Bool Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size) override;
		FILEERROR Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt) override;
		Bool Init(GeListNode* node) override;
		Bool GetDEnabling(GeListNode* node, const DescID& id, const GeData& data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc) override;
		Bool GetDParameter(GeListNode* node, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags) override;

		struct BoneMapData
		{
			std::int16_t ParentId;
			BaseObject* Object;
		};

		struct Settings
		{
			Float Scale = 1.0f;
			maxon::Vector Orientation;
			std::map<std::int16_t, BoneMapData> Skeleton;
			maxon::Bool IncludeAnimation;
			maxon::Bool IncludeMesh;
			maxon::Bool IncludeWeights;
			maxon::Bool IncludeSkeleton;
			maxon::Bool IncludeUVW;
			maxon::Bool IncludePolySelections;
			maxon::Bool IncludeNormals;
			BaseDocument* doc;
		};

		struct SMDObject
		{
			PolygonObject* Mesh;
			std::map<std::int16_t, BoneMapData> Skeleton;
		};

		static SMDObject CreateSMD(const StudiomdlData& smd, const Settings& config);

		static Bool RegisterPlugin();
	};
}