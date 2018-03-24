#include "c4d_general.h"
#include "c4d_shader.h"
#include "c4d_memory.h"

#include	"matrixutil.h"
#include "matrixrotate.h"

typedef	Int32	TYPE_apply_matrix_effect (MATRIX_REF emr, void** src_rows, void* dst, Int32 width);

struct MATRIX_PRIVATE
{

	Int32											color_space;
	Int32											no_components;
	WEIGHT_FMATRIX_MAX				effect_matrix;

	TYPE_apply_matrix_effect* apply_effect;

};

static void	change_effect_matrix(const WEIGHT_FMATRIX* input_matrix, WEIGHT_FMATRIX* effect_matrix, Float32 opacity, Bool scale_matrix, Float64 angle);

static void	matrix_lineC(MATRIX_PRIVATE* emr, PIX_C** src_rows, PIX_C* dst, Int32 width);
static void	matrix_lineW(MATRIX_PRIVATE* emr, PIX_W** src_rows, PIX_W* dst, Int32 width);
static void	matrix_lineF(MATRIX_PRIVATE* emr, PIX_F** src_rows, PIX_F* dst, Int32 width);
static void	matrix_block8_q3(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width);
static void	matrix_block8_q5(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width);
static void	matrix_block8_q7(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width);

static void	matrix_line_alphaC(MATRIX_PRIVATE* emr, PIX_C** src_rows, PIX_C* dst, Int32 width);
static void	matrix_line_alphaW(MATRIX_PRIVATE* emr, PIX_W** src_rows, PIX_W* dst, Int32 width);
static void	matrix_line_alphaF(MATRIX_PRIVATE* emr, PIX_F** src_rows, PIX_F* dst, Int32 width);
static void	matrix_block_alpha8_q3(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width);
static void	matrix_block_alpha8_q5(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width);
static void	matrix_block_alpha8_q7(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width);

//----------------------------------------------------------------------------------------
// Create a matrix object and set up the proper functions
// Function result:		matrix object
// input_matrix:			convolution matrix
// color_space:				color space of the pixel data (used for alpha support, ...)
// px_format:					pixel format (bits per component, number of components, ..)
// opacity:						0.0: result of the convolution is transparent 1.0: result of the convolution completly replaces the source pixel
// scale_matrix:			false: ignore overflows true: scale matrix elements so that the sum is 1.0 (unless they sum to 0)
// angle:							rotation angle of the matrix (0 ... 2pi)
//----------------------------------------------------------------------------------------
MATRIX_REF new_effect_matrix(const WEIGHT_FMATRIX* input_matrix, Int32 color_space, UInt32 px_format, Float32 opacity, Bool scale_matrix, Float64 angle)
{
	MATRIX_PRIVATE* emr;

	ifnoerr (emr = NewMemClear(MATRIX_PRIVATE, 1))
	{
		emr->color_space = color_space;
		emr->no_components = get_PX_CMPNTS(px_format);

		change_effect_matrix(input_matrix, (WEIGHT_FMATRIX*) &emr->effect_matrix, opacity, scale_matrix, angle);

		update_effect_matrix(emr, color_space, px_format);
	}

	return (MATRIX_REF) emr;
}

Int32	delete_effect_matrix(MATRIX_REF emr)
{
	if (emr)
		DeleteMem(emr);

	return 0;
}

void update_effect_matrix(MATRIX_REF t_emr, Int32 color_space, UInt32 px_format)
{
	if (t_emr)
	{
		MATRIX_PRIVATE* emr = (MATRIX_PRIVATE*)t_emr;
		emr->color_space = color_space;
		emr->no_components = get_PX_CMPNTS(px_format);

		switch (get_PX_DEPTH(px_format))
		{
			case PX_DEPTH_8:
				if (color_space & CSPACE_ALPHA_FLAG)	// take care of alpha?
				{
					emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_line_alphaC;
					if (emr->effect_matrix.no_matrix_rows == emr->effect_matrix.no_matrix_columns)	// square matrix?
					{
						switch (emr->effect_matrix.no_matrix_rows)
						{
							case	3:	emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_block_alpha8_q3;	break;
							case	5:	emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_block_alpha8_q5;	break;
							case	7:	emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_block_alpha8_q7;	break;
						}
					}
				}
				else	// color space without alpha
				{
					emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_lineC;
					if (emr->effect_matrix.no_matrix_rows == emr->effect_matrix.no_matrix_columns)	// square matrix?
					{
						switch (emr->effect_matrix.no_matrix_rows)
						{
							case	3:	emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_block8_q3;	break;
							case	5:	emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_block8_q5;	break;
							case	7:	emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_block8_q7;	break;
						}
					}
				}
				break;

			case PX_DEPTH_16:
				if (color_space & CSPACE_ALPHA_FLAG)
					emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_line_alphaW;
				else
					emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_lineW;
				break;

			case PX_DEPTH_32:
				if (color_space & CSPACE_ALPHA_FLAG)
					emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_line_alphaF;
				else
					emr->apply_effect = (TYPE_apply_matrix_effect*) matrix_lineF;
				break;
		}
	}
}


Int32	apply_matrix_effect(MATRIX_REF emr, void** src_rows, void* dst, Int32 width)
{
	if (!((MATRIX_PRIVATE*) emr)->apply_effect)
		return 0;
	((MATRIX_PRIVATE*) emr)->apply_effect(emr, src_rows, dst, width);
	return 0;
}

Int32	get_effect_matrix_info(MATRIX_REF _emr, Int32* no_columns, Int32* no_rows, Int32* x_origin, Int32* y_origin)
{
	MATRIX_PRIVATE* emr;

	emr = (MATRIX_PRIVATE*) _emr;

	if (no_columns)
		*no_columns = emr->effect_matrix.no_matrix_columns;

	if (no_rows)
		*no_rows = emr->effect_matrix.no_matrix_rows;

	if (x_origin)
		*x_origin = emr->effect_matrix.x_origin;

	if (y_origin)
		*y_origin = emr->effect_matrix.y_origin;

	return 0;
}

static void	change_effect_matrix(const WEIGHT_FMATRIX* input_matrix, WEIGHT_FMATRIX* effect_matrix, Float32 opacity, Bool scale_matrix, Float64 angle)
{
#define	MIN_VALUE	0.00001	// cutoff value for scaling

	Int32	no_elements;
	Int32	i;
	Int32	j;
	const Float32* src_value;
	Float32*			 dst_value;
	Float32				 matrix_sum;
	Float32				 v;

	*effect_matrix = *input_matrix;	// copy the header

	src_value	 = input_matrix->matrix_values;
	dst_value	 = effect_matrix->matrix_values;
	matrix_sum = 0;

	for (j = 0; j < effect_matrix->no_matrix_rows; j++)
	{
		for (i = 0; i < effect_matrix->no_matrix_columns; i++)
		{
			v = *src_value++;
			*dst_value++ = v;
			matrix_sum += v;
		}
	}

	if (angle != 0.0)	// rotate matrix?
	{
		rotate_matrix(input_matrix, effect_matrix, angle);

		if (scale_matrix && (matrix_sum >= MIN_VALUE))	// rotation might have produced some rounding errors
		{
			matrix_sum = 0;
			dst_value	 = effect_matrix->matrix_values;	// therefore build the sum again

			for (j = 0; j < effect_matrix->no_matrix_rows; j++)
			{
				for (i = 0; i < effect_matrix->no_matrix_columns; i++)
					matrix_sum += *dst_value++;
			}
		}
	}

	if (scale_matrix)	// scale the matrix to avoid cutting off color values
	{
		if (matrix_sum < 0)
			matrix_sum = -matrix_sum;

		if (matrix_sum < MIN_VALUE)	// avoid division by zero (take rounding errors into account)
			matrix_sum = 1.0;
	}
	else	// no scaling, allow overflow
	{
		matrix_sum = 1.0;
	}

	no_elements = effect_matrix->no_matrix_rows * effect_matrix->no_matrix_columns;
	dst_value = effect_matrix->matrix_values;
	for (i = no_elements; i > 0; i--)	// scale and blend matrix elements
	{
		v = (*dst_value / matrix_sum) * opacity;
		*dst_value++ = v;
	}

	dst_value	 = effect_matrix->matrix_values;
	dst_value += effect_matrix->y_origin * effect_matrix->no_matrix_columns;
	dst_value += effect_matrix->x_origin;
	v = 1.0f - opacity;	// add amount of the source pixel
	*dst_value += v;

	#undef	MIN_MVALUE
}

//----------------------------------------------------------------------------------------
// General matrix handling for pixels with 8 bits per component
// Function result:		-
// emr:								matrix data
// src_rows:					array with pointers to the source lines
// dst:								pointer to the dst line
// no_components:			number of color components per pixel
//----------------------------------------------------------------------------------------
static void	matrix_lineC(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32	c;

		for (c = 0; c < no_components; c++, x_offset++)
		{
			Int32		 my;
			Float32* matrix_values;
			Float32	 n;

			n = 0;
			matrix_values = matrix->matrix_values;

			for (my = 0; my < matrix->no_matrix_rows; my++)
			{
				UChar* src;
				Int32	 mx;

				src = src_rows[my] + x_offset;											// select the right color component

				for (mx = matrix->no_matrix_columns; mx > 0; mx--)	// weigh the components of a source line
				{
					n += *matrix_values++ *(Float32) * src;
					src += no_components;	// next pixel
				}
			}

			if (n < 0.0)	// clamp component if the sum of the matrix elements is not 1.0
				n = 0.0;
			if (n > 255.0)
				n = 255.0;

			*dst++ = (UChar) (n + 0.5);
		}
	}
}

static void	matrix_lineW(MATRIX_PRIVATE* emr, PIX_W** src_rows, PIX_W* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32	c;

		for (c = 0; c < no_components; c++, x_offset++)
		{
			Int32		 my;
			Float32* matrix_values;
			Float32	 n;

			n = 0;
			matrix_values = matrix->matrix_values;

			for (my = 0; my < matrix->no_matrix_rows; my++)
			{
				PIX_W* src;
				Int32	 mx;

				src = src_rows[my] + x_offset;											// select the right color component

				for (mx = matrix->no_matrix_columns; mx > 0; mx--)	// weigh the components of a source line
				{
					n += *matrix_values++ *(Float32) * src;
					src += no_components;	// next pixel
				}
			}

			if (n < 0.0)	// clamp component if the sum of the matrix elements is not 1.0
				n = 0.0;
			if (n > 65535.0)
				n = 65535.0;

			*dst++ = (PIX_W) (n + 0.5);
		}
	}
}

static void	matrix_lineF(MATRIX_PRIVATE* emr, PIX_F** src_rows, PIX_F* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32	c;

		for (c = 0; c < no_components; c++, x_offset++)
		{
			Int32		 my;
			Float32* matrix_values;
			Float32	 n;

			n = 0;
			matrix_values = matrix->matrix_values;

			for (my = 0; my < matrix->no_matrix_rows; my++)
			{
				PIX_F* src;
				Int32	 mx;

				src = src_rows[my] + x_offset;											// select the right color component

				for (mx = matrix->no_matrix_columns; mx > 0; mx--)	// weigh the components of a source line
				{
					n += *matrix_values++ *(Float32) * src;
					src += no_components;	// next pixel
				}
			}

			*dst++ = n;
		}
	}
}

// 3*3 matrix
static void	matrix_block8_q3(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32	c;

		for (c = 0; c < no_components; c++, x_offset++)
		{
			Float32* matrix_values;
			Float32	 n;
			UChar*	 src;

			n = 0;
			matrix_values = matrix->matrix_values;

			src = src_rows[0] + x_offset;						// select the right color component

			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line

			src = src_rows[1] + x_offset;						// next line, select the right color component

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			src = src_rows[2] + x_offset;

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			if (n < 0.0)	// clamp component if the sum of the matrix elements is not 1.0
				n = 0.0;
			if (n > 255.0)
				n = 255.0;

			*dst++ = (UChar) (n + 0.5);
		}
	}
}

// 5*5 matrix
static void	matrix_block8_q5(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32	c;

		for (c = 0; c < no_components; c++, x_offset++)
		{
			Float32* matrix_values;
			Float32	 n;
			UChar*	 src;

			n = 0;
			matrix_values = matrix->matrix_values;

			src = src_rows[0] + x_offset;						// select the right color component

			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line

			src = src_rows[1] + x_offset;						// next line, select the right color component

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			src = src_rows[2] + x_offset;

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			src = src_rows[3] + x_offset;

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			src = src_rows[4] + x_offset;

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			if (n < 0.0)	// clamp component if the sum of the matrix elements is not 1.0
				n = 0.0;
			if (n > 255.0)
				n = 255.0;

			*dst++ = (UChar) (n + 0.5);
		}
	}
}

// 7*7 matrix
static void	matrix_block8_q7(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32	c;

		for (c = 0; c < no_components; c++, x_offset++)
		{
			Float32* matrix_values;
			Float32	 n;
			UChar*	 src;

			n = 0;
			matrix_values = matrix->matrix_values;

			src = src_rows[0] + x_offset;						// select the right color component

			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
			src += no_components;										// next pixel
			n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line

			src = src_rows[1] + x_offset;						// next line, select the right color component

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			src = src_rows[2] + x_offset;

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			src = src_rows[3] + x_offset;

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			src = src_rows[4] + x_offset;

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			src = src_rows[5] + x_offset;

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			src = src_rows[6] + x_offset;

			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;
			src += no_components;
			n += *matrix_values++ *(Float32) * src;

			if (n < 0.0)	// clamp component if the sum of the matrix elements is not 1.0
				n = 0.0;
			if (n > 255.0)
				n = 255.0;

			*dst++ = (UChar) (n + 0.5);
		}
	}
}


//----------------------------------------------------------------------------------------
// Blur line with alpha channel
// Function result:		-
// src_rows:					array with pointers to the source lines
// dst:								pointer to the dst line
// no_components:			number of color components per pixel
// matrix:
//----------------------------------------------------------------------------------------
static void	matrix_line_alphaC(MATRIX_PRIVATE* emr, PIX_C** src_rows, PIX_C* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32		 c;
		Int32		 my;
		Float32* matrix_values;
		Float32	 new_alpha;
		Float32	 n;

		n = 0;
		matrix_values = matrix->matrix_values;

		for (my = 0; my < matrix->no_matrix_rows; my++)
		{
			UChar* src;
			Int32	 mx;

			src = src_rows[my] + x_offset;

			for (mx = matrix->no_matrix_columns; mx > 0; mx--)	// weigh the components of a source line
			{
				n += *matrix_values++ *(Float32) * src;
				src += no_components;	// next pixel
			}
		}

		new_alpha = n;
		if (n < 0.0)	// clamp component if the sum of the matrix elements is not 1.0
			n = 0.0;
		if (n > 255.0)
			n = 255.0;

		*dst++ = (UChar) (n + 0.5);

		if (new_alpha == 0.0)																				// is the matrixred pixel invisible?
			new_alpha = 1.0;																					// avoid division by zero

		for (c = 1, x_offset++; c < no_components; c++, x_offset++)	// weigh every color component with its alpha and matrix value
		{
			n = 0;
			matrix_values = matrix->matrix_values;

			for (my = 0; my < matrix->no_matrix_rows; my++)
			{
				UChar* src;
				UChar* alpha;
				Int32	 mx;

				src = src_rows[my] + x_offset;	// select the right color component
				alpha = src - c;

				for (mx = matrix->no_matrix_columns; mx > 0; mx--)	// weigh the components of a source line
				{
					n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
					alpha += no_components;	// next pixel
					src += no_components;		// next pixel
				}
			}

			n /= new_alpha;	// new color component of the matrixred pixel (has to take the sum of the alphas into account)
			if (n < 0.0)		// clamp component if the sum of the matrix elements is not 1.0
				n = 0.0;
			if (n > 255.0)
				n = 255.0;

			*dst++ = (UChar) (n + 0.5);
		}
	}
}

static void	matrix_line_alphaW(MATRIX_PRIVATE* emr, PIX_W** src_rows, PIX_W* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32		 c;
		Int32		 my;
		Float32* matrix_values;
		Float32	 new_alpha;
		Float32	 n;

		n = 0;
		matrix_values = matrix->matrix_values;

		for (my = 0; my < matrix->no_matrix_rows; my++)
		{
			PIX_W* src;
			Int32	 mx;

			src = src_rows[my] + x_offset;

			for (mx = matrix->no_matrix_columns; mx > 0; mx--)	// weigh the components of a source line
			{
				n += *matrix_values++ *(Float32) * src;
				src += no_components;	// next pixel
			}
		}

		new_alpha = n;
		if (n < 0.0)	// clamp component if the sum of the matrix elements is not 1.0
			n = 0.0;
		if (n > 65535.0)
			n = 65535.0;

		*dst++ = (PIX_W) (n + 0.5);

		if (new_alpha == 0.0)																				// is the matrixred pixel invisible?
			new_alpha = 1.0;																					// avoid division by zero

		for (c = 1, x_offset++; c < no_components; c++, x_offset++)	// weigh every color component with its alpha and matrix value
		{
			n = 0;
			matrix_values = matrix->matrix_values;

			for (my = 0; my < matrix->no_matrix_rows; my++)
			{
				PIX_W* src;
				PIX_W* alpha;
				Int32	 mx;

				src = src_rows[my] + x_offset;	// select the right color component
				alpha = src - c;

				for (mx = matrix->no_matrix_columns; mx > 0; mx--)	// weigh the components of a source line
				{
					n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
					alpha += no_components;	// next pixel
					src += no_components;		// next pixel
				}
			}

			n /= new_alpha;	// new color component of the matrixred pixel (has to take the sum of the alphas into account)
			if (n < 0.0)		// clamp component if the sum of the matrix elements is not 1.0
				n = 0.0;
			if (n > 65535.0)
				n = 65535.0;

			*dst++ = (PIX_W) (n + 0.5);
		}
	}
}

static void	matrix_line_alphaF(MATRIX_PRIVATE* emr, PIX_F** src_rows, PIX_F* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32		 c;
		Int32		 my;
		Float32* matrix_values;
		Float32	 new_alpha;
		Float32	 n;

		n = 0;
		matrix_values = matrix->matrix_values;

		for (my = 0; my < matrix->no_matrix_rows; my++)
		{
			PIX_F* src;
			Int32	 mx;

			src = src_rows[my] + x_offset;

			for (mx = matrix->no_matrix_columns; mx > 0; mx--)	// weigh the components of a source line
			{
				n += *matrix_values++ *(Float32) * src;
				src += no_components;	// next pixel
			}
		}

		new_alpha = n;

		*dst++ = n;

		if (new_alpha == 0.0)																				// is the matrixred pixel invisible?
			new_alpha = 1.0;																					// avoid division by zero

		for (c = 1, x_offset++; c < no_components; c++, x_offset++)	// weigh every color component with its alpha and matrix value
		{
			n = 0;
			matrix_values = matrix->matrix_values;

			for (my = 0; my < matrix->no_matrix_rows; my++)
			{
				PIX_F* src;
				PIX_F* alpha;
				Int32	 mx;

				src = src_rows[my] + x_offset;	// select the right color component
				alpha = src - c;

				for (mx = matrix->no_matrix_columns; mx > 0; mx--)	// weigh the components of a source line
				{
					n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
					alpha += no_components;	// next pixel
					src += no_components;		// next pixel
				}
			}

			n /= new_alpha;	// new color component of the matrixred pixel (has to take the sum of the alphas into account)
			*dst++ = n;
		}
	}
}

// 3*3 matrix
static void	matrix_block_alpha8_q3(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32		 c;
		Float32* matrix_values;
		Float32	 new_alpha;
		Float32	 n;
		UChar*	 src;

		n = 0;
		matrix_values = matrix->matrix_values;

		src = src_rows[0] + x_offset;						// select the right color component

		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line

		src = src_rows[1] + x_offset;						// next line, select the right color component

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		src = src_rows[2] + x_offset;

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		new_alpha = n;
		if (n < 0.0)	// clamp component if the sum of the matrix elements is not 1.0
			n = 0.0;
		if (n > 255.0)
			n = 255.0;

		*dst++ = (UChar) (n + 0.5);

		if (new_alpha == 0.0)																				// is the matrixred pixel invisible?
			new_alpha = 1.0;																					// avoid division by zero

		for (c = 1, x_offset++; c < no_components; c++, x_offset++)	// weigh every color component with its alpha and matrix value
		{
			UChar* alpha;

			n = 0;
			matrix_values = matrix->matrix_values;

			src = src_rows[0] + x_offset;	// select the right color component
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[1] + x_offset;	// next line, select the right color component
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[2] + x_offset;
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			n /= new_alpha;	// new color component of the matrixred pixel (has to take the sum of the alphas into account)
			if (n < 0.0)		// clamp component if the sum of the matrix elements is not 1.0
				n = 0.0;
			if (n > 255.0)
				n = 255.0;

			*dst++ = (UChar) (n + 0.5);
		}
	}
}

// 5*5 matrix
static void	matrix_block_alpha8_q5(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32		 c;
		Float32* matrix_values;
		Float32	 new_alpha;
		Float32	 n;
		UChar*	 src;

		n = 0;
		matrix_values = matrix->matrix_values;

		src = src_rows[0] + x_offset;						// select the right color component

		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line

		src = src_rows[1] + x_offset;						// next line, select the right color component

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		src = src_rows[2] + x_offset;

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		src = src_rows[3] + x_offset;

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		src = src_rows[4] + x_offset;

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		new_alpha = n;
		if (n < 0.0)	// clamp component if the sum of the matrix elements is not 1.0
			n = 0.0;
		if (n > 255.0)
			n = 255.0;

		*dst++ = (UChar) (n + 0.5);

		if (new_alpha == 0.0)																				// is the matrixed pixel invisible?
			new_alpha = 1.0;																					// avoid division by zero

		for (c = 1, x_offset++; c < no_components; c++, x_offset++)	// weigh every color component with its alpha and matrix value
		{
			UChar* alpha;

			n = 0;
			matrix_values = matrix->matrix_values;

			src = src_rows[0] + x_offset;	// select the right color component
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[1] + x_offset;	// next line, select the right color component
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[2] + x_offset;
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[3] + x_offset;
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[4] + x_offset;
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			n /= new_alpha;	// new color component of the matrixred pixel (has to take the sum of the alphas into account)
			if (n < 0.0)		// clamp component if the sum of the matrix elements is not 1.0
				n = 0.0;
			if (n > 255.0)
				n = 255.0;

			*dst++ = (UChar) (n + 0.5);
		}
	}
}

// 7*7 matrix
static void	matrix_block_alpha8_q7(MATRIX_PRIVATE* emr, UChar** src_rows, UChar* dst, Int32 width)
{
	WEIGHT_FMATRIX* matrix;
	Int32	no_components;
	Int32	x_offset;

	no_components = emr->no_components;
	matrix = (WEIGHT_FMATRIX*) &emr->effect_matrix;

	for (x_offset = 0; width > 0; width--)
	{
		Int32		 c;
		Float32* matrix_values;
		Float32	 new_alpha;
		Float32	 n;
		UChar*	 src;

		n = 0;
		matrix_values = matrix->matrix_values;

		src = src_rows[0] + x_offset;						// select the right color component

		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line
		src += no_components;										// next pixel
		n += *matrix_values++ *(Float32) * src;	// weigh the components of a source line

		src = src_rows[1] + x_offset;						// next line, select the right color component

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		src = src_rows[2] + x_offset;

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		src = src_rows[3] + x_offset;

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		src = src_rows[4] + x_offset;

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		src = src_rows[5] + x_offset;

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		src = src_rows[6] + x_offset;

		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;
		src += no_components;
		n += *matrix_values++ *(Float32) * src;

		new_alpha = n;
		if (n < 0.0)	// clamp component if the sum of the matrix elements is not 1.0
			n = 0.0;
		if (n > 255.0)
			n = 255.0;

		*dst++ = (UChar) (n + 0.5);

		if (new_alpha == 0.0)																				// is the matrixred pixel invisible?
			new_alpha = 1.0;																					// avoid division by zero

		for (c = 1, x_offset++; c < no_components; c++, x_offset++)	// weigh every color component with its alpha and matrix value
		{
			UChar* alpha;

			n = 0;
			matrix_values = matrix->matrix_values;

			src = src_rows[0] + x_offset;	// select the right color component
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;	// next pixel
			src += no_components;		// next pixel
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[1] + x_offset;	// next line, select the right color component
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[2] + x_offset;
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[3] + x_offset;
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[4] + x_offset;
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[5] + x_offset;
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			src = src_rows[6] + x_offset;
			alpha = src - c;

			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;
			alpha += no_components;
			src += no_components;
			n += *matrix_values++ *(Float32) * src * (Float32) * alpha;

			n /= new_alpha;	// new color component of the matrixred pixel (has to take the sum of the alphas into account)
			if (n < 0.0)		// clamp component if the sum of the matrix elements is not 1.0
				n = 0.0;
			if (n > 255.0)
				n = 255.0;

			*dst++ = (UChar) (n + 0.5);
		}
	}
}
