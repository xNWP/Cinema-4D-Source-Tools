#include "customgui_hyperlink.h"
#include "c4d_string.h"
#include "c4d_gui.h"


HyperLinkStaticLib *lib_hyperlinkstatic = nullptr;


static HyperLinkStaticLib *CheckPrefsLib(Int32 offset)
{
	return (HyperLinkStaticLib*)CheckLib(CUSTOMGUI_HYPER_LINK_STATIC, offset, (C4DLibrary**)&lib_hyperlinkstatic);
}

Bool HyperLinkCustomGui::SetLinkString(const String* pStrLink, const String *pStrText)
{
	HyperLinkStaticLib *lib = CheckPrefsLib(LIBOFFSET(HyperLinkStaticLib, SetLinkString));
	if (!lib || !lib->SetLinkString) return false;

	return (((iHyperLinkCustomGui*)this)->*lib->SetLinkString)(pStrLink, pStrText);
}

Bool HyperLinkCustomGui::GetLinkString(String* pStrLink, String *pStrText)
{
	HyperLinkStaticLib *lib = CheckPrefsLib(LIBOFFSET(HyperLinkStaticLib, GetLinkString));
	if (!lib || !lib->GetLinkString) return false;

	return (((iHyperLinkCustomGui*)this)->*lib->GetLinkString)(pStrLink, pStrText);
}

Bool HyperLinkCustomGui::SetLinkStringThreaded(const String* pStrLink, const String *pStrText)
{
	HyperLinkStaticLib *lib = CheckPrefsLib(LIBOFFSET(HyperLinkStaticLib, SetLinkStringThreaded));
	if (!lib || !lib->SetLinkStringThreaded) return false;

	return (((iHyperLinkCustomGui*)this)->*lib->SetLinkStringThreaded)(pStrLink, pStrText);
}


void HyperLinkData::SetStrings(const String* pStrLink, const String* pStrText)
{
	HyperLinkStaticLib *lib = CheckPrefsLib(LIBOFFSET(HyperLinkStaticLib, SetStrings));
	if (!lib || !lib->SetStrings) return;

	(((iHyperLinkData*)this)->*lib->SetStrings)(pStrLink, pStrText);
}

void HyperLinkData::GetStrings(String* pStrLink, String* pStrText)
{
	HyperLinkStaticLib *lib = CheckPrefsLib(LIBOFFSET(HyperLinkStaticLib, GetStrings));
	if (!lib || !lib->GetStrings) return;

	(((iHyperLinkData*)this)->*lib->GetStrings)(pStrLink, pStrText);
}

