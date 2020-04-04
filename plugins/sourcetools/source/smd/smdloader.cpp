#include "smdloader.h"

#include "fsmdloader.h"

#include "parser.h"

#include "c4d_baseobject.h"
#include "c4d_basedocument.h"
#include "c4d_canimation.h"
#include "lib_description.h"
#include "obase.h"
#include "lib_modeling.h"
#include "c4d_basetag.h"
#include "c4d_baseselect.h"
#include "lib_ca.h"

#include <map>

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
		return FILEERROR::INVALID;
	}

	struct BoneMapData
	{
		std::int16_t ParentId;
		BaseObject *Object;

		/* Maps Matrix Over Time */
		std::map<std::uint32_t, maxon::Matrix> GlobalMatricesOverTime;
	};

	/* Get Parameters */
	Float ParamScale = node->GetData().GetFloat( SMD_LOADER_SCALE, 1.0f );
	maxon::Vector ParamOrientation = node->GetData().GetVector( SMD_LOADER_ROTATE );
	maxon::Bool ParamImportUnderNull = node->GetData().GetBool( SMD_LOADER_IMPORT_UNDER_NULL, false );
	maxon::Bool ParamIncludeAnimation = node->GetData().GetBool( SMD_LOADER_IMPORT_ANIMATION, true );
	maxon::Bool ParamIncludeMesh = node->GetData().GetBool( SMD_LOADER_IMPORT_MESH, true );

	/* Create Skeleton */
	using Map_BoneId_BoneMapData = std::map<std::int16_t, BoneMapData>;
	Map_BoneId_BoneMapData BoneMap;

	BaseObject* RootObject = nullptr;
	if ( ParamImportUnderNull )
	{
		RootObject = BaseObject::Alloc( Onull );
		RootObject->SetName( name.GetFileString().SubStr( 0, name.GetFileString().GetLength() - 4 ) );
		doc->InsertObject( RootObject, nullptr, nullptr );
	}

	for ( auto &bone : smd.Bones )
	{
		BoneMapData Entry;
		Entry.ParentId = bone.ParentId;
		Entry.Object = BaseObject::Alloc( Ojoint );
		Entry.Object->SetName( maxon::String( bone.Name.c_str() ) );
		BoneMap[bone.Id] = std::move(Entry);

		if ( bone.ParentId == -1 )
		{
			doc->InsertObject( BoneMap[bone.Id].Object, RootObject, nullptr );
		}
		else
		{
			doc->InsertObject( BoneMap[bone.Id].Object, BoneMap[bone.ParentId].Object, nullptr );
		}
	}
	

	Int32 DocumentFramesPerSecond = doc->GetFps();
	BaseTime OriginalTime = doc->GetTime();

	/* Transforms */
	maxon::Matrix TransformMatrix =
		MatrixScale( Vector( ParamScale, ParamScale, ParamScale ) )
		* HPBToMatrix( ParamOrientation, ROTATIONORDER::HPB )
		* MatrixScale( Vector( -1.0f, 1.0f, 1.0f ) )
		* MatrixRotX( PI / 2 );

	/* Set Initial Positions/Rotations On Skeleton */
	for ( auto &frame : smd.SkeletonAnimation )
	{
		if ( !ParamIncludeAnimation && frame.Time != 0 ) break;

		doc->SetTime( BaseTime( frame.Time, DocumentFramesPerSecond ) );

		for ( auto &bone : frame.Entries )
		{
			maxon::Matrix BoneMatrix = HPBToMatrix( maxon::Vector( bone.Rotation.x, bone.Rotation.y, bone.Rotation.z ), ROTATIONORDER::XYZLOCAL );
			BoneMatrix = ~BoneMatrix;

			BoneMatrix.off = maxon::Vector64( bone.Position.x, bone.Position.y, bone.Position.z );
			
			if ( BoneMap[bone.Id].ParentId == -1 ) // root
			{
				BoneMap[bone.Id].GlobalMatricesOverTime[frame.Time] = BoneMatrix;
			}
			else
			{
				auto &ParentGlobalMatrices = BoneMap[BoneMap[bone.Id].ParentId].GlobalMatricesOverTime;
				for ( auto it = ParentGlobalMatrices.rbegin(); it != ParentGlobalMatrices.rend(); ++it )
				{
					if ( it->first <= frame.Time )
					{
						// Found parent matrix at same or closest time
						BoneMatrix = it->second * BoneMatrix;
						BoneMap[bone.Id].GlobalMatricesOverTime[frame.Time] = BoneMatrix;
						break;
					}
				}
			}

			/* Do Transforms */
			BoneMatrix = TransformMatrix * BoneMatrix;

			/* Set Bind Pose */
			if (frame.Time == 0) BoneMap[bone.Id].Object->SetMg( BoneMatrix );

			if ( ParamIncludeAnimation && smd.SkeletonAnimation.size() > 1 )
			{
				CTrack *XTrack, *YTrack, *ZTrack,
					*XRTrack, *YRTrack, *ZRTrack;
				CCurve *XCurve, *YCurve, *ZCurve,
					*XRCurve, *YRCurve, *ZRCurve;

				if ( frame.Time == 0 )
				{
					XTrack = CTrack::Alloc( BoneMap[bone.Id].Object,
											DescID( DescLevel( ID_BASEOBJECT_GLOBAL_POSITION, DTYPE_VECTOR, 0 ),
													DescLevel( VECTOR_X, DTYPE_REAL, 0 ) ) );
					YTrack = CTrack::Alloc( BoneMap[bone.Id].Object,
											DescID( DescLevel( ID_BASEOBJECT_GLOBAL_POSITION, DTYPE_VECTOR, 0 ),
													DescLevel( VECTOR_Y, DTYPE_REAL, 0 ) ) );
					ZTrack = CTrack::Alloc( BoneMap[bone.Id].Object,
											DescID( DescLevel( ID_BASEOBJECT_GLOBAL_POSITION, DTYPE_VECTOR, 0 ),
													DescLevel( VECTOR_Z, DTYPE_REAL, 0 ) ) );
					XRTrack = CTrack::Alloc( BoneMap[bone.Id].Object,
											DescID( DescLevel( ID_BASEOBJECT_GLOBAL_ROTATION, DTYPE_VECTOR, 0 ),
													DescLevel( VECTOR_X, DTYPE_REAL, 0 ) ) );
					YRTrack = CTrack::Alloc( BoneMap[bone.Id].Object,
											DescID( DescLevel( ID_BASEOBJECT_GLOBAL_ROTATION, DTYPE_VECTOR, 0 ),
													DescLevel( VECTOR_Y, DTYPE_REAL, 0 ) ) );
					ZRTrack = CTrack::Alloc( BoneMap[bone.Id].Object,
											DescID( DescLevel( ID_BASEOBJECT_GLOBAL_ROTATION, DTYPE_VECTOR, 0 ),
													DescLevel( VECTOR_Z, DTYPE_REAL, 0 ) ) );

					BoneMap[bone.Id].Object->InsertTrackSorted( XTrack );
					BoneMap[bone.Id].Object->InsertTrackSorted( YTrack );
					BoneMap[bone.Id].Object->InsertTrackSorted( ZTrack );
					BoneMap[bone.Id].Object->InsertTrackSorted( XRTrack );
					BoneMap[bone.Id].Object->InsertTrackSorted( YRTrack );
					BoneMap[bone.Id].Object->InsertTrackSorted( ZRTrack );

					goto end_find_tracks;
				}

				BoneMap[bone.Id].Object->GetVectorTracks( DescID( DescLevel( ID_BASEOBJECT_GLOBAL_POSITION, DTYPE_VECTOR, 0 ) ), XTrack, YTrack, ZTrack );
				BoneMap[bone.Id].Object->GetVectorTracks( DescID( DescLevel( ID_BASEOBJECT_GLOBAL_ROTATION, DTYPE_VECTOR, 0 ) ), XRTrack, YRTrack, ZRTrack );

			end_find_tracks:;

				XCurve = XTrack->GetCurve();
				YCurve = YTrack->GetCurve();
				ZCurve = ZTrack->GetCurve();
				XRCurve = XRTrack->GetCurve();
				YRCurve = YRTrack->GetCurve();
				ZRCurve = ZRTrack->GetCurve();

				CKey *XKey = XCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
				XKey->SetValue( XCurve, BoneMatrix.off.x );
				CKey *YKey = YCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
				YKey->SetValue( YCurve, BoneMatrix.off.y );
				CKey *ZKey = ZCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
				ZKey->SetValue( ZCurve, BoneMatrix.off.z );

				maxon::Vector RotationVector = MatrixToHPB( BoneMatrix, ROTATIONORDER::HPB );

				CKey *XRKey = XRCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
				XRKey->SetValue( XRCurve, RotationVector.x );
				CKey *YRKey = YRCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
				YRKey->SetValue( YRCurve, RotationVector.y );
				CKey *ZRKey = ZRCurve->AddKey( BaseTime( frame.Time, DocumentFramesPerSecond ) );
				ZRKey->SetValue( ZRCurve, RotationVector.z );
			}
		}
	}

	/* Set start/end time accordingly */
	if ( !( filterflags & SCENEFILTER::MERGESCENE ) && smd.SkeletonAnimation.size() > 1 && ParamIncludeAnimation )
	{
		doc->SetMaxTime( BaseTime( (Float)smd.SkeletonAnimation.size(), DocumentFramesPerSecond ) );
		doc->SetLoopMaxTime( BaseTime( (Float)smd.SkeletonAnimation.size(), DocumentFramesPerSecond ) );
	}

	doc->SetTime( OriginalTime );

	/* Build Mesh */
	if ( ParamIncludeMesh )
	{
		Int32 PolyCount = (Int32)smd.Triangles.size();
		if ( PolyCount != 0 )
		{
			PolygonObject* SMDMesh = PolygonObject::Alloc( 0, 0 );
			SMDMesh->SetName( name.GetFileString().SubStr( 0, name.GetFileString().GetLength() - 4 ) );

			doc->InsertObject( SMDMesh, RootObject, nullptr );

			AutoAlloc<Modeling> Modeler;
			Modeler->InitObject( SMDMesh );

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
				PointIndex.push_back( Modeler->AddPoint( SMDMesh, B ) );
				PointIndex.push_back( Modeler->AddPoint( SMDMesh, C ) );

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

				VertexNormals.c = TransformMatrix * maxon::Vector(
					smd.Triangles[i].Vertices[0].Normals.x,
					smd.Triangles[i].Vertices[0].Normals.y,
					smd.Triangles[i].Vertices[0].Normals.z );
				VertexNormals.b = TransformMatrix * maxon::Vector(
					smd.Triangles[i].Vertices[1].Normals.x,
					smd.Triangles[i].Vertices[1].Normals.y,
					smd.Triangles[i].Vertices[1].Normals.z );
				VertexNormals.a = TransformMatrix * maxon::Vector(
					smd.Triangles[i].Vertices[2].Normals.x,
					smd.Triangles[i].Vertices[2].Normals.y,
					smd.Triangles[i].Vertices[2].Normals.z );

				NormalTag::Set( HandleNormals, i, VertexNormals );
			}

			SMDMesh->Message( MSG_UPDATE );

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
			CAWeightTag* WeightTag = CAWeightTag::Alloc();
			SMDMesh->InsertTag( WeightTag );
			BaseObject* SkinObject = BaseObject::Alloc( Oskin );
			doc->InsertObject( SkinObject, SMDMesh, nullptr );

			for ( auto& Bone : BoneMap )
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
	}

	// TODO: Materials, Profiling, Meta, Shortest Route with Euler, Quaternion Rotation

	return FILEERROR::NONE;
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