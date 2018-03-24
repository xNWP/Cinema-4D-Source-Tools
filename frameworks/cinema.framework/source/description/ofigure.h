#ifndef OFIGURE_H__
#define OFIGURE_H__

enum
{
	PRIM_FIGURE_HEIGHT									= 1210, // REAL     - Height [>=0.0]
	PRIM_FIGURE_SUB											= 1211, // LONG     - Subdivision [>2]
	PRIM_FIGURE_LEGACY_AXIS_MODE				= 1212	// BOOL			- R18 Legacy Axis. true: legacy axis (at figure center), false: R18 axis (at figure feet)
};

#endif // OFIGURE_H__
