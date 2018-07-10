// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "UserConfig.h"

namespace ST
{
	void GenerateDefaultConfigFile(tinyxml2::XMLDocument &doc)
	{
		tinyxml2::XMLNode *node = doc.NewElement(CHECK_FOR_UPDATES);
		doc.InsertEndChild(node);
		node = doc.NewElement(MATFT_CUSTOM_UC);
		doc.InsertEndChild(node);
	}

	Bool GetUserConfig(tinyxml2::XMLDocument *doc, const char *element, String &value)
	{
		if (doc == nullptr) // config must be loaded
			return false;

		tinyxml2::XMLElement *e = doc->FirstChildElement(element);

		value = e->GetText();

		return (&value == nullptr) ? false : true;
	}

	Bool SetUserConfig(tinyxml2::XMLDocument *doc, const char *element, const String &value)
	{
		if (doc == nullptr) // config must be loaded
			return false;

		tinyxml2::XMLElement *e = doc->FirstChildElement(element);

		Char *val = NewMem(Char, value.GetCStringLen() + 1);
		value.GetCString(val, value.GetCStringLen() + 1);
		e->SetText(val);
		DeleteMem(val);

		return true;
	}

	tinyxml2::XMLNode* GetNode(tinyxml2::XMLDocument *doc, const char *element)
	{
		if (doc == nullptr) // config must be loaded
			return false;

		tinyxml2::XMLElement *e = doc->FirstChildElement(element);

		if (!e)
			return nullptr;

		return e;
	}

}