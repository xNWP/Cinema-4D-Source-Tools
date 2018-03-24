#ifndef CUSTOMGUI_LAYERSET_H__
#define CUSTOMGUI_LAYERSET_H__

#include "c4d_library.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_customdatatype.h"
#include "customgui_base.h"

#ifdef __API_INTERN__
	#include "ge_string.h"
	#include "ge_file.h"
#else
	#include "c4d_string.h"
	#include "c4d_file.h"
#endif

#define CUSTOMGUI_LAYERSET			200000043
#define CUSTOMDATATYPE_LAYERSET 200000044

#ifndef __API_INTERN__
class LayerSet : public CustomDataType
{
	private:
		LayerSet();
		~LayerSet();

	public:

		Bool Content() const { return C4DOS.Pa->LSL_Content(this); }
		Bool IsLayerEnabled(const String &name) const { return C4DOS.Pa->LSL_IsLayerEnabled(this, name); }
		Bool FindLayerSet(const String &name) const { return C4DOS.Pa->LSL_FindLayerSet(this, name); }

		String GetName() const { return C4DOS.Pa->LSL_GetName(this); }

		LAYERSETMODE GetMode() const { return C4DOS.Pa->LSL_GetMode(this); }
		void SetMode(LAYERSETMODE t_mode) { C4DOS.Pa->LSL_SetMode(this, t_mode); }

		void RemoveLayer(const String &layer) { C4DOS.Pa->LSL_RemoveLayer(this, layer); }
		void AddLayer(const String &layer) { C4DOS.Pa->LSL_AddLayer(this, layer); }
		void FlushLayers() { C4DOS.Pa->LSL_FlushLayers(this); }

		void SetPreviewMode(Int32 s) { C4DOS.Pa->LSL_SetPreviewMode(this, s); }
		Int32 GetPreviewMode(void) { return C4DOS.Pa->LSL_GetPreviewMode(this); }

		const LayerSet& operator = (const LayerSet &layerset);
		Bool operator == (const LayerSet &layerset) const { return C4DOS.Pa->LSL_operator_cmp(this, layerset); }

		void CopyTo(LayerSet &dst) const { C4DOS.Pa->LSL_CopyTo(this, dst); }

		static LayerSet* Alloc() { return C4DOS.Pa->LSL_Alloc(); }
		static void Free(LayerSet *layerset) { C4DOS.Pa->LSL_Free(layerset); }
};

class LayerSetHelper
{
	private:
		LayerSetHelper();
		~LayerSetHelper();
	public:
		Bool Init(const Filename &fn, const LayerSet *selection) { return C4DOS.Pa->LSH_Init(this, fn, selection); }
		Bool EditLayerSet(const String &dialogtitle, LayerSet *layerset, LayerSet *layerseta) { return C4DOS.Pa->LSH_EditLayerSet(this, dialogtitle, layerset, layerseta); }
		Bool MergeLayerSet(const LayerSet &selection, BaseBitmap *bmp, Bool preview) { return C4DOS.Pa->LSH_MergeLayerSet(this, selection, bmp, preview); }

		static LayerSetHelper* Alloc() { return C4DOS.Pa->LSH_Alloc(); }
		static void Free(LayerSetHelper *lsh) { C4DOS.Pa->LSH_Free(lsh); }
};

inline Bool CalculateLockListResolution(BaseDocument *doc, const Filename &filename, Int32 *xres, Int32 *yres)
{
	return C4DOS.Pa->CLL_CalculateResolution(doc, filename, xres, yres);
}

inline Bool CalculateLockListFilename(BaseDocument *doc, Filename &fn, LayerSet *lsl)
{
	return C4DOS.Pa->CLL_CalculateFilename(doc, fn, lsl);
}
#endif

class LayerSetCustomGui : public BaseCustomGui<CUSTOMGUI_LAYERSET>
{
		LayerSetCustomGui();
		~LayerSetCustomGui();
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_DEF_
	class iLayerSetCustomGui
	{
	};
#else
	class iLayerSetCustomGui;
#endif

struct CustomGuiLayerSetLib : public BaseCustomGuiLib
{
};

#endif // CUSTOMGUI_LAYERSET_H__
