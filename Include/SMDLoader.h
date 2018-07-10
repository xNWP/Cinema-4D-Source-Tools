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

#define Tconstraint				1019364
#define ID_CA_CONSTRAINT_TAG_PSR	1000
#define ID_CA_CONSTRAINT_TAG_PSR_POSITION	10005
#define ID_CA_CONSTRAINT_TAG_PSR_TARGET	10001

#include "c4d.h"
#include "c4d_reflection.h"
#include "c4d_symbols.h"
#include <chrono>
#include "Globals.h"
#include "fsmdloader.h"
#include "lib_ca.h"
#include "lib_modeling.h"
#include <map>
//#include "QCSequenceAnimation.h"
#include "stParseTools.h"
#include "stMath.h"
#include "stMem.h"
#include "tinyxml2/tinyxml2.h"
#include "UserConfig.h"
#include <vector>
#include "VTFLib/VTFLib.h"

namespace ST
{
	class SourceSkeletonBone;
	class StudiomdlDataTriangle;
	class SourceSMD;

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
		Filename file;
		std::vector<String> body;
		std::vector<QCBodyGroup> bodygroup;
		std::vector<String> cdmaterials;
		std::vector<IKDecl> ikchain;
	};

	struct VMTMat
	{
		String name;
		std::vector<BaseMaterial*> materials;
	};

	//----------------------------------------------------------------------------------------
	/// Holds all the settings passed during import.
	//----------------------------------------------------------------------------------------
	struct SMDLoaderSettings
	{
		String Custom_Root_Name;

		Float scale;
		Vector orientation;
		Bool SwapYZ;
		Bool animation;
		Bool mesh;
		Bool qc;
		Bool top_null;
		Bool joint_root;
		Bool parent;
		Bool mesh_weld;
		Float mesh_weld_tolerance;
		Bool mesh_normals;
		Bool mesh_uv;
		Bool mesh_materials;
		Bool mesh_weights;
		Filename material_root;
		Bool ik;
		Int32 ik_orientation;
		Bool cache;
		Int32 mat_filetype;
	};

	//----------------------------------------------------------------------------------------
	/// Allows the importing of Studio Model Data (SMD) files.
	//----------------------------------------------------------------------------------------
	class SMDLoader : public SceneLoaderData
	{
	public:
		Bool Init(GeListNode *node);
		void Free(GeListNode *node);
		Bool Message(GeListNode* node, Int32 type, void* data);
		Bool GetDParameter(GeListNode *node, const DescID &id, GeData &t_data, DESCFLAGS_GET &flags);
		Bool GetDEnabling(GeListNode *node, const DescID &id, const GeData &t_data, DESCFLAGS_ENABLE flags, const BaseContainer *itemdesc);
		Bool Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size);
		FILEERROR Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, String* error, BaseThread* bt);
		static NodeData* Alloc() { return NewObjClear(SMDLoader); }
		
		//----------------------------------------------------------------------------------------
		/// Deletes then reinitializes the master records, do this if an error occurs while parsing,
		/// a file as a safety measure.
		//----------------------------------------------------------------------------------------
		void FlushMasterRecords();

		//----------------------------------------------------------------------------------------
		/// Parse a QC file and build it.
		///
		/// @param[in] name					Filename of the QC to load. If smd using Use QC, pass the smd file.
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
		/// Builds a QC file.
		///
		/// @param[in] qc					The qc file to build from.
		/// @param[in] name					Filename of the QC to build.
		/// @param[in] settings				The settings passed during import.
		/// @param[in,out] doc				The document to insert the models/skeleton into.
		/// @param[in] parent				Object to insert elements under.
		/// @param[in] filterflags			Flags passed during import.
		/// @param[out] error				Error message on failed import.
		///
		/// @return							FILEERROR result of building QC.
		//----------------------------------------------------------------------------------------
		FILEERROR BuildQC(const QCFile *qc, const Filename &name, SMDLoaderSettings &settings, BaseDocument *doc, BaseObject *parent, SCENEFILTER filterflags, String *error);

		//----------------------------------------------------------------------------------------
		/// Parse an SMD file and build all its parts.
		///
		/// @param[in] name					Filename of the smd to load.
		/// @param[in] settings				The settings passed during import.
		/// @param[in,out] doc				The document to insert the SMD into.
		/// @param[in] qc					Pointer to qc file associated with the smd, can be nullptr.
		/// @param[in] parent				Object to insert SMD under.
		/// @param[in] filterflags			Flags passed during import.
		/// @param[out] error				Error message on failed import.
		/// @param[in] BuildSkeleton		Whether or not to build the skeleton.
		///
		/// @return							FILEERROR result of reading smd.
		//----------------------------------------------------------------------------------------
		FILEERROR ParseSMD(const Filename &name, const SMDLoaderSettings &settings, BaseDocument *doc, const QCFile *qc, BaseObject *parent, SCENEFILTER filterflags, String *error, Bool BuildSkeleton);

		//----------------------------------------------------------------------------------------
		/// Builds an SMD.
		///
		/// @param[in] smd					The SMD file to build from.
		/// @param[in] settings				The settings passed during import.
		/// @param[in] qc					QC file associated with the SMD, can be nullptr.
		/// @param[in,out] doc				The document to insert the models/skeleton into.
		/// @param[in] parent				Object to insert elements under.
		/// @param[in] filterflags			Flags passed during import.
		/// @param[out] error				Error message on failed import.
		/// @param[in] BuildSkeleton		Whether or not to build the skeleton.
		///
		/// @return							FILEERROR result of building SMD.
		//----------------------------------------------------------------------------------------
		FILEERROR BuildSMD(const SourceSMD *smd, const SMDLoaderSettings &settings, const QCFile *qc, BaseDocument *doc, BaseObject *parent, SCENEFILTER filterflags, String *error, Bool BuildSkeleton);
	
		private:
		Bool m_qc_file;
		std::vector<ST::SourceSkeletonBone*> *m_skeleton;
		std::vector<QCFile*> *m_master_qc_record;
		std::vector<SourceSMD*> *m_master_smd_record;
		std::vector<SourceSMD*> *m_temporary_smd_record;
		std::vector<VMTMat> m_material_cache;

		std::chrono::time_point<std::chrono::system_clock> start;
		std::chrono::time_point<std::chrono::system_clock> end;
	};

	//----------------------------------------------------------------------------------------
	/// Contains all necessary information to build a model from an SMD file.
	//----------------------------------------------------------------------------------------
	class SourceSMD
	{
	public:
		//----------------------------------------------------------------------------------------
		/// Constructs the SourceSMD from an SMD file.
		///
		/// @param[in] SMD				The file to load.
		/// @param[in] settings			Settings passed during import.
		/// @param[out] result			The result of loading the file.
		/// @param[out] error			Information about the error if one occured.
		//----------------------------------------------------------------------------------------
		SourceSMD(const Filename &SMD, const SMDLoaderSettings &settings, FILEERROR result, String *error);

		virtual ~SourceSMD();

		const Filename& GetFile() const { return m_file; }
		std::vector<ST::SourceSkeletonBone*>* GetSkeleton() const { return m_skeleton; }
		const Bool& AnimationBuilt() const { return m_animation_built; }
		std::vector<ST::StudiomdlDataTriangle*>* GetTriangles() const { return m_triangles; }
		const std::map<Int32, String>& GetPolySelections() const { return m_polySelections; }

		//----------------------------------------------------------------------------------------
		/// Rebuild the SMD loading in any extra data that was excluded previously.
		/// If you are using an SMD that is already in the master record you should always call this.
		///
		/// @param[in] settings				The settings passed during import.
		///
		/// @return Bool					True if successful.
		//----------------------------------------------------------------------------------------
		Bool Rebuild(const SMDLoaderSettings &settings);

		//----------------------------------------------------------------------------------------
		/// Returns the number of frames loaded into the SMD.
		///
		/// @return Int32					The number of loaded frames.
		//----------------------------------------------------------------------------------------
		const Int32& FrameCount() const { return m_frames; }

	private:
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
		/// @param[in,out] it				Which line the skeleton class is declared. Returns as where the end occured.
		/// @param[in] settings				Settings passed during import.
		///
		/// @return							Bool true if successful.
		//----------------------------------------------------------------------------------------
		Bool ParseSkeleton(const std::vector<String> *data, const SMDLoaderSettings &settings, Int32 &it);

		//----------------------------------------------------------------------------------------
		/// Parse mesh triangles
		///
		/// @param[in] data					std::vector of strings that contains the data seperated by lines.
		/// @param[in,out] it				Which line the mesh(s) are declared (<material> tag). Returns as where the end occured.
		///
		/// @return							Int32 error value, 0 good, -1 invalid triangle.
		//----------------------------------------------------------------------------------------
		Int32 ParseTriangles(const std::vector<String> *data, Int32 &it);

	private:
		Int32 m_anim_start;
		Int32 m_mesh_start;
		Filename m_file;
		std::vector<ST::SourceSkeletonBone*> *m_skeleton;
		Bool m_animation_built;
		Bool m_mesh_built;
		std::vector<ST::StudiomdlDataTriangle*> *m_triangles;
		std::map<Int32, String> m_polySelections;
		Int32 m_frames;
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
		/// @param[in] name				Name of the bone.
		/// @param[in] parentid			ID of the parent bone.
		//----------------------------------------------------------------------------------------
		SourceSkeletonBone(const Int32 &id, const String &name, const Int32 &parentid)
			: m_id(id), m_parentid(parentid), m_name(name) {}

		BaseObject* GetBone() const { return m_bone; }
		const String& GetName() const { return m_name; }
		const Int32& GetId() const { return m_id; }
		void SetId(const Int32 &id) { m_id = id; }
		const Int32& GetParentId() const { return m_parentid; }
		void SetParentId(const Int32 &id) { m_parentid = id; }
		const Matrix& GetRefMl() const { return m_ref_ml; }
		void SetRefMl(const Matrix &mat) { m_ref_ml = mat; }
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
		void PushBackPos(const Vector &pos) { m_pos.push_back(pos); }
		const Vector& GetPos(const Int32 &frame) const { return m_pos[frame]; }
		void PushBackRot(const Vector &rot) { m_rot.push_back(rot); }
		const Vector& GetRot(const Int32 &frame) const { return m_rot[frame]; }

		BaseObject* CreateBone()
		{
			m_bone = BaseObject::Alloc(Ojoint);
			m_bone->SetMl(m_ref_ml);
			m_bone->SetName(m_name);
			return m_bone;
		}

	private:
		String m_name;
		Int32 m_id;
		Int32 m_parentid;
		BaseObject *m_bone;
		Matrix m_ref_ml;
		CTrack *m_xPtrack;
		CTrack *m_yPtrack;
		CTrack *m_zPtrack;
		CTrack *m_xRtrack;
		CTrack *m_yRtrack;
		CTrack *m_zRtrack;
		std::vector<Vector> m_pos;
		std::vector<Vector> m_rot;
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
		/// @param[in,out] it			Should point to the beginning material tag of the triangle, will return the line location after the last vertex.
		/// @param[out] error			Returns 0 if no error creating, negative otherwise.
		//----------------------------------------------------------------------------------------
		StudiomdlDataTriangle(const std::vector<String> *data, Int32 &it, Int32 &error)
		{
			m_material = (*data)[it];
			it++;

			// Read the data into a substring
			while (it < (it + 3))
			{
				std::vector<String> substrs = Parse::split((*data)[it]);

				if (substrs.size() < 9)
				{
					error = -1; // bad vertex
					break;
				}

				Int32 ParentBone = substrs[0].ParseToInt32();
				Float x = substrs[1].ParseToFloat();
				Float y = substrs[2].ParseToFloat();
				Float z = -substrs[3].ParseToFloat();
				Float nX = substrs[4].ParseToFloat();
				Float nY = substrs[5].ParseToFloat();
				Float nZ = -substrs[6].ParseToFloat();

				m_points.push_back(Vector(x, y, z));
				m_normals.push_back(Vector(nX, nY, nZ));

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
		std::map<Int32, Float>& GetWeightsA() { return m_weights[0]; }
		std::map<Int32, Float>& GetWeightsB() { return m_weights[1]; }
		std::map<Int32, Float>& GetWeightsC() { return m_weights[2]; }

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