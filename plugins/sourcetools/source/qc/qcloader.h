#ifndef QC_LOADER_H__
#define QC_LOADER_H__

#include <c4d_filterdata.h>

#define ID_QCLOADER 1000001 // TODO: Temp value, replace with real id

class QCLoaderData : public SceneLoaderData
{
	static NodeData* Create();

public:
	Bool Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size) override;
	FILEERROR Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt) override;

	static Bool RegisterPlugin();
};

#endif // !QC_LOADER_H__