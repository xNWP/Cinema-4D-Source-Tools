// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "SourceAnimation.h"

namespace ST
{

}

Bool RegisterSourceAnimationTag()
{
	return RegisterTagPlugin(SOURCE_ANIMATION_TAG_ID, GeLoadString(IDS_SOURCE_ANIMATION), PLUGINFLAG_HIDE | TAG_VISIBLE | TAG_EXPRESSION, ST::SourceAnimation::Alloc, 0, 0, 0);
}