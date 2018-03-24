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
			if ((*V)[it] != nullptr)			\
				DeleteObj((*V)[it]);			\
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

// Methods
namespace ST
{
	namespace Mem
	{
		template <typename T>
		//----------------------------------------------------------------------------------------
		/// Returns the bytes a vector uses excluding the vector overhead.
		///
		/// @param[in] ptrvector				Pointer to the vector to check the size of.
		///
		/// @return size_t						The size in bytes.
		//----------------------------------------------------------------------------------------
		size_t SizeOfVector(std::vector<T*> *ptrvector)
		{
			size_t rval = sizeof(T) * ptrvector->size();
			return rval;
		}

		template <typename T>
		size_t SizeOfVector(std::vector<T> vector)
		{
			size_t rval = sizeof(T) * vector.size();
			return rval;
		}

		//----------------------------------------------------------------------------------------
		/// Converts bytes into it's highest divisor units and displays as a string.
		/// bytes = 2040 produces the result '1.99 MiB'.
		///
		/// @param[in] bytes					The number of bytes.
		///
		/// @return String						The formatted string
		//----------------------------------------------------------------------------------------
		String FormatBytes(const size_t &bytes);
	}
}

#endif