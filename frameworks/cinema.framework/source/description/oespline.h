#ifndef OESPLINE_H__
#define OESPLINE_H__

enum
{
	//groups
	MGSPLINEEFFECTOR_GROUPPARAMETER					= 990,
	MGSPLINEEFFECTOR_GROUPEFFECTOR					= 991,

	//subgroups
	MGSPLINEEFFECTOR_GROUPTRANSFORM					= 995,

	//------------------------------
	//Effector controls
	MGSPLINEEFFECTOR_STRENGTH								= 1000,

	//-------------------------------
	//Parameter controls
	MGSPLINEEFFECTOR_TRANSFORMMODE					= 1016,
	MGSPLINEEFFECTOR_TRANSFORMMODE_RELATIVE = 0,
	MGSPLINEEFFECTOR_TRANSFORMMODE_ABSOLUTE = 1,
	MGSPLINEEFFECTOR_TRANSFORMMODE_RELSPLINE = 2,

	//------------------------------
	MGSPLINEEFFECTOR_POSITION_ACTIVE				= 1060,
	MGSPLINEEFFECTOR_ROTATION_ACTIVE				= 1062,
	MGSPLINEEFFECTOR_ROTATION								= 1068,
	MGSPLINEEFFECTOR_SPLINE									= 1100,
	MGSPLINEEFFECTOR_OFFSET									= 1102,
	MGSPLINEEFFECTOR_START									= 1103,
	MGSPLINEEFFECTOR_END										= 1104,
	MGSPLINEEFFECTOR_CLAMP									= 1105,
	MGSPLINEEFFECTOR_OFFSETMODE							= 1106,
	MGSPLINEEFFECTOR_OFFSETMODE_STEP				= 0,
	MGSPLINEEFFECTOR_OFFSETMODE_FALLOFF			= 1,
	MGSPLINEEFFECTOR_OFFSETMODE_RELATIVE		= 2,
	MGSPLINEEFFECTOR_FALLOFFSTRENGTH				= 1107,
	MGSPLINEEFFECTOR_SEGMENTMODE						= 1108,
	MGSPLINEEFFECTOR_SEGMENTMODE_INDEX			= 0,
	MGSPLINEEFFECTOR_SEGMENTMODE_OFFSET			= 1,
	MGSPLINEEFFECTOR_SEGMENTMODE_RANDOM			= 2,
	MGSPLINEEFFECTOR_SEGMENTMODE_SPACED			= 3,
	MGSPLINEEFFECTOR_SEGMENTINDEX						= 1109,
	MGSPLINEEFFECTOR_SEGMENTSEED						= 1110,
	MGSPLINEEFFECTOR_RELATIVEAXIS						= 1111,
	MGSPLINEEFFECTOR_RELATIVEAXIS_X					= 0,
	MGSPLINEEFFECTOR_RELATIVEAXIS_Y					= 1,
	MGSPLINEEFFECTOR_RELATIVEAXIS_Z					= 2,
	MGSPLINEEFFECTOR_RELATIVEAXIS_XNEG			= 3,
	MGSPLINEEFFECTOR_RELATIVEAXIS_YNEG			= 4,
	MGSPLINEEFFECTOR_RELATIVEAXIS_ZNEG			= 5,
	MGSPLINEEFFECTOR_RAIL_SPLINE						= 1112,
	MGSPLINEEFFECTOR_TARGET_RAIL						=	1113,
	MGSPLINEEFFECTOR_UP_VECTOR							=	1114
};
#endif // OESPLINE_H__
