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
		data->SetBool(SMD_IMPORT_TOP_NULL, true);
		data->SetBool(SMD_IMPORT_SKELETON_JOINT, false);
		data->SetBool(SMD_IMPORT_MESH_WELD, true);
		data->SetFloat(SMD_IMPORT_MESH_WELD_TOLERANCE, 0.01);
		data->SetBool(SMD_IMPORT_MESH_MATERIALS, true);
		data->SetBool(SMD_IMPORT_MESH_NORMALS, true);
		data->SetBool(SMD_IMPORT_MESH_UV, true);
		data->SetBool(SMD_IMPORT_IK, true);
		data->SetInt32(SMD_IMPORT_IK_ORIENTATION, IK_CAMERA);
		data->SetBool(SMD_IMPORT_MESH_WEIGHTS, true);
		data->SetBool(SMD_CACHE_MEMORY, true);

		// Initialize the master records
		m_master_qc_record = NewObj(std::vector<QCFile*>);
		m_master_smd_record = NewObj(std::vector<SourceSMD*>);

		return true;
	}

	void SMDLoader::Free(GeListNode *node)
	{
		// free the master records
		DeletePtrVector(m_master_qc_record);
		DeletePtrVector(m_master_smd_record);
	}

	Bool SMDLoader::Message(GeListNode* node, Int32 type, void* data)
	{
		switch (type)
		{
			case MSG_RETRIEVEPRIVATEDATA:
			{
				RetrievePrivateData *pdata = static_cast<RetrievePrivateData*>(data);
				if (pdata)
				{
					pdata->data = ((BaseList2D*)node);
					return true;
				}
				break;
			}

			case MSG_DESCRIPTION_COMMAND:
			{
				DescriptionCommand *dc = (DescriptionCommand*)data;
				switch (dc->id[0].id)
				{
					case SMD_FLUSH_CACHE:
					{
						this->FlushMasterRecords();
						MessageDialog(IDS_CACHE_FLUSHED);
						return true;
					}
				}
			}
		}

		return SceneLoaderData::Message(node, type, data);
	}

	Bool SMDLoader::GetDParameter(GeListNode *node, const DescID &id, GeData &t_data, DESCFLAGS_GET &flags)
	{
		// Override settings here based on state
		if (!node)
			return false;

		BaseContainer *data = ((BaseList2D*)node)->GetDataInstance();

		data->SetString(SMD_CUSTOM_ROOT_NAME, "");

		switch (id[0].id)
		{
			case SMD_IMPORT_QC:
			{
				if (m_qc_file)
					data->SetBool(SMD_IMPORT_QC, true);
				return true;
			}

			case SMD_MEMORY_USAGE:
			{
				String QC = String::IntToString(Int32(m_master_qc_record->size()));
				String SMD = String::IntToString(Int32(m_master_smd_record->size()));
				String SMDP = SMD == "1" ? " SMD, " : " SMD's, ";
				String QCP = QC == "1" ? " QC." : " QC's.";
				data->SetString(SMD_MEMORY_USAGE, SMD + SMDP + QC + QCP);
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
			{
				GeData data;
				node->GetParameter(SMD_IMPORT_QC, data, DESCFLAGS_GET_0);
				if (data.GetBool())
					return true;
				else
					return false;
			}

			case SMD_IMPORT_IK_ORIENTATION:
			{
				GeData dataik;
				node->GetParameter(SMD_IMPORT_IK, dataik, DESCFLAGS_GET_0);
				GeData dataqc;
				node->GetParameter(SMD_IMPORT_QC, dataqc, DESCFLAGS_GET_0);
				if (!dataik.GetBool() || !dataqc.GetBool())
					return false;
				else
					return true;

			}

			case SMD_IMPORT_MATERIAL_ROOT:
			{
				GeData dataqc;
				node->GetParameter(SMD_IMPORT_QC, dataqc, DESCFLAGS_GET_0);
				GeData datamat;
				node->GetParameter(SMD_IMPORT_MESH_MATERIALS, datamat, DESCFLAGS_GET_0);
				if (!dataqc.GetBool() || !datamat.GetBool())
					return false;
				else
					return true;
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
		settings.Custom_Root_Name = node->GetData().GetString(SMD_CUSTOM_ROOT_NAME, "");
		settings.scale = node->GetData().GetFloat(SMD_LOADER_SCALE, 1.0);
		settings.orientation = node->GetData().GetVector(SMD_LOADER_ROTATE, Vector(0, 0, 0));
		settings.animation = node->GetData().GetBool(SMD_IMPORT_ANIMATION, 1);
		settings.mesh = node->GetData().GetBool(SMD_IMPORT_MESH, 1);
		settings.qc = node->GetData().GetBool(SMD_IMPORT_QC, 1);
		settings.top_null = node->GetData().GetBool(SMD_IMPORT_TOP_NULL, 1);
		settings.joint_root = node->GetData().GetBool(SMD_IMPORT_SKELETON_JOINT, 1);
		settings.mesh_weld = node->GetData().GetBool(SMD_IMPORT_MESH_WELD, 1);
		settings.mesh_weld_tolerance = node->GetData().GetFloat(SMD_IMPORT_MESH_WELD_TOLERANCE, 0.01);
		settings.mesh_materials = node->GetData().GetBool(SMD_IMPORT_MESH_MATERIALS, 1);
		settings.mesh_normals = node->GetData().GetBool(SMD_IMPORT_MESH_NORMALS, 1);
		settings.mesh_uv = node->GetData().GetBool(SMD_IMPORT_MESH_UV, 1);
		settings.mesh_weights = node->GetData().GetBool(SMD_IMPORT_MESH_WEIGHTS, 1);
		settings.material_root = node->GetData().GetFilename(SMD_IMPORT_MATERIAL_ROOT);
		settings.ik = node->GetData().GetBool(SMD_IMPORT_IK, 1);
		settings.ik_orientation = node->GetData().GetInt32(SMD_IMPORT_IK_ORIENTATION, IK_XZ);
		settings.cache = node->GetData().GetBool(SMD_CACHE_MEMORY, 1);

		BaseObject *topNull = nullptr;
		if (settings.top_null)
		{
			Filename nameNoSuffix = name;
			nameNoSuffix.ClearSuffix();
			topNull = BaseObject::Alloc(Onull);
			if (settings.Custom_Root_Name != "")
			{
				topNull->SetName(settings.Custom_Root_Name);
			}
			else
			{
				topNull->SetName(nameNoSuffix.GetFileString());
			}
			doc->InsertObject(topNull, nullptr, nullptr);
		}

		FILEERROR res;
		if (settings.qc)
		{
			res = ParseQC(name, settings, doc, topNull, filterflags, error);
		}
		else
		{
			res = ParseSMD(name, settings, doc, nullptr, topNull, filterflags, error, true);
		}

		if (res != FILEERROR_NONE)
		{
			FlushMasterRecords();
			return res;
		}

		return res;
	}

	void SMDLoader::FlushMasterRecords()
	{
		StatusSetSpin();
		StatusSetText(GeLoadString(IDS_FLUSHING_CACHE));

		// free the master records
		DeletePtrVector(m_master_qc_record);
		DeletePtrVector(m_master_smd_record);

		// init the master records
		m_master_qc_record = NewObj(std::vector<QCFile*>);
		m_master_smd_record = NewObj(std::vector<SourceSMD*>);

		StatusClear();
	}

	FILEERROR SMDLoader::ParseQC(const Filename &name, SMDLoaderSettings &settings, BaseDocument *doc, BaseObject *parent, SCENEFILTER filterflags, String *error)
	{
		// TO-DO:	VTA animation
		//			Attachments

		Filename CorrectFile = name;
		if (name.CheckSuffix("smd"))
			CorrectFile.SetSuffix("qc");

		// check if the qc exists in the master record and build from that data
		for (Int32 i = 0; i < m_master_qc_record->size(); i++)
		{
			if ((*m_master_qc_record)[i]->file == CorrectFile)
			{
				FILEERROR res = BuildQC((*m_master_qc_record)[i], CorrectFile, settings, doc, parent, filterflags, error);
				if (res != FILEERROR_NONE)
					return res;
				end = std::chrono::system_clock::now();
				std::chrono::duration<double> duration = end - start;
				GePrint(GeLoadString(IDS_LOADED_FILE)
					+ name.GetFileString() + GeLoadString(IDS_IN)
					+ String::FloatToString(duration.count()) + "s");
				return res;
			}
		}

		AutoAlloc<BaseFile> file;
		Bool fres = file->Open(CorrectFile);
		if (!fres)
		{
			if (!m_qc_file) // User selected qc-file but none found, just default to the smd
			{
				GePrint(name.GetFileString() + ": " + GeLoadString(IDS_NO_QC));
				settings.qc = false;
				return ParseSMD(name, settings, doc, nullptr, parent, filterflags, error, true);
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

		QCFile *NewQC = NewObj(QCFile);
		NewQC->file = CorrectFile;

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
				NewQC->body.push_back((*substrs)[2].SubStr(1, (*substrs)[2].GetLength() - 2));
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
				NewQC->bodygroup.push_back(newBodyGroup);
			}
			else if ((*substrs)[0] == "$cdmaterials")
			{
				if ((*substrs)[1].GetLength() > 2)
					NewQC->cdmaterials.push_back((*substrs)[1].SubStr(1, (*substrs)[1].GetLength() - 2));
			}
			else if ((*substrs)[0] == "$ikchain")
			{
				IKDecl newChain;
				String name = (*substrs)[1].SubStr(1, (*substrs)[1].GetLength() - 2); // name
				String bone = (*substrs)[2].SubStr(1, (*substrs)[2].GetLength() - 2); // lock name
				newChain.name = name;
				newChain.bone = bone;
				NewQC->ikchain.push_back(newChain);
			}

			DeleteObj(substrs);
		}

		file->Close();
		DeleteObj(fileLineData);

		FILEERROR res = BuildQC(NewQC, CorrectFile, settings, doc, parent, filterflags, error);
		if (res != FILEERROR_NONE)
			return res;

		if (settings.cache)
			m_master_qc_record->push_back(NewQC);
		else
			DeleteObj(NewQC);

		end = std::chrono::system_clock::now();
		std::chrono::duration<double> duration = end - start;
		GePrint(GeLoadString(IDS_LOADED_FILE)
			+ name.GetFileString() + GeLoadString(IDS_IN)
			+ String::FloatToString(duration.count()) + "s");

		return FILEERROR_NONE;
	}

	FILEERROR SMDLoader::BuildQC(const QCFile *qc, const Filename &name, SMDLoaderSettings &settings, BaseDocument *doc, BaseObject *parent, SCENEFILTER filterflags, String *error)
	{
		// Build Body Mesh(s)
		Bool BuildSkeleton = true;
		m_temporary_smd_record = NewObj(std::vector<SourceSMD*>);

		for (Int32 bo = 0; bo < qc->body.size(); bo++)
		{
			String filepath = name.GetDirectory().GetString() + "\\" + qc->body[bo];
			Filename CorrectFile(filepath);
			Bool foundRecord = false;

			// check if the SMD exists in the master record and build from that data
			for (Int32 i = 0; i < m_master_smd_record->size(); i++)
			{
				if ((*m_master_smd_record)[i]->GetFile() == CorrectFile)
				{
					Bool BuildRes = (*m_master_smd_record)[i]->Rebuild(settings);
					if (!BuildRes)
					{
						GePrint(GeLoadString(IDS_BAD_REBUILD));
						*error = GeLoadString(IDS_BAD_REBUILD);
						return FILEERROR_READ;
					}

					FILEERROR res = BuildSMD((*m_master_smd_record)[i], settings, qc, doc, parent, filterflags, error, BuildSkeleton);
					if (res != FILEERROR_NONE)
						return res;

					foundRecord = true;
				}
			}

			if (!foundRecord)
			{
				FILEERROR res = ParseSMD(CorrectFile, settings, doc, qc, parent, filterflags, error, BuildSkeleton);
				if (res != FILEERROR_NONE)
					return res;
			}
			BuildSkeleton = false;
		}

		// Build BodyGroup Mesh(s)
		for (Int32 bg = 0; bg < qc->bodygroup.size(); bg++)
		{
			for (Int32 bgi = 0; bgi < qc->bodygroup[bg].mesh.size(); bgi++)
			{
				String filepath = name.GetDirectory().GetString() + "\\" + qc->bodygroup[bg].mesh[bgi];
				Filename filename(filepath);

				Bool foundRecord = false;

				// check if the SMD exists in the master record and build from that data
				for (Int32 i = 0; i < m_master_smd_record->size(); i++)
				{
					if ((*m_master_smd_record)[i]->GetFile() == filename)
					{
						Bool BuildRes = (*m_master_smd_record)[i]->Rebuild(settings);
						if (!BuildRes)
						{
							GePrint(GeLoadString(IDS_BAD_REBUILD));
							*error = GeLoadString(IDS_BAD_REBUILD);
							return FILEERROR_READ;
						}

						FILEERROR res = BuildSMD((*m_master_smd_record)[i], settings, qc, doc, parent, filterflags, error, BuildSkeleton);
						if (res != FILEERROR_NONE)
							return res;

						foundRecord = true;
					}
				}

				if (!foundRecord)
				{
					FILEERROR res = ParseSMD(filename, settings, doc, qc, parent, filterflags, error, BuildSkeleton);
					if (res != FILEERROR_NONE)
						return res;
				}

				BuildSkeleton = false;
			}
		}

		// Build IK-Chain's
		if (settings.ik && qc->ikchain.size() > 0)
		{
			BaseObject *ik_null = BaseObject::Alloc(Onull);
			ik_null->SetName("ik_goal");
			doc->InsertObject(ik_null, parent, nullptr);
			for (Int32 ik = 0; ik < qc->ikchain.size(); ik++) // for each link
			{
				// Search through bones for the named bone
				for (Int32 bone = 0; bone < m_skeleton->size(); bone++)
				{
					if ((*m_skeleton)[bone]->GetName() == qc->ikchain[ik].bone)
					{
						BaseObject *targ = (*m_skeleton)[bone]->GetBone();
						BaseObject *root = targ->GetUp()->GetUp();
						BaseObject *ik_target = BaseObject::Alloc(Onull);
						ik_target->SetName(qc->ikchain[ik].name);
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

						Matrix loc = (*m_skeleton)[bone]->GetBone()->GetMg();
						ik_target->SetMl(loc);
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

		DeletePtrVector(m_temporary_smd_record);
		return FILEERROR_NONE;
	}

	FILEERROR SMDLoader::ParseSMD(const Filename &name, const SMDLoaderSettings &settings, BaseDocument *doc, const QCFile *qc, BaseObject *parent, SCENEFILTER filterflags, String* error, Bool BuildSkeleton)
	{
		// check if SMD exists in master record
		for (Int32 i = 0; i < m_master_smd_record->size(); i++)
		{
			if ((*m_master_smd_record)[i]->GetFile() == name)
			{
				Bool buildRes = (*m_master_smd_record)[i]->Rebuild(settings); // rebuild if necessary.
				if (!buildRes)
				{
					GePrint(GeLoadString(IDS_BAD_REBUILD));
					*error = GeLoadString(IDS_BAD_REBUILD);
					return FILEERROR_READ;
				}

				FILEERROR res = BuildSMD((*m_master_smd_record)[i], settings, qc, doc, parent, filterflags, error, BuildSkeleton);
				if (res != FILEERROR_NONE)
					return res;
				end = std::chrono::system_clock::now();
				std::chrono::duration<double> duration = end - start;
				GePrint(GeLoadString(IDS_LOADED_FILE)
					+ name.GetFileString() + GeLoadString(IDS_IN)
					+ String::FloatToString(duration.count()) + "s");
				return res;
			}
		}

		FILEERROR result = FILEERROR_NONE;
		SourceSMD *NewSMD = NewObj(SourceSMD, name, settings, result, error);
		if (result != FILEERROR_NONE)
			return result;

		result = BuildSMD(NewSMD, settings, qc, doc, parent, filterflags, error, BuildSkeleton);
		if (result != FILEERROR_NONE)
			return result;

		if (settings.cache)
			m_master_smd_record->push_back(NewSMD);
		else if (settings.qc)
			m_temporary_smd_record->push_back(NewSMD);

		if (!settings.qc)
		{
			if (!settings.cache)
				DeleteObj(NewSMD);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> duration = end - start;
			GePrint(GeLoadString(IDS_LOADED_FILE)
				+ name.GetFileString() + GeLoadString(IDS_IN)
				+ String::FloatToString(duration.count()) + "s");
		}

		return FILEERROR_NONE;
	}

	FILEERROR SMDLoader::BuildSMD(const SourceSMD *smd, const SMDLoaderSettings &settings, const QCFile *qc, BaseDocument *doc, BaseObject *parent, SCENEFILTER filterflags, String *error, Bool BuildSkeleton)
	{
		// Rotation
		Matrix RotMat = HPBToMatrix(settings.orientation, ROTATIONORDER_HPB);

		if (BuildSkeleton)
		{
			// build the skeleton
			BaseObject *topNull = nullptr;
			if (settings.joint_root)
				topNull = BaseObject::Alloc(Ojoint);
			else
				topNull = BaseObject::Alloc(Onull);
			topNull->SetName("skeleton");
			doc->InsertObject(topNull, parent, nullptr);		

			std::vector<SourceSkeletonBone*> *skeleton = smd->GetSkeleton();
			m_skeleton = skeleton;
			for (UInt32 i = 0; i < UInt32(skeleton->size()); i++)
			{
				BaseObject *bone = (*skeleton)[i]->CreateBone();
				Int32 ParentId = (*skeleton)[i]->GetParentId();
				BaseObject *boneparent = ParentId == -1 ? topNull : (*skeleton)[ParentId]->GetBone();
				doc->InsertObject(bone, boneparent, nullptr);
				bone->SetRelPos((*skeleton)[i]->GetPos(0));
				bone->SetRelRot((*skeleton)[i]->GetRot(0));

				// Animation
				if (settings.animation && smd->FrameCount() > 1)
				{
					CTrack *xPtrack = NULL, *yPtrack = NULL, *zPtrack = NULL;
					CTrack *xRtrack = NULL, *yRtrack = NULL, *zRtrack = NULL;
					CCurve *xPos = NULL, *yPos = NULL, *zPos = NULL;
					CCurve *xRot = NULL, *yRot = NULL, *zRot = NULL;

					for (Int32 f = 0; f < smd->FrameCount(); f++)
					{
						if (f == 0)
						{
							xPtrack = CTrack::Alloc(bone,
								DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_X, DTYPE_REAL, 0)));
							yPtrack = CTrack::Alloc(bone,
								DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
							zPtrack = CTrack::Alloc(bone,
								DescID(DescLevel(ID_BASEOBJECT_ABS_POSITION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
							xRtrack = CTrack::Alloc(bone,
								DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_X, DTYPE_REAL, 0)));
							yRtrack = CTrack::Alloc(bone,
								DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
							zRtrack = CTrack::Alloc(bone,
								DescID(DescLevel(ID_BASEOBJECT_ABS_ROTATION, DTYPE_VECTOR, 0),
								DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
							bone->InsertTrackSorted(xPtrack);
							bone->InsertTrackSorted(yPtrack);
							bone->InsertTrackSorted(zPtrack);
							bone->InsertTrackSorted(xRtrack);
							bone->InsertTrackSorted(yRtrack);
							bone->InsertTrackSorted(zRtrack);
							(*skeleton)[i]->SetXPTrack(xPtrack);
							(*skeleton)[i]->SetYPTrack(yPtrack);
							(*skeleton)[i]->SetZPTrack(zPtrack);
							(*skeleton)[i]->SetXRTrack(xRtrack);
							(*skeleton)[i]->SetYRTrack(yRtrack);
							(*skeleton)[i]->SetZRTrack(zRtrack);
						}

						xPos = (*skeleton)[i]->GetXPTrack()->GetCurve();
						yPos = (*skeleton)[i]->GetYPTrack()->GetCurve();
						zPos = (*skeleton)[i]->GetZPTrack()->GetCurve();
						xRot = (*skeleton)[i]->GetXRTrack()->GetCurve();
						yRot = (*skeleton)[i]->GetYRTrack()->GetCurve();
						zRot = (*skeleton)[i]->GetZRTrack()->GetCurve();

						Int32 fps = doc->GetFps();
						Vector pos = (*skeleton)[i]->GetPos(f);
						Vector rot = (*skeleton)[i]->GetRot(f);

						CKey *xPKey = xPos->AddKey(BaseTime(f, fps));
						xPKey->SetValue(xPos, pos.x);
						CKey *yPKey = yPos->AddKey(BaseTime(f, fps));
						yPKey->SetValue(yPos, pos.y);
						CKey *zPKey = zPos->AddKey(BaseTime(f, fps));
						zPKey->SetValue(zPos, pos.z);
						CKey *xRKey = xRot->AddKey(BaseTime(f, fps));
						xRKey->SetValue(xRot, rot.x);
						CKey *yRKey = yRot->AddKey(BaseTime(f, fps));
						yRKey->SetValue(yRot, rot.y);
						CKey *zRKey = zRot->AddKey(BaseTime(f, fps));
						zRKey->SetValue(zRot, rot.z);
					}

					// if we're not merging and we have animation, set the start & end accordingly
					if (((filterflags & SCENEFILTER_MERGESCENE) != SCENEFILTER_MERGESCENE)
						&& settings.animation && smd->FrameCount() > 1)
					{
						doc->SetMaxTime(BaseTime(smd->FrameCount(), doc->GetFps()));
						doc->SetLoopMaxTime(BaseTime(smd->FrameCount(), doc->GetFps()));
					}
				}
			}
			topNull->SetMg(RotMat * topNull->GetMg());
		}

		// Build the mesh
		if (settings.mesh)
		{
			std::vector<Int32> index;
			Int32 PolyCount = Int32(smd->GetTriangles()->size());

			if (!(PolyCount > 0)) // don't build poly if no triangles
			{
				return FILEERROR_NONE;
			}

			// the new poly
			PolygonObject *newPoly = PolygonObject::Alloc(0, 0);
			AutoAlloc<Modeling> mod;
			Filename NameNoSuff = smd->GetFile().GetFile();
			NameNoSuff.ClearSuffix();
			newPoly->SetName(NameNoSuff.GetString());
			doc->InsertObject(newPoly, parent, nullptr);
			mod->InitObject(newPoly);

			std::vector<ST::StudiomdlDataTriangle*> *triangles = smd->GetTriangles();

			for (Int32 p = 0; p < PolyCount; p++) // for each triangle
			{
				// z is flipped, build backwards to have proper front facing poly's
				index.push_back(mod->AddPoint(newPoly, RotMat * (*triangles)[p]->GetPointC() * settings.scale));
				index.push_back(mod->AddPoint(newPoly, RotMat * (*triangles)[p]->GetPointB() * settings.scale));
				index.push_back(mod->AddPoint(newPoly, RotMat * (*triangles)[p]->GetPointA() * settings.scale));
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
					normals.a = RotMat * (*triangles)[i]->GetNormalC();
					normals.b = RotMat * (*triangles)[i]->GetNormalB();
					normals.c = RotMat * (*triangles)[i]->GetNormalA();
					NormalTag::Set(handle, i, normals);
				}
				newPoly->Message(MSG_UPDATE);
			}

			// Selection Tags
			BaseSelect *sel = newPoly->GetPolygonS();
			std::map<Int32, String> PolySelections = smd->GetPolySelections();
			Int32 LastIndex = 0;
			for (auto j = PolySelections.begin(); j != PolySelections.end(); j++) // for each selection
			{
				sel->DeselectAll();
				Int32 h;
				for (h = LastIndex; h <= j->first; h++)
					sel->Select(h);
				LastIndex = h;

				SelectionTag *newSelTag = SelectionTag::Alloc(Tpolygonselection);
				newSelTag->SetName(ST::Parse::trim(j->second));
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
							for (Int32 cd = 0; cd < qc->cdmaterials.size(); cd++) // iterate through material directories
							{
								String s_vmt_filename = s_root_dir + qc->cdmaterials[cd] + newMat->GetName() + ".vmt";
								Char *vmt_filename = NewMem(Char, s_vmt_filename.GetCStringLen() + 1);
								s_vmt_filename.GetCString(vmt_filename, s_vmt_filename.GetCStringLen() + 1);
								if (vmt_file->Load(vmt_filename))
								{
									DeleteMem(vmt_filename);
									VertexLitGeneric tmp = Parse::ParseVertexLitGeneric(vmt_file, settings.material_root);

									newMat->SetChannelState(CHANNEL_REFLECTION, false);
									newMat->GetDataInstance()->SetBool(REFLECTION_LAYER_IMPORTED, true);

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
		}

		return FILEERROR_NONE;
	}

	SourceSMD::SourceSMD(const Filename &SMD, const SMDLoaderSettings &settings, FILEERROR result, String *error)
		: m_file(SMD), m_animation_built(false), m_mesh_built(false), m_frames(1), m_mesh_start(-1)
	{
		m_skeleton = NewObj(std::vector<SourceSkeletonBone*>);
		m_triangles = NewObj(std::vector<StudiomdlDataTriangle*>);

		AutoAlloc<BaseFile> file;
		file->Open(SMD);
		if (!file)
		{
			result = file->GetError();
			return;
		}

		// read data into byte array and seperate it into lines.
		Char *fileData = NewMem(Char, file->GetLength());
		file->ReadBytes(fileData, file->GetLength());
		std::vector<String> *fileLineData = ST::Parse::ParseLines(fileData);
		DeleteMem(fileData);

		for (Int32 i = 0; i < fileLineData->size(); i++)
		{
			StatusSetText("Line " + String::IntToString(i) + " of " + String::IntToString(Int32(fileLineData->size())));
			StatusSetBar(Int32(1.0f * i / fileLineData->size() * 100));

			String line = (*fileLineData)[i];
			if (line == "nodes")
			{
				if (!ParseNodes(fileLineData, i))
				{
					*error = GeLoadString(IDS_CRITICAL_ERROR);
					result = FILEERROR_READ;
					return;
				}
			}
			else if (line == "skeleton")
			{
				if (!ParseSkeleton(fileLineData, settings, i))
				{
					*error = GeLoadString(IDS_CRITICAL_ERROR);
					result = FILEERROR_READ;
					return;
				}
			}
			else if (line == "triangles")
			{
				m_mesh_start = i;
				if (settings.mesh)
				{
					if (ParseTriangles(fileLineData, i) != 0)
					{
						*error = GeLoadString(IDS_CRITICAL_ERROR) + ": triangle parse error.";
						result = FILEERROR_READ;
						return;
					}
				}
			}
		}

		StatusClear();

		if (settings.mesh)
			m_mesh_built = true;
		if (settings.animation)
			m_animation_built = true;

		file->Close();
		DeleteObj(fileLineData);

		result = FILEERROR_NONE;
	}

	SourceSMD::~SourceSMD()
	{
		DeletePtrVector(m_skeleton);
		DeletePtrVector(m_triangles);
	}

	Bool SourceSMD::Rebuild(const SMDLoaderSettings &settings)
	{
		// check if anything does need to be built
		if ((settings.animation && !m_animation_built) ||
			(settings.mesh && !m_mesh_built))
		{
			// reopen file
			AutoAlloc<BaseFile> file;
			file->Open(m_file);
			if (!file)
				return false;

			// read data into byte array and seperate it into lines.
			Char *fileData = NewMem(Char, file->GetLength());
			file->ReadBytes(fileData, file->GetLength());
			std::vector<String> *fileLineData = ST::Parse::ParseLines(fileData);
			DeleteMem(fileData);
			file->Close();

			if (settings.animation && !m_animation_built)
			{
				Bool res = ParseSkeleton(fileLineData, settings, m_anim_start);
				if (!res)
					return false;
			}

			if (settings.mesh && !m_mesh_built && m_mesh_start > 0)
			{
				Int32 res = ParseTriangles(fileLineData, m_mesh_start);
				if (res != 0)
					return false;
			}

			DeleteObj(fileLineData);
		}

		return true;
	}

	Bool SourceSMD::ParseNodes(const std::vector<String> *data, Int32 &it)
	{
		it++;
		while ((*data)[it] != "end" && it < data->size())
		{
			Int32 id, parentid;
			String name;
			std::vector<String> *substrs = ST::Parse::split((*data)[it]);
			if ((*substrs).size() < 3)
			{
				DeleteObj(substrs);
				return false;
			}

			id = (*substrs)[0].ParseToInt32();
			name = (*substrs)[1].SubStr(1, (*substrs)[1].GetLength() - 2);
			parentid = (*substrs)[2].ParseToInt32();

			ST::SourceSkeletonBone *bone = NewObj(ST::SourceSkeletonBone, id, name, parentid);
			m_skeleton->push_back(bone);

			it++;
			DeleteObj(substrs);
		}

		return (it == data->size()) ? false : true;
	}

	Bool SourceSMD::ParseSkeleton(const std::vector<String> *data, const SMDLoaderSettings &settings, Int32 &it)
	{
		if ((*data)[it] == "skeleton")
			it++;
		
		Int32 startit = it;

		Int32 frame = -1;		

		while ((*data)[it] != "end" && it < data->size())
		{
			std::vector<String> *substrs = ST::Parse::split((*data)[it]);

			if ((*substrs)[0] == "time")
			{
				frame = (*substrs)[1].ParseToInt32();

				if (frame > 0 && !settings.animation)
				{
					m_anim_start = it;
					DeleteObj(substrs);
					break;
				}

				it++;
				DeleteObj(substrs);
				continue;
			}

			if (substrs->size() < 7) // bad skeleton
			{
				return false;
			}

			Int32 id = (*substrs)[0].ParseToInt32();
			Vector pos((*substrs)[1].ParseToFloat(), (*substrs)[2].ParseToFloat(), -(*substrs)[3].ParseToFloat());
			Vector rot(-(*substrs)[4].ParseToFloat(), -(*substrs)[5].ParseToFloat(), (*substrs)[6].ParseToFloat());

			Matrix mat = HPBToMatrix(rot, ROTATIONORDER_XYZLOCAL);
			mat = ~mat; // invert the matrix to make euler angles local
			mat.off = pos;

			// Set the reference position.
			if (frame == 0)
			{
				(*m_skeleton)[id]->SetRefMl(mat);
			}

			(*m_skeleton)[id]->PushBackPos(pos);
			Vector FinalRot = MatrixToHPB(mat, ROTATIONORDER_HPB);
			(*m_skeleton)[id]->PushBackRot(FinalRot);

			it++;
			DeleteObj(substrs);
		}

		m_frames = m_frames > frame + 1 ? m_frames : frame + 1;
		if (m_frames == 1)
		{
			m_anim_start = startit;
			m_animation_built = true;
		}

		return (it == data->size()) ? false : true;
	}

	Int32 SourceSMD::ParseTriangles(const std::vector<String> *data, Int32 &it)
	{
		Int32 tIt = it + 1; // skip the opening tag

		String CurrentMesh = (*data)[tIt];
		while ((*data)[tIt] != "end") // fill vector
		{
			Int32 error = 2;
			ST::StudiomdlDataTriangle *newTriangle = NewObj(ST::StudiomdlDataTriangle, data, tIt, error);
			if (error != 0)
				return error;

			m_triangles->push_back(newTriangle);

			if ((*data)[tIt] != CurrentMesh) // end of portion
			{
				m_polySelections.emplace((Int32(m_triangles->size()) - 1), CurrentMesh);
				CurrentMesh = (*data)[tIt];
			}
		}

		m_mesh_built = true;
		return 0;
	}
}

Bool RegisterSMDLoader()
{
	return RegisterSceneLoaderPlugin(SMD_IMPORT_ID, GeLoadString(IDS_SMD), 0, ST::SMDLoader::Alloc, "fsmdloader", nullptr);
}