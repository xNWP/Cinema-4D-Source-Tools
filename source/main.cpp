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

	String DownloadURL;
	if (UpdateAvailable("http://code.thatnwp.com/version/Cinema4DSourceToolsUpdate.xml", DownloadURL))
	{
		if (QuestionDialog(
			GeLoadString(IDS_UPDATE_AVAIL_0)
			+ GeLoadString(IDS_PLUGIN_NAME)
			+ GeLoadString(IDS_UPDATE_AVAIL_1)
			+ GeLoadString(IDS_PLUGIN_NAME) + ")."))
		{
			// casting shenanigans
			std::string sURL = DownloadURL.GetCStringCopy();
			std::wstring wURL(sURL.begin(), sURL.end());
			LPCWSTR url = wURL.c_str();

			ShellExecute(NULL, L"open", url, NULL, NULL, SW_SHOWNORMAL);
		}
	}

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
	HMODULE dll = LoadPluginDLL(&String(xstr(LIBCURL_DLL)));

	// Get latest version info from site
	BufferStruct output;
	output.buffer = NULL;
	output.size = 0;

	curl_global_init(CURL_GLOBAL_WIN32);
	CURL *handle = curl_easy_init();
	
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&output);
	curl_easy_setopt(handle, CURLOPT_URL, CheckURL.GetCStringCopy());
	curl_easy_perform(handle);
	curl_easy_cleanup(handle);

	UnloadPluginDLL(dll);

	// parse that info with tinyxml2
	tinyxml2::XMLDocument data;
	data.Parse(output.buffer, output.size);
	tinyxml2::XMLElement *update = data.FirstChildElement("update");
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

	return false;
}