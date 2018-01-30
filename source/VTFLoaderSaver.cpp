// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "VTFLoaderSaver.h"

namespace ST
{
	/* VTFLoader */

	Bool VTFLoader::Identify(const Filename &name, UChar *probe, Int32 size)
	{
		if (!probe || size < 4)
			return false;
		
		UInt32* p = (UInt32*)probe, v1 = p[0];
		lMotor(&v1); // Convert to BE.
	
		return v1 == 0x56544600; // 0x56544600 => VTF\0
	}

	IMAGERESULT VTFLoader::Load(const Filename &name, BaseBitmap *bm, Int32 frame)
	{
		// Load VTFLib.dll
		HMODULE dll = LoadPluginDLL(&String(xstr(VTFLIB_DLL)));

		// Get cPath
		Char cPath[512];
		name.GetString().GetCString(cPath, name.GetString().GetCStringLen() + 1, STRINGENCODING_UTF8);

		VTFLib::CVTFFile *file = new VTFLib::CVTFFile();

		if (!file->Load(cPath)) // Load file
			return IMAGERESULT_FILEERROR;

		UInt bw = file->GetWidth();
		UInt bh = file->GetHeight();
		UInt bdep = file->GetDepth();

		// Check invalid dimensions.
		if (bw <= 0 || bh <= 0)
			return IMAGERESULT_FILEERROR;

		// check if alpha
		VTFImageFormat srcmode = file->GetFormat();
		Bool alpha;

		if (srcmode == IMAGE_FORMAT_DXT1 || srcmode == IMAGE_FORMAT_I8 || srcmode == IMAGE_FORMAT_P8
			|| srcmode == IMAGE_FORMAT_BGR565 || srcmode == IMAGE_FORMAT_RGB565 || srcmode == IMAGE_FORMAT_BGR888
			|| srcmode == IMAGE_FORMAT_BGR888_BLUESCREEN || srcmode == IMAGE_FORMAT_RGB888
			|| srcmode == IMAGE_FORMAT_RGB888_BLUESCREEN)
			alpha = false;
		else
			alpha = true;

		// Create Bitmap
		if (bm->Init(bw, bh, alpha ? 32 : 24) != IMAGERESULT_OK)
			return IMAGERESULT_OUTOFMEMORY;
		
		UInt64 sizeSrc = file->ComputeImageSize(bw, bh, bdep, srcmode);
		UInt64 sizeRGBA = file->ComputeImageSize(bw, bh, bdep, IMAGE_FORMAT_RGBA8888);

		vlByte *RGBAData = new vlByte[sizeRGBA];
		vlByte *srcData = file->GetData(frame, 0, 0, 0);

		file->Convert(srcData, RGBAData, file->GetWidth(), file->GetHeight(), file->GetFormat(), IMAGE_FORMAT_RGBA8888);

		BaseBitmap *bmAlpha = 0;
		if (alpha)
			bmAlpha = bm->AddChannel(true, true);

		// Fill bitmap
		Bool bOk = true; Bool aOk = true;
		for (Int32 y = 0; y < bh; y++) // for each row
		{
			for (Int32 x = 0; x < bw && bOk && aOk; x++) // for each col
			{
				Int32 r = RGBAData[y * (bw * 4) + (x * 4)];
				Int32 g = RGBAData[y * (bw * 4) + (x * 4) + 1];
				Int32 b = RGBAData[y * (bw * 4) + (x * 4) + 2];
				Int32 a = RGBAData[y * (bw * 4) + (x * 4) + 3];
				bOk = bm->SetPixel(x, y, r, g, b);
				if (alpha)
					aOk = bm->SetAlphaPixel(bmAlpha, x, y, a);
			}
		}

		delete file;
		UnloadPluginDLL(dll);

		return bOk && aOk ? IMAGERESULT_OK : IMAGERESULT_FILEERROR;
	}

	Bool VTFLoader::GetInformation(const Filename &name, Int32 *frames, Float *fps)
	{
		HMODULE dll = LoadPluginDLL(&String(xstr(VTFLIB_DLL)));

		VTFLib::CVTFFile *file = new VTFLib::CVTFFile();
		if (!file->Load(name.GetString().GetCStringCopy(), true)) // load only file header
			return false;

		if (file->GetFrameCount() > 1)
			*frames = file->GetFrameCount();
		else
			frames = new Int32(15);

		UnloadPluginDLL(dll);

		return true;
	}

	/* VTFSaver */

	IMAGERESULT VTFSaver::Save(const Filename &name, BaseBitmap *bm, BaseContainer *data, SAVEBIT savebits)
	{
		// Check that resolution is a power of 2, max size is 2^16
		Bool wOk = false, hOk = false;
		for (Int32 i = 0; i <= 16 && (!wOk || !hOk); i++)
		{
			if (!wOk)
			{
				if (bm->GetBw() == Pow(2.0, i))
					wOk = true;
			}
			if (!hOk)
			{
				if (bm->GetBh() == Pow(2.0, i))
					hOk = true;
			}
		}
		
		if (!wOk || !hOk)
			return IMAGERESULT_PARAM_ERROR;

		// Load VTFLib.dll
		HMODULE dll = LoadPluginDLL(&String(xstr(VTFLIB_DLL)));

		VTFLib::CVTFFile *file = new VTFLib::CVTFFile();
		if (!file->Create(bm->GetBw(), bm->GetBh(), 1, 1, 1, savebits & SAVEBIT_ALPHA == SAVEBIT_ALPHA ? IMAGE_FORMAT_RGBA8888 : IMAGE_FORMAT_RGB888, true, false))
			return IMAGERESULT_FILEERROR;

		// Load data into an array
		Int64 dataSize = bm->GetBw() * bm->GetBh() * (savebits & SAVEBIT_ALPHA == SAVEBIT_ALPHA ? 4 : 3);
		vlByte *srcData = new vlByte[dataSize];

		for (Int64 sY = 0; sY < bm->GetBh(); sY++) // for each row
		{
			for (Int64 sX = 0; sX < bm->GetBw(); sX++) // for each col
			{
				UInt16 r, g, b;
				bm->GetPixel(sX, sY, &r, &g, &b);
				Int16 bytes = savebits & SAVEBIT_ALPHA == SAVEBIT_ALPHA ? 4 : 3;
				srcData[sY * bm->GetBw() * bytes + sX * bytes] = (vlByte)r;
				srcData[sY * bm->GetBw() * bytes + sX * bytes + 1] = (vlByte)g;
				srcData[sY * bm->GetBw() * bytes + sX * bytes + 2] = (vlByte)b;
				if (savebits & SAVEBIT_ALPHA == SAVEBIT_ALPHA)
				{
					UInt16 a = 0;
					bm->GetAlphaPixel(bm->GetInternalChannel(), sX, sY, &a);
					srcData[sY * bm->GetBw() * bytes + sX * bytes + 3] = (vlByte)a;
				}
			}
		}

		// Commit Data
		file->SetData(0, 0, 0, 0, srcData);
		Bool sOk = file->Save(name.GetString().GetCStringCopy());

		UnloadPluginDLL(dll);

		return sOk ? IMAGERESULT_OK : IMAGERESULT_FILEERROR;
	}


}

Bool RegisterVTFLoader()
{
	String name = GeLoadString(IDS_VTF);
	if (!RegisterBitmapLoaderPlugin(VTF_IMPORT_ID, name, PLUGINFLAG_BITMAPLOADER_MOVIE, NewObjClear(ST::VTFLoader)))
		return false;

	return true;
}

Bool RegisterVTFSaver()
{
	String name = GeLoadString(IDS_VTF);
	if (!RegisterBitmapSaverPlugin(VTF_EXPORT_ID, name, PLUGINFLAG_BITMAPSAVER_SUPPORT_8BIT, NewObjClear(ST::VTFSaver), "vtf"))
		return false;

	return true;
}