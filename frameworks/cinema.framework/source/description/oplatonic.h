#ifndef OPLATONIC_H__
#define OPLATONIC_H__

enum
{
	PRIM_PLATONIC_RAD					= 1120, // REAL	   - Outer Radius	[>=0.0]
	PRIM_PLATONIC_SUB					= 1121, // LONG     - Subdivision [>=0]
	PRIM_PLATONIC_TYPE				= 1122,	// LONG     - Type [0:Tetra; 1:Hexa; 2:Octa; 3:Dodeca; 4:Icosa; 5:Bucky]
		PRIM_PLATONIC_TYPE_TETRA		= 0,
		PRIM_PLATONIC_TYPE_HEXA			= 1,
		PRIM_PLATONIC_TYPE_OCTA			= 2,
		PRIM_PLATONIC_TYPE_DODECA		= 3,
		PRIM_PLATONIC_TYPE_ICOSA		= 4,
		PRIM_PLATONIC_TYPE_BUCKY		= 5
};

#endif // OPLATONIC_H__
