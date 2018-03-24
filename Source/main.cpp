// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "main.h"

Bool PluginStart(void)
{	// Register Components
	if (!RegisterAboutDialog())
	{
		GePrint("C4DST -- About DLG Failed Load");
		return false;
	}
	/*if (!RegisterAGRLoader())
	{
		GePrint("C4DST -- AGRLoader Failed Load");
		return false;
	}*/
	if (!RegisterSMDLoader())
	{
		GePrint("C4DST -- SMDLoader Failed Load");
		return false;
	}
	/*if (!RegisterSourceAnimationTag())
	{
	GePrint("C4DST -- SourceAnimation Failed Load");
		return false;
	}*/
	if (!RegisterVTFLoader())
	{
		GePrint("C4DST -- VTFLoader Failed Load");
		return false;
	}
	if (!RegisterVTFSaver())
	{
		GePrint("C4DST -- VTFSaver Failed Load");
		return false;
	}

	// Tests
#ifdef _DEBUG
	if (!RegisterTest1())
		return false;
	if (!RegisterTest2())
		return false;
#endif

	String StrLoc = GeGetPluginPath().GetString();
	StrLoc += "\\";
	StrLoc += USER_CONFIG_LOC;
	Char *ChaLoc = NewMem(Char, StrLoc.GetCStringLen() + 1);
	StrLoc.GetCString(ChaLoc, StrLoc.GetCStringLen() + 1);
	tinyxml2::XMLDocument *M_DOC = NewObj(tinyxml2::XMLDocument);
	tinyxml2::XMLError error = M_DOC->LoadFile(ChaLoc);

	if (error == tinyxml2::XML_ERROR_FILE_NOT_FOUND)
	{
		ST::GenerateDefaultConfigFile(*M_DOC);
		// Acknowledge valid installation and ask if the user wants updates
		if (QuestionDialog(GeLoadString(IDS_PLUGIN_NAME)
			+ GeLoadString(IDS_NEW_INSTALL)
			+ GeLoadString(IDS_PLUGIN_NAME) + ")."))
		{
			if (!ST::SetUserConfig(M_DOC, CHECK_FOR_UPDATES, "true"))
				return false;
		}
		else
		{
			if (!ST::SetUserConfig(M_DOC, CHECK_FOR_UPDATES, "false"))
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
	if (!ST::GetUserConfig(M_DOC, CHECK_FOR_UPDATES, CheckUpdate))
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
				ST::OpenURL(DownloadURL);
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

		case C4DPL_BUILDMENU:
		{
#ifdef _DEBUG
			BaseContainer *MainMenu = GetMenuResource("M_EDITOR");

			// ONLY IF TESTING
			BaseContainer testMenu;
			testMenu.InsData(MENURESOURCE_SUBTITLE, "C4DST Test");
			testMenu.InsData(MENURESOURCE_COMMAND, "PLUGIN_CMD_1000001");
			testMenu.InsData(MENURESOURCE_COMMAND, "PLUGIN_CMD_1000002");
			MainMenu->InsData(MENURESOURCE_STRING, testMenu);
#endif
			return true;
		}
	}

	return true;
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

Bool UpdateAvailable(const String &CheckURL, String &DownloadURL)
{
	HMODULE dll = ST::LoadPluginDLL(LIBCURL_DLL);

	// Get latest version info from site
	BufferStruct output;
	output.buffer = NULL;
	output.size = 0;

	curl_global_init(CURL_GLOBAL_WIN32);
	CURL *handle = curl_easy_init();
	
	Char *cCheckURL = NewMem(Char, CheckURL.GetCStringLen() + 1);
	CheckURL.GetCString(cCheckURL, CheckURL.GetCStringLen() + 1);

	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&output);
	curl_easy_setopt(handle, CURLOPT_URL, cCheckURL);
	if (curl_easy_perform(handle) != CURLE_OK)
	{
		GePrint(GeLoadString(IDS_PLUGIN_NAME) + " -- critical error checking for updates, are you connected to the internet?");
		return false;
	}
	curl_easy_cleanup(handle);

	ST::UnloadPluginDLL(dll);

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
	DeleteMem(cCheckURL);

	return false;
}