#include "camioloader.h"

#include "camioparser.h"
#include "error.h"

#include "c4d_symbols.h"
#include "c4d_resource.h"
#include "c4d_baseobject.h"
#include "c4d_basedocument.h"
#include "lib_description.h"
#include "obase.h"
#include "c4d_canimation.h"

#define MAX_CAMIO_VERSION 1

namespace st::camio
{
	NodeData* LoaderData::Create()
	{
		return NewObjClear(LoaderData);
	}

	Bool LoaderData::Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size)
	{
		return CheckCamIOFileHeader(name);
	}

	FILEERROR LoaderData::Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt)
	{
		CamIO camFile;

		/* Parse the CamIO File */
		if (!ParseCamIO(name, camFile))
		{
			auto msg = GeLoadString(S_PARSE_ERROR, name.GetString());
			LogError(msg);
			*error = msg;
			return FILEERROR::INVALID;
		}

		/* Check version */
		if (camFile.Version > MAX_CAMIO_VERSION)
		{
			auto msg = GeLoadString(S_CAMIO_BAD_VERSION,
				maxon::ToString(camFile.Version, nullptr),
				maxon::ToString(MAX_CAMIO_VERSION, nullptr));
			LogError(msg);
			*error = msg;
			return FILEERROR::INVALID;
		}

		/* Create Camera and animation tracks*/
		CameraObject* camera = CameraObject::Alloc();
		doc->InsertObject(camera, nullptr, nullptr);
		
		CTrack* xTrack, * yTrack, * zTrack,
			* xRTrack, * yRTrack, * zRTrack;
		CCurve* xCurve, * yCurve, * zCurve,
			* xRCurve, * yRCurve, * zRCurve;

		xTrack = CTrack::Alloc(camera,
			DescID(DescLevel(ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0),
				DescLevel(VECTOR_X, DTYPE_REAL, 0)));
		yTrack = CTrack::Alloc(camera,
			DescID(DescLevel(ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0),
				DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
		zTrack = CTrack::Alloc(camera,
			DescID(DescLevel(ID_BASEOBJECT_REL_POSITION, DTYPE_VECTOR, 0),
				DescLevel(VECTOR_Z, DTYPE_REAL, 0)));
		xRTrack = CTrack::Alloc(camera,
			DescID(DescLevel(ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0),
				DescLevel(VECTOR_X, DTYPE_REAL, 0)));
		yRTrack = CTrack::Alloc(camera,
			DescID(DescLevel(ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0),
				DescLevel(VECTOR_Y, DTYPE_REAL, 0)));
		zRTrack = CTrack::Alloc(camera,
			DescID(DescLevel(ID_BASEOBJECT_REL_ROTATION, DTYPE_VECTOR, 0),
				DescLevel(VECTOR_Z, DTYPE_REAL, 0)));

		camera->InsertTrackSorted(xTrack);
		camera->InsertTrackSorted(yTrack);
		camera->InsertTrackSorted(zTrack);
		camera->InsertTrackSorted(xRTrack);
		camera->InsertTrackSorted(yRTrack);
		camera->InsertTrackSorted(zRTrack);

		xCurve = xTrack->GetCurve();
		yCurve = yTrack->GetCurve();
		zCurve = zTrack->GetCurve();
		xRCurve = xRTrack->GetCurve();
		yRCurve = yRTrack->GetCurve();
		zRCurve = zRTrack->GetCurve();

		// TODO: not done :-)

		return FILEERROR::NONE;
	}

	Bool LoaderData::RegisterPlugin()
	{
		return RegisterSceneLoaderPlugin(ID_CAMIOLOADER, "CamIO Loader"_s, 0, LoaderData::Create, maxon::String());
	}
}