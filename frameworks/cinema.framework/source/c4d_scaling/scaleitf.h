/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef SCALEITF_H__
#define SCALEITF_H__

#include "x4d_filter.h"

Int32 scale_bm(const BM_TILE* src_bm, const BM_TILE* dst_bm, const RECT32* src_rect, const RECT32* dst_rect, const RECT32* clip_rect);

#endif // SCALEITF_H__
