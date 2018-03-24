/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_FALLOFFDATA_H__
#define C4D_FALLOFFDATA_H__

#ifdef __API_INTERN__
abc def xyz
#endif

#include "ge_math.h"
#include "ofalloff_standard.h"
#include "c4d_basedata.h"
#include "c4d_basecontainer.h"

class HandleInfo;
class C4D_Falloff;

/// @addtogroup FALLOFFCOLORS
/// @ingroup group_enumeration
/// @{
#define FALLOFFCAGE			Vector(1.0f, 1.0f, 0.0f)			///< Default falloff cage color.
#define FALLOFFFALLOFF	Vector(0.7f, 0.1f, 0.0f)			///< Default falloff color.
/// @}

/// @addtogroup ID_C4DFALLOFF
/// @ingroup group_enumeration
/// @{
#define ID_C4DFALLDATALIB	1019551			///< Falloff data library ID.
#define ID_C4DFALLOFFLIB	1019541			///< Falloff library ID.
/// @}

/// @addtogroup ID_C4DFALLOFF
/// @ingroup group_enumeration
/// @{
#define MSG_COLLECTC4DFALLOFF	440000221			///< Message sent to a BaseList that might contain a C4DFalloff, BaseList should fill out the passed FalloffCollectMessage @markPrivate

/// Structure sent to BaseList2D with the message MSG_COLLECTC4DFALLOFF. @markPrivate
struct FalloffCollectMessage
{
	C4D_Falloff* _falloff;				///< Falloff to be filled by the object owning the C4D_Falloff on MSG_COLLECTC4DFALLOFF
};
/// @}

//----------------------------------------------------------------------------------------
/// Holds the data for FalloffData plugins.\n
/// Structure is read-only. The only exception is @link FalloffDataData::_userData _userData@endlink, which can be set to whatever.\n
/// @link FalloffDataData::_userData _userData@endlink must be checked before it is accessed as it can be reset to @formatConstant{nullptr}.\n
/// It is not normally reset to @formatConstant{nullptr} in-between switches to a different falloff, so it should be cleared in FalloffData::FreeFalloff if it has been set before.\n
/// @note @link FalloffDataData::_userData _userData@endlink is usually filled and used for speed within FalloffData::Sample.
//----------------------------------------------------------------------------------------
struct FalloffDataData
{
public:
	//----------------------------------------------------------------------------------------
	/// Default constructor.
	//----------------------------------------------------------------------------------------
	FalloffDataData()
	{
		_mat = Matrix();
		_imat = ~_mat;
		_falloff = _scale = _strength = 1.0;
		_size = Vector(1.0);
		_invert = _clamped = _useSpline = false;
		_visible = true;

		_axis = 0;
		_slice = _torusRadius = _radius = _inverseRadius = _inverseFalloff = 1.0;
		_function = FALLOFF_FUNCTION_SPLINE;
		_spherical = false;

		_userData = nullptr;
	}

	//----------------------------------------------------------------------------------------
	/// Default destructor.
	//----------------------------------------------------------------------------------------
	~FalloffDataData(void) { }

	//----------------------------------------------------------------------------------------
	/// Equality operator. Checks if two FalloffDataDatas are identical.
	/// @param[in] b									The FalloffDataData to compare with.
	/// @return												@trueIfOtherwiseFalse{the FalloffDataDatas are equal}
	//----------------------------------------------------------------------------------------
	Bool operator ==(const FalloffDataData& b)
	{
		return _mat == b._mat && _imat == b._imat && _falloff == b._falloff && _scale == b._scale && _strength == b._strength
					 && _size == b._size && _invert == b._invert && _clamped == b._clamped && _visible == b._visible && _useSpline == b._useSpline
					 && _nodemat == b._nodemat && _inverseNodeMat == b._inverseNodeMat && _offset == b._offset && _axis == b._axis && _slice == b._slice
					 && _torusRadius == b._torusRadius && _function == b._function && _spherical == b._spherical && _radius == b._radius
					 && _inverseRadius == b._inverseRadius && _inverseFalloff == b._inverseFalloff && _userData == b._userData;
	}

	//----------------------------------------------------------------------------------------
	/// Inequality operator. Checks if two FalloffDataDatas are different.
	/// @param[in] b									The FalloffDataData to compare with.
	/// @return												@trueIfOtherwiseFalse{the FalloffDataDatas are not equal}
	//----------------------------------------------------------------------------------------
	Bool operator !=(const FalloffDataData& b)
	{
		return !(*this == b);
	}

	Matrix	_mat,									///< Falloff matrix.
					_imat;								///< Inverse falloff matrix.
	Float		_falloff,							///< Falloff.
					_scale,								///< Scale.
					_strength;						///< Strength.
	Vector	_size;								///< Size.
	Bool		_invert,							///< Invert.
					_clamped,							///< Clamped.
					_visible,							///< Visible.
					_useSpline;						///< Use spline.
	Matrix	_nodemat,							///< The node's matrix.
					_inverseNodeMat;			///< The node's inverse matrix.
	Vector	_offset;							///< Offset.
	Int32		_axis;								///< Axis orientation: @enumerateEnum{FALLOFF_SHAPE_AXIS}
	Float		_slice;								///< Slice @em 0-@em 360&deg;.
	Float		_torusRadius;					///< Torus radius.
	Int32		_function;						///< Falloff function: @enumerateEnum{FALLOFF_FUNCTION}
	Bool		_spherical;						///< @markDeprecated
	Float		_radius,							///< @markDeprecated
					_inverseRadius;				///< @markDeprecated
	Float		_inverseFalloff;			///< Inverse falloff.
	void*		_userData;						///< %User data.
};

//----------------------------------------------------------------------------------------
/// A data class for creating falloff plugins.\n
/// Falloffs appear in any falloff description (unless the flag @ref PLUGINFLAG_HIDE is set during registration) and extend the functionality of effectors and anything that uses falloffs.\n
/// Use RegisterFalloffPlugin() to register a falloff plugin.
//----------------------------------------------------------------------------------------
class FalloffData : public BaseData
{
public:
	/// @name Init/Sample/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// Called to initialize the falloff when it is first created.
	/// @param[in,out] falldata				The falloff's data.
	/// @param[in,out] bc							The falloff's container; normally this is the owning object's container.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	virtual Bool Init(FalloffDataData& falldata, BaseContainer* bc);

	//----------------------------------------------------------------------------------------
	/// Called to initialize the falloff just before sampling. Allows to setup any necessary data in falldata or bc.
	/// @param[in,out] bc							The falloff's data.
	/// @param[in,out] falldata				The falloff's container; normally this is the container of the object owning the falloff.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	virtual Bool InitFalloff(BaseContainer* bc, FalloffDataData& falldata);

	//----------------------------------------------------------------------------------------
	/// Called to sample any point. Assign res to return the sampled value.
	/// @param[in] p									The position of the point to sample in falloff space.
	/// @param[in] data								The falloff's data.
	/// @param[out] res								Set to the sampled value.
	//----------------------------------------------------------------------------------------
	virtual void Sample(const Vector& p, const FalloffDataData& data, Float* res);

	//----------------------------------------------------------------------------------------
	/// Called to free the falloff.
	/// @param[in] falldata						The falloff's data.
	//----------------------------------------------------------------------------------------
	virtual void FreeFalloff(FalloffDataData& falldata);

	/// @}

	//----------------------------------------------------------------------------------------
	/// Called to check for a change in the falloff.
	/// @param[in] bc									The falloff's container; normally this is the container of the object owning the falloff.
	/// @return												@trueIfOtherwiseFalse{the falloff is dirty}
	//----------------------------------------------------------------------------------------
	virtual Bool CheckDirty(BaseContainer* bc);

	//----------------------------------------------------------------------------------------
	/// Called to change the visibility of any element in the falloff description.
	/// Just return @formatConstant{true} or @formatConstant{false} for the @formatParam{id} (like NodeData::GetDEnabling).
	/// @param[in] id									The description ID.
	/// @param[in,out] bc							The falloff's container; normally this is the container of the object owning the falloff.
	/// @param[in,out] desc_bc				The description element's container.
	/// @return												@trueIfOtherwiseFalse{the description element should be visible}
	//----------------------------------------------------------------------------------------
	virtual Bool GetDVisible(DescID& id, BaseContainer* bc, BaseContainer* desc_bc);

	/// @name Handle
	/// @{

	//----------------------------------------------------------------------------------------
	/// Called to get the number of handles for the falloff.\n
	/// Same as ObjectData::GetHandleCount with additional FalloffDataData.
	/// @param[in,out] bc							The falloff's container; normally this is the container of the object owning the falloff.
	/// @param[in,out] data						The falloff's data.
	/// @return												The handle count.
	//----------------------------------------------------------------------------------------
	virtual Int32 GetHandleCount(BaseContainer* bc, const FalloffDataData& data);

	//----------------------------------------------------------------------------------------
	/// Called to get a handle for the falloff.\n
	/// Same as ObjectData::GetHandle with additional FalloffDataData.
	/// @param[in,out] bc							The falloff's container; normally this is the container of the object owning the falloff.
	/// @param[in] i									The handle index.
	/// @param[out] info							Filled with the information for handle @formatParam{i}.
	/// @param[in,out] data						The falloff's data.
	//----------------------------------------------------------------------------------------
	virtual void GetHandle(BaseContainer* bc, Int32 i, HandleInfo& info, const FalloffDataData& data);

	//----------------------------------------------------------------------------------------
	/// Called to set a handle for the falloff.\n
	/// Same as ObjectData::SetHandle with additional FalloffDataData.\n
	/// Called when the user has moved handle @formatParam{i} to position @formatParam{p}. Constrain the movement and update the internal data.
	/// @param[in,out] bc							The falloff's container; normally this is the container of the object owning the falloff.
	/// @param[in] i									The handle index.
	/// @param[in] p									The new position for handle @formatParam{i}.
	/// @param[in,out] data						The falloff's data.
	//----------------------------------------------------------------------------------------
	virtual void SetHandle(BaseContainer* bc, Int32 i, Vector p, const FalloffDataData& data);

	/// @}

	//----------------------------------------------------------------------------------------
	/// Called to draw the falloff in the viewport.\n
	/// Same as ObjectData::Draw with additional FalloffDataData.\n
	/// These predefined color constants should be used: @enumerateEnum{FALLOFFCOLORS}
	/// @param[in,out] data						The falloff's data.
	/// @param[in] drawpass						The draw pass: @enumerateEnum{DRAWPASS}
	/// @param[in] bd									The editor's view. @callerOwnsPointed{base draw}
	/// @param[in] bh									The editor's view help. @callerOwnsPointed{base draw help}
	/// @return												The result of drawing into the editor view: @enumerateEnum{DRAWRESULT}
	//----------------------------------------------------------------------------------------
	virtual DRAWRESULT Draw(const FalloffDataData& data, DRAWPASS drawpass, BaseDraw* bd, BaseDrawHelp* bh);

	//----------------------------------------------------------------------------------------
	/// Called to process messages sent to the falloff.
	/// @param[in] type								The message type: @enumerateEnum{MSG}
	/// @param[in,out] bc							The falloff's container; normally this is the container of the object owning the falloff.
	/// @param[in,out] m_data					The message data. @senderOwnsPointed{data}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	virtual Bool Message(Int32 type, BaseContainer* bc, void* m_data);
};

//----------------------------------------------------------------------------------------
/// Represents a falloff. Allows to sample falloffs.\n
/// It is very simple in use: allocate it, call InitFalloff() first then Sample() giving it a point in world space.
///
/// Many of the methods are there for use within @ref NodeData/@ref ObjectData/@ref ToolData plugins and should be called within their likewise counterparts.\n
/// For instance @link C4D_Falloff::Draw Draw@endlink should be called from within the corresponding @ref NodeData/@ref ObjectData/@ref ToolData Draw override, then the falloff will be drawn in the viewport.
///
/// C4D_Falloff normally needs a container, this is usually the object's container, from this it gets and sets its own parameters for the description (though they can be set directly using the helper functions).
///
/// @note To add a falloff to a description use @link C4D_Falloff::AddFalloffToDescription AddFalloffToDescription@endlink.
//----------------------------------------------------------------------------------------
class C4D_Falloff
{
private:
	C4D_Falloff() { }
	~C4D_Falloff(void) { }

public:
	/// @name Alloc/Free
	/// @{

	//----------------------------------------------------------------------------------------
	/// @allocatesA{falloff}
	/// @return												@allocReturn{falloff}
	//----------------------------------------------------------------------------------------
	static C4D_Falloff* Alloc(void);

	//----------------------------------------------------------------------------------------
	/// @destructsAlloc{falloffs}
	/// @param[in,out] node						@theToDestruct{falloff}
	//----------------------------------------------------------------------------------------
	static void Free(C4D_Falloff*& node);

	/// @}

	//----------------------------------------------------------------------------------------
	/// Gets the last container the falloff should try to use.\n
	/// @note If the falloff has not been given a container at any point it will generate one internally.
	/// @warning Can be @formatConstant{nullptr}. If the falloff has been initialized at some point with a container, but subsequently the original container is no longer available this could be a bad pointer.
	/// @return												The container instance.
	//----------------------------------------------------------------------------------------
	BaseContainer* GetContainerInstance(void);

	/// @name Dirty
	/// @{

	//----------------------------------------------------------------------------------------
	/// Sets the falloff dirty.
	//----------------------------------------------------------------------------------------
	void SetDirty(void);

	//----------------------------------------------------------------------------------------
	/// Gets the falloff dirty value.
	/// @note Useful for checking if the falloff needs to be resampled.
	/// @param[in] bc									Optionally pass the container of the object owning the falloff (recommended).
	/// @return												The dirty value.
	//----------------------------------------------------------------------------------------
	Int32 GetDirty(BaseContainer* bc = nullptr);

	/// @}

	/// @name Matrix
	/// @{

	//----------------------------------------------------------------------------------------
	/// Sets the falloff's matrix.
	/// @param[in] mg									The new matrix.
	//----------------------------------------------------------------------------------------
	void SetMg(Matrix mg);

	//----------------------------------------------------------------------------------------
	/// Gets the falloff's matrix.
	/// @return												The matrix.
	//----------------------------------------------------------------------------------------
	Matrix GetMg(void);

	/// @}

	/// @name Data
	/// @{
	//----------------------------------------------------------------------------------------
	/// Sets the falloff's data directly.
	/// @param[in] falldata						The new falloff's data.
	//----------------------------------------------------------------------------------------
	void SetData(FalloffDataData falldata);

	//----------------------------------------------------------------------------------------
	/// Gets the falloff's data.
	/// @return												The falloff's data.
	//----------------------------------------------------------------------------------------
	FalloffDataData GetData(void);

	/// @}

	/// @name Mode
	/// @{

	//----------------------------------------------------------------------------------------
	/// Sets the falloff mode.\n
	/// @note The falloff mode is normally the falloff's ID (see @em ofalloff_panel.h).
	/// @param[in] type								The new falloff mode.
	/// @param[in] bc									Optionally pass the container of the object owning the falloff (recommended).
	/// @return												@trueIfOtherwiseFalse{the mode was set}
	//----------------------------------------------------------------------------------------
	Bool SetMode(Int32 type, BaseContainer* bc = nullptr);

	//----------------------------------------------------------------------------------------
	/// Gets the falloff mode.\n
	/// @note The fallof's mode is normally the falloff's ID (see @em ofalloff_panel.h).
	/// @return												The falloff's mode.
	//----------------------------------------------------------------------------------------
	Int32 GetMode(void);

	/// @}

	//----------------------------------------------------------------------------------------
	/// Sets the current falloff time.\n
	/// Used for the animated Spline GUI offset, not for any other values currently.
	/// @param[in] time								The new falloff time.
	/// @param[in] bc									Optionally pass the container of the object owning the falloff (recommended).
	//----------------------------------------------------------------------------------------
	void SetTime(BaseTime time, BaseContainer* bc = nullptr);

	//----------------------------------------------------------------------------------------
	/// Initializes the falloff.
	/// @warning Always call before the sample routines.
	/// @note It is recommended to fill at least one of the settings, however not compulsory.
	/// @param[in] bc									Optional container of the object owning the falloff. If given the FalloffDataData will be extracted from this container.
	/// @param[in] doc								Optional document used to retrieve the current time for the animation of the Spline GUI offset.
	/// @param[in] op									Optional object used to set the matrix if given, and if no container is given for @formatParam{bc}, its container will be used instead.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool InitFalloff(BaseContainer* bc = nullptr, BaseDocument* doc = nullptr, BaseObject* op = nullptr);

	/// @name Sample
	/// @{

	//----------------------------------------------------------------------------------------
	/// Samples the falloff for any point in space.
	/// @param[in] p									The point to sample in global space.
	/// @param[out] result						Assigned the sampled value.
	/// @param[in] usespline					Use the GUI spline if it exists (default).
	/// @param[in] weight							An optional weight offset. Equivalent of adding this value to the falloff result before clamping.
	//----------------------------------------------------------------------------------------
	void Sample(const Vector& p, Float* result, Bool usespline = true, Float weight = 0.0);

	//----------------------------------------------------------------------------------------
	/// Samples the falloff for an array of points in space.
	/// @param[in] p									The array of points to sample. @callerOwnsPointed{array}
	/// @param[out] result						Assigned the sampled values.
	/// @param[in] count							The size of array @formatParam{p}.
	/// @param[in] usespline					Use the GUI spline if it exists (default).
	/// @param[in] weight							An optional weight offset. Equivalent of adding this value to the falloff result before clamping.
	//----------------------------------------------------------------------------------------
	void MultiSample(const Vector* p, Float* result, Int32 count, Bool usespline = true, Float weight = 0.0);

	/// @}

	//----------------------------------------------------------------------------------------
	/// Adds the falloff to a description.
	/// @note Use this function within the implementation of NodeData::GetDDescription.
	/// @param[in] description				The description to add the falloff GUI to.
	/// @param[in] bc									Optionally pass the container of the object owning the falloff.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool AddFalloffToDescription(Description* description, BaseContainer* bc = nullptr);

	//----------------------------------------------------------------------------------------
	/// Sends messages to the falloff.
	/// @note Use this function from within the implementation of NodeData::Message to pass all messages on to the falloff, or just send a message with it normally as needed.
	/// @param[in] id									The message type: @enumerateEnum{MSG}
	/// @param[in] bc									Optionally pass the container of the object owning the falloff.
	/// @param[in,out] m_data					The message data. @senderOwnsPointed{data}
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Message(Int32 id, BaseContainer* bc = nullptr, void* m_data = nullptr);

	/// @name Handle
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the number of handles for the falloff.
	/// @note Use this function from within the implementation of ObjectData::GetHandleCount.
	/// @param[in] bc									Optionally pass the container of the object owning the falloff (recommended). Necessary to have user controllable handles.
	/// @return												The handle count.
	//----------------------------------------------------------------------------------------
	Int32 GetHandleCount(BaseContainer* bc = nullptr);

	//----------------------------------------------------------------------------------------
	/// Gets a handle for the falloff.
	/// @note Use this function from within the implementation of ObjectData::GetHandle.
	/// @param[in] i									The handle index.
	/// @param[in] bc									The falloff's container; normally this is the owning object's container.
	/// @param[out] info							Filled with the information for handle @formatParam{i}.
	//----------------------------------------------------------------------------------------
	void GetHandle(Int32 i, BaseContainer* bc, HandleInfo& info);

	//----------------------------------------------------------------------------------------
	/// Called to set a handle for the falloff.
	/// @note Use this function from within the implementation of ObjectData::SetHandle.
	/// @param[in] i									The handle index.
	/// @param[in] p									The new position for handle @formatParam{i}.
	/// @param[in] bc									The falloff's container; normally this is the owning object's container.
	/// @param[out] info							The information for handle @formatParam{i}.
	//----------------------------------------------------------------------------------------
	void SetHandle(Int32 i, Vector p, BaseContainer* bc, const HandleInfo& info);

	/// @}

	//----------------------------------------------------------------------------------------
	/// Draws the falloff in the viewport.
	/// @note Use this function from within the implementation of ObjectData::Draw or ToolData::Draw.
	/// @param[in] bd									The editor's view. @callerOwnsPointed{base draw}
	/// @param[in] bh									The editor's view help. @callerOwnsPointed{base draw help}
	/// @param[in] drawpass						The draw pass: @enumerateEnum{DRAWPASS}
	/// @param[in] bc									Optionally pass the container of the object owning the falloff (recommended).
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Draw(BaseDraw* bd, BaseDrawHelp* bh, DRAWPASS drawpass, BaseContainer* bc = nullptr);

	//----------------------------------------------------------------------------------------
	/// Copies the falloff.
	/// @note Use this function from within the implementation of NodeData::CopyTo; necessary for handles to work correctly with the undo system in @C4D.
	/// @param[out] dest							The destination falloff.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool CopyTo(C4D_Falloff* dest);
};

struct FALLOFFPLUGIN;

/// FalloffData allocator.
typedef FalloffData* FalloffDataAllocator (void);

/// @markPrivate
void FillFalloffPlugin(FALLOFFPLUGIN* fp, Int32 info, FalloffDataAllocator* g);

//----------------------------------------------------------------------------------------
/// Registers a falloff plugin.
/// @param[in] id									@uniquePluginID
/// @param[in] str								The name of the plugin.
/// @param[in] info								The falloff plugin info flags: @enumerateEnum{PLUGINFLAG}
/// @param[in] g									The allocator for the falloff plugin. This is a pointer to a function that creates a new instance of FalloffData with NewObj().
/// @param[in] description				The name of the description resource file to use for the falloff plugin without <i>.res</i> extension, for example @em "ofalloff_falloffname".\n
/// 															The name has to be unique, i.e. @em "ofalloff_falloffname" cannot be used for 2 different descriptions. See Description Resource for more information.
/// @return												@trueIfOtherwiseFalse{the falloff plugin was registered}
//----------------------------------------------------------------------------------------
Bool RegisterFalloffPlugin(Int32 id, const String& str, Int32 info, FalloffDataAllocator* g, const String& description);

//----------------------------------------------------------------------------------------
/// Allocates a falloff.
/// @param[in] type								The falloff type.
/// @return												@allocReturn{falloff}
//----------------------------------------------------------------------------------------
void* AllocFalloff(Int32 type);

#endif // C4D_FALLOFFDATA_H__
