#include	"miniblt.h"

//----------------------------------------------------------------------------------------
// private functions
//----------------------------------------------------------------------------------------
static void	bitblt_line(BLT_PARAM* p);
static void	blt_copy(BLT_PARAM* p, UInt32* src, Int32 src_offset, UInt32* dst, Int32 dst_offset,
										 Int32 dy, Int32 mid_cnt, UInt32 sm, UInt32 em);

//----------------------------------------------------------------------------------------
// Prepare blt function
//----------------------------------------------------------------------------------------
Int32	blt_init(BLT_PARAM* p, BLT_MEM* bfn, Int32 mode)
{
	(void)	bfn;

	p->wr_mode = mode;
	return 1;
}

//----------------------------------------------------------------------------------------
// Reset blt function, free all previously allocated memory
//----------------------------------------------------------------------------------------
void blt_reset(BLT_PARAM* p, BLT_MEM* bfn)
{
	(void)	p;
	(void)	bfn;
}

//----------------------------------------------------------------------------------------
// Copy one line and go to the next destination line
//----------------------------------------------------------------------------------------
void bltline_incdst(BLT_PARAM* p, BLT_LINE* fn)
{
	fn(p);

	p->dst_start_addr = (void*) ((UChar*) p->dst_start_addr + p->dst.width);
}

//----------------------------------------------------------------------------------------
// Simplified bit block transfer
// Function result:		Function pointer (T_PREPARELINE set) or zero
// p:									blt context
// src_x1:						x1 source
// src_y1:						y1 source
// dummy_x:						dummy
// dummy_y:						dummy
// dst_x1:						x1 destination
// dst_y1:						y1 destination
// dst_x2:						x2 destination
// dst_y2:						y2 destination
//----------------------------------------------------------------------------------------
BLT_LINE* bitblt(BLT_PARAM* p, Int32 src_x1, Int32 src_y1, Int32 dummy_x, Int32 dummy_y, Int32 dst_x1, Int32 dst_y1, Int32 dst_x2, Int32 dst_y2)
{
	UChar* src;
	UChar* dst;
	Int32	 src_offset;
	Int32	 dst_offset;
	Int32	 mid_cnt;
	Int32	 dy;
	UInt32 start_mask;
	UInt32 end_mask;
	Int32	 shifts;

	src_x1 -= p->src.xmin;	// take coordinate offset of the source into account
	src_y1 -= p->src.ymin;

	dst_x1 -= p->dst.xmin;	// take coordinate offset of the destination into account
	dst_y1 -= p->dst.ymin;
	dst_x2 -= p->dst.xmin;
	dst_y2 -= p->dst.ymin;

	dy = dst_y2 - dst_y1;

	src_x1 *= get_PX_BITS(p->src.px_format);
	dst_x1 *= get_PX_BITS(p->dst.px_format);
	dst_x2 *= get_PX_BITS(p->dst.px_format);
	dst_x2 += get_PX_BITS(p->dst.px_format) - 1;

	start_mask = 0xffffffffUL >> (dst_x1 & 31);	// start mask
	end_mask = UInt32(0xffffffffUL << (~dst_x2 & 31));	// end mask

#if GE_LITTLE_ENDIAN													// swap the masks on little endian machines
	start_mask = REVERSEu32(start_mask);
	end_mask = REVERSEu32(end_mask);
#endif

	src = (UChar*) p->src.addr;
	dst = (UChar*) p->dst.addr;
	src_offset = p->src.width;
	dst_offset = p->dst.width;

	shifts = (dst_x1 & 31) - (src_x1 & 31);	// # of shifts to the right [blt_copy() does not support bitwise shifting]

	dst_x1 >>= 5;
	dst_x2 >>= 5;

	dst += dst_y1 * p->dst.width;
	dst += dst_x1 << 2;

	mid_cnt = dst_x2 - dst_x1;	// # of destination words - 1

	src_x1 >>= 5;
	src += src_y1 * p->src.width;
	src += src_x1 << 2;

	src_offset -= mid_cnt << 2;
	dst_offset -= mid_cnt << 2;

	if (mid_cnt == 0)
	{
		start_mask &= end_mask;	// combine masks
		end_mask = 0;
		src_offset -= 4;				// adjust offsets
		dst_offset -= 4;
	}

	mid_cnt -= 2;

	if ((shifts & 7) == 0)	// use mis-alignment instead of shifting?
	{
		src -= shifts >> 3;
		shifts = 0;
	}
	else	// this case is not supported
	{
		return 0;
	}

	if (p->wr_mode & T_PREPARELINE)	// prepare output for single lines?
	{
		p->src_start_addr = src;			// save internal params
		p->dst_start_addr = dst;
		p->src_offset = src_offset;
		p->dst_offset = dst_offset;
		p->mid_cnt = mid_cnt;
		p->start_mask = start_mask;
		p->end_mask = end_mask;

		return (BLT_LINE*) bitblt_line;
	}
	else
	{
		blt_copy(p, (UInt32*) src, src_offset, (UInt32*) dst, dst_offset, dy, mid_cnt, start_mask, end_mask);
		return 0;
	}
}

//----------------------------------------------------------------------------------------
// Copy one line
//----------------------------------------------------------------------------------------
static void	bitblt_line(BLT_PARAM* p)
{
	blt_copy(p, (UInt32*) p->src_start_addr, p->src_offset, (UInt32*) p->dst_start_addr, p->dst_offset,
		0, p->mid_cnt, p->start_mask, p->end_mask);
}

//----------------------------------------------------------------------------------------
// Copy Bitmap (post increment)
// Function result:		Function pointer (T_PREPARELINE set) or zero
// p:									blt context
// src:								pointer to the first source word
// src_offset:				distance to the next source line in bytes
// src:								pointer to the first destination word
// src_offset:				distance to the next destination line in bytes
// dy:								# of lines - 1
// mid_cnt:						# of main loops - 1
// start_mask:				mask for the start word (bits set will be copied)
// start_mask:				mask for the end word (bits set will be copied)
//----------------------------------------------------------------------------------------
static void	blt_copy(BLT_PARAM* p, UInt32* src, Int32 src_offset, UInt32* dst, Int32 dst_offset,
										 Int32 dy, Int32 mid_cnt, UInt32 sm, UInt32 em)
{
	Int32	 i;
	UInt32 src_word;

	while (dy >= 0)
	{
		src_word = *src++;

		// intel bug
		// *dst++ = ( (~src_word) & sm ) ^ ( (*dst) | sm );
		*dst = (src_word & sm) | (*dst & (~sm));
		dst++;

		for (i = mid_cnt; i >= 0; i--)
			*dst++ = *src++;

		if (mid_cnt > -2)
		{
			src_word = *src;

			// intel bug
			// *dst = ( ~src_word & em ) ^ ( *dst | em );
			*dst = (src_word & em) | (*dst & (~em));
		}

		src = (UInt32*) ((UChar*) src + src_offset);
		dst = (UInt32*) ((UChar*) dst + dst_offset);

		dy--;
	}
}
