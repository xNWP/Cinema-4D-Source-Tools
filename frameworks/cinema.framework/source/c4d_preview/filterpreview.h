/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef FILTERPREVIEW_H__
#define FILTERPREVIEW_H__

#include "filterthread.h"

//----------------------------------------------------------------------------------------
// PreviewKlasse (UserArea)
//----------------------------------------------------------------------------------------
class PreviewBmp : public GeUserArea
{
	BM_FILTER_SETTINGS*		settings;
	BM_REF								bm;
	AutoAlloc<BaseBitmap>	bmp;
	Bool									bmp_valid;
	FT_APPLY_EFFECT*			apply_effect;
	Bool									real_time;	// false: use preview thread true: immediate redraw of preview
	Int32									down_scale;	// index of the preview scaling factor
	Int32									offset_x;		// offset is relative to the center of the selection
	Int32									offset_y;
	Int32									last_x;			// last offset the preview was displayed with
	Int32									last_y;

	FilterThread					preview_thread;
	FilterThread					document_thread;
	Bool									document_preview;
	Bool									changed_settings;

	void ClipOffsets(RECT32* r);

	friend class PreviewGroup;
	friend Int32 preview_effect(BM_REF bm, const RECT32* src_rect, BM_TILE* dt, PreviewBmp* pv, Bool update_view, BaseThread* thread);

public:
	PreviewBmp();
	~PreviewBmp();
	virtual Bool GetMinSize   (Int32& w, Int32& h);
	virtual void DrawMsg      (Int32 x1, Int32 y1, Int32 x2, Int32 y2, const BaseContainer& msg);
	virtual Bool InputEvent   (const BaseContainer& msg);
	virtual Bool InitValues   (void);
	virtual Int32	Message      (const BaseContainer& msg, BaseContainer& result);

	void SetBitmap(BM_REF bm, FT_APPLY_EFFECT* apply_effect, BM_FILTER_SETTINGS* settings, Bool redraw = true);
	Bool UpdateBitmap(Bool do_effect);
	void SetOffset(Int32 x, Int32 y, Bool do_effect, Bool scale_xy = true);
	void SetDragEffect(Bool showeffect);
	Int32	Shrink(Bool do_effect, Bool redraw);
	Int32	Grow(Bool do_effect, Bool redraw);
	Int32	GetScale(void);
	void SetDocumentPreview(Bool document_preview);
};

class PreviewGroup
{
private:
	GeDialog*	 dlg;
	Int32			 src_preview_id;
	Int32			 dst_preview_id;
	Int32			 zoom_in_id;
	Int32			 zoom_out_id;
	Int32			 zoom_percent_id;
	Bool			 real_time;

	PreviewBmp src_preview;
	PreviewBmp dst_preview;

	void AddPreview(GeDialog* dlg, Int32 w, Int32 h, PreviewBmp& preview, Int32 preview_id);

public:
	PreviewGroup();
	~PreviewGroup();

	void Create(GeDialog* _dlg, Int32 group_id);
	void SetSource(BM_REF bm, BM_FILTER_SETTINGS* settings = 0, Bool redraw = true);
	void SetDestination(BM_REF bm, FT_APPLY_EFFECT* apply_effect, BM_FILTER_SETTINGS* settings, Bool redraw = true, Bool document_preview = false);
	void UpdateSource(Bool do_effect = true);
	void UpdateDestination(Bool do_effect = true);
	void SetDocumentPreview(Bool document_preview);
	void ChangedSettings(void);
	void FinishDocumentUpdate(void);

	Bool Command(Int32 id, const BaseContainer& msg);

	void ZoomIn(void);
	void ZoomOut(void);
	void Update(void);
};

Int32	preview_effect(BM_REF bm, const RECT32* src_rect, BM_TILE* dt, PreviewBmp* pv, Bool update_view, BaseThread* thread);

#endif // FILTERPREVIEW_H__
