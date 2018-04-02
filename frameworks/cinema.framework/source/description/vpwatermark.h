#ifndef VPWATERMARK_H__
#define VPWATERMARK_H__

enum
{
	VP_WATERMARK_PREVIEW											= 10000,		// GROUP
	VP_WATERMARK_PREVIEW_IMAGE								= 10001,		// CUSTOMGUI

	VP_WATERMARK_IMG													= 10010,		// GROUP
	VP_WATERMARK_IMG_FILENAME									= 10011,		// FILENAME
	VP_WATERMARK_IMG_OPACITY									= 10012,		// REAL
	VP_WATERMARK_IMG_BLENDMODE								= 10013,		// LONG
		VP_IMG_BLENDMODE_LIGHTEN									= 1,
		VP_IMG_BLENDMODE_DARKEN										= 2,
		VP_IMG_BLENDMODE_MULTIPLY 								= 3,
		VP_IMG_BLENDMODE_AVERAGE 									= 4,
		VP_IMG_BLENDMODE_ADD											= 5,
		VP_IMG_BLENDMODE_SUBTRACT 								= 6,
		VP_IMG_BLENDMODE_DIFFERENCE 							= 7,
		VP_IMG_BLENDMODE_NEGATION 								= 8,
		VP_IMG_BLENDMODE_SCREEN 									= 9,
		VP_IMG_BLENDMODE_EXCLUSION 								= 10,
		VP_IMG_BLENDMODE_OVERLAY 									= 11,
		VP_IMG_BLENDMODE_SOFTLIGHT 								= 12,
		VP_IMG_BLENDMODE_HARDLIGHT 								= 13,
		VP_IMG_BLENDMODE_COLORDODGE 							= 14,
		VP_IMG_BLENDMODE_COLORBURN 								= 15,
		VP_IMG_BLENDMODE_LINEARDODGE 							= 16,
		VP_IMG_BLENDMODE_LINEARBURN 							= 17,
		VP_IMG_BLENDMODE_LINEARLIGHT 							= 18,
		VP_IMG_BLENDMODE_VIVIDLIGHT 							= 19,
		VP_IMG_BLENDMODE_PINLIGHT 								= 20,
		VP_IMG_BLENDMODE_HARDMIX 									= 21,
		VP_IMG_BLENDMODE_REFLECT 									= 22,
		VP_IMG_BLENDMODE_GLOW 										= 23,
		VP_IMG_BLENDMODE_PHOENIX 									= 24,
		VP_IMG_BLENDMODE_NORMAL 									= 25,
		VP_IMG_BLENDMODE_COLOR										= 26,
		VP_IMG_BLENDMODE_COLOR_INV								= 27,
	VP_WATERMARK_IMG_SCALE										= 10014,		// REAL
	VP_WATERMARK_IMG_SCALE_ASPECT							= 10015,		// BOOL
	VP_WATERMARK_IMG_POS_X										= 10016,		// LONG
	VP_WATERMARK_IMG_POS_Y										= 10017,		// LONG
		VP_WATERMARK_POS_CENTER										= 0,
		VP_WATERMARK_POS_LEFT											= 1,
		VP_WATERMARK_POS_RIGHT										= 2,
		VP_WATERMARK_POS_TOP											= 3,
		VP_WATERMARK_POS_BOTTOM										= 4,
	VP_WATERMARK_IMG_ENABLE										= 10018,		// BOOL
	VP_WATERMARK_IMG_MARGIN										= 10019,		// LONG
	VP_WATERMARK_IMG_SCALE_KEEPSIZE						= 10050,		// BOOL

	VP_WATERMARK_TEXT													= 10020,		// GROUP
	VP_WATERMARK_TEXT_TIMECODE								= 10021,		// BOOL
	VP_WATERMARK_TEXT_DATE										= 10023,		// BOOL
	VP_WATERMARK_TEXT_RENDERTIME							= 10024,		// BOOL
	VP_WATERMARK_TEXT_C4DVERSION							= 10025,		// BOOL
	VP_WATERMARK_TEXT_ACTIVECAMERA						= 10026,		// BOOL
	VP_WATERMARK_TEXT_SCENENAME								= 10027,		// BOOL
	VP_WATERMARK_TEXT_CUSTOM									= 10028,		// BOOL
	VP_WATERMARK_TEXT_CUSTOM_TEXT							= 10029,		// STRING
	VP_WATERMARK_TEXT_FONT										= 10030,		// FONTSELECTOR
	VP_WATERMARK_TEXT_SHOWLABELS							= 10031,		// LONG
	VP_WATERMARK_TEXT_POS_Y										= 10033,		// LONG
	VP_WATERMARK_TEXT_COLOR										= 10034,		// VECTOR
	VP_WATERMARK_TEXT_BG_COLOR								= 10035,		// VECTOR
	VP_WATERMARK_TEXT_BG_OPACITY							= 10036,		// REAL
	VP_WATERMARK_TEXT_ENABLE									= 10038,		// BOOL
	VP_WATERMARK_TEXT_POLYCOUNT								= 10039,		// BOOL
	VP_WATERMARK_TEXT_DYNAMICLAYOUT						= 10040,		// BOOL
	VP_WATERMARK_TEXT_MACHINEINFO							= 10041,		// BOOL
	VP_WATERMARK_TEXT_CUSTOM_TEXT_PH					= 10042,		// LONG
		VP_WATERMARK_PH_C4DTYPE										= 10,
		VP_WATERMARK_PH_BUILDID										= 11,
		VP_WATERMARK_PH_OSTYPE										= 12,
		VP_WATERMARK_PH_OSVER											= 13,
		VP_WATERMARK_PH_CPUTYPE										= 14,
		VP_WATERMARK_PH_CPUNAME										= 15,
		VP_WATERMARK_PH_CPUMHZ										= 16,
		VP_WATERMARK_PH_CPUCNT										= 17,
		VP_WATERMARK_PH_CPUHTCNT									= 18,
		VP_WATERMARK_PH_MACHINE										= 19,
		VP_WATERMARK_PH_MACHMDL										= 20,
		VP_WATERMARK_PH_COMPNAME									= 21,
		VP_WATERMARK_PH_USERNAME									= 22,
		VP_WATERMARK_PH_DOCCOPYRIGHT							= 23,
		VP_WATERMARK_PH_DOCAUTHOR									= 24,
		VP_WATERMARK_PH_LICNAME										= 25,
		VP_WATERMARK_PH_LICORG										= 26,
		VP_WATERMARK_PH_LICNR											= 27,
		VP_WATERMARK_PH_DOCNAME										= 28,
		VP_WATERMARK_PH_DOCPATH										= 29,
		VP_WATERMARK_PH_RENDERER									= 30,
		VP_WATERMARK_PH_RAYDEPTH									= 31,
		VP_WATERMARK_PH_REFLDEPTH									= 32,
		VP_WATERMARK_PH_SHADOWDEPTH								= 33,
		VP_WATERMARK_PH_FORMATDEPTH								= 34,
		VP_WATERMARK_PH_AAFILTER									= 35,
		VP_WATERMARK_PH_AA												= 36,
		VP_WATERMARK_PH_AATHRESHOLD								= 37,
		VP_WATERMARK_PH_AAMAX											= 38,
		VP_WATERMARK_PH_AAMIN											= 39,
		VP_WATERMARK_PH_RAYTHRESHOLD							= 40,
		VP_WATERMARK_PH_LOD												= 41,
		VP_WATERMARK_PH_GI_MODE										= 42,
		VP_WATERMARK_PH_GI_DIFFDEPTH							= 43,
		VP_WATERMARK_PH_GI_ACCURACY								= 44,
		VP_WATERMARK_PH_GI_SAMPLES								= 45,
		VP_WATERMARK_PH_GI_DENSITY								= 46,
		VP_WATERMARK_PH_XMB_MBLUR									= 47,
		VP_WATERMARK_PH_XMB_SAMPLING							= 48,
		VP_WATERMARK_PH_XMB_BLURRY								= 49,
		VP_WATERMARK_PH_RENDERTIME								= 50,
		VP_WATERMARK_PH_POLYCOUNT									= 51,
		VP_WATERMARK_PH_PHYSRAM										= 52,
		VP_WATERMARK_PH_XMB_GI										= 53,
		VP_WATERMARK_PH_OBJCOUNT									= 54,
		VP_WATERMARK_PH_LIGHTCOUNT								= 55,
		VP_WATERMARK_PH_XMB_HDRTHRESH							= 56,
		VP_WATERMARK_PH_C4DVERSION								= 57,
		VP_WATERMARK_PH_CAT_GI										= 58,
		VP_WATERMARK_PH_CAT_XMB										= 59,
		VP_WATERMARK_PH_CAT_CAM										= 60,
		VP_WATERMARK_PH_CAT_AA										= 61,
		VP_WATERMARK_PH_CAM_NAME									= 62,
		VP_WATERMARK_PH_CAM_FL										= 63,
		VP_WATERMARK_PH_CAM_TARGETDIST						= 64,
		VP_WATERMARK_PH_CAM_WB										= 65,
		VP_WATERMARK_PH_CAM_PHY_FNUMBER						= 66,
		VP_WATERMARK_PH_CAM_PHY_ISO								= 67,
		VP_WATERMARK_PH_CAM_PHY_GAIN							= 68,
		VP_WATERMARK_PH_CAM_PHY_SHUTTER						= 69,
		VP_WATERMARK_PH_CAM_PHY_DISTORT						= 70,
		VP_WATERMARK_PH_CAM_PHY_ABERRATION				= 71,
		VP_WATERMARK_PH_STARTTIME									= 72,
		VP_WATERMARK_PH_STARTDATE									= 73,
		VP_WATERMARK_PH_RENDERSETTING							= 74,
		VP_WATERMARK_PH_XMB_SAMPLER								= 75,
		VP_WATERMARK_PH_GI_SAMPLING_HEMISPHERIC		= 78,
		VP_WATERMARK_PH_GI_SAMPLING_AREA					= 79,
		VP_WATERMARK_PH_GI_SAMPLING_SKY						= 80,
		VP_WATERMARK_PH_GI_SAMPLING_RADMAP				= 81,
    VP_WATERMARK_PH_TAKE                      = 82,
		VP_WATERMARK_PH_TRCOMPNAME								= 83,

  VP_WATERMARK_ADVANCED											= 10100,		// GROUP
	VP_WATERMARK_ADVANCED_ADDMULTIPASS				= 10101,		// BOOL
	VP_WATERMARK_ADVANCED_RENDERHUD						= 10102,			// BOOL
  VP_WATERMARK_TEXT_TAKE                    = 10103			// BOOL
};

#endif // VPWATERMARK_H__