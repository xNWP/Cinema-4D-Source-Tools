#include "c4d_memory.h"
#include "c4d_general.h"
#include "c4d_basebitmap.h"
#include "c4d_tagplugin.h"
#include "c4d_file.h"
#include "c4d_resource.h"
#ifdef __API_INTERN__
	#include "operatingsystem.h"
#else
	#include "ge_prepass.h"
#endif

Bool TagData::Draw(BaseTag* tag, BaseObject* op, BaseDraw* bd, BaseDrawHelp* bh)
{
	return true;
}

Bool TagData::GetModifiedObjects(BaseTag* tag, BaseDocument* doc, BaseObject*& op, Bool& pluginownedop, const Matrix& op_mg, Float lod, Int32 flags, BaseThread* thread)
{
	return true;
}

EXECUTIONRESULT TagData::Execute(BaseTag* tag, BaseDocument* doc, BaseObject* op, BaseThread* bt, Int32 priority, EXECUTIONFLAGS flags)
{
	return EXECUTIONRESULT_OK;
}

Bool TagData::AddToExecution(BaseTag* tag, PriorityList* list)
{
	return false;
}

static void FillTagPlugin(TAGPLUGIN* np, DataAllocator* npalloc, Int32 info, Int32 disklevel, BaseBitmap* icon)
{
	FillNodePlugin(np, info, npalloc, icon, disklevel, nullptr);

	np->Draw = &TagData::Draw;
	np->Execute	= &TagData::Execute;
	np->AddToExecution = &TagData::AddToExecution;
	np->GetModifiedObjects = &TagData::GetModifiedObjects;
}

Bool RegisterTagPlugin(Int32 id, const String& str, Int32 info, DataAllocator* npalloc, const String& description, BaseBitmap* icon, Int32 disklevel)
{
	if (description.Content() && !RegisterDescription(id, description))
		return false;

	TAGPLUGIN np;
	ClearMem(&np, sizeof(np));
	FillTagPlugin(&np, npalloc, info, disklevel, icon);
	return GeRegisterPlugin(PLUGINTYPE_TAG, id, str, &np, sizeof(np));
}
