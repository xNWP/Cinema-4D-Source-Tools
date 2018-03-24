/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef MERGELIN_H__
#define MERGELIN_H__

#include	"x4d_filter.h"

//----------------------------------------------------------------------------------------
// Merging several lines
//----------------------------------------------------------------------------------------
extern UInt32* merge_lines_px1_8(Int32 line_cnt, Int32 dst_cnt,
																 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																 UInt32* src, UInt32* dst);

extern UInt32* merge_lines_G8_G8(Int32 line_cnt, Int32 dst_cnt,
																 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																 UChar* src, UChar* dst);

extern UInt32* merge_lines_G16_G16(Int32 line_cnt, Int32 dst_cnt,
																	 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	 PIX_W* src, PIX_W* dst);

extern PIX_F* merge_lines_G32_G32(Int32 line_cnt, Int32 dst_cnt,
																	Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	PIX_F* src, PIX_F* dst);

extern UInt32* merge_lines_xRGB15_xRGB15(Int32 line_cnt, Int32 dst_cnt,
																				 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																				 UInt16* src, UInt16* dst);

extern UInt32* merge_lines_AB16_AB16(Int32 line_cnt, Int32 dst_cnt,
																		 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																		 UInt16* src, UInt16* dst);

extern UInt32* merge_lines_AB32_AB32(Int32 line_cnt, Int32 dst_cnt,
																		 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																		 UInt32* src, UInt32* dst);

extern PIX_F* merge_lines_AB64_AB64(Int32 line_cnt, Int32 dst_cnt,
																		Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																		PIX_F* src, PIX_F* dst);

extern UInt32* merge_lines_AG16_AG16(Int32 line_cnt, Int32 dst_cnt,
																		 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																		 UInt16* src, UInt16* dst);

extern UInt32* merge_lines_AG32_AG32(Int32 line_cnt, Int32 dst_cnt,
																		 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																		 UInt32* src, UInt32* dst);

extern PIX_F* merge_lines_AG64_AG64(Int32 line_cnt, Int32 dst_cnt,
																		Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																		PIX_F* src, PIX_F* dst);

extern UInt32* merge_lines_RGB24_RGB24(Int32 line_cnt, Int32 dst_cnt,
																			 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																			 UChar* src, UChar* dst);

extern UInt32* merge_lines_xRGB24_xRGB24(Int32 line_cnt, Int32 dst_cnt,
																				 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																				 UInt32* src, UInt32* dst);

extern UInt32* merge_lines_CMYK32_CMYK32(Int32 line_cnt, Int32 dst_cnt,
																				 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																				 UInt32* src, UInt32* dst);

extern UInt32* merge_lines_ARGB32_ARGB32(Int32 line_cnt, Int32 dst_cnt,
																				 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																				 UInt32* src, UInt32* dst);


extern UInt32* merge_lines_RGB48_RGB48(Int32 line_cnt, Int32 dst_cnt,
																			 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																			 PIX_W* src, PIX_W* dst);

extern UInt32* merge_lines_xRGB48_xRGB48(Int32 line_cnt, Int32 dst_cnt,
																				 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																				 UInt32* src, UInt32* dst);

extern UInt32* merge_lines_CMYK64_CMYK64(Int32 line_cnt, Int32 dst_cnt,
																				 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																				 UInt32* src, UInt32* dst);

extern UInt32* merge_lines_ARGB64_ARGB64(Int32 line_cnt, Int32 dst_cnt,
																				 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																				 UInt32* src, UInt32* dst);


extern PIX_F* merge_lines_RGB96_RGB96(Int32 line_cnt, Int32 dst_cnt,
																			Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																			PIX_F* src, PIX_F* dst);

extern PIX_F* merge_lines_xRGB96_xRGB96(Int32 line_cnt, Int32 dst_cnt,
																				Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																				PIX_F* src, PIX_F* dst);

extern PIX_F* merge_lines_CMYK128_CMYK128(Int32 line_cnt, Int32 dst_cnt,
																					Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																					PIX_F* src, PIX_F* dst);

extern PIX_F* merge_lines_ARGB128_ARGB128(Int32 line_cnt, Int32 dst_cnt,
																					Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																					PIX_F* src, PIX_F* dst);


#endif // MERGELIN_H__
