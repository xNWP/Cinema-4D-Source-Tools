#include	"scalelin.h"

#if GE_LITTLE_ENDIAN

	#define	INTEL_SWAP16(value)	value = REVERSEu16(value)
	#define	INTEL_SWAP32(value)	value = REVERSEu32(value)

#else

	#define	INTEL_SWAP16(value)
	#define	INTEL_SWAP32(value)

#endif

//----------------------------------------------------------------------------------------
// Divisor to shift count table
//----------------------------------------------------------------------------------------
static Char	cnt_to_shifts[256] =
{
	0,
	1,
	-1,
	2,
	-1, -1, -1,
	3,
	-1, -1, -1, -1, -1, -1, -1,
	4,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	5,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	6,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	7,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	8
};

//----------------------------------------------------------------------------------------
// Grow a line (1 - 8 bits)
// Function result:		-
// e:									negative destination width = - dw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void grow_line_px1_8(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										 UInt32* src, UInt32* dst)
{
	Int32	 shift_bits;
	UInt32 src_word;
	UInt32 dst_word;

	shift_bits = 32 - bits;	// # of shifts to the right for the first pixel

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;
	src_bit_offset &= 31;
	dst_bit_offset &= 31;

	src_word = *src++;
	INTEL_SWAP32(src_word);
	src_word <<= src_bit_offset;
	dst_word	 = *dst;
	INTEL_SWAP32(dst_word);
	dst_word >>= (32 - dst_bit_offset);

	src_bit_offset -= 32;	// (negative) # of bits that have to be read
	dst_bit_offset -= 32;	// (negative) # of bits that have to be written

	while (cnt >= 0)
	{
		dst_word <<= bits;
		dst_word	|= src_word >> shift_bits;	// insert source pixel
		dst_bit_offset += bits;								// next destination bit offset

		if (dst_bit_offset == 0)							// destination word full?
		{
			INTEL_SWAP32(dst_word);
			*dst++ = dst_word;
			dst_bit_offset = -32;
		}

		e += sw;										// add source width to the discriminator

		if (e >= 0)									// read the next source pixel?
		{
			e -= dw;									// subtract destination width from the discriminator

			src_word <<= bits;				// next source pixel
			src_bit_offset += bits;		// next source bit offset

			if (src_bit_offset == 0)	// source word empty?
			{
				src_word = *src++;
				INTEL_SWAP32(src_word);
				src_bit_offset = -32;
			}
		}
		cnt--;
	}

	if (dst_bit_offset > -32)	// write the last destination word?
	{
		UInt32 mask;

		dst_bit_offset = -dst_bit_offset;
		dst_word <<= dst_bit_offset;
		mask = UInt32((1L << dst_bit_offset) - 1);
		INTEL_SWAP32(dst_word);
		INTEL_SWAP32(mask);
		dst_word |= *dst & mask;
		*dst++ = dst_word;
	}
}

//----------------------------------------------------------------------------------------
// Grow a line (16 bits)
// Function result:		-
// e:									negative destination width = - dw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void grow_line_px16(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										UInt16* src, UInt16* dst)
{
	UInt32 src_word;

	(void) bits;

	src = (UInt16*) ((UChar*) src + (src_bit_offset >> 3));
	dst = (UInt16*) ((UChar*) dst + (dst_bit_offset >> 3));

	src_word = *src++;

	while (cnt >= 0)
	{
		*dst++ = (UInt16)src_word;

		e += sw;

		if (e >= 0)
		{
			e -= dw;
			src_word = *src++;
		}
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Grow a line (24 bits)
// Function result:		-
// e:									negative destination width = - dw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void grow_line_px24(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										UChar* src, UChar* dst)
{
	UChar	src_c0;
	UChar	src_c1;
	UChar	src_c2;

	(void) bits;

	src += src_bit_offset >> 3;
	dst += dst_bit_offset >> 3;

	src_c0 = *src++;
	src_c1 = *src++;
	src_c2 = *src++;

	while (cnt >= 0)
	{
		*dst++ = src_c0;
		*dst++ = src_c1;
		*dst++ = src_c2;

		e += sw;

		if (e >= 0)
		{
			e -= dw;
			src_c0 = *src++;
			src_c1 = *src++;
			src_c2 = *src++;
		}
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Grow a line (32 bits)
// Function result:		-
// e:									negative destination width = - dw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void grow_line_px32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										UInt32* src, UInt32* dst)
{
	UInt32 src_word;

	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;
	src_word = *src++;

	while (cnt >= 0)
	{
		*dst++ = src_word;

		e += sw;

		if (e >= 0)
		{
			e -= dw;
			src_word = *src++;
		}
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Grow a line (48 bits)
// Function result:		-
// e:									negative destination width = - dw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void grow_line_px48(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										PIX_W* src, PIX_W* dst)
{
	PIX_W	src_c0;
	PIX_W	src_c1;
	PIX_W	src_c2;

	(void) bits;

	src += src_bit_offset >> 4;
	dst += dst_bit_offset >> 4;

	src_c0 = *src++;
	src_c1 = *src++;
	src_c2 = *src++;

	while (cnt >= 0)
	{
		*dst++ = src_c0;
		*dst++ = src_c1;
		*dst++ = src_c2;

		e += sw;

		if (e >= 0)
		{
			e -= dw;
			src_c0 = *src++;
			src_c1 = *src++;
			src_c2 = *src++;
		}
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Grow a line (64 bits)
// Function result:		-
// e:									negative destination width = - dw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void grow_line_px64(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										UInt32* src, UInt32* dst)
{
	UInt32 src_word0;
	UInt32 src_word1;

	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;
	src_word0 = *src++;
	src_word1 = *src++;

	while (cnt >= 0)
	{
		*dst++ = src_word0;
		*dst++ = src_word1;

		e += sw;

		if (e >= 0)
		{
			e -= dw;
			src_word0 = *src++;
			src_word1 = *src++;
		}
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Grow a line (96 bits)
// Function result:		-
// e:									negative destination width = - dw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void grow_line_px96(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										PIX_F* src, PIX_F* dst)
{
	PIX_F	src_c0;
	PIX_F	src_c1;
	PIX_F	src_c2;

	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	src_c0 = *src++;
	src_c1 = *src++;
	src_c2 = *src++;

	while (cnt >= 0)
	{
		*dst++ = src_c0;
		*dst++ = src_c1;
		*dst++ = src_c2;

		e += sw;

		if (e >= 0)
		{
			e -= dw;
			src_c0 = *src++;
			src_c1 = *src++;
			src_c2 = *src++;
		}
		cnt--;
	}
}


//----------------------------------------------------------------------------------------
// Grow a line (128 bits)
// Function result:		-
// e:									negative destination width = - dw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void grow_line_px128(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										 PIX_F* src, PIX_F* dst)
{
	PIX_F	src_word0;
	PIX_F	src_word1;
	PIX_F	src_word2;
	PIX_F	src_word3;

	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;
	src_word0 = *src++;
	src_word1 = *src++;
	src_word2 = *src++;
	src_word3 = *src++;

	while (cnt >= 0)
	{
		*dst++ = src_word0;
		*dst++ = src_word1;
		*dst++ = src_word2;
		*dst++ = src_word3;

		e += sw;

		if (e >= 0)
		{
			e -= dw;
			src_word0 = *src++;
			src_word1 = *src++;
			src_word2 = *src++;
			src_word3 = *src++;
		}
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (1 - 8 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_px1_8(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
											 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
											 UInt32* src, UInt32* dst)
{
	Int32	 shift_bits;
	UInt32 src_word;
	UInt32 dst_word;

	shift_bits = 32 - bits;	// # of shifts to the right for the first pixel

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;
	src_bit_offset &= 31;
	dst_bit_offset &= 31;

	src_word = *src++;
	INTEL_SWAP32(src_word);
	src_word <<= src_bit_offset;
	dst_word	 = *dst;
	INTEL_SWAP32(dst_word);
	dst_word >>= (32 - dst_bit_offset);

	src_bit_offset -= 32;	// (negative) # of bits that have to be read
	dst_bit_offset -= 32;	// (negative) # of bits that have to be written

	while (cnt >= 0)
	{
		UInt32 src_value;

		src_value = 0;

		while (e < 0)	// read another source pixel?
		{
			UInt32 tmp;

			if (src_bit_offset == 0)
			{
				src_word = *src++;
				INTEL_SWAP32(src_word);
				src_bit_offset = -32;
			}

			tmp =	src_word >> shift_bits;	// source pixel
			if (tmp > src_value)
				src_value = tmp;

			src_word <<= bits;
			src_bit_offset += bits;

			e += dw;
		}

		dst_word <<= bits;
		dst_word	|= src_value;	// insert source pixel
		dst_bit_offset += bits;

		if (dst_bit_offset == 0)
		{
			INTEL_SWAP32(dst_word);
			*dst++ = dst_word;
			dst_bit_offset = -32;
		}

		e -= sw;

		cnt--;
	}

	if (dst_bit_offset > -32)
	{
		UInt32 mask;

		dst_bit_offset = -dst_bit_offset;
		dst_word <<= dst_bit_offset;
		mask = UInt32((1L << dst_bit_offset) - 1);
		INTEL_SWAP32(dst_word);
		INTEL_SWAP32(mask);
		dst_word |= *dst & mask;
		*dst++ = dst_word;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (8 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_A8(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										UChar* src, UChar* dst)
{
	(void) bits;

	src += src_bit_offset >> 3;
	dst += dst_bit_offset >> 3;

	while (cnt >= 0)
	{
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_gray;

		src_cnt	 = 0;
		src_gray = 0;

		while (e < 0)
		{
			src_gray += *src++;
			src_cnt++;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)	// can we shift?
			src_gray >>= shifts;
		else							// we have to divide
			src_gray /= src_cnt;

		*dst++ = (UChar) src_gray;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (16 bits, 3 components a 5 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_xABC15(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												UInt16* src, UInt16* dst)
{
	(void) bits;

	src += src_bit_offset >> 4;
	dst += dst_bit_offset >> 4;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_red;
		UInt32 src_green;
		UInt32 src_blue;

		src_cnt = 0;
		src_red = 0;
		src_green = 0;
		src_blue	= 0;

		while (e < 0)
		{
			src_word = *src++;
			INTEL_SWAP16(src_word);

			src_cnt++;
			src_red += (src_word >> 10) & 0x001fL;
			src_green += (src_word >> 5) & 0x001fL;
			src_blue	+= src_word & 0x001fL;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)
		{
			src_red >>= shifts;
			src_green >>= shifts;
			src_blue	>>= shifts;
		}
		else
		{
			src_red /= src_cnt;
			src_green /= src_cnt;
			src_blue	/= src_cnt;
		}

		dst_word = (src_red << 10) | (src_green << 5) | src_blue;
		INTEL_SWAP16(dst_word);
		*dst++ = (UInt16) dst_word;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (16 bits, 2 independent components a 8 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_AB16(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
											Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
											UInt16* src, UInt16* dst)
{
	(void) bits;

	src += src_bit_offset >> 4;
	dst += dst_bit_offset >> 4;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_a;
		UInt32 src_b;

		src_cnt = 0;
		src_a = 0;
		src_b = 0;

		while (e < 0)
		{
			src_word = *src++;
			INTEL_SWAP16(src_word);

			src_cnt++;
			src_a += (src_word >> 8) & 0x00ffL;
			src_b += src_word & 0x00ffL;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)
		{
			src_a >>= shifts;
			src_b >>= shifts;
		}
		else
		{
			src_a /= src_cnt;
			src_b /= src_cnt;
		}

		dst_word = (src_a << 8) | src_b;
		INTEL_SWAP16(dst_word);
		*dst++ = (UInt16) dst_word;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (16 bits, 2 components a 8 bits, first one is alpha)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_AG16(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
											Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
											UInt16* src, UInt16* dst)
{
	(void) bits;

	src += src_bit_offset >> 4;
	dst += dst_bit_offset >> 4;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 src_cnt;
		UInt32 src_alpha;
		UInt32 src_gray;

		src_cnt = 0;
		src_alpha = 0;
		src_gray	= 0;

		while (e < 0)
		{
			UInt32 alpha;

			src_word = *src++;
			INTEL_SWAP16(src_word);

			src_cnt++;
			alpha = (src_word >> 8) & 0x00ffL;
			src_alpha += alpha;
			src_gray	+= (src_word & 0x00ffL) * alpha;

			e += dw;
		}

		dst_word = (src_alpha / src_cnt) << 8;

		if (src_alpha)
		{
			src_gray /= src_alpha;
			dst_word |= src_gray;
		}

		INTEL_SWAP16(dst_word);
		*dst++ = (UInt16) dst_word;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (24 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_ABC24(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
											 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
											 UChar* src, UChar* dst)
{
	(void) bits;

	src += src_bit_offset >> 3;
	dst += dst_bit_offset >> 3;

	while (cnt >= 0)
	{
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_red;
		UInt32 src_green;
		UInt32 src_blue;

		src_cnt = 0;
		src_red = 0;
		src_green = 0;
		src_blue	= 0;

		while (e < 0)
		{
			src_cnt++;
			src_red += *src++;
			src_green += *src++;
			src_blue	+= *src++;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)
		{
			src_red >>= shifts;
			src_green >>= shifts;
			src_blue	>>= shifts;
		}
		else
		{
			src_red /= src_cnt;
			src_green /= src_cnt;
			src_blue	/= src_cnt;
		}

		*dst++ = (UChar)src_red;
		*dst++ = (UChar)src_green;
		*dst++ = (UChar)src_blue;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (32 bits, 3 components a 8 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_xABC24(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												UInt32* src, UInt32* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_red;
		UInt32 src_green;
		UInt32 src_blue;

		src_cnt = 0;
		src_red = 0;
		src_green = 0;
		src_blue	= 0;

		while (e < 0)
		{
			src_word = *src++;
			INTEL_SWAP32(src_word);

			src_cnt++;
			src_red += (src_word >> 16) & 0x000000ffL;
			src_green += (src_word >> 8) & 0x000000ffL;
			src_blue	+= src_word & 0x000000ffL;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)
		{
			src_red >>= shifts;
			src_green >>= shifts;
			src_blue	>>= shifts;
		}
		else
		{
			src_red /= src_cnt;
			src_green /= src_cnt;
			src_blue	/= src_cnt;
		}

		dst_word = (src_red << 16) | (src_green << 8) | src_blue;
		INTEL_SWAP32(dst_word);
		*dst++ = dst_word;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (32 bits, 4 independent components a 8 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_ABCD32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												UInt32* src, UInt32* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_a;
		UInt32 src_b;
		UInt32 src_c;
		UInt32 src_d;

		src_cnt = 0;
		src_a = 0;
		src_b = 0;
		src_c = 0;
		src_d = 0;

		while (e < 0)
		{
			src_word = *src++;
			INTEL_SWAP32(src_word);

			src_cnt++;
			src_a += (src_word >> 24) & 0x000000ffL;
			src_b += (src_word >> 16) & 0x000000ffL;
			src_c += (src_word >> 8) & 0x000000ffL;
			src_d += src_word & 0x000000ffL;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)
		{
			src_a >>= shifts;
			src_b >>= shifts;
			src_c >>= shifts;
			src_d >>= shifts;
		}
		else
		{
			src_a /= src_cnt;
			src_b /= src_cnt;
			src_c /= src_cnt;
			src_d /= src_cnt;
		}

		dst_word = (src_a << 24) | (src_b << 16) | (src_c << 8) | src_d;
		INTEL_SWAP32(dst_word);
		*dst++ = dst_word;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (32 bits, 4 components a 8 bits, first one is alpha)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_ARGB32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												UInt32* src, UInt32* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 src_cnt;
		UInt32 src_alpha;
		UInt32 src_red;
		UInt32 src_green;
		UInt32 src_blue;

		src_cnt = 0;
		src_alpha = 0;
		src_red = 0;
		src_green = 0;
		src_blue	= 0;

		while (e < 0)
		{
			UInt32 alpha;

			src_word = *src++;
			INTEL_SWAP32(src_word);

			src_cnt++;
			alpha = (src_word >> 24) & 0x000000ffL;
			src_alpha += alpha;
			src_red += ((src_word >> 16) & 0x000000ffL) * alpha;
			src_green += ((src_word >> 8) & 0x000000ffL) * alpha;
			src_blue	+= (src_word & 0x000000ffL) * alpha;

			e += dw;
		}

		dst_word = ((src_alpha / src_cnt) << 24);

		if (src_alpha)
		{
			src_red /= src_alpha;
			src_green /= src_alpha;
			src_blue	/= src_alpha;
			dst_word	|= (src_red << 16) | (src_green << 8) | src_blue;
		}

		INTEL_SWAP32(dst_word);
		*dst++ = dst_word;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (32 bits, 2 components a 16 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_AB32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
											Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
											UInt32* src, UInt32* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_c0;
		UInt32 src_c1;

		src_cnt = 0;
		src_c0	= 0;
		src_c1	= 0;

		while (e < 0)
		{
			src_word = *src++;
			INTEL_SWAP32(src_word);

			src_c0 += (src_word >> 16) & 0x0000ffffL;
			src_c1 += src_word & 0x0000ffffL;
			src_cnt++;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)
		{
			src_c0 >>= shifts;
			src_c1 >>= shifts;
		}
		else
		{
			src_c0 /= src_cnt;
			src_c1 /= src_cnt;
		}

		dst_word = (src_c0 << 16) | src_c1;
		INTEL_SWAP32(dst_word);
		*dst++ = dst_word;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (64 bits, 2 components a 32 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_AB64(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
											Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
											PIX_F* src, PIX_F* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		Int32	src_cnt;
		PIX_F	src_c0;
		PIX_F	src_c1;
		PIX_F	multiplier;

		src_cnt = 0;
		src_c0	= 0;
		src_c1	= 0;

		while (e < 0)
		{
			src_c0 += *src++;
			src_c1 += *src++;
			src_cnt++;

			e += dw;
		}

		multiplier = 1.0f / src_cnt;
		*dst++ = src_c0 * multiplier;
		*dst++ = src_c1 * multiplier;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (16 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_A16(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										 PIX_W* src, PIX_W* dst)
{
	(void) bits;

	src += src_bit_offset >> 4;
	dst += dst_bit_offset >> 4;

	while (cnt >= 0)
	{
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_gray;

		src_cnt	 = 0;
		src_gray = 0;

		while (e < 0)
		{
			src_gray += *src++;
			src_cnt++;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)	// can we shift?
			src_gray >>= shifts;
		else							// we have to divide
			src_gray /= src_cnt;

		*dst++ = (PIX_W) src_gray;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (32 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_A32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
										 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
										 PIX_F* src, PIX_F* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		Int32	src_cnt;
		PIX_F	src_gray;

		src_cnt	 = 0;
		src_gray = 0;

		while (e < 0)
		{
			src_gray += *src++;
			src_cnt++;

			e += dw;
		}

		*dst++ = src_gray / src_cnt;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (32 bits, 2 components a 16 bits, first one is alpha)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_AG32(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
											Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
											UInt32* src, UInt32* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 src_cnt;
		UInt32 src_alpha;
		Int64	 src_gray;

		src_cnt = 0;
		src_alpha = 0;
		src_gray	= 0;

		while (e < 0)
		{
			UInt32 alpha;

			src_word = *src++;
			src_cnt++;
#if GE_LITTLE_ENDIAN
			alpha = src_word & 0x0000ffffUL;
			src_gray += ((src_word >> 16) & 0x0000ffffUL) * alpha;
#else
			alpha = (src_word >> 16) & 0x0000ffffUL;
			src_gray += (src_word & 0x0000ffffUL) * alpha;
#endif
			src_alpha += alpha;

			e += dw;
		}

#if GE_LITTLE_ENDIAN
		dst_word = src_alpha / src_cnt;

		if (src_alpha)
			dst_word |= ((UInt32) (src_gray / src_alpha)) << 16;
#else
		dst_word = (src_alpha / src_cnt) << 16;

		if (src_alpha)
			dst_word |= (UInt32) (src_gray / src_alpha);
#endif
		*dst++ = dst_word;

		e -= sw;
		cnt--;
	}
}


//----------------------------------------------------------------------------------------
// Shrink a line (64 bits, 2 components a 32 bits, first one is alpha)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_AG64(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
											Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
											PIX_F* src, PIX_F* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		Int32	src_cnt;
		PIX_F	src_alpha;
		PIX_F	src_gray;

		src_cnt = 0;
		src_alpha = 0;
		src_gray	= 0;

		while (e < 0)
		{
			PIX_F	alpha;

			src_cnt++;
			alpha = *src++;
			src_alpha += alpha;
			src_gray	+= *src++ *alpha;

			e += dw;
		}

		*dst++ = src_alpha / src_cnt;

		if (src_alpha > 0.0)
			src_gray /= src_alpha;
		else
			src_gray = 0;

		*dst++ = src_gray;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (48 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_ABC48(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
											 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
											 PIX_W* src, PIX_W* dst)
{
	(void) bits;

	src += src_bit_offset >> 4;
	dst += dst_bit_offset >> 4;

	while (cnt >= 0)
	{
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_red;
		UInt32 src_green;
		UInt32 src_blue;

		src_cnt = 0;
		src_red = 0;
		src_green = 0;
		src_blue	= 0;

		while (e < 0)
		{
			src_cnt++;
			src_red += *src++;
			src_green += *src++;
			src_blue	+= *src++;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)
		{
			src_red >>= shifts;
			src_green >>= shifts;
			src_blue	>>= shifts;
		}
		else
		{
			src_red /= src_cnt;
			src_green /= src_cnt;
			src_blue	/= src_cnt;
		}

		*dst++ = (PIX_W)src_red;
		*dst++ = (PIX_W)src_green;
		*dst++ = (PIX_W)src_blue;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (64 bits, 3 components a 16 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_xABC48(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												UInt32* src, UInt32* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_red;
		UInt32 src_green;
		UInt32 src_blue;

		src_cnt = 0;
		src_red = 0;
		src_green = 0;
		src_blue	= 0;

		while (e < 0)
		{
			src_word = *src++;
			INTEL_SWAP32(src_word);

			src_cnt++;
			src_red += src_word & 0x0000ffffL;

			src_word = *src++;
			INTEL_SWAP32(src_word);

			src_green += (src_word >> 16) & 0x0000ffffL;
			src_blue	+= src_word & 0x0000ffffL;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)
		{
			src_red >>= shifts;
			src_green >>= shifts;
			src_blue	>>= shifts;
		}
		else
		{
			src_red /= src_cnt;
			src_green /= src_cnt;
			src_blue	/= src_cnt;
		}

		dst_word = src_red;
		INTEL_SWAP32(dst_word);
		*dst++ = dst_word;

		dst_word = (src_green << 16) | src_blue;
		INTEL_SWAP32(dst_word);
		*dst++ = dst_word;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (96 bits, 3 components a 32 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_ABC96(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
											 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
											 PIX_F* src, PIX_F* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		Int32	src_cnt;
		PIX_F	src_red;
		PIX_F	src_green;
		PIX_F	src_blue;
		PIX_F	multiplier;

		src_cnt = 0;
		src_red = 0;
		src_green = 0;
		src_blue	= 0;

		while (e < 0)
		{
			src_red += *src++;
			src_green += *src++;
			src_blue	+= *src++;
			src_cnt++;

			e += dw;
		}

		multiplier = 1.0f / src_cnt;
		*dst++ = src_red * multiplier;
		*dst++ = src_green * multiplier;
		*dst++ = src_blue * multiplier;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (128 bits, 3 components a 32 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_xABC96(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												PIX_F* src, PIX_F* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		Int32	src_cnt;
		PIX_F	src_red;
		PIX_F	src_green;
		PIX_F	src_blue;
		PIX_F	multiplier;

		src_cnt = 0;
		src_red = 0;
		src_green = 0;
		src_blue	= 0;

		while (e < 0)
		{
			src++;
			src_red += *src++;
			src_green += *src++;
			src_blue	+= *src++;
			src_cnt++;

			e += dw;
		}

		multiplier = 1.0f / src_cnt;
		*dst++ = 0;
		*dst++ = src_red * multiplier;
		*dst++ = src_green * multiplier;
		*dst++ = src_blue * multiplier;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (64 bits, 4 independant components a 16 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_ABCD64(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												UInt32* src, UInt32* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 shifts;
		Int32	 src_cnt;
		UInt32 src_c0;
		UInt32 src_c1;
		UInt32 src_c2;
		UInt32 src_c3;

		src_cnt = 0;
		src_c0	= 0;
		src_c1	= 0;
		src_c2	= 0;
		src_c3	= 0;

		while (e < 0)
		{
			src_word = *src++;
			INTEL_SWAP32(src_word);

			src_cnt++;
			src_c0 += (src_word >> 16) & 0x0000ffffL;
			src_c1 += src_word & 0x0000ffffL;

			src_word = *src++;
			INTEL_SWAP32(src_word);

			src_c2 += (src_word >> 16) & 0x0000ffffL;
			src_c3 += src_word & 0x0000ffffL;

			e += dw;
		}

		shifts = -1;
		if (src_cnt < 256)
			shifts = cnt_to_shifts[src_cnt - 1];

		if (shifts >= 0)
		{
			src_c0 >>= shifts;
			src_c1 >>= shifts;
			src_c2 >>= shifts;
			src_c3 >>= shifts;
		}
		else
		{
			src_c0 /= src_cnt;
			src_c1 /= src_cnt;
			src_c2 /= src_cnt;
			src_c3 /= src_cnt;
		}

		dst_word = (src_c0 << 16) | src_c1;
		INTEL_SWAP32(dst_word);
		*dst++ = dst_word;

		dst_word = (src_c2 << 16) | src_c3;
		INTEL_SWAP32(dst_word);
		*dst++ = dst_word;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (128 bits, 4 components a 32 bits)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_ABCD128(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												 PIX_F* src, PIX_F* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		Int32	src_cnt;
		PIX_F	src_c0;
		PIX_F	src_c1;
		PIX_F	src_c2;
		PIX_F	src_c3;
		PIX_F	multiplier;

		src_cnt = 0;
		src_c0	= 0;
		src_c1	= 0;
		src_c2	= 0;
		src_c3	= 0;

		while (e < 0)
		{
			src_c0 += *src++;
			src_c1 += *src++;
			src_c2 += *src++;
			src_c3 += *src++;
			src_cnt++;

			e += dw;
		}

		multiplier = 1.0f / src_cnt;
		*dst++ = src_c0 * multiplier;
		*dst++ = src_c1 * multiplier;
		*dst++ = src_c2 * multiplier;
		*dst++ = src_c3 * multiplier;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (64 bits, 4 components a 16 bits, first one is alpha)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_ARGB64(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												UInt32* src, UInt32* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		UInt32 src_word;
		UInt32 dst_word;
		Int32	 src_cnt;
		UInt32 src_alpha;
		Int64	 src_red;
		Int64	 src_green;
		Int64	 src_blue;

		src_cnt = 0;
		src_alpha = 0;
		src_red = 0;
		src_green = 0;
		src_blue	= 0;

		while (e < 0)
		{
			UInt32 alpha;

			src_cnt++;

#if GE_LITTLE_ENDIAN
			src_word = *src++;
			alpha = src_word & 0x0000ffffL;
			src_alpha += alpha;
			src_red += ((src_word >> 16) & 0x0000ffffL) * alpha;

			src_word	 = *src++;
			src_green += (src_word & 0x0000ffffL) * alpha;
			src_blue	+= ((src_word >> 16) & 0x0000ffffL) * alpha;
#else
			src_word = *src++;
			alpha = (src_word >> 16) & 0x0000ffffL;
			src_alpha += alpha;
			src_red += (src_word & 0x0000ffffL) * alpha;

			src_word	 = *src++;
			src_green += ((src_word >> 16) & 0x0000ffffL) * alpha;
			src_blue	+= (src_word & 0x0000ffffL) * alpha;
#endif
			e += dw;
		}

#if GE_LITTLE_ENDIAN
		dst_word = src_alpha / src_cnt;

		if (src_alpha)
		{
			dst_word |= ((UInt32) (src_red / src_alpha)) << 16;
			*dst++ = dst_word;

			dst_word	= (UInt32) (src_green / src_alpha);
			dst_word |= ((UInt32) (src_blue / src_alpha)) << 16;
		}
		else
		{
			*dst++ = dst_word;
			dst_word = 0;
		}
#else
		dst_word = (src_alpha / src_cnt) << 16;

		if (src_alpha)
		{
			dst_word |= (UInt32) (src_red / src_alpha);

			*dst++ = dst_word;

			dst_word	= ((UInt32) (src_green / src_alpha)) << 16;
			dst_word |= (UInt32) (src_blue / src_alpha);
		}
		else
		{
			*dst++ = dst_word;
			dst_word = 0;
		}
#endif
		*dst++ = dst_word;

		e -= sw;
		cnt--;
	}
}

//----------------------------------------------------------------------------------------
// Shrink a line (128 bits, 4 components a 32 bits, first one is alpha)
// Function result:		-
// e:									negative source width = - sw (discriminator start value)
// sw:								source width (error for a step to the next destination pixel)
// dw:								destination width (error for a step to the next source pixel)
// cnt:								number of output pixels - 1
// bits:							bits per pixel
// src_bit_offset:		number of unused (left) bits in the first source word
// dst_bit_offset:		number of unused (left) bits in the first destination word
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
void shrink_line_ARGB128(Int32 e, Int32 sw, Int32 dw, Int32 cnt,
												 Int32 bits, Int32 src_bit_offset, Int32 dst_bit_offset,
												 PIX_F* src, PIX_F* dst)
{
	(void) bits;

	src += src_bit_offset >> 5;
	dst += dst_bit_offset >> 5;

	while (cnt >= 0)
	{
		Int32	src_cnt;
		PIX_F	src_alpha;
		PIX_F	src_red;
		PIX_F	src_green;
		PIX_F	src_blue;
		PIX_F	multiplier;

		src_cnt = 0;
		src_alpha = 0;
		src_red = 0;
		src_green = 0;
		src_blue	= 0;

		while (e < 0)
		{
			PIX_F	alpha;

			src_cnt++;
			alpha = *src++;
			src_alpha += alpha;
			src_red += *src++ *alpha;
			src_green += *src++ *alpha;
			src_blue	+= *src++ *alpha;

			e += dw;
		}

		*dst++ = src_alpha / src_cnt;

		multiplier = 0;
		if (src_alpha > 0.0)
			multiplier = 1.0f / src_alpha;

		*dst++ = src_red * multiplier;
		*dst++ = src_green * multiplier;
		*dst++ = src_blue * multiplier;

		e -= sw;
		cnt--;
	}
}
