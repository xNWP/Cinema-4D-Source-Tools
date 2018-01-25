// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef MAIN_H
#define MAIN_H

#include "c4d.h"
#include "c4d_symbols.h"
#include "Globals.h"
#include <Windows.h>
#include "tinyxml2.h"
#include "curl\curl.h"
#include <string>

//----------------------------------------------------------------------------------------
/// Plugin registration functions
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
/// Registers the VTF Loader Plugin
///
/// @return						BOOL true if successful.
//----------------------------------------------------------------------------------------
Bool RegisterVTFLoader();

//----------------------------------------------------------------------------------------
/// Registers the VTF Saver Plugin
///
/// @return						BOOL true if successful.
//----------------------------------------------------------------------------------------
Bool RegisterVTFSaver();

//----------------------------------------------------------------------------------------
/// Registers the About Dialog
///
/// @return						BOOL true if successful.
//----------------------------------------------------------------------------------------
Bool RegisterAboutDialog();

//----------------------------------------------------------------------------------------
/// Loads the specified dll into memory. Use UnloadPluginDLL to unload.
///
/// @param[in] dllName		Path to dll (including extension) relative to the current plugins directory.
///
/// @return				HMODULE handle to dll
//----------------------------------------------------------------------------------------
HMODULE LoadPluginDLL(const String *dllName);

//----------------------------------------------------------------------------------------
/// Decrements the reference count of the specified dll by 1, unloads if reference count == 0
///
/// @param[in] DLLHANDLE		HMODULE handle to the dll
///
/// @return						BOOL true if successful
//----------------------------------------------------------------------------------------
BOOL UnloadPluginDLL(HMODULE DLLHANDLE);

//----------------------------------------------------------------------------------------
/// Checks if an update is available at CheckURL.
///
/// @param[in] CheckURL			The URL to check
/// @param[out] DownloadURL		The URL to the latest version.
///
/// @return						BOOL true if update available.
//----------------------------------------------------------------------------------------
BOOL UpdateAvailable(const String &CheckURL, String &DownloadURL);

#endif