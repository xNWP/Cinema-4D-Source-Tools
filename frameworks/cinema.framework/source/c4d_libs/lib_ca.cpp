#include "lib_ca.h"

//////////////////////////////////////////////////////////////////////////

CALibrary *lib_ca = nullptr;

static CALibrary *CheckCALib(Int32 offset)
{
	return (CALibrary*)CheckLib(LIBRARY_CA, offset, (C4DLibrary**)&lib_ca);
}

#define CALibCall(b) 		CALibrary *lib = CheckCALib(LIBOFFSET(CALibrary, b)); \
															if (!lib || !lib->b) return; \
															(lib->b)

#define CALibCallR(a, b)  CALibrary *lib = CheckCALib(LIBOFFSET(CALibrary, b)); \
															if (!lib || !lib->b) return a; \
															return (lib->b)

//////////////////////////////////////////////////////////////////////////

BaseObject *CAWeightTag::GetJoint(Int32 index, BaseDocument *doc) { CALibCallR(nullptr, weightGetJoint)(this, index, doc); }
Int32 CAWeightTag::GetJointCount() { CALibCallR(0, weightGetJointCount)(this); }
Int32 CAWeightTag::FindJoint(BaseObject *op, BaseDocument *doc) { CALibCallR(NOTOK, weightFindJoint)(this, op, doc); }
JointRestState CAWeightTag::GetJointRestState(Int32 index) { CALibCallR(JointRestState(), weightGetJointRestState)(this, index); }
void CAWeightTag::SetJointRestState(Int32 index, const JointRestState &state) { CALibCall(weightSetJointRestState)(this, index, state); }
void CAWeightTag::GetWeightMap(Int32 index, Float32 *map, Int32 cnt, Bool includeEffectors) { CALibCall(weightGetWeightMap)(this, index, map, cnt, includeEffectors); }
Bool CAWeightTag::SetWeightMap(Int32 index, Float32 *map, Int32 cnt) { CALibCallR(false, weightSetWeightMap)(this, index, map, cnt); }
Int32 CAWeightTag::GetWeightCount(Int32 index) { CALibCallR(0, weightGetWeightCount)(this, index); }
void CAWeightTag::GetIndexWeight(Int32 index, Int32 windex, Int32 &pntindex, Float &weight) { CALibCall(weightGetIndexWeight)(this, index, windex, pntindex, weight); }
Float CAWeightTag::GetWeight(Int32 index, Int32 pntindex) { CALibCallR(0.0, weightGetWeight)(this, index, pntindex); }
Bool CAWeightTag::SetWeight(Int32 index, Int32 pntindex, Float weight) { CALibCallR(false, weightSetWeight)(this, index, pntindex, weight); }
UInt32 CAWeightTag::GetWeightDirty() { CALibCallR(0, weightGetDirty)(this); }
void CAWeightTag::WeightDirty() { CALibCall(weightDirty)(this); }
Matrix CAWeightTag::GetGeomMg() { CALibCallR(Matrix(), weightGetGeomMg)(this); }
void CAWeightTag::SetGeomMg(const Matrix &mg) { CALibCall(weightSetGeomMg)(this, mg); }
Int32 CAWeightTag::AddJoint(BaseObject *op) { CALibCallR(NOTOK, weightAddJoint)(this, op); }
void CAWeightTag::RemoveJoint(BaseObject *op) { CALibCall(weightRemoveJoint)(this, op); }
void CAWeightTag::CalculateBoneStates(Int32 index) { CALibCall(weightCalculateBoneStates)(this, index); }
Bool CAWeightTag::TransferWeightMap(BaseDocument *doc, CAWeightTag *dst, Int32 sindex, Int32 dindex, Int32 offset, Int32 cnt, AliasTrans *trans) { CALibCallR(false, weightTransferWeightMap)(this, doc, dst, sindex, dindex, offset, cnt, trans); }

//////////////////////////////////////////////////////////////////////////

Int32 CAPoseMorphTag::GetMorphCount() { CALibCallR(0, pmorphGetCount)(this); }
CAMorph *CAPoseMorphTag::GetMorph(Int32 index) { CALibCallR(nullptr, pmorphGetMorph)(this, index); }
DescID CAPoseMorphTag::GetMorphID(Int32 index) { CALibCallR(DescID(), pmorphGetDescID)(this, index); }
Int32 CAPoseMorphTag::GetActiveMorphIndex() { CALibCallR(NOTOK, pmorphGetActive)(this); }
Int32 CAPoseMorphTag::GetMode() { CALibCallR(NOTOK, pmorphGetMode)(this); }
CAMorph *CAPoseMorphTag::AddMorph() { CALibCallR(nullptr, pmorphAdd)(this); }
void CAPoseMorphTag::RemoveMorph(Int32 index) { CALibCall(pmorphRemove)(this, index); }
void CAPoseMorphTag::InitMorphs() { CALibCall(pmorphInitMorphs)(this); }
void CAPoseMorphTag::UpdateMorphs(BaseDocument *doc) { CALibCall(pmorphUpdateMorphs)(this, doc); }
Int32 CAPoseMorphTag::GetMorphIndex(CAMorph *morph) { CALibCallR(NOTOK, pmorphGetMorphIndex)(this, morph); }
Bool CAPoseMorphTag::ExitEdit(BaseDocument *doc, Bool apply) { CALibCallR(false, pmorphExitEdit)(this, doc, apply); }
void CAPoseMorphTag::SetActiveMorphIndex(Int32 index) { CALibCall(pmorphSetActiveMorphIndex)(this, index); }

String CAMorph::GetName() { CALibCallR(String(), pmorphGetName)(this); }
Int32 CAMorph::GetID() { CALibCallR(NOTOK, pmorphGetID)(this); }
void CAMorph::SetName(const String &name) { CALibCall(pmorphSetName)(this, name); }
Bool CAMorph::CopyFrom(CAMorph *src, AliasTrans *trn, CAMORPH_COPY_FLAGS flags) { CALibCallR(false, pmorphCopyFrom)(this, src, trn, flags); }
CAMorphNode *CAMorph::Find(CAPoseMorphTag *tag, BaseList2D *bl) { CALibCallR(nullptr, pmorphFind)(this, tag, bl); }
CAMorphNode *CAMorph::GetFirst() { CALibCallR(nullptr, pmorphGetFirst)(this); }
Bool CAMorph::SetMode(BaseDocument *doc, CAPoseMorphTag *tag, CAMORPH_MODE_FLAGS flags, CAMORPH_MODE mode) { CALibCallR(false, pmorphSetMode)(this, doc, tag, flags, mode); }
Int32 CAMorph::FindIndex(CAPoseMorphTag *tag, BaseList2D *bl) { CALibCallR(NOTOK, pmorphFindIndex)(this, tag, bl); }
CAMorphNode *CAMorph::FindFromIndex(CAPoseMorphTag *tag, Int32 index) { CALibCallR(nullptr, pmorphFindFromIndex)(this, tag, index); }
Bool CAMorph::Store(BaseDocument *doc, CAPoseMorphTag *tag, CAMORPH_DATA_FLAGS flags) { CALibCallR(false, pmorphStore)(this, doc, tag, flags); }
Bool CAMorph::Apply(BaseDocument *doc, CAPoseMorphTag *tag, CAMORPH_DATA_FLAGS flags) { CALibCallR(false, pmorphApply)(this, doc, tag, flags); }
Int32 CAMorph::GetNodeIndex(CAMorphNode *node) { CALibCallR(NOTOK, pmorphGetNodeIndex)(this, node); }
BaseList2D *CAMorph::GetTarget(BaseDocument *doc) { CALibCallR(nullptr, pmorphGetTarget)(this, doc); }
void CAMorph::SetTarget(CAPoseMorphTag *tag, BaseDocument *doc, BaseList2D *bl) { CALibCall(pmorphSetTarget)(this, tag, doc, bl); }
void CAMorph::SetStrength(Float strength) { CALibCall(pmorphSetStrength)(this, strength); }
Float CAMorph::GetStrength() { CALibCallR(0.0, pmorphGetStrength)(this); }

CAMorphNode *CAMorphNode::GetNext() { CALibCallR(nullptr, pmorphnodeGetNext)(this); }
CAMorphNode *CAMorphNode::GetPrev() { CALibCallR(nullptr, pmorphnodeGetPrev)(this); }
CAMorphNode *CAMorphNode::GetUp() { CALibCallR(nullptr, pmorphnodeGetUp)(this); }
CAMorphNode *CAMorphNode::GetDown() { CALibCallR(nullptr, pmorphnodeGetDown)(this); }
BaseList2D *CAMorphNode::GetLink(CAPoseMorphTag *tag, CAMorph *morph, BaseDocument *doc) { CALibCallR(nullptr, pmorphnodeGetLink)(this, tag, morph, doc); }
Int32 CAMorphNode::GetPointCount() { CALibCallR(0, pmorphnodeGetPointCount)(this); }
Vector CAMorphNode::GetPoint(Int32 index) { CALibCallR(Vector(), pmorphnodeGetPoint)(this, index); }
void CAMorphNode::SetPoint(Int32 index, const Vector &pnt) { CALibCall(pmorphnodeSetPoint)(this, index, pnt); }
Int32 CAMorphNode::GetTangentCount() { CALibCallR(0, pmorphGetTangentCount)(this); }
Vector CAMorphNode::GetTangent(Int32 index) { CALibCallR(Vector(), pmorphGetTangent)(this, index); }
void CAMorphNode::SetTangent(Int32 index, const Vector &v) { CALibCall(pmorphSetTangent)(this, index, v); }
Int32 CAMorphNode::GetVertexMapTagCount() { CALibCallR(0, pmorphGetVertexMapTagCount)(this); }
Int32 CAMorphNode::GetVertexMapCount(Int32 tindex) { CALibCallR(0, pmorphGetVertexMapCount)(this, tindex); }
Float CAMorphNode::GetVertexMap(Int32 tindex, Int32 index) { CALibCallR(0.0, pmorphGetVertexMap)(this, tindex, index); }
void CAMorphNode::SetVertexMap(Int32 tindex, Int32 index, Float v) { CALibCall(pmorphSetVertexMap)(this, tindex, index, v); }
Bool CAMorphNode::SetVertexMapCount(Int32 tindex, Int32 cnt) { CALibCallR(false, pmorphSetVertexMapCount)(this, tindex, cnt); }
Bool CAMorphNode::SetPointCount(Int32 cnt) { CALibCallR(false, pmorphSetPointCount)(this, cnt); }
Bool CAMorphNode::SetTangentCount(Int32 cnt) { CALibCallR(false, pmorphSetTangentCount)(this, cnt); }
CAMORPH_DATA_FLAGS CAMorphNode::GetInfo() { CALibCallR(CAMORPH_DATA_FLAGS_0, pmorphGetInfo)(this); }
Vector CAMorphNode::GetP() { CALibCallR(Vector(0.0), pmorphGetP)(this); }
Vector CAMorphNode::GetS() { CALibCallR(Vector(0.0), pmorphGetS)(this); }
Vector CAMorphNode::GetR() { CALibCallR(Vector(0.0), pmorphGetR)(this); }
void CAMorphNode::SetP(const Vector &p) { CALibCall(pmorphSetP)(this, p); }
void CAMorphNode::SetS(const Vector &s) { CALibCall(pmorphSetS)(this, s); }
void CAMorphNode::SetR(const Vector &r) { CALibCall(pmorphSetR)(this, r); }
Int32 CAMorphNode::GetParamCount() { CALibCallR(false, pmorphGetParamCount)(this); }
Bool CAMorphNode::SetParamCount(Int32 cnt) { CALibCallR(false, pmorphSetParamCount)(this, cnt); }
Bool CAMorphNode::GetParam(Int32 index, GeData &data, DescID &id) { CALibCallR(false, pmorphGetParam)(this, index, data, id); }
void CAMorphNode::SetParam(Int32 index, const GeData &data, const DescID &id) { CALibCall(pmorphSetParam)(this, index, data, id); }
Int32 CAMorphNode::GetUVTagCount() { CALibCallR(false, pmorphGetUVTagCount)(this); }
Int32 CAMorphNode::GetUVCount(Int32 tindex) { CALibCallR(false, pmorphGetUVCount)(this, tindex); }
Bool CAMorphNode::SetUVCount(Int32 tindex, Int32 cnt) { CALibCallR(false, pmorphSetUVCount)(this, tindex, cnt); }
void CAMorphNode::GetUV(Int32 tindex, Int32 index, UVWStruct &uv) { CALibCall(pmorphGetUV)(this, tindex, index, uv); }
void CAMorphNode::SetUV(Int32 tindex, Int32 index, const UVWStruct &uv) { CALibCall(pmorphSetUV)(this, tindex, index, uv); }
Int32 CAMorphNode::GetWeightMapTagCount() { CALibCallR(false, pmorphGetWeightMapTagCount)(this); }
Int32 CAMorphNode::GetWeightMapJointCount(Int32 tindex) { CALibCallR(false, pmorphGetWeightMapJointCount)(this, tindex); }
Int32 CAMorphNode::GetWeightMapCount(Int32 tindex, Int32 jindex) { CALibCallR(false, pmorphGetWeightMapCount)(this, tindex, jindex); }
Bool CAMorphNode::SetWeightMapCount(Int32 tindex, Int32 jindex, Int32 cnt) { CALibCallR(false, pmorphSetWeightMapCount)(this, tindex, jindex, cnt); }
Float CAMorphNode::GetWeightMap(Int32 tindex, Int32 jindex, Int32 index) { CALibCallR(false, pmorphGetWeightMap)(this, tindex, jindex, index); }
void CAMorphNode::SetWeightMap(Int32 tindex, Int32 jindex, Int32 index, Float v) { CALibCall(pmorphSetWeightMap)(this, tindex, jindex, index, v); }

//////////////////////////////////////////////////////////////////////////

void CAJointObject::GetBone(Matrix &m, Float &len) { CALibCall(jointGetBone)(this, m, len); }
CAWeightTag *CAJointObject::GetWeightTag(Int32 &index) { CALibCallR(nullptr, jointGetWeightTag)(this, index); }

//////////////////////////////////////////////////////////////////////////

void RemoveXRefData(BaseDocument *doc, BaseList2D *bl)
{
	CALibCall(xrefStripRefData)(doc, bl);
}

Bool HasDocumentXRefs(BaseDocument *doc)
{
	CALibCallR(false, xrefHasRefs)(doc);
}

Int32 GetDocumentXRefState()
{
	CALibCallR(0, xrefGetState)();
}

UInt64 GetXRefID(BaseList2D *bl)
{
	CALibCallR(0, xrefGetID)(bl);
}

Bool XRefHasParam(BaseDocument *doc, BaseList2D *bl, const DescID &id)
{
	CALibCallR(false, xrefHasParam)(doc, bl, id);
}

Bool XRefGetParam(BaseDocument *doc, BaseList2D *bl, const DescID &id, GeData &dat)
{
	CALibCallR(0, xrefGetParam)(doc, bl, id, dat);
}

Bool XRefRemoveParam(BaseDocument *doc, BaseList2D *bl, const DescID &id)
{
	CALibCallR(false, xrefRemoveParam)(doc, bl, id);
}

//////////////////////////////////////////////////////////////////////////

BrushBaseLibrary *lib_brushbase = nullptr;

static BrushBaseLibrary *CheckBrushBaseLibrary(Int32 offset)
{
	return (BrushBaseLibrary*)CheckLib(LIBRARY_BRUSH, offset, (C4DLibrary**)&lib_brushbase);
}

#define BrushBaseLibraryCall(b) 		BrushBaseLibrary *lib = CheckBrushBaseLibrary(LIBOFFSET(BrushBaseLibrary, b)); \
															if (!lib || !lib->b) return; \
															(((iBrushBase*)this)->*lib->b)

#define BrushBaseLibraryCallR(a, b)  BrushBaseLibrary *lib = CheckBrushBaseLibrary(LIBOFFSET(BrushBaseLibrary, b)); \
															if (!lib || !lib->b) return a; \
															return (((iBrushBase*)this)->*lib->b)

BrushBase* BrushBase::Alloc()
{
	BrushBaseLibrary *lib = CheckBrushBaseLibrary(LIBOFFSET(BrushBaseLibrary, Alloc)); if (!lib) return nullptr;
	return (BrushBase*)lib->Alloc();
}

void BrushBase::Free(BrushBase *&p)
{
	if (!p) return;
	BrushBaseLibrary *lib = CheckBrushBaseLibrary(LIBOFFSET(BrushBaseLibrary, Free)); if (!lib) return;
	iBrushBase* i = (iBrushBase*)p;
	lib->Free(i);
	p = nullptr;
}

Bool BrushBase::InitTool(BaseDocument* doc, BaseContainer& data, BaseThread* bt, BrushToolData *tool) { BrushBaseLibraryCallR(false, InitTool)(doc, data, bt, tool); }
void BrushBase::FreeTool(BaseDocument* doc, BaseContainer& data) { BrushBaseLibraryCall(FreeTool)(doc, data); }
void BrushBase::InitDefaultSettings(BaseDocument *doc, BaseContainer &data) { BrushBaseLibraryCall(InitDefaultSettings)(doc, data); }
Bool BrushBase::GetDEnabling(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc) { BrushBaseLibraryCallR(false, GetDEnabling)(doc, data, id, t_data, flags, itemdesc); }
Bool BrushBase::SetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags) { BrushBaseLibraryCallR(false, SetDParameter)(doc, data, id, t_data, flags); }
Bool BrushBase::GetDDescription(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags) { BrushBaseLibraryCallR(false, GetDDescription)(doc, data, description, flags); }
Bool BrushBase::Message(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data) { BrushBaseLibraryCallR(false, Message)(doc, data, type, t_data); }
Bool BrushBase::GetCursorInfo(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc) { BrushBaseLibraryCallR(false, GetCursorInfo)(doc, data, bd, x, y, bc); }
Bool BrushBase::MouseInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg) { BrushBaseLibraryCallR(false, MouseInput)(doc, data, bd, win, msg); }
BrushVertexData *BrushBase::GetSelected(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Int32 &vcnt, Int32 x, Int32 y, Float rad, BaseObject *op) { BrushBaseLibraryCallR(nullptr, GetSelected)(doc, data, bd, vcnt, x, y, rad, op); }
Float BrushBase::GetCursor(Int32 &x, Int32 &y) { BrushBaseLibraryCallR(0.0, GetCursor)(x, y); }
void BrushBase::GetObjectInfo(BrushObjectData *data, BrushObjectInfo &info) { BrushBaseLibraryCall(GetObjectInfo)(data, info); }
Bool BrushBase::GetObjectInfo(BaseObject *op, BrushObjectInfo &info) { BrushBaseLibraryCallR(false, GetObjectInfoOp)(op, info); }
BrushPixelData *BrushBase::GetObjectAt(Int32 x, Int32 y) { BrushBaseLibraryCallR(nullptr, GetObjectAt)(x, y); }
Bool BrushBase::ValidateObjects(BaseDocument *doc, BaseContainer& data) { BrushBaseLibraryCallR(false, ValidateObjects)(doc, data); }
Float BrushBase::GetFalloff(Float dst, Int32 flags) { BrushBaseLibraryCallR(0.0, GetFalloff)(dst, flags); }
Bool BrushBase::GetObjects(BaseDocument *doc, AtomArray *objects) { BrushBaseLibraryCallR(false, GetObjects)(doc, objects); }
Bool BrushBase::UpdateCache(BaseDocument *doc, BaseContainer& data, BaseDraw *bd, Bool force) { BrushBaseLibraryCallR(false, UpdateCache)(doc, data, bd, force); }
Float *BrushBase::CalcSurfaceDistances(PolygonObject *pObject, BaseSelect *selected, Neighbor *pNeighbor, Vector *pNormals, Vector *pGlobalPoints, Float *pDistance) { BrushBaseLibraryCallR(nullptr, CalcSurfaceDistances)(pObject, selected, pNeighbor, pNormals, pGlobalPoints, pDistance); }
Float *BrushBase::CalcSurfaceDistancesFromPoint(PolygonObject *pObject, Int32 pindex, Neighbor *pNeighbor, Vector *pNormals, Vector *pGlobalPoints, Float *pDistance) { BrushBaseLibraryCallR(nullptr, CalcSurfaceDistancesFromPoint)(pObject, pindex, pNeighbor, pNormals, pGlobalPoints, pDistance); }

//////////////////////////////////////////////////////////////////////////

#ifndef __API_INTERN__

Bool BrushToolData::InitTool(BaseDocument* doc, BaseContainer& data, BaseThread* bt)
{
	if (!m_pBrushBase) m_pBrushBase = BrushBase::Alloc();
	if (!m_pBrushBase) return false;
	return m_pBrushBase->InitTool(doc, data, bt, this);
}
void BrushToolData::FreeTool(BaseDocument* doc, BaseContainer& data)
{
	if (m_pBrushBase) m_pBrushBase->FreeTool(doc, data);
	BrushBase::Free(m_pBrushBase);
}

void BrushToolData::InitDefaultSettings(BaseDocument *doc, BaseContainer &data)
{
	if (!m_pBrushBase) m_pBrushBase = BrushBase::Alloc();
	if (m_pBrushBase) m_pBrushBase->InitDefaultSettings(doc, data);
}
Bool BrushToolData::GetDEnabling(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc) { return (m_pBrushBase)?m_pBrushBase->GetDEnabling(doc, data, id, t_data, flags, itemdesc):false; }
Bool BrushToolData::SetDParameter(BaseDocument* doc, BaseContainer& data, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags) { return (m_pBrushBase)?m_pBrushBase->SetDParameter(doc, data, id, t_data, flags):false; }
Bool BrushToolData::GetDDescription(BaseDocument* doc, BaseContainer& data, Description* description, DESCFLAGS_DESC& flags)
{
	if (!m_pBrushBase) m_pBrushBase = BrushBase::Alloc();	// FIX[12637]
	if (!SUPER::GetDDescription(doc, data, description, flags)) return false;
	return (m_pBrushBase)?m_pBrushBase->GetDDescription(doc, data, description, flags):false;
}
Bool BrushToolData::Message(BaseDocument *doc, BaseContainer &data, Int32 type, void *t_data) { return (m_pBrushBase)?m_pBrushBase->Message(doc, data, type, t_data):false; }
Bool BrushToolData::GetCursorInfo(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, Float x, Float y, BaseContainer& bc) { return (m_pBrushBase)?m_pBrushBase->GetCursorInfo(doc, data, bd, x, y, bc):false; }
Bool BrushToolData::MouseInput(BaseDocument* doc, BaseContainer& data, BaseDraw* bd, EditorWindow* win, const BaseContainer& msg) { return (m_pBrushBase)?m_pBrushBase->MouseInput(doc, data, bd, win, msg):false; }

#endif
