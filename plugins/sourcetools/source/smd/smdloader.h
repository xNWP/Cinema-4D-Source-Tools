#ifndef SMD_LOADER_H__
#define SMD_LOADER_H__

#include <c4d_filterdata.h>

#define ID_SMDLOADER		1054419

class SMDLoaderData : public SceneLoaderData
{
	static NodeData* Create();

public:
	Bool Identify( BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size ) override;
	FILEERROR Load( BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt ) override;
	Bool Init( GeListNode *node ) override;

	static Bool RegisterPlugin();
};

#endif // !SMD_LOADER_H__
