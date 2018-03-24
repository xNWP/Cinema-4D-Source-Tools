#include "c4d_general.h"
#include "c4d_shader.h"
#include "c4d_memory.h"
#include "c4d_resource.h"
#include "c4d_commandplugin.h"
#include "c4d_plugin.h"
#include "c4d_basebitmap.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"

#include "x4d_filter.h"
#include "c4d_bitmapfilter.h"
#include	"filter_prefs.h"

Bool BfpGetRealTimeFlag(void)
{
	return true;
}

Bool BfpGetDocumentPreviewFlag(void)
{
	BaseContainer	prefs;

	prefs = GetGlobalFilterPrefs(BF_PREFS_GLOBAL);
	return (Bool) prefs.GetInt32(BF_PREFS_DOCUMENT_PREVIEW, BF_PREFS_DOCUMENT_PREVIEW_DFLT);
}

void BfpSetDocumentPreviewFlag(Bool document_preview)
{
	BaseContainer	prefs;

	prefs = GetGlobalFilterPrefs(BF_PREFS_GLOBAL);
	prefs.SetInt32(BF_PREFS_DOCUMENT_PREVIEW, document_preview);
	SetGlobalFilterPrefs(BF_PREFS_GLOBAL, prefs);
}

Bool BfpGetTextureModeFlag(void)
{
	BaseContainer	prefs;

	prefs = GetGlobalFilterPrefs(BF_PREFS_GLOBAL);
	return (Bool) prefs.GetInt32(BF_PREFS_TILE_FLAGS, BF_PREFS_TILE_FLAGS_DFLT);
}

void BfpSetTextureModeFlag(Bool texture_mode)
{
	BaseContainer	prefs;

	prefs = GetGlobalFilterPrefs(BF_PREFS_GLOBAL);
	prefs.SetInt32(BF_PREFS_TILE_FLAGS, texture_mode);
	SetGlobalFilterPrefs(BF_PREFS_GLOBAL, prefs);
}
