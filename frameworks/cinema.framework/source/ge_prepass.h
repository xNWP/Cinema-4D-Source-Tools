/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

/// @defgroup group_enumeration Enumeration

/// @defgroup group_containerid Container ID

/// @defgroup group_macro Macro

/// @defgroup group_library Library

/// @defgroup group_function Function

#ifndef GE_PREPASS_H__
#define GE_PREPASS_H__

#include "ge_math.h"

/// @addtogroup MACFILE
/// @ingroup group_enumeration
/// @{
#define MACTYPE_CINEMA		'C4DC'		///< Standard Mac type code for @C4D.
#define MACCREATOR_CINEMA	'C4D1'		///< Standard Mac creator code for @C4D.
/// @}

/// Maximum image resolution
#ifdef MAXON_TARGET_64BIT
	#define MAX_IMAGE_RESOLUTION 128000			///< If changed, also change @c MAXMIPANZ.
#else
	#define MAX_IMAGE_RESOLUTION 16000
#endif

/// @addtogroup SERVERMESSAGE
/// @ingroup group_enumeration
/// @{
enum SERVERMESSAGE
{
	SERVERMESSAGE_NONE		= 0,				///< None.

	SERVERMESSAGE_WARNING	= 1000,			///< Warning.
	SERVERMESSAGE_ERROR		= 1001,			///< Error.
	SERVERMESSAGE_INFO		= 1002			///< Info.
} ENUM_END_LIST(SERVERMESSAGE);
/// @}

/// @addtogroup RENDERJOBLIST
/// @ingroup group_enumeration
/// @{
enum RENDERJOBLIST
{
	RENDERJOBLIST_INACTIVE	= 1 << 1,			///< Inactive.
	RENDERJOBLIST_ACTIVE		= 1 << 2,			///< Active.
	RENDERJOBLIST_LOAD			= 1 << 3,			///< Load.
	RENDERJOBLIST_ALL				= 14					///< All: @ref RENDERJOBLIST_INACTIVE | @ref RENDERJOBLIST_ACTIVE | @ref RENDERJOBLIST_LOAD.
} ENUM_END_FLAGS(RENDERJOBLIST);
/// @}

/// @addtogroup MESSAGERESULT
/// @ingroup group_enumeration
/// @{
enum MESSAGERESULT
{
	MESSAGERESULT_OK = 1000,					///< Ok.
	MESSAGERESULT_NETWORKERROR,				///< Network error.
	MESSAGERESULT_UNKNOWNERROR,				///< Unknown error.
	MESSAGERESULT_MEMORYERROR					///< Memory error.
} ENUM_END_LIST(MESSAGERESULT);
/// @}

/// @addtogroup MACHINELIST
/// @ingroup group_enumeration
/// @{
enum MACHINELIST
{
	MACHINELIST_ONLINE	= 1 << 1,			///< Online.
	MACHINELIST_OFFLINE	= 1 << 0,			///< Offline.
	MACHINELIST_ALL			= 7,					///< All: @ref MACHINELIST_ONLINE | @ref MACHINELIST_OFFLINE.
} ENUM_END_FLAGS(MACHINELIST);
/// @}

/// @addtogroup VERIFICATIONBIT
/// @ingroup group_enumeration
/// @{
enum VERIFICATIONBIT
{
	VERIFICATIONBIT_0						= 0,					///< None.
	VERIFICATIONBIT_ONLINE			= 1 << 0,			///< Online.
	VERIFICATIONBIT_VERIFIED		= 1 << 1,			///< Verified.
	VERIFICATIONBIT_VERIFIEDME	= 1 << 2,			///< Certified client (set on client for server).
	VERIFICATIONBIT_SHARED			= 1 << 3,			///< Shared.
	VERIFICATIONBIT_VERIFYING		= 1 << 4,			///< Verifying.

	// Error bits
	// If an enum is added, also add it to netrender/source/common.cpp#GetErrorVerificationBits
	VERIFICATIONBIT_FAILURE								= 1 << 5,					///< Unknown.
	//VERIFICATIONBIT_FAILED							= 1 << 6,					///< Removed bit.
	VERIFICATIONBIT_SECURITYTOKENCHANGED	= 1 << 7,					///< Security token changed.
	VERIFICATIONBIT_WRONGBUILDID					= 1 << 8,					///< Wrong build ID.
	VERIFICATIONBIT_WRONGARCHITECTURE			= 1 << 9,					///< Wrong architecture.
	VERIFICATIONBIT_NOTREACHABLE		= 1 << 10,							///< Remote not reachable.
	VERIFICATIONBIT_NOANSWER			= 1 << 11,								///< This not reachable.
	VERIFICATIONBIT_WRONGSECURITYTOKEN		= 1 << 12,				///< Wrong security token.
	VERIFICATIONBIT_DEMONOTACTIVATED			= 1 << 13,				///< Demo not activated.
	VERIFICATIONBIT_REMOVING							= 1 << 14,				///< Removing.
	VERIFICATIONBIT_NORENDERSUPPORT				= 1 << 15,				///< No render support.

	VERIFICATIONBIT_INITIALIZING						= 1 << 16,			///< GUI flag only to show a please wait indicator on startup.
	VERIFICATIONBIT_VERIFICATIONESTABLISHED = 1 << 17,			///< Set soon after the persistent connection has been registered. Can be set without @ref VERIFICATIONBIT_VERIFIED on first connect and host adds itself on the server.
} ENUM_END_FLAGS(VERIFICATIONBIT);
/// @}

/// @addtogroup RENDERJOBCREATOR
/// @ingroup group_enumeration
/// @{
enum RENDERJOBCREATOR
{
	RENDERJOBCREATOR_BATCHRENDER						= (1 << 0),
	RENDERJOBCREATOR_PICTUREVIEWER					= (1 << 1),
	RENDERJOBCREATOR_USER										= (1 << 2),
	RENDERJOBCREATOR_WATCHDIRECTORY					= (1 << 3),
	RENDERJOBCREATOR_WATCHDIRECTORYSTARTUP	= (1 << 4),
	RENDERJOBCREATOR_OTHER									= (1 << 5)
} ENUM_END_FLAGS(RENDERJOBCREATOR);
/// @}

enum DETAILSELECTOR
{
	DETAILSELECTOR_NONE										= 0,
	DETAILSELECTOR_SELECTED								= (1 << 0),
	DETAILSELECTOR_NONSELECTED						= (1 << 1)
} ENUM_END_FLAGS(DETAILSELECTOR);

/// @addtogroup STATUSNETSTATE
/// @ingroup group_enumeration
/// @{
enum STATUSNETSTATE
{
	STATUSNETSTATE_NONE = 0,					///< None.
	STATUSNETSTATE_DISABLE,						///< Disable.
	STATUSNETSTATE_IDLE,							///< Idle.
	STATUSNETSTATE_BUSY,							///< Busy.
	STATUSNETSTATE_BUSY2,							///< Busy 2.
	STATUSNETSTATE_CRITICAL						///< Critical.
} ENUM_END_FLAGS(STATUSNETSTATE);
/// @}

#define C4DUUID_SIZE 16							///< Size of the C4DUuid object.

/// @addtogroup FILTER
/// @ingroup group_enumeration
/// @{
/// Bitmap file formats.
#define FILTER_TIF								1100				///< TIFF
#define FILTER_TGA								1101				///< TGA
#define FILTER_BMP								1102				///< BMP
#define FILTER_IFF								1103				///< IFF
#define FILTER_JPG								1104				///< JPEG
#define FILTER_PICT								1105				///< PICT
#define FILTER_PSD								1106				///< PSD
#define FILTER_RLA								1107				///< RLA
#define FILTER_RPF								1108				///< RPF
#define FILTER_B3D								1109				///< @BP3D
#define FILTER_TIF_B3D						1110				///< TIFF @BP3D
#define FILTER_PSB								1111				///< PSB
#define FILTER_AVI								1122				///< AVI Movie
#define FILTER_MOVIE							1125				///< QuickTime Movie
#define FILTER_QTVRSAVER_PANORAMA	1150				///< QTVR Panorama
#define FILTER_QTVRSAVER_OBJECT		1151				///< QTVR Object
#define FILTER_HDR								1001379			///< HDR
#define FILTER_EXR_LOAD						1016605			///< EXR (Load)
#define FILTER_EXR								1016606			///< EXR
#define FILTER_PNG								1023671			///< PNG
#define FILTER_IES								1024463			///< IES
#define FILTER_B3DNET							1099				///< @BP3D NET @markPrivate
#define FILTER_DPX								1023737			///< DPX
/// @}

/// @addtogroup AVISAVER
/// @ingroup group_containerid
/// @{
/// Container IDs for the AVI movie saver.\n
/// Undocumented. Refer to the AVI format documentation.
#define AVISAVER_FCCTYPE		10000
#define AVISAVER_FCCHANDLER	10001
#define AVISAVER_LKEY				10002
#define AVISAVER_LDATARATE	10003
#define AVISAVER_LQ					10004
/// @}

/// @addtogroup QTSAVER
/// @ingroup group_containerid
/// @{
/// Container IDs for the QT movie saver.\n
/// Undocumented. Refer to the QuickTime format documentation.
#define QTSAVER_COMPRESSOR			10010
#define QTSAVER_QUALITY					10011
#define QTSAVER_TEMPQUAL				10012
#define QTSAVER_FRAMERATE				10013
#define QTSAVER_KEYFRAMES				10014
#define QTSAVER_PLANES					10015
#define QTSAVER_DATARATE				10016
#define QTSAVER_FRAMEDURATION		10017
#define QTSAVER_MINQUALITY			10018
#define QTSAVER_MINTEMPQUAL			10019
#define QTSAVER_FIXEDFRAMERATE	10020
/// @}

/// @addtogroup MISCSAVER
/// @ingroup group_containerid
/// @{
/// Container IDs for image savers.
#define JPGSAVER_QUALITY	10021			///< Quality of JPEG images. A value between @em 0 (lowest) and @em 100 (highest).
#define IMAGESAVER_DPI		10022			///< Resolution in dots per inch.
#define PNG_INTERLACED		11000			///< If @formatConstant{true}, @ref FILTER_PNG will save an interlaced @em PNG.
#define RLA_OPTIONS				10024			///< RLA options: @enumerateEnum{RLAFLAGS}
#define DPX_PLANAR				11000			///< If @formatConstant{true}, @ref FILTER_DPX will save the color channels out in blocks; i.e. all red parts of the pixels, then all green parts of the pixels, then all blue.
/// @}

/// @addtogroup RLAFLAGS
/// @ingroup group_enumeration
/// @{
enum RLAFLAGS
{
	RLAFLAGS_0								= 0,							///< None.
	RLAFLAGS_Z								= (1 << 0),				///< Z.
	RLAFLAGS_OBJECTBUFFER			= (1 << 2),				///< Object buffer.
	RLAFLAGS_UV								= (1 << 3),				///< UV coordinates.
	RLAFLAGS_NORMAL						= (1 << 4),				///< Normals.
	RLAFLAGS_ORIGCOLOR				= (1 << 5),				///< Non-clamped color.
	RLAFLAGS_COVERAGE					= (1 << 6),				///< Coverage.
	RLAFLAGS_OBJECTID					= (1 << 8),				///< Object ID.
	RLAFLAGS_COLOR						= (1 << 9),				///< Color.
	RLAFLAGS_TRANSPARENCY			= (1 << 10),			///< Transparency.
	RLAFLAGS_SUBPIXEL_WEIGHT	= (1 << 12),			///< Sub-pixel weight.
	RLAFLAGS_SUBPIXEL_MASK		= (1 << 13)				///< Sub-pixel mask.
} ENUM_END_FLAGS(RLAFLAGS);
/// @}

/// @addtogroup ASSETDATA_FLAG
/// @ingroup group_enumeration
/// @{
enum ASSETDATA_FLAG
{
	ASSETDATA_FLAG_0								= 0,						///< None.
	ASSETDATA_FLAG_CURRENTFRAMEONLY	= (1 << 0),			///< Only return current frame assets.
	ASSETDATA_FLAG_TEXTURESONLY			= (1 << 1),			///< Only return texture assets. @since R17.048 (was @c ASSETDATA_FLAG_TEXTURES)
	ASSETDATA_FLAG_NET							= (1 << 2),			///< Set if NET is collecting assets to distribute them to the clients.
	ASSETDATA_FLAG_CURRENTTAKEONLY  = (1 << 3),			///< Only return current take assets. @since R17
	ASSETDATA_FLAG_WITHCACHES				= (1 << 4),			///< Also return caches. (Global Illumination / Ambient Occlusion) @since R17.048
	ASSETDATA_FLAG_NOSUBSTANCES			= (1 << 5)			///< Normally Substance Assets are included on ASSETDATA_FLAG_TEXTURESONLY, with this flag they aren't
} ENUM_END_FLAGS(ASSETDATA_FLAG);
/// @}

/// @addtogroup SAVEBIT
/// @ingroup group_enumeration
/// @{
/// Flags for the opening/saving of @link BaseBitmap bitmaps@endlink.
enum SAVEBIT
{
	SAVEBIT_0									= 0,						///< None.
	SAVEBIT_ALPHA							= (1 << 0),			///< Save the alpha channel(s) in the file. (For filter plugins, do not save an alpha channel if this is not set.)
	SAVEBIT_MULTILAYER				= (1 << 1),			///< Save multiple layers.
	SAVEBIT_USESELECTEDLAYERS	= (1 << 2),			///< Use selected layers.
	SAVEBIT_16BITCHANNELS			= (1 << 3),			///< Use <i>16</i>-bit channels.
	SAVEBIT_GREYSCALE					= (1 << 4),			///< Save in grayscale mode.
	SAVEBIT_INTERNALNET				= (1 << 5),			///< @markPrivate
	SAVEBIT_DONTMERGE					= (1 << 7),			///< Avoid merging of layers in @BP3D files.
	SAVEBIT_32BITCHANNELS			= (1 << 8),			///< Use <i>32</i>-bit channels.
	SAVEBIT_SAVERENDERRESULT	= (1 << 9),			///< @markPrivate
	SAVEBIT_FIRSTALPHA_ONLY		= (1 << 10)			///< @markPrivate
} ENUM_END_FLAGS(SAVEBIT);
/// @}

/// @addtogroup SCENEFILTER
/// @ingroup group_enumeration
/// @{
/// Scene filter flags for the loading, saving and merging of documents.
/// @see LoadDocument() SaveDocument() MergeDocument()
enum SCENEFILTER
{
	SCENEFILTER_0									= 0,																	///< None.
	SCENEFILTER_OBJECTS						= (1 << 0),														///< Load/save only the objects and associated items, such as materials used.
	SCENEFILTER_MATERIALS					= (1 << 1),														///< Load/save only the materials.
	SCENEFILTER_DIALOGSALLOWED		= (1 << 3),														///< Flag to inform a plugin that a dialog can be displayed. If this flag is not set then no dialogs must be opened.
	SCENEFILTER_PROGRESSALLOWED		= (1 << 4),														///< Flag to inform a plugin that a progress bar can be displayed. The progress bar can be set by calling StatusSetBar().
	SCENEFILTER_MERGESCENE				= (1 << 5),														///< Flag to inform a plugin that this is a merge operation, i.e. the document that is inserted to is an existing scene.
	SCENEFILTER_NONEWMARKERS			= (1 << 6),														///< Objects loaded from disk will keep their markers (GeMarker).
	SCENEFILTER_SAVECACHES				= (1 << 7),														///< For @em melange export only. Caches of objects will also be written (only supported by @C4D format). This is the same as the global option <i>"Save Polygon Objects for Melange Exchange"</i>.
	SCENEFILTER_NOUNDO						= (1 << 8),														///< Use together with @ref SCENEFILTER_MERGESCENE to avoid that undos are created for the merge operation.
	SCENEFILTER_SAVE_BINARYCACHE	= (1 << 10),													///< Save the binary compiled shaders with the scene (only for @C4D format).
	SCENEFILTER_IDENTIFY_ONLY			= (1 << 11),													///< Do not load the whole document, identify it only.
	SCENEFILTER_ONLY_RENDERDATA		= (1 << 12),													///< Only load render settings. If this flag is set, @ref SCENEFILTER_OBJECTS and @ref SCENEFILTER_MATERIALS are ignored.
	SCENEFILTER_IGNOREMISSINGPLUGINSINNONACTIVERENDERDATA = (1 << 13),	///< Ignore all missing plugins which are part of a non-active render data.
	SCENEFILTER_IGNOREXREFS				= (1 << 14),													///< Avoid that included X-Refs will be loaded. @since R16.038
	SCENEFILTER_DONTCORRECTOUTPUTFORMAT = (1 << 15)											///< Do not change unknown output formats in render settings.
} ENUM_END_FLAGS(SCENEFILTER);
/// @}

/// @addtogroup GEMB
/// @ingroup group_enumeration
/// @{
/// Flags for GeOutString().
enum GEMB
{
	GEMB_OK								= 0x0000,			///< OK.
	GEMB_OKCANCEL					= 0x0001,			///< OK and Cancel.
	GEMB_ABORTRETRYIGNORE	= 0x0002,			///< Abort, Retry and Ignore.
	GEMB_YESNOCANCEL			= 0x0003,			///< Yes, No and Cancel.
	GEMB_YESNO						= 0x0004,			///< Yes and No.
	GEMB_RETRYCANCEL			= 0x0005,			///< Retry and Cancel.
	GEMB_FORCEDIALOG			= 0x8000,			///< Forces the dialog.
	GEMB_ICONSTOP					= 0x0010,			///< Stop icon.
	GEMB_ICONQUESTION			= 0x0020,			///< Question icon.
	GEMB_ICONEXCLAMATION	= 0x0030,			///< Exclamation icon.
	GEMB_ICONASTERISK			= 0x0040,			///< Asterisk icon.
	GEMB_MULTILINE				= 0x0080			///< If the message is more than @em 255 characters and @em 4 lines then this bit should be set for Mac compatibility.\n
																			///< The dialog is then restricted to only an OK button with limited keyboard support.
} ENUM_END_FLAGS(GEMB);
/// @}

/// @addtogroup GEMB_R
/// @ingroup group_enumeration
/// @{
/// Return values for GeOutString().
enum GEMB_R
{
	GEMB_R_UNDEFINED	= 0,			///< Undefined.
	GEMB_R_OK					= 1,			///< OK button.
	GEMB_R_CANCEL			= 2,			///< Cancel button.
	GEMB_R_ABORT			= 3,			///< Abort button.
	GEMB_R_RETRY			= 4,			///< Retry button.
	GEMB_R_IGNORE			= 5,			///< Ignore button.
	GEMB_R_YES				= 6,			///< Yes button.
	GEMB_R_NO					= 7				///< No button.
} ENUM_END_LIST(GEMB_R);
/// @}

/// @addtogroup MOUSEDRAGRESULT
/// @ingroup group_enumeration
/// @{
/// Result codes for EditorWindow::MouseDrag.
enum MOUSEDRAGRESULT
{
	MOUSEDRAGRESULT_ESCAPE		= 1,			///< Drag aborted.
	MOUSEDRAGRESULT_FINISHED	= 2,			///< Drag finished.
	MOUSEDRAGRESULT_CONTINUE	= 3				///< Drag still in progress.
} ENUM_END_LIST(MOUSEDRAGRESULT);
/// @}

/// @addtogroup MOUSEDRAGFLAGS
/// @ingroup group_enumeration
/// @{
/// @see EditorWindow::MouseDragStart() EditorWindow::MouseDrag() GeUserArea::MouseDragStart() GeUserArea::MouseDrag()
enum MOUSEDRAGFLAGS
{
	MOUSEDRAGFLAGS_0											= 0,						///< None.
	MOUSEDRAGFLAGS_DONTHIDEMOUSE					= (1 << 0),			///< Show mouse pointer during drag.
	MOUSEDRAGFLAGS_NOMOVE									= (1 << 1),			///< @c MouseDrag() returns @ref MOUSEDRAGRESULT_CONTINUE even if mouse is not moved. Otherwise @c MouseDrag() only returns if mouse is moved.
	MOUSEDRAGFLAGS_EVERYPACKET						= (1 << 2),			///< Receive every packet of the queue, otherwise only data of the last packet.
	MOUSEDRAGFLAGS_COMPENSATEVIEWPORTORG	= (1 << 3),			///< Compensates the viewport origin during drag.
	MOUSEDRAGFLAGS_AIRBRUSH								= (1 << 4)			///< Airbrush mode.
} ENUM_END_FLAGS(MOUSEDRAGFLAGS);
/// @}

/// @addtogroup INITRENDERRESULT
/// @ingroup group_enumeration
/// @{
/// Result codes for @c InitRender() calls in the rendering API.
enum INITRENDERRESULT
{
	INITRENDERRESULT_OK						= 0,				///< Everything is OK, there was no error.
	INITRENDERRESULT_OUTOFMEMORY	= -100,			///< Not enough memory.
	INITRENDERRESULT_ASSETMISSING	= -101,			///< Assets (textures etc.) are missing.
	INITRENDERRESULT_UNKNOWNERROR	= -102,			///< Unknown error.
	INITRENDERRESULT_USERBREAK		= -103			///< Thread has been canceled. @since R17.032 Was @c INITRENDERRESULT_THREADEDLOCK.
} ENUM_END_LIST(INITRENDERRESULT);
/// @}

/// @addtogroup RENDERRESULT
/// @ingroup group_enumeration
/// @{
/// Result codes for the <tt>Render()</tt> calls in the rendering API.
enum RENDERRESULT
{
	RENDERRESULT_OK										= 0,				///< Function was successful.
	RENDERRESULT_OUTOFMEMORY					= 1,				///< Not enough memory.
	RENDERRESULT_ASSETMISSING					= 2,				///< Assets (textures etc.) are missing.
	RENDERRESULT_SAVINGFAILED					= 5,				///< Failed to save.
	RENDERRESULT_USERBREAK						= 6,				///< %User stopped the processing.
	RENDERRESULT_GICACHEMISSING				= 7,				///< GI cache is missing.
	RENDERRESULT_NOMACHINE						= 9,				///< Machine was not found. Can only happen during Team Rendering.

	RENDERRESULT_PROJECTNOTFOUND			= 1000,			///< Project was not found. Can only be returned by @C4D during command line rendering.
	RENDERRESULT_ERRORLOADINGPROJECT	= 1001,			///< There was an error while loading the project. Can only be returned by @C4D during command line rendering.
	RENDERRESULT_NOOUTPUTSPECIFIED		= 1002			///< Output was not specified. Can only be returned by @C4D during command line rendering.
} ENUM_END_LIST(RENDERRESULT);
/// @}

/// @addtogroup BITDEPTH
/// @ingroup group_enumeration
/// @{
#define BITDEPTH_SHIFT		4			/// Number of color info bits.
#define BITDEPTH_MAXMODES	3			/// Number of color modes.

#define BITDEPTH_UCHAR	0			/// ::UChar (<i>8</i>-bit).
#define BITDEPTH_UWORD	1			/// ::UInt16 (<i>16</i>-bit).
#define BITDEPTH_FLOAT	2			/// ::Float (<i>32</i>-bit).
/// @}

/// @addtogroup COLORMODE
/// @ingroup group_enumeration
/// @{
/// The color mode for @link BaseBitmap bitmaps@endlink.\n
/// The most common values are @ref COLORMODE_RGB for <i>24</i>-bit RGB @link BaseBitmap bitmaps@endlink and @ref COLORMODE_GRAY for <i>8</i>-bit grayscale @link BaseBitmap bitmaps@endlink.
enum COLORMODE
{
	// <i>8</i>-bit modes

	COLORMODE_ILLEGAL	= 0,			///< Illegal <i>8</i>-bit mode.

	COLORMODE_ALPHA		= 1,			///< Only <i>8</i>-bit alpha channel.
	COLORMODE_GRAY		= 2,			///< <i>8</i>-bit grayscale channel.
	COLORMODE_AGRAY		= 3,			///< <i>8</i>-bit grayscale channel with <i>8</i>-bit alpha.
	COLORMODE_RGB			= 4,			///< <i>8</i>-bit RGB channels.
	COLORMODE_ARGB		= 5,			///< <i>8</i>-bit RGB channels with <i>8</i>-bit alpha.
	COLORMODE_CMYK		= 6,			///< <i>8</i>-bit CMYK channel.
	COLORMODE_ACMYK		= 7,			///< <i>8</i>-bit CMYK channel with <i>8</i>-bit alpha.
	COLORMODE_MASK		= 8,			///< <i>8</i>-bit grayscale map as mask.
	COLORMODE_AMASK		= 9,			///< <i>8</i>-bit grayscale map as mask with <i>8</i>-bit alpha.

	// <i>16</i>-bit modes

	COLORMODE_ILLEGALw	= (BITDEPTH_UWORD << BITDEPTH_SHIFT),													///< Illegal <i>16</i>-bit mode.

	COLORMODE_GRAYw			= (COLORMODE_GRAY | (BITDEPTH_UWORD << BITDEPTH_SHIFT)),			///< <i>16</i>-bit grayscale channel.
	COLORMODE_AGRAYw		= (COLORMODE_AGRAY | (BITDEPTH_UWORD << BITDEPTH_SHIFT)),			///< <i>16</i>-bit grayscale channel with <i>16</i>-bit alpha.
	COLORMODE_RGBw			= (COLORMODE_RGB | (BITDEPTH_UWORD << BITDEPTH_SHIFT)),				///< <i>16</i>-bit RGB channels.
	COLORMODE_ARGBw			= (COLORMODE_ARGB | (BITDEPTH_UWORD << BITDEPTH_SHIFT)),			///< <i>16</i>-bit RGB channels with <i>16</i>-bit alpha.
	COLORMODE_MASKw			= (COLORMODE_MASK | (BITDEPTH_UWORD << BITDEPTH_SHIFT)),			///< <i>16</i>-bit grayscale map as mask.

	// <i>32</i>-bit modes

	COLORMODE_ILLEGALf	= (BITDEPTH_FLOAT << BITDEPTH_SHIFT),													///< Illegal <i>32</i>-bit mode.

	COLORMODE_GRAYf			= (COLORMODE_GRAY | (BITDEPTH_FLOAT << BITDEPTH_SHIFT)),			///< <i>32</i>-bit floating point grayscale channel.
	COLORMODE_AGRAYf		= (COLORMODE_AGRAY | (BITDEPTH_FLOAT << BITDEPTH_SHIFT)),			///< <i>32</i>-bit floating point grayscale channel with floating point alpha.
	COLORMODE_RGBf			= (COLORMODE_RGB | (BITDEPTH_FLOAT << BITDEPTH_SHIFT)),				///< <i>32</i>-bit floating point RGB channels.
	COLORMODE_ARGBf			= (COLORMODE_ARGB | (BITDEPTH_FLOAT << BITDEPTH_SHIFT)),			///< <i>32</i>-bit floating point RGB channels with floating point alpha.
	COLORMODE_MASKf			= (COLORMODE_MASK | (BITDEPTH_FLOAT << BITDEPTH_SHIFT))				///< <i>32</i>-bit floating point grayscale map as mask.
} ENUM_END_FLAGS(COLORMODE);
/// @}

/// @addtogroup COLORSPACETRANSFORMATION
/// @ingroup group_enumeration
/// @{
/// Color space transformations.
enum COLORSPACETRANSFORMATION
{
	COLORSPACETRANSFORMATION_NONE						= 0,			///< None.
	COLORSPACETRANSFORMATION_LINEAR_TO_SRGB	= 1,			///< Linear to sRGB color space transformation.
	COLORSPACETRANSFORMATION_SRGB_TO_LINEAR	= 2,			///< sRGB to linear color space transformation.

	COLORSPACETRANSFORMATION_LINEAR_TO_VIEW	= 10,			///< Linear to display color space transformation.
	COLORSPACETRANSFORMATION_SRGB_TO_VIEW		= 11			///< sRGB to display color space transformation.
} ENUM_END_LIST(COLORSPACETRANSFORMATION);
/// @}

/// @addtogroup PIXELCNT
/// @ingroup group_enumeration
/// @{
/// Flags for @ref BaseBitmap::GetPixelCnt/@ref BaseBitmap::SetPixelCnt
enum PIXELCNT
{
	PIXELCNT_0										= 0,							///< None.
	PIXELCNT_DITHERING						= (1 << 0),				///< Allow dithering.
	PIXELCNT_B3DLAYERS						= (1 << 1),				///< Merge @BP3D layers (MultipassBitmap).
	PIXELCNT_APPLYALPHA						= (1 << 2),				///< Apply alpha layers to the result (PaintLayer).
	PIXELCNT_INTERNAL_SETLINE			= (1 << 29),			///< Internal SetLine indicator. @markPrivate
	PIXELCNT_INTERNAL_ALPHAVALUE	= (1 << 30)				///< Get also the alpha value (RGBA <i>32</i>-bit). @markPrivate
} ENUM_END_FLAGS(PIXELCNT);
/// @}

/// @addtogroup INITBITMAPFLAGS
/// @ingroup group_enumeration
/// @{
/// Flags for the initialization of @link BaseBitmap bitmaps@endlink.
/// @see BaseBitmap::Init(Int32 x, Int32 y, Int32 depth = 24, INITBITMAPFLAGS flags = INITBITMAPFLAGS_0)
enum INITBITMAPFLAGS
{
	INITBITMAPFLAGS_0					= 0,						///< None.
	INITBITMAPFLAGS_GRAYSCALE	= (1 << 0),			///< Initialize as grayscale bitmap.
	INITBITMAPFLAGS_SYSTEM		= (1 << 1)			///< @markPrivate
} ENUM_END_FLAGS(INITBITMAPFLAGS);
/// @}

/// @addtogroup MPB_GETLAYERS
/// @ingroup group_enumeration
/// @{
/// Flags for MultipassBitmap::GetLayers.
enum MPB_GETLAYERS
{
	MPB_GETLAYERS_0			= 0,						///< None.
	MPB_GETLAYERS_ALPHA	= (1 << 1),			///< Get alpha layers.
	MPB_GETLAYERS_IMAGE	= (1 << 2)			///< Get image layers.
} ENUM_END_FLAGS(MPB_GETLAYERS);
/// @}

/// @addtogroup MPBTYPE
/// @ingroup group_containerid
/// @{
/// Container IDs for @ref MultipassBitmap::GetParameter/@ref MultipassBitmap::SetParameter.
enum MPBTYPE
{
	MPBTYPE_SHOW				= 1000,			///< ::Bool Get/Set. Determines if the layer will be shown in the external render window. (The @C4D renderer modifies this value itself.)
	MPBTYPE_SAVE				= 1001,			///< ::Bool Get/Set. Determines if the layer is saved with the image or not if @ref SAVEBIT_USESELECTEDLAYERS is used.
	MPBTYPE_PERCENT			= 1002,			///< ::Float Get/Set. The blend parameter, between @em 0.0 and @em 1.0.
	MPBTYPE_BLENDMODE		= 1003,			///< ::Int32 Get/Set. The blend mode (LAYER_NORMAL, LAYER_DISSOLVE etc. from @em bplayer.h).
	MPBTYPE_COLORMODE		= 1004,			///< ::Int32 Get/Set. The color mode: @enumerateEnum{COLORMODE}
	MPBTYPE_BITMAPTYPE	= 1005,			///< ::Int32 Get. The bitmap type (cannot be set with MultipassBitmap::SetParameter).
	MPBTYPE_NAME				= 1006,			///< String Get/Set. The layer name. @warning Only a PaintLayerBmp or PaintLayerFolder can have a name.
	MPBTYPE_DPI					= 1007,			///< ::Int32 Get/Set. The resolution in DPI. @markPrivate
	MPBTYPE_USERID			= 1008,			///< ::Int32 Get/Set. The user ID for the layer. In the renderer this is @em VPBUFFER_XXX.
	MPBTYPE_USERSUBID		= 1009,			///< ::Int32 Get/Set. The user sub-ID for the layer. In the renderer this is used for blend channels for instance.
	MPBTYPE_FORCEBLEND	= 1010			///< ::Int32 Get/Set. The special mode used to force blend layers.
} ENUM_END_LIST(MPBTYPE);
/// @}

/// @addtogroup LENGTHUNIT
/// @ingroup group_enumeration
/// @{
/// @see StringToNumber
enum LENGTHUNIT
{
	LENGTHUNIT_PIXEL	= 0,			///< Pixel.
	LENGTHUNIT_KM			= 1,			///< Kilometer.
	LENGTHUNIT_M			= 2,			///< Meter.
	LENGTHUNIT_CM			= 3,			///< Centimeter.
	LENGTHUNIT_MM			= 4,			///< Millimeter.
	LENGTHUNIT_UM			= 5,			///< Micrometer.
	LENGTHUNIT_NM			= 6,			///< Nanometer.
	LENGTHUNIT_MILE		= 7,			///< Mile.
	LENGTHUNIT_YARD		= 8,			///< Yard.
	LENGTHUNIT_FEET		= 9,			///< Feet.
	LENGTHUNIT_INCH		= 10			///< Inch.
} ENUM_END_LIST(LENGTHUNIT);
/// @}

/// @addtogroup SPLINETYPE
/// @ingroup group_enumeration
/// @{
/// Spline types.
/// @see SplineObject::Alloc SplineObject::GetInterpolationType
enum SPLINETYPE
{
	SPLINETYPE_LINEAR			= 0,		///< Linear.
	SPLINETYPE_CUBIC			= 1,		///< Cubic.
	SPLINETYPE_AKIMA			= 2,		///< Akima.
	SPLINETYPE_BSPLINE		= 3,		///< B-Spline.
	SPLINETYPE_BEZIER			= 4,		///< Bezier.
	RESERVEDSPLINETYPE1		= 5,		///< @markInternal @since R17.032
	RESERVEDSPLINETYPE2		= 6			///< @markInternal @since R17.032
} ENUM_END_LIST(SPLINETYPE);
/// @}

/// @addtogroup BREAKTANGENTS
/// @ingroup group_enumeration
/// @{
/// @since R17.032
enum BREAKTANGENTS
{
	BREAKTANGENTS_FALSE	=	0,			///< Do not break any tangents.
	BREAKTANGENTS_TRUE	=	1,			///< Break the tangents.
	BREAKTANGENTS_AUTO	= 2				///< Only break the tangents if the tangents are already broken.
} ENUM_END_LIST(BREAKTANGENTS);
/// @}

/// @addtogroup TANGENTSIDE
/// @ingroup group_enumeration
/// @{
/// @since R17.032
enum TANGENTSIDE
{
	TANGENTSIDE_0							=	-1,			///< No tangent handles being modified.
	TANGENTSIDE_LEFT					= 0,			///< Modify the left tangent handle.
	TANGENTSIDE_RIGHT					= 1,			///< Modify the right tangent handle.
} ENUM_END_LIST(TANGENTSIDE);
/// @}

/// @addtogroup TANGENTTRANSFORMFLAG
/// @ingroup group_enumeration
/// @{
/// @since R17.032
enum TANGENTTRANSFORMFLAG
{
	TANGENTTRANSFORMFLAG_0							=	0,																					///< No transform flag.
	TANGENTTRANSFORMFLAG_LOCK_LENGTH		=	(1 << 0),																		///< Fix the length of the tangents, only change the rotation.
	TANGENTTRANSFORMFLAG_LOCK_ANGLE			=	(1 << 1),																		///< Fix the angle of the tangents, only change the length.
	TANGENTTRANSFORMFLAG_BREAK_SCALE		=	(1 << 2),																		///< Only scale one handle (but rotate both).
	TANGENTTRANSFORMFLAG_BREAK					=	TANGENTTRANSFORMFLAG_BREAK_SCALE|(1 << 3)		///< Only modify one handle.
} ENUM_END_FLAGS(TANGENTTRANSFORMFLAG);
/// @}

/// @addtogroup SPLINEBOOL_AXIS
/// @ingroup group_enumeration
/// @{
/// @since R17.032
enum SPLINEBOOL_AXIS
{
	SPLINEBOOL_AXIS_0					= 0,			///< No axis.
	SPLINEBOOL_AXIS_SCREEN		=	1,			///< Project into the current screen.
	SPLINEBOOL_AXIS_ZY				=	2,			///< Project on the ZY (X axis) plane.
	SPLINEBOOL_AXIS_XZ				= 3,			///< Project on the XZ (Y axis) plane.
	SPLINEBOOL_AXIS_XY				= 4				///< Project on the XY (Z axis) plane.
} ENUM_END_LIST(SPLINEBOOL_AXIS);
/// @}

/// @addtogroup SPLINEBOOL_MODE
/// @ingroup group_enumeration
/// @{
/// @since R17.032
enum SPLINEBOOL_MODE
{
	SPLINEBOOL_MODE_AMINUSB				=	0,			///< Subtract B from A.
	SPLINEBOOL_MODE_BMINUSA				=	1,			///< Subtract A from B.
	SPLINEBOOL_MODE_UNION					=	2,			///< Union of both A and B.
	SPLINEBOOL_MODE_AND						=	3,			///< And intersection (overlap) of region of A and B.
	SPLINEBOOL_MODE_OR						=	4,			///< Or intersection (outside of overlap) of region of A and B.
	SPLINEBOOL_MODE_INTERSECTION	=	5,			///< Intersection (all segments inside and out) of region of A and B.
} ENUM_END_LIST(SPLINEBOOL_MODE);
/// @}

/// @addtogroup PARTICLEFLAGS
/// @ingroup group_enumeration
/// @{
/// @see Particle
enum PARTICLEFLAGS
{
	PARTICLEFLAGS_0				= 0,						///< None.
	PARTICLEFLAGS_VISIBLE	= (1 << 0),			///< %Particle is visible.
	PARTICLEFLAGS_ALIVE		= (1 << 1)			///< %Particle is alive.
} ENUM_END_FLAGS(PARTICLEFLAGS);
/// @}

/// @addtogroup NBIT
/// @ingroup group_enumeration
/// @{
/// GeListNode bits.
/// @see GeListNode::GetNBit GeListNode::ChangeNBit
enum NBIT
{
	NBIT_0										= 0,			///< None.

	NBIT_TL1_FOLD							= 1,			///< Folding bit for Timeline 1.
	NBIT_TL2_FOLD							= 2,			///< Folding bit for Timeline 2.
	NBIT_TL3_FOLD							= 3,			///< Folding bit for Timeline 3.
	NBIT_TL4_FOLD							= 4,			///< Folding bit for Timeline 4.

	NBIT_TL1_SELECT						= 5,			///< Selection bit for Timeline 1.
	NBIT_TL2_SELECT						= 6,			///< Selection bit for Timeline 2.
	NBIT_TL3_SELECT						= 7,			///< Selection bit for Timeline 3.
	NBIT_TL4_SELECT						= 8,			///< Selection bit for Timeline 4.

	NBIT_TL1_TDRAW						= 9,			///< @markPrivate
	NBIT_TL2_TDRAW						= 10,			///< @markPrivate
	NBIT_TL3_TDRAW						= 11,			///< @markPrivate
	NBIT_TL4_TDRAW						= 12,			///< @markPrivate

	NBIT_CKEY_ACTIVE					= 13,			///< Active point of animation path in editor.

	NBIT_OM1_FOLD							= 14,			///< Folding bit for Object Manager 1.
	NBIT_OM2_FOLD							= 15,			///< Folding bit for Object Manager 2.
	NBIT_OM3_FOLD							= 16,			///< Folding bit for Object Manager 3.
	NBIT_OM4_FOLD							= 17,			///< Folding bit for Object Manager 4.

	NBIT_TL1_FOLDTR						= 18,			///< Track folding for Timeline 1.
	NBIT_TL2_FOLDTR						= 19,			///< Track folding for Timeline 2.
	NBIT_TL3_FOLDTR						= 20,			///< Track folding for Timeline 3.
	NBIT_TL4_FOLDTR						= 21,			///< Track folding for Timeline 4.

	NBIT_TL1_FOLDFC						= 22,			///< F-Curve folding for Timeline 1.
	NBIT_TL2_FOLDFC						= 23,			///< F-Curve folding for Timeline 2.
	NBIT_TL3_FOLDFC						= 24,			///< F-Curve folding for Timeline 3.
	NBIT_TL4_FOLDFC						= 25,			///< F-Curve folding for Timeline 4.

	NBIT_SOURCEOPEN						= 26,

	NBIT_TL1_HIDE							= 27,			///< Hide in Timeline 1.
	NBIT_TL2_HIDE							= 28,			///< Hide in Timeline 2.
	NBIT_TL3_HIDE							= 29,			///< Hide in Timeline 3.
	NBIT_TL4_HIDE							= 30,			///< Hide in Timeline 4.

	NBIT_SOLO_ANIM						= 31,			///< Solo animation.
	NBIT_SOLO_LAYER						= 32,			///< Solo layer.

	NBIT_TL1_SELECT2					= 33,			///< @markPrivate
	NBIT_TL2_SELECT2					= 34,			///< @markPrivate
	NBIT_TL3_SELECT2					= 35,			///< @markPrivate
	NBIT_TL4_SELECT2					= 36,			///< @markPrivate

	NBIT_SOLO_MOTION					= 37,			///< Solo motion.

	NBIT_CKEY_LOCK_T					= 38,			///< Lock key time.
	NBIT_CKEY_LOCK_V					= 39,			///< Lock key value.
	NBIT_CKEY_MUTE						= 40,			///< Mute key.
	NBIT_CKEY_CLAMP						= 41,			///< Clamp key tangents.

	NBIT_CKEY_BREAK						= 42,			///< Break key tangents.
	NBIT_CKEY_KEEPVISUALANGLE	= 43,			///< Keep visual angle.

	NBIT_CKEY_LOCK_O					= 44,			///< Lock key tangents angles.
	NBIT_CKEY_LOCK_L					= 45,			///< Lock key tangents length.
	NBIT_CKEY_AUTO						= 46,			///< Key auto tangents.
	NBIT_CKEY_ZERO_O_OLD			= 48,			///< @markDeprecated
	NBIT_CKEY_ZERO_L_OLD			= 49,			///< @markDeprecated

	NBIT_TL1_FCSELECT					= 50,			///< F-Curve selection bit for Timeline 1.
	NBIT_TL2_FCSELECT					= 51,			///< F-Curve selection bit for Timeline 2.
	NBIT_TL3_FCSELECT					= 52,			///< F-Curve selection bit for Timeline 3.
	NBIT_TL4_FCSELECT					= 53,			///< F-Curve selection bit for Timeline 4.

	NBIT_CKEY_BREAKDOWN				= 54,			///< @markPrivate

	NBIT_TL1_FOLDMOTION				= 55,			///< Motion clip folding for Timeline 1.
	NBIT_TL2_FOLDMOTION				= 56,			///< Motion clip folding for Timeline 2.
	NBIT_TL3_FOLDMOTION				= 57,			///< Motion clip folding for Timeline 3.
	NBIT_TL4_FOLDMOTION				= 58,			///< Motion clip folding for Timeline 4.

	NBIT_TL1_SELECTMOTION			= 59,			///< Motion clip selection for Timeline 1.
	NBIT_TL2_SELECTMOTION			= 60,			///< Motion clip selection for Timeline 2.
	NBIT_TL3_SELECTMOTION			= 61,			///< Motion clip selection for Timeline 3.
	NBIT_TL4_SELECTMOTION			= 62,			///< Motion clip selection for Timeline 4.

	NBIT_OHIDE								= 63,			///< Hide object in Object Manager.
	NBIT_TL_TBAKE							= 64,			///< @markPrivate

	NBIT_TL1_FOLDSM						= 66,			///< @markPrivate
	NBIT_TL2_FOLDSM						= 67,			///< @markPrivate
	NBIT_TL3_FOLDSM						= 68,			///< @markPrivate
	NBIT_TL4_FOLDSM						= 69,			///< @markPrivate

	NBIT_SUBOBJECT						= 70,			///< @markPrivate
	NBIT_LINK_ACTIVE					= 71,			///< @markPrivate
	NBIT_THIDE								= 72,			///< Hide object in Timeline.
	NBIT_SUBOBJECT_AM					= 74,			///< @markPrivate
	NBIT_PROTECTION						= 75,			///< PSR protection.
	NBIT_NOANIM								= 76,			///< No animation.
	NBIT_NOSELECT							= 77,			///< No selection.
	NBIT_EHIDE								= 78,			///< Hide in viewport.
	NBIT_REF									= 79,			///< XRef.
	NBIT_REF_NO_DD						= 80,			///< XRef object no drag and drop. @markPrivate
	NBIT_REF_OHIDE						= 81,			///< XRef object hide. @markPrivate
	NBIT_NO_DD								= 82,			///< No drag and drop duplication.
	NBIT_HIDEEXCEPTVIEWSELECT	= 83,			///< Hide in viewport except to viewport select.
	NBIT_CKEY_WEIGHTEDTANGENT = 84,			///< Weighted Tangent. @since R17.032
	NBIT_CKEY_REMOVEOVERSHOOT = 85,			///< Gradual Clamp of Tangent to avoid OverShooting. @since R17.032
	NBIT_CKEY_AUTOWEIGHT			= 86,			///< Weight still adjusted even if Angle is User Defined. @since R17.032
	NBIT_TAKE_LOCK						= 87,			///< A node in an override group cannot be changed. @since R17.032
	NBIT_TAKE_OBJINGROUP			= 88,			///< The object is overridden by an override group. @since R17.032
	NBIT_TAKE_EGROUPOVERIDDEN	= 89,			///< The object editor visibility is overridden by an override group. @since R17.032
	NBIT_TAKE_RGROUPOVERIDDEN	= 90,			///< The object render visibility is overridden by an override group. @since R17.032
	NBIT_CKEY_BREAKDOWNCOLOR	= 91,			///< This key is a golden pose. @since R18
	NBIT_NO_DELETE						= 92,			///< No delete in OM.
	NBIT_MAX									= 93,			///< Maximum @ref NBIT.
	NBIT_PRIVATE_MASK1				= -1,			///< @markPrivate
	NBIT_PRIVATE_MASK2				= -2,			///< @markPrivate
	NBIT_PRIVATE_MASK3				= -3,			///< @markPrivate
	NBIT_PRIVATE_MASK4				= -4			///< @markPrivate
} ENUM_END_LIST(NBIT);
/// @}

/// @addtogroup CREATEJOBRESULT
/// @ingroup group_enumeration
/// @{
enum CREATEJOBRESULT
{
	CREATEJOBRESULT_OK							= 0,			///< Ok.
	CREATEJOBRESULT_OUTOFMEMORY			= 1,			///< Out of memory.
	CREATEJOBRESULT_ASSETMISSING		= 2,			///< Asset missing.
	CREATEJOBRESULT_SAVINGFAILED		= 3,			///< Saving failed.
	CREATEJOBRESULT_REPOSITORYERROR	= 4				///< Repository error.
} ENUM_END_FLAGS(CREATEJOBRESULT);
/// @}

/// @addtogroup NBITCONTROL
/// @ingroup group_enumeration
/// @{
/// @see GeListNode::ChangeNBit
enum NBITCONTROL
{
	NBITCONTROL_SET							= 1,				///< Set bit.
	NBITCONTROL_CLEAR						= 2,				///< Clear bit.
	NBITCONTROL_TOGGLE					= 3,				///< Toggle bit.
	NBITCONTROL_PRIVATE_NODIRTY	= 0xf0			///< @markPrivate
} ENUM_END_FLAGS(NBITCONTROL);
/// @}

/// @addtogroup BIT
/// @ingroup group_enumeration
/// @{
/// BaseList2D bits.
/// @see	BaseList2D::SetBit BaseList2D::GetBit BaseList2D::DelBit BaseList2D::ToggleBit\n
///				BaseList2D::GetAllBits BaseList2D::SetAllBits
/// @name Active bits
/// @{
#define BIT_ACTIVE	(1 << 1)			///< Active.
#define BIT_ACTIVE2	(1 << 29)			///< @markPrivate
#define BIT_ACTIVE3	(1 << 30)			///< @markPrivate @since R17.032
/// @}
/// @name Material Bits
/// @{
#define BIT_MATMARK				(1 << 2)			///< Marked material.
#define BIT_ENABLEPAINT		(1 << 3)			///< Enable painting.
#define BIT_RECALCPREVIEW	(1 << 5)			///< Recalculate preview.
#define BIT_MFOLD					(1 << 6)			///< Folded in material manager.
#define BIT_BP_FOLDLAYERS	(1 << 9)			///< Fold layers in material manager.
/// @}
/// @name Object Bits
/// @{
#define BIT_IGNOREDRAW											(1 << 2)			///< Ignore object during draw.
#define BIT_OFOLD														(1 << 6)			///< Folded in object manager.
#define BIT_CONTROLOBJECT										(1 << 9)			///< Internal bit set by generators.
#define BIT_RECMARK													(1 << 11)			///< Help bit for recursive operations. @markPrivate
#define BIT_IGNOREDRAWBOX										(1 << 12)			///< Ignore object drawing box.
#define BIT_EDITOBJECT											(1 << 13)			///< Edit object from SDS. @markPrivate
#define BIT_ACTIVESELECTIONDRAW							(1 << 15)			///< Draw active selection.
#define BIT_TEMPDRAW_VISIBLE_CACHECHILD			(1 << 16)			///< @markPrivate. Temp bit for faster redraw.
#define BIT_TEMPDRAW_VISIBLE_DEFCACHECHILD	(1 << 17)			///< @markPrivate. Temp bit for faster redraw.
#define BIT_TEMPDRAW_VISIBLE_CHILD					(1 << 18)			///< @markPrivate. Temp bit for faster redraw.
#define BIT_HIGHLIGHT												(1 << 20)			///< Object highlighted in viewport. @markPrivate
#define BIT_FORCE_UNOPTIMIZED								(1 << 21)			///< Do not optimize the points of a polygon object during OpenGL redraw. @markPrivate
/// @}
/// @name Track Bits
/// @{
#define BIT_TRACKPROCESSED				(1 << 16)			///< Track has been processed, avoid recursions.
#define BIT_ANIM_OFF							(1 << 17)			///< Inactive sequence.
#define BIT_ANIM_SOLO							(1 << 18)			///< Solo track.
#define BIT_ANIM_CONSTANTVELOCITY	(1 << 19)			///< Constant velocity.
/// @}
/// @name Videopost Bits
/// @{
#define BIT_VPDISABLED (1 << 2)			///< Videopost is disabled.
/// @}
/// @name Document Bits
/// @{
#define BIT_DOCUMENT_CHECKREWIND (1 << 2)			///< Document needs to check for a rewind.
/// @}
/// @name RenderData Bits
/// @{
#define BIT_ACTIVERENDERDATA (1 << 28)			///< Active render data.
/// @}
/// @}

/// @addtogroup OBJECT
/// @ingroup group_enumeration
/// @{
/// Object plugin flags.
/// @see RegisterObjectPlugin() RegisterEffectorPlugin()
#define OBJECT_MODIFIER						(1 << 0)			///< Modifier object. Deforms the surrounding object. (e.g. bend)
#define OBJECT_HIERARCHYMODIFIER	(1 << 1)			///< Hierarchical modifier. Deforms the surrounding objects together with other instances in a hierarchy chain.\n
																								///< Only the top-most instance of the plugin in a chain is called. (e.g. bones)
#define OBJECT_GENERATOR					(1 << 2)			///< Generator object. Produces a polygonal or spline representation on its own. (e.g. primitive cube)
#define OBJECT_INPUT							(1 << 3)			///< Used in combination with @ref OBJECT_GENERATOR.\n
																								///< Specifies that the generator builds a polygon or spline using its sub-objects as input. (e.g. Sweep NURBS, Boolean)
#define OBJECT_PARTICLEMODIFIER		(1 << 5)			///< %Particle modifier.
#define OBJECT_NOCACHESUB					(1 << 6)			///< @markPrivate
#define OBJECT_ISSPLINE						(1 << 7)			///< Spline object.
#define OBJECT_UNIQUEENUMERATION	(1 << 8)			///< Unique enumeration. See @ref BaseObject::GetUniqueIP.
#define OBJECT_CAMERADEPENDENT		(1 << 9)			///< Camera dependent.
#define OBJECT_USECACHECOLOR			(1 << 10)			///< If this flag is specified, the generator object itself controls the objects' colors (the ones that determine the wireframe/shaded color).\n
																								///< Normally these are automatically overwritten by the generator objects settings.\n
																								///< e.g. If an instance object is set to green, automatically all of its cache objects get the green color. By setting this flag an instance object could individually color objects.
#define OBJECT_POINTOBJECT				(1 << 11)			///< Point object.
#define OBJECT_POLYGONOBJECT			(1 << 12)			///< Polygon object.
#define OBJECT_NO_PLA							(1 << 13)			///< Objects derived from PointObject will not use auto-keyframing (e.g. Joints can contain points and PLA auto-keyframing is not useful for them).
#define OBJECT_DONTFREECACHE			(1 << 14)			///< Objects' (generators) caches will not be be deleted - users must maintain caches themselves.
#define OBJECT_CALL_ADDEXECUTION	(1 << 15)			///< Must be set to call ObjectData::Execute() in the priority pipeline specified by ObjectData::AddToExecution.
/// @}

/// @addtogroup Tlistelements
/// @ingroup group_enumeration
/// @{
#define Tbaselist2d		110050			///< 2D list.
#define Tbasedocument	110059			///< Document.
#define Tpluginlayer	110064			///< Plugin layer.
#define Tundoablelist	110068			///< Undoable list node (an intermediate class that is not in the SDK).
#define Tgelistnode		110069			///< Node list.
/// @}

/// @addtogroup MaterialTypes Material Types
/// @ingroup group_enumeration
/// @{
#define Mbase				5702					///< Base material.
#define Mmaterial		5703					///< Standard material.
#define Mplugin			5705					///< Plugin material - pass the plugin ID.
#define Mfog				8803					///< Fog.
#define Mterrain		8808					///< Terrain.
#define Mdanel			1011117				///< Danel.
#define Mbanji			1011118				///< Banji.
#define Mbanzi			1011119				///< Banzi.
#define Mcheen			1011120				///< Cheen.
#define Mmabel			1011121				///< Mabel.
#define Mnukei			1011122				///< Nukei.
#define MCgFX				450000237			///< @markPrivate
#define Marchigrass	1028461				///< Architectural Grass material.
#define Mshadowcatcher 1036101 		///< Shadow Catcher.
/// @}

/// @addtogroup VideoPostBase
/// @ingroup group_enumeration
/// @{
#define VPbase 5709			///< Video post base.
/// @}

/// @addtogroup ObjectTypes Object Types
/// @ingroup group_enumeration
/// @{
#define Opolygon					5100				///< Polygon - PolygonObject.
#define Ospline						5101				///< Spline - SplineObject.
#define Olight						5102				///< Light.
#define Ocamera						5103				///< Camera - CameraObject.
#define Ofloor						5104				///< Floor.
#define Osky							5105				///< Sky.
#define Oenvironment			5106				///< Environment.
#define Oloft							5107				///< Loft NURBS.
#define Offd							5108				///< FFD.
#define Oparticle					5109				///< %Particle emitter - ParticleObject.
#define Odeflector				5110				///< %Particle deflector.
#define Ogravitation			5111				///< %Particle gravitation.
#define Orotation					5112				///< %Particle rotation.
#define Owind							5113				///< %Particle wind.
#define Ofriction					5114				///< %Particle friction.
#define Oturbulence				5115				///< %Particle turbulence.
#define Oextrude					5116				///< Extrude NURBS.
#define Olathe						5117				///< Lathe NURBS.
#define Osweep						5118				///< Sweep NURBS.
#define Oattractor				5119				///< %Particle attractor.
#define Obezier						5120				///< Bezier NURBS.
#define Oforeground				5121				///< Foreground.
#define Obackground				5122				///< Background.
#define Obone_EX					5123				///< Bone. @markDeprecated
#define Odestructor				5124				///< %Particle destructor.
#define Ometaball					5125				///< Metaball.
#define Oinstance					5126				///< Instance.
#define Obend							5128				///< Bend deformer.
#define Obulge						5129				///< Bulge deformer.
#define Oshear						5131				///< Shear deformer.
#define Otaper						5133				///< Taper deformer.
#define Otwist						5134				///< Twist deformer.
#define Owave							5135				///< Wave deformer.
#define Ostage						5136				///< Stage.
#define Oline							5137				///< Line.
#define Omicrophone				5138				///< Microphone.
#define Oloudspeaker			5139				///< Loudspeaker.
#define Onull							5140				///< Null.
#define Osymmetry					5142				///< Symmetry.
#define Owrap							5143				///< Wrap deformer.
#define Oboole						1010865			///< Boolean.
#define Oexplosion				5145				///< Explosion deformer.
#define Oformula					5146				///< Formula deformer.
#define Omelt							5147				///< Melt deformer.
#define Oshatter					5148				///< Shatter deformer.
#define Owinddeform				5149				///< Wind deformer.
#define Oarray						5150				///< Array.
#define Oheadphone				5151				///< Headphone.
#define Oworkplane				5153				///< Workplane.
#define Oplugin						5154				///< Object plugin - pass the plugin ID.
#define Obase							5155				///< Base object - BaseObject. For @c instanceof parameters in the API.
#define Opoint						5156				///< Point - PointObject. For @c instanceof parameters in the API.
#define Obasedeform				5157				///< Base deformer. For @c instanceof parameters in the API.
#define Oparticlemodifier	5158				///< %Particle modifier. For @c instanceof parameters in the API.
#define Opolyreduction		1001253			///< %Polygon reduction.
#define Oshowdisplacement	1001196			///< Show displacement.
#define Ojoint						1019362			///< Joint.
#define Oskin							1019363			///< Skin deformer.
#define Oweighteffector		1019677			///< Weight effector.
#define Ocharacter				1021433			///< Character.
#define Ocmotion					1021824			///< CMotion.
#define Oxref							1025766			///< XRef.
/// @addtogroup PrimitiveTypes Primitive Types
/// @ingroup group_enumeration
/// @{
#define Ocube							5159				///< Cube.
#define Osphere						5160				///< Sphere.
#define Oplatonic					5161				///< Platonic.
#define Ocone							5162				///< Cone.
#define Otorus						5163				///< Torus.
#define Odisc							5164				///< Disc.
#define Otube							5165				///< Tube.
#define Ofigure						5166				///< Figure.
#define Opyramid					5167				///< Pyramid.
#define Oplane						5168				///< Plane.
#define Ofractal					5169				///< Fractal.
#define Ocylinder					5170				///< Cylinder.
#define Ocapsule					5171				///< Capsule.
#define Ooiltank					5172				///< Oil-tank.
#define Orelief						5173				///< Relief.
#define Osinglepoly				5174				///< Single polygon.
/// @}
#define Opluginpolygon 1001091				///< Polygon plugin.
/// @addtogroup SplinePrimitiveTypes Spline Primitive Types
/// @ingroup group_enumeration
/// @{
#define Osplineprimitive	5152				///< Spline primitive.
#define Osplineprofile		5175				///< Profile spline.
#define Osplineflower			5176				///< Flower spline.
#define Osplineformula		5177				///< Formula spline.
#define Osplinetext				5178				///< Text spline.
#define Osplinenside			5179				///< N-sided spline.
#define Ospline4side			5180				///< 4-sided spline.
#define Osplinecircle			5181				///< Circle spline.
#define Osplinearc				5182				///< Arc spline.
#define Osplinecissoid		5183				///< Cissoid spline.
#define Osplinecycloid		5184				///< Cycloid spline.
#define Osplinehelix			5185				///< Helix spline.
#define Osplinerectangle	5186				///< Rectangle spline.
#define Osplinestar				5187				///< Star spline.
#define Osplinecogwheel		5188				///< Cogwheel spline.
#define Osplinecontour		5189				///< Contour spline.
/// @}
#define Oselection				5190				///< Selection object.
#define Osds							1007455			///< SDS (HyperNURBS) - SDSObject.
#define Osplinedeformer		1008982			///< Spline deformer.
#define Osplinerail				1008796			///< Spline rail.
#define Oatomarray				1001002			///< Atom array.
#define Ospherify					1001003			///< Spherify.
#define Oexplosionfx			1002603			///< Explosion FX.
#define Oconnector				1011010			///< Connector.
#define Oalembicgenerator 1028083			///< Alembic generator.
#define Ofalloff					440000229		///< Falloff object.
/// @}

/// @addtogroup Yplugin
/// @ingroup group_enumeration
/// @{
/// Small list node plugin.
#define Yplugin 110061
/// @}

/// @addtogroup Zplugin
/// @ingroup group_enumeration
/// @{
/// Big list node plugin.
#define Zplugin 110062
/// @}

/// @addtogroup Zplugin
/// @ingroup group_enumeration
/// @{
/// @markPrivate
#define Olayer 100004801
/// @}

/// @addtogroup Fbase
/// @ingroup group_enumeration
/// @{
/// Virtual filter base.
#define Fbase 1001024
/// @}

/// @addtogroup Zmultipass
/// @ingroup group_enumeration
/// @{
/// Multipass render settings element.
#define Zmultipass 300001048
/// @}

/// @addtogroup SHplugin
/// @ingroup group_enumeration
/// @{
#define SHplugin 110065			///< Shader plugin.
/// @}

/// @addtogroup VPplugin
/// @ingroup group_enumeration
/// @{
#define VPplugin 110066			///< Videopost plugin.
/// @}

#define ID_LISTHEAD 110063			///< GeListHead ID.

/// @addtogroup Rbase
/// @ingroup group_enumeration
/// @{
#define Rbase 110304			///< %Render data ID.
/// @}

/// @addtogroup ShaderTypes Shader Types
/// @ingroup group_enumeration
/// @{
#define Xbase							5707				///< Shader base.
#define Xcolor						5832				///< Color.
#define Xbitmap						5833				///< Bitmap.
#define Xbrick						5804				///< Brick.
#define Xcheckerboard			5800				///< Checkerboard.
#define Xcloud						5802				///< Cloud.
#define Xcolorstripes			5822				///< Color stripes.
#define Xcyclone					5821				///< Cyclone.
#define Xearth						5825				///< Earth.
#define Xfire							5803				///< Fire.
#define Xflame						5817				///< Flame.
#define Xgalaxy						5813				///< Galaxy.
#define Xmetal						5827				///< Metal.
#define Xsimplenoise			5807				///< Simple noise.
#define Xrust							5828				///< Rust.
#define Xstar							5816				///< Star.
#define Xstarfield				5808				///< Star field.
#define Xsunburst					5820				///< Sun burst.
#define Xsimpleturbulence	5806				///< Simple turbulence.
#define Xvenus						5826				///< Venus.
#define Xwater						5818				///< Water.
#define Xwood							5823				///< Wood.
#define Xplanet						5829				///< Planet.
#define Xmarble						5830				///< Marble.
#define Xspectral					5831				///< Spectral.
#define Xgradient					1011100			///< Gradient.
#define Xfalloff					1011101			///< Falloff.
#define Xtiles						1011102			///< Tiles.
#define Xfresnel					1011103			///< Fresnel.
#define Xlumas						1011105			///< Lumas.
#define Xproximal					1011106			///< Proximal.
#define Xnormaldirection	1011107			///< Normal direction.
#define Xtranslucency			1011108			///< Translucency.
#define Xfusion						1011109			///< Fusion.
#define Xposterizer				1011111			///< Posterizer.
#define Xcolorizer				1011112			///< Colorizer.
#define Xdistorter				1011114			///< Distorter.
#define Xprojector				1011115			///< Projector.
#define Xnoise						1011116			///< Noise.
#define Xlayer						1011123			///< Layer.
#define Xspline						1011124			///< Spline.
#define Xfilter						1011128			///< Filter.
#define Xripple						1011199			///< Ripple.
#define Xvertexmap				1011137			///< Vertex map.
#define Xsss							1001197			///< SSS.
#define Xambientocclusion	1001191			///< Ambient occlusion.
#define Xchanlum					1007539			///< Chanlum.
#define Xmosaic						1022119			///< Pixelate.
#define Xxmbsubsurface		1025614			///< Subsurface scattering.
#define Xrainsampler			1026576			///< Rain sampler.
#define Xnormalizer				1026588			///< Normalizer.
#define Xterrainmask			1026277			///< Terrain mask.
#define Xobjectcolor			1033961			///< Object color.
#define Xformula					1031433			///< Formula. @since R17.032
#define Xvariation				1033825 		///< Variation. @since R17.032
#define Xthinfilm					1035731			///< Thinfilm.
/// @}

/// @defgroup SelectionTagTypes SelectionTag Types
/// @ingroup group_enumeration

/// @defgroup VariableTagTypes VariableTag Types
/// @ingroup group_enumeration

/// @addtogroup TagTypes Tag Types
/// @ingroup group_enumeration
/// @{
#define Tpoint						5600					///< Point - PointTag. @ingroup VariableTagTypes
#define Tanchor_EX				5608					///< Anchor. @markDeprecated
#define Tphong						5612					///< Phong.
#define Tdisplay					5613					///< Display.
#define Tkinematic_EX			5614					///< IK. @markDeprecated
#define Ttexture					5616					///< Texture - TextureTag.
#define Ttangent					5617					///< Tangent data- TangentTag. @ingroup VariableTagTypes
#define Tprotection				5629					///< Protection.
#define Tparticle					5630					///< %Particle data - ParticleTag. @ingroup VariableTagTypes
#define Tmotionblur				5636					///< Motion blur.
#define Tcompositing			5637					///< Compositing/render.
#define Tannotation				1030659				///< Annotation.
#define Tsavetemp					5650					///< @markInternal
#define Tpolygon					5604					///< Polygon data - PolygonTag. @ingroup VariableTagTypes
#define Tuvw							5671					///< UVW data - UVWTag. @ingroup VariableTagTypes
#define Tsegment					5672					///< Segment data - SegmentTag. @ingroup VariableTagTypes
#define Tpolygonselection	5673					///< Polygon selection - SelectionTag. @ingroup SelectionTagTypes
#define Tpointselection		5674					///< Point selection - SelectionTag. @ingroup SelectionTagTypes
#define Tcoffeeexpression	5675					///< @COFFEE expression.
#define Ttargetexpression	5676					///< Target expression.
#define Tfixexpression_EX	5677					///< Fix expression. @markDeprecated
#define Tsunexpression		5678					///< Sun expression.
#define Tikexpression_EX	5679					///< IK expression. @markDeprecated
#define Tline							5680					///< Line data. @ingroup VariableTagTypes
#define Tvertexmap				5682					///< Vertex map data. @ingroup VariableTagTypes
#define Trestriction			5683					///< Restriction.
#define Tmetaball					5684					///< Metaball.
#define Tbakeparticle			5685					///< Bake particle.
#define Tmorph						5689					///< Morph. @markDeprecated
#define Tsticktexture			5690					///< Stick texture - StickTextureTag. @ingroup VariableTagTypes
#define Tplugin						5691					///< Plugin tag - pass the plugin ID.
#define Tstop							5693					///< Stop.
#define Tbase							5694					///< Base tag - BaseTag. For @c instanceof parameters in the API.
#define Tvariable					5695					///< Variable tag - VariableTag. For @c instanceof parameters in the API.
#define Tvibrate					5698					///< Vibration.
#define Taligntospline		5699					///< Align to spline.
#define Taligntopath			5700					///< Align to path.
#define Tedgeselection		5701					///< Edge selection - SelectionTag. The edges are encodes like this: <tt>(4*poly)+edge</tt>, where @c edge goes from @em 0-@em 3. @ingroup SelectionTagTypes
#define Tclaudebonet_EX		5708					///< Claude bonet. @markDeprecated
#define Tnormal						5711					///< Normal - NormalTag. Contains 12 ::Int16 per polygon, enumerated like the following: <tt>ax,ay,az,bx,by,bz,cx,cy,cz,dx,dy,dz</tt>.\n
																				///< The value is the Float value of the normal vector component multiplied by @em 32000.0.
																				///< @ingroup VariableTagTypes
#define Tcorner						5712					///< Corner. (Phong break.)
#define Tsds							1007579				///< SDS.
#define Tlookatcamera			1001001				///< Look at camera.
#define Texpresso					1001149				///< XPresso.
#define Tsoftselection		1016641				///< Soft selection.
#define Tbaketexture			1011198				///< Bake texture.
#define Tsdsdata					1018016				///< SDS data.
#define Tweights					1019365				///< Weights.
#define Tposemorph				1024237				///< Pose morph.
#define Tpython						1022749				///< Python expression.
#define Tsculpt						1023800				///< Sculpt.
#define Tmotioncam				1027742				///< Motion camera.
#define Tmorphcam					1027743				///< Morph camera.
#define Tcrane						1028270				///< Camera crane.
#define Tarchigrass				1028463				///< Architectural grass.
#define Tsculptnormals		1027660				///< Sculpt normals. @b Private for Sculpting.
#define Tsplinenormal			440000173			///< Spline normals.
#define Tinteraction			440000164			///< Interaction Tag.
#define Tgrouppriority		200000299			///< Group Priority Tag
#define Tvertexcolor			431000045			///< Vertex color Tag.
/// @}

/// @addtogroup NLAbase
/// @ingroup group_enumeration
/// @{
#define NLAbase	5349			///< NLA base.
/// @}

/// @addtogroup CAnim
/// @ingroup group_enumeration
/// @{
#define CTbase	5350			///< Base track ID.
#define CSbase	5351			///< Base curve ID.
#define CKbase	5352			///< Base key ID.
/// @}

/// @addtogroup TrackTypes
/// @ingroup group_enumeration
/// @{
#define CTpla		100004812			///< PLA.
#define CTsound	100004813			///< Sound.
#define CTmorph	100004822			///< Morph.
#define CTtime	-1						///< Time.
/// @}

/// @addtogroup TakeTypes
/// @ingroup group_enumeration
/// @{
/// @since R17.032
#define OverrideBase	431000051			///< Override Node.
#define OverrideGroup	431000075			///< Override Group Node.
#define TakeBase			431000054			///< Take Nodes.
/// @}

/// @addtogroup TL_MARKEROBJ
/// @ingroup group_enumeration
/// @{
/// Timeline marker ID.
#define TL_MARKEROBJ 465001514
/// @}

/// @addtogroup ID_MACHINE
/// @ingroup group_enumeration
/// @{
#define ID_MACHINE			300002140			///< Machine.
#define ID_MACHINEGROUP	300002142			///< Machine group.
/// @}

/// @addtogroup GVbase
/// @ingroup group_enumeration
/// @{
#define GVbase 1001101			///< Graphview base.
/// @}

/// @addtogroup ID_BS_HOOK
/// @ingroup group_enumeration
/// @{
#define ID_BS_HOOK 100004808			///< BaseSceneHook ID.
/// @}

/// @addtogroup MCOMMAND
/// @ingroup group_enumeration
/// @{
/// %Modeling command IDs.
/// @see	SendModelingCommand()
///				@ref MDATA for the container IDs that can be set as options for a command.
#define MCOMMAND_SPLINE_HARDINTERPOLATION	100			///< Hard interpolation.
#define MCOMMAND_SPLINE_SOFTINTERPOLATION	101			///< Soft interpolation.
#define MCOMMAND_SPLINE_REORDER						102			///< Reorder.
#define MCOMMAND_SPLINE_REVERSE						103			///< Reverse sequence.
#define MCOMMAND_SPLINE_MOVEDOWN					104			///< Move down sequence.
#define MCOMMAND_SPLINE_MOVEUP						105			///< Move up sequence.
#define MCOMMAND_SPLINE_JOINSEGMENT				109			///< Join segment.
#define MCOMMAND_SPLINE_BREAKSEGMENT			110			///< Break segment.
#define MCOMMAND_SPLINE_EQUALLENGTH				111			///< Equal tangent length.
#define MCOMMAND_SPLINE_EQUALDIRECTION		112			///< Equal tangent direction.
#define MCOMMAND_SPLINE_LINEUP						113			///< Line up.
#define MCOMMAND_SPLINE_CREATEOUTLINE			114			///< Create outline: @enumerateEnum{MDATA_SPLINE}
#define MCOMMAND_SPLINE_PROJECT						115			///< Project: @enumerateEnum{MDATA_SPLINE_PROJECTMODE}
#define MCOMMAND_SPLINE_ADDPOINT					116			///< Add point: @enumerateEnum{MDATA_SPLINE_ADDPOINTSEGMENT} @enumerateEnum{MDATA_SPLINE_ADDPOINTPOSITION}
#define MCOMMAND_SELECTALL								200			///< Select all.
#define MCOMMAND_DESELECTALL							201			///< Deselect all.
#define MCOMMAND_SELECTINVERSE						202			///< Invert selection.
#define MCOMMAND_SELECTCONNECTED					203			///< Select connected.
#define MCOMMAND_SELECTGROW								204			///< Grow selection.
#define MCOMMAND_SELECTSHRINK							205			///< Shrink selection.
#define MCOMMAND_SELECTPOINTTOPOLY				206			///< Polygon selection from points.
#define MCOMMAND_SELECTPOLYTOPOINT				207			///< Point selection from polygons.
#define MCOMMAND_SELECTADJACENT						208			///< Select adjacent.
#define MCOMMAND_GENERATESELECTION				209			///< Generate selection.
#define MCOMMAND_HIDESELECTED							211			///< Hide selected.
#define MCOMMAND_HIDEUNSELECTED						212			///< Hide unselected
#define MCOMMAND_HIDEINVERT								213			///< Hide invert.
#define MCOMMAND_UNHIDE										214			///< Unhide.
#define MCOMMAND_REVERSENORMALS						217			///< Reverse normals.
#define MCOMMAND_ALIGNNORMALS							218			///< Align normals.
#define MCOMMAND_SPLIT										220			///< Split.
#define MCOMMAND_TRIANGULATE							221			///< Triangulate.
#define MCOMMAND_UNTRIANGULATE						222			///< Untriangulate: @enumerateEnum{MDATA_UNTRIANGULATE}
#define MCOMMAND_DELETE										224			///< Delete.
#define MCOMMAND_OPTIMIZE									227			///< Optimize: @enumerateEnum{MDATA_OPTIMIZE}
#define MCOMMAND_DISCONNECT								228			///< Disconnect: @enumerateEnum{MDATA_DISCONNECT_PRESERVEGROUPS}
#define MCOMMAND_MAKEEDITABLE							230			///< Make editable (returns object).
#define MCOMMAND_MIRROR										237			///< Mirror: @enumerateEnum{MDATA_MIRROR}
#define MCOMMAND_MATRIXEXTRUDE						238			///< Matrix extrude
#define MCOMMAND_SUBDIVIDE								242			///< Subdivide: @enumerateEnum{MDATA_SUBDIVIDE}
#define MCOMMAND_EXPLODESEGMENTS					243			///< Explode segments.
#define MCOMMAND_KNIFE										244			///< Knife: @enumerateEnum{MDATA_KNIFE}
#define MCOMMAND_CURRENTSTATETOOBJECT			245			///< Current state to object (returns object): @enumerateEnum{MDATA_CURRENTSTATETOOBJECT}

#define MCOMMAND_JOIN											246			///< Join (returns object): @enumerateEnum{MDATA_JOIN_MERGE_SELTAGS}
																									///< @note	The objects to join must be children of a parent object. Example:
																									///< @code
																									/// BaseObject* nullobject = BaseObject::Alloc(Onull);
																									///
																									/// objectA->InsertUnder(nullobject);
																									/// objectB->InsertUnder(nullobject);
																									///
																									/// ModelingCommandData cd;
																									/// cd.op = nullobject;
																									/// cd.doc = doc;
																									///
																									/// SendModelingCommand(MCOMMAND_JOIN, cd);
																									/// @endcode

#define MCOMMAND_CONVERTSELECTION					247			///< Convert selection: @enumerateEnum{MDATA_CONVERTSELECTION}
#define MCOMMAND_EDGE_TO_SPLINE						251			///< Edge to spline.
#define MCOMMAND_BREAKPHONG								255			///< Break phong.
#define MCOMMAND_UNBREAKPHONG							256			///< Unbreak phong.
#define MCOMMAND_PHONGTOSELECTION					257			///< Phong to selection.
#define MCOMMAND_MELT											264			///< Melt.
#define MCOMMAND_RESETSYSTEM							265			///< Reset System: @enumerateEnum{MDATA_RESETSYSTEM}
/// @}

/// @addtogroup MDATA
/// @ingroup group_containerid
/// @{
/// @addtogroup MDATA_SPLINE
/// @ingroup group_containerid
/// @{
#define MDATA_SPLINE_FREEHANDTOLERANCE						2020			///< ::Float Freehand tolerance.
#define MDATA_SPLINE_OUTLINE											2021			///< ::Float Spline outline distance.
#define MDATA_SPLINE_PROJECTMODE									2022			///< ::Int32 Project mode (see dialog).
#define MDATA_SPLINE_ADDPOINTSEGMENT							2023			///< ::Int32 %Segment.
#define MDATA_SPLINE_ADDPOINTPOSITION							2024			///< ::Float Position.
#define MDATA_SPLINE_ADDPOINTSELECT								2025			///< ::Bool Select added point.
#define MDATA_SPLINE_ADDPOINTRESULTINDEX					2026			///< ::Int32 Returned index of the new point (check after invoking command).
#define MDATA_SPLINE_OUTLINESEPARATE							2080			///< ::Bool Outline separate. Creates new object.
/// @}
#define MDATA_DISCONNECT_PRESERVEGROUPS						2028			///< ::Bool Preserve groups.
/// @addtogroup MDATA_MIRROR
/// @ingroup group_containerid
/// @{
#define MDATA_MIRROR_SNAPPOINTS										2069			///< ::Bool Snap to points.
#define MDATA_MIRROR_DUPLICATE										2070			///< ::Bool Duplicate points.
#define MDATA_MIRROR_WELD													2071			///< ::Bool Mirror points.
#define MDATA_MIRROR_TOLERANCE										2072			///< ::Float Mirror tolerance.
#define MDATA_MIRROR_SYSTEM												2067			///< ::Int32 Coordinate system (see dialog).
#define MDATA_MIRROR_PLANE												2068			///< ::Int32 Mirror plane (see dialog).
#define MDATA_MIRROR_VALUE												2073			///< ::Float Mirror value.
#define MDATA_MIRROR_POINT												2074			///< ::Vector Mirror point.
#define MDATA_MIRROR_VECTOR												2075			///< ::Vector Mirror vector.
#define MDATA_MIRROR_SELECTIONS										2120			///< ::Bool Mirror selections
#define MDATA_MIRROR_ONPLANE											2122			///< ::Bool Mirror on plane.
/// @}
/// @addtogroup MDATA_OPTIMIZE
/// @ingroup group_containerid
/// @{
#define MDATA_OPTIMIZE_TOLERANCE									2076			///< ::Float Optimize tolerance.
#define MDATA_OPTIMIZE_POINTS											2077			///< ::Bool Optimize points.
#define MDATA_OPTIMIZE_POLYGONS										2078			///< ::Bool Optimize polygons.
#define MDATA_OPTIMIZE_UNUSEDPOINTS								2079			///< ::Bool Optimize unused points.
/// @}
#define MDATA_CROSSSECTION_ANGLE									2082			///< ::Float Maximum angle.
/// @addtogroup MDATA_SUBDIVIDE
/// @ingroup group_containerid
/// @{
#define MDATA_SUBDIVIDE_HYPER											2098			///< ::Bool Subdivide Hyper NURBS.
#define MDATA_SUBDIVIDE_ANGLE											2099			///< ::Float Subdivide maximum angle.
#define MDATA_SUBDIVIDE_SPLINESUB									2100			///< ::Int32 Subdivisions (spline).
#define MDATA_SUBDIVIDE_SUB												2101			///< ::Int32 Subdivisions (polygon).
/// @}
/// @addtogroup MDATA_KNIFE
/// @ingroup group_containerid
/// @{
#define MDATA_KNIFE_P1														2110			///< ::Vector Knife first point.
#define MDATA_KNIFE_V1														2111			///< ::Vector Knife first vector.
#define MDATA_KNIFE_P2														2112			///< ::Vector Knife second point.
#define MDATA_KNIFE_V2														2113			///< ::Vector Knife second vector.
#define MDATA_KNIFE_ANGLE													2115			///< ::Float Knife angle.
/// @}
/// @addtogroup MDATA_CONVERTSELECTION
/// @ingroup group_containerid
/// @{
#define MDATA_CONVERTSELECTION_LEFT								2126			///< ::Int32 Left selection (see dialog).
#define MDATA_CONVERTSELECTION_RIGHT							2127			///< ::Int32 Right selection (see dialog).
#define MDATA_CONVERTSELECTION_TOLERANT						2128			///< ::Bool Tolerant conversion.
/// @}
/// @addtogroup MDATA_CURRENTSTATETOOBJECT
/// @ingroup group_containerid
/// @{
#define MDATA_CURRENTSTATETOOBJECT_INHERITANCE		2140			///< ::Bool Use inheritance.
#define MDATA_CURRENTSTATETOOBJECT_KEEPANIMATION	2141			///< ::Bool Keep animation.
#define MDATA_CURRENTSTATETOOBJECT_NOGENERATE			2162			///< ::Bool No generate.
/// @}
#define MDATA_ROTATECAMERA												2142			///< ::Bool Tools/Camera Rotation
/// @addtogroup MDATA_RING
/// @ingroup group_containerid
/// @{
#define MDATA_RING_EDGE														2154			///< ::Int32 Ring edge.
#define MDATA_RING_SELECTION											2155			///< ::Int32 Ring selection: @enumerateEnum{SELECTION}
#define MDATA_RING_SKIP														2156			///< ::Int32 Ring skip.
/// @}
/// @addtogroup MDATA_FILLSEL
/// @ingroup group_containerid
/// @{
#define MDATA_FILLSEL_START_POLY									2157			///< ::Int32 Fill selection start polygon.
#define MDATA_FILLSEL_SELECTION										2158			///< ::Int32 Fill selection: @enumerateEnum{SELECTION}
/// @}
/// @addtogroup MDATA_OUTLINESEL
/// @ingroup group_containerid
/// @{
#define MDATA_OUTLINESEL_START_POLY								2159			///< ::Int32 Outline selection start polygon.
#define MDATA_OUTLINESEL_SELECTION								2160			///< ::Int32 Outline selection: @enumerateEnum{SELECTION}
/// @}
/// @addtogroup MDATA_UNTRIANGULATE
/// @ingroup group_containerid
/// @{
#define MDATA_UNTRIANGULATE_ANGLE									2121			///< ::Bool Evaluate angle.
#define MDATA_UNTRIANGULATE_NGONS									2143			///< ::Bool Create N-gons.
#define MDATA_UNTRIANGULATE_ANGLE_RAD							2161			///< ::Float Angle radius.
/// @}
/// @addtogroup MDATA_RESETSYSTEM
/// @ingroup group_containerid
/// @{
#define MDATA_RESETSYSTEM_COMPENSATE							2165			///< ::Bool Compensate.
#define MDATA_RESETSYSTEM_RECURSIVE								2166			///< ::Bool Recursive.
/// @}
#define MDATA_JOIN_MERGE_SELTAGS									2167			///< ::Bool Merge selection tags.
/// @addtogroup MDATA_SETVERTEX
/// @ingroup group_containerid
/// @{
#define MDATA_SETVERTEX_VALUE											4000			///< ::Float Set vertex value.
#define MDATA_SETVERTEX_MODE											4001			///< ::Int32 Set vertex mode (see dialog).
/// @}
/// @}

/// @addtogroup WPREF
/// @ingroup group_containerid
/// @{
/// World preferences.
#define WPREF_UNITS_BASIC				10000			///< ::Int32 Basic units.
#define WPREF_UNITS_TIME				10001			///< ::Int32 Time units.
#define WPREF_UNITS_AUTOCONVERT	10002			///< ::Bool Auto Convert Units.
#define WPREF_UNITS_USEUNITS		10003			///< ::Bool Use units.
#define WPREF_REFRESHTIME				10004			///< ::Int32 Refresh time.
#define WPREF_RATIO							10005			///< ::Float Monitor aspect ratio.
#define WPREF_CENTER						1002			///< ::Bool Create new objects in view center.
#define WPREF_TABLET						1005			///< ::Bool
#define WPREF_HW_OPENGL					1008			///< ::Bool (read-only). This value is set on startup and can only be read.
#define WPREF_LINK_SELECTION		1009			///< ::Bool
#define WPREF_FULLANIMREDRAW		1010			///< ::Bool Full animation redraw.
#define WPREF_SAVE_LAYOUT				1014			///< ::Bool
#define WPREF_INSERTAT					1016			///< ::Int32 Insert object at.
#define WPREF_PASTEAT						1017			///< ::Int32 Paste object at.
#define WPREF_MAX_UNDOS					1018			///< ::Int32
#define WPREF_MAX_LAST					1019			///< ::Int32
#define WPREF_CAMERAROTATION		1020			///< ::Int32 Camera rotation mode: @enumerateEnum{WPREF_CAMERAROTATION}
#define WPREF_OPENGL_TEMP				1092			///< ::Bool Temporary setting (written on shutdown and copied to WPREF_HW_OPENGL on startup)
/// @addtogroup WPREF_CAMERAROTATION
/// @ingroup group_enumeration
/// @{
#define WPREF_CAMERAROTATION_CENTER	1			///< Center.
#define WPREF_CAMERAROTATION_OBJECT	2			///< Object.
#define WPREF_CAMERAROTATION_CURSOR	3			///< Cursor.
#define WPREF_CAMERAROTATION_CAMERA	4			///< Camera.
#define WPREF_CAMERAROTATION_CUSTOM	5			///< Custom.
/// @}

#define WPREF_DOLLYTOCURSOR	1021													// Int32
																	///< - <i>1</i> = Off.
																	///< - <i>2</i> = Orthographic views.
																	///< - <i>3</i> = All views.
#define WPREF_SYNCVIEWPORTS	1022													// BOOL 440000085 // BOOL
#define WPREF_SCRIPTWORDWRAP				1023	// Bool

#define WPREF_OPENGL_PERSPECT						1024			///< ::Bool
#define WPREF_OPENGL_TEXTURE_FILTERING	1025			///< ::Int32 OpenGL texture filtering: @enumerateEnum{WPREF_OPENGL_TEXTURE_FILTERING}
/// @addtogroup WPREF_OPENGL_TEXTURE_FILTERING
/// @ingroup group_enumeration
/// @{
#define WPREF_OPENGL_TEXTURE_FILTERING_NEAREST				0			///< Nearest texture interpolation.
#define WPREF_OPENGL_TEXTURE_FILTERING_LINEAR					1			///< Linear texture interpolation.
#define WPREF_OPENGL_TEXTURE_FILTERING_LINEAR_MIPMAP	2			///< Linear mipmap texture interpolation.
/// @}
#define WPREF_USE_TEXTURES	1026			///< ::Bool
#define WPREF_NAV_POI_MODE	1027			///< ::Int32 Point of Interest (POI) mode: @enumerateEnum{WPREF_NAV_POI}
/// @addtogroup WPREF_NAV_POI
/// @ingroup group_enumeration
/// @{
#define WPREF_NAV_POI_CENTER	1
#define WPREF_NAV_POI_OBJECT	2
#define WPREF_NAV_POI_CAMERA	3
/// @}

#define WPREF_NAV_CURSOR_MODE				1028			///< ::Int32 Cursor Placement mode: @enumerateEnum{WPREF_NAV_CURSOR}
/// @addtogroup WPREF_NAV_CURSOR
/// @ingroup group_enumeration
/// @{
#define WPREF_NAV_CURSOR_OFF				1			///< Off.
#define WPREF_NAV_CURSOR_SELECTION	2			///< Selected.
#define WPREF_NAV_CURSOR_CHILDREN		3			///< Selected children.
#define WPREF_NAV_CURSOR_ALL				4			///< All.
/// @}

#define WPREF_USE_QUICKTIME										1029			///< ::Bool
#define WPREF_TABLET_HIRES										1030			///< ::Bool
#define WPREF_REVERSE_ORBIT										1031			///< ::Bool Reverse orbit.
#define WPREF_NAV_CURSOR_DEEP									1032			///< ::Bool Deep cursor placement.
#define WPREF_NAV_LOCK_POI										1033			///< ::Bool Lock POI for dolly.
#define WPREF_OPENGL_POLYLINES								1034			///< ::Bool: Use polylines.
#define WPREF_OPENGL_LIGHTING									1035			///< ::Bool: Use OpenGL lighting.
#define WPREF_NAV_TRACKBALL										1036			///< ::Bool: Trackball camera rotation.
#define WPREF_OPENGL_GLPOINTS									1037			///< ::Bool: Allow real OpenGL points.
#define WPREF_OPENGL_HIGHENDSHADING						1038			///< ::Bool
#define WPREF_NAV_VIEW_TRANSITION							1039			///< ::Bool Enable the smooth view transition in the viewport.
#define WPREF_REALTIMEMANAGER									1042			///< ::Bool
#define WPREF_MAX_BACKUP											1043			///< ::Int32
#define WPREF_CENTERAXIS											1044			///< ::Bool
#define WPREF_OPENGL_DUALPLANES_ARB						1047			///< ::Bool: Use dual plane ARB extension.
#define WPREF_MATPREVIEW_DEFAULTSIZE					1048			///< ::Int32
#define WPREF_DESCRIPTIONLIMIT								1049			///< ::Int32
#define WPREF_MATPREVIEW_DEFAULTOBJECT_MAT		1050			///< ::Int32
#define WPREF_MATPREVIEW_DEFAULTUSERSCENE_MAT	1051			///< String
#define WPREF_MATPREVIEW_DEFAULTOBJECT_SHD		1052			///< ::Int32
#define WPREF_MATPREVIEW_DEFAULTUSERSCENE_SHD	1053			///< String
#define WPREF_MATPREVIEW_AUTO_UPDATE					1054			///< ::Bool
#define WPREF_MATPREVIEW_REDRAW_TIME					1055			///< ::Int32: Maximum redraw time in milliseconds.
#define WPREF_MATPREVIEW_FPS									1056			///< ::Int32
#define WPREF_MATPREVIEW_LENGTH								1057			///< ::Float
#define WPREF_MATPREVIEW_MAX_MEM							1058			///< ::Int32
#define WPREF_SUBPIXELLIMIT										1062			///< ::Int32
#define WPREF_OPENGL_ROTATEQUADS							1064			///< ::Bool: Rotate quads @em 90&deg; to get another subdivision.
#define WPREF_OPENGL_DUALPLANES_HIGHLIGHT			1066			///< ::Bool: Allow dual plane highlighting in OpenGL mode (GL extension).
#define WPREF_ALLOWBUGREPORTS									1068			///< ::Bool Allow bug reports.
// #define WPREF_OPENGL_HIGHQUALITY						1069			///< ::Bool
#define WPREF_OPENGL_COMPILER									1070			///< ::Int32 OpenGL compiler: @enumerateEnum{WPREF_OPENGL_COMPILER}
/// @addtogroup WPREF_OPENGL_COMPILER
/// @ingroup group_enumeration
/// @{
#define WPREF_OPENGL_COMPILER_GLSL	0			///< GLSL.
#define WPREF_OPENGL_COMPILER_CG		1			///< Cg.
/// @}
#define WPREF_OPENGL_MAX_TRANS_DEPTH					1071			///< ::Int32
#define WPREF_OPENGL_MAX_LIGHTS								1072			///< ::Int32
#define WPREF_OPENGL_MAX_SHADOWS							1073			///< ::Int32
#define WPREF_SAVE_CACHES											1074			///< ::Bool
#define WPREF_SAVE_CACHES_ANIM								1075			///< ::Bool
#define WPREF_OPENGL_ANTIALIAS								1084			///< ::Int32 OpenGL anti-aliasing quality.
#define WPREF_OPENGL_MULTITHREADED						1085			///< ::Bool Multi-threaded OpenGL.
#define WPREF_OPENGL_USE_SHADER_CACHE					1089			///< ::Bool Use shader cache.
#define WPREF_VIEW_DISLAYCOLORPROFILE					1086			///< ColorProfile Display Color Profile.
#define WPREF_OPENGL_VIEWPORT_DITHERING				1091			///< ::Bool Enable Dithering in Viewport. @since R17.032

#define WPREF_MOVEACCELERATION		1081			///< ::Float
#define WPREF_SCALEACCELERATION		1082			///< ::Float
#define WPREF_ROTATEACCELERATION	1083			///< ::Float

#define WPREF_GLOBAL_SCRIPTMODE	1090			/// ::Int32 Global script mode (Console, Script Manager): @enumerateEnum{SCRIPTMODE}

#define WPREF_COLOR_SYSTEM_C4D	1100			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_SYSTEM_BP		1101			///< Not used anymore in new Color Chooser. Deprecated since R17.
/// @addtogroup COLORSYSTEM
/// @ingroup group_enumerations
/// @{
#define COLORSYSTEM_HSVTAB				22			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define COLORSYSTEM_TABLE					30			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define COLORSYSTEM_RGB_COLOR			11			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define COLORSYSTEM_HSV_COLOR			21			///< Not used anymore in new Color Chooser. Deprecated since R17.
/// @}
#define WPREF_COLOR_RGBRANGE	1102			///< ::Int32 RGB color range: @enumerateEnum{COLORSYSTEM_RANGE}

#define WPREF_COLOR_HRANGE	1103				///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_SVRANGE	1104				///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_MODE_COMPACT								1124		///< ::Int32 Compact Mode. @since R17
#define WPREF_COLOR_MODE_RGB										1110		///< ::Bool RGB Sliders Mode. @since R17
#define WPREF_COLOR_MODE_HEX										1111		///< ::Bool Hexadecimal Color Field. @since R17.032
#define WPREF_COLOR_MODE_RGB_OLD_SLIDERS 				1112  	///< ::Bool Use Old-Style RGB Sliders. @since R17.032
#define WPREF_COLOR_MODE_HSV										1113		///< ::Bool HSV sliders Mode. @since R17.032
#define WPREF_COLOR_MODE_KELVIN									1114		///< ::Bool Kelvin Color Temperature Mode. @since R17.032
#define WPREF_COLOR_MODE_MIXER									1115		///< ::Bool Color Mixer Mode. @since R17.032
#define WPREF_COLOR_MODE_SWATCHES								1116		///< ::Bool Color Swatches Mode. @since R17.032
#define WPREF_COLOR_MODE_SWATCHES_SHOWNAMES 		1117		///< ::Bool Show Swatches Group Names. @since R17.032
#define WPREF_COLOR_MODE_SWATCHES_SWATCH_SIZE 	1118		///< ::Int32 Swatches Size Mode. See @ref COLORSYSTEM_SIZE. @since R17
#define WPREF_COLOR_MODE_SPECIAL								1119		///< ::Int32 Special Color Mode (these are exclusive each other). @since R17
#define COLORSYSTEM_MODE_SPECIAL_DISABLED				0				///< Special Mode Disabled. @since R17
#define COLORSYSTEM_MODE_SPECIAL_COLORWHEEL			1				///< Color Wheel Mode. @since R17
#define COLORSYSTEM_MODE_SPECIAL_SPECTRUM				2				///< Color Spectrum Mode. @since R17
#define COLORSYSTEM_MODE_SPECIAL_PICTURE				3				///< Color from Picture Mode. @since R17
#define WPREF_COLOR_MODE_WHEEL_SIZE							1120		///< ::Int32 Color Wheel Size. See @ref COLORSYSTEM_SIZE. @since R17
#define WPREF_COLOR_MODE_WHEEL_SWATCH_SIZE			1121		///< ::Int32 Color Wheel Preview Swatches Size. See @ref COLORSYSTEM_SIZE. @since R17
#define WPREF_COLOR_MODE_SPECTRUM_SIZE					1122		///< ::Int32 Spectrum Size. See @ref COLORSYSTEM_SIZE. @since R17
#define WPREF_COLOR_MODE_PICTURE_SWATCH_SIZE		1123		///< ::Int32 Picture Mode Swatches Size. See @ref COLORSYSTEM_SIZE. @since R17
#define WPREF_COLOR_MODE_SWATCHES_GLOBAL_DATA				1127		///< ::BaseContainer Global swatches data @markPrivate. @since R17
#define WPREF_COLOR_MODE_SWATCHES_REMEMBER_GLOBAL		1128		///< ::Bool If enabled global swatches will be retained between c4d sessions, if false the default swatches will be loaded when c4d restarts. @since R17
#define WPREF_COLOR_REMEMBER_LAST_LAYOUT						1129		///< ::Bool If enabled c4d will remember the last layout for new color choosers, but it will keep the manually adjusted layouts for old color choosers. @since R17
/// @addtogroup COLORSYSTEM_RANGE
/// @ingroup group_enumeration
/// @{
#define COLORSYSTEM_RANGE_PERCENT	0			///< @em 0\%-@em 100\%
#define COLORSYSTEM_RANGE_DEGREE	3			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define COLORSYSTEM_RANGE_255			1			///< @em 0-@em 255
#define COLORSYSTEM_RANGE_65535		2			///< @em 0-@em 65535
/// @}

/// @addtogroup COLORSYSTEM_SIZE
/// @ingroup group_enumeration
/// @{
/// @since R17.032
#define COLORSYSTEM_SIZE_SMALL		0			///< Small.
#define COLORSYSTEM_SIZE_MEDIUM		1			///< Medium.
#define COLORSYSTEM_SIZE_LARGE		2			///< Large.
/// @}

#define WPREF_COLOR_QUICK_C4D			1105			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_QUICK_BP			1106			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_MIX_C4D				1107			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_MIX_BP				1108			///< Not used anymore in new Color Chooser. Deprecated since R17.

#define WPREF_COLOR_SETUPS				1109			///< Not used anymore in new Color Chooser. Deprecated since R17.

#define WPREF_COLOR_QUICKPRESET					1200			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_QUICKPRESET_LAST		1299			///< Not used anymore in new Color Chooser. Deprecated Since R17.
#define WPREF_COLOR_MIXING_1						1301			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_MIXING_2						1302			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_MIXING_3						1303			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_MIXING_4						1304			///< Not used anymore in new Color Chooser. Deprecated since R17.
#define WPREF_COLOR_SYSTEM_COLORCHOOSER	1305			///< Not used anymore in new Color Chooser. Deprecated since R17.

#define WPREF_AUTOSAVE_ENABLE						1400			///< ::Bool
#define WPREF_AUTOSAVE_MIN							1401			///< ::Int32
#define WPREF_AUTOSAVE_LIMIT_TO					1402			///< ::Bool
#define WPREF_AUTOSAVE_LIMIT_NUM				1403			///< ::Int32
#define WPREF_AUTOSAVE_DEST							1405			///< ::Int32
/// @addtogroup WPREF_AUTOSAVE_DEST
/// @ingroup group_enumeration
/// @{
#define WPREF_AUTOSAVE_DEST_BACKUPDIR		0
#define WPREF_AUTOSAVE_DEST_USERDIR			1
#define WPREF_AUTOSAVE_DEST_STARTUPDIR	2
/// @}
#define WPREF_AUTOSAVE_DEST_PATH				1406			///< Filename
#define WPREF_COMMANDER_AT_CURSOR				1407			///< ::Bool

#define WPREF_PLUGINS					30006			///< BaseContainer
#define WPREF_CPUCOUNT				30010			///< ::Int32 Number of CPUs.
#define WPREF_LOGFILE					30011			///< ::Bool Create render log file.
#define WPREF_CONSOLEGI				30013			///< ::Bool Show Global Illumination information in Console.
#define WPREF_CPUCUSTOM				30014			///< ::Bool Custom number of render threads.
#define WPREF_RENDERQUEUELOG	30015			///< ::Bool %Render queue log.

#define WPREF_BUBBLEHELP2									21002			///< ::Bool
#define WPREF_THREADPRIORITY							21003			///< ::Bool
#define WPREF_MENUICON										21004			///< ::Bool
#define WPREF_MENUSHORTCUT								21005			///< ::Bool
#define WPREF_INACTIVEBORDER							21006			///< ::Bool
#define WPREF_ACTIVEBORDER								21007			///< ::Bool
#define WPREF_FONT_STANDARD								21050			///< BaseContainer
#define WPREF_FONT_MONO										21051			///< BaseContainer
#define WPREF_MAC_CTRLCLICK_EMULATES_RMB	21062			///< ::Bool CTRL click emulates right mouse button. OS X only.
#define WPREF_MAC_MENUBAR									21063			///< ::Bool
#define WPREF_UV_RELAX_DATA								21065			///< BaseContainer
#define WPREF_UV_OPTIMAL_MAPPING_DATA			21066			///< BaseContainer
#define WPREF_UV_PROJECTION_DATA					21067			///< BaseContainer
#define WPREF_UV_TAB_SEL									21068			///< BaseContainer
#define WPREF_UV_TRANSFORM_DATA						21069			///< BaseContainer
#define WPREF_LINUX_BROWSERPATH						21070			///< Filename
#define WPREF_MOUSEOVER_SHORTCUT					21072			///< ::Bool
#define WPREF_ONLINEHELP_PATH							21075			///< Filename
#define WPREF_ONLINEHELP_URL							21076			///< String
#define WPREF_LINUX_IMAGEEDITPATH					21077			///< Filename
#define WPREF_LOCKINTERFACE								21078			///< ::Bool Lock the interface layout.
#define WPREF_TOOLCURSOR_BASIC						21079			///< ::Bool Cursor icon for basic tools.
#define WPREF_TOOLCURSOR_ADV							21080			///< ::Bool Cursor icon for advanced tools.
#define WPREF_LOWERPROCESSPRIORITY				21081			///< ::Bool
#define WPREF_HIGHLIGHTNEWFEATURES				21082			///< ::Int

#define WPREF_ONLINEUPDATER_AUTO_CHECK							40000			///< ::Bool Checks automatically for updates.
#define WPREF_ONLINEUPDATER_CHECKSUM								40001			///< ::Int32
#define WPREF_ONLINEUPDATER_SHOW_INSTALLED					40003			///< ::Bool Show installed updates.
#define WPREF_ONLINEUPDATER_AUTORESTART							40004			///< ::Bool Automatically restart the application during installation.
#define WPREF_ONLINEUPDATER_BACKUP									40005			///< ::Bool Create backup copy before installation.
#define WPREF_ONLINEUPDATER_BACKUP_PATH							40014			///< Filename Backup path.
#define WPREF_ONLINEUPDATER_LAST_OPEN_DAY						40011			///< ::Int32 Last day the updater was opened.
#define WPREF_ONLINEUPDATER_LAST_OPEN_HOUR					40012			///< Float Last hour the updater was opened.
#define WPREF_ONLINEUPDATER_REMOVE_FILES						40013			///< ::Bool Remove backup files after update.
#define WPREF_ONLINEUPDATER_SHOW_DEVELOPER_UPDATES	40015			///< ::Bool

#define WPREF_PV_RENDER_VIEW	430000690			///< ::Int32 The index id of the Picture Viewer dialog that receives render output.
#define WPREF_PV_RECENT				465001804			///< For recent files in Picture Viewer.

#define WPREF_COMMUNICATION_LIVELINK_ENABLED	465001648				///< ::Bool If the Livelink to AE should be enabled or disabled when Cinema is started. @since R17.048
#define WPREF_COMMUNICATION_LIVELINK_PORT			465001649				///< ::Int32 The port used by the Livelink connection. @since R17.048
/// @}

/// @addtogroup PREFSDIALOG_ID
/// @ingroup group_enumeration
/// @{
#define		PVPREFSDIALOG_ID			465001700			///< Picture Viewer preferences dialog ID.
#define		SCULPTPREFSDIALOG_ID	1027830				///< Sculpt preferences dialog ID.
#define		TLPREFSDIALOG_ID			465001501			///< Timeline preferences dialog ID.
#define		PHPREFSDIALOG_ID			1031908				///< Phoenix preferences dialog ID.
/// @}

/// @addtogroup WPREFS_TLKEY
/// @ingroup group_enumeration
/// @{
/// Timeline/keyframe preferences IDs
/// @todo Add information for undocumented IDs.
enum
{
	WPREFS_HIGHLIGHT = 1000,
	WPREFS_HIGHLIGHTCURVE,
	WPREFS_CURSORINDICATOR,
	WPREFS_MINIMUM_OLD,
	WPREFS_MINIMUMWIDTH,
	WPREFS_SHOWLAYERCOL,
	WPREFS_TRACKCOLOR,
	WPREFS_TRACKCOLNO,
	WPREFS_TRACKCOLPRS,
	WPREFS_TRACKCOLORG,
	WPREFS_SHOWTRACKSTARTEND,
	WPREFS_SUMMARY,
	WPREFS_HLEAUTOVALUE,
	WPREFS_INTERACTIVEUPDATE,
	WPREFS_CLIPTRANSITIONIME,
	WPREFS_KEYSDOPESHEET,
	WPREFS_KEYSYMBOLS,
	WPREFS_SHOWBRANCHES,
	WPREFS_SHOWVECTRACK,
	WPREFS_KEYFRAMEDOTS,								///< ::Bool Legacy keyframe dots.
	WPREFS_DOTSKILLTRACKS,							///< ::Bool Keyframe dots kill tracks with no keyframes on them.
	WPREFS_LINKKEYFCSELECTION,					///< ::Bool Link Keyframe and FCurve selection together. @since R17.032
	WPREFS_LINKOMSELECTONLY,						///< ::Bool Only display the actual selected object and not the tags etc. when Link Timeline/Object Manager is selected. @since R17.032
	//WPREFS_GLOBALSELECTION,						// Bool One global Timeline selection.
	WPREFS_LINKOMSELECTONLYBUTTAGS,			///< ::Bool Only display the linked objects but also the tags. @since R17.032
	WPREFS_FCLISTVIEW,									///< ::Bool FCurve mode only: list view instead of normal hierarchy. @since R17.032
	WPREFS_FCLISTVIEW_HIERARCHICAL,			///< ::Bool FCurve mode only: hierarchical list view instead of normal hierarchy. @since R17.032
};
/// @}


/// @addtogroup WPREFS_PV
/// @ingroup group_enumeration
/// @{
/// Picture Viewer preferences IDs.
enum
{
	WPREFS_PVMEMORY = 1000,			///< Memory (MB).
	WPREFS_PVDRAWBUCKETS,				///< Draw buckets.
	WPREFS_PVHDMEM,							///< Hard disk memory (MB).
	WPREFS_PVHDFOLDER,					///< Cache Path.
	WPREFS_PVHDUNLIMIT,					///< Unlimited.
};
/// @}

/// @addtogroup WPREFS_SCULPT
/// @ingroup group_enumeration
/// @{
/// Sculpt preferences IDs.
enum
{
	WPREFS_SCULPTMEMORY = 1000,			///< Maximum amount of memory (MB) that a sculpt object should use.
};
/// @}

/// @addtogroup WPREFS_PH
/// @ingroup group_enumeration
/// @{
/// Phoenix preferences IDs
enum
{
	WPREFS_PHMAXCACHEMEM = 1000,
	WPREFS_PHSYSRESERVEMEM,
};
/// @}

/// @addtogroup WPREF_NET
/// @ingroup group_enumeration
/// @{
/// Team Render/NET preferences IDs.
enum
{
	WPREF_NET_NAME = 1000,
	WPREF_NET_SHARE,
	WPREF_NET_THREADCUSTOM,
	WPREF_NET_RENDERTHREADS,
	WPREF_NET_SECURITYTOKEN, // String (saved in the external TR prefs file)
	WPREF_NET_ALLOWRESTARTOFC4D,
	WPREF_NET_SERVICEPORTNUMBER, // Int32 (saved in the external TR prefs file)
	WPREF_NET_SERVICEREPOSITORYPATH,
	WPREF_NET_USEBONJOUR,
	WPREF_NET_USEENCRYPTION,
	WPREF_NET_HANDLEWARNINGASERROR,
	WPREF_NET_ABORTRENDERINGONCLIENTERROR,
	WPREF_NET_PEERTOPEERASSETDISTRIBUTION,
	WPREF_NET_REQUESTONDEMAND,
	WPREF_NET_EXCLUDECLIENTONLOADINGERROR,
	WPREF_NET_RENDERINGTIMEOUT,
	WPREF_NET_ENABLETEAMRENDER,
	WPREF_NET_WEBSERVERPORT,

	// Stored in preferences but not visible
	WPREF_NET_SHOWBUCKETMACHINECOLOR,
	WPREF_NET_SHOWNAME,
	WPREF_NET_SHOWICON,
	WPREF_NET_SHOWINFO,
	WPREF_NET_SHOWCHECKBOX,
	WPREF_NET_SHOWADDRESS,
	WPREF_NET_MACHINEICONSIZE,

	WPREF_NET_ENABLERENDERINGTIMEOUT,
	WPREF_NET_FETCHASSETSALWAYSFROMSERVER,

	WPREF_NET_ASSETCHUNKSIZE,
	WPREF_NET_WAKEONLANFOROFFLINEMACHINES,
	WPREF_NET_KEEPB3DFILESAFTERASSEMBLING,
	WPREF_NET_USERMANAGEMENTENABLED,												///< @since R17.032
	WPREF_NET_DOWNLOADASSETINPARTS,													///< @since R17.032
	WPREF_NET_STOPJOBONSWAPPINGENABLED,											///< @since R17.048
	WPREF_NET_STOPJOBONSWAPPINGAUTO,												///< @since R17.048
	WPREF_NET_STOPJOBONSWAPPINGVALUE,												///< @since R17.048
	WPREF_NET_RESTARTJOBSAFTERUNEXPECTEDSERVERTERMINATION		///< @since R17.SP3
};
/// @}

/// @addtogroup WPREF_COMMUNICATION
/// @ingroup group_containerid
/// @{
enum
{
	WPREF_COMMUNICATION_METRICS_ENABLE,									///< ::Bool. Enable/disable Metrics collection of information.
	WPREF_COMMUNICATION_METRICS_ENABLE_COMMANDS,				///< ::Bool. Enable/disable Metrics collection of commands.
	WPREF_COMMUNICATION_METRICS_ENABLE_PREFERENCES,			///< ::Bool. Enable/disable Metrics collection of user preferences.
	WPREF_COMMUNICATION_METRICS_ENABLE_SYSTEM_INFO,			///< ::Bool. Enable/disable Metrics collection of system information.
	WPREF_COMMUNICATION_METRICS_LICENSE_ACCEPTED,				///< ::Bool. Set to @formatConstant{true} if license has been accepted.
	WPREF_COMMUNICATION_METRICS_ASK_ME_LATER,						///< ::Bool. Set to @formatConstant{true} if license has not been accepted nor denied and the decision will be later.
	WPREF_COMMUNICATION_METRICS_ACTIVE,									///< ::Bool. Set to @formatConstant{true} if a %User ID has been retrieved and data has been sent.

	WPREF_COMMUNICATION_METRICS_DUMMY
};
/// @}

/// @addtogroup WPREF_TAKE Take System Preferences IDs
/// @ingroup group_containerid
/// @{
/// @since R17.032
enum
{
	WPREF_TAKE_BASIC_GROUP = 1000,
	WPREF_TAKE_MAIN_AUTOTAKE,
	WPREF_TAKE_MANAGER_SHOWFILTER,
	WPREF_TAKE_MANAGER_SHOWSHOWSEARCH,
	WPREF_TAKE_MANAGER_TREEMODE,
	WPREF_TAKE_DEFAULT_FILETR_OBJ,
	WPREF_TAKE_DEFAULT_FILETR_TAG,
	WPREF_TAKE_DEFAULT_FILETR_MAT,
	WPREF_TAKE_DEFAULT_FILETR_SHD,
	WPREF_TAKE_DEFAULT_FILETR_LAY,
	WPREF_TAKE_DEFAULT_FILETR_OTH,
	WPREF_TAKE_DEFAULT_FILETR_VIS,
	WPREF_TAKE_DEFAULT_FILETR_TRN,
	WPREF_TAKE_DEFAULT_FILETR_PRM,
	WPREF_TAKE_DEFAULT_FILETR_CAM,
	WPREF_TAKE_DEFAULT_FILETR_RS,
};
/// @}

/// @addtogroup MOUSE
/// @ingroup group_enumeration
/// @{
/// Mouse cursors.
#define MOUSE_HIDE							0				///< Hide cursor.
#define MOUSE_SHOW							1				///< Show cursor.
#define MOUSE_NORMAL						2				///< Normal cursor.
#define MOUSE_BUSY							3				///< Busy cursor.
#define MOUSE_CROSS							4				///< Cross cursor.
#define MOUSE_QUESTION					5				///< Question cursor.
#define MOUSE_ZOOM_IN						6				///< Zoom in cursor.
#define MOUSE_ZOOM_OUT					7				///< Zoom out cursor.
#define MOUSE_FORBIDDEN					8				///< Forbidden cursor.
#define MOUSE_DELETE						9				///< Delete cursor.
#define MOUSE_COPY							10			///< Copy cursor.
#define MOUSE_INSERTCOPY				11			///< Insert copy cursor.
#define MOUSE_INSERTCOPYDOWN		12			///< Insert copy down cursor.
#define MOUSE_MOVE							13			///< Move cursor.
#define MOUSE_INSERTMOVE				14			///< Insert move cursor.
#define MOUSE_INSERTMOVEDOWN		15			///< Insert move down cursor.
#define MOUSE_ARROW_H						16			///< Horizontal arrow cursor.
#define MOUSE_ARROW_V						17			///< Vertical arrow cursor.
#define MOUSE_ARROW_HV					18			///< Horizontal and vertical arrow cursor.
#define MOUSE_POINT_HAND				19			///< Point hand cursor.
#define MOUSE_MOVE_HAND					20			///< Move hand cursor.
#define MOUSE_IBEAM							21			///< I-beam cursor.
#define MOUSE_SELECT_LIVE				22			///< Live selection cursor.
#define MOUSE_SELECT_FREE				23			///< Free selection cursor.
#define MOUSE_SELECT_RECT				24			///< Rectangle selection cursor.
#define MOUSE_SELECT_POLY				25			///< Polygon selection cursor.
#define MOUSE_SPLINETOOLS				26			///< Spline tools cursor.
#define MOUSE_EXTRUDE						27			///< Extrude cursor.
#define MOUSE_NORMALMOVE				28			///< Normal move cursor.
#define MOUSE_ADDPOINTS					29			///< Add points cursor.
#define MOUSE_ADDPOLYGONS				30			///< Add polygons cursor.
#define MOUSE_BRIDGE						31			///< Bridge cursor.
#define MOUSE_MIRROR						32			///< Mirror cursor.
#define MOUSE_PAINTMOVE					33			///< Paint move cursor.
#define MOUSE_PAINTSELECTRECT		34			///< Paint select rectangle cursor.
#define MOUSE_PAINTSELECTCIRCLE	35			///< Paint select circle cursor.
#define MOUSE_PAINTSELECTPOLY		36			///< Paint select polygon cursor.
#define MOUSE_PAINTSELECTFREE		37			///< Paint select free cursor.
#define MOUSE_PAINTMAGICWAND		38			///< Paint magic wand cursor.
#define MOUSE_PAINTCOLORRANGE		39			///< Paint color range cursor.
#define MOUSE_PAINTFILL					40			///< Paint fill cursor.
#define MOUSE_PAINTPICK					41			///< Paint pick cursor.
#define MOUSE_PAINTBRUSH				42			///< Paint brush cursor.
#define MOUSE_PAINTCLONE				43			///< Paint clone cursor.
#define MOUSE_PAINTTEXT					44			///< Paint text cursor.
#define MOUSE_PAINTCROP					45			///< Paint crop cursor.
#define MOUSE_PAINTLINE					46			///< Paint line cursor.
#define MOUSE_PAINTPOLYSHAPE		47			///< Paint polygon shape cursor.
/// @}

/// @addtogroup EVMSG
/// @ingroup group_enumeration
/// @{
/// Global events
#define EVMSG_CHANGE								604										///< Sent by EventAdd().
#define EVMSG_DOCUMENTRECALCULATED	'drcl'								///< Sent while drawing after the animation, expressions and cache building have been done.\n
																													///< It allows that certain managers (e.g. Attribute Manager) update their values to the changes done by the expressions etc.\n
																													///< @warning Any reactions on this message should be fast.\n
																													///< No modifying stuff must be done here as the draw thread is running at the same time and accesses the same data!
#define EVMSG_TOOLCHANGED						Int32(0xfff36465)			///< A tool setting has changed (local event).
#define EVMSG_GRAPHVIEWCHANGED			400008000							///< Something in XPresso has been changed (local event).
#define EVMSG_AUTKEYMODECHANGED			200000009							///< The autokey mode was changed.
#define EVMSG_UPDATEHIGHLIGHT				200000073							///< Sent by in the case that only the highlighting changes.\n
																													///< This happens for example when the mouse is moved over the viewport. Plugins usually do not need to care about this.
#define EVMSG_CHANGEDSCRIPTMODE			1026569								///< Sent when the script mode (Python, @COFFEE) changed.

#define EVMSG_SHOWIN_SB		-200000074			///< Show in Scene Browser.
#define EVMSG_SHOWIN_TL		-200000075			///< Show in Timeline.
#define EVMSG_SHOWIN_FC		-200000076			///< Show in Function Curve editor.
#define EVMSG_SHOWIN_LM		-200000077			///< Show in Layer Manager.
#define EVMSG_TLOM_MERGE	-465001000			///< @markPrivate

#define EVMSG_SHOWIN_MT	-200000078			///< Show in Motion editor.

#define EVMSG_TIMELINESELECTION	-1001			///< A timeline selection has been changed (local event).
#define EVMSG_BROWSERCHANGE			-1002			///< Something in the browser has been changed (local event).
#define EVMSG_MATERIALSELECTION	-1009			///< A material selection has been changed (local event).
#define EVMSG_FCURVECHANGE			-1010			///< Something in the F-Curve manager has been changed (local event).

#define EVMSG_RAYTRACER_FINISHED		-1003					///< @markPrivate
#define EVMSG_MATERIALPREVIEW				-1008					///< @markPrivate
#define EVMSG_ACTIVEVIEWCHANGED			'acvw'				///< @markPrivate
#define EVMSG_ASYNCEDITORMOVE				'edmv'				///< The user moved something in the editor window. Managers should update things like position fields.
#define EVMSG_TAKECHANGED						431000159			///< Sent by the Take System when the current Take ID changed to let all managers react to the new status. @since R17.032

#define MOVE_START		0			///< Move started.
#define MOVE_CONTINUE	1			///< Move continued.
#define MOVE_END			2			///< Move ended. @c par2 == @em ESC
#define EVMSG_TIMECHANGED						'tchg'				///< @markPrivate
#define EVMSG_VIEWWINDOW_OUTPUT			-1011					///< @markPrivate
#define EVMSG_VIEWWINDOW_3DPAINTUPD	-1012					///< @markPrivate
#define EVMSG_UPDATESCHEME					200000010			///< Scheme has been updated.
#define SCHEME_LIGHT	0			///< Light.
#define SCHEME_DARK		1			///< Dark.
#define SCHEME_OTHER	2			///< Other.
/// @}

/// @addtogroup EVENT
/// @ingroup group_enumeration
/// @{
enum EVENT
{
	EVENT_0									= 0,						///< None.
	EVENT_FORCEREDRAW				= (1 << 0),			///< Force a complete redraw.
	EVENT_ANIMATE						= (1 << 1),			///< Animate document.
	EVENT_NOEXPRESSION			= (1 << 2),			///< Do not execute expressions.
	EVENT_GLHACK						= (1 << 3),			///< @markPrivate
	EVENT_CAMERAEXPRESSION	= (1 << 4),			///< If set (and not @ref EVENT_NOEXPRESSION), the event will only update camera dependent expressions (for faster speed).
	EVENT_ENQUEUE_REDRAW		= (1 << 5)			///< Do not stop the current redraw if @ref DrawViews() is running at the moment. In that case enqueue the redraw after the current draw is done. @since R17.032
} ENUM_END_FLAGS(EVENT);
/// @}

/// @addtogroup DRAWFLAGS
/// @ingroup group_enumeration
/// @{
enum DRAWFLAGS
{
	DRAWFLAGS_0														= 0,							///< None.
	DRAWFLAGS_NO_THREAD										= (1 << 1),				///< Synchronous call.
	DRAWFLAGS_NO_REDUCTION								= (1 << 2),				///< Ignore redraw limit.
	DRAWFLAGS_NO_ANIMATION								= (1 << 8),				///< Ignore all animation.
	DRAWFLAGS_ONLY_ACTIVE_VIEW						= (1 << 10),			///< Only redraw the active view.
	DRAWFLAGS_NO_EXPRESSIONS							= (1 << 12),			///< Ignore expressions.
	DRAWFLAGS_INDRAG											= (1 << 13),			///< In drag.
	DRAWFLAGS_NO_HIGHLIGHT_PLANE					= (1 << 14),			///< The entire view is drawn, not just the highlight plane.
	DRAWFLAGS_FORCEFULLREDRAW							= (1 << 15),			///< Force full redraw.
	DRAWFLAGS_ONLY_CAMERAEXPRESSION				= (1 << 16),			///< Camera expression.
	DRAWFLAGS_INMOVE											= (1 << 17),			///< In move.
	DRAWFLAGS_ONLY_BASEDRAW								= (1 << 22),			///< Draw specific base draw only.
	DRAWFLAGS_ONLY_HIGHLIGHT							= (1 << 18),			///< Only highlights.
	DRAWFLAGS_STATICBREAK									= (1 << 19),			///< If the display is done in the main thread (@C4D only does this during animation playback) this allows that a special thread is used to poll the escape key.
																													///< @note Use only in combination with @ref DRAWFLAGS_NO_THREAD.
	DRAWFLAGS_PRIVATE_NO_WAIT_GL_FINISHED	= (1 << 3),				///< @markPrivate
	DRAWFLAGS_PRIVATE_ONLYBACKGROUND			= (1 << 4),				///< @markPrivate
	DRAWFLAGS_PRIVATE_NOBLIT							= (1 << 9),				///< @markPrivate
	DRAWFLAGS_PRIVATE_OPENGLHACK					= (1 << 11),			///< @markPrivate
	DRAWFLAGS_PRIVATE_ONLY_PREPARE				= (1 << 21),			///< @markPrivate
	DRAWFLAGS_PRIVATE_NO_3DCLIPPING				= (1 << 24)				///< @markPrivate
} ENUM_END_FLAGS(DRAWFLAGS);
/// @}

/// @addtogroup ANIMATEFLAGS
/// @ingroup group_enumeration
/// @{
enum ANIMATEFLAGS
{
	ANIMATEFLAGS_0						= 0,						///< None.
	ANIMATEFLAGS_NO_PARTICLES	= (1 << 2),			///< Ignore particles.
	ANIMATEFLAGS_NO_CHILDREN	= (1 << 6),			///< Do not animate children.
	ANIMATEFLAGS_INRENDER			= (1 << 7),			///< Prepare to render scene.
	ANIMATEFLAGS_NO_MINMAX		= (1 << 8),			///< @markPrivate
	ANIMATEFLAGS_NO_NLA				= (1 << 9),			///< @markPrivate
	ANIMATEFLAGS_NLA_SUM			= (1 << 10)			///< @markPrivate
} ENUM_END_FLAGS(ANIMATEFLAGS);
/// @}

/// @addtogroup SAVEDOCUMENTFLAGS
/// @ingroup group_enumeration
/// @{
/// Flags for saving documents.
/// @see SaveDocument()
enum SAVEDOCUMENTFLAGS
{
	SAVEDOCUMENTFLAGS_0										= 0,						///< None.
	SAVEDOCUMENTFLAGS_DIALOGSALLOWED			= (1 << 0),			///< Flag to inform that a dialog can be displayed. If this flag not set then no dialogs must be opened.
	SAVEDOCUMENTFLAGS_SAVEAS							= (1 << 1),			///< Forces a "Save As" and opens the file dialog.
	SAVEDOCUMENTFLAGS_DONTADDTORECENTLIST	= (1 << 2),			///< Do not add the saved document to the recent file list.
	SAVEDOCUMENTFLAGS_AUTOSAVE						= (1 << 3),			///< Sets the @em Autosave mode. Files are not added to the recent file list and the document change star will not be reset.
	SAVEDOCUMENTFLAGS_SAVECACHES					= (1 << 4),			///< For @em melange export only. Caches of objects will also be written (only supported by @C4D file format).
	SAVEDOCUMENTFLAGS_EXPORTDIALOG				= (1 << 5),			///< Opens the Export dialog.
	SAVEDOCUMENTFLAGS_CRASHSITUATION			= (1 << 6),			///< This flag is passed to @C4D if a crash occurred.
	SAVEDOCUMENTFLAGS_NO_SHADERCACHE			= (1 << 7)			///< Disables the @ref SCENEFILTER_SAVE_BINARYCACHE flag.
} ENUM_END_FLAGS(SAVEDOCUMENTFLAGS);
/// @}


/// @addtogroup COPYFLAGS
/// @ingroup group_enumeration
/// @{
/// Flags for the copy of @C4D objects.
enum COPYFLAGS
{
	COPYFLAGS_0																	= 0,							///< None.
	COPYFLAGS_NO_HIERARCHY											= (1 << 2),				///< Copy without children.
	COPYFLAGS_NO_ANIMATION											= (1 << 3),				///< Copy without tracks, sequences or keys.
	COPYFLAGS_NO_BITS														= (1 << 4),				///< Do not copy BaseList2D bits.
	COPYFLAGS_NO_MATERIALPREVIEW								= (1 << 5),				///< Do not create a new material preview.
	COPYFLAGS_NO_BRANCHES												= (1 << 7),				///< Do not copy branches, for example tags on an object. Automatically implies @ref COPYFLAGS_NO_ANIMATION, as animation is a branch.
	COPYFLAGS_DOCUMENT													= (1 << 10),			///< This is a read-only flag that is set when a complete document is copied.
	COPYFLAGS_NO_NGONS													= (1 << 11),			///< Do not copy N-gons.
	COPYFLAGS_CACHE_BUILD												= (1 << 13),			///< This is a read-only flag that is set when a cache is built.
	COPYFLAGS_RECURSIONCHECK										= (1 << 14),			///< Checks and avoids instances to cause recursions.

	COPYFLAGS_PRIVATE_IDENTMARKER								= (1 << 0),				///< @markPrivate
	COPYFLAGS_PRIVATE_NO_INTERNALS							= (1 << 8),				///< @markPrivate
	COPYFLAGS_PRIVATE_NO_PLUGINLAYER						= (1 << 9),				///< @markPrivate
	COPYFLAGS_PRIVATE_UNDO											= (1 << 12),			///< @markPrivate
	COPYFLAGS_PRIVATE_CONTAINER_COPY_DIRTY			= (1 << 15),			///< @markPrivate
	COPYFLAGS_PRIVATE_CONTAINER_COPY_IDENTICAL	= (1 << 16),			///< @markPrivate
	COPYFLAGS_PRIVATE_NO_TAGS										= (1 << 17),			///< @markPrivate
	COPYFLAGS_PRIVATE_DELETE										= (1 << 18),			///< @markPrivate
	COPYFLAGS_PRIVATE_NO_ASSETS									= (1 << 20),			///< @markPrivate
	COPYFLAGS_PRIVATE_NO_RESULTASSETS						= (1 << 21),			///< @markPrivate
	COPYFLAGS_PRIVATE_NO_LOGS										= (1 << 22),			///< @markPrivate @since R17.048
	COPYFLAGS_PRIVATE_BODYPAINT_NODATA					= (1 << 29),			///< @markPrivate
	COPYFLAGS_PRIVATE_BODYPAINT_CONVERTLAYER		= (1 << 30)				///< @markPrivate

} ENUM_END_FLAGS(COPYFLAGS);
/// @}

/// @addtogroup UNDOTYPE
/// @ingroup group_enumeration
/// @{
/// Type list for document undos.
/// @see	BaseDocument::AddUndo(UNDOTYPE type, void* data, Bool allowFromThread = false)\n
///				BaseDocument::FindUndoPtr(BaseList2D* bl, UNDOTYPE type)
enum UNDOTYPE
{
	UNDOTYPE_0													= 0,				///< None.

	UNDOTYPE_CHANGE											= 40,				///< Any change to an object, including hierarchy modifications; modification in positioning (object has been moved from A to B), substructures etc. (Needs to be called @b before the change.)
	UNDOTYPE_CHANGE_NOCHILDREN					= 41,				///< Same as @ref UNDOTYPE_CHANGE, but without child modifications. (Needs to be called @b before the change.)
	UNDOTYPE_CHANGE_SMALL								= 42,				///< Change to local data only (e.g. data container). No substructures (e.g. no tags on an object) and no children. (Needs to be called @b before the change.)
	UNDOTYPE_CHANGE_SELECTION						= 43,				///< Change to point/poly/edge selection only. (Needs to be called @b before the change.)

	UNDOTYPE_NEW												= 44,				///< New object/material/tag etc. was created. (Needs to be called @b after action.)
	UNDOTYPE_DELETE											= 45,				///< Object/node/tag etc. to be deleted. (Needs to be called @b before action.)

	UNDOTYPE_ACTIVATE										= 46,				///< Automatically managed by BaseDocument::SetActiveObject, BaseDocument::SetActiveTag, BaseDocument::SetActiveMaterial etc. No need to use manually.
	UNDOTYPE_DEACTIVATE									= 47,				///< Automatically managed by BaseDocument::SetActiveObject, BaseDocument::SetActiveTag, BaseDocument::SetActiveMaterial etc. No need to use manually.

	UNDOTYPE_BITS												= 48,				///< Change to object bits, e.g. selection status. (Needs to be called @b before the change.)
	UNDOTYPE_HIERARCHY_PSR							= 49,				///< Change in hierarchical placement and PSR values. (Needs to be called @b before the change.)

	UNDOTYPE_PRIVATE_STRING							= 9996,			///< @markPrivate
	UNDOTYPE_PRIVATE_MULTISELECTIONAXIS	= 9997,			///< @markPrivate
	UNDOTYPE_START											= 9998,			///< @markPrivate
	UNDOTYPE_END												= 9999			///< @markPrivate
} ENUM_END_LIST(UNDOTYPE);
/// @}

/// @addtogroup DRAWHANDLE
/// @ingroup group_enumeration
/// @{
/// Draw handle types.
/// @see BaseDraw::DrawHandle2D BaseDraw::DrawHandle
enum DRAWHANDLE
{
	DRAWHANDLE_MINI					= 0,			///< Tiny point.
	DRAWHANDLE_SMALL				= 1,			///< Small point.
	DRAWHANDLE_MIDDLE				= 2,			///< Medium point.
	DRAWHANDLE_BIG					= 3,			///< Handle used by object generators and deformers.
	DRAWHANDLE_CUSTOM				= 4,			///< Custom handle.
	DRAWHANDLE_POINTSIZE		= 5,			///< Use the point size to draw the handle.
	DRAWHANDLE_SELPOINTSIZE	= 6				///< Use the size of selected points to draw the handle.
} ENUM_END_LIST(DRAWHANDLE);
/// @}

/// @addtogroup DRAW_ALPHA
/// @ingroup group_enumeration
/// @{
enum DRAW_ALPHA
{
	DRAW_ALPHA_NONE								= 10,			///< No alpha.
	DRAW_ALPHA_INVERTED						= 11,			///< Generates inverted alpha.
	DRAW_ALPHA_NORMAL							= 12,			///< Generates alpha channel from the image's alpha channel. If no alpha channel exists, the alpha value is set to @em 100%.
	DRAW_ALPHA_FROM_IMAGE					= 13,			///< Generates the alpha channel from the RGB image information.
	DRAW_ALPHA_NORMAL_FROM_IMAGE	= 14			///< Generates alpha channel from the image's alpha channel. If no alpha channel exists, the alpha value is generated from the RGB image.
} ENUM_END_LIST(DRAW_ALPHA);
/// @}

/// @addtogroup DRAW_TEXTUREFLAGS
/// @ingroup group_enumeration
/// @{
enum DRAW_TEXTUREFLAGS
{
	DRAW_TEXTUREFLAGS_0														= 0x0,						///< None.

	DRAW_TEXTUREFLAGS_COLOR_IMAGE_TO_LINEAR				= 0x00000001,			///< Converts the embedded color profile to linear color space.
	DRAW_TEXTUREFLAGS_COLOR_SRGB_TO_LINEAR				= 0x00000002,			///< Converts from sRGB color space to linear color space.
	DRAW_TEXTUREFLAGS_COLOR_IMAGE_TO_SRGB					= 0x00000003,			///< Converts the embedded color profile to sRGB color space.
	DRAW_TEXTUREFLAGS_COLOR_LINEAR_TO_SRGB				= 0x00000004,			///< Converts from linear color space to sRGB color space.
	DRAW_TEXTUREFLAGS_COLOR_CORRECTION_MASK				= 0x0000000f,			///< Color correction mask.

	DRAW_TEXTUREFLAGS_USE_PROFILE_COLOR						= 0x00000010,			///< Use color profile color.
	DRAW_TEXTUREFLAGS_ALLOW_FLOATINGPOINT					= 0x00000020,			///< Allow floating point textures (if supported).
	DRAW_TEXTUREFLAGS_TILE												= 0x00000040,			///< Allow tiling with BaseDraw::DrawTexture (overridden in BaseDraw::SetTexture).

	DRAW_TEXTUREFLAGS_INTERPOLATION_NEAREST				= 0x00100000,			///< Nearest texture interpolation.
	DRAW_TEXTUREFLAGS_INTERPOLATION_LINEAR				= 0x00200000,			///< Linear texture interpolation.
	DRAW_TEXTUREFLAGS_INTERPOLATION_LINEAR_MIPMAP	= 0x00400000,			///< MIP map texture interpolation.
	DRAW_TEXTUREFLAGS_INTERPOLATION_MASK					= 0x00f00000			///< Texture interpolation mask.

} ENUM_END_FLAGS(DRAW_TEXTUREFLAGS);
/// @}

/// @addtogroup TOOLDRAW
/// @ingroup group_enumeration
/// @{
enum TOOLDRAW
{
	TOOLDRAW_0					= 0,						///< None.
	TOOLDRAW_HANDLES		= (1 << 0),			///< The active objects handles will be drawn.
	TOOLDRAW_AXIS				= (1 << 1),			///< The active objects axes will be drawn.
	TOOLDRAW_HIGHLIGHTS	= (1 << 2)			///< The highlights will be drawn.
} ENUM_END_FLAGS(TOOLDRAW);
/// @}

/// @addtogroup TOOLDRAWFLAGS
/// @ingroup group_enumeration
/// @{
enum TOOLDRAWFLAGS
{
	TOOLDRAWFLAGS_0					= 0,						///< None.
	TOOLDRAWFLAGS_INVERSE_Z	= (1 << 0),			///< Inverse Z-buffer mode. If set, the drawing engine of @C4D will only draw elements if they are further away from the camera than other objects.\n
																					///< This is mostly used for helplines (such as the semitransparent axis inside of objects).
																					/// @note This mode only works when all objects are drawn so it should be passed last.
	TOOLDRAWFLAGS_HIGHLIGHT	= (1 << 1)			///< Highlight mode.
} ENUM_END_FLAGS(TOOLDRAWFLAGS);
/// @}

/// @addtogroup VIEWCOLOR
/// @ingroup group_enumeration
/// @{
// Viewport colors.
#define VIEWCOLOR_C4DBACKGROUND								0
#define VIEWCOLOR_FILMFORMAT									1
#define VIEWCOLOR_HORIZON											2
#define VIEWCOLOR_GRID_MAJOR									3
#define VIEWCOLOR_GRID_MINOR									4
#define VIEWCOLOR_SPLINESTART									5
#define VIEWCOLOR_SPLINEEND										6
#define VIEWCOLOR_CAMERA											7
#define VIEWCOLOR_PARTICLE										8
#define VIEWCOLOR_PMODIFIER										9
#define DELME_VIEWCOLOR_BONE									10
#define VIEWCOLOR_MODIFIER										11
#define VIEWCOLOR_ACTIVEPOINT									12
#define VIEWCOLOR_INACTIVEPOINT								13
#define VIEWCOLOR_TANGENT											14
#define VIEWCOLOR_ACTIVEPOLYGON								15
#define VIEWCOLOR_INACTIVEPOLYGON							16
#define VIEWCOLOR_TEXTURE											17
#define VIEWCOLOR_TEXTUREAXIS									18
#define VIEWCOLOR_ACTIVEBOX										19
#define VIEWCOLOR_ANIMPATH										20
#define VIEWCOLOR_XAXIS												21
#define VIEWCOLOR_YAXIS												22
#define VIEWCOLOR_ZAXIS												23
#define VIEWCOLOR_WXAXIS											24
#define VIEWCOLOR_WYAXIS											25
#define VIEWCOLOR_WZAXIS											26
#define VIEWCOLOR_SELECT_AXIS									27
#define VIEWCOLOR_LAYER0											28
#define VIEWCOLOR_LAYER1											29
#define VIEWCOLOR_LAYER2											30
#define VIEWCOLOR_LAYER3											31
#define VIEWCOLOR_LAYER4											32
#define VIEWCOLOR_LAYER5											33
#define VIEWCOLOR_LAYER6											34
#define VIEWCOLOR_LAYER7											35
#define VIEWCOLOR_VERTEXSTART									36
#define VIEWCOLOR_VERTEXEND										37
#define VIEWCOLOR_UVMESH_GREYED								38
#define VIEWCOLOR_UVMESH_APOLY								39
#define VIEWCOLOR_UVMESH_IAPOLY								40
#define VIEWCOLOR_UVMESH_APOINT								41
#define VIEWCOLOR_UVMESH_IAPOINT							42
#define VIEWCOLOR_NORMAL											43
#define VIEWCOLOR_ACTIVECHILDBOX							44
#define VIEWCOLOR_ACTIVEPOLYBOX								45
#define VIEWCOLOR_ACTIVEPOLYCHILDBOX					46
#define VIEWCOLOR_SELECTION_PREVIEW						47
#define VIEWCOLOR_MEASURETOOL									48
// #define VIEWCOLOR_AXIS_BAND								49
#define VIEWCOLOR_SHADEDWIRE									50
#define VIEWCOLOR_NGONLINE										51
#define VIEWCOLOR_FRONTFACING									52
#define VIEWCOLOR_BACKFACING									53
#define VIEWCOLOR_MINSOFTSELECT								54
#define VIEWCOLOR_MAXSOFTSELECT								55
#define VIEWCOLOR_MINHNWEIGHT									56
#define VIEWCOLOR_ZEROHNWEIGHT								57
#define VIEWCOLOR_MAXHNWEIGHT									58
#define VIEWCOLOR_IRR													59
#define VIEWCOLOR_OBJECTHIGHLIGHT							60
#define VIEWCOLOR_OBJECTSELECT								61
#define VIEWCOLOR_C4DBACKGROUND_GRAD1					62
#define VIEWCOLOR_C4DBACKGROUND_GRAD2					63
#define VIEWCOLOR_BRUSHPREVIEW								64
#define VIEWCOLOR_SPLINEHULL									65
#define VIEWCOLOR_TOOLHANDLE									66
#define VIEWCOLOR_ACTIVETOOLHANDLE						67
#define VIEWCOLOR_TOOLHANDLEHIGHLIGHT					68
#define VIEWCOLOR_TOOLHANDLE2									69
#define VIEWCOLOR_TOOLHANDLEHIGHLIGHT2				70
#define VIEWCOLOR_ACTIVETOOLHANDLE2						71
#define VIEWCOLOR_TOOLSELECTION								72
#define VIEWCOLOR_BASEGRID										73
#define VIEWCOLOR_VERTEX_NORMAL								74
#define VIEWCOLOR_MOSELECTEDFG								75
#define VIEWCOLOR_MOSELECTEDBG								76
#define VIEWCOLOR_MODESELECTEDFG							77
#define VIEWCOLOR_MODESELECTEDBG							78
#define VIEWCOLOR_TESSELLATIONWIRE						79

#define VIEWCOLOR_MAXCOLORS										80
/// @}

/// @addtogroup DIRTYFLAGS
/// @ingroup group_enumeration
/// @{
/// Objects dirty flags.
/// @see	C4DAtom::GetDirty C4DAtom::SetDirty\n
///				BaseObject::IsDirty BaseObject::SetDirty
enum DIRTYFLAGS
{
	DIRTYFLAGS_0						= 0,						///< None.
	DIRTYFLAGS_MATRIX				= (1 << 1),			///< Matrix changed.
	DIRTYFLAGS_DATA					= (1 << 2),			///< Container changed.
	DIRTYFLAGS_SELECT				= (1 << 3),			///< Check all valid selections of the object, e.g. points, edge, polys.
	DIRTYFLAGS_CACHE				= (1 << 4),			///< Check if the cache of an object has been changed (rebuilt).
	DIRTYFLAGS_CHILDREN			= (1 << 5),			///< Check if the children are dirty.
	DIRTYFLAGS_DESCRIPTION	= (1 << 6),			///< Description changed.

	DIRTYFLAGS_SELECTION_OBJECTS		= (1 << 20),			///< For BaseDocument, object selections have changed.
	DIRTYFLAGS_SELECTION_TAGS				= (1 << 21),			///< For BaseDocument, tag selections have changed.
	DIRTYFLAGS_SELECTION_MATERIALS	= (1 << 22),			///< For BaseDocument, material selections have changed.

	DIRTYFLAGS_ALL	= -1			///< Check all dirty flags.
} ENUM_END_FLAGS(DIRTYFLAGS);
/// @}

/// @addtogroup HDIRTY_ID
/// @ingroup group_enumeration
/// @{
enum HDIRTY_ID
{
	HDIRTY_ID_ANIMATION					= 0,
	HDIRTY_ID_OBJECT						= 1,
	HDIRTY_ID_OBJECT_MATRIX			= 2,
	HDIRTY_ID_OBJECT_HIERARCHY	= 3,
	HDIRTY_ID_TAG								= 4,
	HDIRTY_ID_MATERIAL					= 5,
	HDIRTY_ID_SHADER						= 6,
	HDIRTY_ID_RENDERSETTINGS		= 7,
	HDIRTY_ID_VP								= 8,
	HDIRTY_ID_FILTER						= 9,
	HDIRTY_ID_NBITS							= 10,
	HDIRTY_ID_MAX
} ENUM_END_LIST(HDIRTY_ID);
/// @}

/// @addtogroup HDIRTYFLAGS
/// @ingroup group_enumeration
/// @{
/// @see C4DAtom::GetHDirty C4DAtom::SetHDirty
enum HDIRTYFLAGS
{
	HDIRTYFLAGS_0									= 0,																							///< None.
	HDIRTYFLAGS_ANIMATION					= (1 << (UInt32)HDIRTY_ID_ANIMATION),							///< Animation mask.
	HDIRTYFLAGS_OBJECT						= (1 << (UInt32)HDIRTY_ID_OBJECT),								///< Object data mask.
	HDIRTYFLAGS_OBJECT_MATRIX			= (1 << (UInt32)HDIRTY_ID_OBJECT_MATRIX),					///< Object matrix mask.
	HDIRTYFLAGS_OBJECT_HIERARCHY	= (1 << (UInt32)HDIRTY_ID_OBJECT_HIERARCHY),			///< Object hierarchy mask.
	HDIRTYFLAGS_TAG								= (1 << (UInt32)HDIRTY_ID_TAG),										///< Tag data mask.
	HDIRTYFLAGS_MATERIAL					= (1 << (UInt32)HDIRTY_ID_MATERIAL),							///< %Material data mask.
	HDIRTYFLAGS_SHADER						= (1 << (UInt32)HDIRTY_ID_SHADER),								///< Shader data mask.
	HDIRTYFLAGS_RENDERSETTINGS		= (1 << (UInt32)HDIRTY_ID_RENDERSETTINGS),				///< %Render settings mask.
	HDIRTYFLAGS_VP								= (1 << (UInt32)HDIRTY_ID_VP),										///< Videopost mask.
	HDIRTYFLAGS_FILTER						= (1 << (UInt32)HDIRTY_ID_FILTER),								///< Filter data mask.
	HDIRTYFLAGS_NBITS							= (1 << (UInt32)HDIRTY_ID_NBITS),									///< N-bits data mask.

	HDIRTYFLAGS_ALL								= -1			///< All.
} ENUM_END_FLAGS(HDIRTYFLAGS);
/// @}

/// @addtogroup ROTATIONORDER
/// @ingroup group_enumeration
/// @{
enum ROTATIONORDER
{
	ROTATIONORDER_YXZGLOBAL	= 0,			///< Global YXZ order.
	ROTATIONORDER_YZXGLOBAL	= 1,			///< Global YZX order.
	ROTATIONORDER_ZYXGLOBAL	= 2,			///< Global ZYX order.
	ROTATIONORDER_ZXYGLOBAL	= 3,			///< Global ZXY order.
	ROTATIONORDER_XZYGLOBAL	= 4,			///< Global XZY order.
	ROTATIONORDER_XYZGLOBAL	= 5,			///< Global XYZ order.

	ROTATIONORDER_YXZLOCAL	= 3,			///< Local YXZ order.
	ROTATIONORDER_YZXLOCAL	= 4,			///< Local YZX order.
	ROTATIONORDER_ZYXLOCAL	= 5,			///< Local ZYX order.
	ROTATIONORDER_ZXYLOCAL	= 0,			///< Local ZXY order.
	ROTATIONORDER_XZYLOCAL	= 1,			///< Local XZY order.
	ROTATIONORDER_XYZLOCAL	= 2,			///< Local XYZ order.

	ROTATIONORDER_HPB				= 6,			///< HPB order.
	ROTATIONORDER_DEFAULT		= 6				///< Default order (HPB).
} ENUM_END_LIST(ROTATIONORDER);
/// @}

/// @addtogroup ROTATIONINTERPOLATION
/// @ingroup group_enumeration
/// @{
enum ROTATIONINTERPOLATION
{
	ROTATIONINTERPOLATION_QUATERNION_SLERP = 2,	///< Quaternion Spherical LERP Interpolation (Linear)
	ROTATIONINTERPOLATION_QUATERNION_CUBIC = 3,	///< Quaternion Smooth Cubic Interpolation (former known as Losch)
} ENUM_END_LIST(ROTATIONINTERPOLATION);
/// @}


/// @addtogroup BUILDFLAGS
/// @ingroup group_enumeration
/// @{
/// Flags for building documents and objects.
/// @see Hierarchy::Run BaseDocument::ExecutePasses HierarchyHelp::GetBuildFlags
enum BUILDFLAGS
{
	BUILDFLAGS_0								= 0,						///< None.
	BUILDFLAGS_INTERNALRENDERER	= (1 << 1),			///< Rendering in the editor.
	BUILDFLAGS_EXTERNALRENDERER	= (1 << 2),			///< Rendering externally.
	BUILDFLAGS_ISOPARM					= (1 << 3)			///< Generate isoparm objects.
} ENUM_END_FLAGS(BUILDFLAGS);
/// @}

/// @addtogroup EXECUTIONFLAGS
/// @ingroup group_enumeration
/// @{
/// Flags for the execution of a certain point in the pipeline.
/// @see PriorityList::Add ObjectData::Execute TagData::Execute SceneHookData::Execute
enum EXECUTIONFLAGS
{
	EXECUTIONFLAGS_0							= 0,						///< None.
	EXECUTIONFLAGS_ANIMATION			= (1 << 1),			///< Animation is calculated.
	EXECUTIONFLAGS_EXPRESSION			= (1 << 2),			///< Expressions are calculated.
	EXECUTIONFLAGS_CACHEBUILDING	= (1 << 3),			///< Cache building is done.
	EXECUTIONFLAGS_CAMERAONLY			= (1 << 4),			///< Only camera dependent expressions shall be executed.
	EXECUTIONFLAGS_INDRAG					= (1 << 5),			///< Pipeline is done within scrubbing.
	EXECUTIONFLAGS_INMOVE					= (1 << 6),			///< Pipeline is done within moving.
	EXECUTIONFLAGS_RENDER								= (1 << 7),			///< The external renderer (Picture Viewer) is running.
	EXECUTIONFLAGS_ALLOW_PRIORITYSHIFT	= (1 << 8)			///< Allow to shift this priority with the priority shift tag. @markPrivate
} ENUM_END_FLAGS(EXECUTIONFLAGS);
/// @}

/// @addtogroup SCENEHOOKDRAW
/// @ingroup group_enumeration
/// @{
enum SCENEHOOKDRAW
{
	SCENEHOOKDRAW_0														= 0,						///< None.
	SCENEHOOKDRAW_DRAW_PASS										= (1 << 0),			///< Normal drawing pass.
	SCENEHOOKDRAW_HIGHLIGHT_PASS_BEFORE_TOOL	= (1 << 1),			///< Highlight pass before tool drawing.
	SCENEHOOKDRAW_HIGHLIGHT_PASS							= (1 << 2),			///< Highlight pass.
	SCENEHOOKDRAW_HIGHLIGHT_PASS_INV					= (1 << 3),			///< Inverted highlight pass.
	SCENEHOOKDRAW_DRAW_PASS_AFTER_CLEAR				= (1 << 4)			///< Immediately after clearing the viewport.
} ENUM_END_FLAGS(SCENEHOOKDRAW);
/// @}

/// @addtogroup DESCFLAGS_DESC
/// @ingroup group_enumeration
/// @{
/// @see NodeData::GetDDescription C4DAtom::GetDescription
enum DESCFLAGS_DESC
{
	DESCFLAGS_DESC_0											= 0,						///< None.
	DESCFLAGS_DESC_RESOLVEMULTIPLEDATA		= (1 << 0),			///< Private and unused.
	DESCFLAGS_DESC_LOADED									= (1 << 1),			///< Set if elements have been added to the description, either by loading or manual addition.
	DESCFLAGS_DESC_RECURSIONLOCK					= (1 << 2),			///< @markPrivate
	DESCFLAGS_DESC_DONTLOADDEFAULT				= (1 << 3),			///< Do not load defaults. Used internally for old plugin tools.
	DESCFLAGS_DESC_MAPTAGS								= (1 << 4),			///< If set, the object description will also contain the tag's descriptions (as sub-containers).
	DESCFLAGS_DESC_NEEDDEFAULTVALUE				= (1 << 5),			///< Set if @em "Reset to Default" was called by the user.
	DESCFLAGS_DESC_TRISTATE								= (1 << 6),			///< @markInternal Set when 2 or more objects are shown.
	DESCFLAGS_DESC_EXPORTHELPSYMBOLSMODE	= (1 << 7),			///< @markInternal Used for help file symbol generator export.
	DESCFLAGS_DESC_MATREFLECTANCEOVERLAP	= (1 << 8),			///< @markInternal Used in materials and in tristate (i.e. 2 or more mats selected) to indicate if the reflectance layer setup ovelaps between all materials.
} ENUM_END_FLAGS(DESCFLAGS_DESC);
/// @}

/// @addtogroup DESCFLAGS_GET
/// @ingroup group_enumeration
/// @{
/// @see for NodeData::GetDParameter C4DAtom::GetParameter
enum DESCFLAGS_GET
{
	DESCFLAGS_GET_0											= 0,						///< None.
	DESCFLAGS_GET_PARAM_GET							= (1 << 1),			///< Parameter retrieved.
	DESCFLAGS_GET_NO_GLOBALDATA					= (1 << 4),			///< @markPrivate
	DESCFLAGS_GET_NO_GEDATADEFAULTVALUE	= (1 << 5)			///< If set, the GeData default type will not be initialized for C4DAtom::GetParameter.
} ENUM_END_FLAGS(DESCFLAGS_GET);
/// @}

/// @addtogroup DESCFLAGS_SET
/// @ingroup group_enumeration
/// @{
/// @see for NodeData::SetDParameter C4DAtom::SetParameter
enum DESCFLAGS_SET
{
	DESCFLAGS_SET_0											= 0,						///< None.
	DESCFLAGS_SET_PARAM_SET							= (1 << 1),			///< Parameter set.
	DESCFLAGS_SET_USERINTERACTION				= (1 << 2),			///< Set when the GUI is calling @c SetParameter().
																											///< @note This is the only time when C4DAtom::SetParameter is allowed to use the user interaction elements (e.g. open dialogs, display messages etc.).
	DESCFLAGS_SET_DONTCHECKMINMAX				= (1 << 3),			///< No check is internally done if the parameter passed is within the [min/max] range of the description, to save some time.
	DESCFLAGS_SET_DONTAFFECTINHERITANCE	= (1 << 6),			///< No parameter inheritance, for render settings and post effects only.
	DESCFLAGS_SET_FORCESET							= (1 << 7),			///< Force the set value without @em GetParameter/@em Compare.
																											///< @warning Use only for calls where for sure the value was changed!
	DESCFLAGS_SET_DONTFREESPLINECACHE		= (1 << 8),			///< @markPrivate @since R16.038
	DESCFLAGS_SET_INDRAG								= (1 << 9)			///< Gadget (e.g. Slider) in dragging mode (not finished). @note Only used when DESCFLAGS_SET_USERINTERACTION is set.
} ENUM_END_FLAGS(DESCFLAGS_SET);
/// @}

/// @addtogroup DESCFLAGS_ENABLE
/// @ingroup group_enumeration
/// @{
enum DESCFLAGS_ENABLE
{
	DESCFLAGS_ENABLE_0 = 0			///< None.
} ENUM_END_FLAGS(DESCFLAGS_ENABLE);
/// @}

/// @addtogroup HIERARCHYCLONEFLAGS
/// @ingroup group_enumeration
/// @{
/// @see BaseObject::GetAndCheckHierarchyClone BaseObject::GetHierarchyClone
enum HIERARCHYCLONEFLAGS
{
	HIERARCHYCLONEFLAGS_0					= 0,						///< None.
	HIERARCHYCLONEFLAGS_ASIS			= (1 << 0),			///< Objects unchanged. (Used by e.g. @ref Oarray.)
	HIERARCHYCLONEFLAGS_ASPOLY		= (1 << 1),			///< Objects cloned as polygons. (Used by e.g. HyperNURBS.)
	HIERARCHYCLONEFLAGS_ASLINE		= (1 << 2),			///< Objects cloned as line objects.
	HIERARCHYCLONEFLAGS_ASSPLINE	= (1 << 3)			///< Objects cloned as splines.
} ENUM_END_FLAGS(HIERARCHYCLONEFLAGS);
/// @}

/// @addtogroup CHECKVALUEFORMAT
/// @ingroup group_enumeration
/// @{
/// @see	ErrorStringDialog()\n
///				GeModalDialog::CheckReal
enum CHECKVALUEFORMAT
{
	CHECKVALUEFORMAT_NOTHING	= 0,			///< No unit.
	CHECKVALUEFORMAT_DEGREE		= 1,			///< Degrees.
	CHECKVALUEFORMAT_PERCENT	= 2,			///< Percent.
	CHECKVALUEFORMAT_METER		= 3,			///< Meter. Working unit.
	CHECKVALUEFORMAT_INT			= 5				///< Integer.
} ENUM_END_LIST(CHECKVALUEFORMAT);
/// @}

/// @addtogroup CHECKVALUERANGE
/// @ingroup group_enumeration
/// @{
/// @see	ErrorStringDialog()\n
///				GeModalDialog Check Methods
enum CHECKVALUERANGE
{
	CHECKVALUERANGE_GREATER					= 0,			///< val > x
	CHECKVALUERANGE_GREATEROREQUAL	= 1,			///< val >= x
	CHECKVALUERANGE_LESS						= 2,			///< val < x
	CHECKVALUERANGE_LESSOREQUAL			= 3,			///< val <= x
	CHECKVALUERANGE_BETWEEN					= 4,			///< x > val > y
	CHECKVALUERANGE_BETWEENOREQUAL	= 5,			///< x >= val >= y
	CHECKVALUERANGE_BETWEENOREQUALX	= 6,			///< x >= val > y
	CHECKVALUERANGE_BETWEENOREQUALY	= 7,			///< x > val >= y
	CHECKVALUERANGE_DIFFERENT				= 8				///< x != val
} ENUM_END_LIST(CHECKVALUERANGE);
/// @}

/// @addtogroup PAINTMESHFLAGS
/// @ingroup group_enumeration
/// @{
enum PAINTMESHFLAGS
{
	PAINTMESHFLAGS_0				= 0,							///< None.

	PAINTMESHFLAGS_QUAD			= (1 << 1),				///< Polygon is quadrangle.
	PAINTMESHFLAGS_SEL			= (1 << 6),				///< Polygon is selected.

	PAINTMESHFLAGS_SELA			= (1 << 2),				///< Point a selected.
	PAINTMESHFLAGS_SELB			= (1 << 3),				///< Point b selected.
	PAINTMESHFLAGS_SELC			= (1 << 4),				///< Point c selected.
	PAINTMESHFLAGS_SELD			= (1 << 5),				///< Point d selected.

	PAINTMESHFLAGS_TA				= (1 << 7),				///< Point a temporary selection for link mode.
	PAINTMESHFLAGS_TB				= (1 << 8),				///< Point b temporary selection for link mode.
	PAINTMESHFLAGS_TC				= (1 << 9),				///< Point c temporary selection for link mode.
	PAINTMESHFLAGS_TD				= (1 << 10),			///< Point d temporary selection for link mode.

	PAINTMESHFLAGS_INACTIVE	= (1 << 11),			///< No draw, no change possible.

	PAINTMESHFLAGS_EDGEA		= (1 << 12),			///< Edge a is N-gon line.
	PAINTMESHFLAGS_EDGEB		= (1 << 13),			///< Edge b is N-gon line.
	PAINTMESHFLAGS_EDGEC		= (1 << 14),			///< Edge c is N-gon line.
	PAINTMESHFLAGS_EDGED		= (1 << 15)				///< Edge d is N-gon line.
} ENUM_END_FLAGS(PAINTMESHFLAGS);
/// @}

/// @addtogroup GETBRANCHINFO
/// @ingroup group_enumeration
/// @{
/// @see NodeData::GetBranchInfo GeListNode::GetBranchInfo
enum GETBRANCHINFO
{
	GETBRANCHINFO_0									= 0,						///< None.
	GETBRANCHINFO_ONLYWITHCHILDREN	= (1 << 1),			///< Only return branch if it is in use, i.e. has content.
	GETBRANCHINFO_GELISTNODES				= (1 << 3),			///< @markPrivate
	GETBRANCHINFO_ONLYMODIFIABLE		= (1 << 4)			///< @markPrivate
} ENUM_END_FLAGS(GETBRANCHINFO);
/// @}

/// @addtogroup BRANCHINFOFLAGS
/// @ingroup group_enumeration
/// @{
/// @see BranchInfo::flags
enum BRANCHINFOFLAGS
{
	BRANCHINFOFLAGS_0								= 0,						///< None.
	BRANCHINFOFLAGS_ANIMATE					= (1 << 0),			///< Animate the nodes in this branch.
	BRANCHINFOFLAGS_HIDEINTIMELINE	= (1 << 4),			///< If set, this branch will not show up in the timeline.
} ENUM_END_FLAGS(BRANCHINFOFLAGS);
/// @}

/// @addtogroup GETACTIVEOBJECTFLAGS
/// @ingroup group_enumeration
/// @{
/// @see BaseDocument::GetActiveObjects
enum GETACTIVEOBJECTFLAGS
{
	GETACTIVEOBJECTFLAGS_0							= 0,						///< None.
	GETACTIVEOBJECTFLAGS_CHILDREN				= (1 << 0),			///< Child objects are added to the selection too, provided they are selected. Otherwise only the topmost parent of each chain is added.
	GETACTIVEOBJECTFLAGS_SELECTIONORDER	= (1 << 1)			///< The selection array is sorted in the selection order, e.g. the first selected object is the first element in the array.
} ENUM_END_FLAGS(GETACTIVEOBJECTFLAGS);
/// @}

/// @addtogroup DRAWPASS
/// @ingroup group_enumeration
/// @{
enum DRAWPASS
{
	DRAWPASS_OBJECT			= 0,		///< Object pass.
	DRAWPASS_BOX				= 1,		///< Box pass.
	DRAWPASS_HANDLES		= 2,		///< Handle pass.
	DRAWPASS_HIGHLIGHTS	= 3,		///< Highlight pass.
	DRAWPASS_XRAY				= 4			///< X-Ray pass.
} ENUM_END_LIST(DRAWPASS);
/// @}

/// @addtogroup FORMAT_FILES
/// @ingroup group_enumeration
/// @{
/// Import/export formats.
#define FORMAT_PREF	1000			///< Preferences.
#define FORMAT_WAV	1018			///< WAV sound.
#define FORMAT_L4D	1020			///< Layout.
#define FORMAT_P4D	1022			///< Layout.

#define FORMAT_C4DIMPORT		1001025			///< @C4D import.
#define FORMAT_C4DEXPORT		1001026			///< @C4D export.
#define FORMAT_XMLIMPORT		1001027			///< @C4D XML import.
#define FORMAT_XMLEXPORT		1001028			///< @C4D XML export.
#define FORMAT_C4D4IMPORT		1001029			///< @C4D R4 import.
#define FORMAT_C4D5IMPORT		1001030			///< @C4D R5 import.
#define FORMAT_VRML1IMPORT	1001031			///< VRML 1 import.
#define FORMAT_VRML1EXPORT	1001032			///< VRML 1 export.
#define FORMAT_VRML2IMPORT	1001033			///< VRML 2 import.
#define FORMAT_VRML2EXPORT	1001034			///< VRML 2 export.
#define FORMAT_DXFIMPORT		1001035			///< DXF import.
#define FORMAT_DXFEXPORT		1001036			///< DXF export.
#define FORMAT_3DSIMPORT		1001037			///< 3DS import.
#define FORMAT_3DSEXPORT		1001038			///< 3DS export.
#define FORMAT_OBJIMPORT		1001039			///< Old OBJ import (R16 and older).
#define FORMAT_OBJEXPORT		1001040			///< Old OBJ export (R16 and older).
#define FORMAT_Q3DIMPORT		1001041			///< QuickDraw 3D import.
#define FORMAT_Q3DEXPORT		1001042			///< QuickDraw 3D export.
#define FORMAT_LWSIMPORT		1001043			///< LWS import.
#define FORMAT_LWOIMPORT		1001044			///< LWO import.
#define FORMAT_AIIMPORT			1001045			///< AI import.
#define FORMAT_DEMIMPORT		1001046			///< DEM import.
#define FORMAT_D3DEXPORT		1001047			///< Direct3D export.
#define FORMAT_OBJ2IMPORT		1030177			///< New OBJ import (R17 and newer). @since R17.048
#define FORMAT_OBJ2EXPORT		1030178			///< New OBJ export (R17 and newer). @since R17.048
#define FORMAT_SKPIMPORT		1033845			///< SketchUp import. @since R17.048
/// @}

/// A special constant that sets the (yellowish) highlight transparency mode.
#define HIGHLIGHT_TRANSPARENCY	-140

/// Hermite factor.
#define HERMITEFAK	4.0

#define CREATE_GL_HAS_ROOT	1
#define CREATE_GL_IS_ROOT		2

#define DELETE_GL_HAS_ROOT	1
#define DELETE_GL_IS_ROOT		2

/// @addtogroup SAVEPROJECT
/// @ingroup group_enumeration
/// @{
/// @see SaveProject()
enum SAVEPROJECT
{
	SAVEPROJECT_0													= 0,							///< None.
	SAVEPROJECT_ASSETS										= (1 << 1),				///< Pass if the assets will be taken into account.
	SAVEPROJECT_SCENEFILE									= (1 << 2),				///< Pass if the scene will be taken into account.
	SAVEPROJECT_DIALOGSALLOWED						= (1 << 3),				///< Show dialogs like error messages, a file selection for missing assets or alerts if necessary.
	SAVEPROJECT_SHOWMISSINGASSETDIALOG		= (1 << 4),				///< If an asset is missing show a warning dialog. Flag can be set without @ref SAVEPROJECT_DIALOGSALLOWED.
	SAVEPROJECT_ADDTORECENTLIST						= (1 << 5),				///< Add document to the recent list.
	SAVEPROJECT_DONTCOPYFILES							= (1 << 6),				///< Does the same as without this flag but does not copy the files to the destination. Flag used to simulate the function.
	SAVEPROJECT_PROGRESSALLOWED						= (1 << 7),				///< Show the progress bar in the main window.
	SAVEPROJECT_DONTTOUCHDOCUMENT					= (1 << 8),				///< Document will be in the same state as before the call was made.
	SAVEPROJECT_DONTFAILONMISSINGASSETS		= (1 << 9),				///< If this flag is passed, the function does not fail anymore when assets are missing.
	SAVEPROJECT_ISNET											= (1 << 10),			///< @markPrivate. Set only if NET module is collecting assets.
	SAVEPROJECT_USEDOCUMENTNAMEASFILENAME	= (1 << 11),			///< Use the document name as the file name to save as project.
	SAVEPROJECT_DONTCLEARSUGGESTEDFOLDER	= (1 << 12),			///< Do not change asset paths of nodes.
	SAVEPROJECT_WITHCACHES								= (1 << 13),			///< Save the project with assets. @since R17.048
	SAVEPROJECT_DONTGENERATEPAINTTEX			= (1 << 14),			///< Does the same as without this flag but does not generate the textures from painted materials.
} ENUM_END_FLAGS(SAVEPROJECT);
/// @}

/// @addtogroup ICONDATAFLAGS
/// @ingroup group_enumeration
/// @{
/// @see IconData::flags
enum ICONDATAFLAGS
{
	ICONDATAFLAGS_0									= 0,						///< None.
	ICONDATAFLAGS_APPLYCOLORPROFILE	= (1 << 0),			///< Apply color profile.
	ICONDATAFLAGS_DISABLED					= (1 << 1)			///< Disabled.
} ENUM_END_FLAGS(ICONDATAFLAGS);
/// @}

/// @addtogroup USERAREAFLAGS
/// @ingroup group_enumeration
/// @{
enum USERAREAFLAGS
{
	USERAREA_0						= (0),					///< None.
	USERAREA_TABSTOP			= (1 << 0),			///< Tab stop.
	USERAREA_HANDLEFOCUS	= (1 << 1),			///< Handles focus.
	USERAREA_COREMESSAGE	= (1 << 2),			///< Receives core messages.
																				///< @see The article @link page_core_messages Core Messages@endlink.
	USERAREA_SYNCMESSAGE	= (1 << 3),			///< Receives sync messages.
	USERAREA_DONT_MIRROR	= (1 << 30)			///< Do not mirror the user area.
} ENUM_END_FLAGS(USERAREAFLAGS);
/// @}

/// @addtogroup RESOURCEIMAGE
/// @ingroup group_enumeration
/// @{
/// @C4D bitmap resource IDs.
#define RESOURCEIMAGE_EMPTY_TRI_RIGHT							310002010
#define RESOURCEIMAGE_RED_TRI_RIGHT								310002011
#define RESOURCEIMAGE_EMPTY_RED_TRI_RIGHT					310002012
#define RESOURCEIMAGE_YELLOW_DIAMOND							310002013
#define RESOURCEIMAGE_YELLOW_TRI_RIGHT						310002014
#define RESOURCEIMAGE_YELLOW_TRI_LEFT							310002015
#define RESOURCEIMAGE_EMPTY_YELLOW_DIAMOND				310002016
#define RESOURCEIMAGE_YELLOW_CIRCLE								310002017
#define RESOURCEIMAGE_EMPTY_YELLOW_CIRCLE					310002018
#define RESOURCEIMAGE_EMPTY_BLUE_CIRCLE						310002019
#define RESOURCEIMAGE_BLUE_CIRCLE									310002020
#define RESOURCEIMAGE_EMPTY_YELLOW_CIRCLE_LEFT		310002021
#define RESOURCEIMAGE_EMPTY_YELLOW_CIRCLE_RIGHT		310002022
#define RESOURCEIMAGE_EMPTY_TRI_LEFT							310002001
#define RESOURCEIMAGE_RED_TRI_LEFT								310002002
#define RESOURCEIMAGE_EMPTY_RED_TRI_LEFT					310002003
#define RESOURCEIMAGE_EMPTY_DIAMOND								310002004
#define RESOURCEIMAGE_RED_DIAMOND									310002005
#define RESOURCEIMAGE_EMPTY_RED_DIAMOND						310002006
#define RESOURCEIMAGE_EMPTY_CIRCLE								200000122
#define RESOURCEIMAGE_RED_CIRCLE									300000121
#define RESOURCEIMAGE_EMPTY_RED_CIRCLE						300000122
#define RESOURCEIMAGE_KEYFRAME_BUTTON_UP					440000141
#define RESOURCEIMAGE_KEYFRAME_BUTTON_OVER				440000142
#define RESOURCEIMAGE_KEYFRAME_BUTTON_DOWN				440000143
#define RESOURCEIMAGE_KEYFRAME_BUTTON_EDGE				440000178
#define RESOURCEIMAGE_PIN													9000
#define RESOURCEIMAGE_SUBGROUP										12678
#define RESOURCEIMAGE_UNLOCKED										12679
#define RESOURCEIMAGE_LOCKED											-12679
#define RESOURCEIMAGE_HISTOGRAM										12680
#define RESOURCEIMAGE_PLUS												300000118
#define RESOURCEIMAGE_MINUS												300000119
#define RESOURCEIMAGE_FOLDER											300000123
#define RESOURCEIMAGE_OPENED											300000124
#define RESOURCEIMAGE_CLOSED											300000125
#define RESOURCEIMAGE_ARROWLEFT										300000126
#define RESOURCEIMAGE_ARROWRIGHT									300000127
#define RESOURCEIMAGE_ARROWUP											300000128
#define RESOURCEIMAGE_AMDUPLICATE									300000129
#define RESOURCEIMAGE_MOVE												13563
#define RESOURCEIMAGE_SCALE												13564
#define RESOURCEIMAGE_ROTATE											13565
#define RESOURCEIMAGE_VIEWCHANGE									13640
#define RESOURCEIMAGE_FULLSCREEN									17301
#define RESOURCEIMAGE_CLOSERRELEASED							12097
#define RESOURCEIMAGE_CLOSERPRESSED								-12097
#define RESOURCEIMAGE_CANCEL											300000130
#define RESOURCEIMAGE_OK													300000131
#define RESOURCEIMAGE_OKCANCEL										300000132
#define RESOURCEIMAGE_BOOLGROUP										300000133
#define RESOURCEIMAGE_ADAPTERGROUP								300000134
#define RESOURCEIMAGE_CALCULATEGROUP							300000135
#define RESOURCEIMAGE_DEFAULTGROUP								300000136
#define RESOURCEIMAGE_DEFAULTOPERATOR							300000137
#define RESOURCEIMAGE_GENERALGROUP								300000138
#define RESOURCEIMAGE_ITERATORGROUP								300000139
#define RESOURCEIMAGE_LOGICALGROUP								300000140
#define RESOURCEIMAGE_TPGROUP											300000141
#define RESOURCEIMAGE_COFFEESCRIPT								300000142
#define RESOURCEIMAGE_PYTHONSCRIPT								1022749
#define RESOURCEIMAGE_UVWTAG_SECONDSTATE					300000143
#define RESOURCEIMAGE_INSTANCEOBJECT_SECONDSTATE	300000144
#define RESOURCEIMAGE_LIGHT_SHADOWS								300000145
#define RESOURCEIMAGE_LIGHT_SPOT									300000146
#define RESOURCEIMAGE_LIGHT_SPOTSHADOWS						300000147
#define RESOURCEIMAGE_LIGHT_PARALLEL							300000148
#define RESOURCEIMAGE_LIGHT_PARALLELSHADOWS				300000149
#define RESOURCEIMAGE_LIGHT_AREA									300000150
#define RESOURCEIMAGE_LIGHT_AREASHADOWS						300000151
#define RESOURCEIMAGE_BASEDRAW										300000152
#define RESOURCEIMAGE_CTRACK											300000153
#define RESOURCEIMAGE_BASEKEY											300000154
#define RESOURCEIMAGE_BASESEQUENCE								300000155
#define RESOURCEIMAGE_BASETRACK										300000156
#define RESOURCEIMAGE_UNKNOWN											300000157
#define RESOURCEIMAGE_BASESHADER									300000158
#define RESOURCEIMAGE_PAINTBITMAP									300000159
#define RESOURCEIMAGE_MULTIPLE										300000160
#define RESOURCEIMAGE_EYEACTIVE										300000161
#define RESOURCEIMAGE_EYEINACTIVE									300000162
#define RESOURCEIMAGE_PENACTIVE										300000163
#define RESOURCEIMAGE_PENINACTIVE									300000164
#define RESOURCEIMAGE_ALPHAACTIVE									300000165
#define RESOURCEIMAGE_ALPHAINACTIVE								300000166
#define RESOURCEIMAGE_LINKEDACTIVE								300000167
#define RESOURCEIMAGE_LINKEDINACTIVE							300000168
#define RESOURCEIMAGE_BPAXIS											300000169
#define RESOURCEIMAGE_BPCROSSED										300000170
#define RESOURCEIMAGE_MOCCATREEVIEWNO							300000171
#define RESOURCEIMAGE_MOCCATREEVIEWYES						300000172
#define RESOURCEIMAGE_MOCCATREEVIEWLOCKED					300000173
#define RESOURCEIMAGE_MOCCAIKTAG1									300000174
#define RESOURCEIMAGE_MOCCAIKTAG2									300000175
#define RESOURCEIMAGE_MOCCAIKTAG3									300000176
#define RESOURCEIMAGE_MOCCAIKTAG4									300000177
#define RESOURCEIMAGE_MOCCAIKTAG5									300000178
#define RESOURCEIMAGE_MOCCAIKTAG6									300000185
#define RESOURCEIMAGE_BITMAPFILTERPLUS						300000179
#define RESOURCEIMAGE_BITMAPFILTERMINUS						300000180
#define RESOURCEIMAGE_CLOTHING1										300000181
#define RESOURCEIMAGE_CLOTHING2										300000182
#define RESOURCEIMAGE_CLOTHING3										300000183
#define RESOURCEIMAGE_CLOTHING4										300000184
#define RESOURCEIMAGE_CLEARSELECTION							300000187
#define RESOURCEIMAGE_GENERICCOMMAND							300000188
#define RESOURCEIMAGE_TIMELINE_KEY1								300000191
#define RESOURCEIMAGE_TIMELINE_KEY2								300000192
#define RESOURCEIMAGE_AMMODELOCK_1								300000193
#define RESOURCEIMAGE_AMMODELOCK_2								300000194
#define RESOURCEIMAGE_SCENEBROWSER_HOME						300000195
#define RESOURCEIMAGE_SCENEBROWSER_FILTER1				300000196
#define RESOURCEIMAGE_SCENEBROWSER_FILTER2				300000197
#define RESOURCEIMAGE_SCENEBROWSER_FIND1					300000198
#define RESOURCEIMAGE_SCENEBROWSER_FIND2					300000199
#define RESOURCEIMAGE_SCENEBROWSER_PATH1					300000200
#define RESOURCEIMAGE_SCENEBROWSER_PATH2					300000201
#define RESOURCEIMAGE_TIMELINE_STATE1							300000202
#define RESOURCEIMAGE_TIMELINE_STATE2							300000203
#define RESOURCEIMAGE_TIMELINE_STATE3							300000204
#define RESOURCEIMAGE_TIMELINE_STATE4							300000205
#define RESOURCEIMAGE_TIMELINE_STATE5							300000206
#define RESOURCEIMAGE_TIMELINE_STATE6							300000207
#define RESOURCEIMAGE_TIMELINE_KEYSTATE1					300000208
#define RESOURCEIMAGE_TIMELINE_KEYSTATE2					300000209
#define RESOURCEIMAGE_TIMELINE_KEYSTATE3					300000210
#define RESOURCEIMAGE_TIMELINE_KEYSTATE4					300000211
#define RESOURCEIMAGE_LAYERMANAGER_STATE1					300000212
#define RESOURCEIMAGE_LAYERMANAGER_STATE2					300000213
#define RESOURCEIMAGE_LAYERMANAGER_STATE3					300000214
#define RESOURCEIMAGE_LAYERMANAGER_STATE4					300000215
#define RESOURCEIMAGE_LAYERMANAGER_STATE5					300000216
#define RESOURCEIMAGE_LAYERMANAGER_STATE6					300000217
#define RESOURCEIMAGE_LAYERMANAGER_STATE7					300000218
#define RESOURCEIMAGE_LAYERMANAGER_STATE8					300000219
#define RESOURCEIMAGE_LAYERMANAGER_STATE9					300000220
#define RESOURCEIMAGE_LAYERMANAGER_STATE10				300000221
#define RESOURCEIMAGE_LAYERMANAGER_STATE11				300000222
#define RESOURCEIMAGE_LAYERMANAGER_STATE12				300000223
#define RESOURCEIMAGE_LAYERMANAGER_STATE13				300000224
#define RESOURCEIMAGE_LAYERMANAGER_STATE14				300000225
#define RESOURCEIMAGE_LAYERMANAGER_STATE15				300000226
#define RESOURCEIMAGE_LAYERMANAGER_STATE16				300000227
#define RESOURCEIMAGE_LAYERMANAGER_STATE17				300000228
#define RESOURCEIMAGE_LAYERMANAGER_STATE18				300000229
#define RESOURCEIMAGE_OBJECTMANAGER_STATE1				300000230
#define RESOURCEIMAGE_OBJECTMANAGER_STATE2				300000231
#define RESOURCEIMAGE_OBJECTMANAGER_STATE3				300000232
#define RESOURCEIMAGE_OBJECTMANAGER_STATE4				300000233
#define RESOURCEIMAGE_OBJECTMANAGER_DOT1					300000234
#define RESOURCEIMAGE_OBJECTMANAGER_DOT2					300000235
#define RESOURCEIMAGE_OBJECTMANAGER_DOT3					300000236
#define RESOURCEIMAGE_OBJECTMANAGER_DOT4					300000237
#define RESOURCEIMAGE_OBJECTMANAGER_LOCK					300000238
#define RESOURCEIMAGE_TIMELINE_FOLDER1						300000239
#define RESOURCEIMAGE_TIMELINE_FOLDER2						300000240
#define RESOURCEIMAGE_TIMELINE_FOLDER3						300000241
#define RESOURCEIMAGE_TIMELINE_FOLDER4						300000242
#define RESOURCEIMAGE_TIMELINE_ROOT1							300000243
#define RESOURCEIMAGE_TIMELINE_ROOT2							300000244
#define RESOURCEIMAGE_TIMELINE_ROOT3							300000245
#define RESOURCEIMAGE_OBJECTMANAGER_DISP1					300000246
#define RESOURCEIMAGE_OBJECTMANAGER_DISP2					300000247
#define RESOURCEIMAGE_OBJECTMANAGER_DISP3					300000248
#define RESOURCEIMAGE_OBJECTMANAGER_DISP4					300000249
#define RESOURCEIMAGE_BROWSER_DESKTOP							300000251
#define RESOURCEIMAGE_BROWSER_HOME								300000252
#define RESOURCEIMAGE_BROWSER_PRESET							300000253
#define RESOURCEIMAGE_BROWSER_CATALOG							300000254
#define RESOURCEIMAGE_BROWSER_SEARCH							300000255
#define RESOURCEIMAGE_BROWSER_PLAY								300000256
#define RESOURCEIMAGE_BROWSER_PAUSE								300000257
#define RESOURCEIMAGE_BROWSER_SMALLVIEW						300000258
#define RESOURCEIMAGE_BROWSER_BIGVIEW							300000259
#define RESOURCEIMAGE_ONLINEHELP_HOME							300000260
#define RESOURCEIMAGE_ARROWDOWN										300000263
#define RESOURCEIMAGE_EYETRISTATE									300000264
#define RESOURCEIMAGE_PREVIOUSPAGE								1022433
#define RESOURCEIMAGE_FOLLOWINGPAGE								1022434
#define RESOURCEIMAGE_LIGHT_PHOTOMETRIC						300000265
#define RESOURCEIMAGE_LIGHT_PHOTOMETRICSHADOWS		300000266
#define RESOURCEIMAGE_MENU_OPTIONS								200000283
#define RESOURCEIMAGE_PICKSESSION									200000270
#define RESOURCEIMAGE_PICKSESSION2								200000271
#define HOTKEY_RESIZE_BRUSH												440000144
#define RESOURCEIMAGE_LAYERMANAGER_STATE19				1028287
#define RESOURCEIMAGE_LAYERMANAGER_STATE20				1028288
/// @}

#ifndef __API_INTERN__

	/// @addtogroup HOTKEY
	/// @ingroup group_enumeration
	/// @{
	#define HOTKEY_CAMERA_MOVE		13563				///< Camera move.
	#define HOTKEY_CAMERA_SCALE		13564				///< Camera scale.
	#define HOTKEY_CAMERA_ROTATE	13565				///< Camera rotate.

	#define HOTKEY_OBJECT_MOVE		13566				///< Object move.
	#define HOTKEY_OBJECT_SCALE		13567				///< Object scale.
	#define HOTKEY_OBJECT_ROTATE	13568				///< Object rotate.

	#define HOTKEY_MODEL_SCALE	13569					///< Model scale.
	#define HOTKEY_ZOOM					13570					///< Zoom.
	#define HOTKEY_SELECT_FREE	13571					///< Freehand selection.
	#define HOTKEY_SELECT_LIVE	13572					///< Live selection.
	#define HOTKEY_SELECT_RECT	13573					///< Rectangle selection.

	#define HOTKEY_PARENT_MOVE 440000088			///< Parent object move.
	/// @}

	/// @addtogroup IDM
	/// @ingroup group_enumeration
	/// @{
	#define IDM_UNDO				12105			///< Undo.
	#define IDM_REDO				12297			///< Redo.
	#define IDM_CUT					12106			///< Cut.
	#define IDM_COPY				12107			///< Copy.
	#define IDM_PASTE				12108			///< Paste.
	#define IDM_DELETE			12109			///< Delete.
	#define IDM_SELECTALL		12112			///< Select all.
	#define IDM_SELECTNONE	12113			///< Select none.
	#define IDM_INVERSION		12374			///< Invert selection.
	#define IDM_KEY_LAST		12415			///< Last key.
	#define IDM_KEY_NEXT		12416			///< Next key.
	/// @}

#endif

/// @addtogroup EXECUTIONPRIORITY
/// @ingroup group_enumeration
/// @{
/// Predefined calling points for objects, tags and scene hooks.
/// @see PriorityList::Add ObjectData::Execute TagData::Execute SceneHookData::Execute
#define EXECUTIONPRIORITY_INITIAL				1000				///< Initial.
#define EXECUTIONPRIORITY_ANIMATION			2000				///< Animation.
#define EXECUTIONPRIORITY_ANIMATION_NLA	2010				///< NLA.
#define EXECUTIONPRIORITY_EXPRESSION		3000				///< Expression.
#define EXECUTIONPRIORITY_DYNAMICS			4000				///< Dynamics.
#define EXECUTIONPRIORITY_GENERATOR			5000				///< Generators.
#define EXECUTIONPRIORITY_FORCE					2147483647	///< Highest priority that will ensure execution even if the execution pipeline is cancelled before. Only use this to e.g. release locks or do super-fast non-blocking operations.
/// @}

/// @addtogroup EXECUTIONRESULT
/// @ingroup group_enumeration
/// @{
/// Predefined result codes for objects, tags and scene hooks execution.
/// @see ObjectData::Execute TagData::Execute SceneHookData::Execute
enum EXECUTIONRESULT
{
	EXECUTIONRESULT_OK					= 0,			///< OK.
	EXECUTIONRESULT_USERBREAK		= 1,			///< %User break.
	EXECUTIONRESULT_OUTOFMEMORY	= 2				///< Not enough memory.
} ENUM_END_LIST(EXECUTIONRESULT);
/// @}

/// @addtogroup DLG
/// @ingroup group_enumeration
/// @{
enum
{
	DLG_OK			= 1,			///< OK button.
	DLG_CANCEL	= 2			///< Cancel button.
};
/// @}

/// @addtogroup IMAGERESULT
/// @ingroup group_enumeration
/// @{
/// Result codes for image initialization, open, save etc.
enum IMAGERESULT
{
	IMAGERESULT_OK							=  1,		///< Image loaded/created.
	IMAGERESULT_NOTEXISTING			= -1,		///< Image does not exist.
	IMAGERESULT_WRONGTYPE				= -2,		///< Image has the wrong type.
	IMAGERESULT_OUTOFMEMORY			= -3,		///< Not enough memory.
	IMAGERESULT_FILEERROR				= -4,		///< File error.
	IMAGERESULT_FILESTRUCTURE		= -5,		///< Invalid file structure.
	IMAGERESULT_MISC_ERROR			= -6,		///< Unknown error.
	IMAGERESULT_PARAM_ERROR			= -7,		///< Parameter error.
	IMAGERESULT_THREADCANCELED	= -8		///< Thread canceled while working.
} ENUM_END_LIST(IMAGERESULT);
/// @}

/// @addtogroup STRINGENCODING
/// @ingroup group_enumeration
/// @{
enum STRINGENCODING
{
	STRINGENCODING_XBIT			= 0,			///< An OS dependent encoding. Only use this if data is passed to an OS functions. The actual coding is unspecified.
																		///< @note Previously it has been said that this encoding is @em UTF-8. That is not true.
	STRINGENCODING_8BIT			= 1,			///< <i>8</i>-bit ASCII. Discards Unicode information.
	STRINGENCODING_7BIT			= 2,			///< <i>7</i>-bit ASCII. Does not understand any international characters, e.g. \"&aring;&auml;&uuml;&ouml;\".
	STRINGENCODING_7BITHEX	= 3,			///< <i>7</i>-bit ASCII, with any non <i>7</i>-bit characters encoded in the text as e.g. "\uEFA0".
	STRINGENCODING_UTF8			= 4,			///< UTF-<i>8</i> encoding.
	STRINGENCODING_HTML			= 5				///< HTML encoding.
} ENUM_END_LIST(STRINGENCODING);
/// @}

/// @addtogroup THREADMODE
/// @ingroup group_enumeration
/// @{
enum THREADMODE
{
	THREADMODE_DEPRECATED_SYNCHRONOUS	= 0,			///< Synchronous thread. @markDeprecated
	THREADMODE_ASYNC									= 1,			///< Asynchronous thread.
	THREADMODE_PRIVATE_OPENGL					= 3
} ENUM_END_LIST(THREADMODE);
/// @}

/// @addtogroup THREADPRIORITY
/// @ingroup group_enumeration
/// @{
enum THREADPRIORITY
{
	THREADPRIORITY_NORMAL	= 0,				///< Normal.
	THREADPRIORITY_ABOVE	= 1000,			///< Above.
	THREADPRIORITY_BELOW	= 1001,			///< Below.
	THREADPRIORITY_LOWEST	= 1002			///< Lowest.
} ENUM_END_LIST(THREADPRIORITY);
/// @}

/// @addtogroup HYPERFILEARRAY
/// @ingroup group_enumeration
/// @{
enum HYPERFILEARRAY
{
	HYPERFILEARRAY_CHAR		= 1,			///< ::Char array.
	HYPERFILEARRAY_WORD		= 2,			///< ::Int16 array.
	HYPERFILEARRAY_LONG		= 3,			///< ::Int32 array.
	HYPERFILEARRAY_LLONG	= 4,			///< ::Int64 array.
	HYPERFILEARRAY_SREAL	= 5,			///< ::Float32 array.
	HYPERFILEARRAY_LREAL	= 6,			///< ::Float64 array.
	HYPERFILEARRAY_REAL		= 7				///< ::Float array.
} ENUM_END_LIST(HYPERFILEARRAY);
/// @}

/// @addtogroup FILEERROR
/// @ingroup group_enumeration
/// @{
enum FILEERROR
{
	FILEERROR_NONE				=  0,			///< No error.
	FILEERROR_OPEN				= -1,			///< Problems opening the file.
	FILEERROR_CLOSE				= -2,			///< Problems closing the file.
	FILEERROR_READ				= -3,			///< Problems reading the file.
	FILEERROR_WRITE				= -4,			///< Problems writing the file.
	FILEERROR_SEEK				= -5,			///< Problems seeking the file.
	FILEERROR_INVALID			= -6,			///< Invalid parameter or operation (e.g. writing in read-mode).
	FILEERROR_OUTOFMEMORY	= -7,			///< Not enough memory.
	FILEERROR_USERBREAK		= -8,			///< %User break.

	// The following errors can only occur with an HyperFile
	FILEERROR_WRONG_VALUE			= -100,			///< Other value detected than expected.
	FILEERROR_CHUNK_NUMBER		= -102,			///< Wrong number of chunks or sub-chunks detected.
	FILEERROR_VALUE_NO_CHUNK	= -103,			///< There was a value without any enclosing START/STOP chunks.
	FILEERROR_FILE_END				= -104,			///< The file end was reached without finishing reading.
	FILEERROR_UNKNOWN_VALUE		= -105			///< Unknown value detected.
} ENUM_END_LIST(FILEERROR);
/// @}

/// @addtogroup FILEOPEN
/// @ingroup group_enumeration
/// @{
enum FILEOPEN
{
	FILEOPEN_APPEND				= 0,			///< Open an existing file for writing and set the position to the end of that file.
	FILEOPEN_READ					= 1,			///< Open the file for reading.
	FILEOPEN_WRITE				= 2,			///< Create a new file for writing.\n
																	///< @warning If the file name points to an existing file, it will be overwritten.
	FILEOPEN_READWRITE		= 3,			///< Open the file for both reading and writing.
	FILEOPEN_READ_NOCACHE	= 4,			///< @markPrivate
	FILEOPEN_SHAREDREAD		= 5,			///< @markPrivate
	FILEOPEN_SHAREDWRITE	= 6				///< @markPrivate
} ENUM_END_LIST(FILEOPEN);
/// @}

/// @addtogroup LOCATION
/// @ingroup group_enumeration
/// @{
enum LOCATION
{
	LOCATION_DISK					= 1,			///< Disk storage.
	LOCATION_IPCONNECTION	= 2,			///< Target is IP connection.
	LOCATION_MEMORY				= 3				///< Target is a memory location.
} ENUM_END_LIST(LOCATION);
/// @}

/// @addtogroup FILESEEK
/// @ingroup group_enumeration
/// @{
enum FILESEEK
{
	FILESEEK_START		= 0,			///< The position is given relative to the start of the file.
	FILESEEK_RELATIVE	= 2				///< The position is given relative to the current position.
} ENUM_END_LIST(FILESEEK);
/// @}

/// @addtogroup FILEDIALOG
/// @ingroup group_enumeration
/// @{
enum FILEDIALOG
{
	FILEDIALOG_NONE				= 0,			///< Never show an error dialog.
	FILEDIALOG_ANY				= 1,			///< Show an error dialog for any error.
	FILEDIALOG_IGNOREOPEN	= 2				///< Do not show an error dialog if the file does not exist, otherwise like @ref FILEDIALOG_ANY.
} ENUM_END_LIST(FILEDIALOG);
/// @}

/// @addtogroup FILESELECT
/// @ingroup group_enumeration
/// @{
enum FILESELECT
{
	FILESELECT_LOAD				= 0,			///< Load dialog.
	FILESELECT_SAVE				= 1,			///< Save dialog.
	FILESELECT_DIRECTORY	= 2				///< Folder selection dialog.
} ENUM_END_LIST(FILESELECT);
/// @}

/// @addtogroup FILESELECTTYPE
/// @ingroup group_enumeration
/// @{
enum FILESELECTTYPE
{
	FILESELECTTYPE_ANYTHING		= 0,			///< Any file.
	FILESELECTTYPE_IMAGES			= 1,			///< Image files.
	FILESELECTTYPE_SCENES			= 2,			///< 3D scene files.
	FILESELECTTYPE_COFFEE			= 3,			///< @COFFEE files.
	FILESELECTTYPE_BODYPAINT	= 4				///< @BP3D files.
} ENUM_END_LIST(FILESELECTTYPE);
/// @}

/// @addtogroup OPERATINGSYSTEM
/// @ingroup group_enumeration
/// @{
enum OPERATINGSYSTEM
{
	OPERATINGSYSTEM_WIN		= 1,			///< Windows.
	OPERATINGSYSTEM_OSX		= 2,			///< OS X.
	OPERATINGSYSTEM_UNIX	= 3				///< UNIX.
} ENUM_END_LIST(OPERATINGSYSTEM);
/// @}

/// @addtogroup BYTEORDER
/// @ingroup group_enumeration
/// @{
enum BYTEORDER
{
	BYTEORDER_MOTOROLA	= 1,			///< Motorola, big endian.
	BYTEORDER_INTEL			= 2				///< Intel, little endian.
} ENUM_END_LIST(BYTEORDER);
/// @}

/// @addtogroup HYPERFILEVALUE
/// @ingroup group_enumeration
/// @{
enum HYPERFILEVALUE
{
	HYPERFILEVALUE_NONE								=  0,			///< None.

	HYPERFILEVALUE_START							=  1,			///< Marks the start of a chunk.
	HYPERFILEVALUE_STOP								=  2,			///< Marks the end of a chunk.
	HYPERFILEVALUE_CSTOP							=  3,			///< Marks the end of a container. @markInternal
	HYPERFILEVALUE_CHAR								= 11,			///< ::Char.
	HYPERFILEVALUE_UCHAR							= 12,			///< ::UChar.
	HYPERFILEVALUE_INT16							= 13,			///< ::Int16.
	HYPERFILEVALUE_UINT16							= 14,			///< ::UInt16.
	HYPERFILEVALUE_INT32							= 15,			///< ::Int32.
	HYPERFILEVALUE_UINT32							= 16,			///< ::UInt32.
	HYPERFILEVALUE_INT64							= 17,			///< ::Int64.
	HYPERFILEVALUE_UINT64							= 18,			///< ::UInt64.
	HYPERFILEVALUE_FLOAT							= 19,			///< ::Float.
	HYPERFILEVALUE_FLOAT64						= 20,			///< ::Float64.
	HYPERFILEVALUE_BOOL								= 21,			///< ::Bool.
	HYPERFILEVALUE_TIME								= 22,			///< BaseTime.
	HYPERFILEVALUE_VECTOR							= 23,			///< ::Vector.
	HYPERFILEVALUE_VECTOR64						= 24,			///< ::Vector64.
	HYPERFILEVALUE_MATRIX							= 25,			///< ::Matrix.
	HYPERFILEVALUE_MATRIX64						= 26,			///< ::Matrix64.
	HYPERFILEVALUE_VECTOR32						= 27,			///< ::Vector32.
	HYPERFILEVALUE_MATRIX32						= 28,			///< ::Matrix32.
	HYPERFILEVALUE_FLOAT32						= 29,			///< ::Float32.

	HYPERFILEVALUE_MEMORY							= 128,			///< Memory.
	HYPERFILEVALUE_IMAGE							= 129,			///< Image.
	HYPERFILEVALUE_STRING							= 130,			///< String.
	HYPERFILEVALUE_FILENAME						= 131,			///< Filename.
	HYPERFILEVALUE_CONTAINER					= 132,			///< BaseContainer.
	HYPERFILEVALUE_ALIASLINK					= 138,			///< BaseLink.
	HYPERFILEVALUE_LMEMORY						= 139,			///< Long memory.
	HYPERFILEVALUE_VECTOR_ARRAY_EX		= 133,			///< @markDeprecated
	HYPERFILEVALUE_POLYGON_ARRAY_EX		= 134,			///< @markDeprecated
	HYPERFILEVALUE_UINT16_ARRAY_EX		= 135,			///< @markDeprecated
	HYPERFILEVALUE_PARTICLE_ARRAY_EX	= 136,			///< @markDeprecated
	HYPERFILEVALUE_SREAL_ARRAY_EX			= 137,			///< @markDeprecated
	HYPERFILEVALUE_ARRAY							= 140,			///< Array.
	HYPERFILEVALUE_UUID								= 141				///< C4DUuid.
} ENUM_END_LIST(HYPERFILEVALUE);
/// @}

/// @addtogroup FINDANIM
/// @ingroup group_enumeration
/// @{
enum FINDANIM
{
	FINDANIM_EXACT	= 0,			///< Exact.
	FINDANIM_LEFT		= 1,			///< Search left.
	FINDANIM_RIGHT	= 2				///< Search right.
} ENUM_END_LIST(FINDANIM);
/// @}

/// @addtogroup CCURVE
/// @ingroup group_enumeration
/// @{
enum CCURVE
{
	CCURVE_CURVE			= 1,			///< Standard curve.
	CCURVE_HLE_BASE		= 2,			///< Internal reduced modification reference curve.
	CCURVE_HLE_CURVE	= 3,			///< Reduced Modification Curve - Curve.
	CCURVE_SS_CURVE		= 4,			///< Snapshot 1.

	// Multiple Snapshots
	CCURVE_SS_CURVE2	= 5,			///< Snapshot 2.
	CCURVE_SS_CURVE3	= 6,			///< Snapshot 3.
	CCURVE_SS_CURVE4	= 7,			///< Snapshot 4.
	CCURVE_SS_CURVE5	= 8,			///< Snapshot 5.

	// Scale and Move HLE Curve
	CCURVE_HLE_SCALE	= 9,			///< Reduced modification curve - scale.
	CCURVE_HLE_MOVE		= 10			///< Reduced modification curve - move.
} ENUM_END_LIST(CCURVE);
/// @}

/// @addtogroup CLOOP
/// @ingroup group_enumeration
/// @{
enum CLOOP
{
	CLOOP_OFF						= 0,			///< No loop.
	CLOOP_CONSTANT			= 1,			///< Constant.
	CLOOP_CONTINUE			= 2,			///< Continue.
	CLOOP_REPEAT				= 3,			///< Repeat.
	CLOOP_OFFSETREPEAT	= 4,			///< Offset repeat.
	CLOOP_OSCILLATE			= 5				///< Oscillate.
} ENUM_END_LIST(CLOOP);
/// @}

/// @addtogroup CINTERPOLATION
/// @ingroup group_enumeration
/// @{
enum CINTERPOLATION
{
	CINTERPOLATION_SPLINE	= 1,			///< Spline.
	CINTERPOLATION_LINEAR	= 2,			///< Linear.
	CINTERPOLATION_STEP		= 3,			///< Step.

	CINTERPOLATION_DUMMY	= 4
} ENUM_END_LIST(CINTERPOLATION);
/// @}

/// @addtogroup CAUTOMODE
/// @ingroup group_enumeration
/// @{
/// @since R17.032
enum CAUTOMODE
{
	CAUTOMODE_CLASSIC			= 1,				///< AutoTangent first implementation.
	CAUTOMODE_FIXEDSLOPE	= 2,				///< AutoTangent with fixed slope for given time.
} ENUM_END_LIST(CAUTOMODE);
/// @}

/// @addtogroup CKEYPRESET
/// @ingroup group_enumeration
/// @{
/// @since R17.032
enum CKEYPRESET
{
	CKEYPRESET_CLASSICAUTO			= 1,			///< Auto, Classical, Clamp.
	CKEYPRESET_NEWAUTO					= 2,			///< Auto, Classical, remove Overshooting.
	CKEYPRESET_NEWAUTOWEIGHTED	= 3,			///< Auto, Fixed Slope, remove Overshooting.
	CKEYPRESET_CUSTOM						= 4,			///< User Defined.
} ENUM_END_LIST(CKEYPRESET);
/// @}

/// @addtogroup CLIPBOARDTYPE
/// @ingroup group_enumeration
/// @{
enum CLIPBOARDTYPE
{
	CLIPBOARDTYPE_EMPTY		= 0,			///< Clipboard is empty.
	CLIPBOARDTYPE_STRING	= 1,			///< Clipboard contains a string.
	CLIPBOARDTYPE_BITMAP	= 2				///< Clipboard contains a bitmap.
} ENUM_END_LIST(CLIPBOARDTYPE);
/// @}

/// @addtogroup EDGESELECTIONTYPE
/// @ingroup group_enumeration
/// @{
/// @see PolygonObject::GetSelectedEdges PolygonObject::SetSelectedEdges() PolygonObject::GetEdgeSelection
enum EDGESELECTIONTYPE
{
	EDGESELECTIONTYPE_SELECTION	= 0,			///< Selected edges.
	EDGESELECTIONTYPE_HIDDEN		= 1,			///< Hidden edges.
	EDGESELECTIONTYPE_PHONG			= 2				///< Phong edges.
} ENUM_END_LIST(EDGESELECTIONTYPE);
/// @}

/// @addtogroup REGISTRYTYPE
/// @ingroup group_enumeration
/// @{
enum REGISTRYTYPE
{
	REGISTRYTYPE_ANY							=  0,
	REGISTRYTYPE_WINDOW						=  1,
	REGISTRYTYPE_OBJECT						=  2,
	REGISTRYTYPE_TRACK_EX					=  3,
	REGISTRYTYPE_SEQUENCE_EX			=  4,
	REGISTRYTYPE_KEY_EX						=  5,
	REGISTRYTYPE_TAG							=  6,
	REGISTRYTYPE_MATERIAL					=  7,
	REGISTRYTYPE_SHADER						=  8,
	REGISTRYTYPE_COFFEE_EXT				=  9,
	REGISTRYTYPE_SOUND						= 10,
	REGISTRYTYPE_LAYOUT						= 11,
	REGISTRYTYPE_BITMAPFILTER			= 12,
	REGISTRYTYPE_VIDEOPOST				= 13,
	REGISTRYTYPE_SCENEHOOK				= 14,
	REGISTRYTYPE_NODE							= 15,
	REGISTRYTYPE_DESCRIPTION			= 16,
	REGISTRYTYPE_LIBRARY					= 17,
	REGISTRYTYPE_CUSTOMDATATYPE		= 18,
	REGISTRYTYPE_RESOURCEDATATYPE	= 19,
	REGISTRYTYPE_SCENELOADER			= 20,
	REGISTRYTYPE_SCENESAVER				= 21,
	REGISTRYTYPE_SNHOOK						= 22,
	REGISTRYTYPE_CTRACK						= 23,
	REGISTRYTYPE_CSEQ							= 24,
	REGISTRYTYPE_CKEY							= 25,
	REGISTRYTYPE_PAINTER					= 26,
	REGISTRYTYPE_GV_VALUE					= 27,
	REGISTRYTYPE_GV_VALGROUP			= 28,
	REGISTRYTYPE_GV_OPGROUP				= 29,
	REGISTRYTYPE_GV_OPCLASS				= 30,
	REGISTRYTYPE_GV_DATA					= 31,
	REGISTRYTYPE_GADGETS					= 32,
	REGISTRYTYPE_PREFS						= 33
} ENUM_END_LIST(REGISTRYTYPE);
/// @}

/// @addtogroup MODELINGCOMMANDMODE
/// @ingroup group_enumeration
/// @{
enum MODELINGCOMMANDMODE
{
	MODELINGCOMMANDMODE_ALL								= 0,			///< All points/polygons.
	MODELINGCOMMANDMODE_POINTSELECTION		= 1,			///< Only the current point selection.
	MODELINGCOMMANDMODE_POLYGONSELECTION	= 2,			///< Only the current polygon selection.
	MODELINGCOMMANDMODE_EDGESELECTION			= 3				///< Only the current edge selection.
} ENUM_END_LIST(MODELINGCOMMANDMODE);
/// @}

/// @addtogroup MODELINGCOMMANDFLAGS
/// @ingroup group_enumeration
/// @{
enum MODELINGCOMMANDFLAGS
{
	MODELINGCOMMANDFLAGS_0					= 0,						///< None.
	MODELINGCOMMANDFLAGS_CREATEUNDO	= (1 << 0)			///< Creates undo and inserts newly created objects into ModelingCommandData::doc, instead of returning in ModelingCommandData::result.
} ENUM_END_FLAGS(MODELINGCOMMANDFLAGS);
/// @}

/// @addtogroup PLUGINTYPE
/// @ingroup group_enumeration
/// @{
enum PLUGINTYPE
{
	PLUGINTYPE_ANY								=  0,			///< Any type.

	PLUGINTYPE_SHADER							=  1,			///< 2D shader. (ShaderData)
	PLUGINTYPE_MATERIAL						=  2,			///< 3D shader. (MaterialData)
	PLUGINTYPE_COFFEEMESSAGE			=  3,			///< @COFFEE message.
	PLUGINTYPE_COMMAND						=  4,			///< Command. (CommandData)
	PLUGINTYPE_OBJECT							=  5,			///< Object. (ObjectData)
	PLUGINTYPE_TAG								=  6,			///< Tag. (TagData)
	PLUGINTYPE_BITMAPFILTER				=  7,			///< Bitmap filter. (BitmapLoaderData, BitmapSaverData)
	PLUGINTYPE_VIDEOPOST					=  8,			///< Videopost effect. (VideoPostData)
	PLUGINTYPE_TOOL								=  9,			///< Tool. (ToolData)
	PLUGINTYPE_SCENEHOOK					= 10,			///< Scene hook. (SceneHookData)
	PLUGINTYPE_NODE								= 11,			///< Node. (NodeData)
	PLUGINTYPE_LIBRARY						= 12,			///< Library. (C4DLibrary)
	PLUGINTYPE_BITMAPLOADER				= 13,			///< Bitmap loader. (BitmapLoaderData)
	PLUGINTYPE_BITMAPSAVER				= 14,			///< Bitmap saver. (BitmapSaverData)
	PLUGINTYPE_SCENELOADER				= 15,			///< Scene loader. (SceneLoaderData)
	PLUGINTYPE_SCENESAVER					= 16,			///< Scene saver. (SceneSaverData)
	PLUGINTYPE_COREMESSAGE				= 17,			///< Core message.
	PLUGINTYPE_CUSTOMGUI					= 18,			///< Custom GUI. (CustomGuiData)
	PLUGINTYPE_CUSTOMDATATYPE			= 19,			///< Custom datatype. (CustomDataTypeClass)
	PLUGINTYPE_RESOURCEDATATYPE		= 20,			///< Resource datatype.
	PLUGINTYPE_MANAGERINFORMATION	= 21,			///< Manager information.
	PLUGINTYPE_CTRACK							= 32,			///< Track. (CTrackData)
	PLUGINTYPE_FALLOFF						= 33,			///< Falloff. (FalloffData)
	PLUGINTYPE_VMAPTRANSFER				= 34,			///< Used by VAMP. @markPrivate
	PLUGINTYPE_PREFS							= 35,			///< Preference hook. (PrefsDialogObject)
	PLUGINTYPE_SNAP								= 36			///< Snap. (SnapData)
} ENUM_END_LIST(PLUGINTYPE);
/// @}

/// @addtogroup DRAWRESULT
/// @ingroup group_enumeration
/// @{
enum DRAWRESULT
{
	DRAWRESULT_ERROR	= 0,			///< There was an error while drawing.
	DRAWRESULT_OK			= 1,			///< Something was drawn.
	DRAWRESULT_SKIP		= 2				///< There was nothing to draw in this pass.
} ENUM_END_LIST(DRAWRESULT);
/// @}

/// @addtogroup DISPLAYMODE
/// @ingroup group_enumeration
/// @{
enum DISPLAYMODE
{
	DISPLAYMODE_UNKNOWN					= -1,			///< Unknown.
	DISPLAYMODE_GOURAUD					= 0,			///< Gouraud shading.
	DISPLAYMODE_QUICK						= 1,			///< Quick shading.
	DISPLAYMODE_WIRE						= 2,			///< Wireframe.
	DISPLAYMODE_ISOPARM					= 3,			///< Isoparm.
	DISPLAYMODE_SHADEDBOX				= 4,			///< Shaded box.
	DISPLAYMODE_BOX							= 5,			///< Box.
	DISPLAYMODE_SKELETON				= 6,			///< Skeleton.
	DISPLAYMODE_GOURAUDWIRE			= 7,			///< Gouraud wireframe.
	DISPLAYMODE_GOURAUDISOPARM	= 8,			///< Gouraud isoparm.
	DISPLAYMODE_QUICKWIRE				= 9,			///< Quick wireframe.
	DISPLAYMODE_QUICKISOPARM		= 10,			///< Quick isoparm.
	DISPLAYMODE_FLATWIRE				= 11,			///< Flat wireframe.
	DISPLAYMODE_FLATISOPARM			= 12,			///< Flat isoparm.
	DISPLAYMODE_FLATBOX					= 13,			///< Flat box.
	DISPLAYMODE_HIDDENWIRE			= 14,			///< Hidden line wireframe.
	DISPLAYMODE_HIDDENISOPARM		= 15,			///< Hidden line isoparm.
	DISPLAYMODE_HIDDENBOX				= 16,			///< Hidden line box.
	DISPLAYMODE_SHADEDBOXWIRE		= 17,			///< Shaded box wireframe.
	DISPLAYMODE_QUICKBOXWIRE		= 18,			///< Quick shaded box wireframe.
	DISPLAYMODE_QUICKBOX				= 19,			///< Quick shaded box.

	DISPLAYMODE_PRIVATE_ISOLINE	= 100,			///< @markPrivate
	DISPLAYMODE_PRIVATE_FLAT		= 1100,			///< @markPrivate
	DISPLAYMODE_PRIVATE_HIDDEN	= 1400			///< @markPrivate
} ENUM_END_LIST(DISPLAYMODE);
/// @}

/// @addtogroup DOCUMENTSETTINGS
/// @ingroup group_enumeration
/// @{
/// Container IDs for the document settings.\n
/// The valid IDs are listed in @em ddoc.h (see @em ddoc.res for the container definition).
/// @see BaseDocument::GetData BaseDocument::SetData BaseDocument::GetSettingsInstance
enum DOCUMENTSETTINGS
{
	DOCUMENTSETTINGS_GENERAL					= 0,			///< General settings.
	DOCUMENTSETTINGS_MODELING					= 1,			///< Modeler settings. (See @ref MDATA options.)
	DOCUMENTSETTINGS_DOCUMENT					= 2,			///< Document settings.
	DOCUMENTSETTINGS_ANIMATIONSYSTEM	= 7,			///< Timeline settings. @markPrivate
	DOCUMENTSETTINGS_TOOLS						= 8				///< Tools settings. (Unused)
} ENUM_END_LIST(DOCUMENTSETTINGS);
/// @}

/// @addtogroup SERIALINFO
/// @ingroup group_enumeration
/// @{
enum SERIALINFO
{
	SERIALINFO_CINEMA4D			= 0,			///< Serial for @C4D.
	SERIALINFO_MULTILICENSE	= 2				///< Serial for @C4D running in a license server environment.
} ENUM_END_LIST(SERIALINFO);
/// @}

/// @addtogroup VERSIONTYPE
/// @ingroup group_enumeration
/// @{
enum VERSIONTYPE
{
	VERSIONTYPE_PRIME									= 0,			///< @C4D Prime.
	VERSIONTYPE_BODYPAINT							= 1,			///< @BP3D.
	VERSIONTYPE_STUDIO								= 2,			///< @C4D Studio.
	VERSIONTYPE_VISUALIZE							= 3,			///< @C4D Visualize.
	VERSIONTYPE_BROADCAST							= 4,			///< @C4D Broadcast.
	VERSIONTYPE_BENCHMARK							= 5,			///< Cinebench.
	VERSIONTYPE_UPDATER								= 6,			///< Online updater.
	VERSIONTYPE_INSTALLER							= 7,			///< Installer.
	VERSIONTYPE_NET_CLIENT						= 8,			///< @C4D NET client.
	VERSIONTYPE_NET_SERVER_3					= 9,			///< @C4D NET server.
	VERSIONTYPE_NET_SERVER_UNLIMITED	= 10,			///< @C4D NET server.
	VERSIONTYPE_UNKNOWN								= 11,			///< Unknown.
	VERSIONTYPE_LICENSESERVER					= 12			///< @C4D License Server.
} ENUM_END_LIST(VERSIONTYPE);
/// @}

/// @addtogroup LAYERSETMODE
/// @ingroup group_enumeration
/// @{
enum LAYERSETMODE
{
	LAYERSETMODE_LAYERS,					///< Layers / layer Sets.
	LAYERSETMODE_LAYERMASKS,			///< Layer masks.
	LAYERSETMODE_ALPHAS,					///< Alpha channels.
	LAYERSETMODE_LAYERALPHA,			///< Layer alpha.
	LAYERSETMODE_DISABLED					///< Disabled.
} ENUM_END_LIST(LAYERSETMODE);
/// @}

/// @addtogroup SYSTEMINFO
/// @ingroup group_enumeration
/// @{
enum SYSTEMINFO
{
	SYSTEMINFO_0									= 0,						///< None.
	SYSTEMINFO_COMMANDLINE				= (1 << 1),			///< Application runs in command line mode.
	SYSTEMINFO_SAVABLEDEMO				= (1 << 3),			///< Savable demo version.
	SYSTEMINFO_SAVABLEDEMO_ACTIVE	= (1 << 4),			///< Activated savable demo version, @ref SYSTEMINFO_SAVABLEDEMO is still set.
	SYSTEMINFO_OPENGL							= (1 << 5),			///< OpenGL is activated and loaded correctly.
	SYSTEMINFO_STUDENT						= (1 << 6),			///< Activated student version, always set along with @ref SYSTEMINFO_SAVABLEDEMO.
	SYSTEMINFO_LITE								= (1 << 7),			///< Lite version, cannot load any plugins.
	SYSTEMINFO_LITE_ACTIVE				= (1 << 8),			///< Lite version is registered, @ref SYSTEMINFO_LITE is still set.
	SYSTEMINFO_CINEWARE						= (1 << 9),			///< CineWare - The Adobe AfterEffects connection.
	SYSTEMINFO_CINERENDER					= (1 << 10)			///< CineRender - The renderer used in Vectorworks, Archicad and Allplan.
} ENUM_END_FLAGS(SYSTEMINFO);
/// @}

#define ID_MT_SOURCECOUNTER	465001520			///< Int32 @markPrivate

/// Maximum number of global texture paths available.
#define MAX_GLOBAL_TEXTURE_PATHS 10

/// @addtogroup SELECTIONFILTERBIT
/// @ingroup group_enumeration
/// @{
enum SELECTIONFILTERBIT
{
	SELECTIONFILTERBIT_0					= 0,							///< None.
	SELECTIONFILTERBIT_NULL				= (1 << 0),				///< Null.
	SELECTIONFILTERBIT_POLYGON		= (1 << 1),				///< Polygon.
	SELECTIONFILTERBIT_SPLINE			= (1 << 2),				///< Spline.
	SELECTIONFILTERBIT_GENERATOR	= (1 << 3),				///< Generator.
	SELECTIONFILTERBIT_HYPERNURBS	= (1 << 4),				///< Subdivision Surface.
	SELECTIONFILTERBIT_DEFORMER		= (1 << 6),				///< Deformer.
	SELECTIONFILTERBIT_CAMERA			= (1 << 7),				///< Camera.
	SELECTIONFILTERBIT_LIGHT			= (1 << 8),				///< Light.
	SELECTIONFILTERBIT_SCENE			= (1 << 9),				///< Scene.
	SELECTIONFILTERBIT_PARTICLE		= (1 << 10),			///< Particle.
	SELECTIONFILTERBIT_OTHER			= (1 << 11),			///< Other.
	SELECTIONFILTERBIT_JOINT			= (1 << 25)				///< Joint.
} ENUM_END_FLAGS(SELECTIONFILTERBIT);
/// @}

/// @addtogroup OBJECTSTATE
/// @ingroup group_enumeration
/// @{
enum OBJECTSTATE
{
	OBJECTSTATE_EDITOR	= 0,			///< Editor visibility.
	OBJECTSTATE_RENDER	= 1,			///< Renderer visibility.
	OBJECTSTATE_DEFORM	= 2				///< Deform state.
} ENUM_END_LIST(OBJECTSTATE);
/// @}

/// @addtogroup DISPLAYFILTER
/// @ingroup group_enumeration
/// @{
/// @see BaseDraw::GetDisplayFilter
/// @note ::DISPLAYFILTER_NULL to ::DISPLAYFILTER_OTHER match @ref SELECTIONFILTERBIT.
enum DISPLAYFILTER
{
	DISPLAYFILTER_0										= 0,							///< None.
	DISPLAYFILTER_NULL								= (1 << 0),				///< Null.
	DISPLAYFILTER_POLYGON							= (1 << 1),				///< Polygon.
	DISPLAYFILTER_SPLINE							= (1 << 2),				///< Spline.
	DISPLAYFILTER_GENERATOR						= (1 << 3),				///< Generator.
	DISPLAYFILTER_HYPERNURBS					= (1 << 4),				///< Subdivision Surface.
	DISPLAYFILTER_UNUSED1							= (1 << 5),				///< Unused.
	DISPLAYFILTER_DEFORMER						= (1 << 6),				///< Deformer.
	DISPLAYFILTER_CAMERA							= (1 << 7),				///< Camera.
	DISPLAYFILTER_LIGHT								= (1 << 8),				///< Light.
	DISPLAYFILTER_SCENE								= (1 << 9),				///< Scene.
	DISPLAYFILTER_PARTICLE						= (1 << 10),			///< %Particle.
	DISPLAYFILTER_OTHER								= (1 << 11),			///< Other.
	DISPLAYFILTER_GRID								= (1 << 13),			///< Grid.
	DISPLAYFILTER_HORIZON							= (1 << 14),			///< Horizon.
	DISPLAYFILTER_WORLDAXIS						= (1 << 15),			///< World axis.
	DISPLAYFILTER_BOUNDS							= (1 << 16),			///< Bounding-box.
	DISPLAYFILTER_HUD									= (1 << 17),			///< HUD.
	DISPLAYFILTER_SDS									= (1 << 18),			///< HN mesh.
	DISPLAYFILTER_HIGHLIGHTING				= (1 << 19),			///< Highlight select.
	DISPLAYFILTER_MULTIAXIS						= (1 << 20),			///< Multi-select axes.
	DISPLAYFILTER_OBJECTHANDLES				= (1 << 21),			///< Highlight handles.
	DISPLAYFILTER_HANDLEBANDS					= (1 << 22),			///< Axis bands.
	DISPLAYFILTER_SDSCAGE							= (1 << 23),			///< HN cage.
	DISPLAYFILTER_NGONLINES						= (1 << 24),			///< N-gon lines.
	DISPLAYFILTER_JOINT								= (1 << 25),			///< Joint objects.
	DISPLAYFILTER_OBJECTHIGHLIGHTING	= (1 << 26),			///< @markPrivate
	DISPLAYFILTER_GUIDELINES					= (1 << 27),			///< Axis guidelines.
	DISPLAYFILTER_POI									= (1 << 28),			///< Navigation cross.
	DISPLAYFILTER_GRADIENT						= (1 << 29),			///< %Gradient.
	DISPLAYFILTER_BASEGRID						= (1 << 30)				///< Base grid.
} ENUM_END_FLAGS(DISPLAYFILTER);
/// @}

/// @addtogroup DISPLAYEDITSTATE
/// @ingroup group_enumeration
/// @{
/// @see BaseDraw::GetEditState
enum DISPLAYEDITSTATE
{
	DISPLAYEDITSTATE_0				= 0,						///< None.
	DISPLAYEDITSTATE_SDS			= (1 << 0),			///< SDS edit state.
	DISPLAYEDITSTATE_DEFORM		= (1 << 1),			///< Deformed edit state.

	DISPLAYEDITSTATE_DOCUMENT	= -1			///< Document edit state.
} ENUM_END_FLAGS(DISPLAYEDITSTATE);
/// @}

/// @addtogroup THREADTYPE
/// @ingroup group_enumeration
/// @{
enum THREADTYPE
{
	THREADTYPE_0							= 0,						///< None.
	THREADTYPE_EDITORREDRAW		= (1 << 0),			///< Editor redraw.
	THREADTYPE_RENDEREDITOR		= (1 << 1),			///< Editor render.
	THREADTYPE_RENDEREXTERNAL	= (1 << 2)			///< External render.
} ENUM_END_FLAGS(THREADTYPE);
/// @}

/// @addtogroup RENDERPROGRESSTYPE
/// @ingroup group_enumeration
/// @{
enum RENDERPROGRESSTYPE
{
	RENDERPROGRESSTYPE_BEFORERENDERING		= 0,			///< Before rendering.
	RENDERPROGRESSTYPE_DURINGRENDERING		= 1,			///< During rendering.
	RENDERPROGRESSTYPE_AFTERRENDERING			= 2,			///< After rendering.
	RENDERPROGRESSTYPE_GLOBALILLUMINATION	= 3,			///< GI prepass.
	RENDERPROGRESSTYPE_QUICK_PREVIEW			= 4				///< Quick Preview rendering. @since R17.048
} ENUM_END_LIST(RENDERPROGRESSTYPE);
/// @}

/// @addtogroup RDATA_SAVECALLBACK_CMD
/// @ingroup group_enumeration
/// @{
enum RDATA_SAVECALLBACK_CMD
{
	RDATA_SAVECALLBACK_CMD_OPEN		= 1,			///< Open call.
	RDATA_SAVECALLBACK_CMD_WRITE	= 2,			///< Write call.
	RDATA_SAVECALLBACK_CMD_CLOSE	= 3				///< Close call.
} ENUM_END_LIST(RDATA_SAVECALLBACK_CMD);
/// @}

/// @addtogroup VPGETINFO
/// @ingroup group_enumeration
/// @{
enum VPGETINFO
{
	VPGETINFO_XRESOLUTION	= 0,			///< X resolution.
	VPGETINFO_YRESOLUTION	= 1,			///< Y resolution.
	VPGETINFO_BITDEPTH		= 2,			///< Bit depth.
	VPGETINFO_CPP					= 3,			///< Colors per pixel.
	VPGETINFO_VISIBLE			= 4,			///< Visibility.
	VPGETINFO_LINEOFFSET	= 5				///< Offset of component in line.
} ENUM_END_LIST(VPGETINFO);
/// @}

/// @addtogroup DRAWOBJECT
/// @ingroup group_enumeration
/// @{
enum DRAWOBJECT
{
	DRAWOBJECT_0								= 0,							///< None.
	DRAWOBJECT_FORCELINES				= (1 << 0),				///< Force wireframe display, independent of view settings.
	DRAWOBJECT_NOBACKCULL				= (1 << 1),				///< Force no backface culling, independent of view settings.
	DRAWOBJECT_LOCALMATRIX			= (1 << 2),				///< Object drawn will be drawn relative to the currently processed object (used when called from the draw method in a base object).
	DRAWOBJECT_EDITMODE					= (1 << 3),				///< Object is drawn in edit-mode style.
	DRAWOBJECT_FORCEBASE				= (1 << 9),				///< The draw call is only executed for the base class, and thus not for the instanciated object, if passed to BaseDraw::DrawObject() and the object type is an instance of either @ref Opoint or @ref Opolygon.\n
																								///< This way, you can do a draw call without running into a recursion if you are in your from points/polygons derived object.
	DRAWOBJECT_FORCEPOINTS			= (1 << 10),			///< Force points display.
	DRAWOBJECT_NO_EOGL					= (1 << 11),			///< No Extended OpenGL.
	DRAWOBJECT_USE_OBJECT_COLOR	= (1 << 12),			///< Use the object's color.
	DRAWOBJECT_USE_CUSTOM_COLOR	= (1 << 13),			///< Use a custom color.
	DRAWOBJECT_XRAY_ON					= (1 << 14),			///< Enables X-Ray mode.
	DRAWOBJECT_XRAY_OFF					= (1 << 15),			///< Disables X-Ray mode.
	DRAWOBJECT_IMMEDIATELY			= (1 << 16),			///< Draws an object immediately. Usually all objects are collected in a Z-depth sorted list before drawing. This flag is used for objects which are immediately deleted after drawing.\n
																								/// @code
																								/// DRAWRESULT MyObject::Draw()
																								/// {
																								/// 	...
																								///
																								/// 	cube = BaseObject::Alloc(cube)
																								/// 	DrawObject(cube, DRAWOBJECT_IMMEDIATELY)
																								/// 	BaseObejct::Free(cube)
																								///
																								/// 	...
																								/// }
																								/// @endcode
	DRAWOBJECT_Z_OFFSET					= (1 << 17),			///< Do not change the Z offset during BaseDraww::DrawObject().
	DRAWOBJECT_PRIVATE_ANY			= (1 << 30)				///< @markPrivate
} ENUM_END_FLAGS(DRAWOBJECT);
/// @}

/// @addtogroup RENDERFLAGS
/// @ingroup group_enumeration
/// @{
enum RENDERFLAGS
{
	RENDERFLAGS_0											= 0,						///< None.
	RENDERFLAGS_EXTERNAL							= (1 << 0),			///< External render.
	RENDERFLAGS_NODOCUMENTCLONE				= (1 << 1),			///< Set to avoid an automatic clone of the scene sent to RenderDocument().
	RENDERFLAGS_SHOWERRORS						= (1 << 2),			///< Show error messages.
	RENDERFLAGS_PREVIEWRENDER					= (1 << 3),			///< Preview render.
	RENDERFLAGS_IRR										= (1 << 4),			///< Interactive region render.
	RENDERFLAGS_CREATE_PICTUREVIEWER	= (1 << 5),			///< %Render in a new Picture Viewer.
	RENDERFLAGS_OPEN_PICTUREVIEWER		= (1 << 6),			///< Open the Picture Viewer.
	RENDERFLAGS_KEEP_CONTEXT					= (1 << 7),			///< @markPrivate
	RENDERFLAGS_BATCHRENDER						= (1 << 8),			///< %Render in Batch %Render. @markPrivate
	RENDERFLAGS_NET										= (1 << 9),			///< Use NET System for rendering.
	RENDERFLAGS_DONTANIMATE						= (1 << 10)			///< Do not animate document before rendering. This should only be used in combination with @ref RENDERFLAGS_PREVIEWRENDER.@since R17.032
} ENUM_END_FLAGS(RENDERFLAGS);
/// @}

/// @addtogroup WRITEMODE
/// @ingroup group_enumeration
/// @{
enum WRITEMODE
{
	WRITEMODE_STANDARD							= 0,		///< Standard.
	WRITEMODE_ASSEMBLE_MOVIE				= 1,		///< Assemble movie.
	WRITEMODE_ASSEMBLE_SINGLEIMAGE	= 2			///< Assemble single image.
} ENUM_END_LIST(WRITEMODE);
/// @}

/// @addtogroup NETRENDERFLAGS
/// @ingroup group_enumeration
/// @{
enum NETRENDERFLAGS
{
	NETRENDERFLAGS_0															= 0,						///< None.
	NETRENDERFLAGS_OPEN_PICTUREVIEWER							= (1 << 0),			///< Open Picture Viewer.
	NETRENDERFLAGS_SHOWERRORS											= (1 << 2),			///< Show errors.
	NETRENDERFLAGS_DELETEAFTERRENDERING						= (1 << 3),			///< Delete after rendering.
	NETRENDERFLAGS_NOPEERTOPEERASSETDISTRIBUTION	= (1 << 4),			///< No peer-to-peer asset distribution. Automatically set by local preferences.
	NETRENDERFLAGS_NOREQUESTONDEMAND							= (1 << 5),			///< No request on demand. Automatically set by local preferences.
	NETRENDERFLAGS_EXCLUDECLIENTONLOADINGERROR		= (1 << 6),			///< Exclude client on rendering error. Automatically set by local preferences.
	NETRENDERFLAGS_SAVERESULTSINREPOSITORY				= (1 << 7),			///< Save results in repository.
	NETRENDERFLAGS_ASSEMBLEB3DFILESIMMEDIATLEY		= (1 << 8),			///< Assemble @BP3D files immediately.
	NETRENDERFLAGS_NOWRITETEST										= (1 << 9),			///< No write test for @BP3D files.
	NETRENDERFLAGS_HANDLEWARNINGASERROR						= (1 << 10),		///< Handle warnings as errors.
	NETRENDERFLAGS_KEEPB3DFILESAFTERASSEMBLING		= (1 << 11)			///< Keep the @BP3D files on assembling.
} ENUM_END_FLAGS(NETRENDERFLAGS);
/// @}

/// @addtogroup CHECKISRUNNING
/// @ingroup group_enumeration
/// @{
enum CHECKISRUNNING
{
	CHECKISRUNNING_ANIMATIONRUNNING				= 0,			///< Animation running.
	CHECKISRUNNING_VIEWDRAWING						= 1,			///< View drawing.
	CHECKISRUNNING_EDITORRENDERING				= 2,			///< Editor rendering.
	CHECKISRUNNING_EXTERNALRENDERING			= 3,			///< External rendering.
	CHECKISRUNNING_PAINTERUPDATING				= 4,			///< Painter updating.
	CHECKISRUNNING_MATERIALPREVIEWRUNNING	= 5,			///< %Material preview running.
	CHECKISRUNNING_EVENTSYSTEM						= 6,			///< Event System.
	CHECKISRUNNING_BAKING									= 7				///< Baking.
} ENUM_END_LIST(CHECKISRUNNING);
/// @}

/// @addtogroup BAKE_TEX_ERR
/// @ingroup group_enumeration
/// @{
enum BAKE_TEX_ERR
{
	BAKE_TEX_ERR_NONE								= 0,				///< None.
	BAKE_TEX_ERR_NO_DOC							= 3000,			///< No document.
	BAKE_TEX_ERR_NO_MEM							= 3001,			///< No more memory available.
	BAKE_TEX_ERR_NO_RENDER_DOC			= 3002,			///< No render document.
	BAKE_TEX_ERR_NO_TEXTURE_TAG			= 3003,			///< @c textag is @formatConstant{nullptr} or not in @c doc.
	BAKE_TEX_ERR_NO_OBJECT					= 3004,			///< One of the tags is not assigned to an object or to another object.
	BAKE_TEX_ERR_NO_UVW_TAG					= 3005,			///< UVW tag is missing.
	BAKE_TEX_ERR_TEXTURE_MISSING		= 3006,			///< No texture.
	BAKE_TEX_ERR_WRONG_BITMAP				= 3007,			///< MultipassBitmap was used, but it has the wrong type or wrong resolution.
	BAKE_TEX_ERR_USERBREAK					= 3008,			///< %User break.
	BAKE_TEX_ERR_NO_OPTIMAL_MAPPING	= 3009,			///< Optimal mapping failed.
	BAKE_TEX_ERR_NO_SOURCE_UVW_TAG	= 3010			///< UVW tag for the source object is missing.
} ENUM_END_LIST(BAKE_TEX_ERR);
/// @}

/// @addtogroup GL_MESSAGE
/// @ingroup group_enumeration
/// @{
enum GL_MESSAGE
{
	GL_MESSAGE_OK								= 1,
	GL_MESSAGE_ERROR						= 0,
	GL_MESSAGE_FORCE_EMULATION	= 2
} ENUM_END_LIST(GL_MESSAGE);
/// @}

/// @addtogroup VIEWPORT_PICK_FLAGS
/// @ingroup group_enumeration
/// @{
enum VIEWPORT_PICK_FLAGS
{
	VIEWPORT_PICK_FLAGS_0													= 0,						///< None.
	VIEWPORT_PICK_FLAGS_ALLOW_OGL									= (1 << 0),			///< Allow OpenGL.
	VIEWPORT_PICK_FLAGS_DONT_STOP_THREADS					= (1 << 1),			///< Do not stop threads.
	VIEWPORT_PICK_FLAGS_USE_SEL_FILTER						= (1 << 2),			///< Use selection filter.
	VIEWPORT_PICK_FLAGS_OGL_ONLY_TOPMOST					= (1 << 3),			///< Picks only topmost object. Use this only when the object pointer is not needed. Only works with OpenGL.
	VIEWPORT_PICK_FLAGS_OGL_ONLY_VISIBLE					= (1 << 4),			///< Picks only visible. Only has an effect when calling ViewportSelect::PickObject() thats take ViewportPixel as argument . Only works with OpenGL.
	VIEWPORT_PICK_FLAGS_OGL_IGNORE_Z							= (1 << 5),			///< Picks ignore Z position. Set this to only check if an object (and which) was hit, not its Z position. Only works with OpenGL.
	VIEWPORT_PICK_FLAGS_OGL_ONLY_TOPMOST_WITH_OBJ	= (1 << 6)			///< Picks only topmost object but returns the topmost object with its Z position. Only works with OpenGL.
} ENUM_END_FLAGS(VIEWPORT_PICK_FLAGS);
/// @}

/// @addtogroup SHADERPOPUP
/// @ingroup group_enumeration
/// @{
#define SHADERPOPUP_SETSHADER					99989			///< Set a shader . @formatParam{param} points to a BaseShader. (param = @c reinterpret_cast<Int32>(shader))
#define SHADERPOPUP_SETFILENAME				99990			///< Set a bitmap. @formatParam{param} points to a Filename. (param = @c reinterpret_cast<Int32>(&fn))
#define SHADERPOPUP_LOADIMAGE					99991			///< Open file dialog and set user result.
#define SHADERPOPUP_EDITPARAMS				99999			///< Edit shaders in the Attribute Manager.
#define SHADERPOPUP_RELOADIMAGE				99998			///< Reload the image. (Only works for a single bitmap shader.)
#define SHADERPOPUP_EDITIMAGE					99997			///< Edit image in external application. (Only works for a single bitmap shader.)
#define SHADERPOPUP_LOCATEIMAGE				99996			///< Show image in finder/explorer. (Only works for a single bitmap shader.) @since R17.032
#define SHADERPOPUP_COPYCHANNEL				99995			///< Copy the shader to the copy buffer. (Only works for a single shader.)
#define SHADERPOPUP_PASTECHANNEL			99994			///< Paste the copy buffer. (Works for multiple shaders.)
#define SHADERPOPUP_CREATENEWTEXTURE	99993			///< Create a new @BP3D texture. (Only works for a single shader.)
#define SHADERPOPUP_CLEARSHADER				99992			///< Clear the shaders.
/// @}

/// @addtogroup DEFAULTFILENAME_SHADER
/// @ingroup group_enumeration
/// @{
#define DEFAULTFILENAME_SHADER_SURFACES	1001			///< Surfaces.
#define DEFAULTFILENAME_SHADER_EFFECTS	1002			///< Effects.
#define DEFAULTFILENAME_SHADER_VOLUME		1003			///< Volume.
/// @}

/// @addtogroup BACKGROUNDHANDLERCOMMAND
/// @ingroup group_enumeration
/// @{
enum BACKGROUNDHANDLERCOMMAND
{
	BACKGROUNDHANDLERCOMMAND_ISRUNNING	= 100,			///< Return @formatConstant{true} if the handler is currently running, otherwise @formatConstant{false}.
	BACKGROUNDHANDLERCOMMAND_STOP				= 101,			///< Stop the current activity. Return @formatConstant{true} when the activity has stopped.
	BACKGROUNDHANDLERCOMMAND_START			= 102,			///< Check if there is something to do. If not, return false. In case there is something to do, directly start this job and return @formatConstant{true}.\n
																									///< There is also the possibility to do a small job synchronously and return false (pretend as if nothing was started).
																									///< @note	As the background handler is processed in the main application thread this means that if you process something unthreaded, the complete application will be blocked.\n
																									///<				For example some code that takes @em 10 seconds means that the user will not be able to click on any button or stop anything during that time.\n
																									///<				That is why only extremely short tasks must be directly processed, otherwise start an asynchronous thread.
	BACKGROUNDHANDLERCOMMAND_REMOVE			= 103				///< The handler is being removed. Return @formatConstant{true}.
} ENUM_END_LIST(BACKGROUNDHANDLERCOMMAND);
/// @}

/// @addtogroup BACKGROUNDHANDLER_PRIORITY
/// @ingroup group_enumeration
/// @{
#define BACKGROUNDHANDLER_PRIORITY_RENDERACTIVEMATERIAL			5000			///< Priority for "Render active material".
#define BACKGROUNDHANDLER_PRIORITY_REDRAWVIEW								4000			///< Priority for "Redraw view".
#define BACKGROUNDHANDLER_PRIORITY_RENDERINACTIVEMATERIALS	3000			///< Priority for "Render inactive materials".
#define BACKGROUNDHANDLER_PRIORITY_RENDEREXTERNAL						-1000			///< Priority for "Render external".
#define BACKGROUNDHANDLER_PRIORITY_REDRAWANTS								-2000			///< Priority for "Redraw ants".
/// @}

/// @addtogroup BACKGROUNDHANDLERFLAGS
/// @ingroup group_enumeration
/// @{
enum BACKGROUNDHANDLERFLAGS
{
	BACKGROUNDHANDLERFLAGS_0									= 0,						///< None.
	BACKGROUNDHANDLERFLAGS_VIEWREDRAW					= (1 << 0),			///< View redraw.
	BACKGROUNDHANDLERFLAGS_EDITORRENDDER			= (1 << 1),			///< Editor render.
	BACKGROUNDHANDLERFLAGS_MATERIALPREVIEW		= (1 << 2),			///< %Material preview.
	BACKGROUNDHANDLERFLAGS_RENDEREXTERNAL			= (1 << 3),			///< %Render external.
	BACKGROUNDHANDLERFLAGS_PRIVATE_VIEWREDRAW	= (1 << 4),			///< @markPrivate

	BACKGROUNDHANDLERFLAGS_SHUTDOWN						= -1						///< Shutdown.
} ENUM_END_FLAGS(BACKGROUNDHANDLERFLAGS);
/// @}

/// @C4D background handler type class.
#define BACKGROUNDHANDLER_TYPECLASS_C4D	1000

/// @addtogroup IDENTIFYFILE
/// @ingroup group_enumeration
/// @{
enum IDENTIFYFILE
{
	IDENTIFYFILE_0							= 0,						///< None.
	IDENTIFYFILE_SCENE					= (1 << 0),			///< Scene file.
	IDENTIFYFILE_IMAGE					= (1 << 1),			///< Image file.
	IDENTIFYFILE_MOVIE					= (1 << 2),			///< Movie file.
	IDENTIFYFILE_SKIPQUICKTIME	= (1 << 3),			///< Skip files that require QuickTime.
	IDENTIFYFILE_SCRIPT					= (1 << 4),			///< Script file.
	IDENTIFYFILE_COFFEE					= (1 << 5),			///< @COFFEE file.
	IDENTIFYFILE_SOUND					= (1 << 6),			///< Sound file.
	IDENTIFYFILE_LAYOUT					= (1 << 7),			///< Layout file.
	IDENTIFYFILE_PYTHON					= (1 << 8)			///< Python file.
} ENUM_END_FLAGS(IDENTIFYFILE);
/// @}

/// @addtogroup CALCHARDSHADOW
/// @ingroup group_enumeration
/// @{
enum CALCHARDSHADOW
{
	CALCHARDSHADOW_0									= 0,							///< None.
	CALCHARDSHADOW_TRANSPARENCY				= (1 << 0),				///< Transparencies/alphas for in-between objects will be evaluated.
	CALCHARDSHADOW_SPECIALGISHADOW		= (1 << 29),			///< @markPrivate
	CALCHARDSHADOW_SPECIALSELFSHADOW	= (1 << 30)				///< @markPrivate
} ENUM_END_FLAGS(CALCHARDSHADOW);
/// @}

/// @addtogroup ILLUMINATEFLAGS
/// @ingroup group_enumeration
/// @{
enum ILLUMINATEFLAGS
{
	ILLUMINATEFLAGS_0																	= 0,							///< None.
	ILLUMINATEFLAGS_SHADOW														= (1 << 0),				///< Full shadow calculations.
	ILLUMINATEFLAGS_NOENVIRONMENT											= (1 << 1),				///< Shadow calculations are enabled but no environment shading will be calculated.
	ILLUMINATEFLAGS_DISABLESHADOWMAP_CORRECTION				= (1 << 20),			///< Shadow maps evaluate the normal at a surface point, to avoid the problem of self-shadowing (that is otherwise inherent due to the way the algorithm works).\n
																																			///< If a free point is sampled in space (where no surface is) this correction has to be disabled though, otherwise wrong results will be returned.
	ILLUMINATEFLAGS_DISABLESHADOWCASTERMP_CORRECTION	= (1 << 21),			///< @markPrivate
	ILLUMINATEFLAGS_LIGHTDIRNORMALS										= (1 << 22),			///< @markPrivate
	ILLUMINATEFLAGS_NODISTANCEFALLOFF									= (1 << 23),			///< Do not take distance falloff into account.
	ILLUMINATEFLAGS_NOGRAIN														= (1 << 24),			///< Do not take grain into account.
	ILLUMINATEFLAGS_BACKLIGHT													= (1 << 25)				///< Take backlight into account.
} ENUM_END_FLAGS(ILLUMINATEFLAGS);
/// @}

/// @addtogroup RAYBIT
/// @ingroup group_enumeration
/// @{
enum RAYBIT
{
	RAYBIT_0									= 0,							///< None.
	RAYBIT_REFLECTION					= (1 << 0),				///< Ray chain contains a reflection ray.
	RAYBIT_TRANSPARENCY				= (1 << 1),				///< Ray chain contains a transparency ray (note: refractions are not contained).
	RAYBIT_REFRACTION					= (1 << 2),				///< Ray chain contains a refraction ray.
	RAYBIT_CUSTOM							= (1 << 3),				///< Ray chain contains a custom ray.

	RAYBIT_CURR_REFLECTION		= (1 << 4),				///< Current ray is a reflection ray.
	RAYBIT_CURR_TRANSPARENCY	= (1 << 5),				///< Current ray is a transparency ray.
	RAYBIT_CURR_REFRACTION		= (1 << 6),				///< Current ray is a refraction ray.
	RAYBIT_CURR_CUSTOM				= (1 << 7),				///< Current ray is a custom ray.

	RAYBIT_VOLUMETRICLIGHT		= (1 << 8),				///< Current ray is used to calculate a volumetric light.
	RAYBIT_ALLOWVLMIX					= (1 << 9),				///< Custom mixing of visible light sources allowed for this ray; bit must be deleted by shader if used.

	RAYBIT_GI									= (1 << 10),			///< Current ray is a Global Illumination ray.
	RAYBIT_BLURRY							= (1 << 11),			///< Current ray is a blurry ray.
	RAYBIT_SSS								= (1 << 12),			///< Current ray is a subsurface ray.

	RAYBIT_AO									= (1 << 13),			///< Current ray is an Ambient Occlusion ray.
	RAYBIT_COMPOSITING				= (1 << 14)				///< Current ray is a compositing ray.
} ENUM_END_FLAGS(RAYBIT);
/// @}

/// @addtogroup VOLUMEINFO
/// @ingroup group_enumeration
/// @{
enum VOLUMEINFO
{
	VOLUMEINFO_0									= 0,							///< None.
	VOLUMEINFO_REFLECTION					= 0x00000002,			///< Shader calculates reflections
	VOLUMEINFO_TRANSPARENCY				= 0x00000004,			///< Shader calculates transparency
	VOLUMEINFO_ALPHA							= 0x00000008,			///< Shader calculates alpha
	VOLUMEINFO_CHANGENORMAL				= 0x00002000,			///< Shader calculates bump mapping
	VOLUMEINFO_DISPLACEMENT				= 0x00004000,			///< Shader calculates displacement mapping
	VOLUMEINFO_ENVREQUIRED				= 0x00100000,			///< Shader needs environment reflection data
	VOLUMEINFO_DUDVREQUIRED				= 0x00200000,			///< Shader needs du/dv bump mapping data
	VOLUMEINFO_MIPSAT							= 0x02000000,			///< Shader requires MIP/SAT data
	VOLUMEINFO_VOLUMETRIC					= 0x20000000,			///< Shader is a volumetric shader
	VOLUMEINFO_TRANSFORM					= 0x00000010,			///< Shader needs back-transformed data.
	VOLUMEINFO_EVALUATEPROJECTION	= 0x04000000,			///< Shader requires texture tag projections.
	VOLUMEINFO_PRIVATE_GLOW				= 0x10000000,			///< Shader calculates glow. @markPrivate.
	VOLUMEINFO_INITCALCULATION		= 0x80000000,			///< Shader needs @c InitCalculation() call.
	VOLUMEINFO_FINAL_ALPHA				= 0x40000000			///< Shader writes final alpha value
} ENUM_END_FLAGS(VOLUMEINFO);
/// @}

/// @addtogroup VIDEOPOSTINFO
/// @ingroup group_enumeration
/// @{
enum VIDEOPOSTINFO
{
	VIDEOPOSTINFO_0												= 0,							///< None.
	VIDEOPOSTINFO_STOREFRAGMENTS					= (1 << 0),				///< The videopost needs fragment information for whole image at @ref VIDEOPOSTCALL_INNER/@ref VIDEOPOSTCALL_RENDER.
	VIDEOPOSTINFO_EXECUTELINE							= (1 << 4),				///< The videopost uses VideoPostData::ExecuteLine.
	VIDEOPOSTINFO_EXECUTEPIXEL						= (1 << 5),				///< The videopost uses VideoPostData::ExecutePixel.
	VIDEOPOSTINFO_REQUEST_MOTIONMATRIX		= (1 << 6),				///< The videopost needs the motion matrix.
	VIDEOPOSTINFO_REQUEST_MOTIONGEOMETRY	= (1 << 7),				///< The videopost needs the motion geometry.
	VIDEOPOSTINFO_CALCVOLUMETRIC					= (1 << 8),				///< If set, VideoPostData::CalcVolumetric() is called for each ray.
	VIDEOPOSTINFO_CALCSHADOW							= (1 << 9),				///< If set, VideoPostData::CalcShadow() is called for each ray.
	VIDEOPOSTINFO_CUSTOMLENS							= (1 << 10),			///< The videopost will provide custom lens rays with VideoPostData::CreateRay.
	VIDEOPOSTINFO_GLOBALILLUMINATION			= (1 << 11),			///< If set, VideoPostData::ComputeDiffuseGI is called for each ray.
	VIDEOPOSTINFO_CAUSTICS								= (1 << 12),			///< If set VideoPostData::ComputeDiffuseCaustic() and VideoPostData::ComputeVolumeCaustic() are called for each ray.
	VIDEOPOSTINFO_CUSTOMLENS_EXTENDED			= (1 << 13),			///< The videopost will provide custom extended lens rays with VideoPostData::CreateExtendedRay.
	VIDEOPOSTINFO_NETFRAME								= (1 << 14),			///< The videopost is a NET frame hook.
	VIDEOPOSTINFO_NETRUNONSERVER					= (1 << 15),			///< The videopost can be run on the NET server.
	VIDEOPOSTINFO_NETCREATEBUFFER					= (1 << 16),			///< The videopost creates a buffer for the NET Client in VideoPostData::NetCreateBuffer.
	VIDEOPOSTINFO_NETCREATEBUFFER_MULTI		= (1 << 17),			///< The videopost creates multiple buffers for the NET Client in VideoPostData::NetCreateBuffer (called consecutively). @since R16.038
	VIDEOPOSTINFO_REQUEST_MOTIONFULL		 	= (1 << 18), 			///< The videopost requires complete motion blur information. @since R17.032
} ENUM_END_FLAGS(VIDEOPOSTINFO);
/// @}

/// @addtogroup SHADERINFO
/// @ingroup group_enumeration
/// @{
/// Information flags for BaseShader::GetRenderInfo.
enum SHADERINFO
{
	SHADERINFO_0									= 0,							///< None.
	SHADERINFO_TRANSFORM					= 0x00000004,			///< Channel needs back-transformed data. (Required for BaseVolumeData::back_p.)
	SHADERINFO_BUMP_SUPPORT				= 0x00000010,			///< Channel shader supports the new bump system. This is strongly recommended for all shaders except simple 2D (UV) samplers.
	SHADERINFO_ALPHA_SUPPORT			= 0x00000020,			///< Channel shader supports alpha output.
	SHADERINFO_REFLECTIONS				= 0x00000040,			///< Channel shader computes reflections.
	SHADERINFO_DUDVREQUIRED				= 0x00000080,			///< Channel shader needs du/dv bump mapping data. See BaseVolumeData::ddu and BaseVolumeData::ddv.
	SHADERINFO_DYNAMICSUBSHADERS	= 0x00000100			///< Channel shader has a dynamic list of sub-shaders in its description.
} ENUM_END_FLAGS(SHADERINFO);
/// @}

/// @addtogroup SAMPLEBUMP
/// @ingroup group_enumeration
/// @{
/// Flags for sampling bump mapping in the rendering API.
enum SAMPLEBUMP
{
	SAMPLEBUMP_0					= 0,						///< None.
	SAMPLEBUMP_MIPFALLOFF	= (1 << 0)			///< Additional bump change over distance is considered.
};
/// @}

/// @addtogroup INITCALCULATION
/// @ingroup group_enumeration
/// @{
/// %Material calculation types for the rendering API.
/// @see BaseMaterial::InitCalculation MaterialData::InitCalculation
enum INITCALCULATION
{
	INITCALCULATION_SURFACE				= 0,			///< Called during rendering for surface calculation.
	INITCALCULATION_TRANSPARENCY	= 1,			///< Called during rendering for shadow rays computation.
	INITCALCULATION_DISPLACEMENT	= 3				///< Called before rendering for displace calculation.
} ENUM_END_LIST(INITCALCULATION);
/// @}

#define ID_SCRIPTFOLDER	1026688			///< @markPrivate

#define ID_COFFEESCRIPT	1001085			///< ID for a BaseList2D object that holds a @COFFEE script. To load @COFFEE scripts use:
																		///< @code
																		/// BaseList2D* op = (BaseList2D*)AllocListNode(ID_COFFEESCRIPT);
																		/// if (op && ReadHyperFile(nullptr, op, fn, 'scrp', nullptr)==FILEERROR_NONE)
																		/// {
																		/// 	BaseBitmap* ptr = nullptr;
																		/// 	op->Message(MSG_SCRIPT_RETRIEVEBITMAP, &ptr);
																		///
																		/// 	String script = op->GetDataInstance()->GetString(COFFEESCRIPT_TEXT);
																		/// }
																		///
																		/// ...
																		///
																		/// blDelete(op);
																		/// @endcode
																		///< To access scripts loaded by @C4D use GetScriptHead().\n
																		///< The container for the @COFFEE script nodes contains the following settings: @enumerateEnum{COFFEESCRIPT}
																		///< The node responds to the following messages: @enumerateEnum{MSG_SCRIPT}

#define ID_PYTHONSCRIPT	1026256			///< ID for a BaseList2D object that holds a Python script. To load Python scripts use:
																		///< @code
																		/// BaseList2D* op = (BaseList2D*)AllocListNode(ID_PYTHONSCRIPT);
																		/// if (op && ReadHyperFile(nullptr, op, fn, 'scrp', nullptr)==FILEERROR_NONE)
																		/// {
																		/// 	BaseBitmap* ptr = nullptr;
																		/// 	op->Message(MSG_SCRIPT_RETRIEVEBITMAP, &ptr);
																		///
																		/// 	String script = op->GetDataInstance()->GetString(PYTHONSCRIPT_TEXT);
																		/// }
																		///
																		/// ...
																		///
																		/// blDelete(op);
																		/// @endcode
																		///< To access scripts loaded by @C4D use GetScriptHead().\n
																		///< The container for the Python script node contains the following settings: @enumerateEnum{PYTHONSCRIPT}
																		///< The node responds to the following messages: @enumerateEnum{MSG_SCRIPT}

/// @addtogroup COFFEESCRIPT
/// @ingroup group_containerid
/// @{
#define COFFEESCRIPT_TEXT					1000			///< String Script.
#define COFFEESCRIPT_SHOWINMENU		1002			///< ::Bool Show in menu.
#define COFFEESCRIPT_ADDEVENT			1003			///< ::Bool Add event.
#define COFFEESCRIPT_SCRIPTENABLE	1006			///< ::Bool Enable script.

#define COFFEESCRIPT_CONTAINER 65536			///< BaseContainer The ID offset for data that is stored per language.\n
																					///< This container does not need to be available. If it is not present for a language, then the English version ("US") is used.\n
																					///< This lets calculate the offset for a given name (e.g. "JP"):
																					/// @code
																					/// static Int32 LanguageToID(const String &str)
																					/// {
																					/// 	return Int32(str[0])*256+Int32(str[1]);
																					/// }
																					///
																					/// BaseContainer* lc = bc->GetContainerInstance(COFFEESCRIPT_CONTAINER+LanguageToID("JP"));
																					/// if (!lc)
																					/// 	return;
																					///
																					/// 	...
																					/// @endcode

#define COFFEESCRIPT_SCRIPTNAME	1			///< String Script name.
#define COFFEESCRIPT_SCRIPTHELP	2			///< String Script help string.
/// @}

/// @addtogroup MSG_SCRIPT
/// @ingroup group_enumeration
/// @{
#define MSG_SCRIPT_EXECUTE				1001184			///< Execute the script. (No arguments.)
#define MSG_SCRIPT_RETRIEVEBITMAP	1001185			///< Retrieves the script bitmap. Pass a pointer to the script's bitmap:
																							/// @code
																							/// BaseBitmap* ptr = nullptr;
																							/// op->Message(MSG_SCRIPT_RETRIEVEBITMAP, &ptr);
																							/// @endcode
/// @}

/// @addtogroup PYTHONSCRIPT
/// @ingroup group_containerid
/// @{
#define PYTHONSCRIPT_TEXT					1000			///< String Script.
#define PYTHONSCRIPT_SHOWINMENU		1002			///< ::Bool Show in menu.
#define PYTHONSCRIPT_ADDEVENT			1003			///< ::Bool Add event.
#define PYTHONSCRIPT_SCRIPTENABLE	1006			///< ::Bool Enable script.

#define PYTHONSCRIPT_CONTAINER 65536			///< BaseContainer The ID offset for data that is stored per language.\n
																					///< This container does not need to be available. If it is not present for a language, then the English version ("US") is used.\n
																					///< This lets calculate the offset for a given name (e.g. "JP"):
																					/// @code
																					/// static Int32 LanguageToID(const String &str)
																					/// {
																					/// 	return Int32(str[0])*256+Int32(str[1]);
																					/// }
																					///
																					/// BaseContainer* lc = bc->GetContainerInstance(PYTHONSCRIPT_CONTAINER+LanguageToID("JP"));
																					/// if (!lc)
																					/// 	return;
																					///
																					/// ...
																					/// @endcode

#define PYTHONSCRIPT_SCRIPTNAME	1			///< String Script name.
#define PYTHONSCRIPT_SCRIPTHELP	2			///< String Script help string.
/// @}

/// @addtogroup BASEDRAW
/// @ingroup group_enumeration
/// @{
#define BASEDRAW_DRAWPORTTYPE				1888			///< Drawport type: @enumerateEnum{DRAWPORT_TYPE}
#define BASEDRAW_IS_SHADOWPASS			1889			///< Is shadow pass.
#define BASEDRAW_IS_RENDERASEDITOR	1890			///< Is render as editor pass.
#define BASEDRAW_IS_OGL_PREPASS			1891			///< Is OpenGL prepass.
#define BASEDRAW_IS_PICK_OBJECT			1892			///< Is object picking pass.
/// @}

/// @addtogroup MULTIPASSCHANNEL
/// @ingroup group_enumeration
/// @{
enum MULTIPASSCHANNEL
{
	MULTIPASSCHANNEL_0								= 0,						///< None.
	MULTIPASSCHANNEL_IMAGELAYER				= (1 << 0),			///< Image layer.
	MULTIPASSCHANNEL_MATERIALCHANNEL	= (1 << 1)			///< %Material channel.
} ENUM_END_LIST(MULTIPASSCHANNEL);
/// @}

/// @addtogroup DLG_TYPE
/// @ingroup group_enumeration
/// @{
enum DLG_TYPE
{
	DLG_TYPE_MODAL = 10,											///< Modal dialog.
	DLG_TYPE_MODAL_RESIZEABLE,								///< Resizable modal dialog.

	DLG_TYPE_ASYNC = 20,											///< Non-modal (asynchronous) dialog.
	DLG_TYPE_ASYNC_POPUP_RESIZEABLE,					///< Non-modal (asynchronous) dialog. Resizable popup dialog style (no menu bar).
	DLG_TYPE_ASYNC_POPUPEDIT,									///< Non-modal (asynchronous) dialog. Popup dialog style (no menu bar, no window frame).

	DLG_TYPE_ASYNC_FULLSCREEN_WORK = 30,			///< Non-modal (asynchronous) dialog. Fullscreen over desktop area.
	DLG_TYPE_ASYNC_FULLSCREEN_MONITOR,				///< Non-modal (asynchronous) dialog. Fullscreen over the whole monitor area.

	DLG_TYPE_
} ENUM_END_LIST(DLG_TYPE);
/// @}

/// @addtogroup MULTIMSG_ROUTE
/// @ingroup group_enumeration
/// @{
enum MULTIMSG_ROUTE
{
	MULTIMSG_ROUTE_NONE				= 0,			///< None.
	MULTIMSG_ROUTE_UP					= 1,			///< Send to parents.
	MULTIMSG_ROUTE_ROOT				= 2,			///< Send to root object.
	MULTIMSG_ROUTE_DOWN				= 3,			///< Send to children.
	MULTIMSG_ROUTE_BROADCAST	= 4				///< Broadcast the message, i.e. distribute it to all branches given by GeListNode::GetBranchInfo.
} ENUM_END_LIST(MULTIMSG_ROUTE);
/// @}

/// @addtogroup VPGETFRAGMENTS
/// @ingroup group_enumeration
/// @{
enum VPGETFRAGMENTS
{
	VPGETFRAGMENTS_0		= 0,						///< None.
	VPGETFRAGMENTS_Z_P	= (1 << 0),			///< Get VPFragment::z and VPFragment::p.
	VPGETFRAGMENTS_N		= (1 << 1)			///< Get VPFragment::n.
} ENUM_END_FLAGS(VPGETFRAGMENTS);
/// @}

#define MSG_GICSEX						1000969
#define MSG_GINEW							1021096
#define ID_OLDCAUSTICS				1000970			///< ID of the old Caustics videopost effect.
#define VPglobalillumination	1021096			///< Global Illumination video post ID.
#define VPGIShadingChain			1026950			///< @markPrivate
#define VPAOShadingChain			1029427			///< @markPrivate
#define VPbirender						1028868			///< Videopost birender.
#define VPPhLensDistortion		1031709			///< Videopost Lens Distortion. @since R17.032

/// @addtogroup SIGNALMODE
/// @ingroup group_enumeration
/// @{
enum SIGNALMODE
{
	SIGNALMODE_DEFAULT	= 0,			///< Default mode.
	SIGNALMODE_RESERVED	= 1				///< Reserved.
} ENUM_END_LIST(SIGNALMODE);
/// @}

/// @addtogroup QUALIFIER
/// @ingroup group_enumeration
/// @{
enum QUALIFIER
{
	QUALIFIER_0					= 0,						///< None.
	QUALIFIER_SHIFT			= (1 << 0),			///< @em SHIFT key.
	QUALIFIER_CTRL			= (1 << 1),			///< @em CTRL key.
	QUALIFIER_MOUSEHIT	= (1 << 10)			///< Indication in BaseObject::DetectHandle that the user pressed the mouse (BaseObject::DetectHandle is also called for cursor information, when hovering over a handle).\n
																			///< For instance if @ref QUALIFIER_MOUSEHIT and @ref QUALIFIER_CTRL are set, BaseObject::DetectHandle could create a new element.
} ENUM_END_FLAGS(QUALIFIER);
/// @}

/// @addtogroup CODEEDITOR
/// @ingroup group_containerid
/// @{
#define CODEEDITOR_SETMODE					'setm'			///< @ref SCRIPTMODE Sets the script mode: @enumerateEnum{SCRIPTMODE}
#define CODEEDITOR_GETSTRING				'gets'			///< String Returns the script string that the editor should show.
#define CODEEDITOR_SETSTRING				'sets'			///< The script was changed. Stores the script string.
#define CODEEDITOR_COMPILE					'comp'			///< BaseContainer The script was compiled: @enumerateEnum{CODEEDITOR_GETERROR}
/// @addtogroup CODEEDITOR_GETERROR
/// @ingroup group_containerid
/// @{
#define CODEEDITOR_GETERROR_RES			'resr'			///< ::Bool Compilation result. @formatConstant{true} if the compilation was successful, otherwise @formatConstant{false}.
#define CODEEDITOR_GETERROR_STRING	'ress'			///< String Error message.
#define CODEEDITOR_GETERROR_LINE		'resl'			///< ::Int32 Error line.
#define CODEEDITOR_GETERROR_POS			'resp'			///< ::Int32 Error position.
/// @}
#define CODEEDITOR_EXECUTE					'exec'			///< ::Bool Returns if the script was executed successfully.
#define CODEEDITOR_DISABLEUNDO			'dsud'			///< ::Bool Disable undo.
#define CODEEDITOR_STOREUNDO				'stun'			///< ::Bool Store undo.
#define CODEEDITOR_RESTOREUNDO			'reun'			///< ::Bool Restore undo.
#define CODEEDITOR_GETID						'reid'			///< ::Int32 Get ID.
/// @}

/// @markPrivate
#define BASECONTAINER_TEMPORARY	440000180

/// @addtogroup DIALOG
/// @ingroup group_enumeration
/// @{
enum
{
	DIALOG_PIN = 1,											///< ::Int32 flags
	DIALOG_CHECKBOX,										///< ::Int32 id, ::Int32 flags, String *name
	DIALOG_STATICTEXT,									///< ::Int32 id, ::Int32 flags, String *name, ::Int32 borderstyle
	DIALOG_BUTTON,											///< ::Int32 id, ::Int32 flags, String *name
	DIALOG_ARROWBUTTON,									///< ::Int32 id, ::Int32 flags, ::Int32 arrowtype
	DIALOG_EDITTEXT,										///< ::Int32 id, ::Int32 flags
	DIALOG_EDITNUMBER,									///< ::Int32 id, ::Int32 flags
	DIALOG_EDITNUMBERUD,								///< ::Int32 id, ::Int32 flags
	DIALOG_EDITSLIDER,									///< ::Int32 id, ::Int32 flags
	DIALOG_SLIDER,											///< ::Int32 id, ::Int32 flags
	DIALOG_COLORFIELD,									///< ::Int32 id, ::Int32 flags
	DIALOG_COLORCHOOSER,								///< ::Int32 id, ::Int32 flags
	DIALOG_USERAREA,										///< ::Int32 id, ::Int32 flags
	DIALOG_RADIOGROUP,									///< ::Int32 id, ::Int32 flags
	DIALOG_COMBOBOX,										///< ::Int32 id, ::Int32 flags
	DIALOG_POPUPBUTTON,									///< ::Int32 id, ::Int32 flags
	DIALOG_CHILD,												///< ::Int32 id, ::Int32 subid, String *child);
	DIALOG_FREECHILDREN,								///< ::Int32 id
	DIALOG_DLGGROUP,										///< ::Int32 flags
	DIALOG_SETTITLE,										///< String *name
	DIALOG_GROUPSPACE,									///< ::Int32 spacex, ::Int32 spacey
	DIALOG_GROUPBORDER,									///< @ref BORDER borderstyle
	DIALOG_GROUPBORDERSIZE,							///< ::Int32 left, ::Int32 top, ::Int32 right, ::Int32 bottom
	DIALOG_SETIDS,											///< ::Int32 left, ::Int32 top, ::Int32 right, ::Int32 bottom
	DIALOG_LAYOUTCHANGED,								///< Relayout dialog
	DIALOG_ACTIVATE,										///< Activate gadget
	DIALOG_ADDSUBMENU,									///< Add submenu, String *text
	DIALOG_ENDSUBMENU,									///< Add submenu, String *text
	DIALOG_ADDMENUCMD,									///< Add menu text, String *text, ::Int32 cmdid
	DIALOG_FLUSHMENU,										///< Delete all menu entries
	DIALOG_INIT,												///< Create new layout
	DIALOG_CHECKNUMBERS,								///< Range check of all dialog elements
	DELME_DIALOG_SETGROUP,							///< Set group as insert group
	DIALOG_FLUSHGROUP,									///< Flush all elements of this group and set insert point to this group
	DIALOG_SETMENU,											///< Set and display menu in manager
	DIALOG_SCREEN2LOCALX,								///< Screen2Local coordinates
	DIALOG_SCREEN2LOCALY,								///< Screen2Local coordinates
	DIALOG_ADDMENUSTR,									///< Add menu text, String *text, ::Int32 id
	DIALOG_RADIOBUTTON,									///< ::Int32 id, ::Int32 flags, String *name
	DIALOG_ADDMENUSEP,									///< Add menu separator
	DIALOG_SEPARATOR,										///< Add separator
	DIALOG_MULTILINEEDITTEXT,						///< Add multi-line edit field
	DIALOG_INITMENUSTR,									///< Enable/disable/check/uncheck menu strings
	DIALOG_RADIOTEXT,										///< ::Int32 id, ::Int32 flags, String *name
	DIALOG_MENURESOURCE,								///< @markPrivate for painter
	DIALOG_LISTVIEW,										///< ::Int32 id, ::Int32 flags
	DIALOG_SUBDIALOG,										///< ::Int32 id, ::Int32 flags
	DIALOG_CHECKCLOSE,									///< CheckClose message for dialog
	DIALOG_GETTRISTATE,									///< Get the TriState flag of the specified gadget
	DIALOG_SDK,													///< ::Int32 id, ::Int32 flags, String *name
	DIALOG_SCROLLGROUP,									///< Create scroll group
	DIALOG_ISOPEN,											///< Returns @formatConstant{true} if the dialog is open
	DIALOG_REMOVEGADGET,								///< Removes an element from the layout
	DIALOG_MENUGROUPBEGIN,							///< Menu group begin
	DIALOG_NOMENUBAR,										///< Removes the menubar
	DIALOG_SAVEWEIGHTS,									///< Store the weights of a group
	DIALOG_LOADWEIGHTS,									///< Restore the weights of a group
	DIALOG_EDITSHORTCUT,								///< Edit field to enter shortcuts
	DIALOG_ISVISIBLE,										///< Returns @formatConstant{true} if the dialog is visible (e.g. @formatConstant{false} if tabbed behind)
	DIALOG_HIDEELEMENT,									///< Hides the element
	DIALOG_SETDEFAULTCOLOR,							///< Set the mapcolor for a color to another value e.g. @ref COLOR_BG = @em (1,1,1)
	DIALOG_COMBOBUTTON,									///< ComboButton
	DIALOG_PRIVATE_NOSTOPEDITORTHREADS,	///< @markPrivate No parameters
	DIALOG_ISACTIVE,										///< returns if the gadget has the focus

	DIALOG_
};
/// @}

/// @addtogroup EDITTEXT
/// @ingroup group_enumeration
/// @{
/// @see	GeDialog::AddEditText\n
///				GeDialog::SetString(const GadgetPtr& id, const String& text, Int32 tristate = 0, Int32 flags = 0)\n
///				GeDialog::SetString(const GadgetPtr& id, const BaseContainer* bc, Int32 bcid, Int32 flags = 0)\n
///				GeDialog::SetString(const GadgetPtr& id, const TriState<String>& tri, Int32 flags = 0)
#define EDITTEXT_PASSWORD	(1 << 0)			///< Password field.
#define EDITTEXT_HELPTEXT	(1 << 1)			///< Sets the help text for an edit field. This text appears if the edit field is empty.
/// @}

/// @addtogroup LV
/// @ingroup group_enumeration
/// @{
enum
{
	LV_GETLINECOUNT							= 1,			///< Request the number of lines of the listview.
	LV_GETCOLUMNCOUNT						= 2,			///< Request the number of columns of the listview.
	LV_GETLINEHEIGHT						= 3,			///< Ask for the height of the specific line.
	LV_GETCOLUMNWIDTH						= 4,			///< Ask for the width of the specific column in line.
	LV_GETCOLUMTYPE							= 5,			///< Ask for the type of the specific column in line.

	LV_COLUMN_TEXT							= C4D_FOUR_BYTE(0, 't', 'x', 't'),			///< Text.
	LV_COLUMN_EDITTEXT					= C4D_FOUR_BYTE(0, 'e', 'd', 't'),			///< Edit text.
	LV_COLUMN_BMP								= C4D_FOUR_BYTE(0, 'b', 'm', 'p'),			///< Bitmap.
	LV_COLUMN_CHECKBOX					= C4D_FOUR_BYTE(0, 'c', 'h', 'k'),			///< Checkbox.
	LV_COLUMN_BUTTON						= C4D_FOUR_BYTE(0, 'b', 't', 'n'),			///< Button.
	LV_COLUMN_USERDRAW					= C4D_FOUR_BYTE(0, 'u', 's', 'r'),			///< %User draw.
	LV_COLUMN_COLORVIEW					= C4D_FOUR_BYTE(0, 'c', 'l', 'v'),			///< Color view.

	LV_GETCOLUMDATA							= 6,				///< Ask for the data of the column in line.
	LV_GETLINESELECTED					= 7,				///< Ask if line is selected.
	LV_GETCOLSPACE							= 8,				///< Ask for space in pixels between 2 columns.
	LV_GETLINESPACE							= 9,				///< Ask for space in pixels between 2 lines.
	LV_GETFIXEDLAYOUT						= 10,				///< Ask for fixed layout.
	LV_DESTROYLISTVIEW					= 11,				///< Destroy listview and all data.
	LV_INITCACHE								= 12,				///< @markInternal.
	LV_NOAUTOCOLUMN							= 13,				///< Ask for fast layout: if @formatConstant{false}, eachline is asked for the width, if @formatConstant{true}, only the first line is asked for the column width; huge speedup.

	LV_LMOUSEDOWN								= 50,				///< Mouse down at line, column.
	LV_ACTION										= 51,				///< Gadget command, col, @c data1 = msg.
	LV_USERDRAW									= 52,				///< %User draw.
	LV_REDRAW										= 53,				///< Redraw the listview (super message).
	LV_DATACHANGED							= 54,				///< Layout data has changed.
	LV_SHOWLINE									= 55,				///< Scroll line into the visible area.
	LV_DRAGRECEIVE							= 56,				///< Drag receive.
	LV_RMOUSEDOWN								= 57,				///< Mouse down at line, column.

	LV_SIMPLE_SELECTIONCHANGED	= 100,			///< Simple listview: selection changed.
	LV_SIMPLE_CHECKBOXCHANGED		= 101,			///< Simple listview: checkbox changed.
	LV_SIMPLE_FOCUSITEM					= 102,			///< Simple listview: set focus to item.
	LV_SIMPLE_BUTTONCLICK				= 103,			///< Simple listview: button click.
	LV_SIMPLE_ITEM_ID						= 1,				///< Item ID.
	LV_SIMPLE_COL_ID						= 2,				///< Column ID.
	LV_SIMPLE_DATA							= 3,				///< Data.
	LV_SIMPLE_DOUBLECLICK				= 104,			///< Simple listview: double-click.
	LV_SIMPLE_FOCUSITEM_NC			= 105,			///< Simple listview: focus item, but no change.
	LV_SIMPLE_RMOUSE						= 106,			///< Simple listview: right mouse click.
	LV_SIMPLE_USERDRAW					= 107,			///< Simple listview: user draw.
	LV_PYTHON_CLEANUP						= 108,			///< Cleanup of Python references.

	// Result types
	LV_RES_INT		= 'long',																///< Result int.
	LV_RES_BITMAP	= C4D_FOUR_BYTE(0, 'b', 'm', 'p'),			///< Result bitmap.
	LV_RES_STRING	= 'strg',																///< Result string.
	LV_RES_VECTOR	= C4D_FOUR_BYTE(0, 'v', 'e', 'c'),			///< Result vector.
	LV_RES_NIL		= C4D_FOUR_BYTE(0, 'n', 'i', 'l'),			///< Result nil.

	LV__
};
/// @}

#ifndef C4D_GL_VARS_DEFINED
enum GlVertexBufferSubBufferType { VBArrayBuffer = 0, VBElementArrayBuffer16 = 1, VBElementArrayBuffer32 = 2, VBTextureBuffer = 3 };
enum GlVertexBufferAccessFlags { VBReadWrite = 0, VBReadOnly = 1, VBWriteOnly = 2 };

	#if defined MAXON_TARGET_WINDOWS
typedef UINT C4DGLuint;
typedef INT C4DGLint;
	#elif defined MAXON_TARGET_OSX
typedef unsigned int C4DGLuint;
typedef int C4DGLint;
	#elif defined MAXON_TARGET_LINUX
typedef UINT C4DGLuint;
typedef INT C4DGLint;
	#endif

typedef Int GlProgramParameter;
	#define C4D_GL_VARS_DEFINED
#endif

#ifndef _C4D_GL_H_
enum GlProgramType { VertexProgram = 1, FragmentProgram = 2, CompiledProgram = 3, GeometryProgram = 4, TessControlProgram = 5, TessEvalProgram = 6 };
enum GlUniformParamType { UniformFloat1						= 0, UniformFloat2 = 1, UniformFloat3 = 2, UniformFloat4 = 3,
													UniformInt1							= 4, UniformInt2 = 5, UniformInt3 = 6, UniformInt4 = 7,
													UniformUint1						= 8, UniformUint2 = 9, UniforUint3 = 10, UniformUint4 = 11,
													UniformFloatMatrix2			= 12, UniformFloatMatrix3 = 13, UniformFloatMatrix4 = 14,
													UniformTexture1D				= 15, UniformTexture2D = 16, UniformTexture3D = 17, UniformTextureCube = 18,
													UniformTexture1Di				= 19, UniformTexture2Di = 20, UniformTexture3Di = 21, UniformTextureCubei = 22,
													UniformTexture1Du				= 23, UniformTexture2Du = 24, UniformTexture3Du = 25, UniformTextureCubeu = 26,
													UniformTexture1DArray		= 27, UniformTexture2DArray = 28,
													UniformTexture1DArrayi	= 29, UniformTexture2DArrayi = 30,
													UniformTexture1DArrayu	= 31, UniformTexture2DArrayu = 32, UniformTextureBuffer = 33, UniformTextureBufferi = 34 };
#endif

typedef UChar PIX;

/// @addtogroup NOTIFY_EVENT
/// @ingroup group_enumeration
/// @{
/// @markPrivate
enum NOTIFY_EVENT
{
	NOTIFY_EVENT_NONE					= -1,
	NOTIFY_EVENT_ALL					= 10,
	NOTIFY_EVENT_ANY					= 11,

	NOTIFY_EVENT_PRE_DEFORM		= 100,
	NOTIFY_EVENT_POST_DEFORM	= 101,
	NOTIFY_EVENT_UNDO					= 102,
	NOTIFY_EVENT_MESSAGE			= 103,
	NOTIFY_EVENT_FREE					= 104,

	NOTIFY_EVENT_COPY					= 107,
	NOTIFY_EVENT_CACHE				= 108,
	NOTIFY_EVENT_REMOVE				= 109,
	NOTIFY_EVENT_CLONE				= 110,
	NOTIFY_EVENT_INSERT				= 111,
	NOTIFY_EVENT_SELECTIONBIT	= 112,
	NOTIFY_EVENT_HIGHLIGHTBIT	= 113,

	NOTIFY_EVENT_SETNAME			= 200,

	NOTIFY_EVENT_0						= 0
} ENUM_END_LIST(NOTIFY_EVENT);
/// @}

/// @addtogroup NOTIFY_EVENT_FLAG
/// @ingroup group_enumeration
/// @{
/// @markPrivate
enum NOTIFY_EVENT_FLAG
{
	NOTIFY_EVENT_FLAG_REMOVED					= (1 << 0),

	NOTIFY_EVENT_FLAG_COPY_UNDO				= (1 << 10),
	NOTIFY_EVENT_FLAG_COPY_CACHE			= (1 << 11),
	NOTIFY_EVENT_FLAG_COPY_DUPLICATE	= (1 << 12),
	NOTIFY_EVENT_FLAG_ONCE						= (1 << 13),
	NOTIFY_EVENT_FLAG_COPY						= ((1 << 10) | (1 << 11) | (1 << 12)),

	NOTIFY_EVENT_FLAG_0								= 0
} ENUM_END_FLAGS(NOTIFY_EVENT_FLAG);
/// @}

/// @addtogroup DESCIDSTATE
/// @ingroup group_enumeration
/// @{
enum DESCIDSTATE
{
	DESCIDSTATE_0								= 0,					///< None.
	DESCIDSTATE_LOCKED					= 1 << 0,			///< Description element is locked.
	DESCIDSTATE_HIDDEN					= 1 << 1,			///< Description element is hidden.
	DESCIDSTATE_OVERRIDE				= 1 << 2,			///< Description is overridden. @since R17.032
	DESCIDSTATE_FORBIDOVERRIDE	= 1 << 3			///< Description cannot be overridden. @since R17.032
} ENUM_END_FLAGS(DESCIDSTATE);
/// @}

/// @addtogroup BASEDRAW_HOOK_MESSAGE
/// @ingroup group_enumeration
/// @{
enum BASEDRAW_HOOK_MESSAGE
{
	BASEDRAW_MESSAGE_ADAPTVIEW				= 1,			///< The user clicked on "Adapt View" menu.
	BASEDRAW_MESSAGE_SET_SCENE_CAMERA	= 2,			///< The user changed the scene camera. The corresponding data is BDSetSceneCameraMsg.
	BASEDRAW_MESSAGE_DELETEBASEDRAW		= 3				///< The base draw is deleted.
} ENUM_END_LIST(BASEDRAW_HOOK_MESSAGE);
/// @}

/// @addtogroup CINEMAINFO
/// @ingroup group_enumeration
/// @{
enum CINEMAINFO
{
	CINEMAINFO_TABLETT				= 4,			///< Tablet.
	CINEMAINFO_OPENGL					= 7,			///< OpenGL.
	CINEMAINFO_TABLETT_HIRES	= 8,			///< High resolution tablet.
	CINEMAINFO_FORBID_GUI			= 9,			///< Forbid GUI.
	CINEMAINFO_FORBID_HWOGL		= 10,			///< Forbid Hardware OpenGL.
	CINEMAINFO_LISTEN					= 11,			///< Listen.
	CINEMAINFO_WATCH_PID			= 12,			///< Watch process ID.
	CINEMAINFO_SETFOREGROUND	= 13			///< Set foreground.
} ENUM_END_FLAGS(CINEMAINFO);
/// @}

/// @addtogroup PROTOCOL
/// @ingroup group_enumeration
/// @{
enum PROTOCOL
{
	PROTOCOL_ZERO	= 0,				///< None.
	PROTOCOL_IPV4	= 1000,			///< IPv4.
	PROTOCOL_IPV6							///< IPv6.
} ENUM_END_LIST(PROTOCOL);
/// @}


/// @addtogroup RESOLVERESULT
/// @ingroup group_enumeration
/// @{
enum RESOLVERESULT
{
	RESOLVERESULT_OK				= 0,			///< Ok.
	RESOLVERESULT_UNKNOWN		= 1,			///< Unknown error while resolving address.
} ENUM_END_LIST(RESOLVERESULT);
/// @}

/// @addtogroup SERVERJOBLIST
/// @ingroup group_enumeration
/// @{
enum SERVERJOBLIST
{
	SERVERJOBLIST_INACTIVE = 1000,			///<
	SERVERJOBLIST_ACTIVE,								///<
	SERVERJOBLIST_DOWNLOAD,							///<
	SERVERJOBLIST_ALL										///<
} ENUM_END_LIST(SERVERJOBLIST);
/// @}

/// @addtogroup EDITION
/// @ingroup group_enumeration
/// @{
enum EDITION
{
	EDITION_C4D				= (1 << 0),									///< @C4D
	EDITION_NETCLIENT	= (1 << 1),									///< NET client.
	EDITION_NETSERVER	= (1 << 2),									///< NET server.
	EDITION_NET				= (1 << 1) | (1 << 2),			///< NET.
} ENUM_END_FLAGS(EDITION);
/// @}

/// @addtogroup JOBCOMMAND
/// @ingroup group_enumeration
/// @{
enum JOBCOMMAND
{
	JOBCOMMAND_NONE = 1000,				///< Do nothing.
	JOBCOMMAND_FETCHJOB,					///< Fetch job.
	JOBCOMMAND_ALLOCATESPACE,			///< Allocate space.
	JOBCOMMAND_DOWNLOAD,					///< Download.
	JOBCOMMAND_RENDER,						///< %Render.
	JOBCOMMAND_DELETE,						///< Delete.
	JOBCOMMAND_STOPANDDELETE,			///< Stop and delete.
	JOBCOMMAND_ASSEMBLE,					///< Assemble.
	JOBCOMMAND_END								///< End.
} ENUM_END_LIST(JOBCOMMAND);
/// @}

/// @addtogroup RENDERTARGET
/// @ingroup group_containerid
/// @{
enum RENDERTARGET
{
	RENDERTARGET_ALL = 1000,	///< Use all machines.
	RENDERTARGET_SPECIFIED,		///< C4DUuid.
	RENDERTARGET_MINMAX				///< Minimum/maximum. <i>1000</i>:min <i>1001</i>:max
} ENUM_END_LIST(RENDERTARGET);
/// @}

/// @addtogroup JOBSTATE
/// @ingroup group_enumeration
/// @{
enum JOBSTATE
{
	JOBSTATE_IDLE = 1000,								///< Idle.

	JOBSTATE_PREPARING_RUNNING,					///< Preparing running. Preparing only for server in @link ::THREADMODE_ASYNC async@endlink mode for NetRenderService::StartRendering.
	JOBSTATE_PREPARING_FAILED,					///< Preparing failed.
	JOBSTATE_PREPARING_OK,							///< Preparing ok.

	JOBSTATE_RENDER_RUNNING,						///< %Render running.
	EX_JOBSTATE_RENDER_PAUSED,					///< %Render paused. Currently not used
	JOBSTATE_RENDER_OK,									///< %Render ok.
	JOBSTATE_RENDER_FAILED,							///< %Render failed.

	JOBSTATE_ALLOCATESPACE_RUNNING,			///< Allocate space running.
	JOBSTATE_ALLOCATESPACE_OK,					///< Allocate space ok.
	JOBSTATE_ALLOCATESPACE_FAILED,			///< Allocated space failed.

	JOBSTATE_DOWNLOAD_RUNNING,					///< Download running.
	JOBSTATE_DOWNLOAD_OK,								///< Download ok.
	JOBSTATE_DOWNLOAD_FAILED,						///< Download failed.

	JOBSTATE_ASSEMBLE_RUNNING,					///< Assemble running.
	JOBSTATE_ASSEMBLE_OK,								///< Assemble ok.
	JOBSTATE_ASSEMBLE_FAILED,						///< Assemble failed.

	JOBSTATE_STOPPED,										///< Stopped.
	JOBSTATE_QUEUED,										///< Queued.
	JOBSTATE_PENDING,										///< non-native state which is only available in the server when no machine is involved in a running job
	JOBSTATE_QUEUED_WAITING,						///< Queued waiting
	JOBSTATE_ASSEMBLE_PENDING						///< Allocate space running.
} ENUM_END_LIST(JOBSTATE);
/// @}

/// @addtogroup ZEROCONFMACHINESTATE
/// @ingroup group_enumeration
/// @{
enum ZEROCONFMACHINESTATE
{
	ZEROCONFMACHINESTATE_ONLINE		= 1,			///< Online.
	ZEROCONFMACHINESTATE_OFFLINE	= 2,			///< Offline.
	ZEROCONFMACHINESTATE_REMOVED	= 3,			///< Removed.
	ZEROCONFMACHINESTATE_UPDATE		= 4,			///< Update.
} ENUM_END_LIST(ZEROCONFMACHINESTATE);
/// @}

/// @addtogroup ZEROCONFACTION
/// @ingroup group_enumeration
/// @{
enum ZEROCONFACTION
{
	ZEROCONFACTION_0				= 0,						///< None.
	ZEROCONFACTION_RESOLVE	= (1 << 0),			///< Resolve.
	ZEROCONFACTION_MONITOR	= (1 << 1)			///< Monitor.
} ENUM_END_FLAGS(ZEROCONFACTION);
/// @}

/// @addtogroup ZEROCONFERROR
/// @ingroup group_enumeration
/// @{
enum ZEROCONFERROR
{
	ZEROCONFERROR_NOERROR										= 0,					///< No error.
	ZEROCONFERROR_UNKNOWN										= -65537,			///< Unknown. @c 0xFFFEFFFF
	ZEROCONFERROR_NOSUCHNAME								= -65538,			///< No such name.
	ZEROCONFERROR_NOMEMORY									= -65539,			///< No memory.
	ZEROCONFERROR_BADPARAM									= -65540,			///< Bad parameter.
	ZEROCONFERROR_BADREFERENCE							= -65541,			///< Bad reference.
	ZEROCONFERROR_BADSTATE									= -65542,			///< Bad state.
	ZEROCONFERROR_BADFLAGS									= -65543,			///< Bad flags.
	ZEROCONFERROR_UNSUPPORTED								= -65544,			///< Unsupported.
	ZEROCONFERROR_NOTINITIALIZED						= -65545,			///< Not initialized.
	ZEROCONFERROR_ALREADYREGISTERED					= -65547,			///< Already registered.
	ZEROCONFERROR_NAMECONFLICT							= -65548,			///< Name conflict.
	ZEROCONFERROR_INVALID										= -65549,			///< Invalid.
	ZEROCONFERROR_FIREWALL									= -65550,			///< Firewall.
	ZEROCONFERROR_INCOMPATIBLE							= -65551,			///< Client Library incompatible with daemon.
	ZEROCONFERROR_BADINTERFACEINDEX					= -65552,			///< Bad interface index.
	ZEROCONFERROR_REFUSED										= -65553,			///< Refused.
	ZEROCONFERROR_NOSUCHRECORD							= -65554,			///< No such record.
	ZEROCONFERROR_NOAUTH										= -65555,			///< No authentication.
	ZEROCONFERROR_NOSUCHKEY									= -65556,			///< No such key.
	ZEROCONFERROR_NATTRAVERSAL							= -65557,			///< NAT traversal.
	ZEROCONFERROR_DOUBLENAT									= -65558,			///< Double NAT.
	ZEROCONFERROR_BADTIME										= -65559,			///< Bad time. Codes up to here existed in Tiger.
	ZEROCONFERROR_BADSIG										= -65560,			///< Bad SIG.
	ZEROCONFERROR_BADKEY										= -65561,			///< Bad key.
	ZEROCONFERROR_TRANSIENT									= -65562,			///< Transient.
	ZEROCONFERROR_SERVICENOTRUNNING					= -65563,			///< Background daemon not running.
	ZEROCONFERROR_NATPORTMAPPINGUNSUPPORTED	= -65564,			///< NAT does not support NAT_PMP or UPNP.
	ZEROCONFERROR_NATPORTMAPPINGDISABLED		= -65565,			///< NAT supports NAT-PMP or UPNP but it is disabled by the administrator.
	ZEROCONFERROR_NOROUTER									= -65566,			///< No router currently configured (probably no network connectivity).
	ZEROCONFERROR_POLLINGMODE								= -65567			///< Polling mode.
} ENUM_END_LIST(ZEROCONFERROR);
/// @}

/// @addtogroup RENDERSETTING_STATICTAB
/// @ingroup group_enumeration
/// @{
#define RENDERSETTING_STATICTAB_OUTPUT				1			///< %Render settings Output tab.
#define RENDERSETTING_STATICTAB_SAVE					2			///< %Render settings Save tab.
#define RENDERSETTING_STATICTAB_MULTIPASS			3			///< %Render settings Multi-Pass tab.
#define RENDERSETTING_STATICTAB_ANTIALIASING	4			///< %Render settings Anti-Aliasing tab.
#define RENDERSETTING_STATICTAB_OPTIONS				5			///< %Render settings Options tab.
#define RENDERSETTING_STATICTAB_STEREO				6			///< %Render settings Stereoscopic tab.
#define RENDERSETTING_STATICTAB_NET						7			///< %Render settings NET tab.
#define RENDERSETTING_STATICTAB_OVERRIDEMAT		8			///< %Render settings Global Material Override tab. @since R17.032
/// @}

#endif // GE_PREPASS_H__
