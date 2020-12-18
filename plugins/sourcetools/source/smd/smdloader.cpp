#include "smdloader.h"
#include "fsmdloader.h"
#include "smdparser.h"

#include "error.h"
#include "c4d_symbols.h"

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

Bool SMDLoaderData::Identify( BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size )
{
	// unfortunately SMD is an ascii format with no FourCC/Header so we will just assume
	// that the file-type is SMD based on the extension alone.
	return (name.GetSuffix().ToLower() == "smd") ? true : false;
}

FILEERROR SMDLoaderData::Load( BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt )
{
	StudiomdlData smd;
	
	if ( !ParseSMD( name, smd ) )
	{
		LogError( "PEGTL failed to parse SMD." );
		return FILEERROR::INVALID;
	}

	auto GetParam = [&node]( Int32 id )->GeData
	{
		static GeData Data;
		node->GetParameter( id, Data, DESCFLAGS_GET::NONE );
		return Data;
	};

	/* Get Parameters */
	Settings config;

	config.Scale = GetParam( SMD_LOADER_SCALE ).GetFloat();
	config.Orientation = GetParam( SMD_LOADER_ROTATE ).GetVector();
	config.IncludeSkeleton = GetParam( SMD_LOADER_IMPORT_SKELETON ).GetBool();
	config.IncludeAnimation = GetParam( SMD_LOADER_IMPORT_ANIMATION ).GetBool();
	config.IncludeMesh = GetParam( SMD_LOADER_IMPORT_MESH ).GetBool();
	config.IncludeWeights = GetParam( SMD_LOADER_IMPORT_WEIGHTS ).GetBool();
	config.IncludePolySelections = true;
	config.IncludeNormals = true;
	config.IncludeUVW = true;
	config.doc = doc;

	auto ParamUnderNull = GetParam( SMD_LOADER_IMPORT_UNDER_NULL ).GetBool();

	/* Does the heavy lifting */
	auto SMDObj = CreateSMD( smd, config );
	
	auto Name = name.GetFile();
	Name.ClearSuffix();
	if ( SMDObj.Mesh ) SMDObj.Mesh->SetName( Name.GetString() );

	if ( ParamUnderNull )
	{
		BaseObject* null = BaseObject::Alloc( Onull );
		null->SetName( Name.GetString() );
		doc->InsertObject( null, nullptr, nullptr );

		if ( config.IncludeSkeleton )
		{
			for ( auto& bone : SMDObj.Skeleton )
			{
				if ( bone.second.ParentId == -1 )
				{
					bone.second.Object->Remove();
					bone.second.Object->InsertUnderLast( null );
				}
			}
		}

		if ( SMDObj.Mesh )
		{
			SMDObj.Mesh->Remove();
			SMDObj.Mesh->InsertUnderLast( null );
		}
	}
	
	/* Set start/end time accordingly */
	if ( !( filterflags & SCENEFILTER::MERGESCENE ) && smd.SkeletonAnimation.size() > 1 && config.IncludeAnimation )
	{
		doc->SetMaxTime( BaseTime( (Float)smd.SkeletonAnimation.size() - 1, doc->GetFps() ) );
		doc->SetLoopMaxTime( BaseTime( (Float)smd.SkeletonAnimation.size() - 1, doc->GetFps() ) );
	}

	return FILEERROR::NONE;
}

SMDLoaderData::SMDObject SMDLoaderData::CreateSMD( const StudiomdlData& smd, const Settings& config )
{
	IF_PROFILING(Benchmark CreateSMDBench("CreateSMD"));
	SMDObject SMDObj;
	SMDObj.Skeleton = config.Skeleton;

	/* Transforms */
	maxon::Matrix TransformRotationMatrix =
		HPBToMatrix( config.Orientation, ROTATIONORDER::HPB )
		* MatrixScale( Vector( -1.0f, 1.0f, 1.0f ) )
		* MatrixRotX( PI / 2 );
	maxon::Matrix TransformMatrix =
		MatrixScale( Vector( config.Scale, config.Scale, config.Scale ) )
		* TransformRotationMatrix;

	BaseObject* RootNull = BaseObject::Alloc( Onull );
	config.doc->InsertObject( RootNull, nullptr, nullptr );

	if ( SMDObj.Skeleton.empty() && config.IncludeSkeleton )
	{
		IF_PROFILING(Benchmark CreateSMDBuildSkeletonBench("CreateSMD-BuildSkeleton"));

		for ( auto& bone : smd.Bones )
		{
			BoneMapData Entry;
			Entry.ParentId = bone.ParentId;
			Entry.Object = BaseObject::Alloc( Ojoint );
			Entry.Object->SetName( bone.Name );
			SMDObj.Skeleton[bone.Id] = std::move( Entry );

			if ( Entry.ParentId == -1 )
				config.doc->InsertObject( Entry.Object, RootNull, RootNull->GetDownLast() );
			else
				config.doc->InsertObject( Entry.Object,
										  SMDObj.Skeleton[Entry.ParentId].Object,
										  SMDObj.Skeleton[Entry.ParentId].Object->GetDownLast() );
		}

		Int32 DocumentFramesPerSecond = config.doc->GetFps();

		/* Set Initial Positions/Rotations On Skeleton */
		std::map<std::int16_t, Vector> LastBoneRotationMap;
		for ( auto& frame : smd.SkeletonAnimation )
		{
			if ( !config.IncludeAnimation && frame.Time != 0 ) break;

			for ( auto& bone : frame.Entries )
			{
				maxon::Matrix BoneLocalMatrix = HPBToMatrix( maxon::Vector( bone.Rotation.x, bone.Rotation.y, bone.Rotation.z ), ROTATIONORDER::XYZLOCAL );
				BoneLocalMatrix = ~BoneLocalMatrix;
				BoneLocalMatrix.off = maxon::Vector64( bone.Position.x, bone.Position.y, bone.Position.z );

				// Do Transform
				if ( SMDObj.Skeleton[bone.Id].ParentId == -1 )
					BoneLocalMatrix = TransformMatrix * BoneLocalMatrix;

				if ( frame.Time == 0 ) SMDObj.Skeleton[bone.Id].Object->SetMl( BoneLocalMatrix );

				if ( config.IncludeAnimation && smd.SkeletonAnimation.size() > 1 )
				{
					CTrack* XTrack, * YTrack, * ZTrack,
						* XRTrack, * YRTrack, * ZRTrack;
					CCurve* XCurve, * YCurve, * ZCurve,
						* XRCurve, * YRCurve, * ZRCurve;

					if ( frame.Time == 0 )
					{
						XTrack = CTrack::Alloc( SMDObj.Skeleton[bone.Id].Object,
												DescID( DescLevel( ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0 ),
												DescLevel( VECTOR_X, DTYPE_REAL, 0 ) ) );
						YTrack = CTrack::Alloc( SMDObj.Skeleton[bone.Id].Object,
												DescID( DescLevel( ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0 ),
												DescLevel( VECTOR_Y, DTYPE_REAL, 0 ) ) );
						ZTrack = CTrack::Alloc( SMDObj.Skeleton[bone.Id].Object,
												DescID( DescLevel( ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0 ),
												DescLevel( VECTOR_Z, DTYPE_REAL, 0 ) ) );
						XRTrack = CTrack::Alloc( SMDObj.Skeleton[bone.Id].Object,
												 DescID( DescLevel( ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0 ),
												 DescLevel( VECTOR_X, DTYPE_REAL, 0 ) ) );
						YRTrack = CTrack::Alloc( SMDObj.Skeleton[bone.Id].Object,
												 DescID( DescLevel( ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0 ),
												 DescLevel( VECTOR_Y, DTYPE_REAL, 0 ) ) );
						ZRTrack = CTrack::Alloc( SMDObj.Skeleton[bone.Id].Object,
												 DescID( DescLevel( ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0 ),
												 DescLevel( VECTOR_Z, DTYPE_REAL, 0 ) ) );

						SMDObj.Skeleton[bone.Id].Object->InsertTrackSorted( XTrack );
						SMDObj.Skeleton[bone.Id].Object->InsertTrackSorted( YTrack );
						SMDObj.Skeleton[bone.Id].Object->InsertTrackSorted( ZTrack );
						SMDObj.Skeleton[bone.Id].Object->InsertTrackSorted( XRTrack );
						SMDObj.Skeleton[bone.Id].Object->InsertTrackSorted( YRTrack );
						SMDObj.Skeleton[bone.Id].Object->InsertTrackSorted( ZRTrack );

						goto end_find_tracks;
					}

					SMDObj.Skeleton[bone.Id].Object->GetVectorTracks( DescID( DescLevel( ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0 ) ), XTrack, YTrack, ZTrack );
					SMDObj.Skeleton[bone.Id].Object->GetVectorTracks( DescID( DescLevel( ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0 ) ), XRTrack, YRTrack, ZRTrack );

				end_find_tracks:;

					XCurve = XTrack->GetCurve();
					YCurve = YTrack->GetCurve();
					ZCurve = ZTrack->GetCurve();
					XRCurve = XRTrack->GetCurve();
					YRCurve = YRTrack->GetCurve();
					ZRCurve = ZRTrack->GetCurve();

					CKey* XKey = XCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
					XKey->SetValue( XCurve, BoneLocalMatrix.off.x );
					CKey* YKey = YCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
					YKey->SetValue( YCurve, BoneLocalMatrix.off.y );
					CKey* ZKey = ZCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
					ZKey->SetValue( ZCurve, BoneLocalMatrix.off.z );

					maxon::Vector RotationVector = MatrixToHPB( BoneLocalMatrix, ROTATIONORDER::HPB );

					// Ensure we take the shortest route
					auto LastRotationIterator = LastBoneRotationMap.find( bone.Id );
					if ( LastRotationIterator != LastBoneRotationMap.end() )
					{
						Vector LastRotation = LastRotationIterator->second;

						while ( Abs( RotationVector.x - LastRotation.x ) > PI )
						{
							if ( RotationVector.x >= LastRotation.x )
								RotationVector.x -= 2 * PI;
							else
								RotationVector.x += 2 * PI;
						}

						while ( Abs( RotationVector.y - LastRotation.y ) > PI )
						{
							if ( RotationVector.y >= LastRotation.y )
								RotationVector.y -= 2 * PI;
							else
								RotationVector.y += 2 * PI;
						}

						while ( Abs( RotationVector.z - LastRotation.z ) > PI )
						{
							if ( RotationVector.z >= LastRotation.z )
								RotationVector.z -= 2 * PI;
							else
								RotationVector.z += 2 * PI;
						}
					}

					LastBoneRotationMap[bone.Id] = RotationVector;

					CKey* XRKey = XRCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
					XRKey->SetValue( XRCurve, RotationVector.x );
					CKey* YRKey = YRCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
					YRKey->SetValue( YRCurve, RotationVector.y );
					CKey* ZRKey = ZRCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
					ZRKey->SetValue( ZRCurve, RotationVector.z );
				}
			}
		}
	}

	/* Build Mesh */
	if ( config.IncludeMesh )
	{
		IF_PROFILING(Benchmark CreateSMDBuildMeshBench("CreateSMD-BuildMesh"));
		Int32 PolyCount = (Int32)smd.Triangles.size();
		if ( PolyCount != 0 )
		{
			PolygonObject* SMDMesh = PolygonObject::Alloc( PolyCount * 3, PolyCount );
			SMDObj.Mesh = SMDMesh;
			config.doc->InsertObject( SMDMesh, RootNull, RootNull->GetDownLast() );

			std::vector<maxon::Vector> PointVec;
			std::map<String, std::vector<Int32>> SelectionMap;
			auto PolygonArr = SMDMesh->GetPolygonW();

			{
				IF_PROFILING(Benchmark CreateSMDBuildMeshPolyonsBench("CreateSMD-BuildMesh-Polygons"));
				Int32 PolygonIterator = 0;
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

					Int32 Aindex = -1, Bindex = -1, Cindex = -1;

					for (Int32 i = Int32(PointVec.size() - 1); i >= 0; i--)
					{
						if (Aindex >= 0 && Bindex >= 0 && Cindex >= 0)
							break;

						if (PointVec[i] == A) Aindex = i;
						else if (PointVec[i] == B) Bindex = i;
						else if (PointVec[i] == C) Cindex = i;
					}

					if (Aindex == -1)
					{
						PointVec.push_back(A);
						Aindex = Int32(PointVec.size() - 1);
					}

					if (Bindex == -1)
					{
						PointVec.push_back(B);
						Bindex = Int32(PointVec.size() - 1);
					}

					if (Cindex == -1)
					{
						PointVec.push_back(C);
						Cindex = Int32(PointVec.size() - 1);
					}

					PolygonArr[PolygonIterator] = CPolygon(Aindex, Bindex, Cindex);
					SelectionMap[triangle.Material].push_back(PolygonIterator++);
				}

				SMDMesh->ResizeObject(Int32(PointVec.size()), PolyCount);
				std::move(PointVec.begin(), PointVec.end(), SMDMesh->GetPointW());
			}

			if (config.IncludeNormals)
			{
				IF_PROFILING(Benchmark CreateSMDBuildMeshNormalsBench("CreateSMD-BuildMesh-Normals"));
				/* Normals */
				SMDMesh->MakeTag(Tphong);
				NormalTag* TagNormals = NormalTag::Alloc(PolyCount);
				SMDMesh->InsertTag(TagNormals);
				NormalHandle HandleNormals = TagNormals->GetDataAddressW();

				for (Int32 i = 0; i < PolyCount; ++i)
				{
					NormalStruct VertexNormals;

					VertexNormals.c = TransformRotationMatrix * maxon::Vector(
						smd.Triangles[i].Vertices[0].Normals.x,
						smd.Triangles[i].Vertices[0].Normals.y,
						smd.Triangles[i].Vertices[0].Normals.z);
					VertexNormals.b = TransformRotationMatrix * maxon::Vector(
						smd.Triangles[i].Vertices[1].Normals.x,
						smd.Triangles[i].Vertices[1].Normals.y,
						smd.Triangles[i].Vertices[1].Normals.z);
					VertexNormals.a = TransformRotationMatrix * maxon::Vector(
						smd.Triangles[i].Vertices[2].Normals.x,
						smd.Triangles[i].Vertices[2].Normals.y,
						smd.Triangles[i].Vertices[2].Normals.z);

					NormalTag::Set(HandleNormals, i, VertexNormals);
				}
			}

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

			if (config.IncludeUVW)
			{
				IF_PROFILING(Benchmark CreateSMDBuildMeshUVWTagBench("CreateSMD-BuildMesh-UVWTag"));
				/* UVW Tag */
				UVWTag* pUVWTag = UVWTag::Alloc(PolyCount);
				SMDMesh->InsertTag(pUVWTag);
				UVWHandle hUVWData = pUVWTag->GetDataAddressW();

				Int32 PolyIndex = 0;
				for (const auto& Poly : smd.Triangles)
				{
					UVWStruct uvData(
						Vector(Poly.Vertices[2].u, 1 - Poly.Vertices[2].v, 0),
						Vector(Poly.Vertices[1].u, 1 - Poly.Vertices[1].v, 0),
						Vector(Poly.Vertices[0].u, 1 - Poly.Vertices[0].v, 0));
					UVWTag::Set(hUVWData, PolyIndex++, uvData);
				}
			}

			/* Weights */
			if ( config.IncludeWeights )
			{
				IF_PROFILING(Benchmark CreateSMDBuildMeshWeightTagBench("CreateSMD-BuildMesh-WeightTag"));
				CAWeightTag* WeightTag = CAWeightTag::Alloc();
				SMDMesh->InsertTag( WeightTag );
				auto SkinObj = BaseObject::Alloc( Oskin );
				config.doc->InsertObject( SkinObj, SMDMesh, nullptr );

				for ( auto& Bone : SMDObj.Skeleton )
					WeightTag->AddJoint( Bone.second.Object );

				Int32 PolyIndex = 0;
				for ( const auto& Poly : smd.Triangles )
				{
					auto GetParentWeight = []( const std::vector<SMDTypes::WeightmapEntry>& WeightMap ) -> float
					{
						float sum = 0;
						for ( const auto& entry : WeightMap )
							sum += entry.Weight;

						float val = std::floor( 100 - ( 100 * sum ) ) / 100;
						return val < 0.0f ? 0.0f : val;
					};

					// C
					for ( auto& w : Poly.Vertices[2].WeightMapEntries )
						WeightTag->SetWeight( w.BoneId, PolygonArr[PolyIndex].a, w.Weight );
					
					float CParentWeight = GetParentWeight( Poly.Vertices[2].WeightMapEntries );
					if ( CParentWeight )
						WeightTag->SetWeight( Poly.Vertices[2].ParentBone, PolygonArr[PolyIndex].a, CParentWeight );

					// B
					for ( auto& w : Poly.Vertices[1].WeightMapEntries )
						WeightTag->SetWeight( w.BoneId, PolygonArr[PolyIndex].b, w.Weight );
					
					float BParentWeight = GetParentWeight( Poly.Vertices[1].WeightMapEntries );
					if ( BParentWeight )
						WeightTag->SetWeight( Poly.Vertices[1].ParentBone, PolygonArr[PolyIndex].b, BParentWeight );

					// A
					for ( auto& w : Poly.Vertices[0].WeightMapEntries )
						WeightTag->SetWeight( w.BoneId, PolygonArr[PolyIndex].c, w.Weight );
					
					float AParentWeight = GetParentWeight( Poly.Vertices[0].WeightMapEntries );
					if ( AParentWeight )
						WeightTag->SetWeight( Poly.Vertices[0].ParentBone, PolygonArr[PolyIndex].c, AParentWeight );

					++PolyIndex;
				}
			}

			SMDMesh->Message(MSG_UPDATE);
		}
	}

	while ( auto Obj = RootNull->GetDown() )
	{
		Obj->Remove();
		Obj->InsertBefore( RootNull );
	}

	BaseObject::Free( RootNull );

	return SMDObj;
}

Bool SMDLoaderData::Init( GeListNode *node )
{
	/* Default settings, overriden by user-prefs */
	BaseContainer *data = ( (BaseList2D *)node )->GetDataInstance();
	data->SetFloat( SMD_LOADER_SCALE, 1.0f );
	data->SetVector( SMD_LOADER_ROTATE, Vector( 0.0f, 0.0f, 0.0f ) );
	data->SetBool( SMD_LOADER_IMPORT_UNDER_NULL, false );
	data->SetBool( SMD_LOADER_IMPORT_ANIMATION, true );
	data->SetBool( SMD_LOADER_IMPORT_MESH, true );
	data->SetBool( SMD_LOADER_IMPORT_WEIGHTS, true );
	data->SetBool( SMD_LOADER_IMPORT_SKELETON, true );

	return true;
}

Bool SMDLoaderData::GetDEnabling( GeListNode* node, const DescID& id, const GeData& data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc )
{
	if ( node == nullptr )
		return false;


	auto GetParam = [&node]( Int32 id )->GeData
	{
		GeData Data;
		node->GetParameter( id, Data, DESCFLAGS_GET::NONE );
		return Data;
	};

	switch ( id[0].id )
	{
		case SMD_LOADER_IMPORT_ANIMATION:
		{
			if ( !GetParam( SMD_LOADER_IMPORT_SKELETON ).GetBool() )
				return false;

			break;
		}

		case SMD_LOADER_IMPORT_WEIGHTS:
		{
			if ( !(
				GetParam( SMD_LOADER_IMPORT_MESH ).GetBool() &&
				GetParam( SMD_LOADER_IMPORT_SKELETON ).GetBool()
				) )
				return false;
		}
	}

	return true;
}

Bool SMDLoaderData::GetDParameter( GeListNode* node, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags )
{
	if ( node == nullptr )
		return false;

	auto GetParam = [&node]( Int32 id )->GeData
	{
		static GeData Data;
		node->GetParameter( id, Data, DESCFLAGS_GET::NONE );
		return Data;
	};

	auto SetFalse = [&t_data, &flags]( void ) -> void
	{
		t_data.SetInt32( 0 );
		flags |= DESCFLAGS_GET::PARAM_GET;
	};

	switch ( id[0].id )
	{
		case SMD_LOADER_IMPORT_ANIMATION:
		{
			if ( !GetParam( SMD_LOADER_IMPORT_SKELETON ).GetBool() )
			{
				SetFalse();
				return true;
			}

			break;
		}

		case SMD_LOADER_IMPORT_WEIGHTS:
		{
			if ( !(
				GetParam( SMD_LOADER_IMPORT_MESH ).GetBool() &&
				GetParam( SMD_LOADER_IMPORT_SKELETON ).GetBool()
				) )
			{
				SetFalse();
				return true;
			}

			break;
		}
	}

	return SceneLoaderData::GetDParameter( node, id, t_data, flags );
}

NodeData* SMDLoaderData::Create()
{
	return NewObjClear( SMDLoaderData );
}

Bool SMDLoaderData::RegisterPlugin()
{
	if ( !RegisterSceneLoaderPlugin(ID_SMDLOADER, "Studiomdl Data (SMD) Loader"_s, 0, SMDLoaderData::Create, "Fsmdloader"_s) )
		return false;

	return true;
}