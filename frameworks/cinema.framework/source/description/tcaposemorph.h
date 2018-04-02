#ifndef TCAPOSEMORPH_H__
#define TCAPOSEMORPH_H__

enum
{
	ID_CA_POSE_SLIDERS_GROUP = 5000,
	ID_CA_POSE_ADVANCED_GROUP,
	ID_CA_POSE_ANIMATE_GROUP,
	ID_CA_POSE_ROTATION_GROUP,
	ID_CA_POSE_OPTIONS_GROUP,
	ID_CA_POSE_INCLUDE_GROUP,

	ID_CA_POSE_MORPHS = 1000,
	ID_CA_POSE_MODE,
	ID_CA_POSE_ADDMORPH,
	ID_CA_POSE_P,
	ID_CA_POSE_S,
	ID_CA_POSE_R,
	ID_CA_POSE_STRENGTH,
	ID_CA_POSE_TARGET,
	ID_CA_POSE_EXTERNAL,
	ID_CA_POSE_MIXING,
	ID_CA_POSE_EXTERNAL_SAVE,
	ID_CA_POSE_RECORD_SLIDER,
	ID_CA_POSE_RESET_SLIDER,
	ID_CA_POSE_PARAM,
	ID_CA_POSE_USERDATA,
	ID_CA_POSE_TARGET_INCLUDE,
	ID_CA_POSE_DEST,
	ID_CA_POSE_POINTS,
	ID_CA_POSE_MAPS,
	ID_CA_POSE_ROTATION_POS,
	ID_CA_POSE_ROTATION_AXIS,
	ID_CA_POSE_ROTATION_FROMEDGE,
	ID_CA_POSE_ROTATION_FROMPOINTS,
	ID_CA_POSE_UV,
	ID_CA_POSE_TAGS,
	ID_CA_POSE_MIXING_DEFORMED,
	ID_CA_POSE_EDIT_MODE,
	ID_CA_POSE_HIERARCHY,
	ID_CA_POSE_TARGET_INCLUDE_MODE,
	ID_CA_POSE_MEMORY_USED,
	ID_CA_POSE_USE_STRENGTH,
	ID_CA_POSE_TOTAL_STRENGTH,
	ID_CA_POSE_ANIMATE_FOLDER_GROUPS,
	ID_CA_POSE_BASE_PRI,

	//////////////////////////////////////////////////////////////////////////

	ID_CA_POSE_ANIMATE_DATA = 4000,
	ID_CA_POSE_ANIMATE_CNT = 100,
	ID_CA_POSE_ANIMATE_OFFSET = 1000,

	ID_CA_POSE_ANIMATE_ENABLE = 0,
	ID_CA_POSE_ANIMATE_STRENGTH = 1,

	//////////////////////////////////////////////////////////////////////////

	ID_CA_POSE_EMULUATION_BEGIN = 3000,
	ID_CA_POSE_EMULUATION_END = 3999,

	//////////////////////////////////////////////////////////////////////////

	ID_CA_POSE_MODE_EDIT = 0,
	ID_CA_POSE_MODE_ANIMATE,

	ID_CA_POSE_MIXING_ABS = 0,
	ID_CA_POSE_MIXING_REL,
	ID_CA_POSE_MIXING_ROT,
	ID_CA_POSE_MIXING_CORRECTIONAL,
	ID_CA_POSE_MIXING_CORRECTIONAL_AREA,

	ID_CA_POSE_MIX_TYPE_AUTO = 0,
	ID_CA_POSE_MIX_TYPE_HIERARCHY,
	ID_CA_POSE_MIX_TYPE_NAME,

	ID_CA_POSE_EDIT_MODE_OFF = 0,
	ID_CA_POSE_EDIT_MODE_TARGET,
	ID_CA_POSE_EDIT_MODE_INPLACE,

	ID_CA_POSE_TARGET_INCLUDE_MODE_INCLUDE = 0,
	ID_CA_POSE_TARGET_INCLUDE_MODE_EXCLUDE,

	//////////////////////////////////////////////////////////////////////////

	ID_CA_POSE_TARGET_DUMMY
};

#endif // TCAPOSEMORPH_H__