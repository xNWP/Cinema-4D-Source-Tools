// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_VTF_LOADER_SAVER_H
#define ST_VTF_LOADER_SAVER_H

#include "c4d.h"
#include "c4d_symbols.h"
#include "Globals.h"
#include "main.h"

#include "VTFLib.h"

namespace ST
{
	//----------------------------------------------------------------------------------------
	/// VTFLoader class
	/// Allows for the importing of Valve Texture Format (VTF) files
	//----------------------------------------------------------------------------------------
	class VTFLoader : public BitmapLoaderData
	{
	public:
		Bool Identify(const Filename &name, UChar *probe, Int32 size);
		IMAGERESULT Load(const Filename &name, BaseBitmap *bm, Int32 frame);
	};

	//----------------------------------------------------------------------------------------
	/// VTFSaver class
	/// Allows for the saving of Valve Texture Format (VTF) files
	//----------------------------------------------------------------------------------------
	class VTFSaver : public BitmapSaverData
	{
	public:
		IMAGERESULT Save(const Filename &name, BaseBitmap *bm, BaseContainer *data, SAVEBIT savebits);
		Int32 GetMaxAlphas(BaseContainer *data) { return 1; }
	};
}

#endif