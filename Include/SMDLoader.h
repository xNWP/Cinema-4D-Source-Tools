// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_SMD_LOADER_H
#define ST_SMD_LOADER_H

#include "c4d.h"
#include "c4d_symbols.h"
#include "Globals.h"
#include "fsmdloader.h"
#include "stParseTools.h"
#include "stMath.h"
#include "stMem.h"
#include <vector>

namespace ST
{
	//----------------------------------------------------------------------------------------
	/// Allows the importing of Studio Model Data (SMD) files.
	//----------------------------------------------------------------------------------------
	class SMDLoader : public SceneLoaderData
	{
		class SourceSkeletonBone;

	public:
		~SMDLoader();

		Bool Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size);
		FILEERROR Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, String* error, BaseThread* bt);
		static NodeData* Alloc() { return NewObjClear(SMDLoader); }

		//----------------------------------------------------------------------------------------
		/// Creates SourceSkeletonBones from nodes class.
		///
		/// @param[in] data					std::vector of strings that contains the data seperated by lines.
		/// @param[in,out] it				Which line the nodes class is declared. Returns as where the end occured.
		///
		/// @return							Bool true if successful.
		//----------------------------------------------------------------------------------------
		Bool ParseNodes(const std::vector<String> *data, Int32 &it);

		//----------------------------------------------------------------------------------------
		/// Parse Skeleton animation/positions
		///
		/// @param[in] data					std::vector of strings that contains the data seperated by lines.
		/// @param[in] doc					The document to insert the skeleton into.
		/// @param[in] parent				The object to parent the skeleton to, can be nullptr.
		/// @param[in,out] it				Which line the skeleton class is declared. Returns as where the end occured.
		///
		/// @return							Bool true if successful.
		//----------------------------------------------------------------------------------------
		Bool ParseSkeleton(const std::vector<String> *data, BaseDocument *doc, BaseObject *parent, Int32 &it);

	private:
		std::vector<SourceSkeletonBone*> *m_skeleton;

		//----------------------------------------------------------------------------------------
		/// Contains all necessary information for a Source Engine skeleton bone.
		/// All position and rotation values are local to the parent.
		//----------------------------------------------------------------------------------------
		class SourceSkeletonBone
		{
		public:
			//----------------------------------------------------------------------------------------
			/// Creates a SourceSkeletonBone from name and id's.
			///
			/// @param[in] name				Name of the bone.
			/// @param[in] id				ID of the bone.
			/// @param[in] parentid			ID of the parent bone.
			//----------------------------------------------------------------------------------------
			SourceSkeletonBone(const Int32 &id, const Int32 &parentid)
				: m_id(id), m_parentid(parentid)
			{
				this->m_bone = BaseObject::Alloc(Ojoint);
			}

			void Free()
			{
				BaseObject::Free(this->m_bone);
			}

			BaseObject* GetBone() const { return m_bone; }
			const String& GetName() const { return m_bone->GetName(); }
			void SetName(const String &name) { m_bone->SetName(name); }
			const Int32& GetId() const { return m_id; }
			void SetId(const Int32 &id) { m_id = id; }
			const Int32& GetParentId() const { return m_parentid; }
			void SetParentId(const Int32 &id) { m_parentid = id; }
			void SetLocalMatrix(const Matrix &mat) { m_bone->SetMl(mat); }

		private:
			Int32 m_id;
			Int32 m_parentid;
			BaseObject *m_bone;
		};
	};
}

//----------------------------------------------------------------------------------------
/// Registers the SMD Loader module.
///
/// @return				Bool true if successful.
//----------------------------------------------------------------------------------------
Bool RegisterSMDLoader();

#endif