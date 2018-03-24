#include "customgui_gradient.h"
#include "c4d_gui.h"

static CustomGuiGradientLib *lib_gradient = nullptr;

static CustomGuiGradientLib *CheckLib(Int32 offset)
{
	return (CustomGuiGradientLib*)CheckLib(CUSTOMGUI_GRADIENT, offset, (C4DLibrary**)&lib_gradient);
}

#define GradientCall(b) 			CustomGuiGradientLib *lib = CheckLib(LIBOFFSET(CustomGuiGradientLib, b)); \
															if (!lib || !lib->b) return; \
															(((iGradient*)this)->*lib->b)

#define GradientCallR(a, b) 		CustomGuiGradientLib *lib = CheckLib(LIBOFFSET(CustomGuiGradientLib, b)); \
															if (!lib || !lib->b) return a; \
															return (((iGradient*)this)->*lib->b)

#define GradientGuiCall(b) 		CustomGuiGradientLib *lib = CheckLib(LIBOFFSET(CustomGuiGradientLib, b)); \
															if (!lib || !lib->b) return; \
															(((iGradientCustomGui*)this)->*lib->b)

#define GradientGuiCallR(a, b) CustomGuiGradientLib *lib = CheckLib(LIBOFFSET(CustomGuiGradientLib, b)); \
															if (!lib || !lib->b) return a; \
															return (((iGradientCustomGui*)this)->*lib->b)

Bool Gradient::InvertKnots(void)
{
	GradientCallR(false, InvertKnots)();
}

Bool Gradient::DoubleKnots(void)
{
	GradientCallR(false, DoubleKnots)();
}

void Gradient::FlushKnots(void)
{
	GradientCall(FlushKnots)();
}

Bool Gradient::InitRender(const InitRenderStruct &irs)
{
	GradientCallR(false, InitRender)(irs);
}

void Gradient::FreeRender(void)
{
	GradientCall(FreeRender)();
}

Vector Gradient::CalcGradientPixel(Float pos)
{
	GradientCallR(Vector(0.0), CalcGradientPixel)(pos);
}

Int32 Gradient::GetKnotCount(void) const
{
	GradientCallR(0, GetKnotCount)();
}

Int32 Gradient::GetRenderKnotCount(void)
{
	GradientCallR(0, GetRenderKnotCount)();
}

Int32 Gradient::InsertKnot(const GradientKnot &knot)
{
	GradientCallR(NOTOK, InsertKnot)(knot);
}

Bool Gradient::RemoveKnot(Int32 index)
{
	GradientCallR(false, RemoveKnot)(index);
}

GradientKnot *Gradient::GetRenderKnot(Int32 index)
{
	GradientCallR(nullptr, GetRenderKnot)(index);
}

GradientKnot Gradient::GetKnot(Int32 index) const
{
	GradientCallR(GradientKnot(), GetKnot)(index);
}

void Gradient::SetKnot(Int32 index, const GradientKnot &k)
{
	GradientCall(SetKnot)(index, k);
}

GeData Gradient::GetData(Int32 id) const
{
	GradientCallR(GeData(), iGetData)(id);
}

Bool Gradient::SetData(Int32 id, const GeData &data)
{
	GradientCallR(false, iSetData)(id, data);
}

Gradient* Gradient::GetAlphaGradient(void)
{
	GradientCallR(nullptr, GetAlphaGradient)();
}

Gradient* Gradient::AllocAlphaGradient(void)
{
	GradientCallR(nullptr, AllocAlphaGradient)();
}

Gradient *Gradient::Alloc()
{
	CustomGuiGradientLib *lib = CheckLib(LIBOFFSET(CustomGuiGradientLib, AllocGradient));
	if (!lib || !lib->AllocGradient) return nullptr;
	return lib->AllocGradient();
}

void Gradient::Free(Gradient *&grad)
{
	CustomGuiGradientLib *lib = CheckLib(LIBOFFSET(CustomGuiGradientLib, FreeGradient));
	if (lib && lib->FreeGradient) lib->FreeGradient(grad);
	grad = nullptr;
}

UInt32 Gradient::GetChecksum() const
{
	GradientCallR(0, GetChecksum)();
}

void Gradient::ConvertToAlphaGradient()
{
	GradientCall(ConvertToAlphaGradient)();
}

void Gradient::ConvertToAlphaGradient(BaseContainer* bc, Int32 id)
{
	Gradient* pGradient = (Gradient*)bc->GetCustomDataType(id, CUSTOMDATATYPE_GRADIENT);
	if (pGradient)
		pGradient->ConvertToAlphaGradient();
}

Gradient* GradientCustomGui::GetGradient()
{
	GradientGuiCallR(nullptr, GetGradient)();
}

Bool GradientCustomGui::SetGradient(Gradient *grad)
{
	GradientGuiCallR(false, SetGradient)(grad);
}

Int32 GradientCustomGui::GetActiveKnot(Bool &bias)
{
	GradientGuiCallR(NOTOK, GetActiveKnot)(bias);
}

void GradientCustomGui::SetActiveKnot(Int32 index, Bool bias)
{
	GradientGuiCall(SetActiveKnot)(index, bias);
}
