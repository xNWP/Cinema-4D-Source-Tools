/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef SCALELIN_H__
#define SCALELIN_H__

#include	"x4d_filter.h"

//----------------------------------------------------------------------------------------
// functions for growing a line
//----------------------------------------------------------------------------------------
extern void	grow_line_px1_8(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
														Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
														UInt32* src, UInt32* dst);

extern void	grow_line_px16(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
													 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
													 UInt16* src, UInt16* dst);

extern void	grow_line_px24(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
													 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
													 UChar* src, UChar* dst);

extern void	grow_line_px32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
													 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
													 UInt32* src, UInt32* dst);

extern void	grow_line_px48(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
													 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
													 PIX_W* src, PIX_W* dst);

extern void	grow_line_px64(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
													 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
													 UInt32* src, UInt32* dst);

extern void	grow_line_px96(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
													 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
													 PIX_F* src, PIX_F* dst);

extern void	grow_line_px128(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
														Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
														PIX_F* src, PIX_F* dst);

//----------------------------------------------------------------------------------------
// additional name definitions
//----------------------------------------------------------------------------------------
#define	grow_line_xRGB15 grow_line_px16
#define	grow_line_RGB24	 grow_line_px24
#define	grow_line_xRGB24 grow_line_px32

#define	grow_line_G8	 grow_line_px1_8
#define	grow_line_G16	 grow_line_px16
#define	grow_line_AG16 grow_line_px16
#define	grow_line_AG32 grow_line_px32

#define	grow_line_Lab24	 grow_line_px24
#define	grow_line_xLab24 grow_line_px32


//----------------------------------------------------------------------------------------
// functions for shrinking a line
//----------------------------------------------------------------------------------------
extern void	shrink_line_px1_8(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															UInt32* src, UInt32* dst);

extern void	shrink_line_A8(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
													 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
													 UChar* src, UChar* dst);

extern void	shrink_line_xABC15(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															 UInt16* src, UInt16* dst);

extern void	shrink_line_AB16(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
														 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
														 UInt16* src, UInt16* dst);

extern void	shrink_line_AB32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
														 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
														 UInt32* src, UInt32* dst);

extern void	shrink_line_AB64(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
														 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
														 PIX_F* src, PIX_F* dst);

extern void	shrink_line_A16(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
														Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
														PIX_W* src, PIX_W* dst);

extern void	shrink_line_A32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
														Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
														PIX_F* src, PIX_F* dst);

extern void	shrink_line_AG16(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
														 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
														 UInt16* src, UInt16* dst);

extern void	shrink_line_AG32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
														 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
														 UInt32* src, UInt32* dst);

extern void	shrink_line_AG64(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
														 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
														 PIX_F* src, PIX_F* dst);

extern void	shrink_line_ABC24(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															UChar* src, UChar* dst);

extern void	shrink_line_xABC24(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															 UInt32* src, UInt32* dst);

extern void	shrink_line_ABC48(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															PIX_W* src, PIX_W* dst);

extern void	shrink_line_xABC48(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															 UInt32* src, UInt32* dst);

extern void	shrink_line_ABC96(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															PIX_F* src, PIX_F* dst);

extern void	shrink_line_xABC96(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															 PIX_F* src, PIX_F* dst);

extern void	shrink_line_ABCD32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															 UInt32* src, UInt32* dst);

extern void	shrink_line_ABCD64(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															 UInt32* src, UInt32* dst);

extern void	shrink_line_ABCD128(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
																Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
																PIX_F* src, PIX_F* dst);

extern void	shrink_line_ARGB32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															 UInt32* src, UInt32* dst);

extern void	shrink_line_ARGB64(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
															 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
															 UInt32* src, UInt32* dst);

extern void	shrink_line_ARGB128(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
																Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
																PIX_F* src, PIX_F* dst);

//----------------------------------------------------------------------------------------
// additional name definitions
//----------------------------------------------------------------------------------------
#define	shrink_line_xRGB15 shrink_line_xABC15
#define	shrink_line_RGB24	 shrink_line_ABC24
#define	shrink_line_xRGB24 shrink_line_xABC24

#define	shrink_line_G8	shrink_line_A8
#define	shrink_line_G16	shrink_line_A16

#define	shrink_line_Lab24	 shrink_line_ABC24
#define	shrink_line_xLab24 shrink_line_xABC24

#endif // SCALELIN_H__
