#include "lib_description.h"


#define LIBID			LIBRARY_DESCRIPTIONLIB
#define LIB				DescriptionLib


static LIB *library = nullptr;


static LIB *CheckLibObjectList(Int32 offset)
{
	return (LIB*)CheckLib(LIBID, offset, (C4DLibrary**)&library);
}





Bool DescLevel::operator == (const DescLevel &d) const
{
	if (d.id != id) return false;

	// special case!
	if (d.dtype == 0 && d.id == 0 && d.creator == 0) return (dtype == 0 && id == 0 && creator == 0);
	else if (dtype == 0 && id == 0 && creator == 0) return (d.dtype == 0 && d.id == 0 && d.creator == 0);

	if (d.dtype && dtype && d.dtype != dtype) return false;
	if (d.creator && creator && d.creator != creator) return false;

	return true;
}

Bool DescLevel::operator != (const DescLevel &d) const
{
	return !(*this == d);
}

Int32 DescID::GetDepth() const
{
	Int32 i = 0;
	for (; (*this)[i].id != 0; i++) { }
	return i;
}

// checks if 'this' is part of 'cmp'
Bool DescID::IsPartOf(const DescID &cmp, Int32 *pos) const
{
	Int32 i;
	for (i = 0; (*this)[i].id != 0; i++)
	{
		// ITEM#37542 MAXON Bug-Report V11.514 [mac], comparing only the id without the type caused a crash in animation.
		if ((*this)[i] != cmp[i])
			break;
	}
	if (pos) *pos = i;
	return i > 0 && (*this)[i].id == 0;
}

Bool Description_Register(Int32 id, const String &idstr, LocalResource *res)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, Register)); if (!lib || !lib->Register) return false;
	return lib->Register(id, idstr, res);
}

#ifndef __API_INTERN__

DescID::DescID()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Init)); if (!lib || !lib->DescID_Init) return;
	lib->DescID_Init(this);
}

DescID::DescID(const DescID &src)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Init)); if (!lib || !lib->DescID_Init) return;
	lib->DescID_Init(this);
	*this = src;
}

DescID::DescID(const DescLevel &id1)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Init)); if (!lib || !lib->DescID_Init) return;
	lib->DescID_Init(this);
	SetId(id1);
}

DescID::DescID(Int32 id1)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Init)); if (!lib || !lib->DescID_Init) return;
	lib->DescID_Init(this);
	SetId(DescLevel(id1));
}

DescID::DescID(const DescLevel &id1, const DescLevel &id2)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Init)); if (!lib || !lib->DescID_Init) return;
	lib->DescID_Init(this);
	SetId(id1);
	PushId(id2);
}

DescID::DescID(const DescLevel &id1, const DescLevel &id2, const DescLevel &id3)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Init)); if (!lib || !lib->DescID_Init) return;
	lib->DescID_Init(this);
	SetId(id1);
	PushId(id2);
	PushId(id3);
}

DescID::~DescID()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Free)); if (!lib || !lib->DescID_Free) return;
	lib->DescID_Free(this);
}

void DescID::SetId(const DescLevel &subid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_SetId)); if (!lib || !lib->DescID_SetId) return;
	lib->DescID_SetId(this, subid);
}

void DescID::PushId(const DescLevel &subid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_PushId)); if (!lib || !lib->DescID_PushId) return;
	lib->DescID_PushId(this, subid);
}

void DescID::PopId()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_PopId)); if (!lib || !lib->DescID_PopId) return;
	lib->DescID_PopId(this);
}

UInt DescID::GetHashCode() const
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_GetHashCode)); if (!lib || !lib->DescID_GetHashCode) return 0;
	return lib->DescID_GetHashCode(this);
}

Bool DescID::Read(HyperFile *hf)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Read)); if (!lib || !lib->DescID_Read) return false;
	return lib->DescID_Read(this, hf);
}

Bool DescID::Write(HyperFile *hf)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Read)); if (!lib || !lib->DescID_Write) return false;
	return lib->DescID_Write(this, hf);
}

DescLevel fallbacklevel(0);

const DescLevel &DescID::operator[] (Int32 pos) const
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_operator1)); if (!lib || !lib->DescID_operator1) return fallbacklevel;
	return lib->DescID_operator1((DescID*)this, pos);
}

const DescID DescID::operator<< (Int32 shift) const
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_operator2)); if (!lib || !lib->DescID_operator2) return fallbacklevel;
	return lib->DescID_operator2((DescID*)this, shift);
}

const DescID& DescID::operator = (const DescID &id)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_CopyTo)); if (!lib || !lib->DescID_CopyTo) return *this;
	lib->DescID_CopyTo((DescID*)&id, (DescID*)this);
	return *this;
}

Bool DescID::operator == (const DescID &d) const
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Compare)); if (!lib || !lib->DescID_Compare) return 0;
	return lib->DescID_Compare((DescID*)&d, (DescID*)this);
}

Bool DescID::operator != (const DescID &d) const
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Compare)); if (!lib || !lib->DescID_Compare) return true;
	return !lib->DescID_Compare((DescID*)&d, (DescID*)this);
}

const DescID & DescID::operator += (const DescID &s)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_AddTo)); if (!lib || !lib->DescID_AddTo) return *this;
	lib->DescID_AddTo((DescID*)this, (DescID*)&s);
	return *this;
}


Description::Description()
{
}

Description *Description::Alloc()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, Alloc)); if (!lib || !lib->Alloc) return nullptr;
	return lib->Alloc();
}

void Description::Free(Description *&description)
{
	if (!description) return;
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, Free)); if (!lib || !lib->Free) return;
	lib->Free(description);
	description = nullptr;
}

Bool Description::LoadDescription(const BCResourceObj *bc, Bool copy)
{
	if (!bc) return false;
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, LoadDescriptionBc)); if (!lib || !lib->LoadDescriptionBc) return false;
	return lib->LoadDescriptionBc(this, bc, copy);
}

Bool Description::LoadDescription(Int32 id)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, LoadDescriptionId)); if (!lib || !lib->LoadDescriptionId) return false;
	return lib->LoadDescriptionId(this, id);
}

Bool Description::LoadDescription(const String &id)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, LoadDescriptionStr)); if (!lib || !lib->LoadDescriptionStr) return false;
	return lib->LoadDescriptionStr(this, &id);
}

Bool Description::SortGroups()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, SortGroups)); if (!lib || !lib->SortGroups) return false;
	return lib->SortGroups(this);
}

const BCResourceObj* Description::GetDescription()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetDescription)); if (!lib || !lib->GetDescription) return nullptr;
	return lib->GetDescription(this);
}

const BaseContainer* Description::GetParameter(const DescID &id, BaseContainer &temp, AtomArray *ar) const
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetParameter)); if (!lib || !lib->GetParameter) return nullptr;
	return lib->GetParameter(this, id, temp, ar);
}

BaseContainer* Description::GetParameterI(const DescID &id, AtomArray *ar)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetParameterI)); if (!lib || !lib->GetParameterI) return nullptr;
	return lib->GetParameterI(this, id, ar);
}

Bool Description::SetParameter(const DescID &id, const BaseContainer &param, const DescID &groupid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetParameter)); if (!lib || !lib->SetParameter) return false;
	return lib->SetParameter(this, id, param, groupid);
}

void *Description::BrowseInit()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, BrowseInit)); if (!lib || !lib->BrowseInit) return nullptr;
	return lib->BrowseInit(this);
}

Bool Description::GetNext(void *handle, const BaseContainer **bc, DescID &id, DescID &groupid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetNext)); if (!lib || !lib->GetNext) return false;
	return lib->GetNext(this, handle, bc, id, groupid);
}

void Description::BrowseFree(void *&handle)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, BrowseFree)); if (!lib || !lib->BrowseFree) return;
	lib->BrowseFree(this, handle);
}

SubDialog *Description::CreateDialogI()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, CreateDialogI)); if (!lib || !lib->CreateDialogI) return nullptr;
	return lib->CreateDialogI(this);
}

void Description::FreeDialog(SubDialog *dlg)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, FreeDialog)); if (!lib) return;
	lib->FreeDialog(this, dlg);
}

Bool Description::CreatePopupMenu(BaseContainer &menu)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, CreatePopupMenu)); if (!lib) return false;
	return lib->CreatePopupMenu(this, &menu);
}

Bool Description::GetPopupId(Int32 id, const DescID &descid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetPopupId)); if (!lib) return false;
	return lib->GetPopupId(this, id, descid);
}

const DescID* Description::GetSingleDescID()
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetSingleDescID)); if (!lib) return nullptr;
	return lib->GetSingleDescID(this);
}

void Description::SetSingleDescriptionMode(const DescID &descid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, SetSingleDescriptionMode)); if (!lib) return;
	lib->SetSingleDescriptionMode(this, descid);
}

Bool Description::GetSubDescriptionWithData(const DescID &did, const AtomArray &op, RESOURCEDATATYPEPLUGIN *resdatatypeplugin, const BaseContainer &bc, DescID *singledescid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetSubDescriptionWithData)); if (!lib) return false;
	return lib->GetSubDescriptionWithData(this, did, op, resdatatypeplugin, bc, singledescid);
}

Bool Description::CheckDescID(const DescID &searchid, const AtomArray &ops, DescID *completeid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, CheckDescID)); if (!lib) return false;
	return lib->CheckDescID(this, searchid, ops, completeid);
}

DescEntry* Description::GetFirst(const AtomArray &op)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescEntryGetFirst)); if (!lib) return nullptr;
	return lib->DescEntryGetFirst(this, op);
}

DescEntry* Description::GetNext(DescEntry *de)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescEntryGetNext)); if (!lib) return nullptr;
	return lib->DescEntryGetNext(this, de);
}

DescEntry* Description::GetDown(DescEntry *de)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescEntryGetDown)); if (!lib) return nullptr;
	return lib->DescEntryGetDown(this, de);
}

void Description::GetDescEntry(DescEntry *de, const BaseContainer **bc, DescID &descid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescEntryGetDescEntry)); if (!lib) return;
	lib->DescEntryGetDescEntry(this, de, bc, descid);
}

String DescGenerateTitle(AtomArray *arr)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescEntryGetDescEntry)); if (!lib) return String();
	return lib->DescGenerateTitle(arr);
}

const DescID operator+(const DescID &v1, const DescID &v2)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DescID_Add)); if (!lib || !lib->DescID_Add) return v1;
	return lib->DescID_Add((DescID*)&v1, (DescID*)&v2);
}

DescID DynamicDescription::Alloc(const BaseContainer &datadescription)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DDAlloc)); if (!lib || !lib->DDAlloc) return DescLevel(0);
	return (this->*lib->DDAlloc)(datadescription);
}

Bool DynamicDescription::Set(const DescID &descid, const BaseContainer &datadescription, BaseList2D *bl)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DDSet)); if (!lib || !lib->DDSet) return false;
	return (this->*lib->DDSet)(descid, datadescription, bl);
}

const BaseContainer* DynamicDescription::Find(const DescID &descid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DDFind)); if (!lib || !lib->DDFind) return nullptr;
	return (this->*lib->DDFind)(descid);
}

Bool DynamicDescription::Remove(const DescID &descid)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DDRemove)); if (!lib || !lib->DDRemove) return false;
	return (this->*lib->DDRemove)(descid);
}

Bool DynamicDescription::CopyTo(DynamicDescription *dest)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DDCopyTo)); if (!lib || !lib->DDCopyTo) return false;
	return (this->*lib->DDCopyTo)(dest);
}

void* DynamicDescription::BrowseInit(void)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DDBrowseInit)); if (!lib || !lib->DDBrowseInit) return nullptr;
	return (this->*lib->DDBrowseInit)();
}

Bool DynamicDescription::BrowseGetNext(void* handle, DescID *id, const BaseContainer **data)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DDBrowseGetNext)); if (!lib || !lib->DDBrowseGetNext) return false;
	return (this->*lib->DDBrowseGetNext)(handle, id, data);
}

void DynamicDescription::BrowseFree(void* &handle)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, DDBrowseFree)); if (!lib || !lib->DDBrowseFree) return;
	(this->*lib->DDBrowseFree)(handle);
}

Bool DynamicDescription::FillDefaultContainer(BaseContainer &res, Int32 type, const String &name)
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, FillDefaultContainer)); if (!lib || !lib->FillDefaultContainer) return false;
	return (this->*lib->FillDefaultContainer)(res, type, name);
}

UInt32 DynamicDescription::GetDirty() const
{
	LIB *lib = CheckLibObjectList(LIBOFFSET(LIB, GetDirty)); if (!lib || !lib->GetDirty) return 0;
	const UInt32 dirty = (this->*lib->GetDirty)();
	return dirty;
}

#endif

