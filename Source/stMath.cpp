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

		Float64 Dot(const Quaternion &q1, const Quaternion &q2)
		{
			Vector64 a = q1.v;
			Vector64 b = q2.v;
			Float64 c = q1.w * q2.w;
			return Dot(a, b) + c;
		}
	}
}