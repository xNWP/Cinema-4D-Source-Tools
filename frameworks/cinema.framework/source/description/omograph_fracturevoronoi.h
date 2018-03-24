#ifndef OMOGRAPH_FRACTUREVORONOI_H__
#define OMOGRAPH_FRACTUREVORONOI_H__

enum
{
	ID_MG_VF_MOTIONGENERATOR_GROUP_EFFECTORS = 990,
	ID_MG_VF_MOTIONGENERATOR_EFFECTORLIST = 2009,
	
	ID_FRACTURE_SELECTION = 1059,
	ID_FRACTURE_WEIGHT = 1063,
	ID_SOURCE_PROPERTIES = 4000,
	ID_DEBUGPROPERTIES = 1500,
	ID_SOURCES = 1600,
	ID_FRACTURE_POINTINPUTTYPE = 1000,
	ID_FRACTURE_POINTINPUTTYPE_UNIFORM = 1001,
	ID_FRACTURE_POINTINPUTTYPE_INPUTOBJECTS = 1002,
	ID_FRACTURE_POINTINPUTTYPE_TEXTURE = 1003,	
	// always visible options
	ID_FRACTURE_SHOWPOINTS = 1055,
	ID_FRACTURE_HIDEPOINTS = 1060,
	ID_FRACTURE_VIEWPORTRATIO = 1062,
	ID_FRACTURE_COLORIZE = 1004,
	ID_FRACTURE_CREATENGONS = 1005,
	ID_FRACTURE_GAP = 1006,
	ID_FRACTURE_SHELL = 1007,
	ID_FRACTURE_AUTOCLOSE = 1058,
	ID_FRACTURE_ACTIVATE_SORTORDER = 1033,
	ID_FRACTURE_INVERT_SORTORDER = 1034,
	ID_FRACTURE_SORTORDER = 1035,
	ID_FRACTURE_SORTORDER_X = 1036,
	ID_FRACTURE_SORTORDER_Y = 1037,
	ID_FRACTURE_SORTORDER_Z = 1038,
	ID_FRACTURE_AUTOMATIC_UPDATE = 1008,
	ID_FRACTURE_AUTOMATIC_UPDATE_ANIMATION = 1061,
	ID_FRACTURE_UPDATE = 1009,
	

	
	// texture tab elements
	ID_FRACTURE_INPUTTEXTURETAB = 1016,
	
	ID_FRACTURE_INPUTTEXTURE = 1017,
	ID_FRACTURE_TEXTURESAMPLEDENSITY = 1018,
	ID_FRACTURE_TEXTURESAMPLESEED = 1039,
	ID_FRACTURE_TEXTURESAMPLEDEPTH = 1040,
	
	ID_FRACTURE_CREATEPOINTSDISTRIBUTION = 1045,
	ID_FRACTURE_CREATEPOINTSUNIFORM = 1046,
	ID_FRACTURE_CREATEPOINTSNORMAL = 1047,
	ID_FRACTURE_CREATEPOINTSINVNORMAL = 1048,
	ID_FRACTURE_CREATEPOINTSEXPONENTIAL = 1049,
	ID_FRACTURE_CREATEPOINTSNORMAL_STANDARDDEVIATION = 1050,
	ID_FRACTURE_CREATEPOINTSEXPONENTIAL_DIMENSIONS = 1051,
	ID_FRACTURE_CREATEPOINTSEXPONENTIAL_X = 1052,
	ID_FRACTURE_CREATEPOINTSEXPONENTIAL_Y = 1053,
	ID_FRACTURE_CREATEPOINTSEXPONENTIAL_Z = 1054,

	ID_FRACTURE_CREATEDISTRIBUTION = 1056,
	ID_FRACTURE_CREATESHADER = 1057,
	
	// createpointstab elements
	ID_FRACTURE_CREATEPOINTSTAB = 1010,
	ID_FRACTURE_CREATEPOINTS = 1011,
	ID_FRACTURE_CREATEPOINTSSEED = 1012,
	ID_FRACTURE_CREATEDPOINTAMOUNT = 1013,
	ID_FRACTURE_CREATEPOINTS_ONLY_INSIDE = 1044,
	
	ID_FRACTURE_CREATEPOINTS_TRANSLATE = 1041,
	ID_FRACTURE_CREATEPOINTS_SCALE = 1042,
	ID_FRACTURE_CREATEPOINTS_ROTATE = 1043,
	
	// inputpoints tab elements
	ID_FRACTURE_INPUTPOINTSTAB = 1014,
	
	ID_FRACTURE_INPUT_POINTS = 1015,

	FRACTURE_SHOWDELAUNAY = 1020,
	FRACTURE_SHOWVORONOI = 1021,
	FRACTURE_SHOWCLIPPED = 1022,
	FRACTURE_CREATENGONS = 1023,

	FRACTURE_VOXELRESSURF = 1024,
	FRACTURE_VOXELRESCELLS = 1025,
	FRACTURE_FILLINTERIOR = 1026,
	FRACTURE_MERGEPOINTS = 1027,
	FRACTURE_THREADCOUNT = 1028,
	FRACTURE_CREATESINGLE = 1029,
	FRACTURE_CREATESINGLENUMBER = 1030,
	FRACTURE_CREATESINGLEFACE = 1031,
	FRACTURE_CREATESINGLEFACENUMBER = 1032,
	
	ID_FRACTURE_SELECTION_TAGS = 1064,
	ID_FRACTURE_CREATE_OUTSIDE_FACE_SELECTION = 1065,
	ID_FRACTURE_CREATE_INSIDE_FACE_SELECTION = 1066,
	ID_FRACTURE_CREATE_INSIDE_VERTEX_SELECTION = 1067,
	ID_FRACTURE_CREATE_OUTSIDE_VERTEX_SELECTION = 1068,
	ID_FRACTURE_CREATE_EDGE_VERTEX_SELECTION = 1069,
	ID_FRACTURE_CREATE_EDGE_SELECTION = 1070
};

#endif	// OMOGRAPH_FRACTUREVORONOI_H__
