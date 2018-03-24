// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_AGR_LOADER_H
#define ST_AGR_LOADER_H

#include "c4d.h"
#include "c4d_symbols.h"
#include "c4d_quaternion.h"
#include "fagrloader.h"
#include "fsmdloader.h"
#include "Globals.h"
#include <map>
#include <set>
#include "SMDLoader.h"
#include "stParseTools.h"
#include <vector>

namespace ST
{
	struct AGRSettings
	{
		Filename RootModelDir;
	};

	class AGRData;
	class ModelHandle;

	//----------------------------------------------------------------------------------------
	/// Allows the importing of Advanced Effects Game Recording (AGR) files.
	//----------------------------------------------------------------------------------------
	class AGRLoader : public SceneLoaderData
	{
	public:
		Bool Init(GeListNode *node) { m_time[0] = -1; m_time[1] = -1; return true; }
		Bool Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size);
		FILEERROR Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, String* error, BaseThread* bt);
		static NodeData* Alloc() { return NewObjClear(AGRLoader); }

	private:
		void AddToDictionary(const String &value);
		String ReadFromDictionary(BaseFile &file);

		Vector& ReadVector(BaseFile &file, Bool quakeformat = false);
		Vector& ReadQAngle(BaseFile &file);
		Quaternion& ReadQuaternion(BaseFile &file, Bool quakeformat = false);

		std::map<Int32, ModelHandle*> m_handles;
		std::vector<ModelHandle*> *m_FreeHandles;

		std::map<Int32, String> m_dictionary;
		Float32 m_time[2];
		std::set<Int32> m_hiddenHandles;
		std::set<Int32> m_deletedHandles;
		std::map<Int32, AGRData> m_raw_data;
		std::vector<Vector> CamPos;
		std::vector<Vector> CamRot;
		std::vector<Float32> CamFov;
		Int32 frame;
	};

	class AGRData
	{
	public:
		Filename Model;
		std::vector<Vector> RootPos;
		std::vector<Vector> RootRot;
		std::vector<std::map<Int32, Vector>> BonePos;
		std::vector<std::map<Int32, Quaternion>> BoneRot;
	};

	class ModelHandle
	{
	public:
		ModelHandle() { m_skeleton = NewObj(std::vector<ST::SourceSkeletonBone*>); }
		void Free(GeListNode *node) { DeletePtrVector(m_skeleton); }

		//----------------------------------------------------------------------------------------
		/// Builds the skeleton cache (m_skeleton) from a qc file.
		///
		/// @param[in] qc				The qc file to build the skeleton from.
		//----------------------------------------------------------------------------------------
		void BuildSkeletonCache(Filename qc);

		Filename Model;
		BaseObject *Skeleton;
		std::vector<ST::SourceSkeletonBone*> *m_skeleton;
	};
}

//----------------------------------------------------------------------------------------
/// Registers the AGR Loader module.
///
/// @return				Bool true if successful.
//----------------------------------------------------------------------------------------
Bool RegisterAGRLoader();

#endif