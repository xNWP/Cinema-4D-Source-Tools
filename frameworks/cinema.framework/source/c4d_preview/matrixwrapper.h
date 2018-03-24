/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef MATRIXWRAPPER_H__
#define MATRIXWRAPPER_H__

#include "c4d_thread.h"
#include "x4d_filter.h"

extern Int32 do_matrix_effect_1dt(BM_REF bm, BM_TILE* dt, MATRIX_REF _emr, Int32 tile_flags);
extern Int32 do_matrix_effect(BM_REF bm, MATRIX_REF _emr, BaseThread* thread, Int32 tile_flags, Bool update_view, String* apply_filter_str);

#endif // MATRIXWRAPPER_H__
