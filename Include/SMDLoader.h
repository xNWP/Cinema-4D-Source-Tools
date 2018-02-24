// Copyright (c) 2018 Brett Anthony. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef ST_SMD_LOADER_H
#define ST_SMD_LOADER_H

#define Tik						1019561
#define ID_CA_IK_TAG_TIP		2000
#define ID_CA_IK_TAG_TARGET		2001
#define ID_CA_IK_TAG_SOLVER		2003
#define ID_CA_IK_TAG_SOLVER_2D	1
#define ID_CA_IK_TAG_SOLVER_3D	2

#include "c4d.h"
#include "c4d_symbols.h"
#include "Globals.h"
#include "fsmdloader.h"
#include "lib_modeling.h"
#include <map>
#include "stParseTools.h"
#include "stMath.h"
#include "stMem.h"
#include <vector>
#include "VTFLib/VTFLib.h"

namespace ST
{
	class SourceSkeletonBone;

	struct QCBodyGroup
	{
		String name;
		std::vector<String> mesh;
	};

	struct IKDecl
	{
		String name;
		String bone;
	};

	struct QCFile
	{
		std::vector<String> body;
		std::vector<QCBodyGroup> bodygroup;
		std::vector<String> cdmaterials;
		std::vector<IKDecl> ikchain;
	};

	//----------------------------------------------------------------------------------------
	/// Holds all the settings passed during import.
	//----------------------------------------------------------------------------------------
	struct SMDLoaderSettings
	{
		Float scale;
		Bool animation;
		Bool mesh;
		Bool qc;
		Bool qc_all;
		Bool mesh_weld;
		Float mesh_weld_tolerance;
		Bool mesh_normals;
		Bool mesh_uv;
		Bool mesh_materials;
		Filename material_root;
		Bool ik;
		Int32 ik_orientation;
		QCFile qc_file;
	};

	//----------------------------------------------------------------------------------------
	/// Allows the importing of Studio Model Data (SMD) files.
	//----------------------------------------------------------------------------------------
	class SMDLoader : public SceneLoaderData
	{
	public:
		Bool Init(GeListNode *node);
		Bool GetDParameter(GeListNode *node, const DescID &id, GeData &t_data, DESCFLAGS_GET &flags);
		Bool GetDEnabling(GeListNode *node, const DescID &id, const GeData &t_data, DESCFLAGS_ENABLE flags, const BaseContainer *itemdesc);
		Bool Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size);
		FILEERROR Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, String* error, BaseThread* bt);
		static NodeData* Alloc() { return NewObjClear(SMDLoader); }
		
		//----------------------------------------------------------------------------------------
		/// Parse a QC file and build all its parts.
		///
		/// @param[in] name					Filename of the QC to load.
		/// @param[in] settings				The settings passed during import.
		/// @param[in,out] doc				The document to insert the models/skeleton into.
		/// @param[in] parent				Object to insert elements under.
		/// @param[in] filterflags			Flags passed during import.
		/// @param[out] error				Error message on failed import.
		///
		/// @return							FILEERROR result of reading QC.
		//----------------------------------------------------------------------------------------
		FILEERROR ParseQC(const Filename &name, SMDLoaderSettings &settings, BaseDocument *doc, BaseObject *parent, SCENEFILTER filterflags, String *error);

		//----------------------------------------------------------------------------------------
		/// Parse an SMD file and build all its parts.
		///
		/// @param[in] name					Filename of the smd to load.
		/// @param[in] settings				The settings passed during import.
		/// @param[in,out] doc				The document to insert the SMD into.
		/// @param[in] parent				Object to insert SMD under.
		/// @param[in] filterflags			Flags passed during import.
		/// @param[out] error				Error message on failed import.
		/// @param[in] BuildSkeleton		Whether or not to build the skeleton.
		///
		/// @return							FILEERROR result of reading smd.
		//----------------------------------------------------------------------------------------
		FILEERROR ParseSMD(const Filename &name, const SMDLoaderSettings &settings, BaseDocument *doc, BaseObject *parent, SCENEFILTER filterflags, String *error, Bool BuildSkeleton);

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
		/// @param[in] settings				The settings passed during import.
		/// @param[in,out] doc				The document to insert the skeleton into.
		/// @param[in] flags				The flags passed during load.
		/// @param[in] parent				The object to parent the skeleton to, can be nullptr.
		/// @param[in,out] it				Which line the skeleton class is declared. Returns as where the end occured.
		///
		/// @return							Bool true if successful.
		//----------------------------------------------------------------------------------------
		Bool ParseSkeleton(const std::vector<String> *data, const SMDLoaderSettings &settings, BaseDocument *doc, SCENEFILTER flags, BaseObject *parent, Int32 &it);

		//----------------------------------------------------------------------------------------
		/// Parse mesh triangles
		///
		/// @param[in] data					std::vector of strings that contains the data seperated by lines.
		/// @param[in] settings				The settings passed during import.
		/// @param[in] name					The name of the mesh.
		/// @param[in,out] doc				The document to insert the mesh(s) into.
		/// @param[in] parent				The object to parent the mesh(s) to, can be nullptr.
		/// @param[in,out] it				Which line the mesh(s) are declared (<material> tag). Returns as where the end occured.
		///
		/// @return							Int32 error value, 0 good, -1 invalid triangle.
		//----------------------------------------------------------------------------------------
		Int32 ParseTriangles(const std::vector<String> *data, const SMDLoaderSettings &settings, const String &name, BaseDocument *doc, BaseObject *parent, Int32 &it);
	private:
		std::vector<ST::SourceSkeletonBone*> *m_skeleton;
		Bool m_qc_file;
	};

	//----------------------------------------------------------------------------------------
	/// Contains all necessary information for a Source Engine skeleton bone.
	/// All position and rotation values are local in respect to the parent.
	//----------------------------------------------------------------------------------------
	class SourceSkeletonBone
	{
	public:
		//----------------------------------------------------------------------------------------
		/// Creates a SourceSkeletonBone from name and id's.
		///
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
		const Vector& GetGlobalRefPos() const { return m_base_pos_g; }
		void SetGlobalRefPos(const Vector &pos) { m_base_pos_g = pos; }
		CTrack* GetXPTrack() const { return m_xPtrack; }
		void SetXPTrack(CTrack *track) { m_xPtrack = track; }
		CTrack* GetYPTrack() const { return m_yPtrack; }
		void SetYPTrack(CTrack *track) { m_yPtrack = track; }
		CTrack* GetZPTrack() const { return m_zPtrack; }
		void SetZPTrack(CTrack *track) { m_zPtrack = track; }
		CTrack* GetXRTrack() const { return m_xRtrack; }
		void SetXRTrack(CTrack *track) { m_xRtrack = track; }
		CTrack* GetYRTrack() const { return m_yRtrack; }
		void SetYRTrack(CTrack *track) { m_yRtrack = track; }
		CTrack* GetZRTrack() const { return m_zRtrack; }
		void SetZRTrack(CTrack *track) { m_zRtrack = track; }

	private:
		Int32 m_id;
		Int32 m_parentid;
		BaseObject *m_bone;
		Vector m_base_pos_g;
		CTrack *m_xPtrack;
		CTrack *m_yPtrack;
		CTrack *m_zPtrack;
		CTrack *m_xRtrack;
		CTrack *m_yRtrack;
		CTrack *m_zRtrack;
	};

	//----------------------------------------------------------------------------------------
	/// Contains all the needed data to draw a triangle from SMD data.
	//----------------------------------------------------------------------------------------
	class StudiomdlDataTriangle
	{
	public:
		//----------------------------------------------------------------------------------------
		/// Fills the object with all needed info from a standard format SMD file (seperated by lines).
		///
		/// @param[in] data				The line data from the SMD file.
		/// @param[in,out] it			Should point to the beginning <material> tag of the triangle, will return the line location after the last vertex.
		/// @param[out] error			Returns 0 if no error creating, negative otherwise.
		//----------------------------------------------------------------------------------------
		StudiomdlDataTriangle(const std::vector<String> *data, Int32 &it, Int32 &error)
		{
			m_material = (*data)[it];
			it++;

			// Read the data into a substring
			while (it < (it + 3))
			{
				std::vector<String> substrs;
				Int32 start = -1;
				for (Int32 i = 0; i <= (*data)[it].GetLength(); i++)
				{
					if ((*data)[it][i] == ' ' && start == -1)
					{
						continue;
					}
					else if (i == (*data)[it].GetLength())
					{
						substrs.push_back((*data)[it].SubStr(start, i - start));
					}
					else if (start == -1)
					{
						start = i;
					}
					else if ((*data)[it][i] == ' ' && start != -1)
					{
						substrs.push_back((*data)[it].SubStr(start, i - start));
						start = -1;
					}
				}

				if (substrs.size() < 10)
				{
					error = -1; // bad vertex
					break;
				}

				Int32 ParentBone = substrs[0].ParseToInt32();
				m_points.push_back(Vector(substrs[1].ParseToFloat(), substrs[2].ParseToFloat(), -substrs[3].ParseToFloat()));
				m_normals.push_back(Vector(substrs[4].ParseToFloat(), substrs[5].ParseToFloat(), -substrs[6].ParseToFloat()));
				m_uv_raw.push_back(Vector(substrs[7].ParseToFloat(), 1 - substrs[8].ParseToFloat(), 0));
				
				std::map<Int32, Float> tempWeights;
				for (Int32 j = 10; j < substrs.size(); j += 2)
					tempWeights.emplace(substrs[j].ParseToInt32(), substrs[j + 1].ParseToFloat());

				// calc diff between custom weights and parent
				Float diff = 1.0;
				for (auto const& n : tempWeights)
				{
					diff -= n.second;
				}

				if (Abs(diff) > 0.0001)
				{
					tempWeights.emplace(ParentBone, diff);
				}

				m_weights.push_back(tempWeights);
				substrs.clear();
				tempWeights.clear();

				it++;
			}
			m_uv = UVWStruct(m_uv_raw[2], m_uv_raw[1], m_uv_raw[0]);
			m_uv_raw.clear();
			error = 0;
		}

		// methods
		Vector GetPointA() const { return m_points[0]; }
		Vector GetPointB() const { return m_points[1]; }
		Vector GetPointC() const { return m_points[2]; }
		Vector GetNormalA() const { return m_normals[0].GetNormalized(); }
		Vector GetNormalB() const { return m_normals[1].GetNormalized(); }
		Vector GetNormalC() const { return m_normals[2].GetNormalized(); }
		UVWStruct GetUVW() const { return m_uv; }

	private:
		String m_material;
		std::vector<Vector> m_points;
		std::vector<Vector> m_normals;
		std::vector<Vector> m_uv_raw;
		UVWStruct m_uv = UVWStruct(DC); // don't construct
		std::vector<std::map<Int32, Float>> m_weights;
	};
}

//----------------------------------------------------------------------------------------
/// Registers the SMD Loader module.
///
/// @return				Bool true if successful.
//----------------------------------------------------------------------------------------
Bool RegisterSMDLoader();

#endif