/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef LIB_CA_H__
#define LIB_CA_H__

#include "c4d_library.h"
#include "ge_math.h"
#include "lib_description.h"

#ifdef __API_INTERN__

#include "pluginobject.h"
#include "plugintag.h"

#else

#include "c4d_baseobject.h"
#include "c4d_basetag.h"
#include "c4d_tooldata.h"
#include "c4d_descriptiondialog.h"

#endif

/// @addtogroup group_characteranimationlibrary Character Animation
/// @ingroup group_library
/// @{

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
void RemoveXRefData(BaseDocument *doc, BaseList2D *bl);

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
Bool HasDocumentXRefs(BaseDocument *doc);

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
Int32 GetDocumentXRefState();

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
UInt64 GetXRefID(BaseList2D *bl);

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
Bool XRefHasParam(BaseDocument *doc, BaseList2D *bl, const DescID &id);

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
Bool XRefGetParam(BaseDocument *doc, BaseList2D *bl, const DescID &id, GeData &dat);

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
Bool XRefRemoveParam(BaseDocument *doc, BaseList2D *bl, const DescID &id);


//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
class MirrorTransformData
{
public:
	Vector m_Mp, m_Mn;
	Matrix m_Mg, m_Mi;

	const BaseContainer *m_pData;
};

/// @markPrivate
#define MSG_MIRROR_TRANSFORM 1025416

/// @markPrivate
#define MIRROR_TRANSFORM_CONTAINER 1025418

/// @addtogroup MIRROR_TRANSFORM_CONTAINER
/// @ingroup group_containerid
/// @{
/// @markPrivate
#define MIRROR_TRANSFORM_CONTAINER_MATRIX		1000	/// ::Matrix Origin global matrix.
#define MIRROR_TRANSFORM_CONTAINER_SOURCE		1001	/// ::BaseLink Origin object link.
#define MIRROR_TRANSFORM_CONTAINER_LMATRIXN	1002	/// ::Matrix Origin relative and normalized local matrix.
#define MIRROR_TRANSFORM_CONTAINER_LMATRIX	1003	/// ::Matrix Origin relative local matrix.
#define MIRROR_TRANSFORM_CONTAINER_FMATRIX	1004	/// ::Matrix Origin frozen local matrix.
#define MIRROR_TRANSFORM_CONTAINER_POS			1005	/// ::Vector Origin relative position.
#define MIRROR_TRANSFORM_CONTAINER_ROT			1006	/// ::Vector Origin relative rotation.
#define MIRROR_TRANSFORM_CONTAINER_SCL			1007	/// ::Vector Origin relative scale.
#define MIRROR_TRANSFORM_CONTAINER_FPOS			1008	/// ::Vector Origin frozen position.
#define MIRROR_TRANSFORM_CONTAINER_FROT			1009	/// ::Vector Origin frozen rotation.
#define MIRROR_TRANSFORM_CONTAINER_FSCL			1010	/// ::Vector Origin frozen scale.
/// @}

class Neighbor;

struct JointRestState
{
	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	JointRestState() { m_Len = 0.0; }
	Matrix	m_bMg,			///< Global matrix of the bone between two joints with the Z axis (V3) along the bone.
					m_bMi;			///< Inverse matrix of the bone between two joints with the Z axis (V3) along the bone.
	Matrix	m_oMg,			///< Global matrix of the actual Joint object.
					m_oMi;			///< Inverse matrix of the actual Joint object.
	Float		m_Len;			///< Bone rest length.
};

class CAWeightTag;

//----------------------------------------------------------------------------------------
/// Joint object.
/// @addAllocFreeAutoAllocNote
//----------------------------------------------------------------------------------------
class CAJointObject : public BaseObject
{
#ifndef __API_INTERN__
private:
	CAJointObject();
	~CAJointObject();
public:
	/// @name Alloc/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// @allocatesA{joint object}
	/// @return												@allocReturn{joint object}
	//----------------------------------------------------------------------------------------
	static CAJointObject *Alloc() { return (CAJointObject*)BaseObject::Alloc(Ojoint); }

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{joint objects}
	/// @param[in,out] pObject				@theToDestruct{joint object}
	//----------------------------------------------------------------------------------------
	static void Free(CAJointObject *&pObject) { BaseObject *op = pObject; BaseObject::Free(op); pObject = nullptr; }

	/// @}
#else
public:
#endif
	/// @name Joint
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the bone data for the joint.
	/// @param[out] m									Assigned the bone matrix.
	/// @param[out] len								Assigned the bone length.
	//----------------------------------------------------------------------------------------
	void GetBone(Matrix &m, Float &len);

	//----------------------------------------------------------------------------------------
	/// Retrieves the weight tag corresponding to the joint.
	/// @param[out] index							Assigned the weight tag index.
	/// @return												The weight tag.
	//----------------------------------------------------------------------------------------
	CAWeightTag *GetWeightTag(Int32 &index);

	/// @}
};


//----------------------------------------------------------------------------------------
/// Weight tag.
/// @addAllocFreeAutoAllocNote
//----------------------------------------------------------------------------------------
class CAWeightTag : public BaseTag
{
#ifndef __API_INTERN__
private:
	CAWeightTag();
	~CAWeightTag();
public:
	/// @name Alloc/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// @allocatesA{weight tag}
	/// @return												@allocReturn{weight tag}
	//----------------------------------------------------------------------------------------
	static CAWeightTag *Alloc() { return (CAWeightTag*)BaseTag::Alloc(Tweights); }

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{weight tags}
	/// @param[in,out] pTag						@theToDestruct{weight tag}
	//----------------------------------------------------------------------------------------
	static void Free(CAWeightTag *&pTag) { BaseTag *tag = pTag; BaseTag::Free(tag); pTag = nullptr; }

	/// @}
#else
public:
#endif

	/// @name Joint
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the joint object at @formatParam{index}.
	/// @param[in] index							The joint index: @em <= @formatParam{index} < GetJointCount()
	/// @param[in] doc								The document or @formatConstant{nullptr}.
	/// @return												The joint object, or @formatConstant{nullptr}.
	//----------------------------------------------------------------------------------------
	BaseObject *GetJoint(Int32 index, BaseDocument *doc);

	//----------------------------------------------------------------------------------------
	/// Gets the total joint count.
	/// @note Can also be found and changed using C4DAtom::SetParameter() with @ref ID_CA_WEIGHT_TAG_JOINTS_LIST.
	/// @return												The joint count.
	//----------------------------------------------------------------------------------------
	Int32 GetJointCount();

	//----------------------------------------------------------------------------------------
	/// Retrieves the index of the joint object the weight tag is attached to.
	/// @param[in] op									The host object.
	/// @param[in] doc								The document or @formatConstant{nullptr}.
	/// @return												The joint index, or @ref NOTOK if not found.
	//----------------------------------------------------------------------------------------
	Int32 FindJoint(BaseObject *op, BaseDocument *doc);

	/// @}

	/// @name Joint Rest State
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the rest state for the joint at @formatParam{index}.
	/// @param[in] index							The joint index: @em <= @formatParam{index} < GetJointCount()
	/// @return												The joint rest state.
	//----------------------------------------------------------------------------------------
	JointRestState GetJointRestState(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Sets the rest state for the joint at @formatParam{index}.
	/// @param[in] index							The joint index: @em <= @formatParam{index} < GetJointCount()
	/// @param[in] state							The new joint rest state.
	//----------------------------------------------------------------------------------------
	void SetJointRestState(Int32 index, const JointRestState &state);

	/// @}

	/// @name Weight
	/// @{

	//----------------------------------------------------------------------------------------
	/// Fills @formatParam{map} with the weights, which must be allocated with @formatParam{cnt} elements (should be the point count).
	/// @param[in] index							The joint index: @em <= @formatParam{index} < GetJointCount()
	/// @param[out] map								Filled with the weight data.
	/// @param[in] cnt								The point count. Size of @formatParam{map}.
	/// @param[in] includeEffectors		If @formatConstant{true} the effectors weights will be added to the @formatParam{map}. Since R17.048
	//----------------------------------------------------------------------------------------
	void GetWeightMap(Int32 index, Float32 *map, Int32 cnt, Bool includeEffectors = false);

	//----------------------------------------------------------------------------------------
	/// Sets the weights with @formatParam{map}.
	/// @param[in] index							The joint index: @em <= @formatParam{index} < GetJointCount()
	/// @param[in] map								The new weight map.
	/// @param[in] cnt								The point count. Size of @formatParam{map}.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetWeightMap(Int32 index, Float32 *map, Int32 cnt);

	//----------------------------------------------------------------------------------------
	/// Gets the total number of stored weights.
	/// @param[in] index							The joint index: @em <= @formatParam{index} < GetJointCount()
	/// @return												The number of weights. @em 0 means weights are not stored.
	//----------------------------------------------------------------------------------------
	Int32 GetWeightCount(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Retrieves the @formatParam{windex} @formatParam{weight} and which point index @formatParam{pntindex}.
	/// @param[in] index							The joint index: @em <= @formatParam{index} < GetJointCount()
	/// @param[in] windex							The weight index: @em <= @formatParam{windex} < GetWeightCount()
	/// @param[out] pntindex					Assigned the point index.
	/// @param[out] weight						Assigned the weight.
	//----------------------------------------------------------------------------------------
	void GetIndexWeight(Int32 index, Int32 windex, Int32 &pntindex, Float &weight);

	//----------------------------------------------------------------------------------------
	/// Retrieves the weight for the point formatParam{pntindex}.
	/// @param[in] index							The joint index: @em <= @formatParam{index} < GetJointCount()
	/// @param[in] pntindex						The point index.
	/// @return												The weight.
	//----------------------------------------------------------------------------------------
	Float GetWeight(Int32 index, Int32 pntindex);

	//----------------------------------------------------------------------------------------
	/// Sets the weight for formatParam{pntindex}.
	/// @param[in] index							The joint index: @em <= @formatParam{index} < GetJointCount()
	/// @param[in] pntindex						The point index.
	/// @param[in] weight							The new weight.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetWeight(Int32 index, Int32 pntindex, Float weight);

	//----------------------------------------------------------------------------------------
	/// Gets the dirty state of the weights.
	/// @return												The weights' dirty state.
	//----------------------------------------------------------------------------------------
	UInt32 GetWeightDirty();

	//----------------------------------------------------------------------------------------
	/// Marks the weights dirty.
	//----------------------------------------------------------------------------------------
	void WeightDirty();

	/// @}

	/// @name Geometry Matrix
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the global matrix for the bind geometry.
	/// @note Use this with the global matrices of the joints to get the local transforms.
	/// @return												The global matrix for the bind geometry.
	//----------------------------------------------------------------------------------------
	Matrix GetGeomMg();

	//----------------------------------------------------------------------------------------
	/// Sets the global matrix for the bind geometry.
	/// @param[in] mg									The new global matrix for the bind geometry.
	//----------------------------------------------------------------------------------------
	void SetGeomMg(const Matrix &mg);

	/// @}

	/// @name Add/Remove Joint
	/// @{

	//----------------------------------------------------------------------------------------
	/// Adds a joint object to the weight tag's "Joints" list.
	/// @param[in] op									The joint object to add to the weight tag's "Joints" list.
	/// @return												The joint object's index in the "Joints" list.\n
	///																@em NOTOK if failed i.e. the tag is not present in an object's tag list.
	//----------------------------------------------------------------------------------------
	Int32 AddJoint(BaseObject *op);

	//----------------------------------------------------------------------------------------
	/// Removes a joint object from the weight tag's "Joints" list.
	/// @param[in] op									The joint object to remove from the weight tag's "Joint" list.
	//----------------------------------------------------------------------------------------
	void RemoveJoint(BaseObject *op);

	/// @}

	/// @name Miscellaneous
	/// @{

	//----------------------------------------------------------------------------------------
	/// Helper function to initialize the joint at @formatParam{index}.\n
	/// Fills in the bind state (JointRestState::m_oMg and JointRestState::m_oMi) and then call the function to set JointRestState::m_bMg, JointRestState::m_bMi and JointRestState::m_Len.
	/// @note The joints must be in the document.
	/// @param[in] index							The joint index: @em <= @formatParam{index} < GetJointCount()\n
	///																@ref NOTOK to process all joints.
	//----------------------------------------------------------------------------------------
	void CalculateBoneStates(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Transfers the weights from one weight tag to another.
	/// @param[in] doc								The document containing the weight tags.
	/// @param[out] dst								The destination weight tag.
	/// @param[in] sindex							The index of the source joint. Pass @ref NOTOK for all joints.
	/// @param[in] dindex							The index of the destination joint. Pass @ref NOTOK for all joints.
	/// @param[in] offset							The offset to move the weight indices when they are copied to the destination. Pass @ref NOTOK for all indices.
	/// @param[in] cnt								The number of weights to be transfered. Pass @ref NOTOK for all weights.
	/// @param[in] trans							An alias translator for the operation. Can be @formatConstant{nullptr}. @callerOwnsPointed{alias translator}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool TransferWeightMap(BaseDocument *doc, CAWeightTag *dst, Int32 sindex, Int32 dindex, Int32 offset, Int32 cnt, AliasTrans *trans);

	/// @}
};


class CAPoseMorphTag;

/// @addtogroup CAMORPH_COPY_FLAGS
/// @ingroup group_enumeration
/// @{
enum CAMORPH_COPY_FLAGS
{
	CAMORPH_COPY_FLAGS_0	= 0			///< None.
} ENUM_END_FLAGS(CAMORPH_COPY_FLAGS);
/// @}

/// @addtogroup CAMORPH_MODE_FLAGS
/// @ingroup group_enumeration
/// @{
enum CAMORPH_MODE_FLAGS
{
	CAMORPH_MODE_FLAGS_COLLAPSE	= 2048,			///< Collapse data. Needs to be passed to collapse the expanded data, for instance after data access.
	CAMORPH_MODE_FLAGS_EXPAND		= 4096,			///< Expand data. Needs to be passed before accessing any data.
	CAMORPH_MODE_FLAGS_ALL			= 1007,			///< Expand or collapse all data

	CAMORPH_MODE_FLAGS_0				= 0					///< None.
} ENUM_END_FLAGS(CAMORPH_MODE_FLAGS);
/// @}

/// @addtogroup CAMORPH_MODE
/// @ingroup group_enumeration
/// @{
enum CAMORPH_MODE
{
	CAMORPH_MODE_ABS = 0,								///< Absolute morph data.
	CAMORPH_MODE_REL,										///< Relative morph data.
	CAMORPH_MODE_ROT,										///< Rotational morph data.
	CAMORPH_MODE_CORRECTIONAL,					///< Correctional morph data.
	CAMORPH_MODE_CORRECTIONAL_AREA,			///< Correctional (Area) morph data.
	CAMORPH_MODE_AUTO = -1,							///< Auto mode. Used to collapse the data automatically into their correct mode.

	CAMORPH_MODE_0 = 0									///< None.
} ENUM_END_LIST(CAMORPH_MODE);
/// @}

/// @addtogroup CAMORPH_DATA_FLAGS
/// @ingroup group_enumeration
/// @{
enum CAMORPH_DATA_FLAGS
{
	CAMORPH_DATA_FLAGS_P					= (1 << 0),			///< Position morphing.
	CAMORPH_DATA_FLAGS_S					= (1 << 1),			///< Scale morphing.
	CAMORPH_DATA_FLAGS_R					= (1 << 2),			///< HPB rotation morphing.
	CAMORPH_DATA_FLAGS_POINTS			= (1 << 3),			///< Points morphing.
	CAMORPH_DATA_FLAGS_TANGETS		= (1 << 4),			///< Tangents morphing.
	CAMORPH_DATA_FLAGS_VERTEXMAPS	= (1 << 5),			///< Vertex map morphing.
	CAMORPH_DATA_FLAGS_WEIGHTMAPS	= (1 << 6),			///< Joint weights morphing.
	CAMORPH_DATA_FLAGS_PARAMS			= (1 << 7),			///< Parameter morphing.
	CAMORPH_DATA_FLAGS_USERDATA		= (1 << 8),			///< %User data morphing.
	CAMORPH_DATA_FLAGS_UV					= (1 << 9),			///< UV coordinate morphing.

	/// This flag has usually to be set to store the current state of an object into the morph.\n
	/// It is storing the morph data as set by the user in the morph tag, otherwise it would mess up the internal data.
	CAMORPH_DATA_FLAGS_ASTAG = (1 << 15),

	/// All data morphing.
	CAMORPH_DATA_FLAGS_ALL = ((1 << 0)|(1 << 1)|(1 << 2)|(1 << 3)|(1 << 4)|(1 << 5)|(1 << 6)|(1 << 7)|(1 << 8)|(1 << 9)),

	CAMORPH_DATA_FLAGS_0 = 0											///< None.
} ENUM_END_FLAGS(CAMORPH_DATA_FLAGS);
/// @}

class CAMorph;

//----------------------------------------------------------------------------------------
/// CAMorphNode class allows to access the actual morph data. For every morph there exist a morph node tree representing the hierarchy of the morphed objects.\n
/// Before using any of the access function always check which data exist with GetInfo(). Also make sure the data has been expanded with @ref CAMORPH_MODE_FLAGS_EXPAND in SetMode().\n
/// Example of a simple case with one polygon object. In this case just access the first morph node of the morph to be changed.\n
/// First exit any editing:
/// @code
/// mtag->ExitEdit(doc, true);
/// @endcode
/// Get the morph to be changed:
/// @code
/// CAMorph* morph = mtag->GetMorph(1);
/// @endcode
/// Now get the morph node. The first will be the object with the morph tag:
/// @code
/// CAMorphNode* mnode = morph->GetFirst();
/// @endcode
/// Data must be made editable
/// @code
/// morph->SetMode(doc, mtag, CAMORPH_MODE_FLAGS_ALL|CAMORPH_MODE_FLAGS_EXPAND,CAMORPH_MODE_ABS);
/// @endcode
/// The point data can now be accessed, but make sure the data exists:
/// @code
/// mnode->GetInfo() & CAMORPH_DATA_FLAGS_POINTS
/// @endcode
/// To access the data use GetPointCount(), SetPointCount(), GetPoint() and SetPoint().\n
/// Once finished put the data back to its original form:
/// @code
/// morph->SetMode(doc, mtag, CAMORPH_MODE_FLAGS_ALL|CAMORPH_MODE_FLAGS_COLLAPSE,CAMORPH_MODE_AUTO);
/// @endcode
/// Finally the tag must be updated:
/// @code
/// mtag->UpdateMorphs();
/// @endcode
//----------------------------------------------------------------------------------------
class CAMorphNode
{
#ifndef __API_INTERN__
private:
	CAMorphNode();
	~CAMorphNode();
#endif
public:

	/// @name Navigation
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the next morph node.
	/// @return												The next morph node, or @formatConstant{nullptr} if there is none. @cinemaOwnsPointed{morph node}
	//----------------------------------------------------------------------------------------
	CAMorphNode *GetNext();

	//----------------------------------------------------------------------------------------
	/// Retrieves the previous morph node.
	/// @return												The previous morph node, or @formatConstant{nullptr} if there is none. @cinemaOwnsPointed{morph node}
	//----------------------------------------------------------------------------------------
	CAMorphNode *GetPrev();

	//----------------------------------------------------------------------------------------
	/// Retrieves the parent morph node.
	/// @return												The parent morph node, or @formatConstant{nullptr} if there is none. @cinemaOwnsPointed{morph node}
	//----------------------------------------------------------------------------------------
	CAMorphNode *GetUp();

	//----------------------------------------------------------------------------------------
	/// Retrieves the first child morph node.
	/// @return												The first child morph node, or @formatConstant{nullptr} if there is none. @cinemaOwnsPointed{morph node}
	//----------------------------------------------------------------------------------------
	CAMorphNode *GetDown();

	/// @}

	/// @name Get Link
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the object linked to the morph node.
	/// @param[in] tag								The morph tag containing the morph data.
	/// @param[in] morph							The morph containing the morph node.
	/// @param[in] doc								The document containing the linked object.
	/// @return												The linked object, or @formatConstant{nullptr} if there is none. @cinemaOwnsPointed{object}
	//----------------------------------------------------------------------------------------
	BaseList2D *GetLink(CAPoseMorphTag *tag, CAMorph *morph, BaseDocument *doc);

	/// @}

	/// @name Get Info
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets what morph data is stored in the morph node.
	/// @return												The data flags: @enumerateEnum{CAMORPH_DATA_FLAGS}
	//----------------------------------------------------------------------------------------
	CAMORPH_DATA_FLAGS GetInfo();

	/// @}

	/// @name Get/Set Positon/Scale/Rotation
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the position of the morph node.
	/// @return												The position.
	//----------------------------------------------------------------------------------------
	Vector GetP();

	//----------------------------------------------------------------------------------------
	/// Retrieves the scale of the morph node.
	/// @return												The scale.
	//----------------------------------------------------------------------------------------
	Vector GetS();

	//----------------------------------------------------------------------------------------
	/// Retrieves the HPB rotation of the morph node.
	/// @return												The HPB rotation.
	//----------------------------------------------------------------------------------------
	Vector GetR();

	//----------------------------------------------------------------------------------------
	/// Sets the position of the morph node.
	/// @param[in] p									The new position.
	//----------------------------------------------------------------------------------------
	void SetP(const Vector &p);

	//----------------------------------------------------------------------------------------
	/// Sets the scale of the morph node.
	/// @param[in] s									The new scale.
	//----------------------------------------------------------------------------------------
	void SetS(const Vector &s);

	//----------------------------------------------------------------------------------------
	/// Sets the HPB rotation.
	/// @param[in] r									The new HPB rotation.
	//----------------------------------------------------------------------------------------
	void SetR(const Vector &r);

	/// @}

	/// @name Point
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the point count of the morph node.
	/// @return												The point count.
	//----------------------------------------------------------------------------------------
	Int32 GetPointCount();

	//----------------------------------------------------------------------------------------
	/// Sets the point count of the morph node.
	/// @param[in] cnt								The new point count.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetPointCount(Int32 cnt);

	//----------------------------------------------------------------------------------------
	/// Retrieves the point at @formatParam{index}.
	/// @param[in] index							The point index: @em 0 <= @formatParam{index} < GetPointCount()
	/// @return												The point at @formatParam{index}.
	//----------------------------------------------------------------------------------------
	Vector GetPoint(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Sets the point at @formatParam{index}.
	/// @param[in] index							The point index: @em 0 <= @formatParam{index} < GetPointCount()
	/// @param[in] pnt								The new point coordinate.
	//----------------------------------------------------------------------------------------
	void SetPoint(Int32 index, const Vector &pnt);

	/// @}

	/// @name Tangent
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the tangent count of the morph node.
	/// @return												The tangent count.
	//----------------------------------------------------------------------------------------
	Int32 GetTangentCount();

	//----------------------------------------------------------------------------------------
	/// Sets the tangent count of the morph node.
	/// @param[in] cnt								The new tangent count.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetTangentCount(Int32 cnt);

	//----------------------------------------------------------------------------------------
	/// Retrieves the tangent at @formatParam{index}.
	/// @param[in] index							The tangent index: @em 0 <= @formatParam{index} < GetTangentCount()
	/// @return												The tangent at @formatParam{index}.
	//----------------------------------------------------------------------------------------
	Vector GetTangent(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Sets the tangent at @formatParam{index}.
	/// @param[in] index							The tangent index: @em 0 <= @formatParam{index} < GetPointCount()
	/// @param[in] v									The new tangent coordinate.
	//----------------------------------------------------------------------------------------
	void SetTangent(Int32 index, const Vector &v);

	/// @}

	/// @name Vertex Map
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the number of vertex map tags of the morph node.
	/// @return												The number of vertex map tags.
	//----------------------------------------------------------------------------------------
	Int32 GetVertexMapTagCount();

	//----------------------------------------------------------------------------------------
	/// Retrieves the size of the vertex map at @formatParam{tindex}.
	/// @param[in] tindex							The vertex map tag index: @em 0 <= @formatParam{tindex} < GetVertexMapTagCount()
	/// @return												The size of the vertex map at @formatParam{tindex}.
	//----------------------------------------------------------------------------------------
	Int32 GetVertexMapCount(Int32 tindex);

	//----------------------------------------------------------------------------------------
	/// Sets the size of the vertex map at @formatParam{tindex}.
	/// @param[in] tindex							The vertex map tag index: @em 0 <= @formatParam{tindex} < GetVertexMapTagCount()
	/// @param[in] cnt								The new size of the vertex map at @formatParam{tindex}.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetVertexMapCount(Int32 tindex, Int32 cnt);

	//----------------------------------------------------------------------------------------
	/// Retrieves the vertex map value at @formatParam{index} of the @formatParam{tindex} vertex map.
	/// @param[in] tindex							The vertex map tag index: @em 0 <= @formatParam{tindex} < GetVertexMapTagCount()
	/// @param[in] index							The vertex map index. @em 0 <= @formatParam{index} < GetVertexMapCount()
	/// @return												The vertex map value.
	//----------------------------------------------------------------------------------------
	Float GetVertexMap(Int32 tindex, Int32 index);

	//----------------------------------------------------------------------------------------
	/// Sets the vertex map value at @formatParam{index} of the @formatParam{tindex} vertex map.
	/// @param[in] tindex							The vertex map tag index: @em 0 <= @formatParam{tindex} < GetVertexMapTagCount()
	/// @param[in] index							The vertex map index. @em 0 <= @formatParam{index} < GetVertexMapCount()
	/// @param[in] v									The new vertex map value.
	//----------------------------------------------------------------------------------------
	void SetVertexMap(Int32 tindex, Int32 index, Float v);

	/// @}

	/// @name Parameters
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the number of parameters for the morph node.
	/// @return												The number of parameters.
	//----------------------------------------------------------------------------------------
	Int32 GetParamCount();

	//----------------------------------------------------------------------------------------
	/// Sets the number of parameters for the morph node.
	/// @param[in] cnt								The new number of parameters.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetParamCount(Int32 cnt);

	//----------------------------------------------------------------------------------------
	/// Retrieves the parameter at @formatParam{index} for the morph node.
	/// @param[in] index							The parameter index: @em 0 <= @formatParam{index} < GetParamCount()
	/// @param[out] data							Assigned the parameter value.
	/// @param[out] id								Assigned the description ID of the parameter.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GetParam(Int32 index, GeData &data, DescID &id);

	//----------------------------------------------------------------------------------------
	/// Sets the parameter at @formatParam{index} for the morph node.
	/// @param[in] index							The parameter index: @em 0 <= @formatParam{index} < GetParamCount()
	/// @param[in] data								The new parameter value.
	/// @param[in] id									The new parameter description ID.
	//----------------------------------------------------------------------------------------
	void SetParam(Int32 index, const GeData &data, const DescID &id);

	/// @}

	/// @name UV
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the number of UV tags.
	/// @return												The number of UV tags.
	//----------------------------------------------------------------------------------------
	Int32 GetUVTagCount();

	//----------------------------------------------------------------------------------------
	/// Retrieves the UV coordinates count of the UV tag at @formatParam{tindex}.
	/// @param[in] tindex							The UV tag index: @em 0 <= @formatParam{tindex} < GetUVTagCount()
	/// @return												The UV coordinates count.
	//----------------------------------------------------------------------------------------
	Int32 GetUVCount(Int32 tindex);

	//----------------------------------------------------------------------------------------
	/// Sets the UV coordinates count of the UV tag at @formatParam{tindex}.
	/// @param[in] tindex							The UV tag index: @em 0 <= @formatParam{tindex} < GetUVTagCount()
	/// @param[in] cnt								The new UV coordinates count.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetUVCount(Int32 tindex, Int32 cnt);

	//----------------------------------------------------------------------------------------
	/// Retrieves the UV coordinate @formatParam{index} of the @formatParam{tindex} UV tag.
	/// @param[in] tindex							The UV tag index: @em 0 <= @formatParam{tindex} < GetUVTagCount()
	/// @param[in] index							The UV coordinates index: @em 0 <= @formatParam{index} < GetUVCount()
	/// @param[out] uv								Assigned the UV coordinates.
	//----------------------------------------------------------------------------------------
	void GetUV(Int32 tindex, Int32 index, UVWStruct &uv);

	//----------------------------------------------------------------------------------------
	/// Sets the UV coordinate @formatParam{index} of the @formatParam{tindex} UV tag.
	/// @param[in] tindex							The UV tag index: @em 0 <= @formatParam{tindex} < GetUVTagCount()
	/// @param[in] index							The UV coordinates index: @em 0 <= @formatParam{index} < GetUVCount()
	/// @param[in] uv									The new UV coordinates.
	//----------------------------------------------------------------------------------------
	void SetUV(Int32 tindex, Int32 index, const UVWStruct &uv);

	/// @}

	/// @name Weight Map
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the number of weight map tags.
	/// @return												The number of weight map tags.
	//----------------------------------------------------------------------------------------
	Int32 GetWeightMapTagCount();

	//----------------------------------------------------------------------------------------
	/// Retrieves the joint count of the weight tag at @formatParam{tindex}.
	/// @param[in] tindex							The weight tag index: @em 0 <= @formatParam{tindex} < GetWeightMapTagCount()
	/// @return												The joint count of the specified weight tag.
	//----------------------------------------------------------------------------------------
	Int32 GetWeightMapJointCount(Int32 tindex);

	//----------------------------------------------------------------------------------------
	/// Retrieves the weights count of the joint at @formatParam{jindex} of @formatParam{tindex} weight tag.
	/// @param[in] tindex							The weight tag index: @em 0 <= @formatParam{tindex} < GetWeightMapTagCount()
	/// @param[in] jindex							The joint index: @em 0 <= @formatParam{jindex} < GetWeightMapJointCount()
	/// @return												The weight count of the specified joint.
	//----------------------------------------------------------------------------------------
	Int32 GetWeightMapCount(Int32 tindex, Int32 jindex);

	//----------------------------------------------------------------------------------------
	/// Sets the weights count of the joint at @formatParam{jindex} of @formatParam{tindex} weight tag.
	/// @param[in] tindex							The weight tag index: @em 0 <= @formatParam{tindex} < GetWeightMapTagCount()
	/// @param[in] jindex							The joint index: @em 0 <= @formatParam{jindex} < GetWeightMapJointCount()
	/// @param[in] cnt								The new weight count.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetWeightMapCount(Int32 tindex, Int32 jindex, Int32 cnt);

	//----------------------------------------------------------------------------------------
	/// Retrieves the weight at @formatParam{index} of @formatParam{jindex} joint and @formatParam{tindex} Weight tag.
	/// @param[in] tindex							The weight tag index: @em 0 <= @formatParam{tindex} < GetWeightMapTagCount()
	/// @param[in] jindex							The joint index: @em 0 <= @formatParam{jindex} < GetWeightMapJointCount()
	/// @param[in] index							The weight index: @em 0 <= @formatParam{index} < GetWeightMapCount()
	/// @return												The weight.
	//----------------------------------------------------------------------------------------
	Float GetWeightMap(Int32 tindex, Int32 jindex, Int32 index);

	//----------------------------------------------------------------------------------------
	/// Sets the weight at @formatParam{index} of @formatParam{jindex} joint and @formatParam{tindex} Weight tag.
	/// @param[in] tindex							The weight tag index: @em 0 <= @formatParam{tindex} < GetWeightMapTagCount()
	/// @param[in] jindex							The joint index: @em 0 <= @formatParam{jindex} < GetWeightMapJointCount()
	/// @param[in] index							The weight index: @em 0 <= @formatParam{index} < GetWeightMapCount()
	/// @param[in] v									The new weight.
	//----------------------------------------------------------------------------------------
	void SetWeightMap(Int32 tindex, Int32 jindex, Int32 index, Float v);

	/// @}
};


//----------------------------------------------------------------------------------------
/// CAMorph class contains the data for each morph. It has to be retrieved from the CAPoseMorphTag.
/// @see CAMorphNode for an example.
//----------------------------------------------------------------------------------------
class CAMorph
{
#ifndef __API_INTERN__
private:
	CAMorph();
	~CAMorph();
#endif
public:

	/// @name Name
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the name of the morph.
	/// @return												The name of the morph.
	//----------------------------------------------------------------------------------------
	String GetName();

	//----------------------------------------------------------------------------------------
	/// Sets the name of the morph.
	/// @param[in] name								The new name of the morph.
	//----------------------------------------------------------------------------------------
	void SetName(const String &name);

	/// @}

	/// @name Miscellaneous
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the internal ID of the morph. Each morph has an ID. This ensures that removed morphs do not affect the DescID for the sliders.
	/// @return												The internal ID of the morph.
	//----------------------------------------------------------------------------------------
	Int32 GetID();

	//----------------------------------------------------------------------------------------
	/// Copies morph data from @formatParam{src}.
	/// @param[in] src								The source morph.
	/// @param[in] trn								An alias translator for the operation. Can be @formatConstant{nullptr}. @callerOwnsPointed{alias translator}
	/// @param[in] flags							The flags: @enumerateEnum{CAMORPH_COPY_FLAGS}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool CopyFrom(CAMorph *src, AliasTrans *trn, CAMORPH_COPY_FLAGS flags);

	/// @}

	/// @name Morph Node
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the morph node for the object specified by @formatParam{bl}.
	/// @note A single morph can be applied to a hierarchy of objects, each has a representation in the morph as a CAMorphNode.
	/// @param[in] tag								The morph tag containing the morph node.
	/// @param[in] bl									The object connected to the morph node.
	/// @return												The morph node for the specified object. @theOwnsPointed{tag,morph node}
	//----------------------------------------------------------------------------------------
	CAMorphNode *Find(CAPoseMorphTag *tag, BaseList2D *bl);

	//----------------------------------------------------------------------------------------
	/// Retrieves the index of the specified morph node. Each morph node can be accessed through their indices.
	/// @param[in] node								The morph node to request the index.
	/// @return												The morph node index.
	//----------------------------------------------------------------------------------------
	Int32 GetNodeIndex(CAMorphNode *node);

	//----------------------------------------------------------------------------------------
	/// Retrieves the index of the morph node for the object specified by @formatParam{bl}.
	/// @note A single morph can be applied to a hierarchy of objects, each has a representation in the morph as a CAMorphNode.
	/// @param[in] tag								The morph tag containing the morph node.
	/// @param[in] bl									The object connected to the morph node.
	/// @return												The index of the morph node of the specified object.
	//----------------------------------------------------------------------------------------
	Int32 FindIndex(CAPoseMorphTag *tag, BaseList2D *bl);

	//----------------------------------------------------------------------------------------
	/// Retrieves the morph node specified by @formatParam{index}.
	/// @note A single morph can be applied to a hierarchy of objects, each has a representation in the morph as a CAMorphNode.
	/// @param[in] tag								The morph tag containing the morph node.
	/// @param[in] index							The index of the requested morph node.
	/// @return												The found morph node. @theOwnsPointed{tag,morph node}
	//----------------------------------------------------------------------------------------
	CAMorphNode *FindFromIndex(CAPoseMorphTag *tag, Int32 index);

	//----------------------------------------------------------------------------------------
	/// Retrieves the first node of the morph.
	/// @return												The first morph node. @theOwnsPointed{tag,morph node}
	//----------------------------------------------------------------------------------------
	CAMorphNode *GetFirst();

	/// @}

	/// @name Morph
	/// @{

	//----------------------------------------------------------------------------------------
	/// Changes the morph's mode.
	/// @note This is not the mode a user would change but data inside the morph. It must be restored to the original mode once changes are finished.\n
	///				To change the morph tag's modes or parameters use C4DAtom::SetParameter().
	///
	/// @b Example:
	/// Point data could be stored as rotational or correctional and in a delta form (only differences from the base).\n
	/// This can not be edited in this form so the data mode must be changed to relative (@ref CAMORPH_MODE_REL) or absolute (@ref CAMORPH_MODE_ABS) before editing and then restored to (@ref CAMORPH_MODE_AUTO) when finished.\n
	/// The flags must be passed as @ref CAMORPH_MODE_FLAGS_EXPAND to expand the data from the delta form and then returned with @ref CAMORPH_MODE_FLAGS_COLLAPSE when finished.\n
	/// For example VAMP uses the following line to expand all data types to relative data:
	/// @code
	/// smorph->SetMode(doc, data.s_morphtag, CAMORPH_MODE_FLAGS_ALL|CAMORPH_MODE_FLAGS_EXPAND,CAMORPH_MODE_REL);
	/// @endcode
	/// It then does some changes and finally restores all types to collapsed (delta) form and to the users mode (AUTO):
	/// @code
	/// data.sources[i]->SetMode(doc, data.s_morphtag, CAMORPH_MODE_FLAGS_ALL|CAMORPH_MODE_FLAGS_COLLAPSE,CAMORPH_MODE_AUTO);
	/// @endcode
	/// @param[in] doc								The document containing the morph tag.
	/// @param[in] tag								The morph tag containing the morph data.
	/// @param[in] flags							The flags: @enumerateEnum{CAMORPH_MODE_FLAGS}
	/// @param[in] mode								The mode: @enumerateEnum{CAMORPH_MODE}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetMode(BaseDocument *doc, CAPoseMorphTag *tag, CAMORPH_MODE_FLAGS flags, CAMORPH_MODE mode);

	//----------------------------------------------------------------------------------------
	/// Stores the current object's state into the morph.\n
	/// The corresponding @formatParam{flags} have to be set for the data. This should normally be @ref CAMORPH_DATA_FLAGS_ASTAG if it is to be used by the user.
	/// @param[in] doc								The document containing the morph tag.
	/// @param[in] tag								The morph tag containing the morph data.
	/// @param[in] flags							The flags: @enumerateEnum{CAMORPH_DATA_FLAGS}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Store(BaseDocument *doc, CAPoseMorphTag *tag, CAMORPH_DATA_FLAGS flags);

	//----------------------------------------------------------------------------------------
	/// Applies the morph to the object. The data to be applied is set with the @formatParam{flags}.
	/// @param[in] doc								The document containing the morph tag.
	/// @param[in] tag								The morph tag containing the morph data.
	/// @param[in] flags							The flags: @enumerateEnum{CAMORPH_DATA_FLAGS}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Apply(BaseDocument *doc, CAPoseMorphTag *tag, CAMORPH_DATA_FLAGS flags);

	/// @}

	/// @name Target
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the target of the morph.
	/// @param[in] doc								The document containing the morph tag.
	/// @return												The target of the morph. @theOwnsPointed{tag,object}
	//----------------------------------------------------------------------------------------
	BaseList2D *GetTarget(BaseDocument *doc);

	//----------------------------------------------------------------------------------------
	/// Sets the target of the morph.
	/// @param[in] tag								The morph tag containing the morph node.
	/// @param[in] doc								The document containing the morph tag.
	/// @param[in] bl									The new target of the morph.
	//----------------------------------------------------------------------------------------
	void SetTarget(CAPoseMorphTag *tag, BaseDocument *doc, BaseList2D *bl);

	/// @}

	/// @name Strength
	/// @{

	//----------------------------------------------------------------------------------------
	/// Sets the strength of the morph.
	/// @param[in] strength						The new strength of the morph.
	//----------------------------------------------------------------------------------------
	void SetStrength(Float strength);

	//----------------------------------------------------------------------------------------
	/// Retrieves the strength of the morph.
	/// @return												The strength of the morph.
	//----------------------------------------------------------------------------------------
	Float GetStrength();

	/// @}
};

//----------------------------------------------------------------------------------------
/// Pose morph tag storing the morph data.
/// @addAllocFreeAutoAllocNote
/// @see CAMorphNode for an example.
//----------------------------------------------------------------------------------------
class CAPoseMorphTag : public BaseTag
{
#ifndef __API_INTERN__
private:
	CAPoseMorphTag();
	~CAPoseMorphTag();
public:
	/// @name Alloc/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// @allocatesA{pose morph tag}
	/// @return												@allocReturn{pose morph tag}
	//----------------------------------------------------------------------------------------
	static CAPoseMorphTag *Alloc() { return (CAPoseMorphTag*)BaseTag::Alloc(Tposemorph); }

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{pose morph tags}
	/// @param[in,out] pTag						@theToDestruct{pose morph tag}
	//----------------------------------------------------------------------------------------
	static void Free(CAPoseMorphTag *&pTag) { BaseTag *tag = pTag; BaseTag::Free(tag); pTag = nullptr; }

	/// @}
#else
public:
#endif

	/// @name Morph
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the number of morphs. This is the number of morphs visible interface.
	/// @return												The number of available morphs.
	//----------------------------------------------------------------------------------------
	Int32 GetMorphCount();

	//----------------------------------------------------------------------------------------
	/// Retrieves the morph at @formatParam{index}.
	/// @param[in] index							The morph index: @em 0 <= @formatParam{index} < GetMorphCount()
	/// @return												The morph. @theOwnsPointed{tag,morph}
	//----------------------------------------------------------------------------------------
	CAMorph *GetMorph(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Retrieves the description ID for the morph slider at @formatParam{index}.
	/// @param[in] index							The morph index: @em 0 <= @formatParam{index} < GetMorphCount()
	/// @return												The description ID of the morph slider.
	//----------------------------------------------------------------------------------------
	DescID GetMorphID(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Retrieves the index of the active morph (usually the one selected in the list).
	/// @return												The index of the active morph.
	//----------------------------------------------------------------------------------------
	Int32 GetActiveMorphIndex();

	//----------------------------------------------------------------------------------------
	/// Retrieves the active morph (usually the one selected).
	/// @return												The active morph. @theOwnsPointed{tag,morph}
	//----------------------------------------------------------------------------------------
	CAMorph *GetActiveMorph() { return GetMorph(GetActiveMorphIndex()); }

	//----------------------------------------------------------------------------------------
	/// Retrieves the base morph. Same as calling GetMorph(0).
	/// @return												The base morph. @theOwnsPointed{tag,morph}
	//----------------------------------------------------------------------------------------
	CAMorph *GetMorphBase() { return GetMorph(0); }

	//----------------------------------------------------------------------------------------
	/// Retrieves the index for the given @formatParam{morph}.
	/// @param[in] morph							The morph.
	/// @return												The index for the @formatParam{morph}.
	//----------------------------------------------------------------------------------------
	Int32 GetMorphIndex(CAMorph *morph);

	//----------------------------------------------------------------------------------------
	/// Sets the active morph index.
	/// @param[in] index							The active morph index to set: @em 0 <= @formatParam{index} < GetMorphCount()
	//----------------------------------------------------------------------------------------
	void SetActiveMorphIndex(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Adds a new morph.
	/// @return												The newly added morph, or @formatConstant{nullptr} if it failed. @theOwnsPointed{tag,morph}
	//----------------------------------------------------------------------------------------
	CAMorph *AddMorph();

	//----------------------------------------------------------------------------------------
	/// Removes the morph at @formatParam{index}.
	/// @param[in] index							The index of the morph to remove: @em 0 <= @formatParam{index} < GetMorphCount()
	//----------------------------------------------------------------------------------------
	void RemoveMorph(Int32 index);

	/// @}

	/// @name Miscellaneous
	/// @{

	//----------------------------------------------------------------------------------------
	/// Retrieves the Edit/Animate mode (same as @ref ID_CA_POSE_MODE in description/tcaposemorph.h)
	/// @return												The Edit/Animate mode. See @ref ID_CA_POSE_MODE in description/tcaposemorph.h.
	//----------------------------------------------------------------------------------------
	Int32 GetMode();

	//----------------------------------------------------------------------------------------
	/// Initializes the morph tag.
	/// @warning Must be called after creating a morph tag and before adding anything to the tag.
	//----------------------------------------------------------------------------------------
	void InitMorphs();

	//----------------------------------------------------------------------------------------
	/// Updates the tag's list and internal data.
	/// @warning Must be called after making changes to the tag is finished.
	/// @param[in] doc								An optional document for the update of the morphs. @callerOwnsPointed{document}
	//----------------------------------------------------------------------------------------
	void UpdateMorphs(BaseDocument *doc = nullptr);

	//----------------------------------------------------------------------------------------
	/// Must be called before doing anything to a morph tag.\n
	/// For example, if the user is in Edit mode and making changes these are not applied to the morph until this function is called.\n
	/// So if this function is not called those changes will be lost. Set @formatParam{apply} to @formatConstant{true} if any user changes should be stored. This is normally the case.
	/// @param[in] doc								The document. @callerOwnsPointed{document}
	/// @param[in] apply							Set to @formatConstant{true} if any user changes should be stored, otherwise set to @formatConstant{false}.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool ExitEdit(BaseDocument *doc, Bool apply);

	/// @}
};


/// @addtogroup BRUSHBASE_MOUSE_FLAG
/// @ingroup group_enumeration
/// @{
#define BRUSHBASE_MOUSE_FLAG_ADDUNDO							(1 << 0)
#define BRUSHBASE_MOUSE_FLAG_ADDUNDO_FULL					(1 << 1)
#define BRUSHBASE_MOUSE_FLAG_SORTED_DIST					(1 << 2)
#define BRUSHBASE_MOUSE_FLAG_SORTED_OBJECT				(1 << 3)
#define BRUSHBASE_MOUSE_FLAG_SORTED_ORIGINOBJECT	(1 << 4)
/// @}

/// @addtogroup BRUSHBASE_FALLOFF
/// @ingroup group_enumeration
/// @{
#define BRUSHBASE_FALLOFF_STRENGTH			(1 << 0)
#define BRUSHBASE_FALLOFF_ABSSTRENGTH		(1 << 1)
/// @}

class _BrushToolBase;
class iBrushBase;
class BrushObjectData;
class BrushToolData;

class BrushObjectInfo
{
public:
	//----------------------------------------------------------------------------------------
	/// Default constructor.
	//----------------------------------------------------------------------------------------
	BrushObjectInfo()
	{
		m_pObject = nullptr;
		m_pOriginObject = nullptr;
		m_pDeformObject = nullptr;
		m_pNeighbor = nullptr;
		m_pPoints = nullptr;
		m_pGlobalPoints = nullptr;
		m_pNormals = nullptr;
		m_pPolys = nullptr;
		m_PointCount = 0;
		m_PolyCount = 0;
	}

	BaseObject	*m_pObject;						///< The object. Not always equal to m_pOriginObject.
	BaseObject	*m_pOriginObject;			///< The original object.
	BaseObject	*m_pDeformObject;			///< The deform object.

	Neighbor	*m_pNeighbor;						///< The neighbor data.
	const Vector	*m_pPoints;					///< The points array.
	Vector	*m_pGlobalPoints,					///< The global points.
					*m_pNormals;							///< The normals.
	const CPolygon	*m_pPolys;				///< The polygons array.
	Int32	m_PointCount,								///< The point count.
				m_PolyCount;								///< The polygon count.
};

class BrushVertexData
{
public:
	Float	m_Dist;										///< The distance.
	Int32	m_Index;									///< The vertex index.
	BrushObjectData	*m_pObject;			///< The object data.
};

class BrushPixelData
{
public:
	BrushObjectData	*m_pObject;			///< The object data.
	Int32	m_Index;									///< The pixel index.
	Float	m_Z;											///< The Z distance.
	BrushPixelData	*m_pNext;				///< The next pixel data.
};

//----------------------------------------------------------------------------------------
/// Helper class for the BrushToolData hook.
//----------------------------------------------------------------------------------------
class BrushBase
{
private:

	BrushBase();
	~BrushBase();

	_BrushToolBase *m_pBase;

public:
	/// @name Alloc/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// @allocatesA{brush base}
	/// @return												@allocReturn{brush base}
	//----------------------------------------------------------------------------------------
	static BrushBase *Alloc();

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{brush base instances}
	/// @param[in,out] p							@theToDestruct{brush base}
	//----------------------------------------------------------------------------------------
	static void Free(BrushBase *&p);

	/// @}

	/// @name Base Implementations
	/// @{

	//----------------------------------------------------------------------------------------
	/// Base implementation for BrushToolData.
	//----------------------------------------------------------------------------------------
	Bool InitTool(BaseDocument* doc, BaseContainer& data, BaseThread* bt, BrushToolData *tool);

	//----------------------------------------------------------------------------------------
	/// Base implementation for BrushToolData.
	//----------------------------------------------------------------------------------------
	void FreeTool(BaseDocument* doc, BaseContainer& data);

	//----------------------------------------------------------------------------------------
	/// Base implementation for BrushToolData.
	//----------------------------------------------------------------------------------------
	void InitDefaultSettings(BaseDocument *doc, BaseContainer &data);

	//----------------------------------------------------------------------------------------
	/// Base implementation for BrushToolData.
	//----------------------------------------------------------------------------------------
	Bool GetDEnabling(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc);

	//----------------------------------------------------------------------------------------
	/// Base implementation for BrushToolData.
	//----------------------------------------------------------------------------------------
	Bool SetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags);

	//----------------------------------------------------------------------------------------
	/// Base implementation for BrushToolData.
	//----------------------------------------------------------------------------------------
	Bool GetDDescription(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags);

	//----------------------------------------------------------------------------------------
	/// Base implementation for BrushToolData.
	//----------------------------------------------------------------------------------------
	Bool Message(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data);

	//----------------------------------------------------------------------------------------
	/// Base implementation for BrushToolData.
	//----------------------------------------------------------------------------------------
	Bool GetCursorInfo(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc);

	//----------------------------------------------------------------------------------------
	/// Base implementation for BrushToolData.
	//----------------------------------------------------------------------------------------
	Bool MouseInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);

	/// @}

	/// @name Helpers
	/// @{

	//----------------------------------------------------------------------------------------
	/// Performs a selection at (@formatParam{x},@formatParam{y}) with radius @formatParam{rad}.
	/// @warning Call ValidateObjects() before this function.
	/// @param[in] doc								The document.
	/// @param[in] data								The data container.
	/// @param[in] bd									The base draw view.
	/// @param[out] vcnt							Assigned the selected vertex count.
	/// @param[in] x									The X coordinate.
	/// @param[in] y									The Y coordinate.
	/// @param[in] rad								The radius.
	/// @param[in] op									The object.
	/// @return												The selected vertices.
	//----------------------------------------------------------------------------------------
	BrushVertexData *GetSelected(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Int32 &vcnt, Int32 x, Int32 y, Float rad, BaseObject *op);

	//----------------------------------------------------------------------------------------
	/// Gets the cursor position and radius.
	/// @param[out] x									Assigned the cursor X position.
	/// @param[out] y									Assigned the cursor Y position.
	/// @return												The radius.
	//----------------------------------------------------------------------------------------
	Float GetCursor(Int32 &x, Int32 &y);

	//----------------------------------------------------------------------------------------
	/// Retrieves object information for @formatParam{data}.
	/// @param[in] data								The brush object data.
	/// @param[out] info							Assigned the brush object information.
	//----------------------------------------------------------------------------------------
	void GetObjectInfo(BrushObjectData *data, BrushObjectInfo &info);

	//----------------------------------------------------------------------------------------
	/// Retrieves the cached object data from @formatParam{op}.
	/// @param[in] op									The object.
	/// @param[out] info							Assigned the brush object information.
	/// @return												@trueIfOtherwiseFalse{successful}\n
	///																@formatConstant{false} if object @formatParam{op} is not found in the cache.
	//----------------------------------------------------------------------------------------
	Bool GetObjectInfo(BaseObject *op, BrushObjectInfo &info);

	//----------------------------------------------------------------------------------------
	/// Validate objects.
	/// @param[in] doc								The document.
	/// @param[in] data								The data container.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool ValidateObjects(BaseDocument *doc, BaseContainer& data);

	//----------------------------------------------------------------------------------------
	/// Get the objects at (@formatParam{x},@formatParam{y}).
	/// @warning Call ValidateObjects() before this function.
	/// @param[in] x									The X coordinate.
	/// @param[in] y									The Y coordinate.
	/// @return												The brush pixel data.
	//----------------------------------------------------------------------------------------
	BrushPixelData *GetObjectAt(Int32 x, Int32 y);

	//----------------------------------------------------------------------------------------
	/// Gets the falloff factor.
	/// @note Only valid within MouseInput() functions.
	/// @param[in] dst								The distance.
	/// @param[in] flags							The flags: @enumerateEnum{BRUSHBASE_FALLOFF}
	/// @return												The falloff factor.
	//----------------------------------------------------------------------------------------
	Float GetFalloff(Float dst, Int32 flags);

	//----------------------------------------------------------------------------------------
	/// Fills in the atom array with the cached (should be active) objects.
	/// @param[in] doc								The document.
	/// @param[out] objects						The cached objects.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool GetObjects(BaseDocument *doc, AtomArray *objects);

	//----------------------------------------------------------------------------------------
	/// Update the cache if object pointers have been changed during mouse drag.\n
	/// It should not be needed to set force if the object has been made dirty (@ref MSG_UPDATE).
	/// @param[in] doc								The document.
	/// @param[in] data								The data container.
	/// @param[in] bd									The base draw view.
	/// @param[in] force							Set to @formatConstant{true} to force the cache update.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool UpdateCache(BaseDocument *doc, BaseContainer& data, BaseDraw *bd, Bool force);

	//----------------------------------------------------------------------------------------
	/// Used internally for surface distance calculations. Creates an array with an element for each point in @formatParam{pObject} set to the distance to selected.\n
	/// If @formatParam{pDistance} is passed this array is used instead.\n
	/// Either pass the various pointers (those with the @formatConstant{nullptr} default parameters) or let them be calculated automatically if @formatConstant{nullptr}.
	/// @param[in] pObject						The object to calculate.
	/// @param[in] selected						The point selection to calculate.
	/// @param[in] pNeighbor					The neighbor information.
	/// @param[in] pNormals						The point normals.
	/// @param[in] pGlobalPoints			The global points.
	/// @param[out] pDistance					The pre-allocated distance array to be filled.
	/// @return												The distance array.
	//----------------------------------------------------------------------------------------
	Float *CalcSurfaceDistances(PolygonObject *pObject, BaseSelect *selected, Neighbor *pNeighbor = nullptr, Vector *pNormals = nullptr, Vector *pGlobalPoints = nullptr, Float *pDistance = nullptr);

	//----------------------------------------------------------------------------------------
	/// Used internally for surface distance calculations. Creates an array with an element for each point in @formatParam{pObject} set to the distance to selected.\n
	/// If @formatParam{pDistance} is passed this array is used instead.\n
	/// Either pass the various pointers (those with the @formatConstant{nullptr} default parameters) or let them be calculated automatically if @formatConstant{nullptr}.
	/// @param[in] pObject						The object to calculate.
	/// @param[in] pindex							The point to calculate.
	/// @param[in] pNeighbor					The neighbor information.
	/// @param[in] pNormals						The point normals.
	/// @param[in] pGlobalPoints			The global points.
	/// @param[out] pDistance					The pre-allocated distance array to be filled.
	/// @return												The distance array.
	//----------------------------------------------------------------------------------------
	Float *CalcSurfaceDistancesFromPoint(PolygonObject *pObject, Int32 pindex, Neighbor *pNeighbor = nullptr, Vector *pNormals = nullptr, Vector *pGlobalPoints = nullptr, Float *pDistance = nullptr);

	/// @}
};

#ifndef __API_INTERN__

//----------------------------------------------------------------------------------------
/// Lets implement custom CA brushes.
/// Normally it is only needed to implement MouseInputStart(), MouseInputDrag() and MouseInputEnd() functions, since the rest have default implementations in BrushBase.\n
/// There are other helper functions in BrushBase as well, available through the @ref m_pBrushBase pointer.
//----------------------------------------------------------------------------------------
class BrushToolData : public DescriptionToolData
{
	INSTANCEOF(BrushToolData, DescriptionToolData)

public:

	BrushToolData() { m_pBrushBase = nullptr; }
	~BrushToolData() { BrushBase::Free(m_pBrushBase); }

	BrushBase *m_pBrushBase;

	/// @name Overloads
	/// @{

	//----------------------------------------------------------------------------------------
	/// Implemented by BrushBase. Normally there is no need to overload this function.
	//----------------------------------------------------------------------------------------
	virtual Bool InitTool(BaseDocument* doc, BaseContainer& data, BaseThread* bt);

	//----------------------------------------------------------------------------------------
	/// Implemented by BrushBase. Normally there is no need to overload this function.
	//----------------------------------------------------------------------------------------
	virtual void FreeTool(BaseDocument* doc, BaseContainer& data);

	//----------------------------------------------------------------------------------------
	/// Implemented by BrushBase. Normally there is no need to overload this function.
	//----------------------------------------------------------------------------------------
	virtual void InitDefaultSettings(BaseDocument *doc, BaseContainer &data);

	//----------------------------------------------------------------------------------------
	/// Implemented by BrushBase. Normally there is no need to overload this function.
	//----------------------------------------------------------------------------------------
	virtual Bool GetDEnabling(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc);

	//----------------------------------------------------------------------------------------
	/// Implemented by BrushBase. Normally there is no need to overload this function.
	//----------------------------------------------------------------------------------------
	virtual Bool SetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags);

	//----------------------------------------------------------------------------------------
	/// Implemented by BrushBase. Normally there is no need to overload this function.
	//----------------------------------------------------------------------------------------
	virtual Bool GetDDescription(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags);

	//----------------------------------------------------------------------------------------
	/// Implemented by BrushBase. Normally there is no need to overload this function.
	//----------------------------------------------------------------------------------------
	virtual Bool Message(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data);

	//----------------------------------------------------------------------------------------
	/// Implemented by BrushBase. Normally there is no need to overload this function.
	//----------------------------------------------------------------------------------------
	virtual Bool GetCursorInfo(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc);

	//----------------------------------------------------------------------------------------
	/// Implemented by BrushBase. Normally there is no need to overload this function.
	//----------------------------------------------------------------------------------------
	virtual Bool MouseInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);

	/// @}

	/// @name Mouse Input
	/// @{

	//----------------------------------------------------------------------------------------
	/// Called at the start of mouse input. Initialize any data needed for the drag and set any flags needed.
	/// @param[in] doc								The document.
	/// @param[in] data								The data.
	/// @param[in] bd									The base draw.
	/// @param[in] win								The editor window.
	/// @param[in] msg								The input message.
	/// @param[in] flags							The flags. Add the flags needed with the @c |= operator: @enumerateEnum{BRUSHBASE_MOUSE_FLAG}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	virtual Bool MouseInputStart(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg, Int32 &flags) { return true; }

	//----------------------------------------------------------------------------------------
	/// Called during mouse drag.
	/// @param[in] doc								The document.
	/// @param[in] data								The data.
	/// @param[in] bd									The base draw.
	/// @param[in] win								The editor window.
	/// @param[in] msg								The input message.
	/// @param[in] vdata							The brush vertex data.
	/// @param[in] vcnt								The brush vertex count.
	/// @param[in] x									The mouse X position.
	/// @param[in] y									The mouse Y position.
	/// @param[in] flags							The flags. Add the flags needed with the @c |= operator: @enumerateEnum{BRUSHBASE_MOUSE_FLAG}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	virtual Bool MouseInputDrag(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg, BrushVertexData* vdata, Int32 vcnt, Float x, Float y, Int32 &flags) { return true; }

	//----------------------------------------------------------------------------------------
	/// Called after mouse drag. Free any data no longer needed.
	/// @param[in] doc								The document.
	/// @param[in] data								The data.
	/// @param[in] bd									The base draw.
	/// @param[in] win								The editor window.
	/// @param[in] msg								The input message.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	virtual Bool MouseInputEnd(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg) { return true; }

	/// @}
};

#endif

/// Character Animation library ID.
#define LIBRARY_CA 1019742

/// Brush library ID.
#define LIBRARY_BRUSH 1019809

/// @}

/// @cond IGNORE

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

struct CALibrary : public C4DLibrary
{
	// Weight Tag

	BaseObject *(*weightGetJoint)(CAWeightTag *tag, Int32 index, BaseDocument *doc);
	Int32 (*weightGetJointCount)(CAWeightTag *tag);
	Int32 (*weightFindJoint)(CAWeightTag *tag, BaseObject *op, BaseDocument *doc);
	JointRestState (*weightGetJointRestState)(CAWeightTag *tag, Int32 index);
	void (*weightSetJointRestState)(CAWeightTag *tag, Int32 index, const JointRestState &state);
	void (*weightGetWeightMapEx)(CAWeightTag *tag, Int32 index, Float32 *map, Int32 cnt);
	Bool (*weightSetWeightMap)(CAWeightTag *tag, Int32 index, Float32 *map, Int32 cnt);
	Int32 (*weightGetWeightCount)(CAWeightTag *tag, Int32 index);
	void (*weightGetIndexWeight)(CAWeightTag *tag, Int32 index, Int32 windex, Int32 &pntindex, Float &weight);
	Float (*weightGetWeight)(CAWeightTag *tag, Int32 index, Int32 pntindex);
	Bool (*weightSetWeight)(CAWeightTag *tag, Int32 index, Int32 pntindex, Float weight);
	UInt32 (*weightGetDirty)(CAWeightTag *tag);
	void (*weightDirty)(CAWeightTag *tag);

	// Joint Object

	void (*jointGetBone)(CAJointObject *op, Matrix &m, Float &len);
	CAWeightTag *(*jointGetWeightTag)(CAJointObject *op, Int32 &index);

	// Weight Tag

	Matrix (*weightGetGeomMg)(CAWeightTag *tag);
	void (*weightSetGeomMg)(CAWeightTag *tag, const Matrix &mg);
	Int32 (*weightAddJoint)(CAWeightTag *tag, BaseObject *op);
	void (*weightRemoveJoint)(CAWeightTag *tag, BaseObject *op);
	void (*weightCalculateBoneStates)(CAWeightTag *tag, Int32 index);
	Bool (*weightTransferWeightMap)(CAWeightTag *tag, BaseDocument *doc, CAWeightTag *dst, Int32 sindex, Int32 dindex, Int32 offset, Int32 cnt, AliasTrans *trans);

	// Pose Morph Tag

	Int32 (*pmorphGetCount)(CAPoseMorphTag *tag);
	CAMorph *(*pmorphGetMorph)(CAPoseMorphTag *tag, Int32 index);
	DescID (*pmorphGetDescID)(CAPoseMorphTag *tag, Int32 index);
	Int32 (*pmorphGetMode)(CAPoseMorphTag *tag);
	Int32 (*pmorphGetActive)(CAPoseMorphTag *tag);
	CAMorph *(*pmorphAdd)(CAPoseMorphTag *tag);
	void (*pmorphRemove)(CAPoseMorphTag *tag, Int32 index);
	void (*pmorphInitMorphs)(CAPoseMorphTag *tag);
	void (*pmorphUpdateMorphsEx)(CAPoseMorphTag *tag);
	Int32 (*pmorphGetMorphIndex)(CAPoseMorphTag *tag, CAMorph *morph);
	Bool (*pmorphExitEdit)(CAPoseMorphTag *tag, BaseDocument *doc, Bool apply);

	String (*pmorphGetName)(CAMorph *morph);
	Int32 (*pmorphGetID)(CAMorph *morph);
	void (*pmorphSetName)(CAMorph *morph, const String &name);
	Bool (*pmorphCopyFrom)(CAMorph *morph, CAMorph *src, AliasTrans *trn, CAMORPH_COPY_FLAGS flags);
	CAMorphNode *(*pmorphFind)(CAMorph *morph, CAPoseMorphTag *tag, BaseList2D *bl);
	CAMorphNode *(*pmorphGetFirst)(CAMorph *morph);
	Bool (*pmorphSetMode)(CAMorph *morph, BaseDocument *doc, CAPoseMorphTag *tag, CAMORPH_MODE_FLAGS flags, CAMORPH_MODE mode);
	Int32 (*pmorphFindIndex)(CAMorph *morph, CAPoseMorphTag *tag, BaseList2D *bl);
	CAMorphNode *(*pmorphFindFromIndex)(CAMorph *morph, CAPoseMorphTag *tag, Int32 index);
	Bool (*pmorphStore)(CAMorph *morph, BaseDocument *doc, CAPoseMorphTag *tag, CAMORPH_DATA_FLAGS flags);
	Bool (*pmorphApply)(CAMorph *morph, BaseDocument *doc, CAPoseMorphTag *tag, CAMORPH_DATA_FLAGS flags);
	Int32 (*pmorphGetNodeIndex)(CAMorph *morph, CAMorphNode *node);

	CAMorphNode *(*pmorphnodeGetNext)(CAMorphNode *node);
	CAMorphNode *(*pmorphnodeGetPrev)(CAMorphNode *node);
	CAMorphNode *(*pmorphnodeGetUp)(CAMorphNode *node);
	CAMorphNode *(*pmorphnodeGetDown)(CAMorphNode *node);
	BaseList2D *(*pmorphnodeGetLink)(CAMorphNode *node, CAPoseMorphTag *tag, CAMorph *morph, BaseDocument *doc);
	Int32 (*pmorphnodeGetPointCount)(CAMorphNode *node);
	Vector (*pmorphnodeGetPoint)(CAMorphNode *node, Int32 index);
	void (*pmorphnodeSetPoint)(CAMorphNode *node, Int32 index, const Vector &pnt);
	Int32 (*pmorphGetTangentCount)(CAMorphNode *node);
	Vector (*pmorphGetTangent)(CAMorphNode *node, Int32 index);
	void (*pmorphSetTangent)(CAMorphNode *node, Int32 index, const Vector &v);
	Int32 (*pmorphGetVertexMapTagCount)(CAMorphNode *node);
	Int32 (*pmorphGetVertexMapCount)(CAMorphNode *node, Int32 tindex);
	Float (*pmorphGetVertexMap)(CAMorphNode *node, Int32 tindex, Int32 index);
	void (*pmorphSetVertexMap)(CAMorphNode *node, Int32 tindex, Int32 index, Float v);
	Bool (*pmorphSetVertexMapCount)(CAMorphNode *node, Int32 tindex, Int32 cnt);
	Bool (*pmorphSetPointCount)(CAMorphNode *node, Int32 cnt);
	Bool (*pmorphSetTangentCount)(CAMorphNode *node, Int32 cnt);
	CAMORPH_DATA_FLAGS (*pmorphGetInfo)(CAMorphNode *node);
	Vector (*pmorphGetP)(CAMorphNode *node);
	Vector (*pmorphGetS)(CAMorphNode *node);
	Vector (*pmorphGetR)(CAMorphNode *node);
	void (*pmorphSetP)(CAMorphNode *node, const Vector &p);
	void (*pmorphSetS)(CAMorphNode *node, const Vector &s);
	void (*pmorphSetR)(CAMorphNode *node, const Vector &r);
	Int32 (*pmorphGetParamCount)(CAMorphNode *node);
	Bool (*pmorphSetParamCount)(CAMorphNode *node, Int32 cnt);
	Bool (*pmorphGetParam)(CAMorphNode *node, Int32 index, GeData &data, DescID &id);
	void (*pmorphSetParam)(CAMorphNode *node, Int32 index, const GeData &data, const DescID &id);
	Int32 (*pmorphGetUVTagCount)(CAMorphNode *node);
	Int32 (*pmorphGetUVCount)(CAMorphNode *node, Int32 tindex);
	Bool (*pmorphSetUVCount)(CAMorphNode *node, Int32 tindex, Int32 cnt);
	void (*pmorphGetUV)(CAMorphNode *node, Int32 tindex, Int32 index, UVWStruct &uv);
	void (*pmorphSetUV)(CAMorphNode *node, Int32 tindex, Int32 index, const UVWStruct &uv);
	Int32 (*pmorphGetWeightMapTagCount)(CAMorphNode *node);
	Int32 (*pmorphGetWeightMapJointCount)(CAMorphNode *node, Int32 tindex);
	Int32 (*pmorphGetWeightMapCount)(CAMorphNode *node, Int32 tindex, Int32 jindex);
	Bool (*pmorphSetWeightMapCount)(CAMorphNode *node, Int32 tindex, Int32 jindex, Int32 cnt);
	Float (*pmorphGetWeightMap)(CAMorphNode *node, Int32 tindex, Int32 jindex, Int32 index);
	void (*pmorphSetWeightMap)(CAMorphNode *node, Int32 tindex, Int32 jindex, Int32 index, Float v);

	void (*xrefStripRefData)(BaseDocument *doc, BaseList2D *bl);
	Bool (*xrefHasRefs)(BaseDocument *doc);
	Int32 (*xrefGetState)();
	UInt64 (*xrefGetID)(BaseList2D *bl);
	Bool (*xrefHasParam)(BaseDocument *doc, BaseList2D *bl, const DescID &id);
	Bool (*xrefGetParam)(BaseDocument *doc, BaseList2D *bl, const DescID &id, GeData &dat);
	Bool (*xrefRemoveParam)(BaseDocument *doc, BaseList2D *bl, const DescID &id);

	void (*pmorphSetActiveMorphIndex)(CAPoseMorphTag *tag, Int32 index);
	BaseList2D *(*pmorphGetTarget)(CAMorph *morph, BaseDocument *doc);
	void (*pmorphSetTarget)(CAMorph *morph, CAPoseMorphTag *tag, BaseDocument *doc, BaseList2D *bl);
	void (*pmorphSetStrength)(CAMorph *morph, Float strength);
	Float (*pmorphGetStrength)(CAMorph *morph);
	void (*pmorphUpdateMorphs)(CAPoseMorphTag *tag, BaseDocument *doc);
	void(*weightGetWeightMap)(CAWeightTag *tag, Int32 index, Float32 *map, Int32 cnt, Bool includeEffectors);
};

struct BrushBaseLibrary : public C4DLibrary
{
	iBrushBase *(*Alloc)();
	void (*Free)(iBrushBase *&p);

	Bool (iBrushBase::*InitTool)(BaseDocument* doc, BaseContainer& data, BaseThread* bt, BrushToolData *tool);
	void (iBrushBase::*FreeTool)(BaseDocument* doc, BaseContainer& data);
	void (iBrushBase::*InitDefaultSettings)(BaseDocument *doc, BaseContainer &data);
	Bool (iBrushBase::*GetDEnabling)(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc);
	Bool (iBrushBase::*SetDParameter)(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags);
	Bool (iBrushBase::*GetDDescription)(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags);
	Bool (iBrushBase::*Message)(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data);
	Bool (iBrushBase::*GetCursorInfo)(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc);
	Bool (iBrushBase::*MouseInput)(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg);
	BrushVertexData *(iBrushBase::*GetSelected)(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Int32 &vcnt, Int32 x, Int32 y, Float rad, BaseObject *op);
	Float (iBrushBase::*GetCursor)(Int32 &x, Int32 &y);
	void (iBrushBase::*GetObjectInfo)(BrushObjectData *data, BrushObjectInfo &info);
	Bool (iBrushBase::*GetObjectInfoOp)(BaseObject *op, BrushObjectInfo &info);
	Bool (iBrushBase::*ValidateObjects)(BaseDocument *doc, BaseContainer& data);
	BrushPixelData *(iBrushBase::*GetObjectAt)(Int32 x, Int32 y);
	Float (iBrushBase::*GetFalloff)(Float dst, Int32 flags);
	Bool (iBrushBase::*GetObjects)(BaseDocument *doc, AtomArray *objects);
	Bool (iBrushBase::*UpdateCache)(BaseDocument *doc, BaseContainer& data, BaseDraw *bd, Bool force);
	Float *(iBrushBase::*CalcSurfaceDistances)(PolygonObject *pObject, BaseSelect *selected, Neighbor *pNeighbor, Vector *pNormals, Vector *pGlobalPoints, Float *pDistance);
	Float *(iBrushBase::*CalcSurfaceDistancesFromPoint)(PolygonObject *pObject, Int32 pindex, Neighbor *pNeighbor, Vector *pNormals, Vector *pGlobalPoints, Float *pDistance);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

/// @endcond

#endif // LIB_CA_H__
