// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "AGRLoader.h"

namespace ST
{
	Bool AGRLoader::Identify(BaseSceneLoader *node, const Filename &name, UChar *probe, Int32 size)
	{
		if (!probe || size < 18)
			return false;

		Int32 v1 = *(probe + 14);
		Char *c = (Char*)probe;
		String header(c);
		if (header != "afxGameRecord")
			return false;
		if (v1 != 4)
		{
			MessageDialog(GeLoadString(IDS_AGR_BAD_VERSION)
				+ String::IntToString(Int32(v1)) + GeLoadString(IDS_AGR_BAD_VERSION_1));
			return false;
		}

		return true;
	}

	FILEERROR AGRLoader::Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, String* error, BaseThread* bt)
	{
		frame = -1;

		AutoAlloc<BaseFile> file;
		file->Open(name, FILEOPEN_READ, FILEDIALOG_NONE, BYTEORDER_INTEL);
		if (!file)
			return file->GetError();

		m_FreeHandles = NewObj(std::vector<ModelHandle*>);

		AGRSettings settings;
		settings.RootModelDir = node->GetData().GetFilename(AGR_LOADER_ASSET_PATH);

		// skip header
		file->Seek(18, FILESEEK_START);

		BasePlugin *plug = FindPlugin(SMD_IMPORT_ID, PLUGINTYPE_SCENELOADER);
		BaseList2D *importer;

		plug->Message(MSG_RETRIEVEPRIVATEDATA, &importer);
		BaseContainer *pdata = importer->GetDataInstance();

		pdata->SetBool(SMD_IMPORT_QC, true);
		pdata->SetBool(SMD_CACHE_MEMORY, true);
		pdata->SetBool(SMD_IMPORT_IK, false);
		pdata->SetBool(SMD_IMPORT_MESH, true);
		pdata->SetFloat(SMD_LOADER_SCALE, 1.0);
		pdata->SetVector(SMD_LOADER_ROTATE, Vector(0, 0, 0));
		pdata->SetBool(SMD_LOADER_SWAPYZ, false);

		Int32 ModelIt = 1;
		while (true)
		{
			if (file->GetPosition() >= file->GetLength() - 1)
				break;

			Float32 Progress = static_cast<Float32>(file->GetPosition()) / file->GetLength();
			StatusSetBar(Int32(Progress * 100));
			StatusSetText("Progress: " + String::FloatToString(Progress * 100) + "%");

			String cmd = ReadFromDictionary(file);

			if (cmd == "afxFrame")
			{
				frame++;
				Float32 v;
				file->ReadFloat32(&v);
				if (m_time[0] == -1)
				{
					m_time[0] = v;
				}
				else
				{
					m_time[1] = v;
				}
				
				Int32 HiddenOffset;
				file->ReadInt32(&HiddenOffset);
				Int64 CurrentOffset = file->GetPosition();

				if (HiddenOffset != 0)
				{
					file->Seek(HiddenOffset - 4, FILESEEK_RELATIVE);
					Int32 NumHidden;
					file->ReadInt32(&NumHidden);
					for (Int32 i = 0; i < NumHidden; i++)
					{
						Int32 h;
						file->ReadInt32(&h);
						m_hiddenHandles.emplace(h);
					}
					file->Seek(CurrentOffset, FILESEEK_START);
				}
			}
			else if (cmd == "entity_state")
			{
				Int32 EntityHandle;
				file->ReadInt32(&EntityHandle);
				Bool NewHandle;

				ModelHandle *handle;
				auto it = m_handles.find(EntityHandle);
				if (it != m_handles.end())
				{
					handle = it->second;
					NewHandle = false;
				}
				else
				{
					// New Handle
					handle = NewObj(ModelHandle);
					m_handles[EntityHandle] = handle;
					NewHandle = true;
				}

				cmd = ReadFromDictionary(file);
				if (cmd == "baseentity")
				{
					Filename Model;
					Model = ReadFromDictionary(file);

					// Model changed
					if (Model != handle->Model)
					{
						Bool found = false;
						// Check if there's an unused model we can use
						for (Int32 i = 0; i < m_FreeHandles->size(); i++)
						{
							if ((*m_FreeHandles)[i]->Model == Model)
							{
								handle->Model = (*m_FreeHandles)[i]->Model;
								handle->Skeleton = (*m_FreeHandles)[i]->Skeleton;
								handle->m_skeleton = (*m_FreeHandles)[i]->m_skeleton;
								m_FreeHandles->erase(m_FreeHandles->begin() + i);
								found = true;
								break;
							}
						}
						// Didn't find an unused model
						if (!found)
						{
							handle->Model = Model;

							// Import the new model
							Model.ClearSuffix();
							pdata->SetString(SMD_CUSTOM_ROOT_NAME, "agr" + String::IntToString(ModelIt));
							Filename Full = settings.RootModelDir.GetString() + Model.GetString().SubStr(1, Model.GetString().GetLength() - 1).ToLower() + "/" + Model.GetFileString();
							Full.SetSuffix("qc");
							if (!MergeDocument(doc, Full, SCENEFILTER_OBJECTS | SCENEFILTER_MATERIALS | SCENEFILTER_MERGESCENE, nullptr))
							{
								String er = GeLoadString(IDS_NO_FILE) + Full.GetString() + GeLoadString(IDS_NO_FILE_0);
								*error = er;
								return FILEERROR_READ;
							}

							// Build the skeleton cache
							handle->BuildSkeletonCache(Full);

							// Find the newly imported skeleton
							BaseObject *root = doc->SearchObject("agr" + String::IntToString(ModelIt));
							handle->Skeleton = ST::Parse::FindChild(root, "skeleton");
							ModelIt++;
						}
					}
					
					CTrack *xP = handle->Skeleton->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
						DescLevel(VECTOR_X, DTYPE_REAL, 0)));
					if (xP == nullptr)
					{
						xP = CTrack::Alloc(handle->Skeleton, DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
							DescLevel(VECTOR_X, DTYPE_REAL, 0)));
						handle->Skeleton->InsertTrackSorted(xP);
					}

					CTrack *yP = handle->Skeleton->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
						DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
					if (yP == nullptr)
					{
						yP = CTrack::Alloc(handle->Skeleton, DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
							DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
						handle->Skeleton->InsertTrackSorted(yP);
					}

					CTrack *zP = handle->Skeleton->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
						DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
					if (zP == nullptr)
					{
						zP = CTrack::Alloc(handle->Skeleton, DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
							DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
						handle->Skeleton->InsertTrackSorted(zP);
					}

					CTrack *xR = handle->Skeleton->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
						DescLevel(VECTOR_X, DTYPE_REAL, 0)));
					if (xR == nullptr)
					{
						xR = CTrack::Alloc(handle->Skeleton, DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
							DescLevel(VECTOR_X, DTYPE_REAL, 0)));
						handle->Skeleton->InsertTrackSorted(xR);
					}

					CTrack *yR = handle->Skeleton->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
						DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
					if (yR == nullptr)
					{
						yR = CTrack::Alloc(handle->Skeleton, DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
							DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
						handle->Skeleton->InsertTrackSorted(yR);
					}

					CTrack *zR = handle->Skeleton->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
						DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
					if (zR == nullptr)
					{
						zR = CTrack::Alloc(handle->Skeleton, DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
							DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
						handle->Skeleton->InsertTrackSorted(zR);
					}

					CCurve *xPC = xP->GetCurve();
					CCurve *yPC = yP->GetCurve();
					CCurve *zPC = zP->GetCurve();
					CCurve *xRC = xR->GetCurve();
					CCurve *yRC = yR->GetCurve();
					CCurve *zRC = zR->GetCurve();

					Bool visible;
					file->ReadBool(&visible);
					Vector Pos = ReadVector(file, true);
					Vector Rot = ReadQAngle(file);

					BaseTime t = BaseTime(frame, doc->GetFps());

					CKey *xPKey = xPC->AddKey(t);
					xPKey->SetValue(xPC, Pos.x);
					CKey *yPKey = yPC->AddKey(t);
					yPKey->SetValue(yPC, Pos.y);
					CKey *zPKey = zPC->AddKey(t);
					zPKey->SetValue(zPC, Pos.z);
					CKey *xRKey = xRC->AddKey(t);
					xRKey->SetValue(xRC, Rot.x);
					CKey *yRKey = yRC->AddKey(t);
					yRKey->SetValue(yRC, Rot.y);
					CKey *zRKey = zRC->AddKey(t);
					zRKey->SetValue(zRC, Rot.z);
				}
				cmd = ReadFromDictionary(file);
				if (cmd == "baseanimating")
				{
					Bool bones;
					file->ReadBool(&bones);
					if (bones)
					{
						Int32 BCount;
						file->ReadInt32(&BCount);
						for (Int32 i = 0; i < BCount; i++)
						{
							
							BaseObject *bone = ST::Parse::FindChild(handle->Skeleton, (*handle->m_skeleton)[i]->GetName());
							Vector Pos = ReadVector(file);

							Quaternion quat = ReadQuaternion(file);

							Matrix m = quat.GetMatrix();

							Vector Rot;

							if (bone->GetUp()->GetName() == "skeleton")
							{
								Rot = MatrixToHPB(m, ROTATIONORDER_XYZGLOBAL);
								Float tX = Pos.x;
								Pos.x = -Pos.y;
								Pos.y = tX;

								Rot.y = -Rot.y;
								Rot.z = -Rot.z - PI / 2;
							}
							else
							{
								Rot = MatrixToHPB(m, ROTATIONORDER_YXZGLOBAL);
								Float tX = Rot.x;
								Rot.x = Rot.y;
								Rot.y = tX;
								Rot.z = -Rot.z;
							}

							CTrack *xP = bone->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_X, DTYPE_REAL, 0)));
							if (xP == nullptr)
							{
								xP = CTrack::Alloc(bone, DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
									DescLevel(VECTOR_X, DTYPE_REAL, 0)));
								bone->InsertTrackSorted(xP);
							}

							CTrack *yP = bone->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
							if (yP == nullptr)
							{
								yP = CTrack::Alloc(bone, DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
									DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
								bone->InsertTrackSorted(yP);
							}

							CTrack *zP = bone->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
							if (zP == nullptr)
							{
								zP = CTrack::Alloc(bone, DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
									DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
								bone->InsertTrackSorted(zP);
							}

							CTrack *xR = bone->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_X, DTYPE_REAL, 0)));
							if (xR == nullptr)
							{
								xR = CTrack::Alloc(bone, DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
									DescLevel(VECTOR_X, DTYPE_REAL, 0)));
								bone->InsertTrackSorted(xR);
							}

							CTrack *yR = bone->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
							if (yR == nullptr)
							{
								yR = CTrack::Alloc(bone, DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
									DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
								bone->InsertTrackSorted(yR);
							}

							CTrack *zR = bone->FindCTrack(DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
							if (zR == nullptr)
							{
								zR = CTrack::Alloc(bone, DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
									DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
								bone->InsertTrackSorted(zR);
							}

							CCurve *xPC = xP->GetCurve();
							CCurve *yPC = yP->GetCurve();
							CCurve *zPC = zP->GetCurve();
							CCurve *xRC = xR->GetCurve();
							CCurve *yRC = yR->GetCurve();
							CCurve *zRC = zR->GetCurve();

							BaseTime t = BaseTime(frame, doc->GetFps());

							CKey *xPKey = xPC->AddKey(t);
							xPKey->SetValue(xPC, Pos.x);
							CKey *yPKey = yPC->AddKey(t);
							yPKey->SetValue(yPC, Pos.y);
							CKey *zPKey = zPC->AddKey(t);
							zPKey->SetValue(zPC, Pos.z);
							CKey *xRKey = xRC->AddKey(t);
							xRKey->SetValue(xRC, Rot.x);
							CKey *yRKey = yRC->AddKey(t);
							yRKey->SetValue(yRC, Rot.y);
							CKey *zRKey = zRC->AddKey(t);
							zRKey->SetValue(zRC, Rot.z);
						}
					}
				}
				cmd = ReadFromDictionary(file);
				Bool vm;
				file->ReadBool(&vm);
			}
			else if (cmd == "afxCam")
			{
				Vector pos = ReadVector(file, true);
				Vector rot = ReadQAngle(file);
				Float32 fov;
				file->ReadFloat32(&fov);
				CamPos.push_back(pos);
				CamRot.push_back(rot);
				CamFov.push_back(fov);
			}
			else if (cmd == "deleted")
			{
				Int32 handle;
				file->ReadInt32(&handle);
				m_deletedHandles.emplace(handle);
			}
			else if (cmd == "afxHidden")
			{
				Int32 HCount, handle;
				file->ReadInt32(&HCount);
				for (Int32 i = 0; i < HCount; i++)
					file->ReadInt32(&handle);
			}
			else if (cmd == "afxFrameEnd")
			{
				// nada
			}
		}

		StatusClear();
		file->Close();

		return FILEERROR_NONE;
	}

	void AGRLoader::AddToDictionary(const String &value)
	{
		String s(value);
		m_dictionary[(Int32)m_dictionary.size()] = s;
	}

	String AGRLoader::ReadFromDictionary(BaseFile &file)
	{
		Int32 KeyWrd;
		String cmd;
		file.ReadInt32(&KeyWrd);
		if (KeyWrd != -1)
		{
			std::map<Int32, String>::iterator it = m_dictionary.find(KeyWrd);
			if (it != m_dictionary.end())
			{
				cmd = it->second;
				return cmd;
			}
		}
		else
		{
			Char *c = NewMem(Char, 512);
			for (Int32 i = 0; i < 512; i++)
			{
				Char ct;
				file.ReadChar(&ct);
				*(c + i) = ct;
				if (ct == '\0')
					break;
			}
			AddToDictionary(c);
			cmd = String(c);
			DeleteMem(c);
			return cmd;
		}
		GePrint("C4DST -- Bad Dictionary Reference at " + String::HexToString(UInt64(file.GetPosition())));
		return String("BAD");
	}

	Vector AGRLoader::ReadVector(BaseFile &file, Bool quakeformat)
	{
		Float32 x, y, z;
		file.ReadFloat32(&x);
		file.ReadFloat32(&y);
		file.ReadFloat32(&z);

		if (isinf(x) || isinf(y) || isinf(z))
		{
			x = 0; y = 0; z = 0;
		}

		return quakeformat ? Vector(-y, z, x) : Vector(x, y, -z);
	}

	Vector AGRLoader::ReadQAngle(BaseFile &file)
	{
		auto test = file.GetPosition();
		Float32 x, y, z;
		file.ReadFloat32(&x);
		file.ReadFloat32(&y);
		file.ReadFloat32(&z);
		x = DegToRad(x); y = DegToRad(y); z = DegToRad(z);

		if (isinf(x) || isinf(y) || isinf(z))
		{
			x = 0; y = 0; z = 0;
		}

		return Vector(x, y, z);
	}

	Quaternion AGRLoader::ReadQuaternion(BaseFile &file)
	{
		Float32 x, y, z, w;
		file.ReadFloat32(&x);
		file.ReadFloat32(&y);
		file.ReadFloat32(&z);
		file.ReadFloat32(&w);

		if (isinf(w) || isinf(x) || isinf(y) || isinf(z))
		{
			w = 0; x = 0; y = 0; z = 0;
		}

		Quaternion r;
		r.w = w;
		r.v = Vector64(x, y, z);
		return r;
	}

	void ModelHandle::BuildSkeletonCache(Filename qc)
	{
		AutoAlloc<BaseFile> file;
		file->Open(qc);

		// Find the first smd
		Int64 i = 0;
		Filename SMD;
		while (i < file->GetLength())
		{
			String line = ST::Parse::ReadLine(file);
			i = file->GetPosition();
			if (line == "")
				continue;
			std::vector<String> lines = ST::Parse::split(line);

			if (lines[0] == "$body")
			{
				String r = lines[2];
				ST::Parse::StripString(r);
				SMD = r;
				break;
			}
			if (lines[0] == "$bodygroup")
			{
				ST::Parse::ReadLine(file);
				line = ST::Parse::ReadLine(file);
				lines = ST::Parse::split(line);
				String r = lines[1];
				ST::Parse::StripString(r);
				SMD = r;
				break;
			}
		}

		file->Close();

		qc.SetFile(SMD);

		file->Open(qc);
		// find nodes
		String line = "";
		while (line != "nodes")
			line = ST::Parse::ReadLine(file);

		line = ST::Parse::ReadLine(file);
		// Fill data
		while (line != "end")
		{
			std::vector<String> sub = ST::Parse::split(line);
			Int32 id = sub[0].ParseToInt32();
			String name = sub[1]; ST::Parse::StripString(name);
			Int32 pid = sub[2].ParseToInt32();

			ST::SourceSkeletonBone *newBone = NewObj(ST::SourceSkeletonBone, id, name, pid);
			m_skeleton->push_back(newBone);

			line = ST::Parse::ReadLine(file);
		}
	}
}

Bool RegisterAGRLoader()
{
	return RegisterSceneLoaderPlugin(AGR_IMPORT_ID, GeLoadString(IDS_AGR), 0, ST::AGRLoader::Alloc, "fagrloader", nullptr);
}