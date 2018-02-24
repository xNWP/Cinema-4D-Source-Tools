// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_MEM_H
#define ST_MEM_H

#include "c4d.h"
#include <vector>

//----------------------------------------------------------------------------------------
/// Clears the contents of a std::vector with pointer members safely.
///
/// @param[in] V					std::vector<type*> *V
//----------------------------------------------------------------------------------------
#define PtrVecClear(V)							\
	if (V != nullptr)							\
	{											\
		decltype(V->size()) it = V->size() - 1;	\
		while (it > 0)							\
		{										\
			DeleteObj((*V)[it]);				\
			it--;								\
		}										\
		DeleteObj((*V)[0]);						\
		V->clear();								\
	}

//----------------------------------------------------------------------------------------
/// Deletes a std::vector with pointer members safely.
///
/// @param[in] V					std::vector<type*> *V
//----------------------------------------------------------------------------------------
#define DeletePtrVector(V)						\
	if (V != nullptr)							\
	{											\
		if (V->size() > 0)						\
		{										\
			PtrVecClear(V);						\
		}										\
		DeleteObj(V);							\
	}

#endif