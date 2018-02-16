// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "stParseTools.h"

namespace ST
{
	namespace Parse
	{
		std::vector<String>* ParseLines(const String &data)
		{
			std::vector<String> *rval = NewObj(std::vector<String>);
			Int32 it = 0;
			Int32 pos = 0;

			while (pos < data.GetLength())
			{
				if (data.FindFirst("\r\n", &it, pos))
				{
					rval->push_back(data.SubStr(pos, it - pos));
					pos = it + 2;
				}
				else
				{
					rval->push_back(data.SubStr(pos, data.GetLength() - pos));
					break;
				}
			}
			return rval;
		}
	}
}