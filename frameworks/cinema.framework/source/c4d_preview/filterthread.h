/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef FILTERTHREAD_H__
#define FILTERTHREAD_H__

#include "c4d_thread.h"
#include "x4d_filter.h"

struct BM_FILTER_SETTINGS
{
};

typedef	Int32	FT_APPLY_EFFECT (BM_REF bm, const RECT32 * src_rect, BM_TILE * dt, BM_FILTER_SETTINGS * settings, Bool update_view, class BaseThread * thread);

class FilterThread : public C4DThread
{
	BM_REF							bm;
	BM_TILE*						dt;
	const RECT32*				src_rect;
	RECT32							r;
	FT_APPLY_EFFECT*		apply_effect;
	BM_FILTER_SETTINGS* settings;
	Bool								redraw;
	Int32								err;
	volatile Bool				done;

public:
	FilterThread();
	void Main(void);
	virtual const Char* GetThreadName() { return "FilterThread"; }
	void Init(BM_REF bm, const RECT32* src_rect, BM_TILE* dt, FT_APPLY_EFFECT* apply_effect, BM_FILTER_SETTINGS* settings, Bool redraw);
	Int32	GetErr(void);
	Bool IsDone(void);
	void WaitforCompletion(void);
};

#endif // FILTERTHREAD_H__
