//============ Copyright © 2020 Brett Anthony. All rights reserved. ============
///
/// This work is licensed under the terms of the MIT license.
/// For a copy, see <https://opensource.org/licenses/MIT>.
//==============================================================================
/// @file vtfloader.h
/// @brief declares the vtf loading plugin.
//==============================================================================

#ifndef VTF_LOADER_H__
#define VTF_LOADER_H__

#include "c4d_filterdata.h"

#define ID_VTFLOADER 1053587

class VTFLoaderData : public BitmapLoaderData
{
public:
	Bool Identify(const Filename& name, UChar* probe, Int32 size) override;
	IMAGERESULT Load(const Filename& name, BaseBitmap* bm, Int32 frame) override;

	static Bool RegisterPlugin();
};

#endif