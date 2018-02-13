// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_USER_CONFIG_H
#define ST_USER_CONFIG_H

#include "c4d.h"
#include "tinyxml2/tinyxml2.h"

#define CHECK_FOR_UPDATES		"CHECK_FOR_UPDATES"

namespace ST
{

	//----------------------------------------------------------------------------------------
	/// Generates the default user-configuration file.
	///
	/// @param[in, out] doc				The document to generate the file from, caller owns the document.
	//----------------------------------------------------------------------------------------
	void GenerateDefaultConfigFile(tinyxml2::XMLDocument &doc);

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
}
#endif