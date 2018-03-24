#include "operatingsystem.h"
#include "c4d_objectplugin.h"
#include "c4d_memory.h"
#include "c4d_general.h"

#ifdef __API_INTERN__
	#include "c4d_resource.h"
	#include "basedraw.h"
	#include "res_colortab_priv.h"
#else
	#include "c4d_tools.h"
	#include "c4d_basebitmap.h"
	#include "c4d_file.h"
	#include "c4d_resource.h"
	#include "c4d_baseobject.h"
	#include "c4d_basedraw.h"
	#include "description/dbasedraw.h"
#endif

Vector HandleInfo::CalculateNewPosition(BaseDraw* bd, const Matrix& mg, const Vector& mouse_pos) const
{
	if (!bd)
		return position;
	Vector result = mg * position;
	switch (type)
	{
		case HANDLECONSTRAINTTYPE_LINEAR:
#ifdef USE_API_MAXON
			result = bd->ProjectPointOnLine(mg * position, mg.sqmat * direction, mouse_pos.x, mouse_pos.y);
#else
			result = bd->ProjectPointOnLine(mg * position, mg.TransformVector(direction), mouse_pos.x, mouse_pos.y);
#endif
			break;
		case HANDLECONSTRAINTTYPE_PLANAR:
		{
			Int32 err;
#ifdef USE_API_MAXON
			result = bd->ProjectPointOnPlane(mg * position, mg.sqmat * direction, mouse_pos.x, mouse_pos.y, &err);
#else
			result = bd->ProjectPointOnPlane(mg * position, mg.TransformVector(direction), mouse_pos.x, mouse_pos.y, &err);
#endif
			if (err)
			{
				Vector dir = Cross(!(bd->WS(mg * (position + direction)) - bd->WS(mg * position)), Vector(0.0, 0.0, 1.0));
				dir = !(bd->SW(bd->WS(mg * position) + dir) - (mg * position));
				result = bd->ProjectPointOnLine(mg * position, dir, mouse_pos.x, mouse_pos.y);
			}
			break;
		}
		case HANDLECONSTRAINTTYPE_FREE:
			if (mouse_pos.z != 0.0)
				result = bd->SW(mouse_pos);
			else
				result = bd->SW(Vector(mouse_pos.x, mouse_pos.y, bd->WC(result).z));
			break;
		case HANDLECONSTRAINTTYPE_RADIAL:
#ifdef USE_API_MAXON
			result = bd->ProjectPointOnPlane(mg * center, mg.sqmat * direction, mouse_pos.x, mouse_pos.y);
#else
			result = bd->ProjectPointOnPlane(mg * center, mg.TransformVector(direction), mouse_pos.x, mouse_pos.y);
#endif
			result = center + (radius * !(result - center));
			break;
		case HANDLECONSTRAINTTYPE_SPHERICAL:
		{
			Float r, cp;

			r = radius * bd->WP_W(mg * center, true);
			if (r == 0.0)
				r = 0.1;

			result = (mouse_pos - bd->WS(mg * center));
			result.z = 0.0;
			cp = FMin(result.GetLength(), r);
			result = cp * !result;
			result.z = -Cos(ASin(cp / r)) * r;
			result = bd->SW(result + bd->WS(mg * center));
			break;
		}
		default:
			break;
	}
	return ~mg * result;
}

void ObjectData::GetDimension(BaseObject* op, Vector* mp, Vector* rad)
{
	// override GetDimension if you do not want C4D's default handling of bounding boxes and set *mp/*rad to 0.0
}

DRAWRESULT ObjectData::Draw(BaseObject* op, DRAWPASS drawpass, BaseDraw* bd, BaseDrawHelp* bh)
{
	if (drawpass != DRAWPASS_HANDLES)
		return DRAWRESULT_SKIP;

	Int32	 i, pass;
	Vector p;
	Int32	 cnt = GetHandleCount(op);
	if (!cnt)
		return DRAWRESULT_SKIP;

#ifdef __API_INTERN__
	Int32					hitid = C4DOS.Bo->GetHighlightHandle(op, bd);
	const Matrix& mg = bh->m;
#else
	Int32					hitid = op->GetHighlightHandle(bd);
	const Matrix& mg = bh->GetMg();
#endif
	Vector col1 = GetViewColor(VIEWCOLOR_SELECTION_PREVIEW);
	Vector col2 = GetViewColor(VIEWCOLOR_ACTIVEPOINT);

	bd->SetMatrix_Matrix(op, mg);

	for (pass = 0; pass < 2; pass++)
	{
		if (pass == 0)
			bd->SetPen(col2);
		else
			bd->SetPen(col1);

		for (i = 0; i < cnt; i++)
		{
			if ((i == hitid) != pass)
				continue;
			HandleInfo info;
			GetHandle(op, i, info);
			if (info.type == HANDLECONSTRAINTTYPE_INVALID)
				continue;
			bd->DrawHandle(info.position, DRAWHANDLE_BIG, 0);

			// #ifndef __API_INTERN__
			// bd->Line3D(Vector(0.0,0.0,0.0)*mg,p);
			// #endif
		}
	}

	return DRAWRESULT_OK;
}

DRAWRESULT ObjectData::DrawShadow(BaseObject* op, BaseDraw* bd, BaseDrawHelp* bh)
{
	return DRAWRESULT_SKIP;
}

void ObjectData::GetHandle(BaseObject* op, Int32 i, HandleInfo& info)
{
}

void ObjectData::SetHandle(BaseObject* op, Int32 i, Vector p, const HandleInfo& info)
{
}

Int32 ObjectData::GetHandleCount(BaseObject* op)
{
	return 0;
}

Int32 ObjectData::DetectHandle(BaseObject* op, BaseDraw* bd, Int32 x, Int32 y, QUALIFIER qualifier)
{
	if (qualifier & QUALIFIER_CTRL)
		return NOTOK;

	Matrix mg = op->GetMg();
	Int32	 i, ret = NOTOK;

	for (i = 0; i < GetHandleCount(op); i++)
	{
		HandleInfo info;
		GetHandle(op, i, info);
		if (info.type == HANDLECONSTRAINTTYPE_INVALID)
			continue;

		if (bd->PointInRange(mg * info.position, x, y))
		{
			ret = i;
			if (!(qualifier & QUALIFIER_SHIFT))
				break;
		}
	}
	return ret;
}

Bool ObjectData::MoveHandle(BaseObject* op, BaseObject* undo, const Vector& mouse_pos, Int32 hit_id, QUALIFIER qualifier, BaseDraw* bd)
{
	Matrix		 mg = op->GetUpMg() * undo->GetMl();
	HandleInfo info;

	undo->GetNodeData<ObjectData>()->GetHandle(undo, hit_id, info);
	SetHandle(op, hit_id, info.CalculateNewPosition(bd, mg, mouse_pos), info);

	return true;
}

SplineObject* ObjectData::GetContour(BaseObject* op, BaseDocument* doc, Float lod, BaseThread* bt)
{
	return nullptr;
}

BaseObject* ObjectData::GetVirtualObjects(BaseObject* op, HierarchyHelp* hh)
{
	return nullptr;
}

Bool ObjectData::ModifyObject(BaseObject* op, BaseDocument* doc, BaseObject* mod, const Matrix& op_mg, const Matrix& mod_mg, Float lod, Int32 flags, BaseThread* thread)
{
	return true;
}

void ObjectData::CheckDirty(BaseObject* op, BaseDocument* doc)
{
}

void ObjectData::ModifyParticles(BaseObject* op, Particle* pp, BaseParticle* ss, Int32 pcnt, Float diff)
{
}

void ObjectData::GetModelingAxis(BaseObject* op, BaseDocument* doc, Matrix& axis)
{
}

Bool ObjectData::AddToExecution(BaseObject* op, PriorityList* list)
{
	return false;
}

EXECUTIONRESULT ObjectData::Execute(BaseObject* op, BaseDocument* doc, BaseThread* bt, Int32 priority, EXECUTIONFLAGS flags)
{
	return EXECUTIONRESULT_OK;
}

static void FillObjectPlugin(OBJECTPLUGIN* np, DataAllocator* npalloc, Int32 info, Int32 disklevel, BaseBitmap* icon, void* emulation)
{
	FillNodePlugin(np, info, npalloc, icon, disklevel, emulation);

	np->command_icon = icon;
	np->GetDimension = &ObjectData::GetDimension;
	np->Draw = &ObjectData::Draw;
	np->DrawShadow = &ObjectData::DrawShadow;
	np->DetectHandle = &ObjectData::DetectHandle;
	np->MoveHandle = &ObjectData::MoveHandle;
	np->Execute	= &ObjectData::Execute;
	np->AddToExecution	= &ObjectData::AddToExecution;
	np->GetModelingAxis	= &ObjectData::GetModelingAxis;
}

Bool RegisterObjectPlugin(Int32 id, const String& str, Int32 objectinfo, DataAllocator* npalloc, const String& description, BaseBitmap* icon, Int32 disklevel)
{
	if (description.Content() && !RegisterDescription(id, description))
		return false;

	OBJECTPLUGIN np;
	ClearMem(&np, sizeof(np));
	FillObjectPlugin(&np, npalloc, objectinfo, disklevel, icon, nullptr);

	np.CheckDirty	= &ObjectData::CheckDirty;

	if (objectinfo & OBJECT_MODIFIER)
		np.ModifyObject	= &ObjectData::ModifyObject;

	if (objectinfo & OBJECT_PARTICLEMODIFIER)
		np.ModifyParticles = &ObjectData::ModifyParticles;

	if (objectinfo & OBJECT_ISSPLINE)
		np.GetContour = &ObjectData::GetContour;

	if (objectinfo & OBJECT_GENERATOR)
		np.GetVirtualObjects = &ObjectData::GetVirtualObjects;

	return GeRegisterPlugin(PLUGINTYPE_OBJECT, id, str, &np, sizeof(np));
}
