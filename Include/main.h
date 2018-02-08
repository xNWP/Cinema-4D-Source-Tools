// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_MAIN_H
#define ST_MAIN_H

#include "c4d.h"
#include "c4d_symbols.h"
#include "curl\curl.h"
#include "Globals.h"
#include <string>
#include "tinyxml2/tinyxml2.h"
#include "UserConfig.h"
#include "VTFLib/VTFLib.h"
#include <Windows.h>

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
HMODULE LoadPluginDLL(const Char *dllName);

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
/// @return						Bool true if update available.
//----------------------------------------------------------------------------------------
Bool UpdateAvailable(const String &CheckURL, String &DownloadURL);

//----------------------------------------------------------------------------------------
/// Opens specified url in default browser.
///
/// @param[in] URL				The URL to open.
//----------------------------------------------------------------------------------------
void OpenURL(const String &url);

//----------------------------------------------------------------------------------------
/// Get's the element from the user config file.
///
/// @param[in] doc				The XML document.
/// @param[in] element			The element to get.
/// @param[out] value			The value contained in the element.
///
/// @return						Bool true if successful.
//----------------------------------------------------------------------------------------
Bool GetUserConfig(tinyxml2::XMLDocument *doc, const char *element, String &value);

//----------------------------------------------------------------------------------------
/// Sets the element (type USER_CONFIG) in the user config file to the specified value
///
/// @param[in] doc				The XML document.
/// @param[in] element			The element to set.
/// @param[in] value			The value to set the element.
///
/// @return						Bool true if successful.
//----------------------------------------------------------------------------------------
Bool SetUserConfig(tinyxml2::XMLDocument *doc, const char *element, const String &value);

#endif