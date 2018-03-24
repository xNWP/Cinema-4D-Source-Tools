#ifndef TOOLCAWEIGHT_H__
#define TOOLCAWEIGHT_H__

enum
{
	ID_CA_WEIGHT_TOOL_JOINTS_GROUP = 5000,
	ID_CA_WEIGHT_TOOL_DISPLAY_GROUP,
	ID_CA_WEIGHT_TOOL_PAINT_GROUP,
	ID_CA_WEIGHT_TOOL_AUTOWEIGHT_GROUP,
	ID_CA_WEIGHT_TOOL_SMOOTH_GROUP,
	ID_CA_WEIGHT_TOOL_SYMMETRY_GROUP,
	ID_CA_WEIGHT_TOOL_SHEET_GROUP,
	ID_CA_WEIGHT_TOOL_CLAMP_GROUP,
	ID_CA_WEIGHT_TOOL_BRUSH_GROUP,
	ID_CA_WEIGHT_TOOL_SHEET_EDIT_GROUP,
	ID_CA_WEIGHT_TOOL_SHEET_OPTIONS_GROUP,
	ID_CA_WEIGHT_TOOL_SHEET_FILTER_GROUP,
	ID_CA_WEIGHT_TOOL_JOINT_FN_GROUP,
	ID_CA_WEIGHT_TOOL_PAINT_FN_GROUP,

	ID_CA_WEIGHT_TOOL_RADIUS = 2000,
	ID_CA_WEIGHT_TOOL_AUTOWEIGHT_DISTANCE,
	ID_CA_WEIGHT_TOOL_PEN,
	ID_CA_WEIGHT_TOOL_VISIBLE_ONLY,
	ID_CA_WEIGHT_TOOL_PREVIEW,
	ID_CA_WEIGHT_TOOL_STRENGTH,
	ID_CA_WEIGHT_TOOL_MODE,
	ID_CA_WEIGHT_TOOL_PROJECTION,
	ID_CA_WEIGHT_TOOL_JOINTS,
	ID_CA_WEIGHT_TOOL_JOINTS_LOCK,
	ID_CA_WEIGHT_TOOL_JOINTS_UNLOCKALL,
	ID_CA_WEIGHT_TOOL_JOINTS_UNLOCK,
	ID_CA_WEIGHT_TOOL_SHOWALL,

	ID_CA_WEIGHT_TOOL_SELECTED,
	ID_CA_WEIGHT_TOOL_CLAMP_LOWER_ENABLE,
	ID_CA_WEIGHT_TOOL_CLAMP_LOWER,
	ID_CA_WEIGHT_TOOL_CLAMP_UPPER_ENABLE,
	ID_CA_WEIGHT_TOOL_CLAMP_UPPER,
	ID_CA_WEIGHT_TOOL_APPLY_ALL,
	ID_CA_WEIGHT_TOOL_FALLOFF,
	ID_CA_WEIGHT_TOOL_WIDTH,
	ID_CA_WEIGHT_TOOL_FALLOFF_CURVE,
	ID_CA_WEIGHT_TOOL_HARDNESS,

	ID_CA_WEIGHT_TOOL_DISPLAY_FALLOFF,
	ID_CA_WEIGHT_TOOL_DISPLAY_CURSOR,
	ID_CA_WEIGHT_TOOL_DISPLAY_MOUSEIN,
	ID_CA_WEIGHT_TOOL_DISPLAY_FALLOFF_COLOR,
	ID_CA_WEIGHT_TOOL_DISPLAY_ERASE_COLOR,
	ID_CA_WEIGHT_TOOL_DISPLAY_CURSOR_COLOR,

	ID_CA_WEIGHT_TOOL_APPLY_SELECTED,
	ID_CA_WEIGHT_TOOL_DISPLAY_ZERO_COLOR,
	ID_CA_WEIGHT_TOOL_DISPLAY_LOWER,
	ID_CA_WEIGHT_TOOL_DISPLAY_UPPER,
	ID_CA_WEIGHT_TOOL_DISPLAY_POINTS,
	ID_CA_WEIGHT_TOOL_DELETED_7,

	ID_CA_WEIGHT_TOOL_EDITOR_WEIGHTS,
	ID_CA_WEIGHT_TOOL_EDITOR_SLIDER,

	ID_CA_WEIGHT_TOOL_NORMALIZE,
	ID_CA_WEIGHT_TOOL_REASSIGN,
	ID_CA_WEIGHT_TOOL_EDITOR_SLIDER_ZERO,
	ID_CA_WEIGHT_TOOL_SHOWALL_JOINTS,
	ID_CA_WEIGHT_TOOL_DELETED_1,
	ID_CA_WEIGHT_TOOL_DISPLAY_COLOR_MODE,
	ID_CA_WEIGHT_TOOL_DISPLAY_COLOR,

	ID_CA_WEIGHT_TOOL_DISPLAY_EFFECTORS,
	ID_CA_WEIGHT_TOOL_LOCK_LIST,
	ID_CA_WEIGHT_TOOL_BAKE,

	ID_CA_WEIGHT_TOOL_FN_AUTOWEIGHT,
	ID_CA_WEIGHT_TOOL_FN_CLEARWEIGHT,
	ID_CA_WEIGHT_TOOL_FN_AUTOWEIGHT_JOINTS,
	ID_CA_WEIGHT_TOOL_FN_AUTOWEIGHT_FALLOFF,
	ID_CA_WEIGHT_TOOL_FN_AUTOWEIGHT_MODE,

	ID_CA_WEIGHT_TOOL_DELETED_2,
	ID_CA_WEIGHT_TOOL_FN_AUTOWEIGHT_SELECTED_VERTICES,

	ID_CA_WEIGHT_TOOL_DELETED_3,
	ID_CA_WEIGHT_TOOL_FN_AUTOWEIGHT_SMOOTH,
	ID_CA_WEIGHT_TOOL_FN_AUTOWEIGHT_VIS,

	ID_CA_WEIGHT_TOOL_SMOOTH_STRENGTH,
	ID_CA_WEIGHT_TOOL_SMOOTH_DISTANCE,
	ID_CA_WEIGHT_TOOL_SMOOTH_CURVE,
	ID_CA_WEIGHT_TOOL_SMOOTH_INTERACTIVE,

	ID_CA_WEIGHT_TOOL_DISPLAY_MOUSEOVER,
	ID_CA_WEIGHT_TOOL_DISPLAY_FADE,

	ID_CA_WEIGHT_TOOL_DELETED_6,
	ID_CA_WEIGHT_TOOL_NORMALIZE_ALL,

	ID_CA_WEIGHT_TOOL_SPLINE,

	ID_CA_WEIGHT_TOOL_SYMMETRY,
	ID_CA_WEIGHT_TOOL_SYMMETRY_RAD,
	ID_CA_WEIGHT_TOOL_SYMMETRY_COORD,
	ID_CA_WEIGHT_TOOL_SYMMETRY_MIRROR,
	ID_CA_WEIGHT_TOOL_SYMMETRY_COORD_CUSTOM_OBJECT,

	ID_CA_WEIGHT_TOOL_DELETED_4,
	ID_CA_WEIGHT_TOOL_DELETED_5,

	ID_CA_WEIGHT_TOOL_SYMMETRY_MODE,
	ID_CA_WEIGHT_TOOL_SYMMETRY_MODE_NAME_LEFT,
	ID_CA_WEIGHT_TOOL_SYMMETRY_MODE_NAME_RIGHT,

	ID_CA_WEIGHT_TOOL_DISPLAY_HSIZE,
	ID_CA_WEIGHT_TOOL_LINK_SELECTION,
	ID_CA_WEIGHT_TOOL_FOCUS,
	ID_CA_WEIGHT_TOOL_WEIGHTS_FILTER,
	ID_CA_WEIGHT_TOOL_WEIGHTS_FILTER_MIN,
	ID_CA_WEIGHT_TOOL_WEIGHTS_FILTER_MAX,
	ID_CA_WEIGHT_TOOL_TOTAL,

	ID_CA_WEIGHT_TOOL_WEIGHTS_SLIDER_MODE,
	ID_CA_WEIGHT_TOOL_SLIDER_NORMALIZE,
	ID_CA_WEIGHT_TOOL_FULLWEIGHTED,

	ID_CA_WEIGHT_TOOL_SMOOTH,
	ID_CA_WEIGHT_TOOL_MIRROR,
	ID_CA_WEIGHT_TOOL_FLIP_PLANE,
	ID_CA_WEIGHT_TOOL_WEIGHTS_SELECTION,

	ID_CA_WEIGHT_TOOL_COPY,
	ID_CA_WEIGHT_TOOL_REPLACE,
	ID_CA_WEIGHT_TOOL_MERGE,
	ID_CA_WEIGHT_TOOL_DISPLAY,
	ID_CA_WEIGHT_TOOL_WEIGHTS_HIDE_ZERO,
	ID_CA_WEIGHT_TOOL_SORT_LIST,
	ID_CA_WEIGHT_TOOL_SELECTED_COLOR_MODE,
	ID_CA_WEIGHT_TOOL_DISPLAY_SELECTED_COLOR,
	ID_CA_WEIGHT_TOOL_EDITOR_ROUND_TO,
	ID_CA_WEIGHT_TOOL_EDITOR_SLIDER_SET,
	ID_CA_WEIGHT_TOOL_FILTER_LIST,

	//////////////////////////////////////////////////////////////////////////

	ID_CA_WEIGHT_TOOL_DIRTY = 1000,

	//////////////////////////////////////////////////////////////////////////

	ID_CA_WEIGHT_TOOL_SYMMETRY_MODE_SINGLE = 0,
	ID_CA_WEIGHT_TOOL_SYMMETRY_MODE_NAME,
	ID_CA_WEIGHT_TOOL_SYMMETRY_MODE_HIEARCHY,

	ID_CA_WEIGHT_TOOL_PEN_NONE = 0,
	ID_CA_WEIGHT_TOOL_PEN_RADIUS,
	ID_CA_WEIGHT_TOOL_PEN_STRENGTH,
	ID_CA_WEIGHT_TOOL_PEN_HARDNESS,

	ID_CA_WEIGHT_TOOL_MODE_ADD = 0,
	ID_CA_WEIGHT_TOOL_MODE_SUBTRACT,
	ID_CA_WEIGHT_TOOL_MODE_ABS,
	ID_CA_WEIGHT_TOOL_MODE_SMOOTH,
	ID_CA_WEIGHT_TOOL_MODE_BLEED,
	ID_CA_WEIGHT_TOOL_MODE_INTENSITY,
	ID_CA_WEIGHT_TOOL_MODE_REMAP,
	ID_CA_WEIGHT_TOOL_MODE_PRUNE,
	ID_CA_WEIGHT_TOOL_MODE_SMOOTH_DIST,
	ID_CA_WEIGHT_TOOL_MODE_DROPPER,
	ID_CA_WEIGHT_TOOL_MODE_SPRAY,
	ID_CA_WEIGHT_TOOL_MODE_ROUND,

	ID_CA_WEIGHT_TOOL_FALLOFF_NONE = 0,
	ID_CA_WEIGHT_TOOL_FALLOFF_LINEAR,
	ID_CA_WEIGHT_TOOL_FALLOFF_DOME,
	ID_CA_WEIGHT_TOOL_FALLOFF_BELL,
	ID_CA_WEIGHT_TOOL_FALLOFF_CIRCLE,
	ID_CA_WEIGHT_TOOL_FALLOFF_NEEDLE,
	ID_CA_WEIGHT_TOOL_FALLOFF_SPLINE,
	ID_CA_WEIGHT_TOOL_FALLOFF_SIMPLE,

	ID_CA_WEIGHT_TOOL_DISPLAY_COLOR_MODE_OBJECT = 0,
	ID_CA_WEIGHT_TOOL_DISPLAY_COLOR_MODE_SINGLE,
	ID_CA_WEIGHT_TOOL_DISPLAY_COLOR_MODE_RAINBOW,

	ID_CA_WEIGHT_TOOL_FN_AUTOWEIGHT_MODE_DISTANCE = 0,
	ID_CA_WEIGHT_TOOL_FN_AUTOWEIGHT_MODE_VISIBLE,

	ID_CA_WEIGHT_TOOL_SYMMETRY_COORD_LOCAL = 0,
	ID_CA_WEIGHT_TOOL_SYMMETRY_COORD_WORLD,
	ID_CA_WEIGHT_TOOL_SYMMETRY_COORD_CUSTOM,

	ID_CA_WEIGHT_TOOL_SYMMETRY_MIRROR_XY = 0,
	ID_CA_WEIGHT_TOOL_SYMMETRY_MIRROR_YZ,
	ID_CA_WEIGHT_TOOL_SYMMETRY_MIRROR_XZ,

	ID_CA_WEIGHT_TOOL_WEIGHTS_FILTER_NONE = 0,
	ID_CA_WEIGHT_TOOL_WEIGHTS_FILTER_NULL,
	ID_CA_WEIGHT_TOOL_WEIGHTS_FILTER_LESS,
	ID_CA_WEIGHT_TOOL_WEIGHTS_FILTER_MORE,
	ID_CA_WEIGHT_TOOL_WEIGHTS_FILTER_RANGE,
	ID_CA_WEIGHT_TOOL_WEIGHTS_FILTER_FOCUS,

	ID_CA_WEIGHT_TOOL_DISPLAY_MOUSEOVER_NONE = 0,
	ID_CA_WEIGHT_TOOL_DISPLAY_MOUSEOVER_SELECTED,
	ID_CA_WEIGHT_TOOL_DISPLAY_MOUSEOVER_ALL,

	ID_CA_WEIGHT_TOOL_FLIP_PLANE_XY = 0,
	ID_CA_WEIGHT_TOOL_FLIP_PLANE_YZ,
	ID_CA_WEIGHT_TOOL_FLIP_PLANE_XZ,

	ID_CA_WEIGHT_TOOL_SELECTED_COLOR_MODE_WEIGHT = 0,
	ID_CA_WEIGHT_TOOL_SELECTED_COLOR_MODE_CUSTOM,
	ID_CA_WEIGHT_TOOL_SELECTED_COLOR_MODE_OBJECT,

	ID_CA_WEIGHT_TOOL_EDITOR_ROUND_TO_1 = 0,
	ID_CA_WEIGHT_TOOL_EDITOR_ROUND_TO_5,
	ID_CA_WEIGHT_TOOL_EDITOR_ROUND_TO_10,

	ID_CA_WEIGHT_TOOL_SORT_LIST_FLAT = 0,
	ID_CA_WEIGHT_TOOL_SORT_LIST_HIERARCHY,
	ID_CA_WEIGHT_TOOL_SORT_LIST_NAME,

	//////////////////////////////////////////////////////////////////////////

	ID_CA_WEIGHT_TOOL_DUMMY
};

#endif // TOOLCAWEIGHT_H__
