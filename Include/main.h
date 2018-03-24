// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_MAIN_H
#define ST_MAIN_H

// Cinema 4D
#include "c4d.h"
#include "c4d_symbols.h"

// Macros
#include "Globals.h"

// Libraries
#include "curl\curl.h"
#include <string>
#include "tinyxml2/tinyxml2.h"

// Modules
#include "AboutDialog.h"
#include "AGRLoader.h"
#include "SMDLoader.h"
//#include "SourceAnimation.h"
#include "UserConfig.h"
#include "VTFLoaderSaver.h"

// Tests
#ifdef _DEBUG
#include "stTests.h"
#endif

// Methods

//----------------------------------------------------------------------------------------
/// Checks if an update is available at CheckURL.
///
/// @param[in] CheckURL			The URL to check
/// @param[out] DownloadURL		The URL to the latest version.
///
/// @return						Bool true if update available.
//----------------------------------------------------------------------------------------
Bool UpdateAvailable(const String &CheckURL, String &DownloadURL);

#endif