/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef SCALE_H__
#define SCALE_H__

#include	"miniblt.h"

typedef UInt32* MERGE_LINES (Int32 line_cnt, Int32 dst_cnt,
														 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
														 UInt32 * src, UInt32 * dst);

typedef void SCALE_LINE (Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												 UInt32 * src, UInt32 * dst);


struct SCALE_PARAM
{
	const BLT_MEM* bfn;
	const RECT32*	 src_rect;
	const RECT32*	 dst_rect;

	Int32					 sw;	// soruce width
	Int32					 sh;	// source height

	Int32					 dw;	// destination width
	Int32					 dh;	// destination height

	BM_TILE				 src_bm;

	MERGE_LINES*	 merge_lines;
	SCALE_LINE*		 scale_line;
	BLT_PARAM			 blt_p;	// bitblt context
};

#endif // SCALE_H__
