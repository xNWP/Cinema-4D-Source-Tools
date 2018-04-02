#ifndef OPHTRACKEDOBJECT_H__
#define OPHTRACKEDOBJECT_H__

enum
{
	PH_OBJ_2D_TRACK_ASSIGNED_TRACKS_GROUP = 10000,
	PH_OBJ_2D_TRACK_ASSIGNED_TRACKS_LISTVIEW,
	PH_MOTION_TRACKER_OBJECT,
	PH_REFERENCE_GEOMETRY_OBJECT,
	
	
	PH_GROUP_TRACKERS = 10500,
	PH_GROUP_RECONSTRUCTION,

	PH_CMD_ASSIGN_SELECTED_TRACKS_TO_OBJECT = 11000,
	PH_CMD_UNASSIGN_SELECTED_TRACKS_FROM_OBJECT,
	PH_CMD_SOLVE_ALL_STAGES_OBJECT,

	PH_KEEP_OBJECT_RECON_WHEN_TRACK_2D_CHANGES,
	PH_3D_OBJECT_PNP_SOLVE_TEXT,
	PH_3D_OBJECT_PNP_SOLVE_USE_DEFERRED_AND_BA_DEBUG,
	PH_3D_OBJECT_PNP_SOLVE_MODE,
	PH_3D_OBJECT_PNP_KNEIP_PNP,
	PH_3D_OBJECT_PNP_EPNP,
	PH_3D_OBJECT_PNP_6PT,
	PH_STRICTLY_ENFORCE_KNOWN_GEOM_FOR_OBJECT_SOLVES,
	PH_USE_ALTERNATE_PNP_SOLVE,

	PH_OBJ_2D_TRACK_USER_featSizeActive = 41085,
	PH_OBJ_2D_TRACK_USER_trackWindowSizeActive,
//	PH_OBJ_2D_TRACK_USER_useExtrapolated2dTrackingActive,
//	PH_OBJ_2D_TRACK_USER_featNameActive,
//	PH_OBJ_2D_TRACK_USER_trackDirModeActive,

	PH_OBJ_2D_TRACK_USER_featSizeActive_MULTI,
	PH_OBJ_2D_TRACK_USER_trackWindowSizeActive_MULTI,
//	PH_OBJ_2D_TRACK_USER_useExtrapolated2dTrackingActive_MULTI,
//	PH_OBJ_2D_TRACK_USER_featNameActive_MULTI,
//	PH_OBJ_2D_TRACK_USER_trackDirModeActive_MULTI,

	PH_OBJ_2D_TRACK_featNameActive2 = 41204
};

#endif // OPHTRACKEDOBJECT_H__
