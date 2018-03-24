#include	"mergelin.h"

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
Char cnt_to_shifts[256] =
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
// Merge lines (1 - 8 bits)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_px1_8(Int32 line_cnt, Int32 dst_cnt,
													Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
													UInt32* src, UInt32* dst)
{
	UInt32	src_word;
	UInt32	dst_word;
	Int32		shift_bits;
	UInt32* merge_buf;

	shift_bits = 32 - src_bits;										// # of shifts to the right for the first pixel

	src += src_bit_offset >> 5;										// pointer to first source word
	src_bit_offset &= 31;
	dst_word = 0;																	// only for the compiler (warning)
	dst	 = (UInt32*) ((UChar*) dst + dst_length);	// points behind the buffer
	dst -= dst_cnt + 1;
	merge_buf = dst;

	if (line_cnt == 0)
	{
		while (dst_cnt >= 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else
	{
		Int32	i;
		Int32	j;

		if (line_cnt > 255)
			line_cnt = 255;

		for (j = dst_cnt; j >= 0; j--)
			*merge_buf++ = *src++;

		for (i = line_cnt - 1; i >= 0; i--)
		{
			src = (UInt32*) ((UChar*) src + src_line_offset);
			merge_buf = (UInt32*) dst;

			for (j = dst_cnt; j >= 0; j--)
			{
				src_word = *src++;
				dst_word = *merge_buf;

				for (src_bit_offset = -32; src_bit_offset < 0; src_bit_offset += src_bits)
				{
					UInt32 src_color;
					UInt32 dst_color;

					src_color = src_word >> shift_bits;
					dst_color = dst_word >> shift_bits;

					src_word <<= src_bits;
					dst_word <<= src_bits;

					if (src_color > dst_color)
						dst_color = src_color;

					dst_word |= dst_color;
				}
				*merge_buf++ = dst_word;
			}
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (8 bits, 1 component)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_G8_G8(Int32 line_cnt, Int32 dst_cnt,
													Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
													UChar* src, UChar* dst)
{
	Int32	shifts;

	(void) src_bits;

	src += (src_bit_offset >> 5) << 2;	// pointer to the first source word
	dst_cnt++;

	if (line_cnt == 0)	// only one line?
	{
		UInt32* merge_buf;

		dst += dst_length;
		dst -= dst_cnt << 2;
		merge_buf = (UInt32*) dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *((UInt32*) src);
			src += 4;
			dst_cnt--;
		}
	}
	else	// multiple lines
	{
		UInt16* merge_buf;
		Int32		i;
		Int32		j;

		if (line_cnt > 255)
			line_cnt = 255;		// limit that to 256 lines (no details anymore - really .-)

		merge_buf = (UInt16*) dst;
		dst_cnt <<= 2;	// # of destination pixels

		for (j = dst_cnt; j > 0; j--)
			*merge_buf++ = *src++;

		for (i = line_cnt - 1; i >= 0; i--)	// add the following lines
		{
			src += src_line_offset;						// next source line
			merge_buf = (UInt16*) dst;

			for (j = dst_cnt; j > 0; j--)
				*merge_buf++ += *src++;
		}

		dst += dst_length;	// points behind the buffer
		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)	// 2^n lines?
		{
			while (dst_cnt > 0)
			{
				*(--dst) = (UChar) (*(--merge_buf) >> shifts);
				dst_cnt--;
			}
		}
		else					// use division
		{
			line_cnt++;	// number of lines

			while (dst_cnt > 0)
			{
				*(--dst) = (UChar) (*(--merge_buf) / line_cnt);
				dst_cnt--;
			}
		}
	}
	return (UInt32*) dst;	// pointer to the merged line
}

//----------------------------------------------------------------------------------------
// Merge lines (16 bits, 3 components)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_xRGB15_xRGB15(Int32 line_cnt, Int32 dst_cnt,
																	Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	UInt16* src, UInt16* dst)
{
	UInt32 src_color;
	UInt32 dst_word;
	Int32	 shifts;

	(void) src_bits;

	src += (src_bit_offset >> 5) << 1;
	dst	 = (UInt16*) ((UChar*) dst + dst_length);

	if (line_cnt == 0)
	{
		UInt32* merge_buf;

		dst = (UInt16*) ((UInt32*) dst - (dst_cnt + 1));
		merge_buf = (UInt32*) dst;

		while (dst_cnt >= 0)
		{
			*merge_buf++ = *((UInt32*) src);
			src += 2;
			dst_cnt--;
		}
	}
	else
	{
		UInt16* merge_buf;
		Int32		i;
		Int32		j;

		if (line_cnt > 255)
			line_cnt = 255;

		dst -= (dst_cnt + 1) << 2;
		merge_buf = (UInt16*) dst;

		dst_cnt += dst_cnt + 1;	// number of destination pixels - 1

		for (j = dst_cnt; j >= 0; j--)
		{
			src_color = *src++;
			INTEL_SWAP16(src_color);

			*merge_buf++ = 0;
			*merge_buf++ = (src_color >> 10) & 0x001f;
			*merge_buf++ = (src_color >> 5) & 0x001f;
			*merge_buf++ = src_color & 0x001f;
		}

		for (i = line_cnt - 1; i >= 0; i--)
		{
			src = (UInt16*) ((UChar*) src + src_line_offset);
			merge_buf = dst;

			for (j = dst_cnt; j >= 0; j--)
			{
				src_color = *src++;
				INTEL_SWAP16(src_color);

				merge_buf++;
				*merge_buf++ += (src_color >> 10) & 0x001f;
				*merge_buf++ += (src_color >> 5) & 0x001f;
				*merge_buf++ += src_color & 0x001f;
			}
		}

		dst = (UInt16*) merge_buf;

		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)
		{
			while (dst_cnt >= 0)
			{
				dst_word	= (UInt32) * (--merge_buf) >> shifts;					// blue
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 5;	// green
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 10;	// red
				--merge_buf;

				INTEL_SWAP16(dst_word);
				*(--dst) = (UInt16) dst_word;
				dst_cnt--;
			}
		}
		else
		{
			line_cnt++;

			while (dst_cnt >= 0)
			{
				dst_word	= (UInt32) (*(--merge_buf) / line_cnt);					// blue
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 5;	// green
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 10;	// red
				--merge_buf;

				INTEL_SWAP16(dst_word);
				*(--dst) = (UInt16) dst_word;
				dst_cnt--;
			}
		}
	}
	return (UInt32*) dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (16 bits, 2 independent components)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_AB16_AB16(Int32 line_cnt, Int32 dst_cnt,
															Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
															UInt16* src, UInt16* dst)
{
	UInt32 src_color;
	UInt32 dst_word;
	Int32	 shifts;

	(void) src_bits;

	src += (src_bit_offset >> 5) << 1;	// points to the first source word
	dst_cnt++;

	if (line_cnt == 0)
	{
		UInt32* merge_buf;

		dst = (UInt16*) ((UChar*) dst + dst_length);
		dst = (UInt16*) ((UInt32*) dst - dst_cnt);
		merge_buf = (UInt32*) dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *((UInt32*) src);
			src += 2;
			dst_cnt--;
		}
	}
	else
	{
		UInt16* merge_buf;
		Int32		i;
		Int32		j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (UInt16*) dst;
		dst_cnt += dst_cnt;	// # of destination pixels

		for (j = dst_cnt; j > 0; j--)
		{
			src_color = *src++;
			INTEL_SWAP16(src_color);

			*merge_buf++ = (src_color >> 8) & 0x00ff;
			*merge_buf++ = src_color & 0x00ff;
		}

		for (i = line_cnt - 1; i >= 0; i--)
		{
			src = (UInt16*) ((UChar*) src + src_line_offset);
			merge_buf = dst;

			for (j = dst_cnt; j > 0; j--)
			{
				src_color = *src++;
				INTEL_SWAP16(src_color);

				*merge_buf++ += (src_color >> 8) & 0x00ff;
				*merge_buf++ += src_color & 0x00ff;
			}
		}

		dst = (UInt16*) ((UChar*) dst + dst_length);
		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)
		{
			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) * (--merge_buf) >> shifts;
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 8;

				INTEL_SWAP16(dst_word);
				*(--dst) = (UInt16) dst_word;
				dst_cnt--;
			}
		}
		else
		{
			line_cnt++;	// number of lines

			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) (*(--merge_buf) / line_cnt);
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 8;

				INTEL_SWAP16(dst_word);
				*(--dst) = (UInt16) dst_word;
				dst_cnt--;
			}
		}
	}
	return (UInt32*) dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (16 bits, 2 components, first one is alpha)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_AG16_AG16(Int32 line_cnt, Int32 dst_cnt,
															Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
															UInt16* src, UInt16* dst)
{
	UInt32 src_color;
	UInt32 dst_word;

	(void) src_bits;

	src += (src_bit_offset >> 5) << 1;	// points to the first source word
	dst_cnt++;

	if (line_cnt == 0)
	{
		UInt32* merge_buf;

		dst = (UInt16*) ((UChar*) dst + dst_length);
		dst = (UInt16*) ((UInt32*) dst - dst_cnt);
		merge_buf = (UInt32*) dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *((UInt32*) src);
			src += 2;
			dst_cnt--;
		}
	}
	else
	{
		UInt32* merge_buf;
		Int32		i;
		Int32		j;
		UInt32	alpha;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (UInt32*) dst;
		dst_cnt += dst_cnt;	// # of destination pixels

		for (j = dst_cnt; j > 0; j--)
		{
			src_color = *src++;
			INTEL_SWAP16(src_color);

			alpha = (src_color >> 8) & 0x00ff;
			*merge_buf++ = alpha;
			*merge_buf++ = (src_color & 0x00ff) * alpha;
		}

		for (i = line_cnt - 1; i >= 0; i--)	// add the following lines
		{
			src = (UInt16*) ((UChar*) src + src_line_offset);
			merge_buf = (UInt32*) dst;

			for (j = dst_cnt; j > 0; j--)
			{
				src_color = *src++;
				INTEL_SWAP16(src_color);

				alpha = (src_color >> 8) & 0x00ff;
				*merge_buf++ += alpha;
				*merge_buf++ += (src_color & 0x00ff) * alpha;
			}
		}

		dst = (UInt16*) ((UChar*) dst + dst_length);
		line_cnt++;	// number of lines

		while (dst_cnt > 0)
		{
			merge_buf -= 2;

			alpha = merge_buf[0];										// sum of alphas
			dst_word = (alpha / line_cnt) << 8;			// alpha

			if (alpha)															// component values different from zero?
				dst_word |= (merge_buf[1] / alpha);		// gray

			INTEL_SWAP16(dst_word);
			*(--dst) = (UInt16) dst_word;
			dst_cnt--;
		}
	}
	return (UInt32*) dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (24 bits, 3 components)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_RGB24_RGB24(Int32 line_cnt, Int32 dst_cnt,
																Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																UChar* src, UChar* dst)
{
	Int32	shifts;

	(void) src_bits;

	src += src_bit_offset >> 3;	// pointer to the first source pixel
	dst_cnt++;

	if (line_cnt == 0)
	{
		UInt32* merge_buf;

		dst += dst_length - (dst_cnt << 2);
		merge_buf = (UInt32*) dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *(UInt32*) src;
			src += 4;
			dst_cnt--;
		}
	}
	else
	{
		UInt16* merge_buf;
		Int32		i;
		Int32		j;

		// we have to adjust dst_cnt and src_line_offset because they
		// count in 4-byte-words -> convert to 3-byte counter
		src_line_offset += dst_cnt << 2;
		dst_cnt = (dst_cnt << 2) / 3;										// number of destination pixels
		src_line_offset -= dst_cnt + dst_cnt + dst_cnt;	// now the offset to the next source line refers to pixels and not to (quad-)words

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (UInt16*) dst;

		for (j = dst_cnt; j > 0; j--)
		{
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
		}

		for (i = line_cnt - 1; i >= 0; i--)				// add the following lines
		{
			src = ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (UInt16*) dst;

			for (j = dst_cnt; j > 0; j--)
			{
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
			}
		}

		dst += dst_length;	// pointer behind the buffer
		dst -= dst_cnt & 1;	// adjust the address if the number of pixels is odd (means: align the start address)

		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)
		{
			while (dst_cnt > 0)
			{
				*(--dst) = (UChar) (*(--merge_buf) >> shifts);	// blue
				*(--dst) = (UChar) (*(--merge_buf) >> shifts);	// green
				*(--dst) = (UChar) (*(--merge_buf) >> shifts);	// red
				dst_cnt--;
			}
		}
		else
		{
			line_cnt++;

			while (dst_cnt > 0)
			{
				*(--dst) = (UChar) (*(--merge_buf) / line_cnt);	// blue
				*(--dst) = (UChar) (*(--merge_buf) / line_cnt);	// green
				*(--dst) = (UChar) (*(--merge_buf) / line_cnt);	// red
				dst_cnt--;
			}
		}
	}
	return (UInt32*) dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (32 bits, 3 components a 8 bits)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_xRGB24_xRGB24(Int32 line_cnt, Int32 dst_cnt,
																	Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	UInt32* src, UInt32* dst)
{
	UInt32 src_color;
	UInt32 dst_word;
	Int32	 shifts;

	(void) src_bits;

	src += src_bit_offset >> 5;
	dst_cnt++;

	if (line_cnt == 0)
	{
		UInt32* merge_buf;

		dst	 = (UInt32*) ((UChar*) dst + dst_length);
		dst -= dst_cnt;
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else
	{
		UInt16* merge_buf;
		Int32		i;
		Int32		j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (UInt16*) dst;

		for (j = dst_cnt; j > 0; j--)
		{
			src_color = *src++;
			INTEL_SWAP32(src_color);

			*merge_buf++ = 0;
			*merge_buf++ = (src_color >> 16) & 0x000000ffL;
			*merge_buf++ = (src_color >> 8) & 0x000000ffL;
			*merge_buf++ = src_color & 0x000000ffL;
		}

		for (i = line_cnt - 1; i >= 0; i--)
		{
			src = (UInt32*) ((UChar*) src + src_line_offset);
			merge_buf = (UInt16*) dst;

			for (j = dst_cnt; j > 0; j--)
			{
				src_color = *src++;
				INTEL_SWAP32(src_color);

				merge_buf++;
				*merge_buf++ += (src_color >> 16) & 0x000000ffL;
				*merge_buf++ += (src_color >> 8) & 0x000000ffL;
				*merge_buf++ += src_color & 0x000000ffL;
			}
		}

		dst = (UInt32*) ((UChar*) dst + dst_length);

		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)
		{
			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) * (--merge_buf) >> shifts;					// blue
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 8;	// green
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 16;	// red
				--merge_buf;

				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;
				dst_cnt--;
			}
		}
		else
		{
			line_cnt++;

			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) (*(--merge_buf) / line_cnt);					// blue
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 8;	// green
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 16;	// red
				--merge_buf;

				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;
				dst_cnt--;
			}
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (32 bits, 4 independent components)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_CMYK32_CMYK32(Int32 line_cnt, Int32 dst_cnt,
																	Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	UInt32* src, UInt32* dst)
{
	UInt32 src_color;
	UInt32 dst_word;
	Int32	 shifts;

	(void) src_bits;

	src += src_bit_offset >> 5;	// pointer to the first source word
	dst_cnt++;

	if (line_cnt == 0)	// single line?
	{
		UInt32* merge_buf;

		dst	 = (UInt32*) ((UChar*) dst + dst_length);
		dst -= dst_cnt;
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else
	{
		UInt16* merge_buf;
		Int32		i;
		Int32		j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (UInt16*) dst;

		for (j = dst_cnt; j > 0; j--)
		{
			src_color = *src++;
			INTEL_SWAP32(src_color);

			*merge_buf++ = (src_color >> 24) & 0x000000ffL;
			*merge_buf++ = (src_color >> 16) & 0x000000ffL;
			*merge_buf++ = (src_color >> 8) & 0x000000ffL;
			*merge_buf++ = src_color & 0x000000ffL;
		}

		for (i = line_cnt - 1; i >= 0; i--)									// add the following lines
		{
			src = (UInt32*) ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (UInt16*) dst;

			for (j = dst_cnt; j > 0; j--)
			{
				src_color = *src++;
				INTEL_SWAP32(src_color);

				*merge_buf++ += (src_color >> 24) & 0x000000ffL;
				*merge_buf++ += (src_color >> 16) & 0x000000ffL;
				*merge_buf++ += (src_color >> 8) & 0x000000ffL;
				*merge_buf++ += src_color & 0x000000ffL;
			}
		}

		dst = (UInt32*) ((UChar*) dst + dst_length);

		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)
		{
			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) * (--merge_buf) >> shifts;					// black
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 8;	// yellow
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 16;	// magenta
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 24;	// cyan

				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;
				dst_cnt--;
			}
		}
		else
		{
			line_cnt++;	// number of lines

			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) (*(--merge_buf) / line_cnt);					// black
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 8;	// yellow
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 16;	// magenta
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 24;	// cyan

				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;
				dst_cnt--;
			}
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (32 bits, 4 components, first one is alpha)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_ARGB32_ARGB32(Int32 line_cnt, Int32 dst_cnt,
																	Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	UInt32* src, UInt32* dst)
{
	UInt32 src_color;
	UInt32 dst_word;

	(void) src_bits;

	src += src_bit_offset >> 5;	// pointer to the first source word
	dst_cnt++;

	if (line_cnt == 0)	// single line?
	{
		UInt32* merge_buf;

		dst	 = (UInt32*) ((UChar*) dst + dst_length);
		dst -= dst_cnt;
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else
	{
		UInt32* merge_buf;
		Int32		i;
		Int32		j;
		UInt32	alpha;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (UInt32*) dst;

		for (j = dst_cnt; j > 0; j--)
		{
			src_color = *src++;
			INTEL_SWAP32(src_color);

			alpha = (src_color >> 24) & 0x000000ffL;
			*merge_buf++ = alpha;
			*merge_buf++ = ((src_color >> 16) & 0x000000ffL) * alpha;
			*merge_buf++ = ((src_color >> 8) & 0x000000ffL) * alpha;
			*merge_buf++ = (src_color & 0x000000ffL) * alpha;
		}

		for (i = line_cnt - 1; i >= 0; i--)									// add the following lines
		{
			src = (UInt32*) ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (UInt32*) dst;

			for (j = dst_cnt; j > 0; j--)
			{
				src_color = *src++;
				INTEL_SWAP32(src_color);

				alpha = (src_color >> 24) & 0x000000ffL;
				*merge_buf++ += alpha;
				*merge_buf++ += ((src_color >> 16) & 0x000000ffL) * alpha;
				*merge_buf++ += ((src_color >> 8) & 0x000000ffL) * alpha;
				*merge_buf++ += (src_color & 0x000000ffL) * alpha;
			}
		}

		dst = (UInt32*) ((UChar*) dst + dst_length);
		line_cnt++;	// number of lines

		while (dst_cnt > 0)
		{
			merge_buf -= 4;

			alpha = merge_buf[0];												// sum of alphas
			dst_word = (alpha / line_cnt) << 24;				// alpha

			if (alpha)																	// component values different from zero?
			{
				dst_word |= (merge_buf[1] / alpha) << 16;	// red
				dst_word |= (merge_buf[2] / alpha) << 8;	// green
				dst_word |= (merge_buf[3] / alpha);				// blue
			}

			INTEL_SWAP32(dst_word);
			*(--dst) = dst_word;
			dst_cnt--;
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (48 bits, 3 components)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_RGB48_RGB48(Int32 line_cnt, Int32 dst_cnt,
																Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																PIX_W* src, PIX_W* dst)
{
	Int32	shifts;

	src += src_bit_offset >> 4;	// pointer to the first source pixel
	dst_cnt++;

	if (line_cnt == 0)
	{
		UInt32* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		merge_buf = (UInt32*) (((UChar*) dst) + dst_length - (dst_cnt << 2));
		dst = (PIX_W*) merge_buf;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *(UInt32*) src;
			src += 2;
			dst_cnt--;
		}
	}
	else
	{
		UInt32* merge_buf;
		Int32		i;
		Int32		j;

		// we have to adjust dst_cnt and src_line_offset because they
		// count in 4-byte-words -> convert to 6-byte counter

		src_line_offset += dst_cnt << 2;	// width of the source line
		dst_cnt = (dst_cnt << 2) / 6;			// number of destination pixels
		src_line_offset -= dst_cnt * 6;		// now the offset to the next source line refers to pixels and not to (quad-)words

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (UInt32*) dst;

		for (j = dst_cnt; j > 0; j--)
		{
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
		}

		for (i = line_cnt - 1; i >= 0; i--)									// add the following lines
		{
			src = (PIX_W*) ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (UInt32*) dst;

			for (j = dst_cnt; j > 0; j--)
			{
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
			}
		}

		dst += dst_length;	// pointer behind the buffer
		dst -= dst_cnt & 1;	// adjust the address if the number of pixels is odd (means: align the start address)

		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)
		{
			while (dst_cnt > 0)
			{
				*(--dst) = (PIX_W) (*(--merge_buf) >> shifts);	// blue
				*(--dst) = (PIX_W) (*(--merge_buf) >> shifts);	// green
				*(--dst) = (PIX_W) (*(--merge_buf) >> shifts);	// red
				dst_cnt--;
			}
		}
		else
		{
			line_cnt++;

			while (dst_cnt > 0)
			{
				*(--dst) = (PIX_W) (*(--merge_buf) / line_cnt);		// blue
				*(--dst) = (PIX_W) (*(--merge_buf) / line_cnt);		// green
				*(--dst) = (PIX_W)  (*(--merge_buf) / line_cnt);	// red
				dst_cnt--;
			}
		}
	}
	return (UInt32*) dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (16 bits, 1 component)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_G16_G16(Int32 line_cnt, Int32 dst_cnt,
														Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
														PIX_W* src, PIX_W* dst)
{
	Int32	shifts;

	(void) src_bits;

	src += src_bit_offset >> 4;	// pointer to the first source word
	dst_cnt++;

	if (line_cnt == 0)	// only one line?
	{
		UInt32* merge_buf;

		dst = (PIX_W*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = (UInt32*) dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *((UInt32*) src);
			src += 2;
			dst_cnt--;
		}
	}
	else	// multiple lines
	{
		UInt32* merge_buf;
		Int32		i;
		Int32		j;

		if (line_cnt > 255)
			line_cnt = 255;		// limit that to 256 lines (no details anymore - really .-)

		merge_buf = (UInt32*) dst;
		dst_cnt <<= 1;	// # of destination pixels

		for (j = dst_cnt; j > 0; j--)
			*merge_buf++ = *src++;

		for (i = line_cnt - 1; i >= 0; i--)									// add the following lines
		{
			src = (PIX_W*) ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (UInt32*) dst;

			for (j = dst_cnt; j > 0; j--)
				*merge_buf++ += *src++;
		}

		dst = (PIX_W*) ((UChar*) dst + dst_length);	// points behind the buffer
		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)	// 2^n lines?
		{
			while (dst_cnt > 0)
			{
				*(--dst) = (PIX_W) (*(--merge_buf) >> shifts);
				dst_cnt--;
			}
		}
		else					// use division
		{
			line_cnt++;	// number of lines

			while (dst_cnt > 0)
			{
				*(--dst) = (PIX_W) (*(--merge_buf) / line_cnt);
				dst_cnt--;
			}
		}
	}
	return (UInt32*) dst;	// pointer to the merged line
}

PIX_F* merge_lines_G32_G32(Int32 line_cnt, Int32 dst_cnt,
													 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
													 PIX_F* src, PIX_F* dst)
{
	(void) src_bits;

	src += (src_bit_offset >> 5);	// pointer to the first source word
	dst_cnt++;

	if (line_cnt == 0)	// only one line?
	{
		PIX_F* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (PIX_F*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else	// multiple lines
	{
		PIX_F* merge_buf;
		PIX_F	 multiplier;
		Int32	 i;
		Int32	 j;

		if (line_cnt > 255)
			line_cnt = 255;		// limit that to 256 lines (no details anymore - really .-)

		merge_buf = (PIX_F*) dst;

		for (j = dst_cnt; j > 0; j--)
			*merge_buf++ = *src++;

		for (i = line_cnt - 1; i >= 0; i--)									// add the following lines
		{
			src = (PIX_F*) ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (PIX_F*) dst;

			for (j = dst_cnt; j > 0; j--)
				*merge_buf++ += *src++;
		}

		dst = (PIX_F*) ((UChar*) dst + dst_length);
		multiplier = 1.0f / (line_cnt + 1);

		while (dst_cnt > 0)
		{
			*(--dst) = *(--merge_buf) * multiplier;
			dst_cnt--;
		}
	}
	return dst;	// pointer to the merged line
}

//----------------------------------------------------------------------------------------
// Merge lines (32 bits, 2 independent components)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_AB32_AB32(Int32 line_cnt, Int32 dst_cnt,
															Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
															UInt32* src, UInt32* dst)
{
	UInt32 src_color;
	UInt32 dst_word;
	Int32	 shifts;

	(void) src_bits;

	src += src_bit_offset >> 5;
	dst_cnt++;

	if (line_cnt == 0)
	{
		UInt32* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (UInt32*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else
	{
		UInt32* merge_buf;
		Int32		i;
		Int32		j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (UInt32*) dst;

		for (j = dst_cnt; j > 0; j--)
		{
			src_color = *src++;
			INTEL_SWAP32(src_color);
			*merge_buf++ = (src_color >> 16) & 0x0000ffffL;
			*merge_buf++ = src_color & 0x0000ffffL;
		}

		for (i = line_cnt - 1; i >= 0; i--)
		{
			src = (UInt32*) ((UChar*) src + src_line_offset);
			merge_buf = (UInt32*) dst;

			for (j = dst_cnt; j > 0; j--)
			{
				src_color = *src++;
				INTEL_SWAP32(src_color);
				*merge_buf++ += (src_color >> 16) & 0x0000ffffL;
				*merge_buf++ += src_color & 0x0000ffffL;
			}
		}

		dst = (UInt32*) ((UChar*) dst + dst_length);

		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)
		{
			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) * (--merge_buf) >> shifts;
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 16;
				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;

				dst_cnt--;
			}
		}
		else
		{
			line_cnt++;

			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) (*(--merge_buf) / line_cnt);
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 16;
				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;

				dst_cnt--;
			}
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (64 bits, 2 independent components)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
PIX_F* merge_lines_AB64_AB64(Int32 line_cnt, Int32 dst_cnt,
														 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
														 PIX_F* src, PIX_F* dst)
{
	(void) src_bits;

	src += src_bit_offset >> 5;	// pointer to the first source word
	dst_cnt++;

	if (line_cnt == 0)	// single line?
	{
		PIX_F* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (PIX_F*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			dst_cnt -= 2;
		}
	}
	else
	{
		PIX_F* merge_buf;
		PIX_F	 multiplier;
		Int32	 i;
		Int32	 j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (PIX_F*) dst;

		for (j = dst_cnt; j > 0; j -= 2)
		{
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
		}

		for (i = line_cnt - 1; i >= 0; i--)									// add the following lines
		{
			src = (PIX_F*) ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (PIX_F*) dst;

			for (j = dst_cnt; j > 0; j -= 2)
			{
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;

			}
		}

		dst = (PIX_F*) ((UChar*) dst + dst_length);
		multiplier = 1.0f / (line_cnt + 1);

		while (dst_cnt > 0)
		{
			*(--dst) = *(--merge_buf) * multiplier;
			*(--dst) = *(--merge_buf) * multiplier;
			dst_cnt -= 2;
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (32 bits, 2 components, first one is alpha)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_AG32_AG32(Int32 line_cnt, Int32 dst_cnt,
															Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
															UInt32* src, UInt32* dst)
{
	UInt32 src_color;
	UInt32 dst_word;

	(void) src_bits;

	src += src_bit_offset >> 5;	// pointer to the first source word
	dst_cnt++;

	if (line_cnt == 0)	// single line?
	{
		UInt32* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (UInt32*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else
	{
		Int64* merge_buf;
		Int32	 i;
		Int32	 j;
		UInt32 alpha;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (Int64*) dst;

		for (j = dst_cnt; j > 0; j--)
		{
			src_color = *src++;
#if GE_LITTLE_ENDIAN
			alpha = src_color & 0x0000ffffUL;
			*merge_buf++ = alpha;
			*merge_buf++ = ((src_color >> 16) & 0x0000ffffUL) * alpha;
#else
			alpha = (src_color >> 16) & 0x0000ffffUL;
			*merge_buf++ = alpha;
			*merge_buf++ = (src_color & 0x0000ffffUL) * alpha;
#endif
		}

		for (i = line_cnt - 1; i >= 0; i--)									// add the following lines
		{
			src = (UInt32*) ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (Int64*) dst;

			for (j = dst_cnt; j > 0; j--)
			{
				src_color = *src++;
#if GE_LITTLE_ENDIAN
				alpha = src_color & 0x0000ffffUL;
				*merge_buf++ += alpha;
				*merge_buf++ += ((src_color >> 16) & 0x0000ffffUL) * alpha;
#else
				alpha = (src_color >> 16) & 0x0000ffffUL;
				*merge_buf++ += alpha;
				*merge_buf++ += (src_color & 0x0000ffffUL) * alpha;
#endif
			}
		}

		dst = (UInt32*) ((UChar*) dst + dst_length);
		line_cnt++;	// number of lines

		while (dst_cnt > 0)
		{
			merge_buf -= 2;

			alpha = (UInt32) merge_buf[0];													// sum of alphas
#if GE_LITTLE_ENDIAN
			dst_word = alpha / line_cnt;														// alpha

			if (alpha)																							// component values different from zero?
				dst_word |= ((UInt32) (merge_buf[1] / alpha)) << 16;	// gray
#else
			dst_word = (alpha / line_cnt) << 16;										// alpha

			if (alpha)																							// component values different from zero?
				dst_word |= (UInt32) (merge_buf[1] / alpha);					// gray
#endif

			*(--dst) = dst_word;

			dst_cnt--;
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (64 bits, 2 components, first one is alpha)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
PIX_F* merge_lines_AG64_AG64(Int32 line_cnt, Int32 dst_cnt,
														 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
														 PIX_F* src, PIX_F* dst)
{
	(void) src_bits;

	src += src_bit_offset >> 5;	// pointer to the first source word
	dst_cnt++;

	if (line_cnt == 0)	// single line?
	{
		PIX_F* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (PIX_F*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			dst_cnt -= 2;
		}
	}
	else
	{
		PIX_F* merge_buf;
		PIX_F	 multiplier;
		PIX_F	 alpha;
		Int32	 i;
		Int32	 j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (PIX_F*) dst;

		for (j = dst_cnt; j > 0; j -= 2)
		{
			alpha = *src++;
			*merge_buf++ = alpha;
			*merge_buf++ = *src++ *alpha;
		}

		for (i = line_cnt - 1; i >= 0; i--)									// add the following lines
		{
			src = (PIX_F*) ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (PIX_F*) dst;

			for (j = dst_cnt; j > 0; j -= 2)
			{
				alpha = *src++;
				*merge_buf++ += alpha;
				*merge_buf++ += *src++ *alpha;
			}
		}

		dst = (PIX_F*) ((UChar*) dst + dst_length);
		multiplier = 1.0f / (line_cnt + 1);

		while (dst_cnt > 0)
		{
			PIX_F	c;

			merge_buf -= 2;

			alpha = merge_buf[0];	// alpha sum
			c = 0;
			if (alpha > 0.0)			// component values different from zero?
				c = merge_buf[1] / alpha;

			*(--dst) = c;
			*(--dst) = alpha * multiplier;

			dst_cnt -= 2;
		}
	}
	return dst;
}


//----------------------------------------------------------------------------------------
// Merge lines (64 bits, 3 components a 16 bits)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1 (is a multiple of 2 in this case ... minus 1 of course!)
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_xRGB48_xRGB48(Int32 line_cnt, Int32 dst_cnt,
																	Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	UInt32* src, UInt32* dst)
{
	UInt32 src_color;
	UInt32 dst_word;
	Int32	 shifts;

	(void) src_bits;

	src += src_bit_offset >> 5;
	dst_cnt++;

	if (line_cnt == 0)
	{
		UInt32* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst	 = (UInt32*) ((UChar*) dst + dst_length);
		dst -= dst_cnt;
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else
	{
		UInt32* merge_buf;
		Int32		i;
		Int32		j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (UInt32*) dst;

		for (j = dst_cnt; j > 0; j -= 2)
		{
			src_color = *src++;
			INTEL_SWAP32(src_color);
			*merge_buf++ = 0;
			*merge_buf++ = src_color & 0x0000ffffL;

			src_color = *src++;
			INTEL_SWAP32(src_color);
			*merge_buf++ = (src_color >> 16) & 0x0000ffffL;
			*merge_buf++ = src_color & 0x0000ffffL;
		}

		for (i = line_cnt - 1; i >= 0; i--)
		{
			src = (UInt32*) ((UChar*) src + src_line_offset);
			merge_buf = (UInt32*) dst;

			for (j = dst_cnt; j > 0; j -= 2)
			{
				src_color = *src++;
				INTEL_SWAP32(src_color);
				merge_buf++;
				*merge_buf++ += src_color & 0x0000ffffL;

				src_color = *src++;
				INTEL_SWAP32(src_color);
				*merge_buf++ += (src_color >> 16) & 0x0000ffffL;
				*merge_buf++ += src_color & 0x0000ffffL;
			}
		}

		dst = (UInt32*) ((UChar*) dst + dst_length);

		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)
		{
			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) * (--merge_buf) >> shifts;					// blue
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 16;	// green
				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;

				dst_word = (UInt32) * (--merge_buf) >> shifts;	// red
				--merge_buf;
				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;

				dst_cnt -= 2;
			}
		}
		else
		{
			line_cnt++;

			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) (*(--merge_buf) / line_cnt);					// blue
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 16;	// green
				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;

				dst_word = (UInt32) (*(--merge_buf) / line_cnt);	// red
				--merge_buf;
				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;

				dst_cnt -= 2;
			}
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (64 bits, 4 components a 16 bits)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1 (is a multiple of 2 in this case ... minus 1 of course!)
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_CMYK64_CMYK64(Int32 line_cnt, Int32 dst_cnt,
																	Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	UInt32* src, UInt32* dst)
{
	UInt32 src_color;
	UInt32 dst_word;
	Int32	 shifts;

	(void) src_bits;

	src += src_bit_offset >> 5;
	dst_cnt++;

	if (line_cnt == 0)
	{
		UInt32* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (UInt32*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else
	{
		UInt32* merge_buf;
		Int32		i;
		Int32		j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (UInt32*) dst;

		for (j = dst_cnt; j > 0; j -= 2)
		{
			src_color = *src++;
			INTEL_SWAP32(src_color);
			*merge_buf++ = (src_color >> 16) & 0x0000ffffL;
			*merge_buf++ = src_color & 0x0000ffffL;

			src_color = *src++;
			INTEL_SWAP32(src_color);
			*merge_buf++ = (src_color >> 16) & 0x0000ffffL;
			*merge_buf++ = src_color & 0x0000ffffL;
		}

		for (i = line_cnt - 1; i >= 0; i--)
		{
			src = (UInt32*) ((UChar*) src + src_line_offset);
			merge_buf = (UInt32*) dst;

			for (j = dst_cnt; j > 0; j -= 2)
			{
				src_color = *src++;
				INTEL_SWAP32(src_color);
				*merge_buf++ += (src_color >> 16) & 0x0000ffffL;
				*merge_buf++ += src_color & 0x0000ffffL;

				src_color = *src++;
				INTEL_SWAP32(src_color);
				*merge_buf++ += (src_color >> 16) & 0x0000ffffL;
				*merge_buf++ += src_color & 0x0000ffffL;
			}
		}

		dst = (UInt32*) ((UChar*) dst + dst_length);

		shifts = cnt_to_shifts[line_cnt];

		if (shifts >= 0)
		{
			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) * (--merge_buf) >> shifts;					// black
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 16;	// yellow
				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;

				dst_word	= (UInt32) * (--merge_buf) >> shifts;					// magenta
				dst_word |= ((UInt32) * (--merge_buf) >> shifts) << 16;	// cyan
				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;

				dst_cnt -= 2;
			}
		}
		else
		{
			line_cnt++;

			while (dst_cnt > 0)
			{
				dst_word	= (UInt32) (*(--merge_buf) / line_cnt);					// black
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 16;	// yellow
				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;

				dst_word	= (UInt32) (*(--merge_buf) / line_cnt);					// magenta
				dst_word |= ((UInt32) (*(--merge_buf) / line_cnt)) << 16;	// cyan
				INTEL_SWAP32(dst_word);
				*(--dst) = dst_word;

				dst_cnt -= 2;
			}
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (64 bits, 4 components, first one is alpha)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1 (is a multiple of 2 in this case ... minus 1 of course!)
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
UInt32* merge_lines_ARGB64_ARGB64(Int32 line_cnt, Int32 dst_cnt,
																	Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	UInt32* src, UInt32* dst)
{
	UInt32 src_color;
	UInt32 dst_word;

	(void) src_bits;

	src += src_bit_offset >> 5;	// pointer to the first source word
	dst_cnt++;

	if (line_cnt == 0)	// single line?
	{
		UInt32* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (UInt32*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else
	{
		Int64* merge_buf;
		Int32	 i;
		Int32	 j;
		UInt32 alpha;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (Int64*) dst;

		for (j = dst_cnt; j > 0; j -= 2)
		{
#if GE_LITTLE_ENDIAN
			src_color = *src++;
			alpha = src_color & 0x0000ffffL;
			*merge_buf++ = alpha;
			*merge_buf++ = ((src_color >> 16) & 0x0000ffffL) * alpha;

			src_color = *src++;
			*merge_buf++ = (src_color & 0x0000ffffL) * alpha;
			*merge_buf++ = ((src_color >> 16) & 0x0000ffffL) * alpha;
#else
			src_color = *src++;
			alpha = (src_color >> 16) & 0x0000ffffL;
			*merge_buf++ = alpha;
			*merge_buf++ = (src_color & 0x0000ffffL) * alpha;

			src_color = *src++;
			*merge_buf++ = ((src_color >> 16) & 0x0000ffffL) * alpha;
			*merge_buf++ = (src_color & 0x0000ffffL) * alpha;
#endif
		}

		for (i = line_cnt - 1; i >= 0; i--)									// add the following lines
		{
			src = (UInt32*) ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (Int64*) dst;

			for (j = dst_cnt; j > 0; j -= 2)
			{
#if GE_LITTLE_ENDIAN
				src_color = *src++;
				alpha = src_color & 0x0000ffffL;
				*merge_buf++ += alpha;
				*merge_buf++ += ((src_color >> 16) & 0x0000ffffL) * alpha;

				src_color = *src++;
				*merge_buf++ += (src_color & 0x0000ffffL) * alpha;
				*merge_buf++ += ((src_color >> 16) & 0x0000ffffL) * alpha;
#else
				src_color = *src++;
				alpha = (src_color >> 16) & 0x0000ffffL;
				*merge_buf++ += alpha;
				*merge_buf++ += (src_color & 0x0000ffffL) * alpha;

				src_color = *src++;
				*merge_buf++ += ((src_color >> 16) & 0x0000ffffL) * alpha;
				*merge_buf++ += (src_color & 0x0000ffffL) * alpha;
#endif
			}
		}

		dst = (UInt32*) ((UChar*) dst + dst_length);
		line_cnt++;	// number of lines

		while (dst_cnt > 0)
		{
			merge_buf -= 4;

			alpha = (UInt32) merge_buf[0];	// sum of alphas

#if GE_LITTLE_ENDIAN
			if (alpha)																							// component values different from zero?
			{
				dst_word	= (UInt32) (merge_buf[2] / alpha);					// green
				dst_word |= ((UInt32) (merge_buf[3] / alpha)) << 16;	// blue
				*(--dst)	= dst_word;

				dst_word = ((UInt32) (merge_buf[1] / alpha)) << 16;	// red
			}
			else
			{
				*(--dst) = 0;
				dst_word = 0;
			}

			dst_word |= alpha / line_cnt;														// alpha
#else
			if (alpha)																							// component values different from zero?
			{
				dst_word	= ((UInt32) (merge_buf[2] / alpha)) << 16;	// green
				dst_word |= (UInt32) (merge_buf[3] / alpha);					// blue
				*(--dst)	= dst_word;

				dst_word = (UInt32) (merge_buf[1] / alpha);	// red
			}
			else
			{
				*(--dst) = 0;
				dst_word = 0;
			}

			dst_word |= (alpha / line_cnt) << 16;	// alpha
#endif
			*(--dst) = dst_word;

			dst_cnt -= 2;
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (96 bits, 3 components a 32 bits float)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1 (is a multiple of 3 in this case ... minus 1 of course!)
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
PIX_F* merge_lines_RGB96_RGB96(Int32 line_cnt, Int32 dst_cnt,
															 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
															 PIX_F* src, PIX_F* dst)
{
	(void) src_bits;

	src += src_bit_offset >> 5;
	dst_cnt++;

	if (line_cnt == 0)
	{
		PIX_F* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (PIX_F*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			dst_cnt--;
		}
	}
	else
	{
		PIX_F* merge_buf;
		PIX_F	 multiplier;
		Int32	 i;
		Int32	 j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (PIX_F*) dst;

		for (j = dst_cnt; j > 0; j -= 3)
		{
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
		}

		for (i = line_cnt - 1; i >= 0; i--)
		{
			src = (PIX_F*) ((UChar*) src + src_line_offset);
			merge_buf = (PIX_F*) dst;

			for (j = dst_cnt; j > 0; j -= 3)
			{
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
			}
		}

		dst = (PIX_F*) ((UChar*) dst + dst_length);
		multiplier = 1.0f / (line_cnt + 1);

		while (dst_cnt > 0)
		{
			*(--dst) = *(--merge_buf) * multiplier;	// blue
			*(--dst) = *(--merge_buf) * multiplier;	// green
			*(--dst) = *(--merge_buf) * multiplier;	// red
			dst_cnt -= 3;
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (128 bits, 3 components a 32 bits float)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1 (is a multiple of 4 in this case ... minus 1 of course!)
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
PIX_F* merge_lines_xRGB96_xRGB96(Int32 line_cnt, Int32 dst_cnt,
																 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																 PIX_F* src, PIX_F* dst)
{
	(void) src_bits;

	src += src_bit_offset >> 5;
	dst_cnt++;

	if (line_cnt == 0)
	{
		PIX_F* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (PIX_F*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			dst_cnt -= 4;
		}
	}
	else
	{
		PIX_F* merge_buf;
		PIX_F	 multiplier;
		Int32	 i;
		Int32	 j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (PIX_F*) dst;

		for (j = dst_cnt; j > 0; j -= 4)
		{
			src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
		}

		for (i = line_cnt - 1; i >= 0; i--)
		{
			src = (PIX_F*) ((UChar*) src + src_line_offset);
			merge_buf = (PIX_F*) dst;

			for (j = dst_cnt; j > 0; j -= 4)
			{
				src++;
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
			}
		}

		dst = (PIX_F*) ((UChar*) dst + dst_length);
		multiplier = 1.0f / (line_cnt + 1);

		while (dst_cnt > 0)
		{
			*(--dst) = *(--merge_buf) * multiplier;	// blue
			*(--dst) = *(--merge_buf) * multiplier;	// green
			*(--dst) = *(--merge_buf) * multiplier;	// red
			*(--dst) = 0;
			dst_cnt -= 4;
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (128 bits, 4 components a 32 bits float)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1 (is a multiple of 4 in this case ... minus 1 of course!)
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
PIX_F* merge_lines_CMYK128_CMYK128(Int32 line_cnt, Int32 dst_cnt,
																	 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	 PIX_F* src, PIX_F* dst)
{
	(void) src_bits;

	src += src_bit_offset >> 5;
	dst_cnt++;

	if (line_cnt == 0)
	{
		PIX_F* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (PIX_F*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			dst_cnt -= 4;
		}
	}
	else
	{
		PIX_F* merge_buf;
		PIX_F	 multiplier;
		Int32	 i;
		Int32	 j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (PIX_F*) dst;

		for (j = dst_cnt; j > 0; j -= 4)
		{
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
		}

		for (i = line_cnt - 1; i >= 0; i--)
		{
			src = (PIX_F*) ((UChar*) src + src_line_offset);
			merge_buf = (PIX_F*) dst;

			for (j = dst_cnt; j > 0; j -= 4)
			{
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
				*merge_buf++ += *src++;
			}
		}

		dst = (PIX_F*) ((UChar*) dst + dst_length);
		multiplier = 1.0f / (line_cnt + 1);

		while (dst_cnt > 0)
		{
			*(--dst) = *(--merge_buf) * multiplier;	// black
			*(--dst) = *(--merge_buf) * multiplier;	// yellow
			*(--dst) = *(--merge_buf) * multiplier;	// magenta
			*(--dst) = *(--merge_buf) * multiplier;	// cyan
			dst_cnt -= 4;
		}
	}
	return dst;
}

//----------------------------------------------------------------------------------------
// Merge lines (32 bits, 4 components, first one is alpha)
// Function result:		-
// line_cnt:					number of lines - 1
// dst_cnt:						number of destination words - 1
// src_bits:					bits per source pixel
// src_bit_offset:		bit offset of the first source pixel to the start of line
// src_line_offset:		offset to the next source line in bytes (assumes that [dst_cnt+1]*4 bytes are read)
// dst_length:				length of the destination buffer in bytes
// src:								source address
// dst:								destination address
//----------------------------------------------------------------------------------------
PIX_F* merge_lines_ARGB128_ARGB128(Int32 line_cnt, Int32 dst_cnt,
																	 Int32 src_bits, Int32 src_bit_offset, Int32 src_line_offset, Int32 dst_length,
																	 PIX_F* src, PIX_F* dst)
{
	(void) src_bits;

	src += src_bit_offset >> 5;	// pointer to the first source word
	dst_cnt++;

	if (line_cnt == 0)	// single line?
	{
		PIX_F* merge_buf;

		// the source line will be copied to the end of the scale buffer to avoid
		// overwritten data in the following shrink or scale function that operates
		// on the same buffer

		dst = (PIX_F*) ((UChar*) dst + dst_length - (dst_cnt << 2));
		merge_buf = dst;

		while (dst_cnt > 0)
		{
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			*merge_buf++ = *src++;
			dst_cnt -= 4;
		}
	}
	else
	{
		PIX_F* merge_buf;
		PIX_F	 multiplier;
		PIX_F	 alpha;
		Int32	 i;
		Int32	 j;

		if (line_cnt > 255)
			line_cnt = 255;

		merge_buf = (PIX_F*) dst;

		for (j = dst_cnt; j > 0; j -= 4)
		{
			alpha = *src++;
			*merge_buf++ = alpha;
			*merge_buf++ = *src++ *alpha;
			*merge_buf++ = *src++ *alpha;
			*merge_buf++ = *src++ *alpha;
		}

		for (i = line_cnt - 1; i >= 0; i--)									// add the following lines
		{
			src = (PIX_F*) ((UChar*) src + src_line_offset);	// next source line
			merge_buf = (PIX_F*) dst;

			for (j = dst_cnt; j > 0; j -= 4)
			{
				alpha = *src++;
				*merge_buf++ += alpha;
				*merge_buf++ += *src++ *alpha;
				*merge_buf++ += *src++ *alpha;
				*merge_buf++ += *src++ *alpha;
			}
		}

		dst = (PIX_F*) ((UChar*) dst + dst_length);
		multiplier = 1.0f / (line_cnt + 1);

		while (dst_cnt > 0)
		{
			PIX_F	invers_alpha;

			merge_buf -= 4;

			alpha = merge_buf[0];	// alpha sum
			invers_alpha = 0;
			if (alpha > 0.0)			// component values different from zero?
				invers_alpha = 1.0f / alpha;

			*(--dst) = merge_buf[3] * invers_alpha;	// blue
			*(--dst) = merge_buf[2] * invers_alpha;	// green
			*(--dst) = merge_buf[1] * invers_alpha;	// red
			*(--dst) = alpha * multiplier;

			dst_cnt -= 4;
		}
	}
	return dst;
}
