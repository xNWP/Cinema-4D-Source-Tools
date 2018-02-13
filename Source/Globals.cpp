// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "Globals.h"

namespace ST
{
	void OpenURL(const String &url)
	{
		// casting shenanigans
		Char* charURL = NewMem(Char, url.GetCStringLen() + 1);
		url.GetCString(charURL, url.GetCStringLen() + 1);
		std::string sURL = charURL;
		std::wstring wURL(sURL.begin(), sURL.end());
		LPCWSTR lURL = wURL.c_str();

		ShellExecute(NULL, L"open", lURL, NULL, NULL, SW_SHOWNORMAL);

		DeleteMem(charURL);
	}

	HMODULE LoadPluginDLL(const Char *dllName)
	{
		// A big thank-you to karanik on the plugincafe forums,
		// this code is mostly based on his.

		String path = GeGetPluginPath().GetString();
		path += String("\\");
		path += dllName;

		maxon::BaseArray<Utf16Char> arr;
		if (!path.GetUtf16(arr))
			return 0;

		// Append null at end
		arr.Append(Utf16Char(0));

		HMODULE mod = LoadLibrary((LPCWSTR)(arr.GetFirst()));
		return mod;
	}

	BOOL UnloadPluginDLL(HMODULE DLLHANDLE)
	{
		return FreeLibrary(DLLHANDLE);
	}
}