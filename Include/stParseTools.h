// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_PARSE_TOOLS_H
#define ST_PARSE_TOOLS_H

#include "c4d.h"
#include <vector>

namespace ST
{
	namespace Parse
	{
		//----------------------------------------------------------------------------------------
		/// Split's a string into it's individual lines (CRLF).
		///
		/// @param[in] data				The input string.
		///
		/// @return						Pointer to std::vector<String>& array of individual lines.
		//----------------------------------------------------------------------------------------
		std::vector<String>* ParseLines(const String &data);
	}
}

#endif