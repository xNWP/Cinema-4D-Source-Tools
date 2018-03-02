// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "stMem.h"

namespace ST
{
	namespace Mem
	{
		String FormatBytes(const size_t &bytes)
		{
			if (!(bytes > 0))
				return String("0 bytes");

			String BytesSuffix[5] = { "bytes", "KiB", "MiB", "GiB", "TiB" };
			Int16 i = -1;
			Float64 val = Float64(bytes);
			Float64 lval;
			while (val >= 1.0 && i < 5)
			{
				lval = val;
				val /= 1024;
				i++;
			}
			if (Int32(lval) == lval)
				return String::IntToString(Int32(lval)) + " " + BytesSuffix[i];
			else
				return String::FloatToString(lval, -1, 2) + " " + BytesSuffix[i];
		}
	}
}