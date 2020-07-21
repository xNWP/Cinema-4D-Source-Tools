#include "qcloader.h"

#include "qcformat.h"
#include "qcparser.h"
#include "smdparser.h"
#include "smdloader.h"
#include "fqcloader.h"

#include "c4dst_error.h"

#include "c4d_baseobject.h"
#include "c4d_basedocument.h"
#include "lib_description.h"

Bool QCLoaderData::Identify( BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size )
{
	// QuakeC is an ASCII format with no FourCC/Header so we will use the file extension
	return ( name.GetSuffix().ToLower() == "qc" ) ? true : false;
}

FILEERROR QCLoaderData::Load( BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt )
{
	QuakeCFormat qc;

	if ( !ParseQC( name, qc ) )
	{
		LogError( "PEGTL failed to parse QC." );
		return FILEERROR::INVALID;
	}

	BaseObject* QCNull = BaseObject::Alloc( Onull );
	QCNull->SetName( name.GetFileString().SubStr( 0, name.GetFileString().GetLength() - 3 ) );
	doc->InsertObject( QCNull, nullptr, nullptr );

	SMDLoaderData::Settings SMDConfig;

	auto GetParam = [&node]( Int32 id )->GeData
	{
		static GeData DataHolder;
		node->GetParameter( id, DataHolder, DESCFLAGS_GET::NONE );
		return DataHolder;
	};

	SMDConfig.IncludeAnimation = false;
	SMDConfig.IncludeMesh = GetParam( QC_LOADER_IMPORT_MESH ).GetBool();
	SMDConfig.IncludeSkeleton = GetParam( QC_LOADER_IMPORT_SKELETON ).GetBool();
	SMDConfig.IncludeWeights = GetParam( QC_LOADER_IMPORT_WEIGHTS ).GetBool();
	SMDConfig.Orientation = GetParam( QC_LOADER_ROTATE ).GetVector();
	SMDConfig.MeshRootObject = QCNull;
	SMDConfig.Scale = GetParam( QC_LOADER_SCALE ).GetFloat();
	SMDConfig.Skeleton = nullptr;
	SMDConfig.SkeletonRootObject = QCNull;

	Bool ParamImportUnderNull = GetParam( QC_LOADER_IMPORT_UNDER_NULL ).GetBool();
	Bool ParamImportMaterials = GetParam( QC_LOADER_IMPORT_MATERIALS ).GetBool();
	Filename MaterialRootDirectory = GetParam( QC_LOADER_MATERIAL_PATH ).GetFilename();

	/* Body Meshes */
	for ( const auto& bm : qc.BodyMeshes )
	{
		StudiomdlData smd;
		Filename fp = name.GetDirectory() + "/" + bm.Filepath.c_str();
		if ( !fp.CheckSuffix( "smd"_s ) ) fp += "smd";
		if ( !ParseSMD( fp, smd ) )
		{
			LogError( "PEGTL failed to parse SMD needed for QC." );
			return FILEERROR::INVALID;
		}

		fp.ClearSuffix();

		auto SMDObj = SMDLoaderData::CreateSMD( smd, fp.GetFileString(),
												SMDConfig, doc );

		SMDConfig.Skeleton = SMDObj.Skeleton;
	}

	/* Bodygroup Meshes */
	for ( const auto& bgm : qc.BodyGroups )
	{
		SMDConfig.MeshRootObject = BaseObject::Alloc( Onull );
		SMDConfig.MeshRootObject->SetName( maxon::String( bgm.Name.c_str() ) );
		doc->InsertObject( SMDConfig.MeshRootObject, QCNull, QCNull->GetDownLast() );
		
		if ( bgm.Blank )
		{
			BaseObject* BlankNull = BaseObject::Alloc( Onull );
			BlankNull->SetName( "blank"_s );
			doc->InsertObject( BlankNull, SMDConfig.MeshRootObject, nullptr );
		}

		for ( const auto& mesh : bgm.Meshes )
		{
			StudiomdlData smd;
			Filename fp = name.GetDirectory() + "/" + mesh.c_str();
			if ( !fp.CheckSuffix( "smd"_s ) ) fp += "smd";

			if ( !ParseSMD( fp, smd ) )
			{
				LogError( "PEGTL failed to parse SMD needed for QC." );
				return FILEERROR::INVALID;
			}

			fp.ClearSuffix();

			auto SMDObj = SMDLoaderData::CreateSMD( smd, fp.GetFileString(),
													SMDConfig, doc );

			SMDConfig.Skeleton = SMDObj.Skeleton;
		}
	}

	/* Remove Null */
	if ( !ParamImportUnderNull )
	{
		while ( auto Obj = QCNull->GetDown() )
		{
			Obj->Remove();
			Obj->InsertBefore( QCNull );
		}

		BaseObject::Free( QCNull );
	}

	return FILEERROR::NONE;
}

Bool QCLoaderData::GetDEnabling( GeListNode* node, const DescID& id, const GeData& data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc )
{
	if ( node == nullptr )
		return false;

	
	auto GetParam = [&node]( Int32 id )->GeData
	{
		static GeData Data;
		node->GetParameter( id, Data, DESCFLAGS_GET::NONE );
		return Data;
	};

	switch ( id[0].id )
	{
		case QC_LOADER_IMPORT_WEIGHTS:
		{
			if ( !(
				GetParam( QC_LOADER_IMPORT_MESH ).GetBool() &&
				GetParam( QC_LOADER_IMPORT_SKELETON ).GetBool()
				) )
				return false;

			break;
		}

		case QC_LOADER_IMPORT_MATERIALS:
		{
			if ( !GetParam( QC_LOADER_IMPORT_MESH ).GetBool() )
				return false;

			break;
		}

		case QC_LOADER_MATERIAL_PATH:
		{
			if ( !GetParam( QC_LOADER_IMPORT_MATERIALS ).GetBool() )
				return false;

			break;
		}
	}

	return true;
}

Bool QCLoaderData::GetDParameter( GeListNode* node, const DescID& id, GeData& t_data, DESCFLAGS_GET& flags )
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
		case QC_LOADER_IMPORT_MATERIALS:
		{
			if ( !GetParam( QC_LOADER_IMPORT_MESH ).GetBool() )
			{
				SetFalse();
				return true;
			}

			break;
		}

		case QC_LOADER_IMPORT_WEIGHTS:
		{
			if ( !(
				GetParam( QC_LOADER_IMPORT_MESH ).GetBool() &&
				GetParam( QC_LOADER_IMPORT_SKELETON ).GetBool() ) )
			{
				SetFalse();
				return true;
			}
		}
	}

	return SceneLoaderData::GetDParameter( node, id, t_data, flags );
}

Bool QCLoaderData::Init( GeListNode* node )
{
	/* Default settings, overriden by user-prefs */
	BaseContainer* data = ( (BaseList2D*)node )->GetDataInstance();
	data->SetFloat( QC_LOADER_SCALE, 1.0f );
	data->SetVector( QC_LOADER_ROTATE, Vector( 0.0f, 0.0f, 0.0f ) );
	data->SetBool( QC_LOADER_IMPORT_UNDER_NULL, false );
	data->SetBool( QC_LOADER_IMPORT_SKELETON, true );
	data->SetBool( QC_LOADER_IMPORT_MESH, true );
	data->SetBool( QC_LOADER_IMPORT_WEIGHTS, true );
	data->SetBool( QC_LOADER_IMPORT_MATERIALS, false );

	return true;
}

NodeData* QCLoaderData::Create()
{
	return NewObjClear( QCLoaderData );
}

Bool QCLoaderData::RegisterPlugin()
{
	if ( !RegisterSceneLoaderPlugin( ID_QCLOADER, "QuakeC (QC) Loader"_s, 0, QCLoaderData::Create, "Fqcloader"_s ) )
		return false;

	return true;
}
