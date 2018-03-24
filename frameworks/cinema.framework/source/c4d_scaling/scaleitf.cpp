#include "c4d_general.h"
#include "c4d_shader.h"
#include "c4d_memory.h"
#include "c4d_resource.h"
#include "c4d_commandplugin.h"
#include "c4d_plugin.h"
#include "c4d_basebitmap.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"

#include	"scaleitf.h"
#include	"scaleblt.h"

static void* blt_malloc(Int32 size);
static Int32 blt_mfree(void* addr);

BLT_MEM	blt_context =
{
	blt_malloc,
	blt_mfree
};

Int32	scale_bm(const BM_TILE* src_bm, const BM_TILE* dst_bm, const RECT32* src_rect, const RECT32* dst_rect, const RECT32* clip_rect)
{
	if (clip_rect == 0)
		clip_rect = (const RECT32*) &dst_bm->xmin;	// clip to the destination tile

	scale_blt(&blt_context,
		src_bm, dst_bm,
		src_rect, dst_rect,
		clip_rect);

	return FILTER_OK;
}

static void* blt_malloc(Int32 size)
{
	UChar* m = nullptr;
	if (size > 0)
	{
		iferr (m = NewMemClear(UChar, size))
			DebugStop();
	}
	return m;
}

static Int32 blt_mfree(void* addr)
{
	DeleteMem(addr);
	return 0;
}


