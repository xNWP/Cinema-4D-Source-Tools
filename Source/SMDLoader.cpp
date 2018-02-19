// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "SMDLoader.h"

namespace ST
{
	Bool SMDLoader::Init(GeListNode* node)
	{
		BaseContainer *data = ((BaseList2D*)node)->GetDataInstance();
		data->SetData(SMD_LOADER_SCALE, GeData(Float32(1.0)));
		data->SetData(SMD_IMPORT_ANIMATION, GeData(Bool(true)));
		data->SetData(SMD_IMPORT_MESH, GeData(Bool(true)));
		
		return true;
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
		if (!file)
			return file->GetError();

		// get options
		Float smdScale = node->GetData().GetFloat(SMD_LOADER_SCALE, 1.0);
		Bool animate = node->GetData().GetBool(SMD_IMPORT_ANIMATION, 1);
		
		// read data into byte array and seperate it into lines.
		Char *fileData = NewMem(Char, file->GetLength());
		file->ReadBytes(fileData, file->GetLength());
		std::vector<String> *fileLineData = ST::Parse::ParseLines(fileData);
		DeleteMem(fileData);

		BaseObject *topNull = BaseObject::Alloc(Onull);
		topNull->SetName(name.GetFileString());
		doc->InsertObject(topNull, nullptr, nullptr);

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
				if (!ParseSkeleton(fileLineData, doc, filterflags, topNull, smdScale, animate, i))
				{
					*error = GeLoadString(IDS_CRITICAL_ERROR);
					return FILEERROR_READ;
				}
			}
		}

		file->Close();
		DeleteObj(fileLineData);
		DeletePtrVector(m_skeleton);

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

			ST::SourceSkeletonBone *bone = NewObj(ST::SourceSkeletonBone, id, parentid);
			bone->SetName(name);
			if (m_skeleton == nullptr)
				m_skeleton = NewObj(std::vector<ST::SourceSkeletonBone*>);
			m_skeleton->push_back(bone);

			it++;
		}

		return (it == data->size()) ? false : true;
	}

	Bool SMDLoader::ParseSkeleton(const std::vector<String> *data, BaseDocument *doc, SCENEFILTER flags, BaseObject *parent, const Float &scale, const Bool &animate, Int32 &it)
	{
		it++;

		Int32 frame = -1;
		CTrack *xPtrack=NULL, *yPtrack=NULL, *zPtrack=NULL;
		CTrack *xRtrack=NULL, *yRtrack=NULL, *zRtrack=NULL;
		CCurve *xPos=NULL, *yPos=NULL, *zPos=NULL;
		CCurve *xRot=NULL, *yRot=NULL, *zRot=NULL;

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

			if (substrs[0] == "time")
			{
				frame = substrs[1].ParseToInt32();
				it++;
				continue;
			}

			Int32 id = substrs[0].ParseToInt32();
			Vector pos(substrs[1].ParseToFloat(), substrs[2].ParseToFloat(), substrs[3].ParseToFloat());
			pos *= scale;
			Vector rot(substrs[4].ParseToFloat(), substrs[5].ParseToFloat(), substrs[6].ParseToFloat());

			// Insert the bone
			StopAllThreads();

			if (frame == 0)
			{
				Int32 parentid = (*m_skeleton)[id]->GetParentId();
				if (parentid == -1)
				{
					doc->InsertObject((*m_skeleton)[id]->GetBone(), parent, nullptr);
				}
				else
				{
					doc->InsertObject((*m_skeleton)[id]->GetBone(), (*m_skeleton)[parentid]->GetBone(), nullptr);
				}

				xPtrack = CTrack::Alloc((*m_skeleton)[id]->GetBone(),
					DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
					DescLevel(VECTOR_X, DTYPE_REAL, 0)));
				yPtrack = CTrack::Alloc((*m_skeleton)[id]->GetBone(),
					DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
					DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
				zPtrack = CTrack::Alloc((*m_skeleton)[id]->GetBone(),
					DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
					DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
				xRtrack = CTrack::Alloc((*m_skeleton)[id]->GetBone(),
					DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
					DescLevel(VECTOR_X, DTYPE_REAL, 0)));
				yRtrack = CTrack::Alloc((*m_skeleton)[id]->GetBone(),
					DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
					DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
				zRtrack = CTrack::Alloc((*m_skeleton)[id]->GetBone(),
					DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
					DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
				(*m_skeleton)[id]->GetBone()->InsertTrackSorted(xPtrack);
				(*m_skeleton)[id]->GetBone()->InsertTrackSorted(yPtrack);
				(*m_skeleton)[id]->GetBone()->InsertTrackSorted(zPtrack);
				(*m_skeleton)[id]->GetBone()->InsertTrackSorted(xRtrack);
				(*m_skeleton)[id]->GetBone()->InsertTrackSorted(yRtrack);
				(*m_skeleton)[id]->GetBone()->InsertTrackSorted(zRtrack);
				(*m_skeleton)[id]->SetXPTrack(xPtrack);
				(*m_skeleton)[id]->SetYPTrack(yPtrack);
				(*m_skeleton)[id]->SetZPTrack(zPtrack);
				(*m_skeleton)[id]->SetXRTrack(xRtrack);
				(*m_skeleton)[id]->SetYRTrack(yRtrack);
				(*m_skeleton)[id]->SetZRTrack(zRtrack);
			}

			xPos = (*m_skeleton)[id]->GetXPTrack()->GetCurve();
			yPos = (*m_skeleton)[id]->GetYPTrack()->GetCurve();
			zPos = (*m_skeleton)[id]->GetZPTrack()->GetCurve();
			xRot = (*m_skeleton)[id]->GetXRTrack()->GetCurve();
			yRot = (*m_skeleton)[id]->GetYRTrack()->GetCurve();
			zRot = (*m_skeleton)[id]->GetZRTrack()->GetCurve();

			Int32 fps = doc->GetFps();

			Matrix mat = HPBToMatrix(rot, ROTATIONORDER_XYZLOCAL);
			mat = ~mat; // invert the matrix to make euler angles local
			mat.off = pos;
			Vector finalRot = MatrixToHPB(mat, ROTATIONORDER_HPB);

			CKey *xPKey = xPos->AddKey(BaseTime(frame, fps));
			xPKey->SetValue(xPos, mat.off.x);
			CKey *yPKey = yPos->AddKey(BaseTime(frame, fps));
			yPKey->SetValue(yPos, mat.off.y);
			CKey *zPKey = zPos->AddKey(BaseTime(frame, fps));
			zPKey->SetValue(zPos, mat.off.z);
			CKey *xRKey = xRot->AddKey(BaseTime(frame, fps));
			xRKey->SetValue(xRot, finalRot.x);
			CKey *yRKey = yRot->AddKey(BaseTime(frame, fps));
			yRKey->SetValue(yRot, finalRot.y);
			CKey *zRKey = zRot->AddKey(BaseTime(frame, fps));
			zRKey->SetValue(zRot, finalRot.z);

			EventAdd();

			it++;

			if (!animate && id == m_skeleton->size() - 1)
				break;
		}

		// if we're not merging and we have animation, set the start & end accordingly
		if (((flags & SCENEFILTER_MERGESCENE) != SCENEFILTER_MERGESCENE)
			&& animate && frame > 0)
		{
			doc->SetMaxTime(BaseTime(frame + 1, doc->GetFps()));
			doc->SetLoopMaxTime(BaseTime(frame + 1, doc->GetFps()));
		}

		return (it == data->size()) ? false : true;
	}
}

Bool RegisterSMDLoader()
{
	return RegisterSceneLoaderPlugin(SMD_IMPORT_ID, GeLoadString(IDS_SMD), 0, ST::SMDLoader::Alloc, "fsmdloader", nullptr);
}