#ifndef SMD_LOADER_H__
#define SMD_LOADER_H__

#include <c4d_filterdata.h>
#include "smdformat.h"

#include <map>
#include <memory>

#define ID_SMDLOADER		1054419

class SMDLoaderData : public SceneLoaderData
{
	static NodeData* Create();

public:
	Bool Identify( BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size ) override;
	FILEERROR Load( BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt ) override;
	Bool Init( GeListNode *node ) override;

	struct BoneMapData
	{
		std::int16_t ParentId;
		BaseObject* Object;
	};

	struct Settings
	{
		Float Scale = 1.0f;
		maxon::Vector Orientation;
		BaseObject* MeshRootObject = nullptr;
		BaseObject* SkeletonRootObject = nullptr;
		std::shared_ptr<std::map<std::int16_t, BoneMapData>> Skeleton = nullptr;
		maxon::Bool IncludeAnimation;
		maxon::Bool IncludeMesh;
		maxon::Bool IncludeWeights;
		maxon::Bool IncludeSkeleton;
	};

	struct SMDObject
	{
		PolygonObject* Mesh;
		std::shared_ptr<std::map<std::int16_t, BoneMapData>> Skeleton;
	};
	
	static SMDObject CreateSMD( const StudiomdlData& smd, const maxon::String& name, Settings config, BaseDocument* doc);

	static Bool RegisterPlugin();
};

#endif // !SMD_LOADER_H__
