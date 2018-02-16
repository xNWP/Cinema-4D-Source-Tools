// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "SMDLoader.h"

namespace ST
{
	SMDLoader::~SMDLoader()
	{
		DeletePtrVector(m_skeleton);
	}

	Bool SMDLoader::Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size)
	{
		// unfortunately SMD is an ascii format so we will just assume
		// that the file-type is smd based on the extension alone.
		return name.GetSuffix().ToLower() == "smd" ? true : false;
	}

	FILEERROR SMDLoader::Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, String* error, BaseThread* bt)
	{
		AutoAlloc<BaseFile> file;
		file->Open(name);
		
		// read data into byte array and seperate it into lines.
		Char *fileData = NewMem(Char, file->GetLength());
		file->ReadBytes(fileData, file->GetLength());
		std::vector<String> *fileLineData = ST::Parse::ParseLines(fileData);
		DeleteMem(fileData);

		BaseObject *topNull;

		for (Int32 i = 0; i < fileLineData->size(); i++)
		{
			String line = (*fileLineData)[i];
			if (line == "nodes")
			{
				if (!ParseNodes(fileLineData, i))
				{
					*error = GeLoadString(IDS_CRITICAL_ERROR);
					return FILEERROR_READ;
				}
			}
			if (line == "skeleton")
			{
				topNull = BaseObject::Alloc(Onull);
				topNull->SetName(name.GetFileString());
				doc->InsertObject(topNull, nullptr, nullptr);
				if (!ParseSkeleton(fileLineData, doc, topNull, i))
				{
					*error = GeLoadString(IDS_CRITICAL_ERROR);
					return FILEERROR_READ;
				}
			}
		}

		file->Close();
		DeleteObj(fileLineData);

		return FILEERROR_NONE;
	}

	Bool SMDLoader::ParseNodes(const std::vector<String> *data, Int32 &it)
	{
		it++;
		while ((*data)[it] != "end" && it < data->size())
		{
			Int32 id, parentid;
			String name;
			std::vector<String> substrs;

			Int32 start = -1;
			for (Int32 i = 0; i <= (*data)[it].GetLength(); i++)
			{
				if ((*data)[it][i] == ' ' && start == -1)
				{
					continue;
				}
				else if (i == (*data)[it].GetLength())
				{
					substrs.push_back((*data)[it].SubStr(start, i - start));
				}
				else if (start == -1)
				{
					start = i;
				}
				else if ((*data)[it][i] == ' ' && start != -1)
				{
					substrs.push_back((*data)[it].SubStr(start, i - start));
					start = -1;
				}
			}
			if (substrs.size() < 3)
				return false;

			id = substrs[0].ParseToInt32();
			name = substrs[1].SubStr(1, substrs[1].GetLength() - 2);
			parentid = substrs[2].ParseToInt32();

			SourceSkeletonBone *bone = NewObj(SourceSkeletonBone, id, parentid);
			bone->SetName(name);
			if (m_skeleton == nullptr)
				m_skeleton = NewObj(std::vector<SourceSkeletonBone*>);
			m_skeleton->push_back(bone);

			it++;
		}

		return (it == data->size()) ? false : true;
	}

	Bool SMDLoader::ParseSkeleton(const std::vector<String> *data, BaseDocument *doc, BaseObject *parent, Int32 &it)
	{
		it++; it++; // two to skip time, need to implement animation yet.

		while ((*data)[it] != "end" && it < data->size())
		{
			std::vector<String> substrs;

			Int32 start = -1;
			for (Int32 i = 0; i <= (*data)[it].GetLength(); i++)
			{
				if ((*data)[it][i] == ' ' && start == -1)
				{
					continue;
				}
				else if (i == (*data)[it].GetLength())
				{
					substrs.push_back((*data)[it].SubStr(start, i - start));
				}
				else if (start == -1)
				{
					start = i;
				}
				else if ((*data)[it][i] == ' ' && start != -1)
				{
					substrs.push_back((*data)[it].SubStr(start, i - start));
					start = -1;
				}
			}
			if (substrs.size() < 7)
				return false;

			Int32 id = substrs[0].ParseToInt32();
			Vector pos(substrs[1].ParseToFloat(), substrs[2].ParseToFloat(), substrs[3].ParseToFloat());
			Vector rot(substrs[4].ParseToFloat(), substrs[5].ParseToFloat(), substrs[6].ParseToFloat());

			// Insert the bone
			StopAllThreads();

			Int32 parentid = (*m_skeleton)[id]->GetParentId();
			if (parentid == -1)
			{
				doc->InsertObject((*m_skeleton)[id]->GetBone(), parent, nullptr);
			}
			else
			{
				doc->InsertObject((*m_skeleton)[id]->GetBone(), (*m_skeleton)[parentid]->GetBone(), nullptr);
			}

			Matrix mat = HPBToMatrix(rot, ROTATIONORDER_XYZLOCAL);
			mat = ~mat; // invert the matrix to make euler angles local
			mat.off = pos;
			(*m_skeleton)[id]->SetLocalMatrix(mat);

			it++;
		}

		return (it == data->size()) ? false : true;
	}
}

Bool RegisterSMDLoader()
{
	return RegisterSceneLoaderPlugin(SMD_IMPORT_ID, GeLoadString(IDS_SMD), 0, ST::SMDLoader::Alloc, 0, nullptr);
}