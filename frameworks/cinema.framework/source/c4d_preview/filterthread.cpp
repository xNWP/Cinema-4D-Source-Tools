#include "filterthread.h"
#include "c4d_general.h"

FilterThread::FilterThread(void)
{
	bm = nullptr;
	src_rect = 0;
	dt = nullptr;
	apply_effect = nullptr;
	settings = nullptr;
	redraw = false;
	done = false;
	err	 = FILTER_OK;
}

//----------------------------------------------------------------------------------------
// Initialize parameters for the effect function
// Function result:		-
// bm:								bitmap reference
// apply_effect:			pointer to the effect function
// settings:					effect settings
// redraw:						flag for update of the document view
//----------------------------------------------------------------------------------------
void FilterThread::Init(BM_REF t_bm, const RECT32* _src_rect, BM_TILE* _dt, FT_APPLY_EFFECT* t_apply_effect, BM_FILTER_SETTINGS* t_settings, Bool t_redraw)
{
	apply_effect = t_apply_effect;
	bm = t_bm;

	if (_src_rect)
	{
		r = *_src_rect;	// copy the source rect (it is likely to be a local stack variable)
		src_rect = &r;
	}
	else
	{
		src_rect = 0;
	}
	dt = _dt;
	settings = t_settings;
	redraw = t_redraw;
}

//----------------------------------------------------------------------------------------
// overridden main function of the thread
// Function result:		-
//----------------------------------------------------------------------------------------
void FilterThread::Main(void)
{
	done = false;
	err	 = apply_effect(bm, src_rect, dt, settings, redraw, Get());
	done = true;
}

//----------------------------------------------------------------------------------------
// Return thread state
// Function result:		true: thread is done false: thread is still running
//----------------------------------------------------------------------------------------
Bool FilterThread::IsDone(void)
{
	return done;
}

//----------------------------------------------------------------------------------------
// Wait until the effect thread is ready
// Function result:		-
//----------------------------------------------------------------------------------------
void FilterThread::WaitforCompletion(void)
{
	GeShowMouse(MOUSE_BUSY);
	Wait(true);
	GeShowMouse(MOUSE_NORMAL);
}

Int32	FilterThread::GetErr(void)
{
	return err;
}
