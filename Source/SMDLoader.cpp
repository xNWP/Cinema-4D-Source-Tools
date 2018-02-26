// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "SMDLoader.h"

namespace ST
{
	Bool SMDLoader::Init(GeListNode *node)
	{
		// Default settings, overriden by user-prefs
		BaseContainer *data = ((BaseList2D*)node)->GetDataInstance();
		data->SetFloat(SMD_LOADER_SCALE, 1.0);
		data->SetVector(SMD_LOADER_ROTATE, Vector(0, 0, 0));
		data->SetBool(SMD_IMPORT_ANIMATION, true);
		data->SetBool(SMD_IMPORT_MESH, true);
		data->SetBool(SMD_IMPORT_QC, true);
		data->SetBool(SMD_IMPORT_MESH_WELD, true);
		data->SetFloat(SMD_IMPORT_MESH_WELD_TOLERANCE, 0.01);
		data->SetBool(SMD_IMPORT_MESH_MATERIALS, true);
		data->SetBool(SMD_IMPORT_MESH_NORMALS, true);
		data->SetBool(SMD_IMPORT_MESH_UV, true);
		data->SetBool(SMD_IMPORT_IK, true);
		data->SetInt32(SMD_IMPORT_IK_ORIENTATION, IK_CAMERA);
		data->SetBool(SMD_IMPORT_MESH_WEIGHTS, true);

		return true;
	}

	Bool SMDLoader::GetDParameter(GeListNode *node, const DescID &id, GeData &t_data, DESCFLAGS_GET &flags)
	{
		// Override settings here based on state
		if (!node)
			return false;

		BaseContainer *data = ((BaseList2D*)node)->GetDataInstance();
		switch (id[0].id)
		{
			case SMD_IMPORT_QC:
			{
				if (m_qc_file)
					data->SetBool(SMD_IMPORT_QC, true);
				return true;
			}
		}

		return SceneLoaderData::GetDParameter(node, id, t_data, flags);
	}

	Bool SMDLoader::GetDEnabling(GeListNode *node, const DescID &id, const GeData &t_data, DESCFLAGS_ENABLE flags, const BaseContainer *itemdesc)
	{
		if (!node)
			return false;

		switch (id[0].id)
		{
			case SMD_IMPORT_MESH_WELD:
			case SMD_IMPORT_MESH_WELD_TOLERANCE:
			case SMD_IMPORT_MESH_MATERIALS:
			case SMD_IMPORT_MESH_NORMALS:
			case SMD_IMPORT_MESH_UV:
			case SMD_IMPORT_MESH_WEIGHTS:
			{
				GeData data;
				node->GetParameter(SMD_IMPORT_MESH, data, DESCFLAGS_GET_0);
				if (data.GetBool())
				{
					if (id[0].id == SMD_IMPORT_MESH_WELD_TOLERANCE)
					{
						node->GetParameter(SMD_IMPORT_MESH_WELD, data, DESCFLAGS_GET_0);
						if (!data.GetBool())
							return false;
					}
					return true;
				}
				else
				{
					return false;
				}
			}

			// TO-DO: find a way to check if we're in the pref dialog
			//		  and re-enable qc in there.
			case SMD_IMPORT_QC:
			{
				if (m_qc_file)
					return false;
				else
					return true;
			}

			case SMD_IMPORT_IK:
			case SMD_IMPORT_IK_ORIENTATION:
			{
				GeData data;
				node->GetParameter(SMD_IMPORT_QC, data, DESCFLAGS_GET_0);
				if (data.GetBool())
					return true;
				else
					return false;
			}

			case SMD_IMPORT_MATERIAL_ROOT:
			{
				GeData dataqc;
				node->GetParameter(SMD_IMPORT_QC, dataqc, DESCFLAGS_GET_0);
				GeData datamat;
				node->GetParameter(SMD_IMPORT_MESH_MATERIALS, datamat, DESCFLAGS_GET_0);
				if (!dataqc.GetBool())
					return false;
				else if (datamat.GetBool())
					return true;
				else
					return false;
			}
		}
		
		// call parent
		return SceneLoaderData::GetDEnabling(node, id, t_data, flags, itemdesc);
	}

	Bool SMDLoader::Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size)
	{
		// unfortunately SMD/QC is an ascii format so we will just assume
		// that the file-type is SMD/QC based on the extension alone.
		m_qc_file = false;

		if (name.GetSuffix().ToLower() == "qc")
		{
			m_qc_file = true;
			return true;
		}

		return name.GetSuffix().ToLower() == "smd" ? true : false;
	}

	FILEERROR SMDLoader::Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, String* error, BaseThread* bt)
	{
		// set timer
		start = std::chrono::system_clock::now();

		// get options
		SMDLoaderSettings settings;
		settings.scale = node->GetData().GetFloat(SMD_LOADER_SCALE, 1.0);
		settings.orientation = node->GetData().GetVector(SMD_LOADER_ROTATE, Vector(0, 0, 0));
		settings.animation = node->GetData().GetBool(SMD_IMPORT_ANIMATION, 1);
		settings.mesh = node->GetData().GetBool(SMD_IMPORT_MESH, 1);
		settings.qc = node->GetData().GetBool(SMD_IMPORT_QC, 1);
		settings.mesh_weld = node->GetData().GetBool(SMD_IMPORT_MESH_WELD, 1);
		settings.mesh_weld_tolerance = node->GetData().GetFloat(SMD_IMPORT_MESH_WELD_TOLERANCE, 0.01);
		settings.mesh_materials = node->GetData().GetBool(SMD_IMPORT_MESH_MATERIALS, 1);
		settings.mesh_normals = node->GetData().GetBool(SMD_IMPORT_MESH_NORMALS, 1);
		settings.mesh_uv = node->GetData().GetBool(SMD_IMPORT_MESH_UV, 1);
		settings.mesh_weights = node->GetData().GetBool(SMD_IMPORT_MESH_WEIGHTS, 1);
		settings.material_root = node->GetData().GetFilename(SMD_IMPORT_MATERIAL_ROOT);
		settings.ik = node->GetData().GetBool(SMD_IMPORT_IK, 1);
		settings.ik_orientation = node->GetData().GetInt32(SMD_IMPORT_IK_ORIENTATION, IK_XZ);

		Filename nameNoSuffix = name;
		nameNoSuffix.ClearSuffix();
		BaseObject *topNull = BaseObject::Alloc(Onull);
		topNull->SetName(nameNoSuffix.GetFileString());
		doc->InsertObject(topNull, nullptr, nullptr);

		FILEERROR res;
		if (settings.qc)
		{
			res = ParseQC(name, settings, doc, topNull, filterflags, error);
		}
		else
		{
			res = ParseSMD(name, settings, doc, topNull, filterflags, error, true);
		}

		// Rotation
		Matrix mat = topNull->GetMg();
		Matrix RotMat = HPBToMatrix(settings.orientation, ROTATIONORDER_HPB);
		mat = RotMat * mat;
		topNull->SetMg(mat);

		return res;
	}

	FILEERROR SMDLoader::ParseQC(const Filename &name, SMDLoaderSettings &settings, BaseDocument *doc, BaseObject *parent, SCENEFILTER filterflags, String *error)
	{
		// TO-DO:	VTA animation
		//			Attachments

		Filename CorrectFile = name;
		if (name.CheckSuffix("smd"))
			CorrectFile.SetSuffix("qc");

		AutoAlloc<BaseFile> file;
		Bool fres = file->Open(CorrectFile);
		if (!fres)
		{
			if (!m_qc_file) // User selected qc-file but none found, just default to the smd
			{
				GePrint(name.GetFileString() + ": " + GeLoadString(IDS_NO_QC));
				settings.qc = false;
				return ParseSMD(name, settings, doc, parent, filterflags, error, true);
			}
			else
				return file->GetError();
		}

		Filename nameNoSuffix = CorrectFile;
		nameNoSuffix.ClearSuffix();

		// read data into byte array and seperate it into lines.
		Char *fileData = NewMem(Char, file->GetLength());
		file->ReadBytes(fileData, file->GetLength());
		std::vector<String> *fileLineData = ST::Parse::ParseLines(fileData);
		DeleteMem(fileData);

		QCFile NewQC;

		for (Int32 it = 0; it < fileLineData->size(); it++) // for each line
		{
			std::vector<String> *substrs = ST::Parse::split((*fileLineData)[it]);

			if (substrs->size() == 0)
			{
				DeleteObj(substrs);
				continue;
			}
			else if ((*substrs)[0] == "$body")
			{
				NewQC.body.push_back((*substrs)[2].SubStr(1, (*substrs)[2].GetLength() - 2));
			}
			else if ((*substrs)[0] == "$bodygroup")
			{
				QCBodyGroup newBodyGroup;
				newBodyGroup.name = (*substrs)[1].SubStr(1, (*substrs)[1].GetLength() - 2);
				for (Int32 j = it + 1; (*fileLineData)[j] != "}"; j++)
				{
					std::vector<String> *line = ST::Parse::split((*fileLineData)[j]);
					if ((*line)[0] == "studio")
					{
						newBodyGroup.mesh.push_back((*line)[1].SubStr(1, (*line)[1].GetLength() - 2));
					}
					DeleteObj(line);
					it = j + 1;
				}
				NewQC.bodygroup.push_back(newBodyGroup);
			}
			else if ((*substrs)[0] == "$cdmaterials")
			{
				if ((*substrs)[1].GetLength() > 2)
					NewQC.cdmaterials.push_back((*substrs)[1].SubStr(1, (*substrs)[1].GetLength() - 2));
			}
			else if ((*substrs)[0] == "$ikchain")
			{
				IKDecl newChain;
				String name = (*substrs)[1].SubStr(1, (*substrs)[1].GetLength() - 2); // name
				String bone = (*substrs)[2].SubStr(1, (*substrs)[2].GetLength() - 2); // lock name
				newChain.name = name;
				newChain.bone = bone;
				NewQC.ikchain.push_back(newChain);
			}

			DeleteObj(substrs);
		}

		file->Close();
		DeleteObj(fileLineData);

		settings.qc_file = NewQC;

		// Build Body Mesh(s)
		Bool BuildSkeleton = true;
		for (Int32 bo = 0; bo < NewQC.body.size(); bo++)
		{
			String filepath = name.GetDirectory().GetString() + "\\" + NewQC.body[bo];
			Filename filename(filepath);
			FILEERROR res = ParseSMD(filename, settings, doc, parent, filterflags, error, BuildSkeleton);
			if (res != FILEERROR_NONE)
				return res;
			BuildSkeleton = false;
		}

		// Build BodyGroup Mesh(s)
		for (Int32 bg = 0; bg < NewQC.bodygroup.size(); bg++)
		{
			for (Int32 bgi = 0; bgi < NewQC.bodygroup[bg].mesh.size(); bgi++)
			{
				String filepath = name.GetDirectory().GetString() + "\\" + NewQC.bodygroup[bg].mesh[bgi];
				Filename filename(filepath);
				FILEERROR res = ParseSMD(filename, settings, doc, parent, filterflags, error, BuildSkeleton);
				if (res != FILEERROR_NONE)
					return res;
				BuildSkeleton = false;
			}
		}
		
		// Build IK-Chain's
		if (settings.ik && NewQC.ikchain.size() > 0)
		{
			BaseObject *ik_null = BaseObject::Alloc(Onull);
			ik_null->SetName("ik_goal");
			doc->InsertObject(ik_null, parent, nullptr);
			for (Int32 ik = 0; ik < NewQC.ikchain.size(); ik++) // for each link
			{
				// Search through bones for the named bone
				for (Int32 bone = 0; bone < m_skeleton->size(); bone++)
				{
					if ((*m_skeleton)[bone]->GetName() == NewQC.ikchain[ik].bone)
					{
						BaseObject *targ = (*m_skeleton)[bone]->GetBone();
						BaseObject *root = targ->GetUp()->GetUp();
						BaseObject *ik_target = BaseObject::Alloc(Onull);
						ik_target->SetName(NewQC.ikchain[ik].name);
						ik_target->SetParameter(DescID(NULLOBJECT_DISPLAY), NULLOBJECT_DISPLAY_STAR, DESCFLAGS_SET_0);
						ik_target->SetParameter(DescID(NULLOBJECT_RADIUS), Float(5.0), DESCFLAGS_SET_0);

						Int32 ikOr = settings.ik_orientation;
						if (ikOr == IK_CAMERA)
							ikOr = NULLOBJECT_ORIENTATION_SCREEN;
						else if (ikOr == IK_XY)
							ikOr = NULLOBJECT_ORIENTATION_XY;
						else if (ikOr == IK_ZY)
							ikOr = NULLOBJECT_ORIENTATION_ZY;
						else if (ikOr == IK_XZ)
							ikOr = NULLOBJECT_ORIENTATION_XZ;
						ik_target->SetParameter(DescID(NULLOBJECT_ORIENTATION), ikOr, DESCFLAGS_SET_0);

						Matrix loc = (*m_skeleton)[bone]->GetRefMg();
						ik_target->SetMg(loc);
						doc->InsertObject(ik_target, ik_null, nullptr);

						BaseTag *ikTag = BaseTag::Alloc(Tik);
						root->InsertTag(ikTag);
						ikTag->SetParameter(DescID(ID_CA_IK_TAG_TIP), targ, DESCFLAGS_SET_0);
						ikTag->SetParameter(DescID(ID_CA_IK_TAG_TARGET), ik_target, DESCFLAGS_SET_0);
						ikTag->SetParameter(DescID(ID_CA_IK_TAG_SOLVER), ID_CA_IK_TAG_SOLVER_3D, DESCFLAGS_SET_0);

						// constraint on bone
						BaseTag *constraint = targ->MakeTag(Tconstraint);
						constraint->SetParameter(ID_CA_CONSTRAINT_TAG_PSR, true, DESCFLAGS_SET_0);
						constraint->SetParameter(ID_CA_CONSTRAINT_TAG_PSR_POSITION, false, DESCFLAGS_SET_0);
						constraint->SetParameter(ID_CA_CONSTRAINT_TAG_PSR_TARGET, ik_target, DESCFLAGS_SET_0);
						
						break;
					}
				}
			}
		}

		DeletePtrVector(m_skeleton);

		end = std::chrono::system_clock::now();
		std::chrono::duration<double> duration = end - start;
		GePrint(GeLoadString(IDS_LOADED_FILE)
			+ name.GetFileString() + GeLoadString(IDS_IN)
			+ String::FloatToString(duration.count()) + "s");

		return FILEERROR_NONE;
	}

	FILEERROR SMDLoader::ParseSMD(const Filename &name, const SMDLoaderSettings &settings, BaseDocument *doc, BaseObject *parent, SCENEFILTER filterflags, String* error, Bool BuildSkeleton)
	{
		AutoAlloc<BaseFile> file;
		file->Open(name);
		if (!file)
			return file->GetError();

		// read data into byte array and seperate it into lines.
		Char *fileData = NewMem(Char, file->GetLength());
		file->ReadBytes(fileData, file->GetLength());
		std::vector<String> *fileLineData = ST::Parse::ParseLines(fileData);
		DeleteMem(fileData);

		for (Int32 i = 0; i < fileLineData->size(); i++)
		{
			String line = (*fileLineData)[i];
			if (line == "nodes" && BuildSkeleton)
			{
				if (!ParseNodes(fileLineData, i))
				{
					*error = GeLoadString(IDS_CRITICAL_ERROR);
					return FILEERROR_READ;
				}
			}
			else if (line == "skeleton" && BuildSkeleton)
			{
				if (!ParseSkeleton(fileLineData, settings, doc, filterflags, parent, i))
				{
					*error = GeLoadString(IDS_CRITICAL_ERROR);
					return FILEERROR_READ;
				}
			}
			else if (line == "triangles" && settings.mesh)
			{
				Filename nameNoSuffix = name;
				nameNoSuffix.ClearSuffix();

				if (ParseTriangles(fileLineData, settings, nameNoSuffix.GetFileString(), doc, parent, i) != 0)
				{
					*error = GeLoadString(IDS_CRITICAL_ERROR) + ": triangle parse error.";
					return FILEERROR_READ;
				}
			}
		}

		file->Close();
		DeleteObj(fileLineData);

		if (!settings.qc) // qc will still need this
			DeletePtrVector(m_skeleton);

		if (!settings.qc)
		{
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> duration = end - start;
			GePrint(GeLoadString(IDS_LOADED_FILE)
				+ name.GetFileString() + GeLoadString(IDS_IN)
				+ String::FloatToString(duration.count()) + "s");
		}

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

	Bool SMDLoader::ParseSkeleton(const std::vector<String> *data, const SMDLoaderSettings &settings, BaseDocument *doc, SCENEFILTER flags, BaseObject *parent, Int32 &it)
	{
		it++;

		Int32 frame = -1;
		CTrack *xPtrack=NULL, *yPtrack=NULL, *zPtrack=NULL;
		CTrack *xRtrack=NULL, *yRtrack=NULL, *zRtrack=NULL;
		CCurve *xPos=NULL, *yPos=NULL, *zPos=NULL;
		CCurve *xRot=NULL, *yRot=NULL, *zRot=NULL;

		BaseObject *skelRoot = BaseObject::Alloc(Onull);
		skelRoot->SetName("skeleton");
		doc->InsertObject(skelRoot, parent, nullptr);

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
			Vector pos(substrs[1].ParseToFloat(), substrs[2].ParseToFloat(), -substrs[3].ParseToFloat());
			pos *= settings.scale;
			Vector rot(-substrs[4].ParseToFloat(), -substrs[5].ParseToFloat(), substrs[6].ParseToFloat());

			// Insert the bone
			StopAllThreads();

			if (frame == 0)
			{
				Int32 parentid = (*m_skeleton)[id]->GetParentId();
				if (parentid == -1)
				{
					doc->InsertObject((*m_skeleton)[id]->GetBone(), skelRoot, nullptr);
				}
				else
				{
					doc->InsertObject((*m_skeleton)[id]->GetBone(), (*m_skeleton)[parentid]->GetBone(), nullptr);
				}

				if (settings.animation)
				{
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
			}

			if (settings.animation)
			{
				xPos = (*m_skeleton)[id]->GetXPTrack()->GetCurve();
				yPos = (*m_skeleton)[id]->GetYPTrack()->GetCurve();
				zPos = (*m_skeleton)[id]->GetZPTrack()->GetCurve();
				xRot = (*m_skeleton)[id]->GetXRTrack()->GetCurve();
				yRot = (*m_skeleton)[id]->GetYRTrack()->GetCurve();
				zRot = (*m_skeleton)[id]->GetZRTrack()->GetCurve();				
			}

			Int32 fps = doc->GetFps();

			Matrix mat = HPBToMatrix(rot, ROTATIONORDER_XYZLOCAL);
			mat = ~mat; // invert the matrix to make euler angles local
			mat.off = pos;

			if (frame == 0)
			{
				// Set the reference position.
				(*m_skeleton)[id]->SetLocalMatrix(mat);
				Matrix GlobalMat = (*m_skeleton)[id]->GetBone()->GetMg();
				(*m_skeleton)[id]->SetRefMg(GlobalMat);
			}

			if (settings.animation)
			{
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
			}

			EventAdd();

			it++;

			if (!settings.animation && id == m_skeleton->size() - 1)
				break;
		}

		// delete tracks if only one frame
		if (frame == 0)
		{
			// this is admitedly sloppy and adds extra cycles,
			// however the effect is minimal, will likely create a class
			// that manages this more gracefully later on.
			for (Int32 i = 0; i < m_skeleton->size(); i++)
			{
				(*m_skeleton)[i]->GetBone()->GetCTrackRoot()->FlushAll();
			}
		}

		// if we're not merging and we have animation, set the start & end accordingly
		if (((flags & SCENEFILTER_MERGESCENE) != SCENEFILTER_MERGESCENE)
			&& settings.animation && frame > 0)
		{
			doc->SetMaxTime(BaseTime(frame + 1, doc->GetFps()));
			doc->SetLoopMaxTime(BaseTime(frame + 1, doc->GetFps()));
		}

		return (it == data->size()) ? false : true;
	}

	Int32 SMDLoader::ParseTriangles(const std::vector<String> *data, const SMDLoaderSettings &settings, const String &name, BaseDocument *doc, BaseObject *parent, Int32 &it)
	{
		Int32 tIt = it + 1; // skip the opening tag

		std::vector<ST::StudiomdlDataTriangle*> *triangles = NewObj(std::vector<ST::StudiomdlDataTriangle*>);
		
		// the new poly
		PolygonObject *newPoly = PolygonObject::Alloc(0, 0);
		AutoAlloc<Modeling> mod;
		newPoly->SetName(name);
		doc->InsertObject(newPoly, parent, nullptr);
		mod->InitObject(newPoly);
		std::map<Int32, String> m_polySelections;

		String CurrentMesh = (*data)[tIt];
		while ((*data)[tIt] != "end") // fill vector
		{
			Int32 error = 2;
			ST::StudiomdlDataTriangle *newTriangle = NewObj(ST::StudiomdlDataTriangle, data, tIt, error);
			if (error != 0)
				return error;

			triangles->push_back(newTriangle);

			if ((*data)[tIt] != CurrentMesh) // end of portion
			{
				m_polySelections.emplace((Int32(triangles->size()) - 1), CurrentMesh);
				CurrentMesh = (*data)[tIt];
			}
		}

		std::vector<Int32> index;
		Int32 PolyCount = Int32(triangles->size());

		for (Int32 p = 0; p < PolyCount; p++) // for each triangle
		{
			// z is flipped, build backwards to have proper front facing poly's
			index.push_back(mod->AddPoint(newPoly, (*triangles)[p]->GetPointC() * settings.scale));
			index.push_back(mod->AddPoint(newPoly, (*triangles)[p]->GetPointB() * settings.scale));
			index.push_back(mod->AddPoint(newPoly, (*triangles)[p]->GetPointA() * settings.scale));
			Int32 *padr = &index[index.size() - 3];
			mod->CreateNgon(newPoly, padr, 3);
		}

		mod->Commit(newPoly);

		// Normal tag
		if (settings.mesh_normals)
		{
			newPoly->MakeTag(Tphong);
			NormalTag *nTag = NormalTag::Alloc(PolyCount);
			newPoly->InsertTag(nTag);
			NormalHandle handle = nTag->GetDataAddressW();

			const CPolygon *CPolyArr = newPoly->GetPolygonR();
			for (Int32 i = 0; i < PolyCount; i++)
			{
				const CPolygon CPoly = *(CPolyArr + i);
				NormalStruct normals;
				normals.a = (*triangles)[i]->GetNormalC();
				normals.b = (*triangles)[i]->GetNormalB();
				normals.c = (*triangles)[i]->GetNormalA();
				NormalTag::Set(handle, i, normals);
			}
			newPoly->Message(MSG_UPDATE);
		}

		// Selection Tags
		BaseSelect *sel = newPoly->GetPolygonS();
		Int32 LastIndex = 0;
		for (auto j = m_polySelections.begin(); j != m_polySelections.end(); j++) // for each selection
		{
			sel->DeselectAll();
			Int32 h;
			for (h = LastIndex; h <= j->first; h++)
				sel->Select(h);
			LastIndex = h;

			SelectionTag *newSelTag = SelectionTag::Alloc(Tpolygonselection);
			newSelTag->SetName(j->second);
			newPoly->InsertTag(newSelTag);
			BaseSelect *tag_sel = newSelTag->GetBaseSelect();
			sel->CopyTo(tag_sel);
		}

		// UVW's
		if (settings.mesh_uv)
		{
			UVWTag *uvTag = UVWTag::Alloc(PolyCount);
			newPoly->InsertTag(uvTag);
			UVWHandle uvHandle = uvTag->GetDataAddressW();
			for (Int32 k = 0; k < PolyCount; k++)
			{
				UVWTag::Set(uvHandle, k, (*triangles)[k]->GetUVW());
			}
		}

		// Materials
		if (settings.mesh_materials)
		{
			BaseTag *polySel = newPoly->GetFirstTag();
			while (polySel)
			{
				if (polySel->GetType() != Tpolygonselection)
				{
					polySel = polySel->GetNext();
					continue;
				}
				TextureTag *newTag = TextureTag::Alloc();
				newPoly->InsertTag(newTag);

				Material *newMat = Material::Alloc();
				newMat->SetName(polySel->GetName());

				newMat->SetChannelState(CHANNEL_REFLECTION, false);
				newMat->SetParameter(MATERIAL_USE_REFLECTION, false, DESCFLAGS_SET_0);

				if (settings.qc)
				{
					HMODULE dll = LoadPluginDLL(VTFLIB_DLL);
					Filename MatRoot = settings.material_root;
					if (MatRoot.GetString() == "")
					{
						GePrint(newMat->GetName() + ": " + GeLoadString(IDS_NO_MAT_DIR));
					}
					else
					{	
						VTFLib::CVMTFile *vmt_file = NewObj(VTFLib::CVMTFile);
						String s_root_dir = settings.material_root.GetString() + "\\";
						for (Int32 cd = 0; cd < settings.qc_file.cdmaterials.size(); cd++) // iterate through material directories
						{
							String s_vmt_filename = s_root_dir + settings.qc_file.cdmaterials[cd] + newMat->GetName() +".vmt";
							Char *vmt_filename = NewMem(Char, s_vmt_filename.GetCStringLen() + 1);
							s_vmt_filename.GetCString(vmt_filename, s_vmt_filename.GetCStringLen() + 1);
							if (vmt_file->Load(vmt_filename))
							{
								DeleteMem(vmt_filename);
								VertexLitGeneric tmp = Parse::ParseVertexLitGeneric(vmt_file, settings.material_root);
								
								if (tmp.basetexture.Content())
								{
									Filename fullpath = Filename(settings.material_root.GetString() + tmp.basetexture.GetString().SubStr(1, tmp.basetexture.GetString().GetLength() - 1));
									BaseShader *sha = BaseShader::Alloc(Xbitmap);
									sha->SetParameter(BITMAPSHADER_FILENAME, fullpath, DESCFLAGS_SET_0);
									newMat->InsertShader(sha);
									newMat->SetParameter(MATERIAL_COLOR_SHADER, sha, DESCFLAGS_SET_0);
								}
								if (tmp.bumpmap.Content())
								{
									Filename fullpath = Filename(settings.material_root.GetString() + tmp.bumpmap.GetString().SubStr(1, tmp.bumpmap.GetString().GetLength() - 1));
									BaseShader *sha = BaseShader::Alloc(Xbitmap);
									sha->SetParameter(BITMAPSHADER_FILENAME, fullpath, DESCFLAGS_SET_0);
									newMat->InsertShader(sha);
									newMat->SetParameter(MATERIAL_NORMAL_SHADER, sha, DESCFLAGS_SET_0);
									newMat->SetChannelState(CHANNEL_NORMAL, true);
								}

								break;
							}
							else
								DeleteMem(vmt_filename);
						}
						DeleteObj(vmt_file);
					}
					UnloadPluginDLL(dll);
				}

				doc->InsertMaterial(newMat);

				newTag->SetMaterial(newMat);
				newTag->SetParameter(DescID(TEXTURETAG_RESTRICTION), polySel->GetName(), DESCFLAGS_SET_0);
				newTag->SetParameter(DescID(TEXTURETAG_PROJECTION), TEXTURETAG_PROJECTION_UVW, DESCFLAGS_SET_0);

				polySel = polySel->GetNext();
			}
		}

		// Weights
		if (settings.mesh_weights)
		{
			CAWeightTag *weightTag = CAWeightTag::Alloc();
			newPoly->InsertTag(weightTag);
			BaseObject *sObj = BaseObject::Alloc(Oskin);
			doc->InsertObject(sObj, newPoly, nullptr);

			// Add Joints
			for (Int32 i = 0; i < m_skeleton->size(); i++)
			{
				weightTag->AddJoint((*m_skeleton)[i]->GetBone());
			}

			// Weight Joints
			for (Int32 j = 0; j < triangles->size(); j++)
			{
				// C Point
				for (auto c = (*triangles)[j]->GetWeightsC().begin(); c != (*triangles)[j]->GetWeightsC().end(); c++)
				{
					Int32 pntindex = (j * 3);
					weightTag->SetWeight(c->first, pntindex, c->second);
				}

				// B Point
				for (auto b = (*triangles)[j]->GetWeightsB().begin(); b != (*triangles)[j]->GetWeightsB().end(); b++)
				{
					Int32 pntindex = (j * 3 + 1);
					weightTag->SetWeight(b->first, pntindex, b->second);
				}

				// A Point
				for (auto a = (*triangles)[j]->GetWeightsA().begin(); a != (*triangles)[j]->GetWeightsA().end(); a++)
				{
					Int32 pntindex = (j * 3 + 2);
					weightTag->SetWeight(a->first, pntindex, a->second);
				}
			}
		}

		// Weld similar points
		if (settings.mesh_weld)
		{
			BaseContainer bc;
			bc.SetFloat(MDATA_OPTIMIZE_TOLERANCE, settings.mesh_weld_tolerance);
			bc.SetBool(MDATA_OPTIMIZE_POINTS, true);
			ModelingCommandData cd;
			cd.doc = doc;
			cd.bc = &bc;
			cd.op = newPoly;
			SendModelingCommand(MCOMMAND_OPTIMIZE, cd);
		}

		DeletePtrVector(triangles);
		EventAdd();

		it = tIt;
		return 0;
	}
}

Bool RegisterSMDLoader()
{
	return RegisterSceneLoaderPlugin(SMD_IMPORT_ID, GeLoadString(IDS_SMD), 0, ST::SMDLoader::Alloc, "fsmdloader", nullptr);
}