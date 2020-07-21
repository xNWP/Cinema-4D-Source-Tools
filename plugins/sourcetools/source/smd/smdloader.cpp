#include "smdloader.h"
#include "fsmdloader.h"
#include "smdparser.h"

#include "c4dst_error.h"

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

#include <map>
#include <unordered_map>

template <>
struct std::hash<maxon::Vector>
{
	std::size_t operator()( const maxon::Vector& vec ) const
	{
		return vec.GetHashCode();
	}
};

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

	maxon::String SmdName = name.GetFileString().SubStr( 0, name.GetFileString().GetLength() - 4 );

	/* Get Parameters */
	Settings config;

	config.Scale = node->GetData().GetFloat( SMD_LOADER_SCALE, 1.0f );
	config.Orientation = node->GetData().GetVector( SMD_LOADER_ROTATE );
	config.IncludeAnimation = node->GetData().GetBool( SMD_LOADER_IMPORT_ANIMATION, true );
	config.IncludeMesh = node->GetData().GetBool( SMD_LOADER_IMPORT_MESH, true );
	config.IncludeWeights = node->GetData().GetBool( SMD_LOADER_IMPORT_WEIGHTS, true );
	config.IncludeSkeleton = node->GetData().GetBool( SMD_LOADER_IMPORT_SKELETON, true );

	if ( node->GetData().GetBool( SMD_LOADER_IMPORT_UNDER_NULL, false ) )
	{
		config.MeshRootObject = BaseObject::Alloc( Onull );
		config.MeshRootObject->SetName( SmdName );
		doc->InsertObject( config.MeshRootObject, nullptr, nullptr );
	}
	else
	{
		config.MeshRootObject = nullptr;
	}

	/* Does the heavy lifting */
	CreateSMD( smd, SmdName, config, doc);

	/* Set start/end time accordingly */
	if ( !( filterflags & SCENEFILTER::MERGESCENE ) && smd.SkeletonAnimation.size() > 1 && config.IncludeAnimation )
	{
		doc->SetMaxTime( BaseTime( (Float)smd.SkeletonAnimation.size() - 1, doc->GetFps() ) );
		doc->SetLoopMaxTime( BaseTime( (Float)smd.SkeletonAnimation.size() - 1, doc->GetFps() ) );
	}

	// TODO: Profiling, Meta

	return FILEERROR::NONE;
}

SMDLoaderData::SMDObject SMDLoaderData::CreateSMD( const StudiomdlData& smd, const maxon::String& name, SMDLoaderData::Settings config, BaseDocument* doc)
{
	SMDObject ActiveSMDObject;
	if ( !config.SkeletonRootObject )
	{
		config.SkeletonRootObject = config.MeshRootObject;
	}

	/* Transforms */
	maxon::Matrix TransformRotationMatrix =
		HPBToMatrix( config.Orientation, ROTATIONORDER::HPB )
		* MatrixScale( Vector( -1.0f, 1.0f, 1.0f ) )
		* MatrixRotX( PI / 2 );
	maxon::Matrix TransformMatrix =
		MatrixScale( Vector( config.Scale, config.Scale, config.Scale ) )
		* TransformRotationMatrix;

	if ( !config.Skeleton && config.IncludeSkeleton )
	{
		config.Skeleton = std::make_shared<std::map<std::int16_t, BoneMapData>>();
		ActiveSMDObject.Skeleton = config.Skeleton;

		for ( auto& bone : smd.Bones )
		{
			BoneMapData Entry;
			Entry.ParentId = bone.ParentId;
			Entry.Object = BaseObject::Alloc( Ojoint );
			Entry.Object->SetName( maxon::String( bone.Name.c_str() ) );
			( *config.Skeleton )[bone.Id] = std::move( Entry );

			if ( bone.ParentId == -1 )
			{
				doc->InsertObject( ( *config.Skeleton )[bone.Id].Object, config.SkeletonRootObject, nullptr );
			}
			else
			{
				doc->InsertObject( ( *config.Skeleton )[bone.Id].Object, ( *config.Skeleton )[bone.ParentId].Object, nullptr );
			}
		}

		Int32 DocumentFramesPerSecond = doc->GetFps();

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
				if ( ( *config.Skeleton )[bone.Id].ParentId == -1 )
					BoneLocalMatrix = TransformMatrix * BoneLocalMatrix;

				if ( frame.Time == 0 ) ( *config.Skeleton )[bone.Id].Object->SetMl( BoneLocalMatrix );

				if ( config.IncludeAnimation && smd.SkeletonAnimation.size() > 1 )
				{
					CTrack* XTrack, * YTrack, * ZTrack,
						* XRTrack, * YRTrack, * ZRTrack;
					CCurve* XCurve, * YCurve, * ZCurve,
						* XRCurve, * YRCurve, * ZRCurve;

					if ( frame.Time == 0 )
					{
						XTrack = CTrack::Alloc( ( *config.Skeleton )[bone.Id].Object,
												DescID( DescLevel( ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0 ),
												DescLevel( VECTOR_X, DTYPE_REAL, 0 ) ) );
						YTrack = CTrack::Alloc( ( *config.Skeleton )[bone.Id].Object,
												DescID( DescLevel( ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0 ),
												DescLevel( VECTOR_Y, DTYPE_REAL, 0 ) ) );
						ZTrack = CTrack::Alloc( ( *config.Skeleton )[bone.Id].Object,
												DescID( DescLevel( ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0 ),
												DescLevel( VECTOR_Z, DTYPE_REAL, 0 ) ) );
						XRTrack = CTrack::Alloc( ( *config.Skeleton )[bone.Id].Object,
												 DescID( DescLevel( ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0 ),
												 DescLevel( VECTOR_X, DTYPE_REAL, 0 ) ) );
						YRTrack = CTrack::Alloc( ( *config.Skeleton )[bone.Id].Object,
												 DescID( DescLevel( ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0 ),
												 DescLevel( VECTOR_Y, DTYPE_REAL, 0 ) ) );
						ZRTrack = CTrack::Alloc( ( *config.Skeleton )[bone.Id].Object,
												 DescID( DescLevel( ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0 ),
												 DescLevel( VECTOR_Z, DTYPE_REAL, 0 ) ) );

						( *config.Skeleton )[bone.Id].Object->InsertTrackSorted( XTrack );
						( *config.Skeleton )[bone.Id].Object->InsertTrackSorted( YTrack );
						( *config.Skeleton )[bone.Id].Object->InsertTrackSorted( ZTrack );
						( *config.Skeleton )[bone.Id].Object->InsertTrackSorted( XRTrack );
						( *config.Skeleton )[bone.Id].Object->InsertTrackSorted( YRTrack );
						( *config.Skeleton )[bone.Id].Object->InsertTrackSorted( ZRTrack );

						goto end_find_tracks;
					}

					( *config.Skeleton )[bone.Id].Object->GetVectorTracks( DescID( DescLevel( ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0 ) ), XTrack, YTrack, ZTrack );
					( *config.Skeleton )[bone.Id].Object->GetVectorTracks( DescID( DescLevel( ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0 ) ), XRTrack, YRTrack, ZRTrack );

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
		Int32 PolyCount = (Int32)smd.Triangles.size();
		if ( PolyCount != 0 )
		{
			PolygonObject* SMDMesh = PolygonObject::Alloc( 0, 0 );
			ActiveSMDObject.Mesh = SMDMesh;
			SMDMesh->SetName( name );

			doc->InsertObject( SMDMesh, config.MeshRootObject, nullptr );

			AutoAlloc<Modeling> Modeler;
			Modeler->InitObject( SMDMesh );

			std::unordered_map<maxon::Vector, std::vector<Int32>> PointMap;
			std::vector<Int32> PointIndex;
			std::map<std::string, std::vector<Int32>> SelectionMap;
			Int32 PolygonIterator = 0;

			for ( auto& triangle : smd.Triangles )
			{
				maxon::Vector C(
					triangle.Vertices[0].Position.x,
					triangle.Vertices[0].Position.y,
					triangle.Vertices[0].Position.z );
				maxon::Vector B(
					triangle.Vertices[1].Position.x,
					triangle.Vertices[1].Position.y,
					triangle.Vertices[1].Position.z );
				maxon::Vector A(
					triangle.Vertices[2].Position.x,
					triangle.Vertices[2].Position.y,
					triangle.Vertices[2].Position.z );

				C = TransformMatrix * C;
				B = TransformMatrix * B;
				A = TransformMatrix * A;

				PointIndex.push_back( Modeler->AddPoint( SMDMesh, A ) );
				PointMap[A].push_back( PointIndex.back() );
				PointIndex.push_back( Modeler->AddPoint( SMDMesh, B ) );
				PointMap[B].push_back( PointIndex.back() );
				PointIndex.push_back( Modeler->AddPoint( SMDMesh, C ) );
				PointMap[C].push_back( PointIndex.back() );

				Int32* pAdr = &PointIndex[PointIndex.size() - 3];
				Modeler->CreateNgon( SMDMesh, pAdr, 3 );

				SelectionMap[triangle.Material].push_back( PolygonIterator++ );
			}

			Modeler->Commit( SMDMesh );

			/* Normals */
			SMDMesh->MakeTag( Tphong );
			NormalTag* TagNormals = NormalTag::Alloc( PolyCount );
			SMDMesh->InsertTag( TagNormals );
			NormalHandle HandleNormals = TagNormals->GetDataAddressW();

			for ( Int32 i = 0; i < PolyCount; ++i )
			{
				NormalStruct VertexNormals;

				VertexNormals.c = TransformRotationMatrix * maxon::Vector(
					smd.Triangles[i].Vertices[0].Normals.x,
					smd.Triangles[i].Vertices[0].Normals.y,
					smd.Triangles[i].Vertices[0].Normals.z );
				VertexNormals.b = TransformRotationMatrix * maxon::Vector(
					smd.Triangles[i].Vertices[1].Normals.x,
					smd.Triangles[i].Vertices[1].Normals.y,
					smd.Triangles[i].Vertices[1].Normals.z );
				VertexNormals.a = TransformRotationMatrix * maxon::Vector(
					smd.Triangles[i].Vertices[2].Normals.x,
					smd.Triangles[i].Vertices[2].Normals.y,
					smd.Triangles[i].Vertices[2].Normals.z );

				NormalTag::Set( HandleNormals, i, VertexNormals );
			}

			/* Selection Tags */
			BaseSelect* Selector = SMDMesh->GetPolygonS();

			for ( auto& p : SelectionMap )
			{
				Selector->DeselectAll();
				for ( auto& index : p.second )
					Selector->Select( index );

				SelectionTag* pSelectionTag = SelectionTag::Alloc( Tpolygonselection );
				pSelectionTag->SetName( maxon::String( p.first.c_str() ) );
				SMDMesh->InsertTag( pSelectionTag );

				BaseSelect* TagSelection = pSelectionTag->GetBaseSelect();
				Selector->CopyTo( TagSelection );
			}

			/* UVW Tag */
			UVWTag* pUVWTag = UVWTag::Alloc( PolyCount );
			SMDMesh->InsertTag( pUVWTag );
			UVWHandle hUVWData = pUVWTag->GetDataAddressW();

			Int32 PolyIndex = 0;
			for ( const auto& Poly : smd.Triangles )
			{
				UVWStruct uvData(
					Vector( Poly.Vertices[2].u, 1 - Poly.Vertices[2].v, 0 ),
					Vector( Poly.Vertices[1].u, 1 - Poly.Vertices[1].v, 0 ),
					Vector( Poly.Vertices[0].u, 1 - Poly.Vertices[0].v, 0 ) );
				UVWTag::Set( hUVWData, PolyIndex++, uvData );
			}

			/* Weights */
			if ( config.IncludeWeights )
			{
				CAWeightTag* WeightTag = CAWeightTag::Alloc();
				SMDMesh->InsertTag( WeightTag );
				BaseObject* SkinObject = BaseObject::Alloc( Oskin );
				doc->InsertObject( SkinObject, SMDMesh, nullptr );

				for ( auto& Bone : ( *config.Skeleton ) )
					WeightTag->AddJoint( Bone.second.Object );

				PolyIndex = 0;
				for ( const auto& Poly : smd.Triangles )
				{
					// C
					Int32 PointIndex = PolyIndex * 3;
					for ( auto& w : Poly.Vertices[2].WeightMapEntries )
						WeightTag->SetWeight( w.BoneId, PointIndex, w.Weight );

					// B
					++PointIndex;
					for ( auto& w : Poly.Vertices[1].WeightMapEntries )
						WeightTag->SetWeight( w.BoneId, PointIndex, w.Weight );

					// C
					++PointIndex;
					for ( auto& w : Poly.Vertices[0].WeightMapEntries )
						WeightTag->SetWeight( w.BoneId, PointIndex, w.Weight );

					++PolyIndex;
				}
			}

			/* Weld Identical Points */
			for ( auto& Point : PointMap )
			{
				auto FirstIndex = Point.second.begin();
				for ( auto OtherIndex = FirstIndex + 1; OtherIndex != Point.second.end(); OtherIndex++ )
				{
					Modeler->WeldPoints( SMDMesh, *OtherIndex, *FirstIndex );
				}
			}

			// Commit changes
			Modeler->Commit( SMDMesh );
		}
	}

	return ActiveSMDObject;
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