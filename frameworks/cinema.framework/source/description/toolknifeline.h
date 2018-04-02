#ifndef TOOLKNIFELINE_H__
#define TOOLKNIFELINE_H__

enum
{
	MDATA_KNIFELINE_VISIBLE_ONLY = 4998,			// BOOL
	MDATA_KNIFELINE_SPLIT_MODE,								// LONG
	MDATA_KNIFELINE_SINGLE				= 5001,			// BOOL
	MDATA_KNIFELINE_INFINITE,									// BOOL

	MDATA_KNIFELINE_SELECTED,									// BOOL
	MDATA_KNIFELINE_SELECT_CUT,								// BOOL
	MDATA_KNIFELINE_CUTPOLYS,									// BOOL
	MDATA_KNIFELINE_AUTOSNAP,									// BOOL

	MDATA_KNIFELINE_ANGLE_CONSTRAINT,					// BOOL
	MDATA_KNIFELINE_ANGLE_CONSTRAINT_VALUE,		// REAL

		MDATA_KNIFELINE_SPLIT_MODE_NOSPLIT = 0,
		MDATA_KNIFELINE_SPLIT_MODE_SPLIT,
		MDATA_KNIFELINE_SPLIT_MODE_REGION_A,
		MDATA_KNIFELINE_SPLIT_MODE_REGION_B,

	MDATA_KNIFELINE_
};

#endif // TOOLKNIFELINE_H__