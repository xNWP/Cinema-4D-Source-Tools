#ifndef PREFSCINEMAN_H__
#define PREFSCINEMAN_H__

enum
{
	PREF_CINEMAN_MAIN_GROUP					= 999,
	PREF_CINEMAN_RENDERER						= 1000,
		PREF_CINEMAN_RENDERER_PRMAN						= 0,
		PREF_CINEMAN_RENDERER_AIR							= 2,
		PREF_CINEMAN_RENDERER_3D							= 4,

	PREF_CINEMAN_DIRECTORY					= 1001,
	PREF_CINEMAN_TEMP								= 1002,
		PREF_CINEMAN_TEMP_LCL									= 0,
		PREF_CINEMAN_TEMP_PRJ									= 1,


	PREFS_CINEMAN_DUMMY
};

#endif // PREFSCINEMAN_H__