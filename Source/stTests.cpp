// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
#ifdef _DEBUG

#include "stTests.h"

namespace ST
{
	namespace Tests
	{
		Bool Test1::Execute(BaseDocument *doc)
		{
			GePrint("-- START TEST SMD IMPORT -- ");
			DiagnosticOutput("-- START TEST SMD IMPORT -- ");

			AutoAlloc<BaseFile> file;
			if (!file->Open("C:\\testfilessmd.txt"))
				return file->GetError();

			AutoAlloc<BaseFile> debugout;
			if (!debugout->Open("C:\\debugout.txt", FILEOPEN_WRITE))
				return file->GetError();

			// read data into byte array and seperate it into lines.
			Char *fileData = NewMem(Char, file->GetLength());
			file->ReadBytes(fileData, file->GetLength());
			std::vector<String> *fileLineData = ST::Parse::ParseLines(fileData);

			file->Close();

			BasePlugin *plug = FindPlugin(SMD_IMPORT_ID, PLUGINTYPE_SCENELOADER);
			BaseList2D *importer;

			plug->Message(MSG_RETRIEVEPRIVATEDATA, &importer);
			BaseContainer *data = importer->GetDataInstance();

			data->SetBool(SMD_IMPORT_QC, false);
			data->SetBool(SMD_CACHE_MEMORY, false);

			// Actual testing starts here
			for (Int32 i = 0; i < fileLineData->size(); i++)
			{
				Filename loadFile = (*fileLineData)[i];
				String *error = nullptr;

				String str = "-- Loading: " + loadFile.GetString() +
					" (" + String::IntToString(i) + "/" +
					String::IntToString(Int32(fileLineData->size())) + ")";
				Char *cstr = NewMem(Char, str.GetCStringLen() + 1);
				str.GetCString(cstr, str.GetCStringLen() + 1);

				StatusSetText(str);

				GePrint(cstr);
				DiagnosticOutput(cstr);
				debugout->WriteString(str + "\n");
				DeleteMem(cstr);

				LoadDocument(loadFile, SCENEFILTER_0, nullptr, error);
				if (error == nullptr)
					error = NewObj(String, "N/A");

				str = "-- Result: " + *error;
				cstr = NewMem(Char, str.GetCStringLen() + 1);
				str.GetCString(cstr, str.GetCStringLen() + 1);

				GePrint(cstr);
				DiagnosticOutput(cstr);
				debugout->WriteString(str + "\n");
				DeleteMem(cstr);
				DeleteObj(error);

				CloseAllDocuments();
			}

			GePrint("-- END TEST SMD IMPORT -- ");
			DiagnosticOutput("-- END TEST SMD IMPORT -- ");

			debugout->Close();
			StatusClear();
			return true;
		}

		Bool Test2::Execute(BaseDocument *doc)
		{
			GePrint("-- START TEST QC IMPORT -- ");
			DiagnosticOutput("-- START TEST QC IMPORT -- ");

			AutoAlloc<BaseFile> file;
			if (!file->Open("C:\\testfilesqc.txt"))
				return file->GetError();

			AutoAlloc<BaseFile> debugout;
			if (!debugout->Open("C:\\debugout.txt", FILEOPEN_WRITE))
				return file->GetError();

			// read data into byte array and seperate it into lines.
			Char *fileData = NewMem(Char, file->GetLength());
			file->ReadBytes(fileData, file->GetLength());
			std::vector<String> *fileLineData = ST::Parse::ParseLines(fileData);

			file->Close();

			BasePlugin *plug = FindPlugin(SMD_IMPORT_ID, PLUGINTYPE_SCENELOADER);
			BaseList2D *importer;

			plug->Message(MSG_RETRIEVEPRIVATEDATA, &importer);
			BaseContainer *data = importer->GetDataInstance();

			data->SetBool(SMD_IMPORT_QC, true);
			data->SetBool(SMD_CACHE_MEMORY, false);

			// Actual testing starts here
			for (Int32 i = 0; i < fileLineData->size(); i++)
			{
				Filename loadFile = (*fileLineData)[i];
				String *error = nullptr;

				String str = "-- Loading: " + loadFile.GetString() +
					" (" + String::IntToString(i) + "/" +
					String::IntToString(Int32(fileLineData->size())) + ")";
				Char *cstr = NewMem(Char, str.GetCStringLen() + 1);
				str.GetCString(cstr, str.GetCStringLen() + 1);

				StatusSetText(str);

				GePrint(cstr);
				DiagnosticOutput(cstr);
				debugout->WriteString(str + "\n");
				DeleteMem(cstr);

				LoadDocument(loadFile, SCENEFILTER_0, nullptr, error);
				if (error == nullptr)
					error = NewObj(String, "N/A");

				str = "-- Result: " + *error;
				cstr = NewMem(Char, str.GetCStringLen() + 1);
				str.GetCString(cstr, str.GetCStringLen() + 1);

				GePrint(cstr);
				DiagnosticOutput(cstr);
				debugout->WriteString(str + "\n");
				DeleteMem(cstr);
				DeleteObj(error);

				CloseAllDocuments();
			}

			GePrint("-- END TEST QC IMPORT -- ");
			DiagnosticOutput("-- END TEST QC IMPORT -- ");

			debugout->Close();
			StatusClear();
			return true;
		}
	}
}

Bool RegisterTest1()
{
	ST::Tests::Test1 *t_cmd = NewObjClear(ST::Tests::Test1);
	return RegisterCommandPlugin(TEST_RESERVE_0, "Test SMD Load", PLUGINFLAG_HIDEPLUGINMENU, 0, 0, t_cmd);
}

Bool RegisterTest2()
{
	ST::Tests::Test2 *t_cmd = NewObjClear(ST::Tests::Test2);
	return RegisterCommandPlugin(TEST_RESERVE_1, "Test QC Load", PLUGINFLAG_HIDEPLUGINMENU, 0, 0, t_cmd);
}

#endif