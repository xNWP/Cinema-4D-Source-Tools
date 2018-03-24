/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef CUSTOMGUI_GRADIENT_H__
#define CUSTOMGUI_GRADIENT_H__

#include "c4d_library.h"
#include "c4d_basecontainer.h"
#include "c4d_gui.h"
#include "c4d_customdatatype.h"
#include "customgui_base.h"

/// Gradient custom GUI ID.
#define CUSTOMGUI_GRADIENT			1000480

/// Gradient custom data ID.
#define CUSTOMDATATYPE_GRADIENT 1000481

/// Plugin ID for the Gradient GUI preset type.\n
/// Can be used to filter a list of presets for the Content Browser.
#define ID_GRADIENTGUI_BROWSERPRESET	1027759

/// @markPrivate
#define ID_GRADIENTGUI_POPUPDIALOG		1027760

/// @addtogroup GRADIENTPROPERTY_CUSTOMGUISETTINGS
/// @ingroup CUSTOMGUISETTINGS
/// @{
///< These 2 options are allowed from ::DTYPE_COLOR:\n
///< - ::DR_COLORFIELD_ICC_BASEDOC: Use ICC profile of the current document.
///< - ::DR_COLORFIELD_ICC_BPTEX: Use ICC profile of the current @em BodyPain3D texture.
#define GRADIENTPROPERTY_COLOR				'colr'			///< ::Bool Show color controls.
#define GRADIENTPROPERTY_ALPHA				'alph'			///< ::Bool Show alpha controls.
#define GRADIENTPROPERTY_NOEDITCOLOR	'nedc'			///< ::Bool No color editing.
#define GRADIENTPROPERTY_NOPRESETS		'nopr'			///< ::Bool No load/save preset buttons.
																									///< @note The property is used like this in a @em res file:
																									/// @code
																									/// GRADIENT MYGRADIENT { NOPRESETS; }
																									/// @endcode
/// @}

/// @addtogroup GRADIENT_INTERPOLATION
/// @ingroup group_enumeration
/// @{
/// Gradient interpolation types.
enum
{
	GRADIENT_INTERPOLATION_CUBICKNOT						= 0,			///< Cubic knot.
	GRADIENT_INTERPOLATION_CUBICBIAS						= 1,			///< Cubic bias.
	GRADIENT_INTERPOLATION_SMOOTHKNOT						= 2,			///< Smooth knot.
	GRADIENT_INTERPOLATION_LINEARKNOT						= 3,			///< Linear knot.
	GRADIENT_INTERPOLATION_LINEAR								= 4,			///< Linear.
	GRADIENT_INTERPOLATION_NONE									= 5,			///< None.
	GRADIENT_INTERPOLATION_EXP_UP								= 6,			///< Exponential up.
	GRADIENT_INTERPOLATION_EXP_DOWN							= 7				///< Exponential down.
};
/// @}

/// @addtogroup GRADIENTMODE
/// @ingroup group_enumeration
/// @{
#define GRADIENTMODE_COLOR					0			///< Color only.
#define GRADIENTMODE_ALPHA					1			///< Alpha only.
#define GRADIENTMODE_COLORALPHA			2			///< Color and alpha.
/// @}

/// @addtogroup GRADIENT_CONTAINERIDS
/// @ingroup group_containerid
/// @{
#define GRADIENT_INTERPOLATION	1000			///< ::Int32 Interpolation: @enumerateEnum{GRADIENT_INTERPOLATION}
#define GRADIENT_KNOT						1001			///< BaseContainer Holds the gradient knots as sub-containers: @enumerateEnum{GRADIENTKNOT_CONTAINERIDS}
#define GRADIENT_MODE						1002			///< ::Int32 Gradient mode: @enumerateEnum{GRADIENTMODE}
#define GRADIENT_UNCLAMPED			1003			///< ::Bool Unclamped.
/// @}

/// @addtogroup GRADIENTKNOT_CONTAINERIDS
/// @ingroup group_containerid
/// @{
#define GRADIENTKNOT_COLOR			1000			///< ::Vector Color.
#define GRADIENTKNOT_BRIGHTNESS	1001			///< ::Float Brightness.
#define GRADIENTKNOT_POSITION		1002			///< ::Float Position.
#define GRADIENTKNOT_BIAS				1003			///< ::Float Bias.
#define GRADIENTKNOT_ID					1004			///< ::Int32 Index.
/// @}

//-------------------------------------------------------------------------------------------------
/// Represents a knot in a @link Gradient gradient@endlink.
//-------------------------------------------------------------------------------------------------
struct GradientKnot
{
	//-------------------------------------------------------------------------------------------------
	/// Default constructor.
	//-------------------------------------------------------------------------------------------------
	GradientKnot() { col = Vector(1.0); brightness = 1.0; pos = 0.0; bias = 0.5; index = 0; }

	Vector	col;						///< Color.
	Float		brightness;			///< Brightness.
	Float		pos;						///< Position.
	Float		bias;						///< Bias.
	Int32		index;					///< Index.
};

//-------------------------------------------------------------------------------------------------
/// Gradient data type (@ref CUSTOMDATATYPE_GRADIENT) for GradientCustomGui.
/// @addAllocFreeAutoAllocNote
//-------------------------------------------------------------------------------------------------
class Gradient : public CustomDataType
{
private:
		Gradient();
		~Gradient();

public:
	/// @name Alloc/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// @allocatesA{gradient data}
	/// @return												@allocReturn{gradient data}
	//----------------------------------------------------------------------------------------
	static Gradient *Alloc();

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{gradient data}
	/// @param[in,out] grad						@theToDestruct{gradient data}
	//----------------------------------------------------------------------------------------
	static void Free(Gradient *&grad);

	/// @}

	/// @name Knots
	/// @{

	//----------------------------------------------------------------------------------------
	/// Inverts the knots.
	/// @return												@trueIfOtherwiseFalse{the knots were successfully inverted}
	//----------------------------------------------------------------------------------------
	Bool InvertKnots(void);

	//----------------------------------------------------------------------------------------
	/// Doubles the knots.
	/// @return												@trueIfOtherwiseFalse{the knots were successfully doubled}
	//----------------------------------------------------------------------------------------
	Bool DoubleKnots(void);

	//-------------------------------------------------------------------------------------------------
	/// Flushes all the knots.
	//-------------------------------------------------------------------------------------------------
	void FlushKnots(void);

	/// @}

	/// @name Render
	/// @{

	//----------------------------------------------------------------------------------------
	/// Initializes the gradient data for render.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool InitRender(const InitRenderStruct &irs);

	//-------------------------------------------------------------------------------------------------
	/// Frees the gradient data from render.
	//-------------------------------------------------------------------------------------------------
	void FreeRender(void);

	//----------------------------------------------------------------------------------------
	/// Calculates a gradient pixel.
	/// @param[in] pos								The X position.
	/// @return												The calculated gradient pixel.
	//----------------------------------------------------------------------------------------
	Vector CalcGradientPixel(Float pos);

	//----------------------------------------------------------------------------------------
	/// Gets a pointer to the knot at @formatParam{index} between InitRender() and FreeRender().
	/// @param[in] index							The knot index. @em 0 <= @formatParam{index} < GetRenderKnotCount()
	/// @return												The render knot at @formatParam{index}. @theOwnsPointed{gradient data,knot}
	//----------------------------------------------------------------------------------------
	GradientKnot *GetRenderKnot(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Gets the number of knots for GetRenderKnot().
	/// @return												The render knot count.
	//----------------------------------------------------------------------------------------
	Int32 GetRenderKnotCount(void);

	/// @}

	/// @name Knot
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the number of knots.
	/// @return												The knot count.
	//----------------------------------------------------------------------------------------
	Int32 GetKnotCount(void) const;

	//----------------------------------------------------------------------------------------
	/// Inserts a knot.
	/// @param[in] knot								The knot to insert.
	/// @return												The index of the inserted knot: GetKnotCount() - @em 1
	//----------------------------------------------------------------------------------------
	Int32 InsertKnot(const GradientKnot &knot);

	//----------------------------------------------------------------------------------------
	/// Removes a knot.
	/// @param[in] index							The knot index. @em 0 <= @formatParam{index} < GetKnotCount()
	/// @return												@trueIfOtherwiseFalse{the knot was successfully removed}
	//----------------------------------------------------------------------------------------
	Bool RemoveKnot(Int32 index);

	//----------------------------------------------------------------------------------------
	/// Gets the knot at @formatParam{index}.
	/// @param[in] index							The knot index. @em 0 <= @formatParam{index} < GetKnotCount()
	/// @return												The knot.
	//----------------------------------------------------------------------------------------
	GradientKnot GetKnot(Int32 index) const;

	//----------------------------------------------------------------------------------------
	/// Sets knot at @formatParam{index}.
	/// @param[in] index							The knot index. @em 0 <= @formatParam{index} < GetKnotCount()
	/// @param[in] k									The knot.
	//----------------------------------------------------------------------------------------
	void SetKnot(Int32 index, const GradientKnot &k);

	/// @}

	/// @name Data
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets data from the gradient container.
	/// @param[in] id									The gradient data ID: @enumerateEnum{GRADIENT_CONTAINERIDS}
	/// @return												The data.
	//----------------------------------------------------------------------------------------
	GeData GetData(Int32 id) const;

	//----------------------------------------------------------------------------------------
	/// Sets data in the gradient container.
	/// @param[in] id									The gradient data ID: @enumerateEnum{GRADIENT_CONTAINERIDS}
	/// @param[in] data								The data.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetData(Int32 id, const GeData &data);

	/// @}

	/// @name Alpha
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the alpha gradient.
	/// @return												The alpha gradient. @theOwnsPointed{gradient data,alpha gradient}
	//----------------------------------------------------------------------------------------
	Gradient* GetAlphaGradient(void);

	//----------------------------------------------------------------------------------------
	/// Allocates an alpha gradient.
	/// @return												The allocated alpha gradient, or @formatConstant{nullptr} if the allocation failed. @theOwnsPointed{gradient data,alpha gradient}
	//----------------------------------------------------------------------------------------
	Gradient* AllocAlphaGradient(void);

	//----------------------------------------------------------------------------------------
	/// Converts this gradient to an alpha gradient.
	//----------------------------------------------------------------------------------------
	void ConvertToAlphaGradient();

	//----------------------------------------------------------------------------------------
	/// Converts a gradient within a container into an alpha gradient.
	/// @param[in] bc									The container holding the gradient. @callerOwnsPointed{container}
	/// @param[in] id									The ID of the gradient within the container.
	//----------------------------------------------------------------------------------------
	static void ConvertToAlphaGradient(BaseContainer* bc, Int32 id);

	/// @}

	/// @name Miscellaneous
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets a checksum of the whole gradient state, including the needles, colors and interpolation type.
	/// @return												The checksum.
	//----------------------------------------------------------------------------------------
	UInt32 GetChecksum() const;

	/// @}
};

//----------------------------------------------------------------------------------------
/// Gradient GUI (@ref CUSTOMGUI_GRADIENT) for the Gradient data type.
/// Here are the settings: @enumerateEnum{GRADIENTPROPERTY_CUSTOMGUISETTINGS}
//----------------------------------------------------------------------------------------
class GradientCustomGui : public BaseCustomGui<CUSTOMGUI_GRADIENT>
{
private:
	GradientCustomGui();
	~GradientCustomGui();

public:

	/// @name Gradient Data
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the gradient data.
	/// @return												The gradient data.
	//----------------------------------------------------------------------------------------
	Gradient *GetGradient();

	//----------------------------------------------------------------------------------------
	/// Sets the gradient data.
	/// @warning Unlike SetData() it sends a parent GUI message, causing parent GUI elements (e.g. a shader or dialog that contains the gradient custom GUI) to update automatically.
	/// @note	It is recommended to call SetData() instead, because SetGradient() just sets @formatParam{grad} instance and if there is an alpha gradient, it will be destroyed.\n
	///				With SetData() it needs some more lines of code but alpha gradients will be preserved.
	/// @param[in] grad								The gradient data to set. @callerOwnsPointed{gradient data}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool SetGradient(Gradient *grad);

	/// @}

	/// @name Active Knot/Bias
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the active knot or bias control index.
	/// @param[in] bias								Assigned @formatConstant{true} if the returned index is for a bias control, otherwise it is for a knot.
	/// @return												The active knot index.
	//----------------------------------------------------------------------------------------
	Int32 GetActiveKnot(Bool &bias);

	//----------------------------------------------------------------------------------------
	/// Sets the active knot or bias control.
	/// @param[in] index							The knot or bias index to set.
	/// @param[in] bias								Pass @formatConstant{true} to set a bias, otherwise a knot.
	//----------------------------------------------------------------------------------------
	void SetActiveKnot(Int32 index, Bool bias);

	/// @}
};

/// @cond IGNORE

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#ifndef _INTERNAL_DEF_
	class iGradientCustomGui
	{
	};
	class iGradient
	{
	};
#else
	class iGradientCustomGui;
	class iGradient;
#endif

struct CustomGuiGradientLib : public BaseCustomGuiLib
{
	Bool							(iGradient::*InvertKnots)(void);
	Bool							(iGradient::*DoubleKnots)(void);
	void							(iGradient::*FlushKnots)(void);

	Bool							(iGradient::*InitRender)(const InitRenderStruct &irs);
	void							(iGradient::*FreeRender)(void);
	Vector						(iGradient::*CalcGradientPixel)(Float pos) const;

	Int32							(iGradient::*GetKnotCount)(void) const;

	Int32							(iGradient::*InsertKnot)(const GradientKnot &knot);
	Bool							(iGradient::*RemoveKnot)(Int32 index);

	GradientKnot			(iGradient::*GetKnot)(Int32 index) const;
	void							(iGradient::*SetKnot)(Int32 index, const GradientKnot &k);

	GeData						(iGradient::*iGetData)(Int32 id) const;
	Bool							(iGradient::*iSetData)(Int32 id, const GeData &data);

	GradientKnot*			(iGradient::*GetRenderKnot)(Int32 index);
	Int32							(iGradient::*GetRenderKnotCount)(void);

	Gradient*					(iGradient::*GetAlphaGradient)(void);

	Gradient*					(*AllocGradient)(void);
	void							(*FreeGradient)(Gradient *grad);

	Gradient*					(iGradientCustomGui::*GetGradient)();

	Int32							(iGradientCustomGui::*GetActiveKnot)(Bool &bias);
	void							(iGradientCustomGui::*SetActiveKnot)(Int32 index, Bool bias);
	UInt32						(iGradient::*GetChecksum)() const;

	Gradient*					(iGradient::*AllocAlphaGradient)(void);
	void							(iGradient::*ConvertToAlphaGradient)();

	Bool							(iGradientCustomGui::*SetGradient)(Gradient *grad);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

/// @endcond

#endif // CUSTOMGUI_GRADIENT_H__
