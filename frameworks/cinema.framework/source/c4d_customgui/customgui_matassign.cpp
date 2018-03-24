#include "customgui_matassign.h"
#include "c4d_string.h"
#include "c4d_gui.h"


static CustomGuiMatAssignLib *lib_matassign = nullptr;


static CustomGuiMatAssignLib *CheckLib(Int32 offset)
{
	return (CustomGuiMatAssignLib*)CheckLib(CUSTOMGUI_MATASSIGN, offset, (C4DLibrary**)&lib_matassign);
}

#define InExcludeCall(b) 			CustomGuiMatAssignLib *lib = CheckLib(LIBOFFSET(CustomGuiMatAssignLib, b)); \
															if (!lib || !lib->b) return; \
															(((iMatAssignData*)this)->*lib->b)

#define InExcludeCallR(a, b) 		CustomGuiMatAssignLib *lib = CheckLib(LIBOFFSET(CustomGuiMatAssignLib, b)); \
															if (!lib || !lib->b) return a; \
															return (((iMatAssignData*)this)->*lib->b)

#define InExcludeGuiCall(b) 		CustomGuiMatAssignLib *lib = CheckLib(LIBOFFSET(CustomGuiMatAssignLib, b)); \
															if (!lib || !lib->b) return; \
															(((iMatAssignCustomGui*)this)->*lib->b)

#define InExcludeGuiCallR(a, b) CustomGuiMatAssignLib *lib = CheckLib(LIBOFFSET(CustomGuiMatAssignLib, b)); \
															if (!lib || !lib->b) return a; \
															return (((iMatAssignCustomGui*)this)->*lib->b)

#define IncludeTableCallR(a, b) 		CustomGuiMatAssignLib *lib = CheckLib(LIBOFFSET(CustomGuiMatAssignLib, b)); \
															if (!lib || !lib->b) return a; \
															return (((iMatAssignTable*)this)->*lib->b)

Bool MatAssignData::InsertObject(BaseList2D* pObject, Int32 lFlags) { InExcludeCallR(false, InsertObject)(pObject, lFlags); }
Int32 MatAssignData::GetObjectIndex(BaseDocument *doc, BaseList2D* pObject) { InExcludeCallR(-1, GetObjectIndex)(doc, pObject); }
Bool MatAssignData::DeleteObject(Int32 lIndex) { InExcludeCallR(false, DeleteObject)(lIndex); }
Int32 MatAssignData::GetObjectCount() { InExcludeCallR(0, GetObjectCount)(); }
BaseList2D* MatAssignData::ObjectFromIndex(BaseDocument *doc, Int32 lIndex) { InExcludeCallR(nullptr, ObjectFromIndex)(doc, lIndex); }
void MatAssignData::SetMaterial(const AtomArray &materials) { InExcludeCall(SetMaterial)(materials); }
Bool MatAssignData::GetMaterial(BaseDocument *doc, AtomArray &materials) { InExcludeCallR(false, GetMaterial)(doc, materials); }

Bool MatAssignTable::Check(BaseList2D *op) { IncludeTableCallR(false, Check)(op); }
Int32 MatAssignTable::GetObjectCount() { IncludeTableCallR(false, GetObjectCountT)(); }
BaseList2D* MatAssignTable::GetObject(Int32 lIndex) { IncludeTableCallR(nullptr, GetObject)(lIndex); }
void FreeInclusionTable(MatAssignTable *&pTable)
{
	if (!pTable) return;
	CustomGuiMatAssignLib *lib = CheckLib(LIBOFFSET(CustomGuiMatAssignLib, LIB_FreeInclusionTable));
	if (!lib || !lib->LIB_FreeInclusionTable) return;
	MatAssignTable* t = pTable;
	(lib->LIB_FreeInclusionTable)((iMatAssignTable*)t);
	pTable = nullptr;
}
