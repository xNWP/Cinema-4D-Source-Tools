#include "c4d_memory.h"
#include "c4d_basetag.h"
#include "c4d_basecontainer.h"

class BaseSelect;

Int32 VariableTag::GetDataCount(void)
{
	return C4DOS.Tg->GetDataCount(this);
}

Int32 VariableTag::GetDataSize(void)
{
	return C4DOS.Tg->GetDataSize(this);
}

BaseSelect* SelectionTag::GetBaseSelect(void)
{
	return C4DOS.Tg->GetBaseSelect(this);
}

Vector TextureTag::GetPos(void)
{
	return C4DOS.Tx->GetPos(this);
}

Vector TextureTag::GetScale(void)
{
	return C4DOS.Tx->GetScale(this);
}

Vector TextureTag::GetRot(void)
{
	return C4DOS.Tx->GetRot(this);
}

Matrix TextureTag::GetMl(void)
{
	return C4DOS.Tx->GetMl(this);
}

void TextureTag::SetPos(const Vector& v)
{
	C4DOS.Tx->SetPos(this, v);
}

void TextureTag::SetScale(const Vector& v)
{
	C4DOS.Tx->SetScale(this, v);
}

void TextureTag::SetRot(const Vector& v)
{
	C4DOS.Tx->SetRot(this, v);
}

void TextureTag::SetMl(const Matrix& m)
{
	C4DOS.Tx->SetMl(this, m);
}

BaseMaterial* TextureTag::GetMaterial(Bool ignoredoc)
{
	return C4DOS.Tx->GetMaterial(this, ignoredoc);
}

void TextureTag::SetMaterial(BaseMaterial* mat)
{
	C4DOS.Tx->SetMaterial(this, mat);
}

Bool StickTextureTag::Record(BaseObject* op, Bool always)
{
	return C4DOS.Tg->Record(this, op, always);
}

BaseTag* BaseTag::Alloc(Int32 type)
{
	return C4DOS.Tg->Alloc(type, 0);
}

void BaseTag::Free(BaseTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}

VariableTag* VariableTag::Alloc(Int32 type, Int32 count)
{
	return (VariableTag*)C4DOS.Tg->Alloc(type, count);
}

void VariableTag::Free(VariableTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}

SelectionTag* SelectionTag::Alloc(Int32 type)
{
	return (SelectionTag*)C4DOS.Tg->Alloc(type, 0);
}

void SelectionTag::Free(SelectionTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}

VertexMapTag* VertexMapTag::Alloc(Int32 count)
{
	return (VertexMapTag*)C4DOS.Tg->Alloc(Tvertexmap, count);
}

void VertexMapTag::Free(VertexMapTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}

NormalTag* NormalTag::Alloc(Int32 count)
{
	return (NormalTag*)C4DOS.Tg->Alloc(Tnormal, count);
}

void NormalTag::Free(NormalTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}

UVWTag* UVWTag::Alloc(Int32 count)
{
	return (UVWTag*)C4DOS.Tg->Alloc(Tuvw, count);
}

void UVWTag::Free(UVWTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}

TextureTag* TextureTag::Alloc()
{
	return (TextureTag*)C4DOS.Tg->Alloc(Ttexture, 0);
}

void TextureTag::Free(TextureTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}

StickTextureTag* StickTextureTag::Alloc(Int32 type)
{
	return (StickTextureTag*)C4DOS.Tg->Alloc(Tsticktexture, 0);
}

void StickTextureTag::Free(StickTextureTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}

void VertexColorTag::Set(VertexColorHandle dataptr, Neighbor* nb, const CPolygon* vadr, Int32 pIndex, const Vector4d32& color)
{
	if (!nb || !vadr) // per vertex mode
	{
		Vector4d32* data = static_cast<Vector4d32*>(dataptr);
		if (data)
		{
			data[pIndex].x = Clamp01(color.x);
			data[pIndex].y = Clamp01(color.y);
			data[pIndex].z = Clamp01(color.z);
			data[pIndex].w = Clamp01(color.w);
		}
		return;
	}

	Int32*	faces = nullptr;
	Int32		faceCount = 0;
	VertexColorStruct vcs;
	Vector4d32 clamepedColor = color;
	nb->GetPointPolys(pIndex, &faces, &faceCount);
	for (Int32 i = 0; i < faceCount; ++i)
	{
		VertexColorTag::Get(dataptr, faces[i], vcs);

		clamepedColor.x = Clamp01(color.x);
		clamepedColor.y = Clamp01(color.y);
		clamepedColor.z = Clamp01(color.z);
		clamepedColor.w = Clamp01(color.w);

		vcs[vadr[faces[i]].Find(pIndex)] = clamepedColor;

		VertexColorTag::Set(dataptr, faces[i], vcs);
	}
}

Vector4d32 VertexColorTag::Get(ConstVertexColorHandle dataptr, Neighbor* nb, const CPolygon* vadr, Int32 pIndex)
{
	Vector4d32 res = Vector4d32(0.0, 0.0, 0.0, 0.0);

	if (!nb || !vadr) // per vertex mode
	{
		const Vector4d32* data = static_cast<const Vector4d32*>(dataptr);
		if (data)
		{
			res = data[pIndex];
			res.x = Clamp01(res.x);
			res.y = Clamp01(res.y);
			res.z = Clamp01(res.z);
			res.w = Clamp01(res.w);
		}
		return res;
	}

	Vector4d32 temp;

	Int32*	faces = nullptr;
	Int32		faceCount = 0;
	VertexColorStruct vcs;
	nb->GetPointPolys(pIndex, &faces, &faceCount);

	if (faceCount <= 0)
		return res;

	for (Int32 i = 0; i < faceCount; ++i)
	{
		VertexColorTag::Get(dataptr, faces[i], vcs);
		temp = vcs[vadr[faces[i]].Find(pIndex)];
		res += temp;
	}

	res = res * Inverse((Float32)faceCount);

	return res;
}

void VertexColorTag::SetColor(VertexColorHandle dataptr, Neighbor* nb, const CPolygon* vadr, Int32 pIndex, const Vector32& color)
{
	if (!nb || !vadr) // per vertex mode
	{
		Vector4d32* data = static_cast<Vector4d32*>(dataptr);
		if (data)
		{
			data[pIndex].x = Clamp01(color.x);
			data[pIndex].y = Clamp01(color.y);
			data[pIndex].z = Clamp01(color.z);
		}
		return;
	}

	Int32*	faces = nullptr;
	Int32		faceCount = 0;
	Int32		index = NOTOK;
	VertexColorStruct vcs;
	nb->GetPointPolys(pIndex, &faces, &faceCount);
	for (Int32 i = 0; i < faceCount; ++i)
	{
		VertexColorTag::Get(dataptr, faces[i], vcs);
		index = vadr[faces[i]].Find(pIndex);
		vcs[index].x = Clamp01(color.x);
		vcs[index].y = Clamp01(color.y);
		vcs[index].z = Clamp01(color.z);
		VertexColorTag::Set(dataptr, faces[i], vcs);
	}
}

Vector32 VertexColorTag::GetColor(ConstVertexColorHandle dataptr, Neighbor* nb, const CPolygon* vadr, Int32 pIndex)
{
	Vector32 res;

	if (!nb || !vadr) // per vertex mode
	{
		const Vector4d32* data = static_cast<const Vector4d32*>(dataptr);
		if (data)
		{
			res.x = Clamp01(data[pIndex].x);
			res.y = Clamp01(data[pIndex].y);
			res.z = Clamp01(data[pIndex].z);
		}
		return res;
	}

	Vector4d32 temp;

	Int32*	faces = nullptr;
	Int32		faceCount = 0;
	VertexColorStruct vcs;
	nb->GetPointPolys(pIndex, &faces, &faceCount);
	for (Int32 i = 0; i < faceCount; ++i)
	{
		VertexColorTag::Get(dataptr, faces[i], vcs);
		temp = vcs[vadr[faces[i]].Find(pIndex)];
		res += Vector32(temp.x, temp.y, temp.z);
	}
	if (faceCount > 0)
		res /= Float32(faceCount);

	return res;
}

void VertexColorTag::SetAlpha(VertexColorHandle dataptr, Neighbor* nb, const CPolygon* vadr, Int32 pIndex, Float32 value)
{
	if (!nb || !vadr) // per vertex mode
	{
		Vector4d32* data = static_cast<Vector4d32*>(dataptr);
		if (data)
			data[pIndex].w = Clamp01(value);

		return;
	}

	Int32*	faces = nullptr;
	Int32		faceCount = 0;
	VertexColorStruct vcs;
	nb->GetPointPolys(pIndex, &faces, &faceCount);
	for (Int32 i = 0; i < faceCount; ++i)
	{
		VertexColorTag::Get(dataptr, faces[i], vcs);
		vcs[vadr[faces[i]].Find(pIndex)].w = Clamp01(value);
		VertexColorTag::Set(dataptr, faces[i], vcs);
	}
}

Float32 VertexColorTag::GetAlpha(ConstVertexColorHandle dataptr, Neighbor* nb, const CPolygon* vadr, Int32 pIndex)
{
	Float32 res = 0.0;

	if (!nb || !vadr) // per vertex mode
	{
		const Vector4d32* data = static_cast<const Vector4d32*>(dataptr);
		if (data)
			res = Clamp01(data[pIndex].w);
		return res;
	}

	Vector4d32 temp;

	Int32*	faces = nullptr;
	Int32		faceCount = 0;
	VertexColorStruct vcs;
	nb->GetPointPolys(pIndex, &faces, &faceCount);
	for (Int32 i = 0; i < faceCount; ++i)
	{
		VertexColorTag::Get(dataptr, faces[i], vcs);
		temp = vcs[vadr[faces[i]].Find(pIndex)];
		res += temp.w;
	}
	if (faceCount > 0)
		res /= faceCount;

	return res;
}

VertexColorTag* VertexColorTag::Alloc(Int32 count)
{
	return (VertexColorTag*)C4DOS.Tg->Alloc(Tvertexcolor, count);
}

void VertexColorTag::Free(VertexColorTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}

GvNodeMaster* XPressoTag::GetNodeMaster(void)
{
	RetrievePrivateData rp;
	rp.flags = 0;
	rp.data	 = nullptr;

	if (!Message(MSG_RETRIEVEPRIVATEDATA, &rp))
		return nullptr;
	return (GvNodeMaster*)rp.data;
}

XPressoTag* XPressoTag::Alloc()
{
	return (XPressoTag*)C4DOS.Tg->Alloc(Texpresso, 0);
}

void XPressoTag::Free(XPressoTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}


HNWeightTag* HNWeightTag::Alloc()
{
	return (HNWeightTag*)C4DOS.Tg->Alloc(Tsds, 0);
}

void HNWeightTag::Free(HNWeightTag*& bl)
{
	C4DOS.Bl->Free(bl);
	bl = nullptr;
}

Bool HNWeightTag::GetTagData(HNData* data)
{
	if (!data)
		return false;

	RetrievePrivateData rp;
	rp.flags = 0;
	rp.data	 = data;

	if (!Message(MSG_RETRIEVEPRIVATEDATA, &rp))
		return false;

	return true;
}

BaseTag* BaseTag::GetOrigin()
{
	return C4DOS.Tg->GetOrigin(this);
}

// read/write overrides
const Vector* PointTag::GetDataAddressR(void) { return (const Vector*)C4DOS.Tg->GetDataAddressR(this); }
Vector* PointTag::GetDataAddressW(void) { return (Vector*)C4DOS.Tg->GetDataAddressW(this); }

const Vector* StickTextureTag::GetDataAddressR(void) { return (const Vector*)C4DOS.Tg->GetDataAddressR(this);	}
Vector* StickTextureTag::GetDataAddressW(void) { return (Vector*)C4DOS.Tg->GetDataAddressW(this);	}

const Float32* VertexMapTag::GetDataAddressR(void) { return (const Float32*)C4DOS.Tg->GetDataAddressR(this); }
Float32* VertexMapTag::GetDataAddressW(void) { return (Float32*)C4DOS.Tg->GetDataAddressW(this); }

const Segment* SegmentTag::GetDataAddressR(void) { return (const Segment*)C4DOS.Tg->GetDataAddressR(this); }
Segment* SegmentTag::GetDataAddressW(void) { return (Segment*)C4DOS.Tg->GetDataAddressW(this); }

const Tangent* TangentTag::GetDataAddressR(void) { return (const Tangent*)C4DOS.Tg->GetDataAddressR(this); }
Tangent* TangentTag::GetDataAddressW(void) { return (Tangent*)C4DOS.Tg->GetDataAddressW(this); }

const CPolygon* PolygonTag::GetDataAddressR(void) { return (const CPolygon*)C4DOS.Tg->GetDataAddressR(this); }
CPolygon* PolygonTag::GetDataAddressW(void) { return (CPolygon*)C4DOS.Tg->GetDataAddressW(this); }

ConstUVWHandle UVWTag::GetDataAddressR(void) { return (ConstUVWHandle)C4DOS.Tg->GetDataAddressR(this); }
UVWHandle UVWTag::GetDataAddressW(void) { return (UVWHandle)C4DOS.Tg->GetDataAddressW(this); }

ConstVertexColorHandle VertexColorTag::GetDataAddressR(void) { return (ConstVertexColorHandle)C4DOS.Tg->GetDataAddressR(this); }
VertexColorHandle VertexColorTag::GetDataAddressW(void) { return (VertexColorHandle)C4DOS.Tg->GetDataAddressW(this); }

ConstNormalHandle NormalTag::GetDataAddressR(void) { return (ConstNormalHandle)C4DOS.Tg->GetDataAddressR(this);	}
NormalHandle NormalTag::GetDataAddressW(void) { return (NormalHandle)C4DOS.Tg->GetDataAddressW(this);	}

const void* VariableTag::GetLowlevelDataAddressR(void) { return C4DOS.Tg->GetDataAddressR(this); }
void* VariableTag::GetLowlevelDataAddressW(void) { return C4DOS.Tg->GetDataAddressW(this); }

Bool VertexColorTag::IsPerPointColor() { return C4DOS.Tg->IsPerPointColor(this); }

Bool VertexColorTag::SetPerPointMode(Bool perPointColor) {  return C4DOS.Tg->SetPerPointMode(this, perPointColor); }
