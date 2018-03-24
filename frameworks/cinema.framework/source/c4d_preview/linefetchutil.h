/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef LINEFETCHUTIL_H__
#define LINEFETCHUTIL_H__

#include "c4d_general.h"
#include "c4d_memory.h"
#include "c4d_gui.h"

#include "x4d_filter.h"
#include "c4d_bitmapfilter.h"

typedef	struct ROW_ROOT* ROW_REF;

#define	ROW_FETCH_UPDATE_VIEW	0x0001	// update view when destination tiles are detached

extern ROW_REF new_row_fetcher(BM_REF bm, Int32 x1, Int32 x2, Int32 tile_flags, Int32 tile_mode, BM_TILE* static_tile, Int32 update_flags = ROW_FETCH_UPDATE_VIEW);
extern void	delete_row_fetcher(ROW_REF rr, Bool discard_all);
extern UChar* rf_get_bitmap_row(ROW_REF rr, Int32 y);
extern void	rf_free_bitmap_row(ROW_REF rr, Int32 y);

extern ROW_REF new_column_fetcher(BM_REF bm, Int32 y1, Int32 y2, Int32 tile_flags, Int32 tile_mode, BM_TILE* static_tile, Int32 update_flags = ROW_FETCH_UPDATE_VIEW);
extern void	delete_column_fetcher(ROW_REF rr, Bool discard_all);
extern UChar* rf_get_bitmap_column(ROW_REF rr, Int32 x, Int32* pixel_offset);
extern void	rf_free_bitmap_column(ROW_REF rr, Int32 x);

void premultiply_alpha(UChar* buf, Int32 width, Int32 no_components, Int32 pixel_offset);
void premultiply_alpha(UInt16* buf, Int32 width, Int32 no_components, Int32 pixel_offset);
void premultiply_alpha(Float32* buf, Int32 width, Int32 no_components, Int32 pixel_offset);
void separate_alpha(UChar* buf, Int32 width, Int32 no_components, Int32 pixel_offset);
void separate_alpha(UInt16* buf, Int32 width, Int32 no_components, Int32 pixel_offset);
void separate_alpha(Float32* buf, Int32 width, Int32 no_components, Int32 pixel_offset, Float32 clip = 1e-6f);

#endif // LINEFETCHUTIL_H__
