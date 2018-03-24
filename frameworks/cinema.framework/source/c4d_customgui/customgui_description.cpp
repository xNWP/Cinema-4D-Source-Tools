#include "customgui_description.h"
#include "c4d_string.h"
#include "c4d_gui.h"


static DescriptionGuiLib *lib_description = nullptr;


static DescriptionGuiLib *CheckPrefsLib(Int32 offset)
{
	return (DescriptionGuiLib*)CheckLib(CUSTOMGUI_DESCRIPTION, offset, (C4DLibrary**)&lib_description);
}


void DescriptionCustomGui::SetObjectList(const AtomArray &list)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, SetObjectList));
	if (!lib || !lib->SetObjectList) return;

	(((iDescriptionCustomGui*)this)->*lib->SetObjectList)(list);
}

void DescriptionCustomGui::SetObject(C4DAtom *op)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, SetObject));
	if (!lib || !lib->SetObject) return;

	(((iDescriptionCustomGui*)this)->*lib->SetObject)(op);
}

Bool DescriptionCustomGui::GetObjectList(AtomArray &list)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, GetObjectList));
	if (!lib || !lib->GetObjectList) return false;

	return (((iDescriptionCustomGui*)this)->*lib->GetObjectList)(list);
}

void DescriptionCustomGui::SetMaster(GeDialog *dlg, MasterCallBackFunc *func)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, SetMaster));
	if (!lib || !lib->SetMaster) return;

	(((iDescriptionCustomGui*)this)->*lib->SetMaster)(dlg, func);
}

GeData DescriptionCustomGui::MasterMessage(const BaseContainer &msg)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, MasterMessage));
	if (!lib || !lib->MasterMessage) return false;

	return (((iDescriptionCustomGui*)this)->*lib->MasterMessage)(msg);
}

String DescriptionCustomGui::GetFilterString(AMFILTERFLAGS &flags)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, GetFilterString));
	if (!lib || !lib->GetFilterString) return String();

	return (((iDescriptionCustomGui*)this)->*lib->GetFilterString)(flags);
}

void DescriptionCustomGui::SetFilterString(const String &filter, AMFILTERFLAGS flags)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, SetFilterString));
	if (!lib || !lib->SetFilterString) return;

	(((iDescriptionCustomGui*)this)->*lib->SetFilterString)(filter, flags);
}

void DescriptionCustomGui::SetFilter(DescriptionFilter *flt)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, SetFilter));
	if (!lib || !lib->SetFilter) return;

	(((iDescriptionCustomGui*)this)->*lib->SetFilter)(flt);
}

Int32 DescriptionCustomGui::HighlightDescID(Int32 id, Bool check)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, HighlightDescID));
	if (!lib || !lib->HighlightDescID) return 0;

	return (((iDescriptionCustomGui*)this)->*lib->HighlightDescID)(id, check);
}

void DescriptionCustomGui::SetActiveTabPage(const DescID &activetab)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, SetActiveTabPage));
	if (!lib || !lib->SetActiveTabPage) return;

	return (((iDescriptionCustomGui*)this)->*lib->SetActiveTabPage)(activetab);
}

Bool DescriptionCustomGui::GetDescIDSelection(BaseContainer &selection)
{
	DescriptionGuiLib *lib = CheckPrefsLib(LIBOFFSET(DescriptionGuiLib, GetDescIDSelection));
	if (!lib || !lib->GetDescIDSelection) return false;

	return (((iDescriptionCustomGui*)this)->*lib->GetDescIDSelection)(selection);
}
