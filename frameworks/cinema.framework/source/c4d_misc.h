/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_MISC_H__
#define C4D_MISC_H__

#ifndef USE_API_MAXON

#include "c4d_misc/general.h"
#include "c4d_misc/memory/debugglobals.h"
#include "c4d_misc/memory/defaultallocator.h"
#include "c4d_misc/datastructures/autoiterator.h"
#include "c4d_misc/datastructures/basearray.h"
#include "c4d_misc/datastructures/blockarray.h"
#include "c4d_misc/datastructures/pointerarray.h"
#include "c4d_misc/datastructures/baselist.h"
#include "c4d_misc/datastructures/sort.h"
#include "c4d_misc/datastructures/sortedarray.h"
#include "c4d_misc/datastructures/hashmap.h"

#else

#include "maxon/apibase.h"

#endif

#endif // C4D_MISC_H__
