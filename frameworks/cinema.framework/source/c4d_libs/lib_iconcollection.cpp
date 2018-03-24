#include "lib_iconcollection.h"
#include "ge_autoptr.h"
#include "c4d_baselist.h"


#define LIBID			LIBRARY_ICON_COLLECTION
#define LIB				IconCollectionLib


static LIB *library = nullptr;


static LIB *CheckLibObjectList(Int32 offset)
{
	return (LIB*)CheckLib(LIBID, offset, (C4DLibrary**)&library);
}


Bool RegisterIcon(Int32 lIconID, BaseBitmap * pBmp, Int32 x, Int32 y, Int32 w, Int32 h, ICONFLAG lFlags)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, RegisterIconBitmap)); if (!lib || !lib->RegisterIconBitmap) return false;
	return lib->RegisterIconBitmap(lIconID, pBmp, x, y, w, h, lFlags);
}

Bool RegisterIcon(Int32 lIconID, Filename fn, Int32 x, Int32 y, Int32 w, Int32 h, ICONFLAG lFlags)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, RegisterIconFile)); if (!lib || !lib->RegisterIconFile) return false;
	return lib->RegisterIconFile(lIconID, fn, x, y, w, h, lFlags);
}

Bool GetIcon(Int32 lIconID, IconData* pData)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetIcon)); if (!lib || !lib->GetIcon) return false;
	return lib->GetIcon(lIconID, pData);
}

Bool UnregisterIcon(Int32 lIconID)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, UnregisterIcon)); if (!lib || !lib->UnregisterIcon) return false;
	return lib->UnregisterIcon(lIconID);
}
