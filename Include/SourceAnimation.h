// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef SOURCE_ANIMATION_H
#define SOURCE_ANIMATION_H

#include "c4d.h"
#include "c4d_symbols.h"
#include "Globals.h"

namespace ST
{
	class SourceAnimation : public TagData
	{
	public:

		static NodeData* Alloc() { return NewObj(SourceAnimation); }
	};
}

Bool RegisterSourceAnimationTag();

#endif