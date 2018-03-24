#include	"scaleblt.h"
#include	"scale.h"
#include	"mergelin.h"
#include	"scalelin.h"

//----------------------------------------------------------------------------------------
// private functions
//----------------------------------------------------------------------------------------
static void	scaleblt_clip(SCALE_PARAM* p, Int32 clip_xmin, Int32 clip_ymin, Int32 clip_xmax, Int32 clip_ymax);
static void	do_scale_blt(SCALE_PARAM* scale_p,
												 Int32 src_x1, Int32 src_y1, Int32 src_x2, Int32 src_y2,
												 Int32 dst_x1, Int32 dst_y1, Int32 dst_x2, Int32 dst_y2);
static Int32 scale_buf_alloc(SCALE_PARAM* p,
														 Int32 src_x1, Int32 src_x2,
														 Int32 dst_x1, Int32 dst_x2,
														 Int32 shrink_vertical, BM_TILE* bm);
static void	scale_buf_free(SCALE_PARAM* p, UInt32* scale_buf);

//----------------------------------------------------------------------------------------
// Scaling BitBlt
// Function result:		BLT_OK, BLT_MEM_ERR or BLT_PX_FORMAT_ERR
// bfn:								memory allocation
// in_src_bm:					source bitmap
// in_dst_bm:					destination bitmap
// src_rect:					source rectangle
// dst_rect:					destination rectangle
// clip_rect:					clipping rectangle (for clipping the destination)
//----------------------------------------------------------------------------------------
Int32	scale_blt(BLT_MEM* bfn,
								const BM_TILE* in_src_bm, const BM_TILE* in_dst_bm,
								const RECT32* src_rect, const RECT32* dst_rect,
								const RECT32* clip_rect)
{
#define	src_bm			 (scale_p.src_bm)
#define	scale_buf_bm (scale_p.blt_p.src)
#define	dst_bm			 (scale_p.blt_p.dst)
#define	sw					 (scale_p.sw)
#define	sh					 (scale_p.sh)
#define	dw					 (scale_p.dw)
#define	dh					 (scale_p.dh)
#define	merge_lines	 (scale_p.merge_lines)
#define	scale_line	 (scale_p.scale_line)

	SCALE_PARAM	scale_p;
	Int32				err;

	scale_p.bfn = bfn;

	src_bm = *in_src_bm;
	dst_bm = *in_dst_bm;

	scale_p.src_rect = src_rect;
	scale_p.dst_rect = dst_rect;
	scale_p.blt_p.dst_rect = dst_rect;

	sw = src_rect->x2 - 1 - src_rect->x1 + 1;	// error for step to the next destination pixel (= src width)
	sh = src_rect->y2 - 1 - src_rect->y1 + 1;	// error for step to the next destination line (= src height)

	dw = dst_rect->x2 - 1 - dst_rect->x1 + 1;	// error for step to the next source pixel (= dst width)
	dh = dst_rect->y2 - 1 - dst_rect->y1 + 1;	// error for step to the next source line (= dst height)

	scale_buf_bm = src_bm;
	merge_lines	 = (MERGE_LINES*)  0;

	if (sh > dh)	// shrink vertically?
	{
		Int32	used_bits;
		Int32	bits;

		bits = get_PX_BITS(scale_buf_bm.px_format);
		used_bits = get_PX_USED(scale_buf_bm.px_format);

		if ((scale_buf_bm.px_format & PX_PACKING) == PX_FLOAT)	// floating point components?
		{
			switch ((int) get_PX_CMPNTS(scale_buf_bm.px_format))	// choose the right merging routine
			{
				case	1:
				{
					if (bits == 32)
						merge_lines = (MERGE_LINES*) merge_lines_G32_G32;
					break;
				}
				case	2:
				{
					if (bits == 64)
					{
						merge_lines = (MERGE_LINES*) merge_lines_AB64_AB64;
						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							merge_lines = (MERGE_LINES*) merge_lines_AG64_AG64;
					}
					break;
				}
				case	3:
				{
					if (bits == 96)
						merge_lines = (MERGE_LINES*) merge_lines_RGB96_RGB96;
					else if ((bits == 128) && (used_bits == 96))
						merge_lines = (MERGE_LINES*) merge_lines_xRGB96_xRGB96;

					break;
				}
				case	4:
				{
					if (bits == 128)
					{
						merge_lines = (MERGE_LINES*) merge_lines_CMYK128_CMYK128;

						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							merge_lines = (MERGE_LINES*) merge_lines_ARGB128_ARGB128;
					}
					break;
				}
			}
		}
		else																										// integer pixel values
		{
			switch ((int) get_PX_CMPNTS(scale_buf_bm.px_format))	// choose the right merging routine
			{
				case	1:
				{
					if (bits < 8)
						merge_lines = (MERGE_LINES*) merge_lines_px1_8;
					else if (bits == 8)
						merge_lines = (MERGE_LINES*) merge_lines_G8_G8;
					else if (bits == 16)
						merge_lines = (MERGE_LINES*) merge_lines_G16_G16;

					break;
				}
				case	2:
				{
					if (bits == 16)
					{
						merge_lines = (MERGE_LINES*) merge_lines_AB16_AB16;
						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							merge_lines = (MERGE_LINES*) merge_lines_AG16_AG16;
					}
					else if (bits == 32)
					{
						merge_lines = (MERGE_LINES*) merge_lines_AB32_AB32;
						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							merge_lines = (MERGE_LINES*) merge_lines_AG32_AG32;
					}
					break;
				}
				case	3:
				{
					if (bits == 16)
						merge_lines = (MERGE_LINES*) merge_lines_xRGB15_xRGB15;
					else if (bits == 24)
						merge_lines = (MERGE_LINES*) merge_lines_RGB24_RGB24;
					else if ((bits == 32) && (used_bits == 24))
						merge_lines = (MERGE_LINES*) merge_lines_xRGB24_xRGB24;
					else if (bits == 48)
						merge_lines = (MERGE_LINES*) merge_lines_RGB48_RGB48;
					else if ((bits == 64) && (used_bits == 48))
						merge_lines = (MERGE_LINES*) merge_lines_xRGB48_xRGB48;

					break;
				}
				case	4:
				{
					if (bits == 32)
					{
						merge_lines = (MERGE_LINES*) merge_lines_CMYK32_CMYK32;

						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							merge_lines = (MERGE_LINES*) merge_lines_ARGB32_ARGB32;
					}
					else if (bits == 64)
					{
						merge_lines = (MERGE_LINES*) merge_lines_CMYK64_CMYK64;

						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							merge_lines = (MERGE_LINES*) merge_lines_ARGB64_ARGB64;
					}
					break;
				}
			}
		}
		if (merge_lines == (MERGE_LINES*) 0)
			return BLT_PX_FORMAT_ERR;
	}
	scale_line = (SCALE_LINE*) 0;
	if (sw > dw)	// shrink horizontally?
	{
		Int32	used_bits;
		Int32	bits;

		bits = get_PX_BITS(scale_buf_bm.px_format);
		used_bits = get_PX_USED(scale_buf_bm.px_format);

		if ((scale_buf_bm.px_format & PX_PACKING) == PX_FLOAT)	// floating point components?
		{
			switch ((int) get_PX_CMPNTS(scale_buf_bm.px_format))
			{
				case	1:
				{
					if (bits == 32)
						scale_line = (SCALE_LINE*) shrink_line_A32;

					break;
				}
				case	2:
				{
					if (bits == 64)
					{
						scale_line = (SCALE_LINE*) shrink_line_AB64;
						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							scale_line = (SCALE_LINE*) shrink_line_AG64;
					}
					break;
				}
				case	3:
				{
					if (bits == 96)
						scale_line = (SCALE_LINE*) shrink_line_ABC96;
					else if ((bits == 128) && (used_bits == 96))
						scale_line = (SCALE_LINE*) shrink_line_xABC96;

					break;
				}
				case	4:
				{
					if (bits == 128)
					{
						scale_line = (SCALE_LINE*) shrink_line_ABCD128;
						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							scale_line = (SCALE_LINE*) shrink_line_ARGB128;
					}
					break;
				}
			}
		}
		else	// integer pixel values
		{
			switch ((int) get_PX_CMPNTS(scale_buf_bm.px_format))
			{
				case	1:
				{
					if (bits < 8)
						scale_line = (SCALE_LINE*) shrink_line_px1_8;
					else if (bits == 8)
						scale_line = (SCALE_LINE*) shrink_line_A8;
					else if (bits == 16)
						scale_line = (SCALE_LINE*) shrink_line_A16;

					break;
				}
				case	2:
				{
					if (bits == 16)
					{
						scale_line = (SCALE_LINE*) shrink_line_AB16;
						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							scale_line = (SCALE_LINE*) shrink_line_AG16;
					}
					if (bits == 32)
					{
						scale_line = (SCALE_LINE*) shrink_line_AB32;
						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							scale_line = (SCALE_LINE*) shrink_line_AG32;
					}
					break;
				}
				case	3:
				{
					if (bits == 16)
						scale_line = (SCALE_LINE*) shrink_line_xABC15;
					else if (bits == 24)
						scale_line = (SCALE_LINE*) shrink_line_ABC24;
					else if ((bits == 32) && (used_bits == 24))
						scale_line = (SCALE_LINE*) shrink_line_xABC24;
					else if (bits == 48)
						scale_line = (SCALE_LINE*) shrink_line_ABC48;
					else if ((bits == 64) && (used_bits == 48))
						scale_line = (SCALE_LINE*) shrink_line_xABC48;

					break;
				}
				case	4:
				{
					if (bits == 32)
					{
						scale_line = (SCALE_LINE*) shrink_line_ABCD32;
						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							scale_line = (SCALE_LINE*) shrink_line_ARGB32;
					}
					if (bits == 64)
					{
						scale_line = (SCALE_LINE*) shrink_line_ABCD64;
						if (scale_buf_bm.color_space & CSPACE_ALPHA_FLAG)
							scale_line = (SCALE_LINE*) shrink_line_ARGB64;
					}
					break;
				}
			}
		}
	}
	else
	{
		switch ((int) get_PX_BITS(scale_buf_bm.px_format))
		{
			case	1:
			case	2:
			case	4:
			case	8:	scale_line = (SCALE_LINE*) grow_line_px1_8;	break;
			case	16:	scale_line = (SCALE_LINE*) grow_line_px16; break;
			case	24:	scale_line = (SCALE_LINE*) grow_line_px24; break;
			case	32:	scale_line = (SCALE_LINE*) grow_line_px32; break;
			case	48:	scale_line = (SCALE_LINE*) grow_line_px48; break;
			case	64:	scale_line = (SCALE_LINE*) grow_line_px64; break;
			case	96:	scale_line = (SCALE_LINE*) grow_line_px96; break;
			case	128:	scale_line = (SCALE_LINE*) grow_line_px128; break;
		}
	}

	if (scale_line)	// can we handle this pixel format?
	{
		if (scale_buf_alloc(&scale_p,
					src_rect->x1 - src_bm.xmin, src_rect->x2 - src_bm.xmin - 1,
					dst_rect->x1 - dst_bm.xmin, dst_rect->x2 - dst_bm.xmin - 1,
					sh > dh, (BM_TILE*) &scale_buf_bm))
		{
			if (blt_init(&scale_p.blt_p, bfn, T_LOGIC_COPY))
			{
				scaleblt_clip(&scale_p, clip_rect->x1, clip_rect->y1, clip_rect->x2, clip_rect->y2);
				err = BLT_OK;

				blt_reset(&scale_p.blt_p, bfn);
			}
			else
			{
				err = BLT_MEM_ERR;
			}

			scale_buf_free(&scale_p, (UInt32*) scale_buf_bm.addr);
		}
		else
		{
			err = BLT_MEM_ERR;
		}
	}
	else
	{
		err = BLT_PX_FORMAT_ERR;
	}

	return err;

	#undef	scale_line
	#undef	merge_lines
	#undef	dh
	#undef	dw
	#undef	sh
	#undef	sw
	#undef	dst_bm
	#undef	scale_buf_bm
	#undef	src_bm
}

//----------------------------------------------------------------------------------------
// Clip source and destination coordinates according to clip_xmin/ymin/xmax/ymax
// and call the blt function
// Function result:		-
// p:									context
// clip_xmin:					.
// clip_ymin:					.
// clip_xmax:					.
// clip_ymax:					clipping rectangle (continous coordinates)
//----------------------------------------------------------------------------------------
static void	scaleblt_clip(SCALE_PARAM* p, Int32 clip_xmin, Int32 clip_ymin, Int32 clip_xmax, Int32 clip_ymax)
{
	Int32	src_x1;
	Int32	src_y1;
	Int32	src_x2;
	Int32	src_y2;
	Int32	dst_x1;
	Int32	dst_y1;
	Int32	dst_x2;
	Int32	dst_y2;
	Int32	src_width;
	Int32	src_height;
	Int32	dst_width;
	Int32	dst_height;
	Int32	offset;
	Int32	xmin_round;
	Int32	ymin_round;
	Int32	xmax_round;
	Int32	ymax_round;

	src_x1 = p->src_rect->x1;
	src_y1 = p->src_rect->y1;
	src_x2 = p->src_rect->x2;
	src_y2 = p->src_rect->y2;

	dst_x1 = p->dst_rect->x1;
	dst_y1 = p->dst_rect->y1;
	dst_x2 = p->dst_rect->x2;
	dst_y2 = p->dst_rect->y2;

	src_width	 = src_x2 - src_x1;	// source width
	src_height = src_y2 - src_y1;
	dst_width	 = dst_x2 - dst_x1;
	dst_height = dst_y2 - dst_y1;

	src_x2--;	// discrete x2
	src_y2--;
	dst_x2--;
	dst_y2--;

	xmin_round = 0;
	ymin_round = 0;
	xmax_round = 0;
	ymax_round = 0;

	if (dst_width < src_width)
	{
		xmin_round = dst_width - 1;	// dst_dx
		xmax_round = src_width - 1;	// src_dx
	}
	if (dst_height < src_height)
	{
		ymin_round = dst_height - 1;	// dst_dy
		ymax_round = src_height - 1;	// src_dy
	}

	// clip dst_x2 and dst_y2 before dst_x1 and dst_y1
	// because the unclipped src_x1, src_y1, dst_x1 and
	// dst_y1 are needed

	if (dst_x2 >= clip_xmax)
	{
		offset = clip_xmax - 1 - dst_x1;
		if (offset < 0)						// not visible?
			return;
		offset *= src_width;			// ###NOTE: 64 bits are necessary if the bitmap width exceeds 32K pixels
		offset += xmax_round;			// shrinking: xmax_round = src_dx else: xmax_round = 0
		src_x2	= src_x1 + (offset / dst_width);
		dst_x2	= clip_xmax - 1;	// discrete coordinate
	}

	if (dst_y2 >= clip_ymax)
	{
		offset = clip_ymax - 1 - dst_y1;
		if (offset < 0)				// not visible?
			return;
		offset *= src_height;	// ###NOTE: 64 bits are necessary if the bitmap height exceeds 32K pixels
		offset += ymax_round;
		src_y2	= src_y1 + (offset / dst_height);
		dst_y2	= clip_ymax - 1;
	}

	if (dst_x1 < clip_xmin)
	{
		offset	= clip_xmin - dst_x1;
		offset *= src_width;	// ###NOTE: 64 bits are necessary if the bitmap width exceeds 32K pixels
		offset += xmin_round;
		src_x1 += offset / dst_width;
		dst_x1	= clip_xmin;
	}

	if (dst_y1 < clip_ymin)
	{
		offset	= clip_ymin - dst_y1;
		offset *= src_height;	// ###NOTE: 64 bits are necessary if the bitmap height exceeds 32K pixels
		offset += ymin_round;
		src_y1 += offset / dst_height;
		dst_y1	= clip_ymin;
	}

	if (dst_x1 > dst_x2)	// not visible?
		return;
	if (dst_y1 > dst_y2)
		return;

	do_scale_blt(p, src_x1, src_y1, src_x2, src_y2, dst_x1, dst_y1, dst_x2, dst_y2);
}

//----------------------------------------------------------------------------------------
// Scaling BitBlt, vertical action
// Function result:		-
// scale_p:						context
// src_...						clipped discrete source coordinates
// dst_...						clipped discrete destination coordinates
//----------------------------------------------------------------------------------------
static void	do_scale_blt(SCALE_PARAM* scale_p,
												 Int32 src_x1, Int32 src_y1, Int32 src_x2, Int32 src_y2,
												 Int32 dst_x1, Int32 dst_y1, Int32 dst_x2, Int32 dst_y2)
{
#define	src_bm			 (&scale_p->src_bm)
#define	scale_buf_bm (&scale_p->blt_p.src)
#define	dst_bm			 (&scale_p->blt_p.dst)
#define	merge_lines	 (scale_p->merge_lines)
#define	scale_line	 (scale_p->scale_line)

	BLT_LINE* blt_line;
	UInt32*		src;
	Int32			src_bit_offset;
	Int32			scale_bit_offset;
	Int32			merge_bit_offset;
	Int32			offset;

	Int32	hcnt;
	Int32	he;
	Int32	sw;
	Int32	dw;

	Int32	vcnt;
	Int32	ve;
	Int32	sh;
	Int32	dh;

	(void) src_y2;		// not used (because of sh)

	sw = scale_p->sw;	// error for step to the next destination pixel (= src width)
	sh = scale_p->sh;	// error for step to the next destination line (= src height)

	dw = scale_p->dw;	// error for step to the next source pixel (= dst width)
	dh = scale_p->dh;	// error for step to the next source line (= dst height)

	hcnt = dst_x2 - dst_x1;
	vcnt = dst_y2 - dst_y1;

	src_bit_offset = (src_x1 - src_bm->xmin) * get_PX_BITS(src_bm->px_format);
	scale_bit_offset	= (dst_x1 - dst_bm->xmin) * get_PX_BITS(scale_buf_bm->px_format);
	merge_bit_offset	= (src_x1 - src_bm->xmin) * get_PX_BITS(scale_buf_bm->px_format);
	merge_bit_offset &= 31;
	scale_bit_offset &= 31;

	scale_p->blt_p.wr_mode |= T_PREPARELINE;	// prepare blitting single lines
	blt_line = bitblt(&scale_p->blt_p,
							 scale_bit_offset * get_PX_BITS(scale_buf_bm->px_format), 0, 0, 0,
							 dst_x1, dst_y1, dst_x2, dst_y2);

	src	 = (UInt32*)((UChar*) src_bm->addr + (src_bm->width * (src_y1 - src_bm->ymin)));
	src += src_bit_offset >> 5;
	src_bit_offset &= 31;

	// get start value for horizontal scaling
	he = 0;

	offset = src_x1 - scale_p->src_rect->x1;
	if (offset)						// is x source clipped?
		he += offset * dw;	// adjust discriminator

	offset = dst_x1 - scale_p->dst_rect->x1;
	if (offset)						// is x destination clipped?
		he -= offset * sw;	// adjust discriminator

	if (sw > dw)					// shrink?
	{
		he -= sw;
	}
	else	// grow
	{
		he	= -he;
		he -= dw;
	}

	// get start value for vertical scaling
	ve = 0;

	offset = src_y1 - scale_p->src_rect->y1;
	if (offset)						// is y source clipped?
		ve += offset * dh;	// adjust discriminator

	offset = dst_y1 - scale_p->dst_rect->y1;
	if (offset)						// is y destination clipped?
		ve -= offset * sh;	// adjust discriminator

	if (sh > dh)					// shrink?
	{
		Int32	src_cnt;
		Int32	buf_cnt;
		Int32	src_line_offset;

		src_cnt	 = (((src_x2 + 1) * (Int32) get_PX_BITS(src_bm->px_format)) + 31) >> 5;
		src_cnt -= (src_x1 * (Int32) get_PX_BITS(src_bm->px_format)) >> 5;
		src_cnt -= 1;	// # of source words - 1 between src_x1 and src_x2

		buf_cnt	 = (((src_x2 + 1) * (Int32) get_PX_BITS(scale_buf_bm->px_format)) + 31) >> 5;
		buf_cnt -= (src_x1 * (Int32) get_PX_BITS(scale_buf_bm->px_format)) >> 5;
		buf_cnt -= 1;

		src_line_offset = src_bm->width - ((src_cnt + 1) << 2);

		ve -= sh;

		while (vcnt >= 0)
		{
			Int32		line_cnt;
			UInt32* merge_addr;

			line_cnt = 0;

			while (ve < 0)	// determine # of source lines
			{
				line_cnt++;
				ve += dh;
			}

			merge_addr = merge_lines(line_cnt - 1, buf_cnt,
										 get_PX_BITS(src_bm->px_format), src_bit_offset, src_line_offset, scale_buf_bm->width,
										 src, (UInt32*) scale_buf_bm->addr);

			scale_line(he, sw, dw, hcnt,
				get_PX_BITS(scale_buf_bm->px_format), merge_bit_offset, scale_bit_offset,
				merge_addr, (UInt32*) scale_buf_bm->addr);

			bltline_incdst(&scale_p->blt_p, blt_line);	// output of the scaled line

			src = (UInt32*) ((UChar*) src + (line_cnt * src_bm->width));

			ve -= sh;	// adjust discriminator
			vcnt--;
		}
	}
	else
	{
		ve	= -ve;
		ve -= dh;

		scale_line(he, sw, dw, hcnt,
			get_PX_BITS(src_bm->px_format), src_bit_offset, scale_bit_offset,
			src, (UInt32*) scale_buf_bm->addr);

		while (vcnt >= 0)
		{
			bltline_incdst(&scale_p->blt_p, blt_line);	// output of the scaled line

			ve += sh;																		// adjust discriminator

			if (ve >= 0)																// next source line?
			{
				src = (UInt32*) ((UChar*) src + src_bm->width);
				ve -= dh;	// adjust discriminator

				if (vcnt > 0)
				{
					scale_line(he, sw, dw, hcnt,
						get_PX_BITS(src_bm->px_format), src_bit_offset, scale_bit_offset,
						src, (UInt32*) scale_buf_bm->addr);
				}
			}
			vcnt--;
		}
	}

	#undef	scale_line
	#undef	merge_lines
	#undef	dst_bm
	#undef	scale_buf_bm
	#undef	src_bm
}

//----------------------------------------------------------------------------------------
// Allocate a buffer for merge_lines() and scale_line()
// Function result:		true/false
// p:									context
// src_x1:						left discrete x coordinate (source)
// src_x2:						right discrete x coordinate (source)
// dst_x1:						left discrete x coordinate (destination)
// dst_x2:						right discrete x coordinate (destination)
// shrink_vertical:		true: additional space for merging the lines is needed
// bm:								structure for the buffer
//----------------------------------------------------------------------------------------
static Int32 scale_buf_alloc(SCALE_PARAM* p,
														 Int32 src_x1, Int32 src_x2,
														 Int32 dst_x1, Int32 dst_x2,
														 Int32 shrink_vertical, BM_TILE* bm)
{
	Int32	len;

	len	 = (((dst_x2 + 1) * get_PX_BITS(bm->px_format)) + 31) >> 5;
	len -= ((dst_x1 * get_PX_BITS(bm->px_format)) >> 5);

	if (shrink_vertical)	// merge_lines?
	{
		Int32	src_cnt;

		src_cnt = (src_x2 + 32 - (src_x1 & ~31)) & ~31;
		len = 4 * src_cnt;	// for up to four components width 8 bit per component (merging needs 16 or 32 bits per component, so max. 4 bytes per component)
		if (bm->color_space & CSPACE_ALPHA_FLAG)
			len += len;				// with alpha we need 32 bit for merging
	}

	len <<= 2;	// length in bytes

	bm->addr	= (UChar*) p->bfn->malloc(len);
	bm->width = len;
	bm->xmin	= 0;
	bm->ymin	= 0;
	bm->xmax	= (len << 3) / get_PX_BITS(bm->px_format);
	bm->ymax	= 1;

	return bm->addr != 0;
}

//----------------------------------------------------------------------------------------
// Free scale buffer
// Function result:		-
// p:									context
// scale_buf:					pointer to the buffer
//----------------------------------------------------------------------------------------
static void	scale_buf_free(SCALE_PARAM* p, UInt32* scale_buf)
{
	if (scale_buf)
		p->bfn->mfree(scale_buf);
}
