#include "qcloader.h"

#include "qcformat.h"
#include "qcparser.h"
#include "smdparser.h"
#include "smdloader.h"
#include "fqcloader.h"
#include "c4d_symbols.h"
#include "vmtloader.h"
#include "vmtparser.h"
#include "fstools.h"

#include "error.h"
#include "benchmark.h"

#include "c4d_baseobject.h"
#include "c4d_basedocument.h"
#include "lib_description.h"
#include "c4d_resource.h"
#include "c4d_basetag.h"
#include "ttexture.h"

#define Tik 1019561 // Ik Tag ID
#define ID_CA_IK_TAG_TIP		2000
#define ID_CA_IK_TAG_TARGET		2001
#define ID_CA_IK_TAG_SOLVER		2003
#define ID_CA_IK_TAG_SOLVER_2D	1
#define ID_CA_IK_TAG_SOLVER_3D	2

Bool QCLoaderData::Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size)
{
	// QuakeC is an ASCII format with no FourCC/Header so we will use the file extension
	return (name.GetSuffix().ToLower() == "qc") ? true : false;
}

FILEERROR QCLoaderData::Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt)
{
	IF_PROFILING(Benchmark QCLoadBench("QCLoaderData::Load"));
	auto GetParam = [&node](Int32 id)->GeData
	{
		GeData DataHolder;
		node->GetParameter(id, DataHolder, DESCFLAGS_GET::NONE);
		return DataHolder;
	};

	Bool ParamImportMaterials = GetParam(QC_LOADER_SOURCETYPE).GetInt32() == SOURCETYPE_NONE ? false : true;
	Bool ParamImportIK = GetParam(QC_LOADER_IMPORT_IK).GetBool();
	Bool ParamImportPhysics = GetParam(QC_LOADER_IMPORT_PHYSICS).GetBool();

	Filename MaterialRootDirectory;

	if (ParamImportMaterials)
	{
		// Check for valid material path
		MaterialRootDirectory = GetParam(QC_LOADER_MATERIAL_PATH).GetFilename();
		if (!GeFExist(MaterialRootDirectory, true))
		{
			*error = GeLoadString(S_INVALID_MATERIAL_PATH);
			return FILEERROR::WRONG_VALUE;
		}
	}

	QuakeCFormat qc;
	if (!ParseQC(name, qc))
	{
		LogError("PEGTL failed to parse QC.");
		*error = GeLoadString(S_PARSE_ERROR, name.GetString());
		return FILEERROR::INVALID;
	}
	
	BaseObject* QCNull = BaseObject::Alloc(Onull);
	auto Name = name.GetFile();
	Name.ClearSuffix();
	QCNull->SetName(Name.GetString());
	doc->InsertObject(QCNull, nullptr, nullptr);

	SMDLoaderData::Settings SMDConfig;

	SMDConfig.IncludeAnimation = GetParam(QC_LOADER_IMPORT_ANIMATION).GetBool();
	SMDConfig.IncludeMesh = GetParam(QC_LOADER_IMPORT_MESH).GetBool();
	SMDConfig.IncludeSkeleton = GetParam(QC_LOADER_IMPORT_SKELETON).GetBool();
	SMDConfig.IncludeWeights = GetParam(QC_LOADER_IMPORT_WEIGHTS).GetBool();
	SMDConfig.Orientation = GetParam(QC_LOADER_ROTATE).GetVector();
	SMDConfig.Scale = GetParam(QC_LOADER_SCALE).GetFloat();
	SMDConfig.IncludeNormals = true;
	SMDConfig.IncludePolySelections = true;
	SMDConfig.IncludeUVW = true;
	SMDConfig.doc = doc;

	Bool ParamImportUnderNull = GetParam(QC_LOADER_IMPORT_UNDER_NULL).GetBool();

	// Count the total number of meshes in the QC
	auto TotalMeshes = qc.Models.size() + qc.BodyMeshes.size();
	for (auto i : qc.BodyGroups)
		TotalMeshes += i.Meshes.size();

	std::map<maxon::String, std::vector<BaseTag*>> MaterialMap;

	IF_PROFILING(Benchmark QCLoadMeshBuildBench("QCLoad-MeshBuild"));

	/* Body Meshes */
	for (const auto& bm : qc.BodyMeshes)
	{
		StudiomdlData smd;
		Filename fp = name.GetDirectory() + "/" + bm.Filepath;
		if (!fp.CheckSuffix("smd"_s)) fp += "smd";
		if (!ParseSMD(fp, smd))
		{
			LogError("PEGTL failed to parse SMD needed for QC.");
			*error = GeLoadString(S_PARSE_ERROR, fp.GetString());
			return FILEERROR::INVALID;
		}

		auto SMDObj = SMDLoaderData::CreateSMD(smd, SMDConfig);

		SMDConfig.Skeleton = SMDObj.Skeleton;

		if (SMDConfig.IncludeMesh)
		{
			fp = fp.GetFile();
			fp.ClearSuffix();
			SMDObj.Mesh->SetName(fp.GetString());
			SMDObj.Mesh->Remove();
			SMDObj.Mesh->InsertUnderLast(QCNull);

			if (ParamImportMaterials)
			{
				/* Prepare material maps */
				for (auto PolyTag = SMDObj.Mesh->GetTag(Tpolygonselection);
					PolyTag != nullptr; PolyTag = PolyTag->GetNext())
				{
					if (PolyTag->GetType() != Tpolygonselection)
						continue;
					MaterialMap[PolyTag->GetName()].push_back(PolyTag);
				}
			}
		}
	}

	/* Bodygroup Meshes */
	for (const auto& bgm : qc.BodyGroups)
	{
		BaseObject* BodyGroupNull = nullptr;
		if (SMDConfig.IncludeMesh)
		{
			BodyGroupNull = BaseObject::Alloc(Onull);
			BodyGroupNull->SetName(maxon::String(bgm.Name));
			doc->InsertObject(BodyGroupNull, QCNull, QCNull->GetDownLast());
		}

		for (const auto& mesh : bgm.Meshes)
		{
			StudiomdlData smd;
			Filename fp = name.GetDirectory() + "/" + mesh;
			if (!fp.CheckSuffix("smd"_s)) fp.SetSuffix("smd"_s);

			if (!ParseSMD(fp, smd))
			{
				LogError("PEGTL failed to parse SMD needed for QC.");
				*error = GeLoadString(S_PARSE_ERROR, fp.GetString());
				return FILEERROR::INVALID;
			}

			auto SMDObj = SMDLoaderData::CreateSMD(smd, SMDConfig);

			SMDConfig.Skeleton = SMDObj.Skeleton;

			if (SMDConfig.IncludeMesh)
			{
				fp = fp.GetFile();
				fp.ClearSuffix();
				SMDObj.Mesh->SetName(fp.GetString());
				SMDObj.Mesh->Remove();
				SMDObj.Mesh->InsertUnderLast(BodyGroupNull);

				/* Prepare material maps */
				if (ParamImportMaterials)
				{
					for (auto PolyTag = SMDObj.Mesh->GetTag(Tpolygonselection);
						PolyTag != nullptr; PolyTag = PolyTag->GetNext())
					{
						if (PolyTag->GetType() != Tpolygonselection)
							continue;
						MaterialMap[PolyTag->GetName()].push_back(PolyTag);
					}
				}
			}
		}

		if (SMDConfig.IncludeMesh)
		{
			if (bgm.Blank)
			{
				BaseObject* BlankNull = BaseObject::Alloc(Onull);
				BlankNull->SetName("blank"_s);
				doc->InsertObject(BlankNull, BodyGroupNull, BodyGroupNull->GetDownLast());
			}
		}
	}

	IF_PROFILING(QCLoadMeshBuildBench.StopBenchmark());

	/* Apply materials */
	if (ParamImportMaterials && SMDConfig.IncludeMesh)
	{
		IF_PROFILING(Benchmark QCLoadMaterialBench("QCLoad-Material"));
		std::vector<Filename> cdmat;
		for (const auto& dir : qc.cdmaterials)
			cdmat.push_back(Filename(dir));

		for (auto& dir : cdmat)
			if (!ResolveLocalFilepath(dir, std::vector<Filename>({ MaterialRootDirectory }), true))
				LogError("Couldn't resolve cdmaterial path: " + dir.GetString());

		cdmat.push_back(MaterialRootDirectory);

		for (auto& Mat : MaterialMap)
		{
			Filename fp = Mat.first;
			fp.SetSuffix("vmt"_s);

			if (!ResolveLocalFilepath(fp, cdmat))
			{
				LogError("Coudln't resolve material path: " + fp.GetString());
				continue;
			}

			ValveMaterialType vmt;
			if (!ParseVMT(fp, vmt))
			{
				LogError("Failed to parse VMT file: " + fp.GetString());
				continue;
			}

			VMTLoaderData::Settings config;
			config.BitmapExtension = GetParam(QC_MATERIAL_EXTENSION).GetString();
			config.cdmaterials = cdmat;
			auto MatObj = VMTLoaderData::CreateVMT(vmt, config);

			fp.ClearSuffix();
			((BaseObject*)MatObj)->SetName(fp.GetFileString());

			doc->InsertMaterial((BaseMaterial*)MatObj, nullptr);
			
			for (auto& PTag : Mat.second)
			{
				auto Obj = PTag->GetObject();
				TextureTag* TTag = TextureTag::Alloc();
				Obj->InsertTag(TTag);
				TTag->SetMaterial((BaseMaterial*)MatObj);
				TTag->SetParameter(TEXTURETAG_RESTRICTION, PTag->GetName(), DESCFLAGS_SET::NONE);
				TTag->SetParameter(TEXTURETAG_PROJECTION, TEXTURETAG_PROJECTION_UVW, DESCFLAGS_SET::NONE);
			}
		}
	}

	/* IkChains */
	if (ParamImportIK && qc.IkRules.size() > 0)
	{
		auto Iks = qc.IkRules;
		BaseObject* IkNull = BaseObject::Alloc(Onull);
		IkNull->SetName("ik_goals"_s);
		doc->InsertObject(IkNull, QCNull, nullptr);

		for (auto& bone : SMDConfig.Skeleton)
		{
			if (Iks.size() == 0)
				break;

			auto BoneName = bone.second.Object->GetName();
			for (auto ik = Iks.begin(); ik != Iks.end(); ik++)
			{
				if (ik->EndBone == BoneName)
				{
					BaseObject* StartBone = bone.second.Object->GetUp()->GetUp();
					if (StartBone == nullptr)
					{
						String msg = "IK could not get start bone. IK Name: " + ik->Name + " -- End Bone: " + ik->EndBone;
						LogError(msg);
						break;
					}

					BaseObject* ikTarget = BaseObject::Alloc(Onull);
					ikTarget->SetName(ik->Name);
					ikTarget->SetMg(bone.second.Object->GetMg());
					doc->InsertObject(ikTarget, IkNull, nullptr);

					auto ikTag = StartBone->MakeTag(Tik);
					ikTag->SetParameter(DescID(ID_CA_IK_TAG_TIP), bone.second.Object, DESCFLAGS_SET::NONE);
					ikTag->SetParameter(DescID(ID_CA_IK_TAG_TARGET), ikTarget, DESCFLAGS_SET::NONE);
					ikTag->SetParameter(DescID(ID_CA_IK_TAG_SOLVER), ID_CA_IK_TAG_SOLVER_3D, DESCFLAGS_SET::NONE);

					Iks.erase(ik);

					break;
				}
			}
		}

		for (auto& ik : Iks)
		{
			String msg = "Could not find IK end bone. IK Name: " + ik.Name + " -- End Bone: " + ik.EndBone;
			LogError(msg);
		}
	}

	/* Reorder skeleton */
	if (SMDConfig.IncludeSkeleton)
	{
		BaseObject* DummyNull = BaseObject::Alloc(Onull);
		doc->InsertObject(DummyNull, QCNull, nullptr);
		for (auto& bone : SMDConfig.Skeleton)
		{
			if (bone.second.ParentId == -1)
			{
				bone.second.Object->Remove();
				bone.second.Object->InsertBefore(DummyNull);
			}
		}
		BaseObject::Free(DummyNull);
	}

	/* Physics Mesh */
	if (ParamImportPhysics)
	{
		IF_PROFILING(Benchmark QCLoadPhysicsBench("QCLoad-Physics"));

		SMDConfig.IncludeNormals = false;
		SMDConfig.IncludePolySelections = false;
		SMDConfig.IncludeUVW = false;
		SMDConfig.IncludeMesh = true;

		StudiomdlData smd;
		Filename fp = name.GetDirectory() + "/" + qc.PhysicsMesh.Filepath;
		if (!fp.CheckSuffix("smd"_s)) fp.SetSuffix("smd"_s);

		if (!ParseSMD(fp, smd))
		{
			LogError("PEGTL failed to parse SMD needed for QC.");
			*error = GeLoadString(S_PARSE_ERROR, fp.GetString());
			return FILEERROR::INVALID;
		}

		auto SMDObj = SMDLoaderData::CreateSMD(smd, SMDConfig);
		SMDObj.Mesh->SetName("physics"_s);
		SMDObj.Mesh->Remove();
		SMDObj.Mesh->InsertUnderLast(QCNull);
	}

	/* Remove Null */
	if (!ParamImportUnderNull)
	{
		while (auto Obj = QCNull->GetDown())
		{
			Obj->Remove();
			Obj->InsertBefore(QCNull);
		}

		BaseObject::Free(QCNull);
	}

	return FILEERROR::NONE;
}

Bool QCLoaderData::GetDEnabling(GeListNode* node, const DescID& id, const GeData& data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc)
{
	if (node == nullptr)
		return false;

	auto GetParam = [&node](Int32 id)->GeData
	{
		GeData Data;
		node->GetParameter( id, Data, DESCFLAGS_GET::NONE );
		return Data;
	};

	switch (id[0].id)
	{
		case QC_LOADER_IMPORT_WEIGHTS:
		{
			return GetParam(QC_LOADER_IMPORT_MESH).GetBool() &&
				GetParam(QC_LOADER_IMPORT_SKELETON).GetBool();

		}

		case QC_LOADER_SOURCETYPE:
		{
			return GetParam(QC_LOADER_IMPORT_MESH).GetBool();
		}

		case QC_MATERIAL_EXTENSION:
		{
			if (GetParam(QC_LOADER_SOURCETYPE).GetInt32() != SOURCETYPE_VMF_OTHER)
				return false;
			else return true;
		}

		case QC_LOADER_MATERIAL_PATH:
		{
			if (GetParam(QC_LOADER_SOURCETYPE).GetInt32() == SOURCETYPE_NONE)
				return false;
			else return true;
		}

		case QC_LOADER_IMPORT_ANIMATION:
		{
			return GetParam(QC_LOADER_IMPORT_SKELETON).GetBool();
		}
	}

	return true;
}

Bool QCLoaderData::GetDParameter(GeListNode* node, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags)
{
	if (node == nullptr)
		return false;

	auto GetParam = [&node](Int32 id)->GeData
	{
		GeData Data;
		node->GetParameter(id, Data, DESCFLAGS_GET::NONE);

		return Data;
	};

	auto SetFalse = [&t_data, &flags](void) -> void
	{
		t_data.SetInt32(0);
		flags |= DESCFLAGS_GET::PARAM_GET;
	};


	switch (id[0].id)
	{
		case QC_LOADER_SOURCETYPE:
		{
			if (!GetParam(QC_LOADER_IMPORT_MESH).GetBool())
			{
				t_data.SetInt32(SOURCETYPE_NONE);
				flags |= DESCFLAGS_GET::PARAM_GET;
				return true;
			}

			break;
		}

		case QC_LOADER_IMPORT_WEIGHTS:
		{
			if (!(
				GetParam(QC_LOADER_IMPORT_MESH).GetBool() &&
				GetParam(QC_LOADER_IMPORT_SKELETON).GetBool()))
			{
				SetFalse();
				return true;
			}

			break;
		}

		case QC_MATERIAL_EXTENSION:
		{
			if (GetParam(QC_LOADER_SOURCETYPE).GetInt32() == SOURCETYPE_NONE)
			{
				t_data.SetString(""_s);
				flags |= DESCFLAGS_GET::PARAM_GET;
				return true;
			}
			
			if (GetParam(QC_LOADER_SOURCETYPE).GetInt32() == SOURCETYPE_VMF_VTF)
			{
				t_data.SetString("vtf"_s);
				flags |= DESCFLAGS_GET::PARAM_GET;
				return true;
			}

			if (GetParam(QC_LOADER_SOURCETYPE).GetInt32() == SOURCETYPE_VMF_TGA)
			{
				t_data.SetString("tga"_s);
				flags |= DESCFLAGS_GET::PARAM_GET;
				return true;
			}

			break;
		}

		case QC_LOADER_MATERIAL_PATH:
		{
			if (GetParam(QC_LOADER_SOURCETYPE).GetInt32() == SOURCETYPE_NONE)
			{
				t_data.SetFilename(""_s);
				flags |= DESCFLAGS_GET::PARAM_GET;
				return true;
			}

			break;
		}

		case QC_LOADER_IMPORT_ANIMATION:
		{
			if (!GetParam(QC_LOADER_IMPORT_SKELETON).GetBool())
			{
				SetFalse();
				return true;
			}

			break;
		}
	}

	return SceneLoaderData::GetDParameter(node, id, t_data, flags);
}

Bool QCLoaderData::Init(GeListNode* node)
{
	/* Default settings, overriden by user-prefs */
	BaseContainer* data = ((BaseList2D*)node)->GetDataInstance();
	data->SetFloat(QC_LOADER_SCALE, 1.0f);
	data->SetVector(QC_LOADER_ROTATE, Vector(0.0f, 0.0f, 0.0f));
	data->SetBool(QC_LOADER_IMPORT_UNDER_NULL, false);
	data->SetBool(QC_LOADER_IMPORT_SKELETON, true);
	data->SetBool(QC_LOADER_IMPORT_MESH, true);
	data->SetBool(QC_LOADER_IMPORT_WEIGHTS, true);
	data->SetInt32(QC_LOADER_SOURCETYPE, SOURCETYPE_NONE);
	data->SetFilename(QC_LOADER_MATERIAL_PATH, ""_s);
	data->SetBool(QC_LOADER_IMPORT_ANIMATION, true);
	data->SetBool(QC_LOADER_IMPORT_IK, false);
	data->SetBool(QC_LOADER_IMPORT_PHYSICS, false);

	return true;
}

NodeData* QCLoaderData::Create()
{
	return NewObjClear(QCLoaderData);
}

Bool QCLoaderData::RegisterPlugin()
{
	if (!RegisterSceneLoaderPlugin(ID_QCLOADER, "QuakeC (QC) Loader"_s, 0, QCLoaderData::Create, "Fqcloader"_s))
		return false;

	return true;
}
