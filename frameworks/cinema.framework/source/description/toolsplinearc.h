#ifndef TOOLSPLINEARC_H__
#define TOOLSPLINEARC_H__

enum
{
	MDATA_GUIGROUP									= 902,
	MDATA_NUMERICGROUP							=	903,

	MDATA_SPLINEARC_MODE						= 1100, // INTEGER
		MDATA_SPLINEARC_MODE_THREEPOINT					= 0,		//Three point arc
		MDATA_SPLINEARC_MODE_CENTEREDGE					=	1,		//Center than outside/angles
		MDATA_SPLINEARC_MODE_LINE								= 2,		//Described as the hyperbole between two intersecting lines

	MDATA_SPLINEARC_FIRSTPOINT			=	1101, // VECTOR
	MDATA_SPLINEARC_MIDPOINT				= 1102, // VECTOR
	MDATA_SPLINEARC_ENDPOINT				= 1103, // VECTOR
	MDATA_SPLINEARC_CENTER					= 1104, // VECTOR
	MDATA_SPLINEARC_RADIUS					= 1105, // FLOAT
	MDATA_SPLINEARC_ANGLE						= 1106, // FLOAT
	MDATA_SPLINEARC_FULLCIRCLE			= 1107, // BOOLEAN

	MDATA_SPLINEARC_HYPERBOLICLINES	=	1150, // BOOLEAN
	MDATA_SPLINEARC_ROTATEPOINT			=	1151, // INTEGER
		MDATA_SPLINEARC_ROTATEPOINT_CENTER		=	0,		//Rotate around the center point
		MDATA_SPLINEARC_ROTATEPOINT_FIRST			= 1,		//Rotate around the first arc point
		MDATA_SPLINEARC_ROTATEPOINT_MIDDLE		=	2,		//Rotate around the middle arc point
		MDATA_SPLINEARC_ROTATEPOINT_LAST			= 3,		//Rotate around the last arc point

		MDATA_SPLINEARC_POINTINDEX1		= 1200,	// INTEGER (HIDDEN)
		MDATA_SPLINEARC_OBJECT1				= 1201, // BASELINK (HIDDEN)
		MDATA_SPLINEARC_POINTINDEX2		= 1202,	// INTEGER (HIDDEN)
		MDATA_SPLINEARC_OBJECT2				= 1203, // BASELINK (HIDDEN)

	MDATA_SPLINEARC_ACTIVEFIRST			=	1205,	// BOOL (HIDDEN)
	MDATA_SPLINEARC_ACTIVEMID				=	1206,	// BOOL (HIDDEN)
	MDATA_SPLINEARC_ACTIVEEND				=	1207,	// BOOL (HIDDEN)
	MDATA_SPLINEARC_ACTIVECENTER		=	1208,	// BOOL (HIDDEN)

	MDATA_SPLINEARC_PLANE						= 1220	// MATRIX (HIDDEN)
};

#endif // TOOLSPLINEARC_H__
