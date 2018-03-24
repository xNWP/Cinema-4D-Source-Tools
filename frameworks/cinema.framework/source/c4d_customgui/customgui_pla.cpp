#include "customgui_pla.h"
#include "c4d_string.h"
#include "c4d_gui.h"
#include "lib_ca.h"

static PLALib *lib_pla = nullptr;

static PLALib *CheckPrefsLib(Int32 offset)
{
	return (PLALib*)CheckLib(CUSTOMDATATYPE_PLA, offset, (C4DLibrary**)&lib_pla);
}

void PLAData::GetVariableTags(PointTag *&ptag, TangentTag *&htag)
{
	PLALib *lib = CheckPrefsLib(LIBOFFSET(PLALib, GetVariableTags)); if (!lib || !lib->GetVariableTags) return;

	(((iPLAData*)this)->*lib->GetVariableTags)(ptag, htag);
}

GeListHead*	mttag_data::GetLayerHead(void)
{
	PLALib *lib = CheckPrefsLib(LIBOFFSET(PLALib, xGetLayerHead)); if (!lib || !lib->xGetLayerHead) return nullptr;

	return (*lib->xGetLayerHead)((MT_TagData*)this);
}

Bool mtlayer_data::IsAnimationLayer(void)
{
	PLALib *lib = CheckPrefsLib(LIBOFFSET(PLALib, xIsAnimationLayer)); if (!lib || !lib->xIsAnimationLayer) return false;

	return (*lib->xIsAnimationLayer)((MT_LayerData*)this);
}

GeListHead*	mtlayer_data::GetAnimationHead(void)
{
	PLALib *lib = CheckPrefsLib(LIBOFFSET(PLALib, xGetAnimationHead)); if (!lib || !lib->xGetAnimationHead) return nullptr;

	return (*lib->xGetAnimationHead)((MT_LayerData*)this);
}

GeListHead*	mtlayer_data::GetClipHead(void)
{
	PLALib *lib = CheckPrefsLib(LIBOFFSET(PLALib, xGetClipHead)); if (!lib || !lib->xGetClipHead) return nullptr;

	return (*lib->xGetClipHead)((MT_LayerData*)this);
}

Bool AnimateNLA(BaseDocument *doc, BaseObject *op, const BaseTime &time, ANIMATEFLAGS flags)
{
	PLALib *lib = CheckPrefsLib(LIBOFFSET(PLALib, xAnimateNLA)); if (!lib || !lib->xAnimateNLA) return false;

	return (*lib->xAnimateNLA)(doc, op, time, flags);
}

void mtlayer_data::SetQuaternionInterpolation(Bool quatInterp, Bool bUndo)
{
	PLALib *lib = CheckPrefsLib(LIBOFFSET(PLALib, xSetQuaternionInterpolation)); if (!lib || !lib->xSetQuaternionInterpolation) return;

	return (*lib->xSetQuaternionInterpolation)((MT_LayerData*)this, quatInterp, bUndo);
}

Bool mtlayer_data::IsQuaternionInterpolation()
{
	PLALib *lib = CheckPrefsLib(LIBOFFSET(PLALib, xIsQuaternionInterpolation)); if (!lib || !lib->xIsQuaternionInterpolation) return false;

	return (*lib->xIsQuaternionInterpolation)((MT_LayerData*)this);
}

