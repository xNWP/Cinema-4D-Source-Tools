// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_MATH_H
#define ST_MATH_H

#include "c4d.h"

namespace ST
{
	namespace Math
	{
		//----------------------------------------------------------------------------------------
		/// Set's the world rotation of an object.
		///
		/// @param[in,out] obj				Object to apply the rotation to.
		/// @param[in] angle				The angle (in radians) to set the rotation to.
		/// @param[in] order				The rotation order to use, default HPB.
		//----------------------------------------------------------------------------------------
		void SetWorldRotation(BaseObject *obj, const Vector &angle, const ROTATIONORDER &order = ROTATIONORDER_HPB);
	}
}

#endif