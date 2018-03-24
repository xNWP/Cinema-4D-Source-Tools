#ifndef OMOTIONTRACKER_H__
#define OMOTIONTRACKER_H__

enum
{
	//---------------------------------------------
	// Copied from drendersettings.h, and PH_ prefix added
	// Allows state to be directly copied across in either direction,
	// although for these parameters this isn't actually required.
	PH_RDATA_FILMASPECT							= 6006,
	PH_RDATA_FILMPRESET							= 6007,
	PH_RDATA_FILMPRESET_CUSTOM					= 0,
	PH_RDATA_FILMPRESET_SQUARE					= 1, // 1:1
	PH_RDATA_FILMPRESET_STANDARD				= 2, // 4:3
	PH_RDATA_FILMPRESET_HDTV						= 3, // 16:9
	PH_RDATA_FILMPRESET_35MMSTILL				= 4, // 3:2
	PH_RDATA_FILMPRESET_WIDESCREEN			= 5, // 14:9
	PH_RDATA_FILMPRESET_35MM						= 6, // 1.85:1
	PH_RDATA_FILMPRESET_PANAVISION			= 7, // 2.39:1

	// Based on ocamera.h:
	PH_CAMERAOBJECT_APERTURE_PRESET_CUSTOM	= 0,
	PH_CAMERAOBJECT_APERTURE_PRESET_8				= 1,
	PH_CAMERAOBJECT_APERTURE_PRESET_16			= 2,
	PH_CAMERAOBJECT_APERTURE_PRESET_35STILL	= 3,
	PH_CAMERAOBJECT_APERTURE_PRESET_35MOVIE	= 4,
	PH_CAMERAOBJECT_APERTURE_PRESET_70			= 5,

	PH_CAMERAOBJECT_FOCUS_PRESET_CUSTOM			= 0,
	PH_CAMERAOBJECT_FOCUS_PRESET_WIDESUPER	= 1,
	PH_CAMERAOBJECT_FOCUS_PRESET_WIDE				= 2,
	PH_CAMERAOBJECT_FOCUS_PRESET_C4D				= 3,
	PH_CAMERAOBJECT_FOCUS_PRESET_NORMAL			= 4,
	PH_CAMERAOBJECT_FOCUS_PRESET_PORTRAIT		= 5,
	PH_CAMERAOBJECT_FOCUS_PRESET_TELE				= 6,
	PH_CAMERAOBJECT_FOCUS_PRESET_TELESUPER	= 7,


	// Based on onull.h:
	PH_3D_RECON_NULLOBJECT_DISPLAY_DOT				= 0,
	PH_3D_RECON_NULLOBJECT_DISPLAY_POINT			= 1,
	PH_3D_RECON_NULLOBJECT_DISPLAY_CIRCLE			= 2,
	PH_3D_RECON_NULLOBJECT_DISPLAY_RECTANGLE	= 3,
	PH_3D_RECON_NULLOBJECT_DISPLAY_DIAMOND		= 4,
	PH_3D_RECON_NULLOBJECT_DISPLAY_TRIANGLE		= 5,
	PH_3D_RECON_NULLOBJECT_DISPLAY_PENTAGON		= 6,
	PH_3D_RECON_NULLOBJECT_DISPLAY_HEXAGON		= 7,
	PH_3D_RECON_NULLOBJECT_DISPLAY_OCTAGON		= 8,
	PH_3D_RECON_NULLOBJECT_DISPLAY_STAR				= 9,
	PH_3D_RECON_NULLOBJECT_DISPLAY_AXIS				= 10,
	PH_3D_RECON_NULLOBJECT_DISPLAY_CUBE				= 11,
	PH_3D_RECON_NULLOBJECT_DISPLAY_PYRAMID		= 12,
	PH_3D_RECON_NULLOBJECT_DISPLAY_SPHERE			= 13,
	PH_3D_RECON_NULLOBJECT_DISPLAY_NONE				= 14,

	PH_2D_TRACK_DIR_MODE_UNDEFINED			= 0,
	PH_2D_TRACK_DIR_MODE_FORWARD				= 1,
	PH_2D_TRACK_DIR_MODE_REVERSE				= 2,
	PH_2D_TRACK_DIR_MODE_BIDIRECTIONAL	= 3,


	// WARN: Don't add any more elements below without restarting sequence number.
	PH_UNUSED_CMD_BUTT_00 = 10000,

	PH_CREATE_USER_TRACKS,
	PH_CREATE_CONSTRAINT_MASK,
	PH_CREATE_CONSTRAINT_POSITION,
	PH_CREATE_CONSTRAINT_VECTOR,
	PH_CREATE_CONSTRAINT_PLANAR,


	PH_FOOTAGE_FILENAME = 10500,
	PH_FOOTAGE_RESET,
	PH_FOOTAGE_RELOAD,

	PH_FOOTAGE_SYS_MEMORY_AVAILABLE,
	PH_FOOTAGE_SYS_MEMORY_SAFETY_RESERVE_MB_LEGACY,
	PH_FOOTAGE_DOWNSAMPLING_FACTOR,
	PH_FOOTAGE_DOWNSAMPLED_RES_X_PIXELS,
	PH_FOOTAGE_DOWNSAMPLED_RES_Y_PIXELS,
	PH_FOOTAGE_MEMORY_MAX_CACHE_SIZE_MB_LEGACY,

	PH_FOOTAGE_TRACK_FRAME_START,
	PH_FOOTAGE_TRACK_FRAME_STOP,

	PH_FOOTAGE_OFFSET_TRACKS_SELECTED,
	PH_FOOTAGE_TRACK_FRAME_OFFSET,

	ID_FEATURE_INTERNALS = 11000,


	PH_FOOTAGE_VIEW_SCALE = 20000,
	PH_FOOTAGE_VIEW_OFFSET_X,
	PH_FOOTAGE_VIEW_OFFSET_Y,

	PH_FOOTAGE_VIEW_FULL,
	PH_FOOTAGE_USE_FOREGROUND_DISPLAY,
	PH_FOOTAGE_MATCH_VIEW_WIDTH,
	PH_FOOTAGE_MATCH_VIEW_HEIGHT,

	PH_RDATA_RENDER_FILM_ASPECT, // Display field for render aspect ratio

	PH_CREATE_CAMERA_MAPPING_TEXTURE_TAG,
	PH_CREATE_BACKGROUND_OBJECT,

	PH_FOOTAGE_INFO_BOX_00,
	PH_FOOTAGE_INFO_BOX_01,
	PH_FOOTAGE_INFO_BOX_02,
	PH_FOOTAGE_INFO_BOX_03,
	PH_FOOTAGE_INFO_BOX_04,
	PH_FOOTAGE_INFO_BOX_05,

	PH_FOOTAGE_USE_FOREGROUND_DISPLAY_TOGGLE,
	PH_FRAME_SELECTED_TRACKS,
	PH_FRAME_ALL_TRACKS,
	PH_CREATE_PHOENIX_WITH_CAMERA,
	PH_CREATE_TRACKED_OBJECT,

	PH_FOOTAGE_SHOW_IMAGE = 30000,
	PH_AUTO_2D_RETRACK_ON_CHANGE,

	PH_GROUP_FOOTAGE = 40000,

	PH_LINKED_ELEMENT_LIST = 40051,

	PH_FOOTAGE_BRIGHTNESS = 40100,

	PH_FOOTAGE_ROTATION,

	PH_FOOTAGE_SUBGROUP_FOOTAGE_SETTINGS = 40500,
	PH_FOOTAGE_SUBGROUP_NAVIGATION_SETTINGS,
	PH_FOOTAGE_SUBGROUP_VISIBILITY_SETTINGS,

	//==== 2D Tracking ====
	PH_GROUP_2D_TRACK = 41000,

	PH_2D_TRACK_SUBTAB_MODE,
		PH_SUBTAB_2D_TRACK_MANUAL,
		PH_SUBTAB_2D_TRACK_AUTO,
		PH_SUBTAB_2D_TRACK_FILTER,
		PH_SUBTAB_2D_TRACK_DISPLAY,
		PH_SUBTAB_2D_TRACK_SELECTION,

	PH_GROUP_2D_TRACK_AUTO,
	PH_2D_TRACK_AUTO_TRACK,
	PH_2D_TRACK_AUTO_TRACK_FORWARD,
	PH_2D_TRACK_AUTO_TRACK_BACKWARD,

	PH_GROUP_2D_TRACK_MANUAL,
	PH_2D_TRACK_MANUAL_TRACK,
	PH_2D_TRACK_MANUAL_TRACK_FORWARD,
	PH_2D_TRACK_MANUAL_TRACK_BACKWARD,


	PH_GROUP_2D_TRACK_DISPLAY,

	PH_2D_TRACK_STR_SETTINGS,
	PH_2D_TRACK_STR_DISPLAY,
	PH_2D_TRACK_STR_FEATURE_BEHAVIOUR,

	PH_2D_TRACK_SMART_TRACK,
	PH_2D_TRACK_SMART_TRACK_FORWARD,
	PH_2D_TRACK_SMART_TRACK_BACKWARD,

	PH_2D_TRACK_USER_TRACKS_LISTVIEW_LEGACY,
	PH_2D_TRACK_USER_TRACKS_LISTVIEW,

	PH_2D_TRACK_STR_TRACK_LIST,
	PH_2D_TRACK_USER_TRACKS_OBJECTS_CACHE_VAL,

	PH_2D_TRACK_autoReplaceLostFeatures = 41050,
	PH_2D_TRACK_featSize,
	PH_2D_TRACK_numFeatsTargetFullFrame,
	PH_2D_TRACK_numRegionsFullFrame,
	PH_2D_TRACK_minSpacing,
	PH_2D_TRACK_maxTrack2dError,

	PH_2D_TRACK_trackWindowSize,
	PH_2D_TRACK_featSizeActive,
	PH_2D_TRACK_trackWindowSizeActive,

	PH_2D_TRACK_showFeat,
	PH_2D_TRACK_showFeatSize,
	PH_2D_TRACK_showTrackWindowSize,
	PH_2D_TRACK_showTrackTrails,

	PH_2D_TRACK_useExtrapolated2dTracking,
	PH_2D_TRACK_useExtrapolated2dTrackingActive,

	PH_2D_TRACK_featNameActive,

	PH_2D_TRACK_TRIM_BUTTON,
	PH_2D_TRACK_UNTRIM_BUTTON,

	PH_2D_TRACK_MANUAL_RESET,
	PH_2D_TRACK_AUTO_RESET,
	PH_2D_TRACK_AUTO_CREATE_MARKERS,

	PH_2D_TRACK_MAKE_SELECTED_BECOME_USER_TRACKS,

	PH_2D_TRACK_trackFromCam_dead,
	PH_2D_TRACK_trackToCam_dead,

	PH_2D_TRACK_trackDirModeActive,

	PH_2D_TRACK_CREATE_USER_FEAT_AT_POS,
	PH_2D_TRACK_INSERT_SINGLE_KEY_AT_POS,
	PH_2D_TRACK_AUTOKEYS_BUTTON,
	PH_2D_TRACK_DELETE_KEYS_BUTTON,

	PH_CREATE_USER_TRACKS_MODE,
	PH_CREATE_CONSTRAINT_MASK_MODE,
	PH_CREATE_CONSTRAINT_POSITION_MODE,
	PH_CREATE_CONSTRAINT_VECTOR_MODE,
	PH_CREATE_CONSTRAINT_PLANAR_MODE,
	PH_CREATE_CONSTRAINT_CAMERA_ORIENT_MODE,

	PH_2D_TRACK_USER_featSizeActive,
	PH_2D_TRACK_USER_trackWindowSizeActive,
	PH_2D_TRACK_USER_useExtrapolated2dTrackingActive,
	PH_2D_TRACK_USER_featNameActive,
	PH_2D_TRACK_USER_trackDirModeActive,

	PH_2D_TRACK_USER_featSizeActive_MULTI,
	PH_2D_TRACK_USER_trackWindowSizeActive_MULTI,
	PH_2D_TRACK_USER_useExtrapolated2dTrackingActive_MULTI,
	PH_2D_TRACK_USER_featNameActive_MULTI,
	PH_2D_TRACK_USER_trackDirModeActive_MULTI,

	PH_2D_TRACK_USER_featSizeActive_STR,
	PH_2D_TRACK_USER_trackWindowSizeActive_STR,

	PH_USE_VIRTUAL_OBJECT_PREFIX_FOR_TRACK_LISTVIEW,

	PH_2D_TRACK_DISP_FEAT_MODE = 41200,
	PH_2D_TRACK_dispFeat_showFeatWithTrack,
	PH_2D_TRACK_dispFeat_showFeat,
	PH_2D_TRACK_dispFeat_none,

	PH_2D_TRACK_featNameActive2,

	//==== 2D Filtering ====
	PH_GROUP_2D_TRACK_FILTER = 42000,
	PH_2D_TRACK_FILTER,

	PH_2D_TRACK_FILTER_minTrackLen_Active,
	PH_2D_TRACK_FILTER_minTrackLen,

	PH_2D_TRACK_FILTER_maxError_Active,
	PH_2D_TRACK_FILTER_maxError,

	PH_2D_TRACK_FILTER_maxAccel_Active,
	PH_2D_TRACK_FILTER_maxAccel,

	PH_2D_TRACK_FILTER_smartAccel_Active,
	PH_2D_TRACK_FILTER_smartAccel,

	PH_2D_TRACK_FILTER_cropNearEdges_Active_unused,
	PH_2D_TRACK_FILTER_cropNearEdges_unused,

	PH_2D_TRACK_FILTER_deleteEntireTrackOnFail_Active,


	//==== Active Selection ====
	PH_GROUP_2D_TRACK_SELECTION = 42500,

	//==== 3D Reconstruction ====
	PH_GROUP_3D_RECON = 43000,

	// Global solve settings
	PH_FOCAL_SOLVE_MODE,
		PH_FOCAL_MODE_UNKNOWN_VARIABLE,
		PH_FOCAL_MODE_UNKNOWN_FIXED,
		PH_FOCAL_MODE_KNOWN_FIXED,
		// PH_FOCAL_MODE_KNOWN_VARIABLE, *Defined later so as not to interrupt numbering
	PH_FOCAL_KNOWN_FIXED,
	PH_APERTURE_KNOWN_FIXED,

	// Initial Triplet (3 camera recon)
	PH_3D_RECON_initTriplet_camA,
	PH_3D_RECON_initTriplet_camB,
	PH_3D_RECON_initTriplet_camC,
	PH_UNUSED_0,

	// Extension (Sub-sampled recon over range)
	PH_3D_RECON_solveFromCam_legacy, // (Renamed from PH_3D_RECON_extendFromCam)
	PH_3D_RECON_solveToCam_legacy, // (Renamed from PH_3D_RECON_extendToCam)
	PH_3D_RECON_extendStep,
	PH_3D_RECON_SOLVE_EXTEND,
	PH_UNUSED_1,

	// Final solve (Solve for all missing cameras)
	PH_3D_RECON_SOLVE_DEFERRED,

	// Run all stages of solver
	PH_3D_RECON_SOLVE_ALL_STAGES,

	// Section labels
	PH_3D_RECON_STR_CAMERA_SETTINGS,
	PH_3D_RECON_STR_TRIPLET,
	PH_3D_RECON_STR_EXTEND,
	PH_3D_RECON_STR_DEFER,
	PH_3D_RECON_STR_DISPLAY_SETTINGS,

	// Additional camera values, based on ocamera.res
	PH_CAMERAOBJECT_FOCUS_PRESET,
	PH_CAMERAOBJECT_APERTURE_PRESET,
	PH_CAMERAOBJECT_APERTURE_35,
	PH_CAMERAOBJECT_FOV,
	PH_CAMERAOBJECT_FOV_VERTICAL,

	PH_UNUSED_2,
	PH_UNUSED_3,

	PH_3D_RECON_STR_SOLVER_SETTINGS,

	PH_3D_RECON_SOLVE_INITIAL,

	PH_3D_RECON_HIERARCHICAL_SOLVE_ALL_STAGES,

	PH_SUPER_SOLVER,

	PH_3D_RECON_HIERARCHICAL_SOLVE_ALL_STAGES_OBJECTS,
	PH_OBJECT_SOLVE,
	PH_SELECTED_TRACK_DATA_DUMP_CURR_FRAME,

	PH_FOCAL_MODE_KNOWN_VARIABLE, // Indicates that existing camera focal track is to be used

	PH_KEEP_BACKGROUND_RECON_WHEN_TRACK_2D_CHANGES,


	PH_SOLVE_MODE = 43450,
		PH_SOLVE_MODE_FULL_3D,
		PH_SOLVE_MODE_NODAL,
		PH_SOLVE_MODE_PLANAR,

	PH_3D_RECON_SUBTAB_MODE = 43500,
		PH_SUBTAB_3D_RECON_RECON,
		PH_SUBTAB_3D_RECON_DISPLAY,

	PH_GROUP_3D_RECON_RECON,
	PH_GROUP_3D_RECON_DISPLAY,

	PH_3D_RECON_NULLOBJECT_DISPLAY_MODE,
	PH_3D_RECON_NULLOBJECT_RADIUS,

	//==== Selection ====
	PH_GROUP_SELECTION = 44000,
	PH_SELECT_AUTO_TRACKS,
	PH_SELECT_USER_TRACKS,
	PH_SELECT_RECONSTRUCTED_TRACKS,
	PH_INVERT_TRACK_SELECTION,

	PH_HIDE_SELECTED_TRACKS,
	PH_HIDE_UNSELECTED_TRACKS,
	PH_UNHIDE_ALL_TRACKS,
	PH_INVERT_TRACK_VISIBILITY,

	PH_DELETE_SELECTED_TRACKS,
	PH_RESTORE_DELETED_TRACKS,

	PH_VIEW_MODE_2D,
	PH_VIEW_MODE_3D,


	PH_2D_TRACK_USER_TRACKS_GROUP = 50000,
	PH_2D_TRACK_USER_TRACKS_GROUP_DATA_BASE,

	PH_AUTO_OFFSET = 55100,
	PH_AUTO_UPDATE_TRACKS,
	PH_NUDGE_LEFT,
	PH_NUDGE_RIGHT,
	PH_NUDGE_UP,
	PH_NUDGE_DOWN,

	//==== Common group ====
	// (Unnamed group - common to all tabs)
	PH_GROUP_EXPERIMENTAL = 60000,

	PH_SHOW_GRAPH_VIEW,

	PH_DEBUG_BUTTON_7,

	PH_DEBUG_BUTTON_10,
	PH_DEBUG_BUTTON_11,
	PH_DEBUG_BUTTON_12,
	PH_DEBUG_BUTTON_13,
	PH_DEBUG_BUTTON_14,
	PH_DEBUG_BUTTON_15,
	PH_DEBUG_BUTTON_16,
	PH_DEBUG_BUTTON_17,
	PH_DEBUG_BUTTON_18,
	PH_DEBUG_BUTTON_19,

	PH_GENERAL_INFO_BOX_00,
	PH_GENERAL_INFO_BOX_01,
	PH_GENERAL_INFO_BOX_02,
	PH_GENERAL_INFO_BOX_03,
	PH_GENERAL_INFO_BOX_04,
	PH_GENERAL_INFO_BOX_05,

	PH_DEBUG_SAVE_PARTIAL_RECONSTRUCTIONS,
	PH_DEBUG_LOAD_PARTIAL_RECONSTRUCTIONS,

	PH_DEBUG_3D_SOLVE_WITHOUT_DEFFERED,

	// PHLENS Lens Distortion support - needed in all elements which support usage of lenses.
	PH_GROUP_LENS_DISTORTION = 100000,
	PH_LENS_PROFILE_FILENAME,
	PH_LENS_PROFILE_NAME,
	PH_LENS_PROFILE_TYPE,

	PH_LENS_PARAMS_GROUP = 100050,

	PH_LENS_PROFILE_PARAM_0 = 100100,
	PH_LENS_PROFILE_PARAM_1,
	PH_LENS_PROFILE_PARAM_2,
	PH_LENS_PROFILE_PARAM_3,
	PH_LENS_PROFILE_PARAM_4,

	PH_LENS_PARAM_RC_00 = 105000,
	PH_LENS_PARAM_RC_01,
	PH_LENS_PARAM_RC_02,
	PH_LENS_PARAM_RC_03,
	PH_LENS_PARAM_RC_04,
	PH_LENS_PARAM_RC_05,
	PH_LENS_PARAM_RC_10 = 105100,
	PH_LENS_PARAM_RC_11,
	PH_LENS_PARAM_RC_12,
	PH_LENS_PARAM_RC_13,
	PH_LENS_PARAM_RC_14,
	PH_LENS_PARAM_RC_15,
	PH_LENS_PARAM_RC_20 = 105200,
	PH_LENS_PARAM_RC_21,
	PH_LENS_PARAM_RC_22,
	PH_LENS_PARAM_RC_23,
	PH_LENS_PARAM_RC_24,
	PH_LENS_PARAM_RC_25,
	PH_LENS_PARAM_RC_30 = 105300,
	PH_LENS_PARAM_RC_31,
	PH_LENS_PARAM_RC_32,
	PH_LENS_PARAM_RC_33,
	PH_LENS_PARAM_RC_34,
	PH_LENS_PARAM_RC_35,
	PH_LENS_PARAM_RC_40 = 105400,
	PH_LENS_PARAM_RC_41,
	PH_LENS_PARAM_RC_42,
	PH_LENS_PARAM_RC_43,
	PH_LENS_PARAM_RC_44,
	PH_LENS_PARAM_RC_45,
};

#endif // OMOTIONTRACKER_H__
