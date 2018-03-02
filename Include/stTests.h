// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifdef _DEBUG

#ifndef ST_TESTS_H
#define ST_TESTS_H

#include "c4d.h"
#include "Globals.h"
#include "SMDLoader.h"
#include "stParseTools.h"
#include <vector>

namespace ST
{
	namespace Tests
	{
		class Test1 : public CommandData
		{
		public:
			Bool Execute(BaseDocument *doc);
		};

		class Test2 : public CommandData
		{
		public:
			Bool Execute(BaseDocument *doc);
		};
	}
}

Bool RegisterTest1();
Bool RegisterTest2();

#endif
#endif