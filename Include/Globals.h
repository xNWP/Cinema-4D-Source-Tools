// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_GLOBALS_H
#define ST_GLOBALS_H

// stringification macro
#define xstr(s) str(s)
#define str(s) #s

#define VERSION_MAJOR	0
#define VERSION_MINOR	21
#define VERSION_TAG		"-dev"

// About Dialog
#define ABOUT_ID		1040531

// VTF Import/Export
#define VTF_IMPORT_ID	1040515
#define VTF_EXPORT_ID	1040526

// DLL Locale
#define VTFLIB_DLL		"lib\\VTFLib.dll"
#define LIBCURL_DLL		"lib\\libcurl.dll"

// User Config
#define USER_CONFIG_LOC	"userconfig.xml"
#define PLUGIN_FOLDER	GeGetPluginPath().GetString().GetCStringCopy()

#endif