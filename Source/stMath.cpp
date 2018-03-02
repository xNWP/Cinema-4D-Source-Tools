// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "stMath.h"

namespace ST
{
	namespace Math
	{
		void SetWorldRotation(BaseObject *obj, const Vector &angle, const ROTATIONORDER &order)
		{
			Matrix mg = obj->GetMg();
			Vector pos = mg.off;
			Matrix mr = HPBToMatrix(angle, order);
			mr.off = pos;
			obj->SetMg(mr);
		}
	}
}