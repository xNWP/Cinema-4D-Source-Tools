// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "main.h"

Bool PluginStart(void)
{
	// Register Components
	if (!RegisterAboutDialog())
		return false;
	if (!RegisterVTFLoader())
		return false;
	if (!RegisterVTFSaver())
		return false;

	String VersionTag = xstr(VERSION_TAG);
	VersionTag = (VersionTag == "0" ? "" : VersionTag);
	GePrint("Loaded " + GeLoadString(IDS_PLUGIN_NAME) + " " + xstr(VERSION_MAJOR) + "." xstr(VERSION_MINOR) + VersionTag);

	return true;
}

void PluginEnd(void)
{
}

Bool PluginMessage(Int32 id, void *data)
{
	switch (id)
	{
	case C4DPL_INIT_SYS: // Do not init w/o resources.
		if (!resource.Init())
			return false;
	}

	return true;
}

HMODULE LoadPluginDLL(const String *dllName)
{
	// A big thank-you to karanik on the plugincafe forums,
	// this code is mostly based on his.

	String path = GeGetPluginPath().GetString();
	path += String("\\");
	path += String(*dllName);

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

BOOL UpdateAvailable(const String &CheckURL, String &DownloadURL)
{
	HMODULE dll = LoadPluginDLL(&String("lib\\libcurl.dll"));

	CURLcode curlcode = curl_global_init(CURL_GLOBAL_WIN32);

	UnloadPluginDLL(dll);

	return true;
}