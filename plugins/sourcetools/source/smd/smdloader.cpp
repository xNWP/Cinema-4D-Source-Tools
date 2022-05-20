#include "smdloader.h"
#include "fsmdloader.h"
#include "smdparser.h"

#include "error.h"
#include "c4d_symbols.h"
#include "utility.h"

#include "c4d_baseobject.h"
#include "c4d_basedocument.h"
#include "c4d_canimation.h"
#include "lib_description.h"
#include "obase.h"
#include "lib_modeling.h"
#include "c4d_basetag.h"
#include "c4d_baseselect.h"
#include "lib_ca.h"
#include "ge_math.h"
#include "c4d_resource.h"

#include "benchmark.h"

#include <cmath> // std::floor
#include <unordered_map>

namespace st::smd
{
	Bool LoaderData::Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size)
	{
		// unfortunately SMD is an ascii format with no FourCC/Header so we will just assume
		// that the file-type is SMD based on the extension alone.
		return (name.GetSuffix().ToLower() == "smd") ? true : false;
	}

	FILEERROR LoaderData::Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt)
	{
		StudiomdlData smd;

		if (!ParseSMD(name, smd))
		{
			auto msg = GeLoadString(S_PARSE_ERROR, name.GetString());
			LogError(msg);
			*error = msg;
			return FILEERROR::INVALID;
		}

		auto GetParam = [&node](Int32 id)->GeData
		{
			static GeData Data;
			node->GetParameter(id, Data, DESCFLAGS_GET::NONE);
			return Data;
		};

		/* Get Parameters */
		Settings config;

		config.Scale = GetParam(SMD_LOADER_SCALE).GetFloat();
		config.Orientation = GetParam(SMD_LOADER_ROTATE).GetVector();
		config.IncludeSkeleton = GetParam(SMD_LOADER_IMPORT_SKELETON).GetBool();
		config.IncludeAnimation = GetParam(SMD_LOADER_IMPORT_ANIMATION).GetBool();
		config.IncludeMesh = GetParam(SMD_LOADER_IMPORT_MESH).GetBool();
		config.IncludeWeights = GetParam(SMD_LOADER_IMPORT_WEIGHTS).GetBool();
		config.IncludePolySelections = true;
		config.IncludeNormals = true;
		config.IncludeUVW = true;
		config.doc = doc;

		auto ParamUnderNull = GetParam(SMD_LOADER_IMPORT_UNDER_NULL).GetBool();

		/* Does the heavy lifting */
		auto SMDObj = CreateSMD(smd, config);

		auto Name = name.GetFile();
		Name.ClearSuffix();
		if (SMDObj.Mesh) SMDObj.Mesh->SetName(Name.GetString());

		if (ParamUnderNull)
		{
			BaseObject* null = BaseObject::Alloc(Onull);
			null->SetName(Name.GetString());
			doc->InsertObject(null, nullptr, nullptr);

			if (config.IncludeSkeleton)
			{
				for (auto& bone : SMDObj.Skeleton)
				{
					if (bone.second.ParentId == -1)
					{
						bone.second.Object->Remove();
						bone.second.Object->InsertUnderLast(null);
					}
				}
			}

			if (SMDObj.Mesh)
			{
				SMDObj.Mesh->Remove();
				SMDObj.Mesh->InsertUnderLast(null);
			}
		}

		/* Set start/end time accordingly */
		if (!(filterflags & SCENEFILTER::MERGESCENE) && smd.SkeletonAnimation.size() > 1 && config.IncludeAnimation)
		{
			doc->SetMaxTime(BaseTime((Float)smd.SkeletonAnimation.size() - 1, doc->GetFps()));
			doc->SetLoopMaxTime(BaseTime((Float)smd.SkeletonAnimation.size() - 1, doc->GetFps()));
		}

		return FILEERROR::NONE;
	}

	LoaderData::SMDObject LoaderData::CreateSMD(const StudiomdlData& smd, const Settings& config)
	{
		IF_PROFILING(Benchmark CreateSMDBench("CreateSMD"));
		SMDObject SMDObj;
		SMDObj.Skeleton = config.Skeleton;

		/* Transforms */
		const maxon::Matrix RotationMatrix = HPBToMatrix(config.Orientation, ROTATIONORDER::HPB) * SrcToC4DTransformMatrix;
		const maxon::Matrix TransformMatrix =
			MatrixScale(Vector(config.Scale, config.Scale, config.Scale))
			* RotationMatrix;

		BaseObject* RootNull = BaseObject::Alloc(Onull);
		config.doc->InsertObject(RootNull, nullptr, nullptr);

		if (SMDObj.Skeleton.empty() && config.IncludeSkeleton)
		{
			IF_PROFILING(Benchmark CreateSMDBuildSkeletonBench("CreateSMD-BuildSkeleton"));
			{
				IF_PROFILING(Benchmark CreateSMDBuildSkeletonInsertBonesBench("CreateSMD-BuildSkeleton-InsertBones"));
				for (auto& bone : smd.Bones)
				{
					BoneMapData Entry;
					Entry.ParentId = bone.ParentId;
					Entry.Object = BaseObject::Alloc(Ojoint);
					Entry.Object->SetName(bone.Name);
					SMDObj.Skeleton[bone.Id] = std::move(Entry);

					if (Entry.ParentId == -1)
						config.doc->InsertObject(Entry.Object, RootNull, RootNull->GetDownLast());
					else
						config.doc->InsertObject(Entry.Object,
							SMDObj.Skeleton[Entry.ParentId].Object,
							SMDObj.Skeleton[Entry.ParentId].Object->GetDownLast());
				}
			}

			// Animation + Default Pose
			Int32 DocumentFramesPerSecond = config.doc->GetFps();
			std::map<std::int16_t, Vector> LastBoneRotationMap;
			IF_PROFILING(Benchmark CreateSMDAnimationBench("CreateSMD-Animation", false));
			IF_PROFILING(Benchmark CreateSMDAnimationInitTracksCurvesBench("CreateSMD-Animation-InitTracksCurves", false, false));
			IF_PROFILING(Benchmark CreateSMDAnimationTransformShortRouteBench("CreateSMD-Animation-TransformShortRoute", false, false));
			IF_PROFILING(Benchmark CreateSMDAnimationAddSetKeysBench("CreateSMD-Animation-AddSetKeys", false, false));
			IF_PROFILING(if (config.IncludeAnimation) {
				CreateSMDAnimationBench.PrintOnDestruct(true);
				CreateSMDAnimationInitTracksCurvesBench.PrintOnDestruct(true);
				CreateSMDAnimationTransformShortRouteBench.PrintOnDestruct(true);
				CreateSMDAnimationAddSetKeysBench.PrintOnDestruct(true);
			})

			for (const auto& bone : smd.SkeletonAnimation[0].Entries) {
				auto DoBoneTransform = [&SMDObj, &TransformMatrix](const Types::SkeletonAnimationEntry& b) -> maxon::Matrix {
					maxon::Matrix BoneLocalMatrix = HPBToMatrix(maxon::Vector
					(b.Rotation.x, b.Rotation.y, b.Rotation.z), ROTATIONORDER::XYZLOCAL);
					BoneLocalMatrix = ~BoneLocalMatrix;
					BoneLocalMatrix.off = maxon::Vector(b.Position.x, b.Position.y, b.Position.z);
					if (SMDObj.Skeleton[b.Id].ParentId == -1) BoneLocalMatrix = TransformMatrix * BoneLocalMatrix;
					return BoneLocalMatrix;
				};

				// Set Default Pose				
				SMDObj.Skeleton[bone.Id].Object->SetMl(DoBoneTransform(bone));

				// Animation
				if (config.IncludeAnimation) {
					// Initialize + Insert Tracks + Get Curves
					IF_PROFILING(CreateSMDAnimationInitTracksCurvesBench.StartBenchmark());
					CCurve* curves[6];
					Int32 curveIt = 0;
					for (const auto& trackProp : { ID_BASEOBJECT_REL_POSITION, ID_BASEOBJECT_REL_ROTATION }) {
						for (const auto& trackComp : { VECTOR_X, VECTOR_Y, VECTOR_Z }) {
							CTrack* track = CTrack::Alloc(SMDObj.Skeleton[bone.Id].Object,
								DescID(DescLevel(trackProp, DTYPE_VECTOR, 0), DescLevel(trackComp, DTYPE_REAL, 0)));
							SMDObj.Skeleton[bone.Id].Object->InsertTrackSorted(track);
							curves[curveIt++] = track->GetCurve();
						}
					}
					IF_PROFILING(CreateSMDAnimationInitTracksCurvesBench.StopBenchmark());

					Int32 frameIt = 0;
					for (const auto& frame : smd.SkeletonAnimation) {
						IF_PROFILING(CreateSMDAnimationTransformShortRouteBench.StartBenchmark());
						// transform
						auto point = DoBoneTransform(smd.SkeletonAnimation[frameIt++].Entries[bone.Id]);
						auto rotVec = MatrixToHPB(point, ROTATIONORDER::HPB);

						// Ensure we take the shortest route
						auto LastRotationIterator = LastBoneRotationMap.find(bone.Id);
						if (LastRotationIterator != LastBoneRotationMap.end())
						{
							Vector LastRotation = LastRotationIterator->second;
							for (const auto& rotComp : { 0, 1, 2 }) {
								while (Abs(rotVec[rotComp] - LastRotation[rotComp]) > PI) {
									if (rotVec[rotComp] < LastRotation[rotComp]) rotVec[rotComp] += PI2;
									else rotVec[rotComp] -= PI2;
								}
							}
						}
						LastBoneRotationMap[bone.Id] = rotVec;
						IF_PROFILING(CreateSMDAnimationTransformShortRouteBench.StopBenchmark());

						// add + set, pos & rot
						IF_PROFILING(CreateSMDAnimationAddSetKeysBench.StartBenchmark());
						curveIt = 0;
						for (const auto& curveProp : { point.off, rotVec }) {
							for (const auto& curveComp : { 0, 1, 2 }) {
								curves[curveIt]->AddKey(BaseTime(frame.Time, DocumentFramesPerSecond))
									->SetValue(curves[curveIt], curveProp[curveComp]);
								curveIt++;
							}
						}
						IF_PROFILING(CreateSMDAnimationAddSetKeysBench.StopBenchmark());
					}
				}
			}
		}

		/* Build Mesh */
		if (config.IncludeMesh)
		{
			IF_PROFILING(Benchmark CreateSMDBuildMeshBench("CreateSMD-BuildMesh"));
			Int32 PolyCount = (Int32)smd.Triangles.size();
			if (PolyCount != 0)
			{
				// Construct Mesh
				PolygonObject* SMDMesh = PolygonObject::Alloc(PolyCount * 3, PolyCount);
				SMDObj.Mesh = SMDMesh;
				config.doc->InsertObject(SMDMesh, RootNull, RootNull->GetDownLast());

				// Point + Polygon Locals
				auto pointHashFunc = [](const maxon::Vector& v) { return v.GetHashCode(); };
				std::unordered_map<maxon::Vector, Int32, decltype(pointHashFunc)> PointIndexMap(10, pointHashFunc);
				std::map<String, std::vector<Int32>> SelectionMap;
				auto PolygonArr = SMDMesh->GetPolygonW();
				auto PointArr = SMDMesh->GetPointW();
				
				// Normals Locals
				IF_PROFILING(Benchmark CreateSMDBuildMeshNormalsBench("CreateSMD-BuildMesh-Normals", false, false));
				NormalTag* TagNormals = nullptr;
				NormalHandle HandleNormals = nullptr;
				if (config.IncludeNormals) {
					IF_PROFILING(CreateSMDBuildMeshNormalsBench.PrintOnDestruct(true));
					SMDMesh->MakeTag(Tphong);
					TagNormals = NormalTag::Alloc(PolyCount);
					SMDMesh->InsertTag(TagNormals);
					HandleNormals = TagNormals->GetDataAddressW();
				}

				// UVW Locals
				IF_PROFILING(Benchmark CreateSMDBuildMeshUVWTagBench("CreateSMD-BuildMesh-UVWTag", false, false));
				UVWTag* pUVWTag = nullptr;
				UVWHandle hUVWData = nullptr;
				if (config.IncludeUVW) {
					IF_PROFILING(CreateSMDBuildMeshUVWTagBench.PrintOnDestruct(true));
					pUVWTag = UVWTag::Alloc(PolyCount);
					SMDMesh->InsertTag(pUVWTag);
					hUVWData = pUVWTag->GetDataAddressW();
				}

				IF_PROFILING(Benchmark CreateSMDBuildMeshPolygonsFindDupsBench("CreateSMD-BuildMesh-Polygons-FindDups", true, false));
				Int32 PolygonIterator = 0;
				Int32 PointIterator = 0;
				for (auto& triangle : smd.Triangles)
				{
					maxon::Vector C(
						triangle.Vertices[0].Position.x,
						triangle.Vertices[0].Position.y,
						triangle.Vertices[0].Position.z);
					maxon::Vector B(
						triangle.Vertices[1].Position.x,
						triangle.Vertices[1].Position.y,
						triangle.Vertices[1].Position.z);
					maxon::Vector A(
						triangle.Vertices[2].Position.x,
						triangle.Vertices[2].Position.y,
						triangle.Vertices[2].Position.z);

					C = TransformMatrix * C;
					B = TransformMatrix * B;
					A = TransformMatrix * A;

					IF_PROFILING(CreateSMDBuildMeshPolygonsFindDupsBench.StartBenchmark());
					Int32 pointIndices[3];
					Int32 pointIndicesIterator = 0;
					for (auto& point : { A, B, C }) {
						const auto& [pointIt, bPointInserted] = PointIndexMap.emplace(point, PointIterator);
						if (bPointInserted) {
							PointArr[PointIterator] = point;
							pointIndices[pointIndicesIterator++] = PointIterator++;
						}
						else {
							pointIndices[pointIndicesIterator++] = pointIt->second;
						}
					}
					IF_PROFILING(CreateSMDBuildMeshPolygonsFindDupsBench.StopBenchmark());

					PolygonArr[PolygonIterator] = CPolygon(pointIndices[0], pointIndices[1], pointIndices[2]);
					SelectionMap[triangle.Material].push_back(PolygonIterator);

					// Normals
					if (config.IncludeNormals) {
						IF_PROFILING(CreateSMDBuildMeshNormalsBench.StartBenchmark());
						NormalStruct VertexNormals;

						VertexNormals.c = RotationMatrix * maxon::Vector(
							triangle.Vertices[0].Normals.x,
							triangle.Vertices[0].Normals.y,
							triangle.Vertices[0].Normals.z);
						VertexNormals.b = RotationMatrix * maxon::Vector(
							triangle.Vertices[1].Normals.x,
							triangle.Vertices[1].Normals.y,
							triangle.Vertices[1].Normals.z);
						VertexNormals.a = RotationMatrix * maxon::Vector(
							triangle.Vertices[2].Normals.x,
							triangle.Vertices[2].Normals.y,
							triangle.Vertices[2].Normals.z);

						NormalTag::Set(HandleNormals, PolygonIterator, VertexNormals);
						IF_PROFILING(CreateSMDBuildMeshNormalsBench.StopBenchmark());
					}

					// UVW
					if (config.IncludeUVW) {
						IF_PROFILING(CreateSMDBuildMeshUVWTagBench.StartBenchmark());
						UVWStruct uvData(
							Vector(triangle.Vertices[2].u, 1 - triangle.Vertices[2].v, 0),
							Vector(triangle.Vertices[1].u, 1 - triangle.Vertices[1].v, 0),
							Vector(triangle.Vertices[0].u, 1 - triangle.Vertices[0].v, 0));
						UVWTag::Set(hUVWData, PolygonIterator, uvData);
						IF_PROFILING(CreateSMDBuildMeshUVWTagBench.StopBenchmark());
					}

					PolygonIterator++;
				}

				SMDMesh->ResizeObject(PointIterator, PolyCount);

				if (config.IncludePolySelections)
				{
					IF_PROFILING(Benchmark CreateSMDBuildMeshSelectionTagBench("CreateSMD-BuildMesh-SelectionTag"));
					/* Selection Tags */
					BaseSelect* Selector = SMDMesh->GetPolygonS();

					for (auto& p : SelectionMap)
					{
						Selector->DeselectAll();
						for (auto& index : p.second)
							Selector->Select(index);

						SelectionTag* pSelectionTag = SelectionTag::Alloc(Tpolygonselection);
						pSelectionTag->SetName(p.first);
						SMDMesh->InsertTag(pSelectionTag);

						BaseSelect* TagSelection = pSelectionTag->GetBaseSelect();
						Selector->CopyTo(TagSelection);
					}
				}

				/* Weights */
				if (config.IncludeWeights)
				{
					IF_PROFILING(Benchmark CreateSMDBuildMeshWeightTagBench("CreateSMD-BuildMesh-WeightTag"));
					CAWeightTag* WeightTag = CAWeightTag::Alloc();
					SMDMesh->InsertTag(WeightTag);
					auto SkinObj = BaseObject::Alloc(Oskin);
					config.doc->InsertObject(SkinObj, SMDMesh, nullptr);

					for (auto& Bone : SMDObj.Skeleton)
						WeightTag->AddJoint(Bone.second.Object);

					Int32 PolyIndex = 0;
					for (const auto& Poly : smd.Triangles)
					{
						auto GetParentWeight = [](const std::vector<Types::WeightmapEntry>& WeightMap) -> float
						{
							float sum = 0;
							for (const auto& entry : WeightMap)
								sum += entry.Weight;

							float val = std::floor(100 - (100 * sum)) / 100;
							return val < 0.0f ? 0.0f : val;
						};

						// C
						for (auto& w : Poly.Vertices[2].WeightMapEntries)
							WeightTag->SetWeight(w.BoneId, PolygonArr[PolyIndex].a, w.Weight);

						float CParentWeight = GetParentWeight(Poly.Vertices[2].WeightMapEntries);
						if (CParentWeight)
							WeightTag->SetWeight(Poly.Vertices[2].ParentBone, PolygonArr[PolyIndex].a, CParentWeight);

						// B
						for (auto& w : Poly.Vertices[1].WeightMapEntries)
							WeightTag->SetWeight(w.BoneId, PolygonArr[PolyIndex].b, w.Weight);

						float BParentWeight = GetParentWeight(Poly.Vertices[1].WeightMapEntries);
						if (BParentWeight)
							WeightTag->SetWeight(Poly.Vertices[1].ParentBone, PolygonArr[PolyIndex].b, BParentWeight);

						// A
						for (auto& w : Poly.Vertices[0].WeightMapEntries)
							WeightTag->SetWeight(w.BoneId, PolygonArr[PolyIndex].c, w.Weight);

						float AParentWeight = GetParentWeight(Poly.Vertices[0].WeightMapEntries);
						if (AParentWeight)
							WeightTag->SetWeight(Poly.Vertices[0].ParentBone, PolygonArr[PolyIndex].c, AParentWeight);

						++PolyIndex;
					}
				}

				SMDMesh->Message(MSG_UPDATE);
			}
		}

		while (auto Obj = RootNull->GetDown())
		{
			Obj->Remove();
			Obj->InsertBefore(RootNull);
		}

		BaseObject::Free(RootNull);

		return SMDObj;
	}

	Bool LoaderData::Init(GeListNode* node)
	{
		/* Default settings, overriden by user-prefs */
		BaseContainer* data = ((BaseList2D*)node)->GetDataInstance();
		data->SetFloat(SMD_LOADER_SCALE, 1.0f);
		data->SetVector(SMD_LOADER_ROTATE, Vector(0.0f, 0.0f, 0.0f));
		data->SetBool(SMD_LOADER_IMPORT_UNDER_NULL, false);
		data->SetBool(SMD_LOADER_IMPORT_ANIMATION, true);
		data->SetBool(SMD_LOADER_IMPORT_MESH, true);
		data->SetBool(SMD_LOADER_IMPORT_WEIGHTS, true);
		data->SetBool(SMD_LOADER_IMPORT_SKELETON, true);

		return true;
	}

	Bool LoaderData::GetDEnabling(GeListNode* node, const DescID& id, const GeData& data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc)
	{
		if (node == nullptr)
			return false;


		auto GetParam = [&node](Int32 id)->GeData
		{
			GeData Data;
			node->GetParameter(id, Data, DESCFLAGS_GET::NONE);
			return Data;
		};

		switch (id[0].id)
		{
		case SMD_LOADER_IMPORT_ANIMATION:
		{
			if (!GetParam(SMD_LOADER_IMPORT_SKELETON).GetBool())
				return false;

			break;
		}

		case SMD_LOADER_IMPORT_WEIGHTS:
		{
			if (!(
				GetParam(SMD_LOADER_IMPORT_MESH).GetBool() &&
				GetParam(SMD_LOADER_IMPORT_SKELETON).GetBool()
				))
				return false;
		}
		}

		return true;
	}

	Bool LoaderData::GetDParameter(GeListNode* node, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags)
	{
		if (node == nullptr)
			return false;

		auto GetParam = [&node](Int32 id)->GeData
		{
			static GeData Data;
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
		case SMD_LOADER_IMPORT_ANIMATION:
		{
			if (!GetParam(SMD_LOADER_IMPORT_SKELETON).GetBool())
			{
				SetFalse();
				return true;
			}

			break;
		}

		case SMD_LOADER_IMPORT_WEIGHTS:
		{
			if (!(
				GetParam(SMD_LOADER_IMPORT_MESH).GetBool() &&
				GetParam(SMD_LOADER_IMPORT_SKELETON).GetBool()
				))
			{
				SetFalse();
				return true;
			}

			break;
		}
		}

		return SceneLoaderData::GetDParameter(node, id, t_data, flags);
	}

	NodeData* LoaderData::Create()
	{
		return NewObjClear(LoaderData);
	}

	Bool LoaderData::RegisterPlugin()
	{
		return RegisterSceneLoaderPlugin(ID_SMDLOADER, "Studiomdl Data (SMD) Loader"_s, 0, LoaderData::Create, "Fsmdloader"_s);
	}
}