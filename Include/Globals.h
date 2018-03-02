// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_GLOBALS_H
#define ST_GLOBALS_H

// Libraries //
#include "c4d.h"
#include <string>
#include <Windows.h>

// Macros //

// stringification macro
#define xstr(s) str(s)
#define str(s) #s

#define VERSION_MAJOR	0
#define VERSION_MINOR	34
#define VERSION_TAG		"-alpha"

// About Dialog
#define ABOUT_ID		1040531

// VTF Import/Export
#define VTF_IMPORT_ID	1040515
#define VTF_EXPORT_ID	1040526

// SMD Import
#define SMD_IMPORT_ID	1040673

// Source Animation Tag
#define SOURCE_ANIMATION_TAG_ID	 1000006

// Tests
#define TEST_RESERVE_0	1000001
#define TEST_RESERVE_1	1000002
#define TEST_RESERVE_2	1000003
#define TEST_RESERVE_3	1000004
#define TEST_RESERVE_4	1000005

// DLL Locale
#define VTFLIB_DLL		"lib\\VTFLib.dll"
#define LIBCURL_DLL		"lib\\libcurl.dll"

// User Config
#define USER_CONFIG_LOC	"userconfig.xml"

// Methods //
namespace ST
{
	//----------------------------------------------------------------------------------------
	/// Opens specified url in default browser.
	///
	/// @param[in] url				The URL to open.
	//----------------------------------------------------------------------------------------
	void OpenURL(const String &url);

	//----------------------------------------------------------------------------------------
	/// Loads the specified dll into memory. Use UnloadPluginDLL to unload.
	///
	/// @param[in] dllName		Path to dll (including extension) relative to the current plugins directory.
	///
	/// @return				HMODULE handle to dll
	//----------------------------------------------------------------------------------------
	HMODULE LoadPluginDLL(const Char *dllName);

	//----------------------------------------------------------------------------------------
	/// Decrements the reference count of the specified dll by 1, unloads if reference count == 0
	///
	/// @param[in] DLLHANDLE		HMODULE handle to the dll
	///
	/// @return						BOOL true if successful
	//----------------------------------------------------------------------------------------
	BOOL UnloadPluginDLL(HMODULE DLLHANDLE);
}

#endif