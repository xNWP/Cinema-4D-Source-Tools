#include "SourceAnimation.h"

namespace ST
{

}

Bool RegisterSourceAnimationTag()
{
	return RegisterTagPlugin(SOURCE_ANIMATION_TAG_ID, GeLoadString(IDS_SOURCE_ANIMATION), TAG_VISIBLE | TAG_EXPRESSION, 0, 0, 0, 0);
}