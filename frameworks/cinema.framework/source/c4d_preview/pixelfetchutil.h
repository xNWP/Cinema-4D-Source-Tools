/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef PIXELFETCHUTIL_H__
#define PIXELFETCHUTIL_H__

#include "x4d_filter.h"

typedef	struct PIXEL_ROOT* PIXEL_REF;

PIXEL_REF new_pixel_fetcher(BM_REF bm, Int32 tile_flags, Int32 no_cached_tiles);
void delete_pixel_fetcher(PIXEL_REF pf);
UChar* pf_get_pixel_addr(PIXEL_REF pf, Int32 x, Int32 y);

Bool pf_get_pixel(PIXEL_REF pf, Int32 x, Int32 y, PIX_C* dst);
Bool pf_get_pixel(PIXEL_REF pf, Int32 x, Int32 y, PIX_W* dst);
Bool pf_get_pixel(PIXEL_REF pf, Int32 x, Int32 y, PIX_F* dst);

Bool pf_get_pixel_bilinear(PIXEL_REF pf, Float fx, Float fy, PIX_C* pixel);
Bool pf_get_pixel_bilinear(PIXEL_REF pf, Float fx, Float fy, PIX_W* pixel);
Bool pf_get_pixel_bilinear(PIXEL_REF pf, Float fx, Float fy, PIX_F* pixel);

UChar	bilinear8(Float x, Float y, UChar* values);
UInt16 bilinear16(Float x, Float y, UInt16* values);
Float	bilinear_double(Float x, Float y, Float* values);


#endif // PIXELFETCHUTIL_H__
