/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef MATRIXUTIL_H__
#define MATRIXUTIL_H__

#include "x4d_filter.h"

struct WEIGHT_FMATRIX
{
	Int32		no_matrix_columns;
	Int32		no_matrix_rows;
	Int32		x_origin;
	Int32		y_origin;
	Float32	matrix_values[VARIABLE_ARRAY_SIZE];
};

#define	MAXTRIX_MAX_COLUMNS	15	// maximum number of maxtrix columns
#define	MAXTRIX_MAX_ROWS		15	// maximum number of maxtrix rows

struct WEIGHT_FMATRIX_3x3
{
	Int32		no_matrix_columns;
	Int32		no_matrix_rows;
	Int32		x_origin;
	Int32		y_origin;
	Float32	matrix_values[3][3];
};

struct WEIGHT_FMATRIX_5x5
{
	Int32		no_matrix_columns;
	Int32		no_matrix_rows;
	Int32		x_origin;
	Int32		y_origin;
	Float32	matrix_values[5][5];
};

struct WEIGHT_FMATRIX_7x7
{
	Int32		no_matrix_columns;
	Int32		no_matrix_rows;
	Int32		x_origin;
	Int32		y_origin;
	Float32	matrix_values[7][7];
};

struct WEIGHT_FMATRIX_MAX
{
	Int32		no_matrix_columns;
	Int32		no_matrix_rows;
	Int32		x_origin;
	Int32		y_origin;
	Float32	matrix_values[MAXTRIX_MAX_COLUMNS * MAXTRIX_MAX_ROWS];
};

typedef void* MATRIX_REF;

extern MATRIX_REF new_effect_matrix(const WEIGHT_FMATRIX* input_matrix, Int32 color_space, UInt32 px_format, Float32 opacity, Bool scale_matrix, Float64 angle);
extern Int32 delete_effect_matrix(MATRIX_REF emr);
extern void update_effect_matrix(MATRIX_REF emr, Int32 color_space, UInt32 px_format);
extern Int32 apply_matrix_effect(MATRIX_REF emr, void** src_rows, void* dst, Int32 width);
extern Int32 get_effect_matrix_info(MATRIX_REF _emr, Int32* no_columns, Int32* no_rows, Int32* x_origin, Int32* y_origin);

#endif // MATRIXUTIL_H__
