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

	String StrLoc = PLUGIN_FOLDER;
	StrLoc += "\\"; StrLoc += USER_CONFIG_LOC;
	Char *ChaLoc = NewMem(Char, StrLoc.GetCStringLen() + 1);
	StrLoc.GetCString(ChaLoc, StrLoc.GetCStringLen() + 1);
	tinyxml2::XMLDocument *M_DOC = NewObj(tinyxml2::XMLDocument);
	tinyxml2::XMLError error = M_DOC->LoadFile(ChaLoc);
	if (error == tinyxml2::XML_ERROR_FILE_NOT_FOUND)
	{
		GenerateDefaultConfigFile(*M_DOC);
		// Acknowledge valid installation and ask if the user wants updates
		if (QuestionDialog(GeLoadString(IDS_PLUGIN_NAME)
			+ GeLoadString(IDS_NEW_INSTALL)
			+ GeLoadString(IDS_PLUGIN_NAME) + ")."))
		{
			if (!SetUserConfig(M_DOC, CHECK_FOR_UPDATES, "true"))
				return false;
		}
		else
		{
			if (!SetUserConfig(M_DOC, CHECK_FOR_UPDATES, "false"))
				return false;
		}

		// save the file
		M_DOC->SaveFile(ChaLoc);
	}
	else if (error != tinyxml2::XML_SUCCESS)
	{
		GePrint(GeLoadString(IDS_PLUGIN_NAME) + " -- critical error loading userconfig.xml");
		return false;
	}

	String CheckUpdate;
	if (!GetUserConfig(M_DOC, CHECK_FOR_UPDATES, CheckUpdate))
		return false;

	if (CheckUpdate == "true")
	{
		String DownloadURL;
		if (UpdateAvailable("http://code.thatnwp.com/version/Cinema4DSourceToolsUpdate.xml", DownloadURL))
		{
			if (QuestionDialog(
				GeLoadString(IDS_UPDATE_AVAIL_0)
				+ GeLoadString(IDS_PLUGIN_NAME)
				+ GeLoadString(IDS_UPDATE_AVAIL_1)
				+ GeLoadString(IDS_PLUGIN_NAME) + ")."))
			{
				OpenURL(DownloadURL);
			}
		}
	}

	GePrint("Loaded " + GeLoadString(IDS_PLUGIN_NAME) + " " + xstr(VERSION_MAJOR) + "." xstr(VERSION_MINOR) + VERSION_TAG);

	DeleteObj(M_DOC);
	DeleteMem(ChaLoc);

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

// Define our struct for accepting LCs output
struct BufferStruct
{
	char * buffer;
	size_t size;
};

// This is the function we pass to LC, which writes the output to a BufferStruct
// Thanks to secdef9 at HackThisSite.org for this code !!
// https://www.hackthissite.org/articles/read/1078
static size_t WriteMemoryCallback
(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;

	struct BufferStruct * mem = (struct BufferStruct *) data;

	mem->buffer = (char*)realloc(mem->buffer, mem->size + realsize + 1);

	if (mem->buffer)
	{
		memcpy(&(mem->buffer[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->buffer[mem->size] = 0;
	}
	return realsize;
}

BOOL UpdateAvailable(const String &CheckURL, String &DownloadURL)
{
	HMODULE dll = LoadPluginDLL(LIBCURL_DLL);

	// Get latest version info from site
	BufferStruct output;
	output.buffer = NULL;
	output.size = 0;

	curl_global_init(CURL_GLOBAL_WIN32);
	CURL *handle = curl_easy_init();
	
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&output);
	curl_easy_setopt(handle, CURLOPT_URL, CheckURL.GetCStringCopy());
	if (curl_easy_perform(handle) != CURLE_OK)
	{
		GePrint(GeLoadString(IDS_PLUGIN_NAME) + " -- critical error checking for updates, are you connected to the internet?");
		return false;
	}
	curl_easy_cleanup(handle);

	UnloadPluginDLL(dll);

	// parse that info with tinyxml2
	tinyxml2::XMLDocument *data = NewObj(tinyxml2::XMLDocument);
	data->Parse(output.buffer, output.size);
	tinyxml2::XMLElement *update = data->FirstChildElement("update");
	tinyxml2::XMLElement *major = update->FirstChildElement("version")->FirstChildElement("major");
	tinyxml2::XMLElement *minor = update->FirstChildElement("version")->FirstChildElement("minor");
	tinyxml2::XMLElement *download = update->FirstChildElement("link");

	int i_major, i_minor;
	major->QueryIntText(&i_major);
	minor->QueryIntText(&i_minor);
	DownloadURL = download->GetText();

	// Finally check if latest version > current version
	if (i_major >= VERSION_MAJOR)
	{
		if (i_minor > VERSION_MINOR)
		{
			return true;
		}
	}

	DeleteObj(data);

	return false;
}

void OpenURL(const String &url)
{
	// casting shenanigans
	std::string sURL = url.GetCStringCopy();
	std::wstring wURL(sURL.begin(), sURL.end());
	LPCWSTR lURL = wURL.c_str();

	ShellExecute(NULL, L"open", lURL, NULL, NULL, SW_SHOWNORMAL);
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

	e->SetText(value.GetCStringCopy());

	return true;
}