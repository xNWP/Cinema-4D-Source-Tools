/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef MINIBLT_H__
#define MINIBLT_H__

#include	"x4d_filter.h"

//----------------------------------------------------------------------------------------
// interface function types
//----------------------------------------------------------------------------------------
typedef	void* BLT_MALLOC (Int32 size);
typedef	Int32	BLT_MFREE (void* addr);

typedef void* BLT_FUNC (struct BLT_PARAM* p,
												Int32 src_x1, Int32 src_y1, Int32 src_x2, Int32 src_y2,
												Int32 dst_x1, Int32 dst_y1, Int32 dst_x2, Int32 dst_y2);

typedef void BLT_LINE (struct BLT_PARAM* p);

//----------------------------------------------------------------------------------------
// interface structures
//----------------------------------------------------------------------------------------
struct BLT_MEM
{
	BLT_MALLOC* malloc;
	BLT_MFREE*	mfree;
};

struct BLT_PARAM
{
	// rects
	const RECT32* src_rect;
	const RECT32* dst_rect;

	// bitmaps
	BM_TILE	src;
	BM_TILE	dst;

	// misc.
	const BLT_MEM* bfn;
	Int32					 wr_mode;

	// variables for single line output
	Int32	 mid_cnt;
	UInt32 start_mask;
	UInt32 end_mask;
	void*	 src_start_addr;
	void*	 dst_start_addr;
	Int32	 src_offset;
	Int32	 dst_offset;
};

//----------------------------------------------------------------------------------------
// supported transfer modes
#define	T_LOGIC_COPY	0
#define	T_PREPARELINE	0x80000000L

// error codes
#define	BLT_OK						0
#define	BLT_MEM_ERR				-1
#define	BLT_PX_FORMAT_ERR	-2

//----------------------------------------------------------------------------------------
// functions
//----------------------------------------------------------------------------------------
extern Int32 blt_init(BLT_PARAM* p, BLT_MEM* bfn, Int32 mode);
extern void	blt_reset(BLT_PARAM* p, BLT_MEM* bfn);
extern BLT_LINE* bitblt(BLT_PARAM* p, Int32 src_x1, Int32 src_y1, Int32 dummy_x, Int32 dummy_y, Int32 dst_x1, Int32 dst_y1, Int32 dst_x2, Int32 dst_y2);
extern void	bltline_incdst(BLT_PARAM* p, BLT_LINE* fn);

#endif // MINIBLT_H__




