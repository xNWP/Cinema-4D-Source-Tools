// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_VMT
#define ST_VMT

#include "c4d.h"
#include <vector>

namespace ST
{
	struct VertexLitGeneric
	{
		Filename basetexture;
		Filename bumpmap;
		Filename detail;
		Bool phong = 0;
		Bool BasemapAlphaPhongMask = 0;
		Bool BasemapLuminancePhongMask = 0;
		Int32 PhongExponent = -1;
		Filename PhongExponentTexture;
		Float alpha = -1.0;
		Bool translucent = 0;
		Filename Iris;
		Filename AmbientOcclTexture;
		Filename Envmap;
	};
}

#endif