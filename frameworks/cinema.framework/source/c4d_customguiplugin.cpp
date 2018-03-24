#include "c4d_customguiplugin.h"
#include "c4d_memory.h"
#include "c4d_basebitmap.h"
#include "c4d_general.h"
#include "c4d_gui.h"
#include "operatingsystem.h"


Bool RegisterCustomGuiPlugin(const String& str, Int32 info, CustomGuiData* dat)
{
	if (!dat)
		return false;

	CUSTOMGUIPLUGIN np;
	ClearMem(&np, sizeof(np));

	np.adr	= dat;
	np.info	= info;
	np.Destructor	= &BaseData::Destructor;
	np.Alloc = &CustomGuiData::Alloc;
	np.Free	 = &CustomGuiData::Free;
	np.GetResourceSym	= &CustomGuiData::GetResourceSym;
	np.GetProperties	= &CustomGuiData::GetProperties;
	np.GetResourceDataType = &CustomGuiData::GetResourceDataType;

	return GeRegisterPlugin(PLUGINTYPE_CUSTOMGUI, dat->GetId(), str, &np, sizeof(np));
}

CUSTOMGUIPLUGIN* FindCustomGuiPlugin(Int32 type)
{
	BasePlugin* plug = FindPlugin(type, PLUGINTYPE_CUSTOMGUI);
	if (!plug)
		return nullptr;

	return (CUSTOMGUIPLUGIN*)plug->GetPluginStructure();
}
