/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef FILTER_PREFS_H__
#define FILTER_PREFS_H__

enum
{
	BF_PREFS_TEST	= 1000000,
	BF_PREFS_GLOBAL

};

enum
{
	BF_PREFS_SRC_PREVIEW,			// (Int32) false: no source preview true: show source preview
	BF_PREFS_DST_PREVIEW,
	BF_PREFS_PREVIEW_WIDTH,		// (Int32) width of a preview object in pixels
	BF_PREFS_PREVIEW_HEIGHT,	// (Int32) height of a preview object in pixels
	BF_PREFS_PREVIEW_PERCENT,	// (Int32) current preview scale (it's an index, not the current scale)

	BF_PREFS_TILE_FLAGS,			// (Int32) false: border pixels are repeated true: texture is wrapped
	BF_PREFS_DOCUMENT_PREVIEW	// (Int32) true: update the document window
};

enum
{
	BF_PREFS_SRC_PREVIEW_DFLT			 = false,	// (Int32) false: no source preview true: show source preview
	BF_PREFS_DST_PREVIEW_DFLT			 = true,
	BF_PREFS_PREVIEW_WIDTH_DFLT		 = 256,		// (Int32) width of a preview object in pixels
	BF_PREFS_PREVIEW_HEIGHT_DFLT	 = 192,		// (Int32) height of a preview object in pixels
	BF_PREFS_PREVIEW_PERCENT_DFLT	 = 4,			// (Int32) current preview scale (it's an index, not the current scale)
	BF_PREFS_TILE_FLAGS_DFLT			 = false,	// (Int32) false: border pixels are repeated true: texture is wrapped
	BF_PREFS_DOCUMENT_PREVIEW_DFLT = true		// (Int32) true: update the document window
};

Bool BfpGetRealTimeFlag(void);
Bool BfpGetDocumentPreviewFlag(void);
void BfpSetDocumentPreviewFlag(Bool document_preview);
Bool BfpGetTextureModeFlag(void);
void BfpSetTextureModeFlag(Bool texture_mode);


#endif // FILTER_PREFS_H__
