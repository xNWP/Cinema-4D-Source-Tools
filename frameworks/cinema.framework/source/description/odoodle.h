#ifndef ODOODLE_H__
#define ODOODLE_H__

enum
{
	DOODLEOBJECT_GROUP_OPTIONS	=	995,
	DOODLEOBJECT_SETBD					= 1000,
	DOODLEOBJECT_BD							= 1001,
	DOODLEOBJECT_IMAGE					= 1002,
	DOODLEOBJECT_ADDIMAGE				= 1003,
	DOODLEOBJECT_DELIMAGE				= 1004,
	DOODLEOBJECT_CLEARFRAME			=	1005,
	DOODLEOBJECT_TITLE					=	1006,
	DOODLEOBJECT_BODY						=	1007,
	DOODLEOBJECT_GHOST_PREV			=	1008,
	DOODLEOBJECT_GHOST_NEXT			=	1009,
	DOODLEOBJECT_SIZE_X					=	1010,
	DOODLEOBJECT_SIZE_Y					=	1011,
	DOODLEOBJECT_LOAD_BITMAP		=	1012,
	DOODLEOBJECT_REMOVE_UNUSED	=	1013,
	DOODLEOBJECT_EXPORT					=	1014,
	DOODLEOBJECT_IMPORT					=	1015,
	DOODLEOBJECT_CURRENTVIEW		=	1016,
	DOODLEOBJECT_SMOOTHVIEW			=	1017,
	DOODLEOBJECT_SAVECOMPRESSED	=	1018,
	DOODLEOBJECT_EXPORT_FORMAT	=	1019,
		DOODLEOBJECT_EXPORT_FORMAT_PNG = 0,
		DOODLEOBJECT_EXPORT_FORMAT_TIF = 1
};

#endif // ODOODLE_H__
