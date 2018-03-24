#include "lib_activeobjectmanager.h"
#include "ge_autoptr.h"
#include "c4d_baselist.h"


#define LIBID			LIBRARY_ACTIVEOBJECTMANAGER
#define LIB				ActiveObjectManagerLib


static LIB *library = nullptr;


static LIB *CheckLibObjectList(Int32 offset)
{
	return (LIB*)CheckLib(LIBID, offset, (C4DLibrary**)&library);
}


Bool ActiveObjectManager_RegisterMode(ACTIVEOBJECTMODE id, const String &text, MESSAGEHOOK *hook)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, RegisterMode)); if (!lib || !lib->RegisterMode) return false;
	return lib->RegisterMode(id, text, hook);
}

void ActiveObjectManager_SetMode(ACTIVEOBJECTMODE id, Bool openmanager)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, SetMode)); if (!lib || !lib->SetMode) return;
	lib->SetMode(id, openmanager);
}

void ActiveObjectManager_SetObjects(ACTIVEOBJECTMODE id, const AtomArray &objects, Int32 flags, const DescID &activepage)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, SetObjects)); if (!lib || !lib->SetObjects) return;
	lib->SetObjects(id, objects, flags, activepage);
}

void ActiveObjectManager_SetObject(ACTIVEOBJECTMODE id, C4DAtom *op, Int32 flags, const DescID &activepage)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, SetObjects)); if (!lib || !lib->SetObjects) return;
	AutoAlloc<AtomArray> objects; if (!objects) return;
	objects->Append(op);
	lib->SetObjects(id, objects, flags, activepage);
}

Bool ActiveObjectManager_GetObjects(ACTIVEOBJECTMODE id, AtomArray &objects)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetObjects)); if (!lib || !lib->GetObjects) return false;
	return lib->GetObjects(id, objects);
}

Bool ActiveObjectManager_GetModeInfo(ACTIVEOBJECTMODE id, ActiveModeInfo &info)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetModeInfo)); if (!lib || !lib->GetModeInfo) return false;
	return lib->GetModeInfo(id, info);
}

Int32 ActiveObjectManager_GetModeCount()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetModeCount)); if (!lib || !lib->GetModeCount) return false;
	return lib->GetModeCount();
}

Bool ActiveObjectManager_GetModeInfoIdx(Int32 idx, ActiveModeInfo &info)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetModeInfoIdx)); if (!lib || !lib->GetModeInfoIdx) return false;
	return lib->GetModeInfoIdx(idx, info);
}

ACTIVEOBJECTMODE ActiveObjectManager_GetLastMode()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetLastMode)); if (!lib || !lib->GetLastMode) return ACTIVEOBJECTMODE_NONE;
	return lib->GetLastMode();
}

void ActiveObjectManager_Open()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, Open)); if (!lib || !lib->Open) return;
	lib->Open();
}

Bool EditObjectModal(const AtomArray &objects, const String &dlgtitle)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, EditObjectModal)); if (!lib || !lib->EditObjectModal) return false;
	return lib->EditObjectModal(objects, dlgtitle);
}

Bool EditObjectModal(C4DAtom *op, const String &dlgtitle)
{
	if (!op) return false;
	AutoAlloc<AtomArray> objects; if (!objects) return false;
	objects->Append(op);
	return EditObjectModal(objects, dlgtitle);
}

Bool EditDescription(C4DAtom *bl, const DescID &id)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, EditDescription)); if (!lib || !lib->EditDescription) return false;
	return lib->EditDescription(bl, id);
}

void AddDescription(C4DAtom* bl)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, AddDescription)); if (!lib || !lib->AddDescription) return;
	return lib->AddDescription(bl);
}

void PasteDescription(C4DAtom* bl)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, PasteDescription)); if (!lib || !lib->PasteDescription) return;
	return lib->PasteDescription(bl);
}
