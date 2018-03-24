/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef OPERATINGSYSTEM_H__
#define OPERATINGSYSTEM_H__

#include "ge_math.h"
#include "ge_prepass.h"
#include "c4d_basetime.h"
#include "vector4.h"
#include "matrix4.h"
#include "description/ddoc.h"

#include "c4d_misc.h"
#ifdef USE_API_MAXON
	#include "maxon/basearray.h"
#endif

/// @C4D API version.
#define API_VERSION	18000

class C4DAtom;
class C4DAtomGoal;
class AtomArray;
class NodeData;
class GeListNode;
class GeListHead;
class GeMarker;
class AliasTrans;
class Registry;
class CDialog;
class CUserArea;
class _GeListView;
class _SimpleListView;
class BaseTag;
class MPBaseThread;
class Semaphore;
class VariableTag;
class BaseTime;
class BaseChannel;
class C4DUuid;
class BaseContainer;
class BaseDocument;
class BaseSelect;
class HyperFile;
class MemoryFileStruct;
class BaseList2D;
class BaseObject;
class SplineObject;
class GeSignal;
class BaseShader;
class PointObject;
class PolygonObject;
class LineObject;
class MultipassObject;
class BaseDraw;
class BaseDrawHelp;
class BaseView;
class BaseLink;
class String;
class BaseBitmap;
class DeprecatedMemoryPool;
class BaseMaterial;
class Material;
class BaseMaterial;
class BaseVideoPost;
class RenderData;
class LocalFileTime;
class Render;
class TextureTag;
class MovieSaver;
class ZeroConfBrowser;
class ZeroConfService;
class NetworkIpConnection;
class NetworkInterface;
class NetworkIpAddrPort;
class BrowseFiles;
class BrowseVolumes;
class Parser;
class BaseFile;
class AESFile;
class SelectionTag;
class BaseTag;
class LassoSelection;
class UVWTag;
class ObjectSafety;
class BaseSceneHook;
class ParticleTag;
class StickTextureTag;
class Particle;
class LocalResource;
class HierarchyHelp;
class FolderSequence;
class SoundSequence;
class BaseSound;
class Stratified2DRandom;
class BaseThread;
class EnumerateEdges;
class PaintTexture;
class PaintLayer;
class PaintLayerBmp;
class SDKBrowserURL;
class PaintLayerMask;
class PaintLayerFolder;
class PaintBitmap;
class PaintMaterial;
class LayerSet;
class EditorWindow;
class VPBuffer;
class GeData;
class Description;
class DescID;
class DynamicDescription;
class Description;
class BaseContainer;
class Filename;
class BasePlugin;
class PriorityList;
class LensGlowStruct;
class CBaseFrame;
class PolyTriangulate;
class ViewportSelect;
class Pgon;
class NgonBase;
class MultipassBitmap;
class Coffee;
class VALUE;
class CKey;
class CCurve;
class CTrack;
class GeClipMap;
class CAnimInfo;
class GlString;
class Gradient;
class GlProgramFactory;
class GlFrameBuffer;
class GlVertexBuffer;
class LayerObject;
class C4DObjectList;
class LayerSetHelper;
class BaseBitmapLink;
class BitmapLoaderPlugin;
class ColorProfile;
class ColorProfileConvert;
class SplineLengthData;
class UnitScaleData;
class ParserCache;
class GlVertexBufferAttributeInfo;
class GlVertexBufferVectorInfo;
class NetworkIpAddr;
class RootTextureString;
class NetRenderService;
class AssetEntry;
class ReflectionLayer;
class BaseOverride;
class TakeData;
class VertexColorTag;
class HUDTextEntry;

struct NetRenderDocumentContext;
struct FinalizeTmpData;
struct BucketData;
struct RayShaderStackElement;
struct AssetData;
struct LayerData;
struct CustomDataType;
struct ParticleDetails;
struct PolyInfo;
struct IlluminanceSurfacePointData;
struct SDataEx;
struct VolumeData;
struct Ray;
struct Tangent;
struct UVWStruct;
struct Segment;
struct TexList;
struct CPolygon;
struct RayHitID;
struct InitRenderStruct;
struct RayIllumination;
struct RayObject;
struct RayLight;
struct RaySampler;
struct RayHemiSample;
struct RayHemisphere;
struct RayRadianceObject;
struct RayMotionObject;
struct RayMotionLight;
struct RayMotionCamera;
struct PolyVector;
struct TexData;
struct VideoPostStruct;
struct SurfaceData;
struct SurfaceDataEx;
struct RayPolyWeight;
struct MouseDownInfo;
struct DrawInfo;
struct RayLightCache;
struct IconData;
struct C4D_GraphView;
struct NODEPLUGIN;
struct VPFragment;
struct BranchInfo;
struct AnimValue;
struct ObjectColorProperties;
struct PixelFragment;
struct ChannelData;
struct CUSTOMDATATYPEPLUGIN;
struct RESOURCEDATATYPEPLUGIN;
struct TempUVHandle;
struct TextureSize;
struct ViewportPixel;
struct NgonNeighbor;
struct SurfaceIntersection;
struct ARRAY;
struct OBJECT;
struct CSTRING;
struct CLASS;
struct C4DPL_CommandLineArgs;
struct BakeProgressInfo;
struct GlLight;
struct GlGetIdentity;
struct OITInfo;
struct BitmapRenderRegion;
struct GeRWSpinlock;
struct GeSpinlock;
struct PickSessionDataStruct;
struct StereoCameraInfo;
class GlVertexSubBufferData;
struct GlVertexBufferDrawSubbuffer;
struct GlFBAdditionalTextureInfo;
struct GlTextureInfo;
struct BaseSelectData;
struct C4D_BitmapFilter;
struct GlReadDescriptionData;
struct GlWriteDescriptionData;
struct DisplaceInfo;

/// @addtogroup operatingsystem_callbacks_handlers Callbacks/Handlers
/// @ingroup group_function
/// @{

/// @markInternal dialog hook.
typedef Int32 CDialogMessage(CDialog *cd, CUserArea *cu, BaseContainer *msg);

/// @markInternal listview hook.
typedef void ListViewCallBack(Int32 &res_type, void *&result, void *userdata, void *secret, Int32 cmd, Int32 line, Int32 col, void *data1);

//----------------------------------------------------------------------------------------
/// Hook passed to IlluminanceSimple(). Called during illuminance calculations.
/// @param[in] sd									The volume data for the point being calculated.
/// @param[in] rlc								The light data cache for the point being calculated.
/// @param[in] dat								The private data sent to IlluminanceSimple().
//----------------------------------------------------------------------------------------
typedef void IlluminationModel(VolumeData *sd, RayLightCache *rlc, void *dat);

//----------------------------------------------------------------------------------------
/// Callback for @COFFEE error handling.
/// @param[in] priv_data					The private data for the error handler, as passed to Coffee::InstallErrorHook().
/// @param[in] bc									The error container with the following IDs:
/// 															- <i>1</i>: Error number.
/// 															- <i>2</i>: Error line.
/// 															- <i>3</i>: Error position.
/// 															- <i>4</i>: Error file.
/// 															- <i>5</i>: Error string.
/// @return												@trueIfOtherwiseFalse{the error should be passed along to the default console output}
//----------------------------------------------------------------------------------------
typedef Bool COFFEE_ERRORHANDLER(void *priv_data, const BaseContainer &bc);

/// @addtogroup operatingsystem_extended_opengl_mode Extended OpenGL Mode
/// @ingroup group_function
/// @{
/// @extOpenGlMode

typedef void*		(*GlProgramFactoryAllocPrivate)();
typedef void		(*GlProgramFactoryFreePrivate)(void* pData);
typedef void*		(*GlProgramFactoryAllocDescription)();
typedef void		(*GlProgramFactoryFreeDescription)(void* pData);
typedef Bool		(*GlProgramFactoryReadDescription)(GlReadDescriptionData* pFile, void* pData);
typedef Bool		(*GlProgramFactoryWriteDescription)(GlWriteDescriptionData* pFile, const void* pData);
typedef void		(*GlProgramFactoryCreateTextureFunctionCallback)(const Float* prIn, Float* prOut, void* pData);
typedef void		(*GlProgramFactoryMessageCallback)(Int32 lMessage, const void* pObj, UInt64 ulIndex, GlProgramFactory* pFactory);
typedef Int32		(*GlProgramFactoryErrorHandler)(GlProgramType type, const char* pszError);
typedef void		(*GlVertexBufferDrawElementCallback)(Int32 lElement, void* pData);

/// @}

//----------------------------------------------------------------------------------------
/// Callback for BrowserLibraryPopup().
/// @param[in] userdata						The data sent to BrowserLibraryPopup().
/// @param[in] cmd								The browser command ID.
/// @param[in] url								The URL of the preset.
//----------------------------------------------------------------------------------------
typedef void (*BrowserPopupCallback)(void *userdata, Int32 cmd, SDKBrowserURL &url);

/// @markPrivate
typedef Bool (*BaseDrawMessageHook)(BaseDraw* pBaseDraw, BaseDocument* pDoc, BASEDRAW_HOOK_MESSAGE msg, void* pData);

/// @markPrivate
typedef ZEROCONFACTION (*ZeroConfBrowserCallback)(const String& serviceName, Int32 lInterface, ZEROCONFMACHINESTATE state, Bool moreComing, ZEROCONFERROR error, void *context);
/// @markPrivate
typedef void (*ZeroConfBrowserResolvedCallback)(const String& serviceName, const String& fullyQualifiedDomainName, Int32 port, Int32 lInterface, Bool txtRecordUpdate, const String* keys, const String* values, Int32 count, ZEROCONFERROR error, void* context);

/// @markInternal thread hook.
typedef void ThreadMain(void *data);
/// @markInternal thread hook.
typedef Bool ThreadTest(void *data);
/// @markInternal thread hook.
typedef const Char *ThreadName(void *data);

//----------------------------------------------------------------------------------------
/// Callback for the progress of RenderDocument().
/// @see	RenderJob::GetProgressHook\n
///				NetRenderService::InitRendering
/// @param[in] p									The progress, between @em 0.0 and @em 1.0.
/// @param[in] progress_type			The render progress type: @enumerateEnum{RENDERPROGRESSTYPE}
/// @param[in] context						The context passed to RenderDocument(). @callerOwnsPointed{context}
//----------------------------------------------------------------------------------------
typedef void ProgressHook(Float p, RENDERPROGRESSTYPE progress_type, void* context);

//----------------------------------------------------------------------------------------
/// Callback for the write progress of RenderDocument().
/// @see	RenderJob::GetWriteProgressHook\n
///				NetRenderService::InitRendering
/// @param[in] mode								The write mode.
/// @param[in] bmp								The bitmap written to.
/// @param[in] mainImage					@trueOtherwiseFalse{for main image}
/// @param[in] frame							The frame number.
/// @param[in] renderTime					The bitmap frame time.
/// @param[in] streamnum					The stream number.
/// @param[in] streamname					The stream name.
/// @param[in] context						The context data passed. @callerOwnsPointed{data}
//----------------------------------------------------------------------------------------
typedef void WriteProgressHook(WRITEMODE mode, BaseBitmap* bmp, const Filename &fn, Bool mainImage, Int32 frame, Int32 renderTime, Int32 streamnum, const String& streamname, void* context);

//----------------------------------------------------------------------------------------
/// Callback for the progress of texture baking.
/// @param[in] info								The bake progress information.
//----------------------------------------------------------------------------------------
typedef void BakeProgressHook(BakeProgressInfo* info);

/// @markInternal hierarchy hook.
typedef void *HierarchyAlloc(void *main);
/// @markInternal hierarchy hook.
typedef void HierarchyFree(void *main, void *data);
/// @markInternal hierarchy hook.
typedef void HierarchyCopyTo(void *main, void *src, void *dst);
/// @markInternal hierarchy hook.
typedef Bool HierarchyDo(void *main, void *data, BaseObject *op, const Matrix &mg, Bool controlobject);

//----------------------------------------------------------------------------------------
/// Callback for PopupEditText().
/// @param[in] mode								The popup edit mode: @enumerateEnum{POPUPEDITTEXTCALLBACK}
/// @param[in] text								The edit text.
/// @param[in] userdata						The user data passed to PopupEditText().
//----------------------------------------------------------------------------------------
typedef void PopupEditTextCallback(Int32 mode, const String &text, void *userdata);

/// @markPrivate
typedef void (*LASTCURSORINFOFUNC)();

/// @markPrivate
typedef Bool (*SaveCallbackImageFunc)(RDATA_SAVECALLBACK_CMD cmd, void* userdata, BaseDocument* doc, Int32 framenum, BaseBitmap* bmp, const Filename &fn);

//----------------------------------------------------------------------------------------
/// Callback for background handlers registered with GeAddBackgroundHandler()\n
/// Example from the active material rendering:
/// @code
/// Bool Handler_ActiveMaterial(void *data, Int32 command, Int32 flags)
/// {
/// 	switch (command)
/// 	{
/// 		case BACKGROUNDHANDLERCOMMAND_ISRUNNING:
/// 		{
/// 			return world->materialpreview && world->materialpreview->IsRunning();
/// 		} break;
///
/// 		case BACKGROUNDHANDLERCOMMAND_STOP:
/// 		{
/// 			if (flags&BACKGROUNDHANDLERFLAGS_MATERIALPREVIEW)
/// 			{
/// 				if (world->materialpreview)
/// 					world->materialpreview->End();
/// 			}
/// 		} break;
///
/// 		case BACKGROUNDHANDLERCOMMAND_START:
/// 		{
/// 			return CheckActiveMaterialPreview(world->GetActiveDocument());
/// 		} break;
/// 	}
/// 	return true;
/// }
/// @endcode
/// @param[in] data								The data passed to GeAddBackgroundHandler()
/// @param[in] command						The callback command: @enumerateEnum{BACKGROUNDHANDLERCOMMAND}
/// @param[in] parm								The flags given to GeStopBackgroundThreads(): @enumerateEnum{BACKGROUNDHANDLERFLAGS}
/// @return												Depends on the background handler @formatParam{command}.
//----------------------------------------------------------------------------------------
typedef Bool BackgroundHandler(void *data, BACKGROUNDHANDLERCOMMAND command, BACKGROUNDHANDLERFLAGS parm);

//----------------------------------------------------------------------------------------
/// A custom crash handler.\n
/// See the SDK examples and @em main.cpp.
/// @param[in] crashinfo					The crash information text.
//----------------------------------------------------------------------------------------
typedef void (*C4D_CrashHandler)(Char *crashinfo);

/// Create OpenGL context hook.
typedef void (*C4D_CreateOpenGLContext)(void* context, void* root, UInt32 flags);

/// Delete OpenGL context hook.
typedef void (*C4D_DeleteOpenGLContext)(void* context, UInt32 flags);

//----------------------------------------------------------------------------------------
/// Callback for CodeEditor_Open().
/// @param[in] obj								The object the source belongs to.
/// @param[in] msg								The message container.
/// @return												A GeData depending on the message.
//----------------------------------------------------------------------------------------
typedef GeData CodeEditorCallback(BaseList2D *obj, const BaseContainer &msg);

//----------------------------------------------------------------------------------------
/// Callback for @COFFEE definitions.
//----------------------------------------------------------------------------------------
typedef void (*V_CODE)(Coffee*, VALUE*&, Int32);

/// @}


typedef void* UVWHandle;										///< Handle for UVW data. See also: UVWTag
typedef const void* ConstUVWHandle;					///< Handle for read-only UVW data. See also: UVWTag
typedef void* NormalHandle;									///< Handle for normal data. See also: NormalTag
typedef const void* ConstNormalHandle;			///< Handle for read-only normal data. See also: NormalTag
typedef void* VertexColorHandle;						///< Handle for vertex color data. See also: VertexColorTag
typedef const void* ConstVertexColorHandle;	///< Handle for read-only vertex color data. See also: VertexColorTag

//----------------------------------------------------------------------------------------
/// Holds UVW tag variable coordinates data.
/// @see UVWTag
//----------------------------------------------------------------------------------------
struct UVWStruct
{
	/// @name Constructors
	/// @{

	//----------------------------------------------------------------------------------------
	/// Default constructor.
	//----------------------------------------------------------------------------------------
	UVWStruct() {}

	//----------------------------------------------------------------------------------------
	/// Creates an empty UVW variable without constructing the vectors.
	/// @param[in] dc									Dummy argument. Pass DC.
	//----------------------------------------------------------------------------------------
	explicit UVWStruct(_DONTCONSTRUCT dc) : a(DC), b(DC), c(DC), d(DC) { }

	//----------------------------------------------------------------------------------------
	/// Fills the coordinates for a quadrangle.
	/// @param[in] t_a								The coordinates of the first point.
	/// @param[in] t_b								The coordinates of the second point.
	/// @param[in] t_c								The coordinates of the third point.
	/// @param[in] t_d								The coordinates of the fourth point.
	//----------------------------------------------------------------------------------------
	UVWStruct(const Vector &t_a, const Vector &t_b, const Vector &t_c, const Vector &t_d) { a = t_a; b = t_b; c = t_c; d = t_d; }

	//----------------------------------------------------------------------------------------
	/// Fills the coordinates for a triangle.
	/// @param[in] t_a								The coordinates of the first point.
	/// @param[in] t_b								The coordinates of the second point.
	/// @param[in] t_c								The coordinates of the third point.
	//----------------------------------------------------------------------------------------
	UVWStruct(const Vector &t_a, const Vector &t_b, const Vector &t_c) { a = t_a; b = t_b; c = t_c; }

	/// @}

	/// @name Coordinates
	/// @{

	Vector	a,		///< The UVW coordinate for the first point.
					b,		///< The UVW coordinate for the second point.
					c,		///< The UVW coordinate for the third point.
					d;		///< The UVW coordinate for the fourth point.

	/// @}

	/// @name Get/Set Coordinates
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets/sets the UVW coordinate for the point at @formatParam{index}.
	/// @param[in] index							The point index. @em 0 <= @formatParam{index} < 3.\n
	/// 															@em 0 returns @ref a, @em 1 returns @ref b, @em 2 returns @ref c and @em 3 returns @ref d.\n
	/// 															Any other value must not be used and will crash.
	/// @return												The UVW coordinate.
	//----------------------------------------------------------------------------------------
	Vector& operator [] (Int32 index) const { return ((Vector*)this)[index & 3]; }

	/// @}
};

//----------------------------------------------------------------------------------------
/// Holds Normal tag variable coordinates data.
/// @see NormalTag
//----------------------------------------------------------------------------------------
struct NormalStruct
{

	/// @name Constructors
	/// @{

	//----------------------------------------------------------------------------------------
	/// Default constructor.
	//----------------------------------------------------------------------------------------
	NormalStruct() {}

	//----------------------------------------------------------------------------------------
	/// Creates an empty vertex normal variable without constructing the vectors.
	/// @param[in] dc									Dummy argument. Pass DC.
	//----------------------------------------------------------------------------------------
	explicit NormalStruct(_DONTCONSTRUCT dc) : a(DC), b(DC), c(DC), d(DC) {}

	//----------------------------------------------------------------------------------------
	/// Fills the vertex normals.
	/// @param[in] t_a								///< The vertex normal for the first point.
	/// @param[in] t_b								///< The vertex normal for the second point.
	/// @param[in] t_c								///< The vertex normal for the third point.
	/// @param[in] t_d								///< The vertex normal for the fourth point.
	//----------------------------------------------------------------------------------------
	NormalStruct(const Vector &t_a, const Vector &t_b, const Vector &t_c, const Vector &t_d) { a = t_a; b = t_b; c = t_c; d = t_d; }

	/// @}

	/// @name Vertex Normals
	/// @{

	Vector	a,		///< The vertex normal for the first point.
					b,		///< The vertex normal for the second point.
					c,		///< The vertex normal for the third point.
					d;		///< The vertex normal for the fourth point.

	/// @}

	/// @name Get/Set Vertex Normals
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the vertex normal for the point at @formatParam{index}.
	/// @param[in] index							The point index. @em 0 <= @formatParam{index} < 3.\n
	/// 															@em 0 returns @ref a, @em 1 returns @ref b, @em 2 returns @ref c and @em 3 returns @ref d.\n
	/// 															Any other value must not be used and will crash.
	/// @return												The vertex normal for the point at @formatParam{index}.
	//----------------------------------------------------------------------------------------
	Vector& operator [] (Int32 index) const { return ((Vector*)this)[index & 3]; }

	/// @}
};

//----------------------------------------------------------------------------------------
/// Represents a polygon and its vertex color values.
//----------------------------------------------------------------------------------------
struct VertexColorStruct
{
	Vector4d32 a, b, c, d;

	VertexColorStruct() {}
	VertexColorStruct(_DONTCONSTRUCT dc) : a(DC), b(DC), c(DC), d(DC) {}
	VertexColorStruct(const Vector& t_a, const Vector& t_b, const Vector& t_c, const Vector& t_d) { a = Vector4d32(t_a); b = Vector4d32(t_b); c = Vector4d32(t_c); d = Vector4d32(t_d); }
	VertexColorStruct(const Vector32& t_a, const Vector32& t_b, const Vector32& t_c, const Vector32& t_d) { a = Vector4d32(t_a); b = Vector4d32(t_b); c = Vector4d32(t_c); d = Vector4d32(t_d); }
	VertexColorStruct(const Vector4d32& t_a, const Vector4d32& t_b, const Vector4d32& t_c, const Vector4d32& t_d) { a = t_a; b = t_b; c = t_c; d = t_d; }

	Vector4d32& operator[](Int32 index) const { return ((Vector4d32*)this)[index & 3]; }
};

//----------------------------------------------------------------------------------------
/// Represents a single icon in a large bitmap array.
//----------------------------------------------------------------------------------------
struct IconData
{
	BaseBitmap* bmp;			///< The bitmap. Can be @formatConstant{nullptr}.
	Int32 x,							///< The X coordinate of the upper-left corner of the icon.
				y,							///< The Y coordinate of the upper-left corner of the icon.
				w,							///< The width of the icon.
				h;							///< The height of the icon.
	ICONDATAFLAGS flags;	///< The flags: @enumerateEnum{ICONDATAFLAGS}

	/// @name Constructors
	/// @{

	//----------------------------------------------------------------------------------------
	/// Default constructor
	//----------------------------------------------------------------------------------------
	IconData() : bmp(nullptr), x(0), y(0), w(0), h(0), flags(ICONDATAFLAGS_0) { }

	//----------------------------------------------------------------------------------------
	/// Fills the icon data.
	/// @param[in] t_bmp							The bitmap. @callerOwnsPointed{base bitmap}
	/// @param[in] t_x								The X coordinate of the upper-left corner of the icon.
	/// @param[in] t_y								The Y coordinate of the upper-left corner of the icon.
	/// @param[in] t_w								The width of the icon.
	/// @param[in] t_h								The height of the icon.
	//----------------------------------------------------------------------------------------
	IconData(BaseBitmap* t_bmp, Int32 t_x, Int32 t_y, Int32 t_w, Int32 t_h) : bmp(t_bmp), x(t_x), y(t_y), w(t_w), h(t_h), flags(ICONDATAFLAGS_0) { }

	/// @}

	/// @name Part
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets a copy of the bitmap's part for the icon data.
	/// @see BaseBitmap::GetClonePart
	/// @return												The copy of the icon part.
	//----------------------------------------------------------------------------------------
	BaseBitmap* GetClonePart() const;

	//----------------------------------------------------------------------------------------
	/// Gets a copy of the scaled bitmap's part for the icon data with the size @ref GetGuiW()/@ref GetGuiH().
	/// @return												The copy of the scaled icon part.
	//----------------------------------------------------------------------------------------
	BaseBitmap* GetGuiScalePart() const;

	/// @}

	/// @name GUI Scale
	/// @{

	//----------------------------------------------------------------------------------------
	/// Gets the GUI scaled width of the icon data.
	/// @return												The GUI scaled width.
	//----------------------------------------------------------------------------------------
	Int32 GetGuiW() const;

	//----------------------------------------------------------------------------------------
	/// Gets the GUI scaled height of the icon data.
	/// @return												The GUI scaled height.
	//----------------------------------------------------------------------------------------
	Int32 GetGuiH() const;

	/// @}
};


//----------------------------------------------------------------------------------------
/// A helper object for SendModelingCommand().
//----------------------------------------------------------------------------------------
struct ModelingCommandData
{
	//----------------------------------------------------------------------------------------
	/// Default constructor.
	//----------------------------------------------------------------------------------------
	ModelingCommandData() { doc = nullptr; op = nullptr; bc = nullptr; mode = MODELINGCOMMANDMODE_ALL; flags = MODELINGCOMMANDFLAGS_0; result = nullptr; arr = nullptr; }

	//----------------------------------------------------------------------------------------
	/// Default destructor.
	//----------------------------------------------------------------------------------------
	~ModelingCommandData();

	BaseDocument* doc;						///< The document for the operation. Should be set if possible.
																///< @note Must be set for @ref MCOMMAND_MAKEEDITABLE, @ref MCOMMAND_CURRENTSTATETOOBJECT and @ref MCOMMAND_SPLINE_PROJECT.
	BaseObject* op;								///< The input object. Use @ref arr for multiple objects.
	BaseContainer* bc;						///< The modeling command container. Optional to set extra options.
	MODELINGCOMMANDMODE mode;			///< The modeling command mode: @enumerateEnum{MODELINGCOMMANDMODE}
	MODELINGCOMMANDFLAGS flags;		///< The modeling command flags: @enumerateEnum{MODELINGCOMMANDFLAGS}

	AtomArray* arr;								///< The input objects. If this is @formatConstant{nullptr} @ref op is used.
																///< The contents of @ref arr may be changed during the operation.\n
																///< If SendModelingCommand() returns successfully, @ref arr contains all the input objects that were changed,
																///< while @ref result contains the array of newly created objects.
	AtomArray* result;						///< The resulting object array for commands that create new objects.\n
																///< @note Not used if @ref MODELINGCOMMANDFLAGS_CREATEUNDO is set in @ref flags.
};


/// @markPrivate
struct MultiPassChannel
{
	Int32 id;
	String* name;
	MULTIPASSCHANNEL flags;
};


/// @addtogroup VIEWPORTSELECTFLAGS
/// @ingroup group_enumeration
/// @{
enum VIEWPORTSELECTFLAGS
{
	VIEWPORTSELECTFLAGS_0											= 0,			///< None.
	VIEWPORTSELECTFLAGS_USE_HN								= 1,			///< Use HyperNURBS.
	VIEWPORTSELECTFLAGS_USE_DEFORMERS					= 2,			///< Use deformers.
	VIEWPORTSELECTFLAGS_REGION_SELECT					= 4,			///< A rectangle, polygon and lasso selection counts the number of vertices of a polygon within its area. Usually hidden vertices are not taken into account.\n This flag will allow hidden vertices to be taken into account, otherwise it would not be possible to select polygons if for example all points are hidden.
	VIEWPORTSELECTFLAGS_IGNORE_HIDDEN_SEL			= 8,			///< Ignore hidden selection.
	VIEWPORTSELECTFLAGS_USE_DISPLAY_MODE			= 16,			///< If this flag is set and the display mode is Wireframe or Isoparms only edges and vertices are written into the ViewportSelect buffer.\n The ViewportSelect mode must be @ref Mpolyedgepoint.
	VIEWPORTSELECTFLAGS_FORCE_USE_DEFORMERS		= 32,			///< Use deformers even when the viewport DISPLAYEDITSTATE_DEFORM is disabled.
} ENUM_END_FLAGS(VIEWPORTSELECTFLAGS);
/// @}


/// @addtogroup SCRIPTMODE
/// @ingroup group_enumeration
/// @{
/// Script mode for multi-line edit text fields.
enum SCRIPTMODE
{
	SCRIPTMODE_NONE							= 0,	///< Normal multi-line text field.
	SCRIPTMODE_PYTHON						= 1,	///< @em %Python syntax highlighting.
	SCRIPTMODE_COFFEE						= 2		///< @COFFEE syntax highlighting.
} ENUM_END_LIST(SCRIPTMODE);
/// @}



/// @cond IGNORE

struct C4D_Shader
{
	Float						(*SNoise							)(Vector p);
	Float						(*SNoiseT							)(Vector p, Float t);
	Float						(*Noise								)(Vector p);
	Float						(*NoiseT							)(Vector p, Float t);
	Float						(*PNoise							)(Vector p, Vector d);
	Float						(*PNoiseT							)(Vector p, Float t, Vector d, Float dt);
	Float						(*Turbulence					)(Vector p, Float oct, Bool abs);
	Float						(*TurbulenceT					)(Vector p, Float t, Float oct, Bool abs);
	Float						(*WavyTurbulence			)(Vector p, Float t, Float oct, Float start);
	void						(*InitFbm							)(Float *table, Int32 max_octaves, Float lacunarity, Float h);
	Float						(*Fbm									)(const Float *table, Vector p, Float oct);
	Float						(*FbmT								)(const Float *table, Vector p, Float t, Float oct);
	Float						(*RidgedMultifractal	)(const Float *table, Vector p, Float oct, Float offset, Float gain);
	Float						(*CalcSpline					)(Float x, const Float *knot, Int32 nknots);
	Vector					(*CalcSplineV					)(Float x, const Vector *knot, Int32 nknots);

	void						(*Illuminance1				)(VolumeData *sd, Vector *diffuse, Vector *specular, Float exponent);

	Int32						(*GetCurrentCPU				)(const VolumeData *sd);
	Int32						(*GetCPUCount					)(const VolumeData *sd);
	void*						(*GetRayData					)(const VolumeData *sd, Int32 i);

	const RayObject* (*GetObj							)(const VolumeData *sd, Int32 i);
	Int32						(*GetObjCount					)(const VolumeData *sd);

	const RayLight*	(*GetLight						)(const VolumeData *sd, Int32 i);
	Int32						(*GetLightCount				)(const VolumeData *sd);

	const RayObject* (*ID_to_Obj					)(const VolumeData *sd, const RayHitID &id);

	void						(*GetUVW							)(const VolumeData *sd, const RayObject *op, Int32 uvwind, Int32 i, PolyVector *uvw);
	Vector					(*GetPointUVW					)(const VolumeData *sd, const TexData *tdp, const RayHitID &lhit, const Vector64 &p);
	void						(*GetNormals					)(const VolumeData *sd, const RayObject *op, Int32 polygon, PolyVector *norm);
	TexData*				(*GetTexData					)(const VolumeData *sd, const RayObject *op, Int32 index);
	Vector64				(*GetNormal						)(const VolumeData *sd, const RayObject *op, Int32 polygon, Bool second);
	Vector64				(*GetSmoothedNormal		)(const VolumeData *sd, const RayHitID &hit, const Vector64 &p);
	Bool						(*GetRS								)(const VolumeData *sd, const RayHitID &hit, const Vector64 &p, Float *r, Float *s);

	void						(*GetRay							)(const VolumeData *sd, Float x, Float y, Ray *ray);
	Vector64				(*ScreenToCamera			)(const VolumeData *sd, const Vector64 &p);
	Vector64				(*CameraToScreen			)(const VolumeData *sd, const Vector64 &p);
	Bool						(*ProjectPoint				)(const VolumeData *sd, const TexData *tdp, const RayHitID &lhit, const Vector64 &p, const Vector64 &n, Vector *uv);

	VolumeData*			(*AllocVolumeData			)();
	void						(*FreeVolumeData			)(VolumeData *sd);

	void						(*StatusSetText				)(const VolumeData *sd, const String *str);
	void						(*StatusSetBar				)(const VolumeData *sd, Float percentage);

	TexData*				(*AllocTexData				)();
	void						(*FreeTexData					)(TexData *td);
	void						(*InitTexData					)(TexData *td);

	Vector					(*CalcVisibleLight		)(const VolumeData *sd, const Ray *ray, Float maxdist, Vector *trans);
	void						(*GetXY								)(const VolumeData *sd, Int32 *x, Int32 *y, Int32 *scale);

	Int32						(*Obj_to_Num					)(const VolumeData *sd, const RayObject *obj);
	Int32						(*Light_to_Num				)(const VolumeData *sd, const RayLight *light);

	void						(*CopyVolumeData			)(const VolumeData *src, VolumeData *dst);

	Bool						(*VPAllocateBuffer		)(Render *render, Int32 id, Int32 subid, Int32 bitdepth, Bool visible);
	VPBuffer*				(*VPGetBuffer					)(const Render *render, Int32 id, Int32 subid);
	Int32						(*VPGetInfo						)(const VPBuffer *buf, VPGETINFO type);
	Bool						(*VPGetLine						)(const VPBuffer *buf, Int32 x, Int32 y, Int32 cnt, void *data, Int32 bitdepth, Bool dithering);
	Bool						(*VPSetLine						)(const VPBuffer *buf, Int32 x, Int32 y, Int32 cnt, void *data, Int32 bitdepth, Bool dithering);

	void						(*OutOfMemory					)(VolumeData *sd);
	Float						(*GetLightFalloff			)(Int32 falloff, Float inner, Float outer, Float dist);

	Bool						(*TestBreak						)(VolumeData *sd);

	void						(*VPGetRenderData			)(const Render *render, BaseContainer *bc);
	void						(*VPSetRenderData			)(Render *render, const BaseContainer *bc);

	void						(*Illuminance					)(VolumeData *sd, Vector *diffuse, Vector *specular, IlluminationModel *model, void *data);

	BaseVideoPost*	(*FindVideoPost	)(const VolumeData *sd, Int32 i, Bool index);
	const VPFragment**		(*VPGetFragments)(const VolumeData *sd, Int32 x, Int32 y, Int32 cnt, VPGETFRAGMENTS flags);
	Bool						(*AddLensGlowEx				)(const VolumeData *sd, const LensGlowStruct *lgs, Vector *lgs_pos, Int32 lgs_cnt, Float intensity);

	RayLight*				(*AllocRayLight				)(BaseDocument *doc, BaseObject *op);
	void						(*FreeRayLight				)(RayLight *lgt);

	Int32						(*TranslateObjIndex		)(const VolumeData *sd, Int32 index, Bool old_to_new);
	Bool						(*TranslatePolygon		)(const VolumeData *sd, const RayObject *op, Int32 local_index, Vector *previous_points);
	Bool						(*SampleLensFX				)(const VolumeData *sd, const VPBuffer *rgba, const VPBuffer *fx, BaseThread *bt);
	Int32						(*VPAllocateBufferFX	)(Render *render, Int32 id, const String &name, Int32 bitdepth, Bool visible);

	VolumeData*			(*VPGetInitialVolumeData)(const Render *render, Int32 cpu);

	Bool						(*CalcFgBg						)(const VolumeData *sd, Bool foreground, Int32 x, Int32 y, Int32 subx, Int32 suby, Vector *color, Float *alpha);
	Int32						(*GetRayPolyState			)(const VolumeData *sd, const RayObject *op, Int32 i);

	void						(*GetWeights					)(const VolumeData *sd, const RayHitID &hit, const Vector64 &p, RayPolyWeight *wgt);
	void						(*InitVolumeData			)(const VolumeData *src, VolumeData *dst);

	Vector					(*TraceColor					)(VolumeData *sd, Ray *ray, Float maxdist, const RayHitID &lhit, SurfaceIntersection *si);
	Bool						(*TraceGeometry				)(const VolumeData *sd, const Ray *ray, Float maxdist, const RayHitID &lhit, SurfaceIntersection *si);
	void						(*GetSurfaceDataEx		)(VolumeData *sd, SurfaceDataEx *cd, Int32 calc_illum, Bool calc_shadow, Bool calc_refl, Bool calc_trans, Ray *ray, const SurfaceIntersection &si);

	void						(*SkipRenderProcess		)(VolumeData *sd);

	void*						(*VPGetPrivateData		)(const Render *render);
	Render*					(*GetRenderInstance		)(const VolumeData *sd);

	Vector					(*CentralDisplacePointUV	)(const VolumeData *sd, const RayObject *op, Int32 local_id, Int32 uu, Int32 vv);

	Vector					(*CalcDisplacementNormals	)(const VolumeData *sd, Float par_u, Float par_v, Int32 u0, Int32 v0, Int32 u1, Int32 v1, Int32 u2, Int32 v2, const Vector &a, const Vector &b, const Vector &c, const RayObject *op, Int32 polynum);

	Stratified2DRandom*	(*SNAlloc										)(void);
	void								(*SNFree										)(Stratified2DRandom *rnd);
	Bool						(Stratified2DRandom::*SNInit		)(Int32 initial_value, Bool reset);
	void						(Stratified2DRandom::*SNGetNext	)(Float *xx, Float *yy);
	BAKE_TEX_ERR		(*BakeTexture										)(BaseDocument* doc, const BaseContainer &data, BaseBitmap *bmp, BaseThread* th, BakeProgressHook* hook, BakeProgressInfo* info);
	BaseDocument*		(*InitBakeTexture								)(BaseDocument* doc, TextureTag* textag, UVWTag* texuvw, UVWTag* destuvw, const BaseContainer &bc, BAKE_TEX_ERR* err, BaseThread* th);
	BaseDocument*		(*InitBakeTextureA							)(BaseDocument* doc, TextureTag** textags, UVWTag** texuvws, UVWTag** destuvws, Int32 cnt, const BaseContainer &bc, BAKE_TEX_ERR* err, BaseThread* th);

	void						(*GetDUDVEx											)(const VolumeData *vd, const TexData *tex, const Vector64 &p, const Vector64 &phongn, const Vector64 &orign, const RayHitID &hitid, Bool forceuvw, Vector *ddu, Vector *ddv);
	void						(*CalcArea											)(VolumeData *sd, const RayLight *light, Bool nodiffuse, Bool nospecular, Float specular_exponent, const Vector64 &ray_vector, const Vector64 &p, const Vector64 &bumpn, const Vector64 &orign, RAYBIT raybits, Vector *diffuse, Vector *specular);
	Bool						(*Illuminate										)(VolumeData *sd, const RayLight *light, Vector *col, Vector64 *lv, const Vector64 &p, const Vector64 &bumpn, const Vector64 &phongn, const Vector64 &orign, const Vector64 &ray_vector, ILLUMINATEFLAGS calc_shadow, const RayHitID &hitid, RAYBIT raybits, Bool cosine_cutoff, Vector *xshadow);
	void						(*IlluminanceSurfacePoint				)(VolumeData *sd, IlluminanceSurfacePointData *f, Vector *diffuse, Vector *specular);
	Vector					(*IlluminanceAnyPoint						)(VolumeData *sd, const Vector64 &p, ILLUMINATEFLAGS flags, RAYBIT raybits);
	Vector					(*CalcShadow										)(VolumeData *sd, const RayLight *light, const Vector64 &p, const Vector64 &bumpn, const Vector64 &phongn, const Vector64 &orign, const Vector64 &rayv, Bool transparency, const RayHitID &hitid, RAYBIT raybits);

	Bool						(*SetRenderProperty							)(Render *render, Int32 id, const GeData &dat);
	void						(*SetXY													)(VolumeData *sd, Float x, Float y);
	void						(*InitSurfacePointProperties		)(VolumeData *sd, TexData *td);

	Float						(*SNoiseP												)(Vector p, Float t, Int32 t_repeat);
	Float						(*TurbulenceP										)(Vector p, Float t, Float oct, Bool abs, Int32 t_repeat);
	Float						(*FbmP													)(const Float *table, Vector p, Float t, Float oct, Int32 t_repeat);
	Float						(*RidgedMultifractalP						)(const Float *table, Vector p, Float t, Float oct, Float offset, Float gain, Int32 t_repeat);

	Bool						(*AttachVolumeDataFake					)(VolumeData *sd, BaseObject *camera, const BaseContainer &renderdata, void *priv);
	RayObject*			(*AllocRayObject								)(Int32 tex_cnt, void *priv);
	void						(*FreeRayObject									)(RayObject *op);

	Bool						(*TraceGeometryEnhanced					)(const VolumeData *sd, const Ray *ray, Float maxdist, const RayHitID &lhit, Int32 raydepth, RAYBIT raybits, Vector64 *oldray, SurfaceIntersection *si);
	Vector					(*TraceColorDirect							)(VolumeData *sd, Ray *ray, Float maxdist, Int32 raydepth, RAYBIT raybits, const RayHitID &lhit, Vector64 *oldray, SurfaceIntersection *si);

	Vector					(*CalcHardShadow								)(VolumeData *sd, const Vector64 &p1, const Vector64 &p2, CALCHARDSHADOW flags, const RayHitID &lhit, Int32 recursion_id, void *recursion_data);
	void						(*StatusSetSpinMode							)(const VolumeData *sd, Bool on);

	Vector					(*TransformColor								)(const Vector &v, COLORSPACETRANSFORMATION colortransformation);

	void						(*VPIccConvert									)(const Render *rnd, void *data, Int32 xcnt, Int32 components, Bool inverse);

	Bool						(*SaveShaderStack								)(VolumeData *sd, RayShaderStackElement *&stack, Int32 &stack_cnt);
	Bool						(*RestoreShaderStack						)(VolumeData *sd, RayShaderStackElement *stack, Int32 stack_cnt);

	const RayObject* (*GetSky												)(const VolumeData *sd, Int32 i);
	Int32						(*GetSkyCount										)(const VolumeData *sd);

	Bool						(*AddLensGlow										)(const VolumeData *sd, const LensGlowStruct *lgs, Vector *lgs_pos, Int32 lgs_cnt, Float intensity, Bool linear_workflow);
	RaySampler*			(*GetSampler										)(const VolumeData *sd, void *guid, Int32 depth);
	Float						(*GetRayWeight									)(const VolumeData *sd);

	Float						(*CalcAmbientOcclusionEx				)(VolumeData *sd, SurfaceIntersection *pSI, RaySampler *sampler, Float minlength, Float maxlength, Float index, Bool self, Bool trans, Float weight);

	Vector					(*CalcSubsurfaceScattering			)(VolumeData *sd, Vector scattering, Vector absorption, Vector diffuse, Float ior);

	Int32						(*GetStreamCount								)(const VolumeData *sd);
	void						(*GetStreamRay									)(const VolumeData *sd, Int32 stream, Float x, Float y, Ray *ray);

	void						(*GetSceneBoundaries						)(const VolumeData *sd, Vector &min, Vector &max);
	Bool						(*GetDisplaceInfo								)(const VolumeData *sd, const RayObject* op, DisplaceInfo& info);
	Vector					(*CentralDisplaceUVGetNormal		)(const VolumeData *sd, const RayObject *op, Int32 local_id, Int32 uu, Int32 vv);
	Int32						(*GetDisplaceNeighbor						)(const VolumeData *sd, const RayObject* op, Int32 local_id, Int32 side);

	Bool								(*CalcIndirectIllumination	)(VolumeData *sd, RayHemisphere *hs, Float weight);
	RayRadianceObject*	(*CreateRadianceMaps				)(VolumeData *sd);
	RayRadianceObject*	(*GetRadianceMaps						)(const VolumeData *sd);
	Vector							(*CalcRadianceValue					)(VolumeData *sd, Ray *ray, const SurfaceIntersection &si);
	void								(*GetDUDV										)(const VolumeData *vd, const TexData *tex, const Vector64 &p, const Vector64 &phongn, const Vector64 &orign, const RayHitID &hitid, Bool forceuvw, Vector *ddu, Vector *ddv, Bool usetangents);
	Bool								(*IsPhysicalRender					)(const VolumeData *sd);
	Int32*							(*GetUniqueID								)(const VolumeData *sd, const RayObject *op, Int32 &length);
	Bool								(*CalcIndirectPDF						)(VolumeData *sd, const Vector &point, const Vector &normal, const Vector &ray_in, const Vector &ray_out, Float &pdf_qmc, Float &pdf_area, Float &pdf_portal, Float &pdf_sky);
	Bool								(*CalcIndirectPath					)(VolumeData *sd, const Vector &dir, void *source, void *target);

	void						(*GetSurfaceData								)(VolumeData *sd, SurfaceData *cd, Int32 calc_illum, Bool calc_shadow, Bool calc_refl, Bool calc_trans, Ray *ray, const SurfaceIntersection &si);

	Vector					(*CalcRadiancePoly							)(VolumeData *sd, RayRadianceObject *obj, SurfaceIntersection *si, Int32 poly, Int32 u, Int32 v, Bool back);
	void						(*CorrectLocalID								)(const VolumeData *sd, const RayObject* op, Int32& local_id);
	Float						(*GetPhysicalCameraIntensity		)(const VolumeData *sd);
	Bool						(*CentralDisplacePointUVGetBarycentric)(const VolumeData *sd, const RayObject *op, Int32& local_id, Int32& uu, Int32& vv, RayPolyWeight& bary, Bool& displaceQuad);
	void						(*SetPhysicalRayTime						)(VolumeData *sd, Float time);
	Vector					(*CalcBackTransformPoint				)(const VolumeData *sd);
	Matrix64				(*CalcMotionObjectMatrixInv			)(const VolumeData *sd, const RayObject *op);
	Bool						(*GetTile												)(const VolumeData* sd, Int32& xMin, Int32& yMin, Int32& xMax, Int32& yMax, Int32& renderThreadIndex);
	RayMotionObject*		(*GetMotionObject						)(const VolumeData *sd, const RayObject *op);
	RayMotionLight*			(*GetMotionLight						)(const VolumeData *sd, const RayLight *light);
	RayMotionCamera*		(*GetMotionCamera						)(const VolumeData *sd, Int32 stream);

	Float						(*CalcAmbientOcclusion					)(VolumeData *sd, SurfaceIntersection *pSI, RaySampler *sampler, Float minlength, Float maxlength, Float index, Bool self, Bool trans, Float weight, Bool reverse);

	Vector					(*CentralDisplacePointFromUVPoint						)(const VolumeData *sd, const RayObject* op, Int32 local_id, Bool bFirst, Float par_u, Float par_v, const Vector& uv, const UVWStruct& uvw);
	Vector					(*CentralDisplaceGetSurfaceNormalFromUVPoint)(const VolumeData *sd, const RayObject *op, Int32 local_id, Bool bFirst, Float par_u, Float par_v, const Vector& uv, const UVWStruct& uvw);
	Vector					(*CentralDisplaceGetShadingNormalFromUVPoint)(const VolumeData *sd, const RayObject *op, Int32 local_id, Bool bFirst, Float par_u, Float par_v, const Vector& uv, const UVWStruct& uvw);
	void						(*GetDUDVFromUVPoint												)(VolumeData *vd, const RayObject *op, const TexData *tex, Float par_u, Float par_v, const Vector64 &uv, const Vector &p, const Vector64 &phongn, const Vector64 &orign, const UVWStruct& uvw, const RayHitID &hitid, Bool forceuvw, Vector *ddu, Vector *ddv, Bool usetangents);
};

struct C4D_HyperFile
{
	Bool						(HyperFile::*Open								)(Int32 ident, const Filename &name, FILEOPEN mode, FILEDIALOG error_dialog);
	Bool						(HyperFile::*Close							)();

	Bool						(HyperFile::*WriteChar					)(Char v);
	Bool						(HyperFile::*WriteUChar					)(UChar v);
	Bool						(HyperFile::*WriteInt16					)(Int16 v);
	Bool						(HyperFile::*WriteUInt16				)(UInt16 v);
	Bool						(HyperFile::*WriteInt32					)(Int32 v);
	Bool						(HyperFile::*WriteUInt32				)(UInt32 v);
	Bool						(HyperFile::*WriteFloat					)(Float v);
	Bool						(HyperFile::*WriteFloat32				)(Float32 v);
	Bool						(HyperFile::*WriteFloat64				)(Float64 v);
	Bool						(HyperFile::*WriteBool					)(Bool v);
	Bool						(HyperFile::*WriteTime					)(const BaseTime &v);
	Bool						(HyperFile::*WriteVector				)(const Vector &v);
	Bool						(HyperFile::*WriteVector32			)(const Vector32 &v);
	Bool						(HyperFile::*WriteVector64			)(const Vector64 &v);
	Bool						(HyperFile::*WriteMatrix				)(const Matrix &v);
	Bool						(HyperFile::*WriteMatrix32			)(const Matrix32 &v);
	Bool						(HyperFile::*WriteMatrix64			)(const Matrix64 &v);
	Bool						(HyperFile::*WriteString				)(const String &v);
	Bool						(HyperFile::*WriteFilename			)(const Filename &v);
	Bool						(HyperFile::*WriteContainer			)(const BaseContainer &v);
	Bool						(HyperFile::*WriteMemory				)(const void *data, Int count);
	Bool						(HyperFile::*WriteInt64					)(Int64 v);

	Bool						(HyperFile::*ReadChar						)(Char *v);
	Bool						(HyperFile::*ReadUChar					)(UChar *v);
	Bool						(HyperFile::*ReadInt16					)(Int16 *v);
	Bool						(HyperFile::*ReadUInt16					)(UInt16 *v);
	Bool						(HyperFile::*ReadInt32					)(Int32 *v);
	Bool						(HyperFile::*ReadUInt32					)(UInt32 *v);
	Bool						(HyperFile::*ReadFloat					)(Float *v);
	Bool						(HyperFile::*ReadFloat32				)(Float32 *v);
	Bool						(HyperFile::*ReadFloat64				)(Float64 *v);
	Bool						(HyperFile::*ReadBool						)(Bool *v);
	Bool						(HyperFile::*ReadTime						)(BaseTime *v);
	Bool						(HyperFile::*ReadVector					)(Vector *v);
	Bool						(HyperFile::*ReadVector32				)(Vector32 *v);
	Bool						(HyperFile::*ReadVector64				)(Vector64 *v);
	Bool						(HyperFile::*ReadMatrix					)(Matrix *v);
	Bool						(HyperFile::*ReadMatrix32				)(Matrix32 *v);
	Bool						(HyperFile::*ReadMatrix64				)(Matrix64 *v);
	Bool						(HyperFile::*ReadString					)(String *v);
	Bool						(HyperFile::*ReadFilename				)(Filename *v);
	Bool						(HyperFile::*ReadImage					)(BaseBitmap *v);
	Bool						(HyperFile::*ReadContainer			)(BaseContainer *v, Bool flush);
	Bool						(HyperFile::*ReadMemory					)(void **data, Int *size);
	Bool						(HyperFile::*ReadInt64					)(Int64 *v);

	FILEERROR				(HyperFile::*GetError						)() const;
	void						(HyperFile::*SetError						)(FILEERROR err);
	Bool						(HyperFile::*ReadValueHeader		)(HYPERFILEVALUE *h);
	Bool						(HyperFile::*SkipValue					)(HYPERFILEVALUE h);
	Bool						(HyperFile::*WriteChunkStart		)(Int32 id, Int32 level);
	Bool						(HyperFile::*WriteChunkEnd			)();
	Bool						(HyperFile::*ReadChunkStart			)(Int32 *id, Int32 *level);
	Bool						(HyperFile::*ReadChunkEnd				)();
	Bool						(HyperFile::*SkipToEndChunk			)();
	BaseDocument*		(HyperFile::*GetDocument				)() const;

	Int32						(HyperFile::*GetFileVersion			)() const;

	Bool						(HyperFile::*WriteImage					)(BaseBitmap *v, Int32 format, const BaseContainer *data, SAVEBIT savebits);
	Bool						(HyperFile::*WriteArray					)(const void *data, HYPERFILEARRAY type, Int32 structure_increment, Int32 count);
	Bool						(HyperFile::*ReadArray					)(void *data, HYPERFILEARRAY type, Int32 structure_increment, Int32 count);

	HyperFile*			(*AllocHF							)();
	void						(*FreeHF							)(HyperFile *&hf);

	FILEERROR				(*ReadFile						)(BaseDocument *doc, GeListNode *node, const Filename &filename, Int32 ident, String *warning_string);
	FILEERROR				(*WriteFile						)(BaseDocument *doc, GeListNode *node, const Filename &filename, Int32 ident);

	Bool						(*WriteGeData					)(HyperFile *hf, const GeData &v);
	Bool						(*ReadGeData					)(HyperFile *hf, GeData &v);
	Bool						(HyperFile::*ReadUInt64					)(UInt64 *v);
	Bool						(HyperFile::*WriteUInt64				)(UInt64 v);

	void						(HyperFile::*SetFileVersion		)(Int32 val);
	Bool						(HyperFile::*ReadUuid					)(C4DUuid *v);
	Bool						(HyperFile::*WriteUuid				)(const C4DUuid &v);
	LOCATION				(HyperFile::*GetLocation			)() const;
};

struct C4D_BaseContainer
{
	BaseContainer		*Default;

	BaseContainer*	(*Alloc								)(Int32 id);
	void						(*Free								)(BaseContainer *killme);
	Bool						(*Compare							)(const BaseContainer &bc1, const BaseContainer &bc2);
	void*						(*BrowseContainer			)(const BaseContainer *bc, Int32 *id, GeData **data, void *handle);

	void						(BaseContainer::*SDKInit						)(Int32 id, const BaseContainer *src);
	BaseContainer*	(BaseContainer::*GetClone						)(COPYFLAGS flags, AliasTrans *trans) const;
	void						(BaseContainer::*FlushAll						)();
	Int32						(BaseContainer::*GetId							)() const;
	void						(BaseContainer::*SetId							)(Int32 newid);

	void						(BaseContainer::*SetVoid						)(Int32 id, void *v);
	void						(BaseContainer::*SetFloat						)(Int32 id, Float v);
	void						(BaseContainer::*SetBool						)(Int32 id, Bool v);
	void						(BaseContainer::*SetInt32						)(Int32 id, Int32 v);
	void						(BaseContainer::*SetString					)(Int32 id, const String &v);
	void						(BaseContainer::*SetFilename				)(Int32 id, const Filename &v);
	void						(BaseContainer::*SetTime						)(Int32 id, const BaseTime &v);
	void						(BaseContainer::*SetContainer				)(Int32 id, const BaseContainer &v);
	void						(BaseContainer::*SetVector					)(Int32 id, const Vector &v);
	void						(BaseContainer::*SetMatrix					)(Int32 id, const Matrix &v);

	BaseContainer		(BaseContainer::*GetContainer				)(Int32 id) const;
	BaseContainer*	(BaseContainer::*GetContainerInstance)(Int32 id);
	Bool						(BaseContainer::*RemoveData					)(Int32 id);
	Int32						(BaseContainer::*FindIndex					)(Int32 id, GeData **data) const;
	Int32						(BaseContainer::*GetIndexId					)(Int32 index) const;
	Bool						(BaseContainer::*RemoveIndex				)(Int32 index);
	GeData*					(BaseContainer::*GetIndexData				)(Int32 index) const;

	BaseList2D*			(BaseContainer::*GetLink						)(Int32 id, const BaseDocument *doc, Int32 instanceof) const;
	void						(BaseContainer::*SetLink						)(Int32 id, C4DAtomGoal *link);

	const GeData&		(BaseContainer::*GetData						)(Int32 id) const;
	Bool						(BaseContainer::*GetParameter				)(const DescID &id, GeData &t_data) const;
	Bool						(BaseContainer::*SetParameter				)(const DescID &id, const GeData &t_data);

	GeData*					(BaseContainer::*InsData						)(Int32 id, const GeData &n);
	GeData*					(BaseContainer::*SetData						)(Int32 id, const GeData &n);
	void						(BaseContainer::*SetInt64						)(Int32 id, Int64 v);
	GeData*					(BaseContainer::*InsDataAfter				)(Int32 id, const GeData &n, const GeData *last);
	Bool						(BaseContainer::*CopyTo							)(BaseContainer *dest, COPYFLAGS flags, AliasTrans *trans) const;
	void						(BaseContainer::*Sort								)();

	Float						(BaseContainer::*GetFloat						)(Int32 id, Float preset) const;
	Bool						(BaseContainer::*GetBool						)(Int32 id, Bool preset) const;
	Int32						(BaseContainer::*GetInt32						)(Int32 id, Int32 preset) const;
	String					(BaseContainer::*GetString					)(Int32 id, const String& preset) const;
	Filename				(BaseContainer::*GetFilename				)(Int32 id, const Filename& preset) const;
	BaseTime				(BaseContainer::*GetTime						)(Int32 id, const BaseTime& preset) const;
	Vector					(BaseContainer::*GetVector					)(Int32 id, const Vector& preset) const;
	Matrix					(BaseContainer::*GetMatrix					)(Int32 id, const Matrix& preset) const;
	Int64						(BaseContainer::*GetInt64						)(Int32 id, Int64 preset) const;
	void*						(BaseContainer::*GetVoid						)(Int32 id, void* preset) const;
	const GeData*		(BaseContainer::*GetDataPointer			)(Int32 id) const;
	void						(BaseContainer::*Merge							)(const BaseContainer &src);
	UInt32					(BaseContainer::*GetDirty						)() const;
	void						(BaseContainer::*GetDataPointers		)(const Int32* ids, Int32 cnt, const GeData** data) const;

	UInt64					(BaseContainer::*GetUInt64					)(Int32 id, UInt64 preset) const;
	UInt32					(BaseContainer::*GetUInt32					)(Int32 id, UInt32 preset) const;

	void						(BaseContainer::*SetUInt64					)(Int32 id, UInt64 v);
	void						(BaseContainer::*SetUInt32					)(Int32 id, UInt32 v);

	void						(BaseContainer::*SetMemory					)(Int32 id, void *mem, Int count);
	void*						(BaseContainer::*GetMemoryAndRelease)(Int32 id, Int& count, void* preset);
	void*						(BaseContainer::*GetMemory					)(Int32 id, Int& count, void* preset) const;

	void						(BaseContainer::*SetUuid						)(Int32 id, const C4DUuid& v);
	C4DUuid					(BaseContainer::*GetUuid						)(Int32 id, const C4DUuid& preset) const;
	const BaseContainer*	(BaseContainer::*GetContainerInstanceConst)(Int32 id) const;
};

struct C4D_Uuid
{
	void						(*Init										)(C4DUuid* uuid);

	Bool						(C4DUuid::*Compare				)(const C4DUuid& uuid2) const;

	void						(C4DUuid::*CopyTo					)(UChar* buf) const;
	void						(C4DUuid::*CopyFrom				)(UChar* buf);

	void						(C4DUuid::*CopyToUuid			)(const C4DUuid& dst) const;
	void						(C4DUuid::*CopyFromUuid		)(const C4DUuid& src);

	Bool						(C4DUuid::*CopyFromString	)(const String& uuid);

	String					(C4DUuid::*GetString			)() const;
	UInt32					(C4DUuid::*GetHashCode		)() const;
};

struct C4D_GeData
{
	void						(*Free								)(GeData *data);
	Bool						(*IsEqual							)(const GeData *data, const GeData *data2);
	Int32						(*GetType							)(const GeData *data);
	void						(*CopyData						)(GeData *dest, const GeData *src, AliasTrans *aliastrans);

	Bool						(*SetNil							)(GeData *data);
	Bool						(*SetInt32						)(GeData *data, Int32 n);
	Bool						(*SetFloat						)(GeData *data, Float n);
	Bool						(*SetVector						)(GeData *data, const Vector &n);
	Bool						(*SetMatrix						)(GeData *data, const Matrix &n);
	Bool						(*SetString						)(GeData *data, const String *n);
	Bool						(*SetFilename					)(GeData *data, const Filename *n);
	Bool						(*SetBaseTime					)(GeData *data, const BaseTime &n);
	Bool						(*SetBaseContainer		)(GeData *data, const BaseContainer *n);
	Bool						(*SetLink							)(GeData *data, const BaseLink &n);

	Int32						(*GetInt32							)(const GeData *data);
	Float						(*GetFloat							)(const GeData *data);
	const Vector&		(*GetVector						)(const GeData *data);
	const Matrix&		(*GetMatrix						)(const GeData *data);
	const String&		(*GetString						)(const GeData *data);
	const Filename&	(*GetFilename					)(const GeData *data);
	const BaseTime&	(*GetTime							)(const GeData *data);
	BaseContainer*	(*GetContainer				)(const GeData *data);
	BaseLink*				(*GetLink							)(const GeData *data);

	Bool						(*SetCustomData				)(GeData *data, Int32 type, const CustomDataType &n);
	CustomDataType*	(*GetCustomData				)(const GeData *data, Int32 type);
	Bool						(*InitCustomData			)(GeData *data, Int32 type);

	Bool						(*SetInt64						)(GeData *data, Int64 n);
	Int64						(*GetInt64						)(const GeData *data);
	void						(*SetVoid							)(GeData *data, void *v);

	Bool						(*SetBlLink						)(GeData *data, BaseList2D *bl);
	void						(*SetMemory						)(GeData *data, void *mem, Int count);
	void*						(*GetMemoryAndRelease	)(GeData *data, Int& count);
	void*						(*GetMemory						)(const GeData *data, Int& count);

	Bool						(*SetUuid							)(GeData *data, const C4DUuid *n);
	const C4DUuid&	(*GetUuid							)(const GeData *data);
};

struct C4D_String
{
	String					*Default; // Safety value

	String*					(*Alloc								)(void);
	void						(*Init								)(String *str);
	void						(*Free								)(String *str);
	void						(*InitCString					)(String *str, const Char *txt, Int32 count, STRINGENCODING type);
	void						(*InitArrayEx					)(String *str, Int32 count, Utf16Char fillchr);
	void						(*Flush								)(String *str);
	void						(*CopyTo							)(const String *src, String *dst);
	Bool						(*Add									)(String *dst, const String *src);

	String					(*RealToStringEx			)(Float v, Int32 vk, Int32 nk, Bool e, Utf16Char xchar);
	String					(*LongToString				)(Int32 l);
	String					(*LLongToString				)(Int64 l);
	String					(*LLongToStringExEx		)(Int64 l);

	Utf16Char				(*GetChrEx						)(const String *str, Int32 pos);
	void						(*SetChrEx						)(String *str, Int32 pos, Utf16Char chr);

	Int32						(String::*GetLength			)() const;
	Bool						(String::*FindFirst			)(const String &str, Int32 *pos, Int32 start) const;
	Bool						(String::*FindLast			)(const String &str, Int32 *pos, Int32 start) const;
	void						(String::*Delete				)(Int32 pos, Int32 count);
	void						(String::*Insert				)(Int32 pos, const String &str, Int32 start, Int32 end);
	String					(String::*SubStr				)(Int32 start, Int32 count) const;
	Float						(String::*ParseToFloat	)(Int32 *error, Int32 unit, Int32 angular_type, Int32 base) const;
	Int32						(String::*ParseToInt32	)(Int32 *error) const;
	String					(String::*ToUpper				)() const;
	String					(String::*ToLower				)() const;
	Int32						(String::*GetCStringLen	)(STRINGENCODING type) const;
	Int32						(String::*GetCString		)(Char *cstr, Int32 max, STRINGENCODING type) const;
	void						(String::*GetUcBlockEx	)(Utf16Char* Ubc, Int32 Max) const;
	void						(String::*GetUcBlockNullEx)(Utf16Char* Ubc, Int32 Max) const;
	void						(String::*SetUcBlockEx	)(const Utf16Char* Ubc, Int32 Count);
	Int32						(String::*Compare				)(const String &dst) const;
	Int32						(String::*LexCompare		)(const String &dst) const;
	Int32						(String::*RelCompare		)(const String &dst) const;
	Int32						(String::*ComparePart		)(const String &Str, Int32 cnt, Int32 pos) const;
	Int32						(String::*LexComparePart)(const String &Str, Int32 cnt, Int32 pos) const;
	Bool						(String::*FindFirstChEx	)(Utf16Char ch, Int32 *Pos, Int32 Start) const;
	Bool						(String::*FindLastChEx	)(Utf16Char ch, Int32 *Pos, Int32 Start) const;
	Bool						(String::*FindFirstUpper)(const String &find, Int32 *pos, Int32 start) const;
	Bool						(String::*FindLastUpper	)(const String &find, Int32 *pos, Int32 start) const;

	String					(*MemoryToString				)(Int64 mem);
	String					(*HexToString32					)(UInt32 v, Bool prefix0x);
	String					(*HexToString64					)(UInt64 v, Bool prefix0x);
	String					(*IntToString64					)(Int64 l);
	String					(*UIntToString64				)(UInt64 l);
	String					(*FloatToString32Ex			)(Float32 v, Int32 vvk, Int32 nnk, Bool e, Utf16Char xchar);
	String					(*FloatToString64Ex			)(Float64 v, Int32 vvk, Int32 nnk, Bool e, Utf16Char xchar);

	UInt64					(String::*ToUInt64			)(Bool* error) const;
	UInt32					(String::*ToUInt32			)(Bool* error) const;
	Int64						(String::*ToInt64				)(Bool* error) const;
	Int32						(String::*ToInt32				)(Bool* error) const;

	Float						(String::*ToFloat				)(Bool* error) const;

	Bool						(String::*FindFirstCh		)(Utf32Char ch, Int32 *Pos, Int32 Start) const;
	Bool						(String::*FindLastCh		)(Utf32Char ch, Int32 *Pos, Int32 Start) const;
	void						(*InitArray							)(String *str, Int32 count, Utf32Char fillchr);
	String					(*RealToString					)(Float v, Int32 vk, Int32 nk, Bool e, Utf32Char xchar);
	Utf32Char					(*GetChr								)(const String *str, Int32 pos);
	void						(*SetChr								)(String *str, Int32 pos, Utf32Char chr);
	String					(*FloatToString32				)(Float32 v, Int32 vvk, Int32 nnk, Bool e, Utf32Char xchar);
	String					(*FloatToString64				)(Float64 v, Int32 vvk, Int32 nnk, Bool e, Utf32Char xchar);
	Bool						(String::*SetUtf32			)(const Utf32Char* Ubc, Int count);
	Bool						(String::*SetUtf16			)(const Utf16Char* Ubc, Int count);
	Bool						(String::*GetUtf16			)(maxon::BaseArray<Utf16Char>& dst);
	Bool						(String::*GetUtf32			)(maxon::BaseArray<Utf32Char>& dst);
};

struct C4D_Bitmap
{
	BaseBitmap*			(*Alloc								)(void);
	void						(*Free								)(BaseBitmap *bm);
	BaseBitmap*			(*GetClone						)(const BaseBitmap *src);
	Int32						(*GetBw								)(const BaseBitmap *bm);
	Int32						(*GetBh								)(const BaseBitmap *bm);
	Int32						(*GetBt								)(const BaseBitmap *bm);
	Int32						(*GetBpz							)(const BaseBitmap *bm);
	IMAGERESULT			(*Init2								)(BaseBitmap *bm, const Filename *name, Int32 frame, Bool *ismovie);
	void						(*FlushAll						)(BaseBitmap *bm);
	IMAGERESULT			(BaseBitmap::*Save		)(const Filename &name, Int32 format, const BaseContainer *data, SAVEBIT savebits) const;
	void						(*SetCMAP							)(BaseBitmap *bm, Int32 i, Int32 r, Int32 g, Int32 b);
	void						(*ScaleIt							)(const BaseBitmap *src, BaseBitmap *dst, Int32 intens, Bool sample, Bool nprop);
	void						(*SetPen							)(BaseBitmap *bm, Int32 r, Int32 g, Int32 b);
	void						(*Clear								)(BaseBitmap *bm, Int32 x1, Int32 y1, Int32 x2, Int32 y2, Int32 r, Int32 g, Int32 b);
	void						(*Line								)(BaseBitmap *bm, Int32 x1, Int32 y1, Int32 x2, Int32 y2);
	void						(*GetPixel						)(const BaseBitmap *bm, Int32 x, Int32 y, UInt16 *r, UInt16 *g, UInt16 *b);
	BaseBitmap *		(*AddChannel					)(BaseBitmap *bm, Bool internal, Bool straight);
	void						(*RemoveChannel				)(BaseBitmap *bm, BaseBitmap *channel);
	void						(*GetAlphaPixel				)(const BaseBitmap *bm, BaseBitmap *channel, Int32 x, Int32 y, UInt16 *val);
	BaseBitmap *		(*GetInternalChannel	)(BaseBitmap *bm);
	Int32						(*GetChannelCount			)(const BaseBitmap *bm);
	BaseBitmap *		(*GetChannelNum				)(BaseBitmap *bm, Int32 num);
	BaseBitmap*			(*GetClonePart				)(const BaseBitmap *src, Int32 x, Int32 y, Int32 w, Int32 h);
	Bool						(*CopyTo							)(const BaseBitmap *src, BaseBitmap *dst);
	void						(*ScaleBicubic				)(const BaseBitmap *src, BaseBitmap *dest, Int32 src_xmin, Int32 src_ymin, Int32 src_xmax, Int32 src_ymax, Int32 dst_xmin, Int32 dst_ymin, Int32 dst_xmax, Int32 dst_ymax);
	BaseBitmap*			(*GetAlphaBitmap			)(const BaseBitmap *bm, BaseBitmap *channel);

	Bool						(*IsMultipassBitmap		)(const BaseBitmap *bm);

	MultipassBitmap*(*MPB_AllocWrapperPB	)(Int32 bx, Int32 by, COLORMODE mode);
	MultipassBitmap*(*MPB_AllocWrapper		)(BaseBitmap *bmp);
	PaintBitmap*		(*MPB_GetPaintBitmap	)(MultipassBitmap *mp);
	Int32						(*MPB_GetLayerCount		)(const MultipassBitmap *mp);
	Int32						(*MPB_GetAlphaLayerCount)(const MultipassBitmap *mp);
	Int32						(*MPB_GetHiddenLayerCount)(const MultipassBitmap *mp);
	MultipassBitmap*(*MPB_GetLayerNum			)(MultipassBitmap *mp, Int32 num);
	MultipassBitmap*(*MPB_GetAlphaLayerNum)(MultipassBitmap *mp, Int32 num);
	MultipassBitmap*(*MPB_GetHiddenLayerNum)(MultipassBitmap *mp, Int32 num);
	MultipassBitmap*(*MPB_AddLayer				)(MultipassBitmap *mp, MultipassBitmap *insertafter, COLORMODE colormode, Bool hidden);
	MultipassBitmap*(*MPB_AddFolder				)(MultipassBitmap *mp, MultipassBitmap *insertafter, Bool hidden);
	MultipassBitmap*(*MPB_AddAlpha				)(MultipassBitmap *mp, MultipassBitmap *insertafter, COLORMODE colormode);
	Bool						(*MPB_DeleteLayer			)(MultipassBitmap *mp, MultipassBitmap *layer);
	MultipassBitmap*(*MPB_FindUserID			)(MultipassBitmap *mp, Int32 id, Int32 subid);
	void						(*MPB_ClearImageData	)(MultipassBitmap *mp);
	void						(*MPB_SetMasterAlpha	)(MultipassBitmap *mp, BaseBitmap *master);
	GeData					(*MPB_GetParameter		)(const MultipassBitmap *mp, MPBTYPE id);
	Bool						(*MPB_SetParameter		)(MultipassBitmap *mp, MPBTYPE id, const GeData &par);

	UInt32						(*GetDirty						)(const BaseBitmap *bm);

	void						(*GetPixelCnt					)(const BaseBitmap *bm, Int32 x, Int32 y, Int32 cnt, UChar *buffer, Int32 inc, COLORMODE dstmode, PIXELCNT flags, ColorProfileConvert *conversion);
	GeData					(*GetBaseBitmapData		)(const BaseBitmap *bm, Int32 id, const GeData &t_default);
	Bool						(*SetBaseBitmapData		)(BaseBitmap *bm, Int32 id, const GeData &data);

	void						(*SetDirty						)(BaseBitmap *bm);
	Bool						(*CopyPartTo					)(const BaseBitmap *src, BaseBitmap *dst, Int32 x, Int32 y, Int32 w, Int32 h);

	BaseBitmapLink	*(*BBL_Alloc						)(void);
	void						(*BBL_Free						)(BaseBitmapLink *link);
	BaseBitmap			*(*BBL_Get							)(BaseBitmapLink *link);
	void						(*BBL_Set							)(BaseBitmapLink *link, BaseBitmap *bmp);

	Int							(*GetMemoryInfo				)(const BaseBitmap *bmp);
	Int32						(*MPB_GetEnabledLayerCount)(const MultipassBitmap *mp);
	Bool						(*MPB_GetLayers				)(MultipassBitmap *mp, MPB_GETLAYERS flags, BaseBitmap **&list, Int32 &count);
	UChar*					(*GetDrawPortBits			)(BaseBitmap *bm);
	Bool						(*GetUpdateRegions		)(const BaseBitmap *mp, BaseContainer &regions);
	IMAGERESULT			(*Init1								)(BaseBitmap *bm, Int32 x, Int32 y, Int32 depth, INITBITMAPFLAGS flags);
	Bool						(*AddUpdateRegion			)(BaseBitmap *bm, Int32 id, Int32 type, Int32 xmin, Int32 xmax, Int32 ymin, Int32 ymax);
	Bool						(*RemoveUpdateRegion	)(BaseBitmap *bm, Int32 id);
	BaseBitmap*			(*GetUpdateRegionBitmap)(const BaseBitmap *bm);
	IMAGERESULT			(*Init3								)(BaseBitmap *&bm, const Filename &name, Int32 frame, Bool *ismovie, BitmapLoaderPlugin **loaderplugin);
	MultipassBitmap*(*MPB_GetSelectedLayer)(MultipassBitmap *mp);
	Bool						(*SetPixelCnt					)(BaseBitmap *bm, Int32 x, Int32 y, Int32 cnt, UChar *buffer, Int32 inc, COLORMODE srcmode, PIXELCNT flags);
	Bool						(*SetPixel						)(BaseBitmap *bm, Int32 x, Int32 y, Int32 r, Int32 g, Int32 b);
	Bool						(*SetAlphaPixel				)(BaseBitmap *bm, BaseBitmap *channel, Int32 x, Int32 y, Int32 val);
	void						(*MPB_FreeHiddenLayers)(MultipassBitmap *mp);
	Bool						(*SetColorProfile			)(BaseBitmap *bm, const ColorProfile *profile);
	const ColorProfile*	(*GetColorProfile	)(const BaseBitmap *bm);

	ColorProfile*		(*ProfileAlloc				)(void);
	void						(*ProfileFree					)(ColorProfile *profile);
	Bool						(*ProfileCopy					)(const ColorProfile *src, ColorProfile *dst);
	Bool						(*ProfileEqual				)(const ColorProfile *src, const ColorProfile *dst);
	const ColorProfile *(*ProfileSRGB			)();
	const ColorProfile *(*ProfileLinearRGB)();
	Bool						(*ProfileWindow				)(ColorProfile *profile, CDialog *dlg);
	Bool						(*ProfileFromFile			)(ColorProfile *profile, const Filename &fn);
	Bool						(*ProfileFromMemory		)(ColorProfile *profile, const void *mem, Int64 memsize);
	Bool						(*ProfileToMemory			)(const ColorProfile *profile, void *&mem, Int64 &memsize);
	Bool						(*ProfileToFile				)(const ColorProfile *profile, const Filename &fn);
	String					(*ProfileInfo					)(const ColorProfile *profile, Int32 info);
	Bool						(*ProfileIsMonitorMode)(const ColorProfile *profile);
	Bool						(*ProfileHasProfile		)(const ColorProfile *profile);
	Bool						(*ProfileSetMonitorMode)(ColorProfile *profile, Bool on);

	ColorProfileConvert*	(*ProfileConvAlloc)(void);
	void						(*ProfileConvFree			)(ColorProfileConvert *profile);
	Bool						(*ProfileConvTransform)(ColorProfileConvert *profile, COLORMODE srccolormode, const ColorProfile *srcprofile, COLORMODE dstcolormode, const ColorProfile *dstprofile, Bool bgr);
	void						(*ProfileConvConvert	)(const ColorProfileConvert *profile, const PIX *src, PIX *dst, Int32 cnt, Int32 SkipInputComponents, Int32 SkipOutputComponents);
	Bool						(*ProfileCheckColorMode)(const ColorProfile *profile, COLORMODE colormode);
	const ColorProfile *(*ProfileSGray		)();
	const ColorProfile *(*ProfileLinearGray)();
	Bool						(MultipassBitmap::*SetTempColorProfile)(const ColorProfile *profile, Bool dithering);
	Int32						(MultipassBitmap::*GetUserID)(void) const;

	void						(*Arc									)(BaseBitmap *bm, Int32 x, Int32 y, Float radius, Float angle_start, Float angle_end, Int32 subdiv);

	void						(MultipassBitmap::*SetUserID)(Int32 id);
	void						(MultipassBitmap::*SetUserSubID)(Int32 subid);
	void						(MultipassBitmap::*SetSave)(Bool save);
	void						(MultipassBitmap::*SetBlendMode)(Int32 mode);
	void						(MultipassBitmap::*SetName)(const String &name);
	void						(MultipassBitmap::*SetColorMode)(COLORMODE mode);
	void						(MultipassBitmap::*SetComponent)(Int32 c);
	void						(MultipassBitmap::*SetDpi)(Int32 dpi);

	String					(*MPB_GetPassName			)(Int32 id, Int32 subid, String *suggestion);
	Bool						(*MPB_SetResultBitmap)(MultipassBitmap* mp, BaseBitmap *bmp);
};

struct C4D_MovieSaver
{
	MovieSaver*			(*Alloc								)(void);
	void						(*Free								)(MovieSaver *ms);
	IMAGERESULT			(*Write								)(MovieSaver *ms, BaseBitmap *bm);
	void						(*Close								)(MovieSaver *ms);
	Bool						(*Choose							)(MovieSaver *ms, Int32 id, BaseContainer *bc);
	IMAGERESULT			(*Open								)(MovieSaver *ms, const Filename *name, BaseBitmap *bm, Int32 fps, Int32 id, const BaseContainer *data, SAVEBIT savebits, BaseSound *sound);
};

struct C4D_BaseChannel
{
	BaseChannel*		(*Alloc								)(void);
	void						(*Free								)(BaseChannel *bc);
	Bool						(*Compare							)(BaseChannel *bc1, BaseChannel *bc2);
	INITRENDERRESULT(*InitTexture					)(BaseChannel *bc, const InitRenderStruct &irs);
	void						(*FreeTexture					)(BaseChannel *bc);
	Vector					(*BcSample						)(BaseChannel *bc, VolumeData *vd, Vector *p, Vector *delta, Vector *n, Float t, Int32 tflag, Float off, Float scale);
	BaseBitmap*			(*BCGetBitmap					)(BaseChannel *bc);
	void						(*GetData							)(BaseChannel *bc, BaseContainer *ct);
	void						(*SetData							)(BaseChannel *bc, const BaseContainer *ct);
	Bool						(*ReadData						)(HyperFile *hf, BaseChannel *bc);
	Bool						(*WriteData						)(HyperFile *hf, BaseChannel *bc);

	Int32						(*GetPluginID					)(BaseChannel *bc);
	BaseShader*		(*GetPluginShader			)(BaseChannel *bc);

	Bool						(*Attach							)(BaseChannel *bc, GeListNode *element);

	Bool						(*HandleShaderPopup			)(const BaseContainer &bc, const DescID &descid, Int32 value, Int param);
	Bool						(*HandleShaderPopupI		)(BaseList2D *parent, BaseShader *&current, Int32 value, Int param);
	Bool						(*BuildShaderPopupMenu	)(BaseContainer *menu, const BaseContainer &bc, const DescID &descid, Int param);
	Bool						(*BuildShaderPopupMenuI	)(BaseContainer *menu, BaseList2D *parent, BaseShader *current, Int param);

	void						(*HandleShaderMessage	)(GeListNode *node, BaseShader *ps, Int32 type, void *data);
	Bool						(*ReadDataConvert			)(GeListNode *node, Int32 id, HyperFile *hf);

	INITRENDERRESULT(BaseShader::*InitRender		)(const InitRenderStruct &irs);
	void						(BaseShader::*FreeRender		)(void);
	Vector					(BaseShader::*Sample				)(ChannelData *vd);
	Vector					(BaseShader::*SampleBump		)(ChannelData *vd, SAMPLEBUMP bumpflags);
	BaseBitmap*			(BaseShader::*GetBitmap			)(void);
	SHADERINFO			(BaseShader::*GetRenderInfo	)(void);

	BaseShader*			(*PsAlloc										)(Int32 type);
	Bool						(BaseShader::*PsCompare			)(BaseShader* dst);

	String					(*GetChannelName						)(Int32 channelid);
	GL_MESSAGE			(BaseShader::*GlMessage			)(Int32 type, void *data);
	Bool						(BaseShader::*IsColorManagementOff)(BaseDocument *doc);
	void						(BaseShader::*DestroyGLImage)(BaseDocument* doc);
	void						(BaseShader::*InvalidateGLImage)(BaseDocument* doc);
	BaseShader*			(BaseShader::*GetSubsurfaceShader)(Float &bestmpl);
};

struct C4D_Filename
{
	Filename				*Default; // Safety value

	Filename*				(*Alloc								)(void);
	Filename*				(*GetClone						)(const Filename *fn);
	void						(*Free								)(Filename *fn);
	Bool						(Filename::*FileSelect)(FILESELECTTYPE type, FILESELECT flags, const String &title, const String &force_suffix);
	Bool						(*Content							)(const Filename *fn);
	const String		(*GetString						)(const Filename *fn);
	void						(*SetString						)(Filename *fn, const String *str);
	const Filename	(*GetDirectory				)(const Filename *fn);
	const Filename	(*GetFile							)(const Filename *fn);
	void						(*ClearSuffix					)(Filename *fn);
	void						(*SetSuffix						)(Filename *fn, const String *str);
	Bool						(*CheckSuffix					)(const Filename *fn, const String *str);
	void						(*SetDirectory				)(Filename *fn, const Filename *str);
	void						(*SetFile							)(Filename *fn, const Filename *str);
	Bool						(*Compare							)(const Filename *fn1, const Filename *fn2);
	void						(*Add									)(Filename *dst, const Filename *src);

	void						(*Init								)(Filename *fn);
	void						(*Flush								)(Filename *fn);
	void						(*CopyTo							)(const Filename *src, Filename *dst);
	void						(*SetMemoryReadMode		)(Filename *fn, void *adr, Int size, Bool transferOwnership);
	void						(*SetMemoryWriteMode	)(Filename *fn, MemoryFileStruct *mfs);

	MemoryFileStruct*	(*MemoryFileStructAlloc)();
	void						(*MemoryFileStructFree)(MemoryFileStruct *&mfs);
	void						(*MemoryFileStructGetData)(MemoryFileStruct *mfs, void *&data, Int &size, Bool release);
	void						(*SetCString					)(Filename *fn, const Char *str);
	void						(*ClearSuffixComplete	)(Filename *fn);

	void						(Filename::*SetIpConnection)(NetworkIpConnection *ipc);
	NetworkIpConnection*		(Filename::*GetIpConnection)() const;

	const String		(*GetSuffix						)(const Filename *fn);
	Bool						(Filename::*IsBrowserUrl)() const;
	const MemoryFileStruct*	(Filename::*GetMemoryModeI)() const;
};

struct C4D_BrowseFiles
{
	BrowseFiles*		(*Alloc								)(const Filename *dir, Int32 flags);
	void						(*Free								)(BrowseFiles *bf);
	void						(*Init								)(BrowseFiles *bf, const Filename *dir, Int32 flags);

	Bool						(BrowseFiles::*GetNext				)(void);
	Filename				(BrowseFiles::*GetFilename		)(void);
	Bool						(BrowseFiles::*IsDir					)(void);
	Int64						(BrowseFiles::*GetSize				)(void);
	void						(BrowseFiles::*GetFileTime		)(Int32 mode, LocalFileTime *out);
	Bool						(BrowseFiles::*IsHidden				)(void);
	Bool						(BrowseFiles::*IsReadOnly			)(void);
	Bool						(BrowseFiles::*IsBundle				)(void);

	BrowseVolumes*	(*BvAlloc							)(void);
	void						(*BvFree							)(BrowseVolumes *bv);
	void						(BrowseVolumes::*BvInit				)(void);
	Bool						(BrowseVolumes::*BvGetNext		)(void);
	Filename				(BrowseVolumes::*BvGetFilename)(void);
	String					(BrowseVolumes::*BvGetVolumeName)(Int32 *out_flags);
};

struct C4D_File
{
	BaseFile*				(*Alloc								)(void);
	void						(*Free								)(BaseFile *fl);
	AESFile*				(*AESAlloc						)(void);
	Bool						(*AESCheckEncryption	)(const Filename& encrypt, const Filename& decrypt, const char* key, Int32 keylen, Int32 blocksize);

	Bool						(BaseFile::*Open							)(const Filename &name, FILEOPEN mode, FILEDIALOG error_dialog, BYTEORDER order, Int32 type, Int32 creator);
	Bool						(BaseFile::*Close							)();
	void						(BaseFile::*SetOrder					)(BYTEORDER order);
	Int						(BaseFile::*ReadBytes						)(void *data, Int len, Bool just_try_it);
	Bool						(BaseFile::*WriteBytes				)(const void *data, Int len);
	Bool						(BaseFile::*Seek							)(Int64 pos, FILESEEK mode);
	Int64						(BaseFile::*GetPosition				)();
	Int64						(BaseFile::*GetLength					)();
	FILEERROR				(BaseFile::*GetError					)() const;
	void						(BaseFile::*SetError					)(FILEERROR error);
	Bool						(BaseFile::*WriteChar					)(Char v);
	Bool						(BaseFile::*WriteUChar				)(UChar v);
	Bool						(BaseFile::*WriteInt16				)(Int16 v);
	Bool						(BaseFile::*WriteUInt16				)(UInt16 v);
	Bool						(BaseFile::*WriteInt32				)(Int32 v);
	Bool						(BaseFile::*WriteUInt32				)(UInt32 v);
	Bool						(BaseFile::*WriteFloat32			)(Float32 v);
	Bool						(BaseFile::*WriteFloat64			)(Float64 v);
	Bool						(BaseFile::*ReadChar					)(Char *v);
	Bool						(BaseFile::*ReadUChar					)(UChar *v);
	Bool						(BaseFile::*ReadInt16					)(Int16 *v);
	Bool						(BaseFile::*ReadUInt16				)(UInt16 *v);
	Bool						(BaseFile::*ReadInt32					)(Int32 *v);
	Bool						(BaseFile::*ReadUInt32				)(UInt32 *v);
	Bool						(BaseFile::*ReadFloat32				)(Float32 *v);
	Bool						(BaseFile::*ReadFloat64				)(Float64 *v);
	Bool						(BaseFile::*ReadInt64					)(Int64 *v);
	Bool						(BaseFile::*WriteInt64				)(Int64 v);

	Bool						(AESFile::*AESOpen						)(const Filename &name, const char* key, Int32 keylen, Int32 blocksize, UInt32 aes_flags, FILEOPEN mode, FILEDIALOG error_dialog, BYTEORDER order, Int32 type, Int32 creator);
	Bool						(BaseFile::*ReadUInt64				)(UInt64 *v);
	Bool						(BaseFile::*WriteUInt64				)(UInt64 v);
	LOCATION				(BaseFile::*GetLocation				)() const;
};

struct C4D_Dialog
{
	CDialog*				(*Alloc									)(CDialogMessage *dlgfunc, void *userdata);
	void						(*Free									)(CDialog *cd);
	void*						(*GetUserData						)(CDialog *cd);
	Bool						(*Close									)(CDialog *cd);
	Bool						(*Enable								)(CDialog *cd, Int32 id, Bool enabled, void *gadptr);
	void						(*SetTimer							)(CDialog *cd, Int32 timer);
	Bool						(*SetInt32							)(CDialog *cd, Int32 id, Int32 value, Int32 min, Int32 max, Int32 step, void *gadptr);
	Bool						(*SetFloat							)(CDialog *cd, Int32 id, Float value, Float min, Float max, Float step, Int32 format, void *gadptr);
	Bool						(*SetVector							)(CDialog *cd, Int32 id, const Vector &value, void *gadptr);
	Bool						(*SetString							)(CDialog *cd, Int32 id, const String *text, void *gadptr);
	Bool						(*SetColorField					)(CDialog *cd, Int32 id, const Vector &color, Float brightness, Float maxbrightness, Int32 flags, void *gadptr);
	Bool						(*GetInt32							)(CDialog *cd, Int32 id, Int32 &value, void *gadptr);
	Bool						(*GetFloat							)(CDialog *cd, Int32 id, Float &value, void *gadptr);
	Bool						(*GetVector							)(CDialog *cd, Int32 id, Vector &value, void *gadptr);
	Bool						(*GetString							)(CDialog *cd, Int32 id, String *&text, void *gadptr);
	Bool						(*GetColorField					)(CDialog *cd, Int32 id, Vector &color, Float &brightness, void *gadptr);
	Bool						(*LoadDialogResource		)(CDialog *cd, Int32 id, LocalResource *lr, Int32 flags);
	Bool						(*TabGroupBegin					)(CDialog *cd, Int32 id, Int32 flags, Int32 tabtype);
	Bool						(*GroupBeginEx					)(CDialog *cd, Int32 id, Int32 flags, Int32 cols, Int32 rows, const String *title, Int32 groupflags);
	Bool						(*GroupSpace						)(CDialog *cd, Int32 spacex, Int32 spacey);
	Bool						(*GroupBorder						)(CDialog *cd, UInt32 borderstyle);
	Bool						(*GroupBorderSize				)(CDialog *cd, Int32 left, Int32 top, Int32 right, Int32 bottom);
	Bool						(*GroupEnd							)(CDialog *cd);
	Bool						(*SetPopup							)(CDialog *cd, Int32 id, const BaseContainer *bc, void *gadptr);
	Bool						(*Screen2Local					)(CDialog *cd, Int32 *x, Int32 *y);
	Bool						(*SetVisibleArea				)(CDialog *cd, Int32 scrollgroupid, Int32 x1, Int32 y1, Int32 x2, Int32 y2);
	Bool						(*GetItemDim						)(CDialog *cd, Int32 id, Int32 *x, Int32 *y, Int32 *w, Int32 *h, void *gadptr);
	Bool						(*SendRedrawThread			)(CDialog *cd, Int32 id);
	Bool						(*GetVisibleArea				)(CDialog *cd, Int32 id, Int32 *x1, Int32 *y1, Int32 *x2, Int32 *y2);
	Bool						(*RestoreLayout					)(CDialog *cd, void *secret);
	Bool						(*SetMessageResult			)(CDialog *cd, const BaseContainer *result);

	Bool						(*SetDragDestination		)(CDialog *cd, Int32 cursor);
	Bool						(*AttachSubDialog				)(CDialog *parentcd, Int32 id, CDialog *cd);
	Int32						(*GetID									)(CDialog *cu);
	void*						(*FindCustomGui					)(CDialog *cd, Int32 id);
	Bool						(*AddGadget							)(CDialog *cd, Int32 type, Int32 id, const String *name, Int32 par1, Int32 par2, Int32 par3, Int32 par4, const BaseContainer *customdata, void **resptr);
	Bool						(*ReleaseLink						)(CDialog *cd);
	Bool						(*SendParentMessage			)(CDialog *cd, const BaseContainer *msg);

	Bool						(*Open									)(CDialog *cd, DLG_TYPE dlgtype, CDialog *parent, Int32 xpos, Int32 ypos, Int32 defaultw, Int32 defaulth);
	CUserArea*			(*AttachUserArea				)(CDialog *cd, Int32 id, void *userdata, USERAREAFLAGS userareaflags, void *gadptr);
	Bool						(*GetDragObject					)(CDialog *cd, const BaseContainer *msg, Int32 *type, void **object);

	LassoSelection*	(*LSAlloc								)(void);
	void						(*LSFree								)(LassoSelection *ls);
	Int32						(*LSGetMode							)(LassoSelection *ls);
	Bool						(*LSTest								)(LassoSelection *ls, Int32 x, Int32 y);
	Bool						(*LSCheckSingleClick		)(LassoSelection *ls);
	Bool						(*LSStart								)(LassoSelection *ls, CBaseFrame *cd, Int32 mode, Int32 start_x, Int32 start_y, Int32 start_button, Int32 sx1, Int32 sy1, Int32 sx2, Int32 sy2);
	Bool						(*LSTestPolygon					)(LassoSelection *ls, const Vector &pa, const Vector &pb, const Vector &pc, const Vector &pd);

	CBaseFrame*			(*CBF_FindBaseFrame			)(CDialog *cd, Int32 id);
	Bool						(*CBF_SetDragDestination)(CBaseFrame *cbf, Int32 cursor);
	void*						(*CBF_GetWindowHandle		)(CBaseFrame *cbf);
	GeData					(*SendUserAreaMessage		)(CDialog *cd, Int32 id, BaseContainer *msg, void *gadptr);
	Bool						(*LSGetRectangle				)(LassoSelection *ls, Float &x1, Float &y1, Float &x2, Float &y2);
	Bool						(*CBF_GetColorRGB				)(CBaseFrame *cbf, Int32 colorid, Int32 &r, Int32 &g, Int32 &b);
	Bool						(*RemoveLastCursorInfo	)(LASTCURSORINFOFUNC func);
	String					(*Shortcut2String				)(Int32 shortqual, Int32 shortkey);

	Bool						(*GetIconCoordInfo			)(Int32 &id, const Char* ident);
	Bool						(*GetInterfaceIcon			)(Int32 type, Int32 id_x, Int32 id_y, Int32 id_w, Int32 id_h, IconData &d);
	Bool						(*IsEnabled							)(CDialog *cd, Int32 id, void *gadptr);
	GeClipMap*			(*GetInterfaceScheme		)(Int32 type);
	Bool						(*GroupBegin						)(CDialog *cd, Int32 id, Int32 flags, Int32 cols, Int32 rows, const String *title, Int32 groupflags, Int32 minx, Int32 miny);
	void						(*CBF_ActivateFading		)(CBaseFrame *cbf, Int32 milliseconds);
	void						(*CBF_AdjustColor				)(CBaseFrame *cbf, Int32 colorid, Int32 highlightid, Float percent);
};

struct C4D_UserArea
{
	void						(*Free								)(CUserArea* cu);
	void*						(*GetUserData					)(CUserArea *cu);
	Int32						(*GetWidth						)(CUserArea *cu);
	Int32						(*GetHeight						)(CUserArea *cu);
	Int32						(*GetID								)(CUserArea *cu);
	void						(*SetMinSize					)(CUserArea *cu, Int32 w, Int32 h);
	void						(*DrawLine						)(CUserArea *cu, Int32 x1, Int32 y1, Int32 x2, Int32 y2);
	void						(*DrawRectangle				)(CUserArea *cu, Int32 x1, Int32 y1, Int32 x2, Int32 y2);
	void						(*DrawSetPenV					)(CUserArea *cu, const Vector &color);
	void						(*DrawSetPenI					)(CUserArea *cu, Int32 id);
	void						(*SetTimer						)(CUserArea *cu, Int32 timer);
	Bool						(*GetInputState				)(CBaseFrame *cu, Int32 askdevice, Int32 askchannel, BaseContainer *res);
	Bool						(*GetInputEvent				)(CBaseFrame *cu, Int32 askdevice, BaseContainer *res);
	void						(*KillEvents					)(CBaseFrame *cu);
	void						(*DrawSetFont					)(CUserArea *cu, Int32 fontid);
	Int32						(*DrawGetTextWidth		)(CUserArea *cu, const String *text);
	Int32						(*DrawGetFontHeight		)(CUserArea *cu);
	void						(*DrawSetTextColII		)(CUserArea *cu, Int32 fg, Int32 bg);
	void						(*DrawSetTextColVI		)(CUserArea *cu, const Vector &fg, Int32 bg);
	void						(*DrawSetTextColIV		)(CUserArea *cu, Int32 fg, const Vector &bg);
	void						(*DrawSetTextColVV		)(CUserArea *cu, const Vector &fg, const Vector &bg);
	void						(*DrawBitmap					)(CUserArea *cu, BaseBitmap *bmp, Int32 wx, Int32 wy, Int32 ww, Int32 wh, Int32 x, Int32 y, Int32 w, Int32 h, Int32 mode);
	void						(*SetClippingRegion		)(CUserArea *cu, Int32 x, Int32 y, Int32 w, Int32 h);
	void						(*ScrollArea					)(CUserArea *cu, Int32 xdiff, Int32 ydiff, Int32 x, Int32 y, Int32 w, Int32 h);
	void						(*ClearClippingRegion )(CUserArea *cu);
	Bool						(*OffScreenOn					)(CUserArea *cu);

	Bool						(*Global2Local				)(CBaseFrame *cu, Int32 *x, Int32 *y);
	Bool						(*SendParentMessage		)(CUserArea *cu, const BaseContainer *msg);

	Bool						(*Screen2Local				)(CBaseFrame *cu, Int32 *x, Int32 *y);
	Bool						(*SetDragDestination	)(CUserArea *cu, Int32 cursor);
	Bool						(*HandleMouseDrag			)(CUserArea *cu, const BaseContainer *msg, Int32 type, void *data, Int32 dragflags);
	Bool						(*IsEnabled						)(CUserArea *cu);

	void						(*GetBorderSize				)(CUserArea *cu, Int32 type, Int32 *l, Int32 *t, Int32 *r, Int32 *b);
	void						(*DrawBorder					)(CUserArea *cu, Int32 type, Int32 x1, Int32 y1, Int32 x2, Int32 y2);

	_GeListView*		(*GeListView_Alloc						)(void);
	void						(*GeListView_Free							)(_GeListView *lv);
	Bool						(*GeListView_Attach						)(_GeListView *lv, CDialog *cd, Int32 id, ListViewCallBack *callback, void *userdata);
	void						(*GeListView_LvSuperCall			)(_GeListView *lv, Int32 &res_type, void *&result, void *secret, Int32 cmd, Int32 line, Int32 col);
	void						(*GeListView_Redraw						)(_GeListView *lv);
	void						(*GeListView_DataChanged			)(_GeListView *lv);
	Bool						(*GeListView_ExtractMouseInfo )(_GeListView *lv, void *secret, MouseDownInfo &info, Int32 size);
	Bool						(*GeListView_ExtractDrawInfo	)(_GeListView *lv, void *secret, DrawInfo &info, Int32 size);
	Bool						(*GeListView_SendParentMessage)(_GeListView *lv, const BaseContainer *msg);
	Int32						(*GeListView_GetId						)(_GeListView *lv);
	void						(*GeListView_ShowCell					)(_GeListView *lv, Int32 line, Int32 col);

	_SimpleListView*	(*SimpleListView_Alloc				)(void);
	void							(*SimpleListView_Free					)(_SimpleListView *lv);
	Bool							(*SimpleListView_SetLayout		)(_SimpleListView *lv, Int32 columns, const BaseContainer &data);
	Bool							(*SimpleListView_SetItem			)(_SimpleListView *lv, Int32 id, const BaseContainer &data);
	Bool							(*SimpleListView_GetItem			)(_SimpleListView *lv, Int32 id, BaseContainer *data);
	Int32							(*SimpleListView_GetItemCount	)(_SimpleListView *lv);
	Bool							(*SimpleListView_GetItemLine	)(_SimpleListView *lv, Int32 num, Int32 *id, BaseContainer *data);
	Bool							(*SimpleListView_RemoveItem		)(_SimpleListView *lv, Int32 id);
	Int32							(*SimpleListView_GetSelection	)(_SimpleListView *lv, BaseSelect *selection);
	Bool							(*SimpleListView_SetSelection	)(_SimpleListView *lv, BaseSelect *selection);
	void							(*SimpleListView_ShowCell			)(_SimpleListView *lv, Int32 line, Int32 col);

	Int32						(*SimpleListView_GetProperty	)(_SimpleListView *lv, Int32 id);
	Bool						(*SimpleListView_SetProperty	)(_SimpleListView *lv, Int32 id, Int32 val);

	Int32						(*IsHotkeyDown								)(CUserArea *cu, Int32 id);
	Bool						(*HasFocus										)(CUserArea *cu);

	void						(*MouseDragStart							)(CUserArea *cu, Int32 Button, Float mx, Float my, MOUSEDRAGFLAGS flag);
	MOUSEDRAGRESULT	(*MouseDrag										)(CUserArea *cu, Float *mx, Float *my, BaseContainer *channels);
	MOUSEDRAGRESULT	(*MouseDragEnd								)(CUserArea *cu);
	Int32						(*DrawGetTextWidth_ListNodeName)(CUserArea *cu, BaseList2D *node, Int32 fontid);
	Bool						(*OffScreenOnRect							)(CUserArea *cu, Int32 x, Int32 y, Int32 w, Int32 h);
	void						(*DrawText										)(CUserArea *cu, const String &txt, Int32 x, Int32 y, Int32 flags);
	void						(*DrawSetTextRotation					)(CUserArea *cu, Float textrotation);
	Int32						(*DrawGetFontBaseLine					)(CUserArea *cu);
	Bool						(*Local2Global								)(CBaseFrame *cu, Int32 *x, Int32 *y);
	Bool						(*Local2Screen								)(CBaseFrame *cu, Int32 *x, Int32 *y);
	void						(*DrawBezier									)(CUserArea *cu, Float sx, Float sy, Float *p, Int32 count, Bool closed, Bool filled);
	Bool						(*IsR2L												)(CUserArea *cu);
	Float						(*GetPixelRatio								)(const CBaseFrame *cu);
};

struct C4D_Parser
{
	Parser*					(*Alloc												)(void);
	void						(*Free												)(Parser *pr);
	Bool						(*Eval												)(Parser *pr, const String *str, Int32 *error, Float *res, Int32 unit, Int32 angletype, Int32 basis);
	Bool						(*EvalLong										)(Parser *pr, const String *str, Int32 *error, Int32 *res, Int32 unit, Int32 basis);
	Bool						(*AddVar											)(Parser *pr, const String *str, Float *value, Bool case_sensitive);
	Bool						(*AddVarLong									)(Parser *pr, const String *str, Int32 *value, Bool case_sensitive);
	Bool						(*RemoveVar										)(Parser *pr, const String *s, Bool case_sensitive);
	Bool						(*RemoveAllVars								)(Parser *pr);
	void						(*GetParserData								)(Parser *pr, ParserCache *p);
	Bool						(*Init												)(Parser *pr, const String *s, Int32 *error, Int32 unit, Int32 angle_unit, Int32 base);
	Bool						(*ReEval											)(Parser *pr, Float *result, Int32 *error);
	Bool						(*Calculate										)(Parser *pr, const ParserCache *pdat, Float *result, Int32 *error);
	Bool						(*ReEvalLong									)(Parser *pr, Int32 *result, Int32 *error);
	Bool						(*CalculateLong								)(Parser *pr, const ParserCache *pdat, Int32 *result, Int32 *error);
	Bool						(*Reset												)(Parser *pr, ParserCache *p);
	ParserCache*		(*AllocPCache									)(void);
	void						(*FreePCache									)(ParserCache *p);
	Bool						(*CopyPCache									)(ParserCache *p, ParserCache *d);
	Bool						(*GenerateShaderCode					)(Parser *pr, const String& resultVariableName, String *result);
	Bool						(*GenerateShaderCodeFromCache	)(Parser *pr, const ParserCache *d, const String& resultVariableName, String *result);
};

struct C4D_Resource
{
	LocalResource*	(*Alloc								)(const Filename *path);
	void						(*FreeEx							)(LocalResource *lr);
	LocalResource*	(*GetCinemaResource		)(void);
	const String&		(*LoadString					)(LocalResource *lr, Int32 id);

	BaseContainer*	(*GetMenuResource			)(const String &menuname);
	void						(*UpdateMenus					)(void);
	Bool						(*ReloadResource			)(LocalResource *lr, const Filename *path);

	void						(*Free								)(LocalResource *lr, Bool regardIsStopped);
};

struct C4D_Atom
{
	C4DAtom*				(C4DAtom::*GetClone							)(COPYFLAGS flags, AliasTrans *trn);
	Bool						(C4DAtom::*CopyTo								)(C4DAtom *dst, COPYFLAGS flags, AliasTrans *trn);
	Int32						(C4DAtom::*GetType							)(void) const;
	Bool						(C4DAtom::*IsInstanceOf					)(Int32 id) const;
	Bool						(C4DAtom::*Message							)(Int32 type, void *data);
	Bool						(C4DAtom::*MultiMessage					)(MULTIMSG_ROUTE flags, Int32 type, void *data);
	Bool						(C4DAtom::*GetDescription				)(Description &res, DESCFLAGS_DESC flags);
	Bool						(C4DAtom::*GetParameter					)(const DescID &id, GeData &t_data, DESCFLAGS_GET flags);
	Bool						(C4DAtom::*SetParameter					)(const DescID &id, const GeData &t_data, DESCFLAGS_SET flags);
	DynamicDescription*		(C4DAtom::*GetDynamicDescription)();

	GeListNode*			(GeListNode::*GetNext					)(void) const;
	GeListNode*			(GeListNode::*GetPred					)(void) const;
	GeListNode*			(GeListNode::*GetUp						)(void) const;
	GeListNode*			(GeListNode::*GetDown					)(void) const;
	GeListNode*			(GeListNode::*GetDownLast			)(void) const;
	void						(GeListNode::*InsertBefore		)(GeListNode *bl);
	void						(GeListNode::*InsertAfter			)(GeListNode *bl);
	void						(GeListNode::*InsertUnder			)(GeListNode *bl);
	void						(GeListNode::*InsertUnderLast	)(GeListNode *bl);
	void						(GeListNode::*Remove					)(void);
	GeListHead*			(GeListNode::*GetListHead			)(void);
	BaseDocument*		(GeListNode::*GetDocument			)(void) const;

	GeListNode*			(GeListHead::*GetFirst				)(void) const;
	GeListNode*			(GeListHead::*GetLast					)(void) const;
	void						(GeListHead::*FlushAll				)(void);
	void						(GeListHead::*InsertFirst			)(GeListNode *bn);
	void						(GeListHead::*InsertLast			)(GeListNode *bn);
	void						(GeListHead::*SetParent				)(GeListNode *parent);
	GeListNode*			(GeListHead::*GetParent				)(void) const;

	BaseList2D*			(BaseList2D::*GetMain					)(void) const;
	const String&		(BaseList2D::*GetName					)(void) const;
	void						(BaseList2D::*SetName					)(const String &str);
	Bool						(BaseList2D::*GetAnimatedParameter)(const DescID &id, GeData &t_data1, GeData &t_data2, Float &mix, DESCFLAGS_GET flags);
	Bool						(BaseList2D::*Scale						)(Float scale);

	// AtomArray
	AtomArray*			(*AtomArrayAlloc							)();
	void						(*AtomArrayFree								)(AtomArray *&obj);
	Int32						(AtomArray::*GetCount					)() const;
	C4DAtom *				(AtomArray::*GetIndex					)(Int32 idx) const;
	Bool						(AtomArray::*Append						)(C4DAtom *obj);
	void						(AtomArray::*Flush						)();
	Bool						(AtomArray::*AACopyTo					)(AtomArray *dest) const;

	Int32						(AtomArray::*AAGetUserID			)() const;
	void						(AtomArray::*AASetUserID			)(Int32 t_userid);

	void*						(AtomArray::*AAGetUserData		)() const;
	void						(AtomArray::*AASetUserData		)(void *t_userdata);

	C4DAtom*				(AtomArray::*AAGetPreferred		)() const;
	void						(AtomArray::*AASetPreferred		)(C4DAtom *t_preferred);

	BaseShader*			(BaseList2D::*GetFirstShader	)() const;
	void						(BaseList2D::*InsertShader		)(BaseShader *shader, BaseShader *pred);

	Bool						(BaseList2D::*SetAnimatedParameter	)(CTrack *track, const DescID &id, const GeData &t_data1, const GeData &t_data2, Float mix, DESCFLAGS_SET flags);
	void						(AtomArray::*AAFilterObject					)(Int32 type, Int32 instance, Int32 generators);
	Bool						(AtomArray::*AACopyToFilter					)(AtomArray *dest, Int32 type, Int32 instance, Int32 generators) const;
	Bool						(AtomArray::*AAAppendArr						)(AtomArray *src);
	void						(AtomArray::*AAFilterObjectChildren	)();
	Bool						(AtomArray::*AARemove								)(C4DAtom *obj);

	Bool						(C4DAtom::*GetEnabling							)(const DescID &id, const GeData &t_data, DESCFLAGS_ENABLE flags, const BaseContainer *itemdesc);
	Int32						(AtomArray::*AAGetCountTI						)(Int32 type, Int32 instance) const;

	Bool						(GeListNode::*IsDocumentRelated	)(void) const;
	Int32						(AtomArray::*AAFind							)(C4DAtom *obj) const;
	Bool						(GeListNode::*GetNBit						)(NBIT bit) const;
	Bool						(GeListNode::*ChangeNBit				)(NBIT bit, NBITCONTROL bitmode);
	Int32						(GeListNode::*GetBranchInfo			)(BranchInfo *info, Int32 max, GETBRANCHINFO flags);
	Int32						(C4DAtom::*GetClassification		)(void) const;
	Bool						(BaseList2D::*TransferMarker		)(BaseList2D *dst) const;
	const GeMarker&	(BaseList2D::*GetMarker					)(void) const;
	void						(BaseList2D::*SetMarker					)(const GeMarker &m);
	GeMarker*				(*GeMarkerAlloc									)();
	void						(*GeMarkerFree									)(GeMarker *&obj);
	Bool						(GeMarker::*IsEqual							)(const GeMarker &m) const;
	Bool						(GeMarker::*Content							)() const;
	Int32						(C4DAtom::*GetRealType					)(void) const;
	Int32						(GeMarker::*Compare							)(const GeMarker &m) const;
	void						(GeMarker::*GeMarkerSet					)(const GeMarker &m);
	Bool						(GeMarker::*GeMarkerRead				)(HyperFile *hf);
	Bool						(GeMarker::*GeMarkerWrite				)(HyperFile *hf) const;
	Bool						(BaseList2D::*TransferGoal			)(BaseList2D *dst, Bool undolink);
	void						(GeMarker::*GeMarkerGetMemory		)(void *&data, Int32 &size) const;
	Bool						(BaseList2D::*AddUniqueID				)(Int32 appid, const Char *const mem, Int bytes);
	Bool						(BaseList2D::*FindUniqueID			)(Int32 appid, const Char *&mem, Int &bytes) const;
	Int32						(BaseList2D::*GetUniqueIDCount	)() const;
	Bool						(BaseList2D::*GetUniqueIDIndex	)(Int32 idx, Int32 &id, const Char *&mem, Int &bytes) const;
	Bool						(C4DAtom::*TranslateDescID			)(const DescID &id, DescID &res_id, C4DAtom *&res_at);

	Bool						(AtomArray::*AACompareArr			)(AtomArray *cmp);
};

struct C4D_Coffee
{
	Coffee*					(*GeCoffeeAlloc								)();
	void						(*GeCoffeeFree								)(Coffee* &cof);
	Bool						(*GeCoffeeCompileString				)(Coffee* cof, const String& src);
	Bool						(*GeCoffeeCompileFile					)(Coffee* cof, const Filename& file);
	VALUE*					(*GeCoffeeAddGlobalSymbol			)(Coffee* cof, const String& name);
	VALUE*					(*GeCoffeeFindGlobalSymbol		)(Coffee* cof, const String& name);
	Bool						(*GeCoffeeExecute							)(Coffee* cof, VALUE* func, GeData* retval, GeData* arg1, GeData* arg2, GeData* arg3);
	Bool						(*GeCoffeeGeData2Value				)(Coffee* cof, const GeData& src, VALUE* dest);
	Bool						(*GeCoffeeValue2GeData				)(Coffee* cof, VALUE *src, GeData* dest);
	Bool						(*GeCoffeeGetLastError				)(Coffee* cof, String *err_string, Int32 *err_line, Int32 *err_pos);
	Bool						(*CodeEditor_OpenEx						)(BaseList2D *obj, CodeEditorCallback *callback);

	VALUE*					(*CoValGetObjMember						)(VALUE *val, Int32 nr);
	VALUE*					(*CoValGetArrayMember					)(VALUE *val, Int32 i);
	void						(*CoValSetArray								)(VALUE *val, ARRAY *a);
	OBJECT*					(*CoValGetObject							)(VALUE *val, Int32 *err);
	void						(*CoValSetObject							)(VALUE *val, OBJECT *o);
	void						(*CoValSetString							)(VALUE *val, CSTRING *s);
	String					(*CoValGetString							)(VALUE *val);
	Bool						(*CoValIsInstanceOf						)(VALUE *val, VALUE *cl, Int32 *err);
	Int32						(*CoValGetSize								)(VALUE *val);
	UChar*					(*CoValGetBytes								)(VALUE *val);

	VALUE*					(*CoGetGlobalClass						)(Coffee* cof, const String &name);
	CLASS*					(*CoAddGlobalClass						)(Coffee* cof, const String &name, const String &parent);
	Bool						(*CoAddGlobalSymbol						)(Coffee* cof, const String &name, const VALUE *v, Int32 type);
	Bool						(*CoAddGlobalFunction					)(Coffee* cof, const String &name, V_CODE fcn);
	Bool						(*CoAddClassMember						)(Coffee* cof, const String &name, CLASS *c, Int32 type);
	Bool						(*CoAddClassMethod						)(Coffee* cof, const String &name, CLASS *c, Int32 type, V_CODE fcn, Int32 argc);
	CSTRING*				(*CoAllocString								)(Coffee* cof, const String &s);
	OBJECT*					(*CoNewObject									)(Coffee* cof, const String &cl_name);
	ARRAY*					(*CoNewArray									)(Coffee* cof, Int32 size);
	void						(*CoWrongcnt									)(Coffee* cof, Int32 n, Int32 cnt);
	void						(*CoErrCheckType							)(Coffee* cof, VALUE *v, Int32 type, Int32 *err);
	void						(*CoErrCheckObjectType				)(Coffee* cof, VALUE *v, const String &cl_name, Int32 *err);
	void						(*CoErrCheckArgCount					)(Coffee* cof, Int32 argc, Int32 cnt, Int32 *err);
	Int32						(*CoGetType										)(Coffee* cof);
	const Filename&	(*CoGetRootFile								)(Coffee* cof);
	OBJECT*					(*CoAllocDynamic							)(Coffee* cof, BaseList2D *bl, Bool coffeeallocation);
	CLASS*					(*CoAddInheritance						)(Coffee* cof, Int32 id, const String &name, const String &from, Bool use_constructor);
	Coffee*					(*CoGetMaster									)(void);
	void						(*CoSetError									)(Coffee* cof, Int32 type, const String &s1, const String &s2);
	void						(*CoInstallErrorHook					)(Coffee* cof, COFFEE_ERRORHANDLER *priv_hndl, void *priv_data);
	void						(*CoSetRootFile								)(Coffee* cof, const Filename &fn);
	Bool						(*CoCompileFile								)(Coffee* cof, const Filename &fn, Bool tofile);
	Bool						(*CodeEditor_Open							)(BaseList2D *obj, CodeEditorCallback *callback, const BaseContainer &bc);
};

struct C4D_BaseList
{
	Int32						(*GetDiskType					)(const C4DAtom *at);
	void						(*GetMarker						)(BaseList2D *bl, UInt32 *l1, UInt32 *l2);
	void						(*SetAllBits					)(BaseList2D *bl, Int32 mask);
	Int32						(*GetAllBits					)(const BaseList2D *bl);
	void						(*Free								)(C4DAtom *at);
	Bool						(*Read								)(C4DAtom *at, HyperFile *hf, Int32 id, Int32 level);
	Bool						(*Write								)(C4DAtom *at, HyperFile *hf);
	Bool						(*ReadObject					)(C4DAtom *bn, HyperFile *hf, Bool readheader);
	Bool						(*WriteObject					)(C4DAtom *bn, HyperFile *hf);
	void						(*GetData							)(BaseList2D *bl, BaseContainer *ct);
	void						(*SetData							)(BaseList2D *bl, const BaseContainer *ct, Bool add);
	BaseContainer*	(*GetDataInstance			)(BaseList2D *bl);

	GeListHead*			(*AllocListHead				)(void);
	GeListNode*			(*AllocListNode				)(Int32 bits, Int32 *id_array, Int32 id_cnt);

	NodeData*				(*GetNodeData					)(GeListNode *bn, Int32 index);
	Int32						(*GetNodeID						)(GeListNode *bn, Int32 index);
	NODEPLUGIN*			(*RetrieveTable				)(GeListNode *node, Int32 index);
	NODEPLUGIN*			(*RetrieveTableX			)(NodeData *node, Int32 index);

	GeListNode*			(*GetCustomData				)(GeListNode *bn);
	void						(*SetCustomData				)(GeListNode *bn, GeListNode *custom);
	String					(*GetBubbleHelp				)(BaseList2D *bl);

	void						(BaseList2D::*ClearKeyframeSelection	)();
	Bool						(BaseList2D::*FindKeyframeSelection		)(const DescID &id);
	Bool						(BaseList2D::*SetKeyframeSelection		)(const DescID &id, Bool selection);
	Bool						(BaseList2D::*KeyframeSelectionContent)();

	LayerObject*			(BaseList2D::*GetLayerObject				)(BaseDocument *doc);
	Bool							(BaseList2D::*SetLayerObject				)(LayerObject *layer);
	const LayerData*	(BaseList2D::*GetLayerData					)(BaseDocument *doc, Bool rawdata) const;
	Bool							(BaseList2D::*SetLayerDataEx				)(BaseDocument *doc, const LayerData &data);

	GeListHead*				(BaseList2D::*GetCTrackRoot	)();
	CTrack*						(BaseList2D::*GetFirstCTrack	)(void);
	CTrack*						(BaseList2D::*FindCTrack			)(const DescID &id);

	const String &		(BaseList2D::*GetTypeName			)(void);

	void							(BaseList2D::*InsertTrackSorted	)(CTrack *track);
	BaseList2D*				(*Alloc													)(Int32 type);

	GeListHead*				(BaseList2D::*GetNLARoot				)();
	BaseList2D*				(BaseList2D::*AnimationLayerRemap)(BaseObject **layer);

	Bool	(BaseList2D::*AddEventNotification)(BaseList2D *bl, NOTIFY_EVENT eventid, NOTIFY_EVENT_FLAG flags, const BaseContainer *data);
	Bool	(BaseList2D::*RemoveEventNotification)(BaseDocument *doc, BaseList2D *bl, NOTIFY_EVENT eventid);
	Bool	(BaseList2D::*FindEventNotification)(BaseDocument *doc, BaseList2D *bl, NOTIFY_EVENT eventid);

	Bool	(BaseList2D::*SetDescIDState)(const DescID &id, DESCIDSTATE descidstate);
	DESCIDSTATE	(BaseList2D::*GetDescIDState)(const DescID &id, Bool tolerant) const;

	Bool             (BaseList2D::*SetLayerData)(BaseDocument *doc, const LayerData &data);

	GeListHead*      (BaseList2D::*GetOverrideRoot)();
	BaseOverride*    (BaseList2D::*GetFirstOverride)();
	GeListHead*      (BaseList2D::*GetShaderRepositoryRoot)();
};

struct C4D_Tag
{
	BaseTag*				(*Alloc								)(Int32 type, Int32 count);
	Int32						(*GetDataCount				)(VariableTag *bt);
	Int32						(*GetDataSize					)(VariableTag *bt);
	void*						(*GetDataAddressW			)(VariableTag *bt);
	BaseSelect*			(*GetBaseSelect				)(SelectionTag *tag);
	Bool						(*Record							)(StickTextureTag *stt, BaseObject *op, Bool always);

	void						(*UvGet								)(UVWTag *tag, Int32 i, UVWStruct *s);
	void						(*UvSet								)(UVWTag *tag, Int32 i, UVWStruct *s);
	void						(*UvCpy								)(UVWTag *tag, Int32 dst, UVWTag *srctag, Int32 src);

	BaseTag*				(*GetOrigin						)(BaseTag *tag);
	const void*			(*GetDataAddressR			)(VariableTag *bt);
	void						(*UvGet2							)(const void *handle, Int32 i, UVWStruct *s);
	void						(*UvSet2							)(void *handle, Int32 i, const UVWStruct &s);
	void						(*UvCpy2							)(const void *srchandle, Int32 src, void *dsthandle, Int32 dst);

	void						(*NrmGet							)(const void *handle, Int32 i, NormalStruct *s);
	void						(*NrmSet							)(void *handle, Int32 i, const NormalStruct &s);
	void						(*NrmCpy							)(const void *srchandle, Int32 src, void *dsthandle, Int32 dst);

	void						(*VcolGet							)(const void *handle, Int32 i, VertexColorStruct *s);
	void						(*VcolSet							)(void *handle, Int32 i, const VertexColorStruct &s);
	Bool						(*IsPerPointColor			)(VertexColorTag* tag);
	Bool 						(*SetPerPointMode			)(VertexColorTag* tag, Bool perVertexColor);
};

struct C4D_Object
{
	BaseObject*			(*Alloc								)(Int32 type);
	SplineObject*		(*AllocSplineObject		)(Int32 pcnt, SPLINETYPE type);
	Float						(*GetVisibility				)(BaseObject *op, Float parent);

	Vector					(BaseObject::*GetAbsPos)() const;
	void						(BaseObject::*SetAbsPos						)(const Vector &v);
	Vector					(BaseObject::*GetAbsScale					)() const;
	void						(BaseObject::*SetAbsScale					)(const Vector &v);
	Vector					(BaseObject::*GetAbsRot						)() const;
	void						(BaseObject::*SetAbsRot						)(const Vector &v);
	const Matrix&		(BaseObject::*GetMl								)() const;
	void						(BaseObject::*SetMl								)(const Matrix &m);
	Matrix					(BaseObject::*GetMg								)() const;
	void						(BaseObject::*SetMg								)(const Matrix &m);
	Matrix					(BaseObject::*GetMln							)() const;
	Matrix					(BaseObject::*GetMgn							)() const;
	Matrix					(BaseObject::*GetUpMg							)() const;

	Vector					(BaseObject::*GetFrozenPos				)() const;
	void						(BaseObject::*SetFrozenPos				)(const Vector &v);
	Vector					(BaseObject::*GetFrozenScale			)() const;
	void						(BaseObject::*SetFrozenScale			)(const Vector &v);
	Vector					(BaseObject::*GetFrozenRot				)() const;
	void						(BaseObject::*SetFrozenRot				)(const Vector &v);
	Matrix					(BaseObject::*GetFrozenMln					)() const;
	Matrix					(BaseObject::*GetRelMln						)() const;

	Vector					(BaseObject::*GetRelPos						)() const;
	void						(BaseObject::*SetRelPos						)(const Vector &v);
	Vector					(BaseObject::*GetRelScale					)() const;
	void						(BaseObject::*SetRelScale					)(const Vector &v);
	Vector					(BaseObject::*GetRelRot						)() const;
	void						(BaseObject::*SetRelRot						)(const Vector &v);
	Matrix					(BaseObject::*GetRelMl						)() const;
	void						(BaseObject::*SetRelMl						)(const Matrix &m);

	Vector					(*GetMp								)(BaseObject *op);
	Vector					(*GetRad							)(BaseObject *op);
	Int32						(*GetMode							)(BaseObject *op, OBJECTSTATE mode);
	void						(*SetMode							)(BaseObject *op, OBJECTSTATE mode, Int32 val);
	BaseTag*				(*GetFirstTag					)(BaseObject *op);
	BaseTag*				(*GetTag							)(BaseObject *op, Int32 type, Int32 nr);
	void*						(*GetTagData					)(BaseObject *op, Int32 type, Int32 nr);
	Int32						(*GetTagDataCount			)(const BaseObject *op, Int32 type);
	void						(*InsertTag						)(BaseObject *op, BaseTag *tp, BaseTag *pred);
	void						(*KillTag							)(BaseObject *op, Int32 type, Int32 nr);
	Int32						(*GetInfo							)(GeListNode *op);
	Bool						(*Edit								)(BaseList2D *op);
	BaseObject*			(*GetCache						)(BaseObject *op, HierarchyHelp *hh);
	BaseObject*			(*GetDeformCache			)(BaseObject *op);
	LineObject*			(*GetIsoparm					)(BaseObject *op);
	Bool						(*IsDirty							)(BaseObject *op, DIRTYFLAGS flags);
	void						(*SetDirty						)(C4DAtom *op, DIRTYFLAGS flags);
	Bool						(*CheckCache					)(BaseObject *op, HierarchyHelp *hh);
	void						(*SetIsoparm					)(BaseObject *op, LineObject *l);
	BaseObject*			(*GenPrimitive				)(BaseDocument *doc, Int32 type, const BaseContainer *bc, Float lod, Bool isoparm, BaseThread *bt);
	BaseObject*			(*GenSplinePrimitive	)(BaseDocument *doc, Int32 type, const BaseContainer *bc, Float lod, BaseThread *bt);
	void						(*NewDependenceList		)(BaseObject *op);
	Bool						(*CmpDependenceList		)(BaseObject *op);
	void						(*TouchDependenceList	)(BaseObject *op);
	void						(*AddDependence				)(BaseObject *op, HierarchyHelp *hh, BaseObject *pp);
	Bool						(*AddTextureEx				)(BaseList2D *op, const Filename *fn, AssetData *gd);
	BaseObject*			(*GetVirtualLineObject)(BaseObject *op, HierarchyHelp *hh, const Matrix &mloc, Bool keep_spline, Bool recurse, Matrix *mres, Bool *dirty);
	void						(*Touch								)(BaseObject *op);

	// Point object
	BaseSelect*			(*PoGetPointS					)(PointObject *op);
	BaseSelect*			(*PoGetPointH					)(PointObject *op);
	Bool						(*PoResizeObject			)(PointObject *op, Int32 pcnt);
	Float32*					(*PoCalcVertexMap			)(PointObject *op, BaseObject *modifier);

	// Line object
	Bool						(*LoResizeObject			)(LineObject *op, Int32 pcnt, Int32 scnt);

	// Polygon object
	BaseSelect*			(*PyGetPolygonS				)(PolygonObject *op);
	BaseSelect*			(*PyGetPolygonH				)(PolygonObject *op);
	Bool						(*PyResizeObject			)(PolygonObject *op, Int32 pcnt, Int32 vcnt);

	// Spline object
	Vector					(*SpGetSplinePoint		)(SplineObject *op, Float t, Int32 segment, const Vector *padr);
	Vector					(*SpGetSplineTangent	)(SplineObject *op, Float t, Int32 segment, const Vector *padr);

	SplineLengthData*	(*SpLDAlloc					)(void);
	void						(*SpLDFree						)(SplineLengthData *&sp);

	Bool						(*SpInitLength				)(SplineLengthData *dat, SplineObject *op, Int32 segment, const Vector *padr);
	Float						(*SpUniformToNatural	)(SplineLengthData *dat, Float t);
	Float						(*SpGetLength					)(SplineLengthData *dat);
	Float						(*SpGetSegmentLength	)(SplineLengthData *dat, Int32 a, Int32 b);
	LineObject*			(*SpGetLineObject			)(SplineObject *op, BaseDocument *doc, Float lod, BaseThread *thread);
	SplineObject*		(*SpGetRealSpline			)(BaseObject *op);
	Bool						(*SpResizeObject			)(SplineObject *op, Int32 pcnt, Int32 scnt);

	// Particle object
	Int32						(*PrGetCount					)(BaseObject *op);
	Float						(*PrGetLifetime				)(BaseObject *op);
	Particle*				(*PrGetParticleW			)(BaseObject *op, ParticleTag *pt, Int32 i);
	Bool						(*PrIsMatrixAvailable	)(BaseObject *op);
	ParticleDetails*(*PrGetParticleDetails)(BaseDocument *doc, BaseObject *op);

	// Camera object
	Int32						(*CoGetProjection			)(BaseObject *op);
	Float						(*CoGetFocus					)(BaseObject *op);
	Float						(*CoGetZoom						)(BaseObject *op);
	Vector					(*CoGetOffset					)(BaseObject *op);
	Float						(*CoGetAperture				)(BaseObject *op);
	Bool						(*CoSetProjection			)(BaseObject *op, Int32 projection);
	Bool						(*CoSetFocus					)(BaseObject *op, Float v);
	Bool						(*CoSetZoom						)(BaseObject *op, Float v);
	Bool						(*CoSetOffset					)(BaseObject *op, const Vector &offset);
	Bool						(*CoSetAperture				)(BaseObject *op, Float v);

	// Object safety
	ObjectSafety*		(*OsAlloc							)(BaseObject *op);
	void						(*OsFree							)(ObjectSafety *os, Bool restore);

	// Triangulation
	Bool						(*Triangulate					)(const Vector *padr, Int32 pcnt, CPolygon **vadr, Int32 *vcnt);
	PolygonObject*	(*TriangulateLine			)(LineObject *op, Float regular, BaseThread *bt);
	SplineObject*		(*FitCurve						)(Vector *padr, Int32 pcnt, Float error, BaseThread *bt);

	UVWTag*					(*GenerateUVW					)(BaseObject *op, const Matrix &opmg, TextureTag *tp, const Matrix &texopmg, BaseView *view);

	UInt32						(*GetDirty						)(const C4DAtom *op, DIRTYFLAGS flags);

	Bool						(*TriangulateStandard )(const Vector *padr, Int32 pcnt, const Int32 *list, Int32 lcnt, CPolygon *&vadr, Int32 &vcnt, BaseThread *thread);
	Bool						(*TriangulateRegular	)(const Vector *pinp, Int32 pinp_cnt, const Int32 *list, Int32 lcnt, Vector *&padr, Int32 &pcnt, CPolygon *&vadr, Int32 &vcnt, Float regular_width, BaseThread *thread);

	Bool						(*SpSetDefaultCoeff		)(SplineObject *op);
	BaseObject*			(*GenerateText				)(BaseContainer *cp, BaseThread *bt, Bool separate);

	BaseSelect*			(*PyGetEdgeS					)(PolygonObject *op);
	BaseSelect*			(*PyGetEdgeH					)(PolygonObject *op);
	void						(*GetColorProperties	)(BaseObject *op, ObjectColorProperties *co);
	void						(*SetColorProperties	)(BaseObject *op, ObjectColorProperties *co);

	Bool						(*CopyTagsTo					)(BaseObject *op, BaseObject *dest, Int32 visible, Int32 variable, Int32 hierarchical, AliasTrans *trans);
	BaseObject*			(*GetHierarchyClone		)(BaseObject *op, HierarchyHelp *hh, BaseObject *pp, HIERARCHYCLONEFLAGS flags, Bool *dirty, AliasTrans *trans);

	BaseObject*			(*GetCacheParent			)(BaseObject *op);
	Bool						(*CheckDisplayFilter	)(BaseObject *op, Int32 flags);

	BaseSelect*			(*PyGetPhongBreak			)(PolygonObject *op);

	Int32						(*GetUniqueIP					)(BaseObject *op);
	void						(*SetUniqueIP					)(BaseObject *op, Int32 ip);

	void						(*SetOrigin						)(BaseObject *op, BaseObject *origin);
	BaseObject*			(*GetOrigin						)(BaseObject *op, Bool safe);
	BaseObject*			(*InternalCalcBooleOld)(BaseObject *curr, Int32 booletype, HierarchyHelp *hh);

	Vector32*				(*CreatePhongNormals	)(PolygonObject *op);

	PolyTriangulate*	(*PolyTriangAlloc		)();
	void							(*PolyTriangFree			)(PolyTriangulate *&pTriang);
	Bool							(*PolyTriangTriang		)(PolyTriangulate* pTriang, const Vector* pvPoints, const Int32 lPointCount, const Int32* plSegments, const Int32 lSegCnt,
		CPolygon*& pPolys, Int32& lPolyCount, Int32 lFlags, const Int32* plMap, BaseThread* pThread,
		const Int32 lConstraints, const Int32* plConstrainedEdges);
	Bool							(*PolyTriangTriangRelease)(PolyTriangulate* pTriang, const Vector* pvPoints, const Int32 lPointCount, const Int32* plSegments, const Int32 lSegCnt,
		CPolygon*& pPolys, Int32& lPolyCount, Int32 lFlags, const Int32* plMap, BaseThread* pThread,
		const Int32 lConstraints, const Int32* plConstrainedEdges);

	Bool						(*PyGetPolygonTranslationMap)(PolygonObject *op, Int32 &ngoncnt, Int32 *&polymap);
	Bool						(*PyGetNGonTranslationMap)(PolygonObject *op, const Int32 ngoncnt, const Int32 *polymap, Int32 **&ngons);
	Pgon*						(*PyGetNgon)(PolygonObject *op);
	Int32						(*PyGetNgonCount)(PolygonObject *op);
	Bool						(*PyResizeObjectNgon	)(PolygonObject *op, Int32 pcnt, Int32 vcnt, Int32 ncnt);
	void						(*PyGetSelectedNgons	)(PolygonObject *op, BaseSelect* sel);
	void						(*PyGetHiddenNgons		)(PolygonObject *op, BaseSelect* sel);
	NgonBase*				(*PyGetNgonBase)(PolygonObject *op);
	Bool						(*PyValidateEdgeSelection)(PolygonObject *op, BaseSelect* sel);
	Bool						(*PyGetEdgeSelection)(PolygonObject *op, BaseSelect* sel, EDGESELECTIONTYPE type);

	BaseObject*			(*GetTopOrigin						)(BaseObject *op, Bool parent, Bool safe);
	BaseObject*			(*GetEditObject						)(BaseObject *op, BaseObject **psds, DISPLAYEDITSTATE state);
	Int32						(*GetHighlightHandle			)(BaseObject *op, BaseDraw *bd);

	const Matrix &	(*GetModelingAxis)(BaseObject *op, BaseDocument *doc);
	void						(*SetModelingAxis)(BaseObject *op, const Matrix &m);
	Bool						(*PolyTriangHasIdentical)(PolyTriangulate* pTriang);
	Bool						(*CalculateVisiblePoints)(BaseDraw *bd, PolygonObject *op, Vector *padr, UChar *pset, Bool select_visibonly);
	Int32						(*PolyTriangGetType)(PolyTriangulate* pTriang);

	void						(*PyGetNgonEdgesCompact)(PolygonObject *op, UChar *&edges);
	UInt32					(*PyVBOInitUpdate)(PolygonObject *op, BaseDraw* bd);
	Bool						(*PyVBOStartUpdate)(PolygonObject *op, BaseDraw* bd, GlVertexBufferAccessFlags access, Bool latemap);
	void						(*PyVBOUpdateVector)(PolygonObject *op, Int32 i, const Vector32 &v, const GlVertexBufferAttributeInfo* pInfo);
	void						(*PyVBOEndUpdate)(PolygonObject *op, BaseDraw* bd);
	void						(*PyVBOFreeUpdate)(PolygonObject *op);

	Int32						(*IntersectionTest)(PolygonObject *op, BaseDraw *bd, Float x, Float y, const Matrix &mg, Float *z, MODELINGCOMMANDMODE mode, UChar *pPointSelect, Int32 lSelectCount);

	Bool						(*PyValidateEdgeSelectionA)(PolygonObject *op);

#ifdef MAXON_TARGET_SINGLEPRECISION
	Bool	(*PolyTriangTriangA)(PolyTriangulate* pTriang, const Vector64* pvPoints, const Int32 lPointCount, const Int32* plSegments, const Int32 lSegCnt,
		CPolygon*& pPolys, Int32& lPolyCount, Int32 lFlags, const Int32* plMap, BaseThread* pThread,
		const Int32 lConstraints, const Int32* plConstrainedEdges);
	Bool	(*PolyTriangTriangReleaseA)(PolyTriangulate* pTriang, const Vector64* pvPoints, const Int32 lPointCount, const Int32* plSegments, const Int32 lSegCnt,
		CPolygon*& pPolys, Int32& lPolyCount, Int32 lFlags, const Int32* plMap, BaseThread* pThread,
		const Int32 lConstraints, const Int32* plConstrainedEdges);
#endif

	void						(*PolyTriangSetPolygonMatrix)(PolyTriangulate* pTriang, Matrix64* m);
	UInt32					(*PolyTriangGetState)(PolyTriangulate* pTriang);
	const Particle*	(*PrGetParticleR)(BaseObject *op, ParticleTag *pt, Int32 i);

	void						(*GetIcon							)(BaseList2D *op, IconData *dat);

	UInt32					(C4DAtom::*GetHDirty	)(HDIRTYFLAGS mask) const;
	void						(C4DAtom::*SetHDirty	)(HDIRTYFLAGS mask);

	const void*			(*GetTagDataR					)(const BaseObject *op, Int32 type, Int32 nr);

	void						(*RemoveFromCache)(BaseObject *op);
	Bool						(*SearchHierarchy)(BaseObject *op, BaseObject *find);
	Bool						(*PyResizeObjectNgonFlags)(PolygonObject *op, Int32 pcnt, Int32 vcnt, Int32 ncnt, Int32 vc_flags);
	void						(*CopyMatrixTo)(BaseObject *src, BaseObject *dst);
	Int32						(*CoStereoGetCameraCount)(const BaseObject* op, BaseDocument* doc, BaseDraw* bd, RenderData* rd, Int32 flags);
	Bool						(*CoStereoGetCameraInfo)(const BaseObject* op, BaseDocument* doc, BaseDraw* bd, RenderData* rd, Int32 n, StereoCameraInfo &info, Int32 flags);

	void						(BaseObject::*SetRotationOrder	)(ROTATIONORDER order);
	ROTATIONORDER		(BaseObject::*GetRotationOrder	)() const;
	const GlVertexBufferAttributeInfo*	(*PyVBOUpdateVectorGetAttribute)(PolygonObject *op, UInt32 flags);

	void						(*PyVBOUpdateFaceVector)(PolygonObject *op, Int32 i, const Vector32 &v, const GlVertexBufferAttributeInfo* pInfo);
	void						(*PyVBOInvalidate			)(PolygonObject *op);
	void						(*PoIncreaseBoundingBox)(PointObject *op, Int32 cnt, Vector* v);

	UInt64					(*GetGUID							)(BaseObject *op);			// Added in R14.004
	Bool						(*AddTexture					)(BaseList2D *op, const Filename *fn, Bool netRequestOnDemand, AssetData *gd);

	// editor visibility
	Bool						(*CheckEditorVisibility)(BaseObject* op);

	Vector					(*SpCalcSplinePoint		)(Float offset, SPLINETYPE type, Bool closed, Int32 pcnt, const Vector *padr, const Tangent *tadr);
	Vector					(*SpCalcSplineTangent	)(Float offset, SPLINETYPE type, Bool closed, Int32 pcnt, const Vector *padr, const Tangent *tadr);
	void						(*SpCalcSplineInsert	)(Float offset, SPLINETYPE type, Bool closed, Int32 pcnt, const Vector *padr, const Tangent *tadr, Int32 &pointIndex, Vector &resultPoint, Tangent &resultTangent, Vector &leftTangent, Vector &rightTangent);
	Bool						(*SpCalcSplineDefaultTangents)(SPLINETYPE type, Bool closed, Int32 pcnt, const Vector* padr, Tangent* tadr);
	void						(*SpCalcSplineMovement)(const Vector& newPos, Float offset, SPLINETYPE type, const Matrix& splineMg, BaseDraw *bd, const Vector& planeNormal, Bool closed, Bool lockTangentAngle, Bool lockTangentLength, BREAKTANGENTS breakTangents, Int32 pcnt, Vector* padr, Tangent* tadr);
	Tangent					(*SpTransformTangent	)(const Vector& newPos, const Vector& planeNormal, const Vector& position, const Tangent& tangent, TANGENTSIDE tangentSide, TANGENTTRANSFORMFLAG flags);
	SplineObject*		(*SpBooleanSplines		)(SplineObject* initialSpline, AtomArray* booleanObjects, BaseDocument *doc, BaseDraw* bd, SPLINEBOOL_AXIS projectionAxis, SPLINEBOOL_MODE booleanMode);

	void						(BaseObject::*SetQuaternionRotationMode)(Bool active, Bool bUndo);
	Bool						(BaseObject::*IsQuaternionRotationMode)();

	Bool						(*SynchronizeVectorTrackKeys)(BaseDocument* doc, BaseObject *op, Int32 vectorTrackID, Bool bUndo, BaseTime startRange, BaseTime endRange);
	Bool						(*GetVectorTracks)(BaseList2D	 *op, const DescID &id, CTrack *&xfound, CTrack *&yfound, CTrack *&zfound);
	Bool						(*GetVectorCurves)(CCurve *curveToSearch, CCurve *&xfound, CCurve *&yfound, CCurve *&zfound);
	Bool						(*EvaluateSynchronizedRotation)(BaseDocument *doc, BaseObject *bo, const BaseTime &time, ANIMATEFLAGS flags, Vector *resultRotation);
	Bool						(*FindBestEulerAngle)(BaseDocument* doc, BaseObject *op, Int32 RotationVectorID, Bool bAdjustTangent, Bool bUndo, BaseTime startRange, BaseTime endRange);
};

struct C4D_Document
{
	// %Render data
	RenderData*			(*RdAlloc							)(void);

	// Document
	BaseDocument*		(*Alloc								)(void);
	void						(*FlushAll						)(BaseDocument *doc);
	BaseContainer		(*GetData							)(BaseDocument *doc, DOCUMENTSETTINGS type);
	void						(*SetData							)(BaseDocument *doc, DOCUMENTSETTINGS type, const BaseContainer *bc);
	BaseObject*			(*GetFirstObject			)(BaseDocument *doc);
	BaseMaterial*		(*GetFirstMaterial		)(BaseDocument *doc);
	RenderData*			(*GetFirstRenderData	)(BaseDocument *doc);
	void						(*InsertRenderData		)(BaseDocument *doc, RenderData *rd, RenderData *parent, RenderData *pred);
	void						(*InsertMaterial			)(BaseDocument *doc, BaseMaterial *mat, BaseMaterial *pred, Bool checknames);
	void						(*InsertObject				)(BaseDocument *doc, BaseObject *op, BaseObject *parent, BaseObject *pred, Bool checknames);
	RenderData*			(*GetActiveRenderData	)(BaseDocument *doc);
	BaseObject*			(*GetActiveObject			)(BaseDocument *doc);
	BaseMaterial*		(*GetActiveMaterial		)(BaseDocument *doc);
	BaseTag*				(*GetActiveTag				)(BaseDocument *doc, BaseObject *active);
	void						(*SetActiveRenderData	)(BaseDocument *doc, RenderData *rd);
	BaseObject*			(*GetHighest					)(BaseDocument *doc, Int32 type, Bool editor);
	BaseMaterial*		(*SearchMaterial			)(BaseDocument *doc, const String *str, Bool inc);
	BaseObject*			(*SearchObject				)(BaseDocument *doc, const String *str, Bool inc);
	Bool						(*StartUndo						)(BaseDocument *doc);
	Bool						(*EndUndo							)(BaseDocument *doc);
	Bool						(*AddUndoEx						)(BaseDocument *doc, UNDOTYPE type, void *data);
	Bool						(*DoRedo							)(BaseDocument *doc);
	void						(*AnimateObject				)(BaseDocument *doc, BaseList2D *op, const BaseTime &time, ANIMATEFLAGS flags);
	BaseDraw*				(*GetActiveBaseDraw		)(BaseDocument *doc);
	BaseDraw*				(*GetRenderBaseDraw		)(BaseDocument *doc);
	BaseDraw*				(*GetBaseDraw					)(BaseDocument *doc, Int32 num);
	Int32						(*GetSplinePlane			)(BaseDocument *doc);

	// Hierarchy help
	Float						(*HhGetLOD						)(HierarchyHelp *hh);
	BUILDFLAGS			(*HhGetBuildFlags			)(HierarchyHelp *hh);
	BaseThread*			(*HhGetThread					)(HierarchyHelp *hh);
	BaseDocument*		(*HhGetDocument				)(HierarchyHelp *hh);
	const Matrix&		(*HhGetMg							)(HierarchyHelp *hh);

	// Hierarchy
	Bool						(*RunHierarchy				)(void *main, BaseDocument *doc, Bool spheres, Float lod, Bool uselod, BUILDFLAGS flags, void *startdata, BaseThread *bt, HierarchyAlloc *ha, HierarchyFree *hf, HierarchyCopyTo *hc, HierarchyDo *hd);

	BaseSceneHook*	(*FindSceneHook				)(const BaseDocument *doc, Int32 id);

	void						(BaseDocument::*SetActiveObject		)(BaseObject *op, Int32 mode);
	void						(BaseDocument::*GetActiveObjects	)(AtomArray &selection, GETACTIVEOBJECTFLAGS flags) const;
	void						(BaseDocument::*GetActiveTags			)(AtomArray &selection) const;

	void						(*PrAdd								)(PriorityList *list, GeListNode *node, Int32 priority, EXECUTIONFLAGS flags);
	BaseObject*			(*GetHelperAxis				)(BaseDocument *doc);
	BaseVideoPost*	(*RdGetFirstVideoPost	)(RenderData *rd);
	void						(*RdInsertVideoPost		)(RenderData *rd, BaseVideoPost *pvp, BaseVideoPost *pred);
	void						(BaseDocument::*GetActiveMaterials)(AtomArray &selection) const;

	void						(*SetRewind						)(BaseDocument *doc, Int32 flags);

	void						(BaseDocument::*SetActiveTag			)(BaseTag *op, Int32 mode);
	void						(BaseDocument::*SetActiveMaterial	)(BaseMaterial *mat, Int32 mode);

	BaseVideoPost*	(*VpAlloc								)(Int32 type);

	BaseList2D*			(*GetUndoPtr						)(BaseDocument *doc);
	void						(*AutoKey								)(BaseDocument *doc, BaseList2D *undo, BaseList2D *op, Bool recursive, Bool pos, Bool scale, Bool rot, Bool param, Bool pla);
	Bool						(*DoUndo								)(BaseDocument *doc, Bool multiple);
	Bool						(*IsCacheBuilt					)(BaseDocument *doc, Bool force);
	void						(BaseDocument::*GetActivePolygonObjects)(AtomArray &selection, Bool children) const;
	BaseTime				(*GetUsedTime						)(BaseDocument *doc, BaseList2D *check_op, Bool min);
	void						(*ForceCreateBaseDraw		)(BaseDocument *doc);

	BaseContainer*	(*GetDataInstance				)(BaseDocument *doc, Int32 type);
	void						(*RunAnimation					)(BaseDocument *doc, Bool forward, Bool stop);
	void						(*SetDocumentTime				)(BaseDocument *doc, const BaseTime &time);

	BaseDocument*		(*IsolateObjects				)(BaseDocument *doc, const AtomArray &t_objects);

	void						(BaseDocument::*GetSelection)(AtomArray &selection) const;
	void						(BaseDocument::*SetSelection)(BaseList2D *bl, Int32 mode);

	// Layers
	LayerObject*		(*DlAlloc												)(void);
	GeListHead*			(*GetLayerObjectRoot						)(BaseDocument *doc);
	Bool						(*HandleSelectedTextureFilename	)(BaseDocument *doc, BaseChannel *bc, const Filename &fn, Filename *resfilename, Bool undo, GEMB_R *already_answered);
	Bool						(*ReceiveMaterials							)(BaseDocument *doc, BaseObject *op, AtomArray *mat, Bool clearfirst);
	Bool						(*ReceiveNewTexture							)(BaseDocument *doc, BaseObject *op, const Filename &filename, Bool sdown, GEMB_R *already_answered);

	void						(*SetKeyDefault					)(BaseDocument *doc, CCurve *seq, Int32 kidx);

	void						(*Record								)(BaseDocument *doc);
	BaseContainer		(*GetAllTexturesEx			)(BaseDocument *doc, const AtomArray *ar);
	Bool						(*RecordKey							)(BaseDocument *doc, BaseList2D *op, const BaseTime &time, const DescID &id, BaseList2D *undo, Bool eval_attribmanager, Bool autokeying, Bool allow_linking);

	Bool						(*CloseAllDocuments			)();
	BaseObject*			(*GetRealActiveObject		)(BaseDocument *doc, const AtomArray *help, Bool *multi);
	Bool						(*AddUndoBD							)(BaseDocument *doc, BaseDraw* bd);

	Bool						(*CollectSounds					)(BaseDocument *doc, BaseSound *snd, const BaseTime &from, const BaseTime &to);
	void						(*RecordZero						)(BaseDocument *doc);

	MultipassObject*(*RdGetFirstMultipass		)(RenderData *rd);
	void						(*RdInsertMultipass			)(RenderData *rd, MultipassObject *pvp, MultipassObject *pred);
	MultiPassChannel *multipasschannels;
	void						(*InsertRenderDataLast	)(BaseDocument *doc, RenderData *rd);

	void						(*RecordNoEvent					)(BaseDocument *doc);
	Int32						(*GetDrawTime						)(BaseDocument *doc);
	Bool						(*StopExternalRenderer	)();
	Int32						(*GetBaseDrawCount			)(BaseDocument *doc);
	Bool						(BaseDocument::*ExecutePasses)(BaseThread *bt, Bool animation, Bool expressions, Bool caches, BUILDFLAGS flags);

	const PickSessionDataStruct *(BaseDocument::*GetPickSession)() const;
	void						(BaseDocument::*StartPickSession)(PickSessionDataStruct *psd);
	void						(BaseDocument::*StopPickSession)(Bool cancel);
	Bool						(*VpStereoMergeImages	)(BaseVideoPost* vp, BaseBitmap* dest, const BaseBitmap* const* source, Int32 cnt, const BaseContainer &settings, COLORSPACETRANSFORMATION transform);
	Int32						(*VpStereoGetCameraCountEditor)(BaseVideoPost* vp, BaseDocument* doc, BaseDraw *bd);
	Int32						(*VpStereoGetCameraCountRenderer)(BaseVideoPost* vp, BaseDocument* doc, RenderData* rd);
	Bool						(*VpStereoGetCameraInfo)(BaseVideoPost* vp, BaseDocument* doc, BaseDraw *bd, RenderData* rd, Int32 index, StereoCameraInfo& info);
	Bool						(*VpRenderEngineCheck)(BaseVideoPost* vp, Int32 id);
	void						(BaseDocument::*GetActiveObjectsFilter)(AtomArray &selection, Bool children, Int32 type, Int32 instanceof) const;
	Bool						(BaseDocument::*GetDefaultKey)(CKey* pKey, Bool &bOverdub) const;
	void						(BaseDocument::*SetDefaultKey)(CKey* pKey, Bool bOverdub);
	BaseList2D*			(*FindUndoPtr						)(BaseDocument *doc, BaseList2D *bl, UNDOTYPE type);
	void						(*SendInfo							)(BaseDocument *doc, Int32 type, Int32 format, const Filename &fn, BaseList2D *bl, Bool hooks_only);
	void						(BaseDocument::*SetHighlightedObject)(BaseObject *op, Int32 mode);
	void						(BaseDocument::*SetHighlightedObjects)(AtomArray &selection, Int32 mode);
	void						(BaseDocument::*GetHighlightedObjects)(AtomArray &selection) const;

	Bool						(BaseDocument::*IsAxisEnabled)();
	Bool						(*AddUndo							)(BaseDocument *doc, UNDOTYPE type, void *data, Bool allowFromThread);
	void						(*FlushUndoBuffer			)(BaseDocument *doc);
	BaseBitmap*			(BaseDocument::*GetDocPreviewBitmap)();
	BaseContainer		(*GetAllTextures			)(BaseDocument *doc, Bool isNet, const AtomArray *ar);
	NetRenderDocumentContext*	(BaseDocument::*GetNetRenderDocumentContext)() const;
	void						(BaseDocument::*SetNetRenderDocumentContext)(NetRenderDocumentContext* context);
	TakeData*				(BaseDocument::*GetTakeData)();

	BaseObject*			(BaseDocument::*GetTargetObject)() const;
	void						(BaseDocument::*SetTargetObject)(BaseObject* op);
};

struct C4D_Thread
{
	BaseThread*			(*Alloc								)(ThreadMain *tm, ThreadTest *tt, void *data, ThreadName *tn);
	void						(*Free								)(BaseThread *bt);
	Bool						(*Start								)(BaseThread *bt, THREADMODE mode, THREADPRIORITY priority, void *reserved);
	void						(*End									)(BaseThread *bt, Bool wait);
	void						(*Wait								)(BaseThread *bt, Bool checkevents);
	Bool						(*TestBreak						)(BaseThread *bt);
	Bool						(*TestBaseBreak				)(BaseThread *bt);
	Bool						(*IsRunning						)(BaseThread *bt);
	THREADTYPE			(*Identify						)(BaseThread *bt);
	void						(*ThreadLock					)(void);
	void						(*ThreadUnlock				)(void);
	Int32						(*GetCurrentThreadCount)(void);
	UInt32					(*GetCurrentThreadId	)(void);
	BaseThread*			(*GetCurrentThread		)(void);

	MPBaseThread*		(*MPAlloc							)(BaseThread *parent, Int32 count, ThreadMain *tm, ThreadTest *tt, void **data, ThreadName *tn);
	void						(*MPFree							)(MPBaseThread *mp);
	BaseThread*			(*MPGetThread					)(MPBaseThread *mp, Int32 i);
	void*						(*MPWaitForNextFree		)(MPBaseThread *mp);
	void						(*MPWait							)(MPBaseThread *mp);
	void						(*MPEnd								)(MPBaseThread *mp);

	Semaphore*			(*SMAlloc							)(void);
	void						(*SMFree							)(Semaphore *&sm);
	Bool						(*SMLock							)(Semaphore *sm);
	Bool						(*SMLockAndWait				)(Semaphore *sm, BaseThread *bt);
	void						(*SMUnlock						)(Semaphore *sm);

	BaseThread			*NoThread;

	void						(GeSpinlock::*Lock						)();
	void						(GeSpinlock::*Unlock					)();
	Bool						(GeSpinlock::*AttemptLock			)();

	void						(GeRWSpinlock::*ReadLock				)();
	void						(GeRWSpinlock::*ReadUnlock			)();
	void						(GeRWSpinlock::*WriteLock				)();
	void						(GeRWSpinlock::*WriteUnlock			)();
	Bool						(GeRWSpinlock::*AttemptWriteLock)();

	GeSignal*				(*SIGAlloc						)(void);
	void						(*SIGFree							)(GeSignal *&sm);

	Bool						(GeSignal::*SIGInit		)(SIGNALMODE mode);
	void						(GeSignal::*SIGSet		)(void);
	void						(GeSignal::*SIGClear	)(void);
	Bool						(GeSignal::*SIGWait		)(Int32 timeout);
	Bool						(*SMLockDebug					)(Semaphore *sm, Int32 line, const char* file);
	Bool						(*SMLockAndWaitDebug	)(Semaphore *sm, BaseThread *bt, Int32 line, const char* file);

	BaseThread*			userEscTestThread;
};

struct C4D_Material
{
	BaseMaterial*		(*Alloc								)(Int32 type);
	void						(*Update							)(BaseMaterial *mat, Int32 preview, Bool rttm);
	BaseChannel*		(*GetChannel					)(BaseMaterial *bm, Int32 id);
	Bool						(*GetChannelState			)(Material *mat, Int32 channel);
	void						(*SetChannelState			)(Material *mat, Int32 channel, Bool state);
	Bool						(*Compare							)(BaseMaterial *m1, BaseMaterial *m2);
	BaseBitmap*			(*GetPreview					)(BaseMaterial *bm, Int32 flags);

	void						(BaseMaterial::*DisplaceEx			)(VolumeData *sd);
	void						(BaseMaterial::*ChangeNormal		)(VolumeData *sd);
	void						(BaseMaterial::*CalcSurface			)(VolumeData *sd);
	void						(BaseMaterial::*CalcTransparency)(VolumeData *sd);
	void						(BaseMaterial::*CalcAlpha				)(VolumeData *sd);
	void						(BaseMaterial::*CalcVolumetric	)(VolumeData *sd);
	void						(BaseMaterial::*InitCalculation	)(VolumeData *sd, INITCALCULATION type);
	VOLUMEINFO			(BaseMaterial::*GetRenderInfo		)(void);

	Vector						(*GetAverageColor			)(BaseMaterial *mat, Int32 channel);
	GL_MESSAGE				(BaseMaterial::*GlMessage	)(Int32 type, void *data);
	Bool							(BaseMaterial::*HasEditorTransparency)();
	RayIllumination*	(BaseMaterial::*GetRayIllumination)(void);
	INITRENDERRESULT	(BaseMaterial::*InitTextures		)(const InitRenderStruct &irs);
	void							(BaseMaterial::*UnlockTextures	)(void);

	ReflectionLayer*	(*AddReflectionLayer					)(Material *mat);
	ReflectionLayer*	(*GetReflectionLayerID				)(Material *mat, Int32 id);
	ReflectionLayer*	(*GetReflectionLayerIndex			)(Material *mat, Int32 index);
	ReflectionLayer*	(*GetReflectionLayerTrans			)(Material *mat);
	Int32							(*GetReflectionLayerCount			)(Material *mat);
	void							(*RemoveReflectionLayerID			)(Material *mat, Int32 id);
	void							(*RemoveReflectionLayerIndex	)(Material *mat, Int32 index);
	void							(*RemoveReflectionAllLayers		)(Material *mat);
	void							(*GetAllReflectionShaders			)(Material *mat, maxon::BaseArray<BaseShader*>& shaders);
	void							(*GetReflectionPrimaryLayers	)(Material *mat, Int32 &reflection_layer, Int32 &specular_layer);
	Int32							(*ReflectionLayerGetLayerID		)(Material *mat, const ReflectionLayer* layer);
	String						(*ReflectionLayerGetName			)(Material *mat, const ReflectionLayer* layer);
	void							(*ReflectionLayerSetName			)(Material *mat, ReflectionLayer* layer, const String& name);
	Int32							(*ReflectionLayerGetFlags			)(Material *mat, const ReflectionLayer* layer);
	void							(*ReflectionLayerSetFlags			)(Material *mat, ReflectionLayer* layer, Int32 flags);

	void							(BaseMaterial::*Displace)(VolumeData *sd, const RayPolyWeight *weights);
};

struct C4D_Texture
{
	Vector					(*GetPos							)(TextureTag *tag);
	Vector					(*GetScale						)(TextureTag *tag);
	Vector					(*GetRot							)(TextureTag *tag);
	Matrix					(*GetMl								)(TextureTag *tag);
	void						(*SetPos							)(TextureTag *tag, const Vector &v);
	void						(*SetScale						)(TextureTag *tag, const Vector &v);
	void						(*SetRot							)(TextureTag *tag, const Vector &v);
	void						(*SetMl								)(TextureTag *tag, const Matrix &m);

	void						(*SetMaterial					)(TextureTag *tag, BaseMaterial *mat);
	BaseMaterial*		(*GetMaterial					)(TextureTag *tag, Bool ignoredoc);
};

struct C4D_BaseSelect
{
	BaseSelect*			(*Alloc								)(void);
	void						(*Free								)(BaseSelect *bs);
	Int32						(*GetCount						)(const BaseSelect *bs);
	Int32						(*GetSegments					)(const BaseSelect *bs);
	Bool						(*Select							)(BaseSelect *bs, Int32 num);
	Bool						(*SelectAllEx					)(BaseSelect *bs, Int32 min, Int32 max);
	Bool						(*Deselect						)(BaseSelect *bs, Int32 num);
	Bool						(*DeselectAll					)(BaseSelect *bs);
	Bool						(*Toggle							)(BaseSelect *bs, Int32 num);
	Bool						(*ToggleAll						)(BaseSelect *bs, Int32 min, Int32 max);
	Bool						(*GetRangeEx					)(const BaseSelect *bs, Int32 seg, Int32 *a, Int32 *b);
	Bool						(*IsSelected					)(const BaseSelect *bs, Int32 num);
	Bool						(*CopyTo							)(const BaseSelect *bs, BaseSelect *dest);
	BaseSelect*			(*GetClone						)(const BaseSelect *bs);
	Bool						(*FromArray						)(BaseSelect *bs, UChar *selection, Int32 count);
	UChar*					(*ToArray							)(const BaseSelect *bs, Int32 count);
	Bool						(*Merge								)(BaseSelect *bs, const BaseSelect *src);
	Bool						(*DeselectBS					)(BaseSelect *bs, const BaseSelect *src);
	Bool						(*Cross								)(BaseSelect *bs, const BaseSelect *src);
	Bool						(*FindSegment					)(const BaseSelect *bs, Int32 num, Int32 *segment);
	BaseSelectData*	(*GetData							)(BaseSelect *bs);
	Bool						(*CopyFrom						)(BaseSelect *bs, BaseSelectData *ndata, Int32 ncnt);
	Int32						(*GetDirty						)(const BaseSelect *bs);
	Int32						(*GetLastElement			)(const BaseSelect *bs);
	Bool						(*GetRange						)(const BaseSelect *bs, Int32 seg, Int32 maxElements, Int32 *a, Int32 *b);
	Bool						(*SelectAll						)(BaseSelect *bs, Int32 min, Int32 max, Bool deselectAll);
};

struct C4D_CAnimation
{
	BaseTime				(CKey::*GetTime								)(void) const;
	Bool						(CKey::*CopyDataTo						)(CCurve *destseq, CKey *dest, AliasTrans *trans) const;
	void						(CKey::*FlushData1						)(void);
	BaseTime				(CKey::*GetTimeLeft						)(void) const;
	BaseTime				(CKey::*GetTimeRight					)(void) const;
	Float						(CKey::*GetValue							)(void) const;
	Float						(CKey::*GetValueLeft					)(void) const;
	Float						(CKey::*GetValueRight					)(void) const;
	CINTERPOLATION	(CKey::*GetInterpolation			)(void) const;
	void						(CKey::*SetTime								)(CCurve *seq, const BaseTime &t);
	void						(CKey::*SetTimeLeft						)(CCurve *seq, const BaseTime &t);
	void						(CKey::*SetTimeRight					)(CCurve *seq, const BaseTime &t);
	void						(CKey::*SetValue							)(CCurve *seq, Float v);
	void						(CKey::*SetValueLeft					)(CCurve *seq, Float v);
	void						(CKey::*SetValueRight					)(CCurve *seq, Float v);
	void						(CKey::*SetGeData							)(CCurve *seq, const GeData &d);
	void						(CKey::*SetInterpolation			)(CCurve *seq, CINTERPOLATION inter);
	CTrack*					(CKey::*GetTrackCKey					)(void);
	CCurve*					(CKey::*GetSequenceCKey				)(void);
	const GeData&		(CKey::*GetGeData							)(void) const;
	CKey*						(*CKey_Alloc									)(void);
	void						(*CKey_Free										)(CKey *&ckey);

	Int32						(CCurve::*GetKeyCount					)(void) const;
	CKey*						(CCurve::*GetKey1							)(Int32 index);
	const CKey*			(CCurve::*GetKey2							)(Int32 index) const;
	CKey*						(CCurve::*FindKey1						)(const BaseTime &time, Int32 *nidx, FINDANIM match);
	const CKey*			(CCurve::*FindKey2						)(const BaseTime &time, Int32 *nidx, FINDANIM match) const;
	CKey*						(CCurve::*AddKeyEx						)(const BaseTime &time, Int32 *nidx);
	Bool						(CCurve::*InsertKeyEx					)(const CKey *key);
	Bool						(CCurve::*DelKeyEx						)(Int32 index);
	Int32						(CCurve::*MoveKeyEx						)(const BaseTime &time, Int32 idx, CCurve *dseq);
	void						(CCurve::*FlushKeysEx					)(void);
	void						(CCurve::*SortKeysByTimeEx		)(void);
	void						(CCurve::*CalcSoftTangents		)(Int32 kidx, Float *vl, Float *vr, BaseTime *tl, BaseTime *tr) const;
	Float64					(CCurve::*CalcHermite					)(Float64 time, Float64 t1, Float64 t2, Float64 val1, Float64 val2, Float64 tan1_val, Float64 tan2_val, Float64 tan1_t, Float64 tan2_t, Bool deriv) const;
	void						(CCurve::*GetTangents					)(Int32 kidx, Float64 *vl, Float64 *vr, Float64 *tl, Float64 *tr) const;

	Float						(CCurve::*GetValue1						)(const BaseTime &time, Int32 fps) const;
	CTrack*					(CCurve::*GetTrackCSeq				)(void);

	CTrack*					(*CTrackAlloc									)(BaseList2D *bl, const DescID &id);
	Bool						(CTrack::*Animate							)(const CAnimInfo *info, Bool *chg, void *data);
	const DescID&		(CTrack::*GetDescriptionID		)(void) const;
	Bool						(CTrack::*SetDescriptionID		)(BaseList2D *object, const DescID &id);

	Bool						(CTrack::*Draw								)(GeClipMap *map, const BaseTime &clip_left, const BaseTime &clip_right) const;
	CLOOP						(CTrack::*GetBefore						)(void) const;
	CLOOP						(CTrack::*GetAfter						)(void) const;
	void						(CTrack::*SetBefore						)(CLOOP type);
	void						(CTrack::*SetAfter						)(CLOOP type);

	CTrack*					(CTrack::*GetTimeTrack				)(BaseDocument *doc);
	CCurve*					(CTrack::*GetCurve						)(CCURVE type, Bool bCreate);
	void						(CTrack::*SetTimeTrack				)(CTrack *track);
	void						(CTrack::*FlushData						)(void);
	Float						(CTrack::*GetValue3						)(BaseDocument *doc, const BaseTime &time, Int32 fps);
	Bool						(CTrack::*Remap								)(Float64 time, Float64 *ret_time, Int32 *ret_cycle) const;
	Int32						(CTrack::*GuiMessage					)(const BaseContainer &msg, BaseContainer &result);
	Int32						(CTrack::*GetHeight						)();
	Bool						(CTrack::*FillKey							)(BaseDocument *doc, BaseList2D *bl, CKey *key);
	Bool						(CTrack::*TrackInformation		)(BaseDocument *doc, CKey *key, String *str, Bool set);

	const BaseContainer *(CTrack::*GetParameterDescription)(BaseContainer &temp) const;

	Int32						(CTrack::*GetTrackCategory		)(void) const;
	Bool						(CTrack::*AnimateTrack				)(BaseDocument *doc, BaseList2D *op, const BaseTime &tt, const Int32 flags, Bool *chg, void *data);
	Int32						(CTrack::*GetUnit							)(Float *step);

	Int32						(CTrack::*GetTLHeight					)(Int32 id);
	void						(CTrack::*SetTLHeight					)(Int32 id, Int32 size);

	BaseTime				(CCurve::*GetStartTime				)(void) const;
	BaseTime				(CCurve::*GetEndTime					)(void) const;

	CKey*						(CCurve::*FindNextUnmuted1		)(Int32 idx, Int32 *ret_idx);
	const CKey*			(CCurve::*FindNextUnmuted2		)(Int32 idx, Int32 *ret_idx) const;

	CKey*						(CCurve::*FindPrevUnmuted1		)(Int32 idx, Int32 *ret_idx);
	const CKey*			(CCurve::*FindPrevUnmuted2		)(Int32 idx, Int32 *ret_idx) const;

	CKey*						(CCurve::*AddKeyAdaptTangentEx)(const BaseTime &time, Bool bUndo, Int32 *nidx);

	CAUTOMODE				(CKey::*GetAutomaticTangentMode)(void) const;
	void						(CKey::*SetAutomaticTangentMode)(CCurve *seq, CAUTOMODE inter);

	Bool						(CKey::*SetTimeLeftAdjustValue)(CCurve *seq, const BaseTime &t);
	Bool						(CKey::*SetTimeRightAdjustValue)(CCurve *seq, const BaseTime &t);

	Bool						(CTrack::*IsSynchronized)(void) const;
	void						(CTrack::*SetSynchronized)(Bool synch);

	ROTATIONINTERPOLATION (CKey::*GetQuatInterpolation)(void) const;
	void									(CKey::*SetQuatInterpolation)(CCurve *seq, ROTATIONINTERPOLATION inter, Bool bUndo, Bool synchronize);

	CKey*						(CCurve::*AddKeyAdaptTangent)(const BaseTime &time, Bool bUndo, Int32 *nidx, Bool bSynchronize);
	CKey*						(CCurve::*AddKey)(const BaseTime &time, Int32 *nidx, Bool bUndo, Bool bSynchronize);
	Bool						(CCurve::*InsertKey)(const CKey *key, Bool bUndo, Bool bSynchronize);
	Bool						(CCurve::*DelKey)(Int32 index, Bool bUndo, Bool bSynchronize);
	Int32						(CCurve::*MoveKey)(const BaseTime &time, Int32 idx, CCurve *dseq, Bool bUndo, Bool bSynchronize);
	void						(CCurve::*FlushKeys)(Bool bUndo, Bool bSynchronize);
	void						(CCurve::*SortKeysByTime)(Bool bUndo, Bool bSynchronize);
};


class GeSndInfo;

struct C4D_BaseSound
{
	BaseSound*			(*Alloc								)(void);
	void						(*Free								)(BaseSound *bs);
	BaseSound*			(*GetClone						)(BaseSound *bs);
	Bool						(*CopyTo							)(BaseSound *bs, BaseSound *dest);
	Bool						(*InitEx							)(BaseSound *bs, Int32 samples, Int32 fmode, Bool stereo, Bool b16);
	void						(*FlushAll						)(BaseSound *bs);
	Bool						(*Load								)(BaseSound *bs, const Filename *fn);
	Bool						(*Save								)(BaseSound *bs, const Filename *fn);
	void						(*GetSampleEx					)(BaseSound *bs, Int32 i, SDataEx *data);
	void						(*SetSampleEx					)(BaseSound *bs, Int32 i, SDataEx *data);
	BaseBitmap*			(*GetBitmap						)(BaseSound *bs, Int32 width, Int32 height, const BaseTime &start, const BaseTime &stop);
	Char*						(*GetRAWEx						)(BaseSound *bs);
	Bool						(*WriteIt							)(BaseSound *bs, HyperFile *hf);
	Bool						(*ReadIt							)(BaseSound *bs, HyperFile *hf, Int32 level);
	BaseBitmap*			(*GetBitmap2					)(BaseSound *bs, Int32 width, Int32 height, const BaseTime &start, const BaseTime &stop, const Vector &draw_col, const Vector &back_col);
	GeListHead*			(*GetMarkerRoot				)(BaseSound *bs);
	BaseSound*			(*GetClonePart				)(BaseSound *bs,	const BaseTime &start,	const BaseTime &stop,	Bool reverse);
	Char*						(*GetSoundInfoEx			)(BaseSound *bs, Bool *stereo, Bool *b16, Int32 *frequency, Int32 *samples, BaseTime *length);
	Bool						(*Init								)(BaseSound *bs, Int sample_cnt, Float frequency, Int32 channel_cnt);
	void						(*GetSoundInfo				)(BaseSound *bs, GeSndInfo *info);
};

struct C4D_BaseDraw
{
	// BaseDraw
	Bool						(*HasCameraLink				)(BaseDraw *bd);
	BaseObject*			(*GetEditorCamera			)(BaseDraw *bd);
	Vector					(*CheckColor					)(BaseDraw *bd, const Vector &col);
	void						(*SetTransparency			)(BaseDraw *bd, Int32 trans);
	Int32						(*GetTransparency			)(BaseDraw *bd);
	Bool						(*PointInRange				)(BaseDraw *bd, const Vector &p, Int32 x, Int32 y);
	void						(*SetPen							)(BaseDraw *bd, const Vector &col, Int32 flags);
	Float						(*SimpleShade					)(BaseDraw *bd, const Vector &p, const Vector &n);
	void						(*DrawPoint2D					)(BaseDraw *bd, const Vector &p);
	void						(*DrawLine2D					)(BaseDraw *bd, const Vector &p1, const Vector &p2);
	void						(*DrawHandle2D				)(BaseDraw *bd, const Vector &p, DRAWHANDLE type);
	void						(*DrawCircle2D				)(BaseDraw *bd, Int32 mx, Int32 my, Float rad);
	DRAWRESULT			(*DrawPObject					)(BaseDraw *bd, BaseDrawHelp *bh, BaseObject *op, DRAWOBJECT drawpolyflags, DRAWPASS drawpass, BaseObject* parent, const Vector &col);

	// BaseDrawHelp
	BaseDocument*		(*BbGetDocument				)(BaseDrawHelp *bb);
	BaseTag*				(*BbGetActiveTag			)(BaseDrawHelp *bb);
	const Matrix&		(*BbGetMg							)(BaseDrawHelp *bb);
	void						(*BbGetDisplay				)(BaseDrawHelp *bb, BaseContainer *bc);
	void						(*BbSetDisplay				)(BaseDrawHelp *bb, BaseContainer *bc);
	void						(*BbSetMg							)(BaseDrawHelp *bb, const Matrix &mg);
	DRAWFLAGS				(*BbGetViewSchedulerFlags)(const BaseDrawHelp *bb);
	BaseDrawHelp		*(*BbAlloc							)(BaseDraw *bd, BaseDocument *doc);
	void						(*BbFree							)(BaseDrawHelp *&p);

	BaseObject*			(*GetSceneCamera			)(BaseDraw *bd, const BaseDocument *doc);
	Vector					(*GetObjectColor			)(BaseDraw *bd, BaseObject *op, BaseDrawHelp *bh, Bool lines);
	void						(*LineZOffset					)(BaseDraw *bd, Int32 offset);
	void						(*SetMatrix_Projection)(BaseDraw *bd);
	void						(*SetMatrix_Screen		)(BaseDraw *bd);
	void						(*SetMatrix_Camera		)(BaseDraw *bd);
	void						(*SetMatrix_Matrix		)(BaseDraw *bd, BaseObject *op, const Matrix &mg);
	void						(*DrawLine						)(BaseDraw *bd, const Vector &p1, const Vector &p2, Int32 flags);
	void						(*LineStripBegin			)(BaseDraw *bd);
	void						(*LineStrip						)(BaseDraw *bd, const Vector &vp, const Vector &vc, Int32 flags);
	void						(*LineStripEnd				)(BaseDraw *bd);
	void						(*DrawHandle					)(BaseDraw *bd, const Vector &vp, DRAWHANDLE type, Int32 flags);
	void						(*DrawTexture					)(BaseDraw *bd, const BaseBitmap *bmp, Vector *padr4, Vector *cadr, Vector *vnadr, Vector *uvadr, Int32 pntcnt, DRAW_ALPHA alphamode, DRAW_TEXTUREFLAGS flags);
	void						(*SetLightList				)(BaseDraw *bd, Int32 mode);

	void						(*InitUndo						)(BaseDraw *bd, BaseDocument *doc);
	void						(*DoUndo							)(BaseDraw *bd, BaseDocument *doc);
	void						(*SetDrawParam				)(BaseDraw *bd, Int32 id, const GeData &data);
	GeData					(*GetDrawParam				)(BaseDraw *bd, Int32 id);

	void						(*DrawPoly						)(BaseDraw *bd, Vector *vp, Vector *vf, Vector *vn, Int32 anz, Int32 flags);
	DISPLAYFILTER		(*GetDisplayFilter		)(BaseDraw *bd);
	DISPLAYEDITSTATE(*GetEditState			)(BaseDraw *bd);
	Bool						(*IsViewOpen					)(BaseDraw *bd, BaseDocument *doc);

	void						(*DrawCircle					)(BaseDraw *bd, const Matrix &m);
	void						(*DrawBox							)(BaseDraw *bd, const Matrix &m, Float size, const Vector &col, Bool wire);
	void						(*DrawPolygon					)(BaseDraw *bd, Vector *p, Vector *f, Bool quad);
	void						(*DrawSphere					)(BaseDraw *bd, const Vector &off, const Vector &size, const Vector &col, Int32 flags);
	Bool						(*TestBreak						)(BaseDraw *bd);
	void						(*DrawArrayEnd				)(BaseDraw *bd);
	OITInfo&				(*GetOITInfo					)(BaseDraw *bd);
	Int32						(*GetGlLightCount			)(const BaseDraw *bd);
	const GlLight*	(*GetGlLight					)(const BaseDraw *bd, Int32 lIndex);

	Bool						(*GetFullscreenPolygonVectors)(BaseDraw *bd, Int32 &lAttributeCount, const GlVertexBufferAttributeInfo* const *&ppAttibuteInfo, Int32 &lVectorInfoCount, const GlVertexBufferVectorInfo* const* &ppVectorInfo);
	Bool						(*DrawFullscreenPolygon)(BaseDraw *bd, Int32 lVectorInfoCount, const GlVertexBufferVectorInfo* const* ppVectorInfo);
	Bool						(*AddToPostPass				)(BaseDraw *bd, BaseObject *op, BaseDrawHelp *bh, Int32 flags);
	Bool						(*GetDrawStatistics		)(const BaseDraw* bd, BaseContainer &bc);

	void						(*SetMatrix_MatrixO			)(BaseDraw *bd, BaseObject *op, const Matrix &mg, Int32 zoffset);
	void						(*SetMatrix_ScreenO			)(BaseDraw *bd, Int32 zoffset);
	void						(*SetMatrix_CameraO			)(BaseDraw *bd, Int32 zoffset);

	EditorWindow*		(*GetEditorWindow)(BaseDraw *bd);

	void						(*DrawPointArray			)(BaseDraw *bd, Int32 cnt, const Vector32 *vp, const Float32 *vc, Int32 colcnt, const Vector32 *vn);
	void						(*DrawTexture1				)(BaseDraw *bd, C4DGLuint bmp, Vector *padr4, Vector *cadr, Vector *vnadr, Vector *uvadr, Int32 pntcnt, DRAW_ALPHA alphamode);
	void						(*InitClipbox					)(BaseDraw *bd, Int32 left, Int32 top, Int32 right, Int32 bottom, Int32 flags);
	void						(*InitView						)(BaseDraw *bd, BaseContainer *camera, const Matrix &op_m, Float sv, Float pix_x, Float pix_y, Bool fitview);
	void						(*InitializeView			)(BaseDraw *bd, BaseDocument *doc, BaseObject *cam, Bool editorsv);
	void						(*SetTexture					)(BaseDraw *bd, BaseBitmap *bm, Bool tile, DRAW_ALPHA alphamode, DRAW_TEXTUREFLAGS flags);
	void						(*SetSceneCamera			)(BaseDraw *bd, BaseObject *op, Bool animate);
	void						(*SetMatrix_ScreenOM	)(BaseDraw *bd, Int32 zoffset, const Matrix4d* m);

	Bool						(*InitDrawXORLine			)(BaseDraw *bd);
	void						(*FreeDrawXORLine			)(BaseDraw *bd);
	void						(*DrawXORPolyLine			)(BaseDraw *bd, const Float32* p, Int32 cnt);
	void						(*BeginDrawXORPolyLine)(BaseDraw *bd);
	void						(*EndDrawXORPolyLine	)(BaseDraw *bd, Bool blit);
	BaseDraw*				(*AllocBaseDraw				)();
	void						(*FreeBaseDraw				)(BaseDraw*& bv);

	Bool						(*DrawScene						)(BaseDraw* bd, Int32 flags);
	DISPLAYMODE			(*GetReductionMode		)(const BaseDraw* bd);
	void						(*GlDebugString				)(BaseDraw* bd, Bool bConsoleOutput, const char* pszFormat, ...);
	void						(*SetPointSize				)(BaseDraw* bd, Float pointsize);
	Vector					(*ConvertColor				)(BaseDraw* bd, const Vector &c);
	Vector					(*ConvertColorReverse	)(BaseDraw* bd, const Vector &c);
	void						(*SetDepth						)(BaseDraw* bd, Bool enable);

	void						(*DrawArc							)(BaseDraw* bd, const Vector &pos, Float radius, Float angle_start, Float angle_end, Int32 subdiv, Int32 flags);
	DRAWPASS				(*GetDrawPass					)(const BaseDraw* bd);
	void						(*SetClipPlaneOffset	)(BaseDraw* bd, Float o);
	Bool						(*BbIsActive					)(const BaseDrawHelp *bb);
	Bool						(*BbIsHighlight				)(const BaseDrawHelp *bb);
	Bool						(*GetHighlightPassColor)(const BaseDraw* bd, const BaseDrawHelp& bh, Bool lineObject, Vector &col);
	GlFrameBuffer*	(*GetHighlightFramebuffer)(BaseDraw* bd, const Vector32& vMin, const Vector32& vMax);
	void						(*GetGridStep					)(BaseDraw* bd, Float &step, Float &fade);
	void						(*AddMessageHook			)(BaseDraw *bd, BaseDrawMessageHook fn);
	Bool						(*IsOpenGL						)(BaseDraw *bd);
	Bool						(*IsEnhancedOpenGL		)(BaseDraw *bd);

	void						(*DrawHUDText					)(BaseDraw* bd, Int32 x, Int32 y, const String& text);
	void						(*DrawMultipleHUDText	)(BaseDraw* bd, const maxon::BaseArray<HUDTextEntry>& texts);
};

struct C4D_BaseView
{
	void						(*GetFrame						)(BaseView *bv, Int32 *cl, Int32 *ct, Int32 *cr, Int32 *cb);
	void						(*GetSafeFrameEx			)(BaseView *bv, Int32 *from, Int32 *to, Int32 *horizontal);
	void						(*GetParameter				)(const BaseView *bv, Vector *offset, Vector *scale, Vector *scale_z);
	Matrix					(*GetMg								)(BaseView *bv);
	Matrix					(*GetMi								)(BaseView *bv);
	Int32						(*GetProjection				)(BaseView *bv);
	Bool						(*TestPoint						)(BaseView *bv, Float x, Float y);
	Bool						(*TestPointZ					)(BaseView *bv, const Vector &p);
	Bool						(*TestClipping3D			)(BaseView *bv, const Vector &mp, const Vector &rad, const Matrix &mg, Bool *clip2d, Bool *clipz);
	Bool						(*ClipLine2D					)(BaseView *bv, Vector *p1, Vector *p2);
	Bool						(*ClipLineZ						)(BaseView *bv, Vector *p1, Vector *p2);
	Vector					(*WS									)(BaseView *bv, const Vector &p);
	Vector					(*SW									)(BaseView *bv, const Vector &p);
	Vector					(*SW_R								)(BaseView *bv, Float x, Float y, const Vector &wp);
	Vector					(*WC									)(BaseView *bv, const Vector &p);
	Vector					(*CW									)(BaseView *bv, const Vector &p);
	Vector					(*SC									)(BaseView *bv, const Vector &p);
	Vector					(*CS									)(BaseView *bv, const Vector &p, Bool z_inverse);
	Vector					(*WC_V								)(BaseView *bv, const Vector &v);
	Vector					(*CW_V								)(BaseView *bv, const Vector &v);
	Bool						(*BackfaceCulling			)(BaseView *bv, const Vector &n, const Vector &p);
	Bool						(*ZSensitiveNear			)(BaseView *bv);

	ViewportSelect*	(*VSAlloc							)();
	void						(*VSFree							)(ViewportSelect *&p);
	Bool						(*VSInitObj						)(ViewportSelect *vs, Int32 w, Int32 h, BaseDraw* bd, BaseObject* op, Int32 mode, Bool onlyvisible, VIEWPORTSELECTFLAGS flags);
	Bool						(*VSInitAr						)(ViewportSelect *vs, Int32 w, Int32 h, BaseDraw* bd, AtomArray* ar, Int32 mode, Bool onlyvisible, VIEWPORTSELECTFLAGS flags);
	ViewportPixel*	(*VSGetPixelInfoPoint	)(ViewportSelect *vs, Int32 x, Int32 y);
	ViewportPixel*	(*VSGetPixelInfoPolygon)(ViewportSelect *vs, Int32 x, Int32 y);
	ViewportPixel*	(*VSGetPixelInfoEdge	)(ViewportSelect *vs, Int32 x, Int32 y);
	void						(*VSShowHotspot				)(ViewportSelect *p, EditorWindow *bw, Int32 x, Int32 y);
	void						(*VSSetBrushRadius		)(ViewportSelect *p, Int32 r);
	void						(*VSClearPixelInfo		)(ViewportSelect *vs, Int32 x, Int32 y, UChar mask);
	Bool						(*VSGetCameraCoordinates)(ViewportSelect *vs, Float x, Float y, Float z, Vector &v);
	Float						(*ZSensitiveNearClipping)(BaseView *bv);
	Bool						(*VSDrawPolygon				)(ViewportSelect *vs, const Vector* p, Int32 ptcnt, Int32 i, BaseObject* op, Int32 onlyvisible);
	Bool						(*VSDrawHandle				)(ViewportSelect *vs, const Vector& p, Int32 i, BaseObject* op, Int32 onlyvisible);
	Int32						(*GetFrameScreen			)(BaseDraw *bv, Int32 *cl, Int32 *ct, Int32 *cr, Int32 *cb);
	const Matrix4d&	(*GetViewMatrix				)(BaseDraw *bv, Int32 n);
	ViewportPixel*	(*VSGetNearestPoint		)(ViewportSelect *vs, BaseObject* op, Int32 &x, Int32 &y, Int32 maxrad, Bool onlyselected, Int32* ignorelist, Int32 ignorecnt);
	ViewportPixel*	(*VSGetNearestPolygon	)(ViewportSelect *vs, BaseObject* op, Int32 &x, Int32 &y, Int32 maxrad, Bool onlyselected, Int32* ignorelist, Int32 ignorecnt);
	ViewportPixel*	(*VSGetNearestEdge		)(ViewportSelect *vs, BaseObject* op, Int32 &x, Int32 &y, Int32 maxrad, Bool onlyselected, Int32* ignorelist, Int32 ignorecnt);
	void						(*VSShowHotspotS			)(EditorWindow *bw, Int32 x, Int32 y, Int32 rad, Bool bRemove);
	Bool						(*VSPickObject				)(BaseDraw* bd, BaseDocument* doc, Int32 x, Int32 y, Int32 rad, VIEWPORT_PICK_FLAGS flags, LassoSelection* ls, C4DObjectList* list, Matrix4d* m);
	StereoCameraInfo*	(*GetStereoInfo			)(const BaseView* bd);
	void						(*OverrideCamera			)(BaseDraw* bd, StereoCameraInfo* si);
	Bool						(*ZSensitiveFar				)(BaseView *bv);
	Float						(*ZSensitiveFarClipping)(BaseView *bv);

	Float						(*PW_S								)(BaseView *bv, Float z, Bool horizontal);
	Float						(*WP_S								)(BaseView *bv, Float z, Bool horizontal);
	Float						(*PW_W								)(BaseView *bv, const Vector &p, Bool horizontal);
	Float						(*WP_W								)(BaseView *bv, const Vector &p, Bool horizontal);

	void						(*GetSafeFrame				)(BaseView *bv, Int32 *cl, Int32 *ct, Int32 *cr, Int32 *cb);

	Vector					(*ProjectPointOnLine	)(BaseView *bv, const Vector &p, const Vector &v, Float mouse_x, Float mouse_y, Float *offset, Int32 *err);
	Vector					(*ProjectPointOnPlane	)(BaseView *bv, const Vector &p, const Vector &v, Float mouse_x, Float mouse_y, Int32 *err);
	const Matrix&		(*GetBaseMatrix				)(const BaseView* bv);
	void						(*SetBaseMatrix				)(BaseView* bv, const Matrix &m);
	Float						(*GetPlanarRotation		)(const BaseView* bv);
	void						(*SetPlanarRotation		)(BaseView* bv, Float r);

	Bool						(*VSPickObject1				)(BaseDraw* bd, BaseDocument* doc, Int32 x, Int32 y, Int32 rad, Int32 &xr, Int32 &yr, Int32 &wr, Int32 &hr, ViewportPixel **&pixels, VIEWPORT_PICK_FLAGS flags, LassoSelection* ls, C4DObjectList* list, Matrix4d* m);
	Bool						(*VSPickObject2				)(BaseDraw* bd, BaseDocument* doc, Int32 x1, Int32 y1, Int32 x2, Int32 y2, Int32 &xr, Int32 &yr, Int32 &wr, Int32 &hr, ViewportPixel **&pixels, VIEWPORT_PICK_FLAGS flags, LassoSelection* ls, C4DObjectList* list, Matrix4d* m);

	Vector					(*WS_V								)(BaseView *bv, const Vector &v, const Vector &p);
	Vector					(*SW_V								)(BaseView *bv, const Vector &v, const Vector &p);
};

struct C4D_Pool
{
	DeprecatedMemoryPool*			(*Alloc								)(Int block_size);
	void						(*Free								)(DeprecatedMemoryPool *pool);
	void*						(*AllocElement				)(DeprecatedMemoryPool *pool, Int size, Bool clear);
	void						(*FreeElement					)(DeprecatedMemoryPool *pool, void *mem, Int size);
	void*						(*AllocElementS				)(DeprecatedMemoryPool *pool, Int size, Bool clear);
	void						(*FreeElementS				)(DeprecatedMemoryPool *pool, void *mem);
	void*						(*ReAllocElementS			)(DeprecatedMemoryPool *pool, void* old, Int size, Bool clear);
};

typedef Int32		(*GeExecuteProgramExCallback)(Int32 cmd, void *userdata, const Filename &logfile);
typedef Int32		(*GeFileMonitorCallback)(const Filename &item, Int flags, void *userdata);

struct C4D_General
{
	void						(*Free								)(void *data);
	void						(*Print								)(const String &str);

	Bool						(*FExist							)(const Filename *name, Bool isdir);
	Bool						(*SearchFile					)(const Filename *directory, const Filename *name, Filename *found);
	Bool						(*FKill								)(const Filename *name, Int32 flags);
	Bool						(*FCopyFile						)(const Filename *source, const Filename *dest, Int32 flags);
	Bool						(*FRename							)(const Filename *source, const Filename *dest);
	Bool						(*FCreateDir					)(const Filename *name);
	Bool						(*ExecuteFile					)(const Filename *path);
	const Filename	(*GetStartupPath			)(void);
	Bool						(*ExecuteProgram			)(const Filename *program, const Filename *file);

	void						(*ShowMouse						)(Int32 v);
	void						(*GetSysTime					)(Int32 *year, Int32 *month, Int32 *day, Int32 *hour, Int32 *minute, Int32 *second);
	Int32						(*GetTimer						)(void);
	void						(*GetLineEnd					)(String *str);
	Int32						(*GetDefaultFPS				)(void);
	GEMB_R					(*OutString						)(const String *str, GEMB flags);
	OPERATINGSYSTEM	(*GetCurrentOS			)(void);
	BYTEORDER				(*GetByteOrder				)(void);
	void						(*GetGray							)(Int32 *r, Int32 *g, Int32 *b);
	Bool						(*ChooseColor					)(Vector *col, Int32 flags);
	void						(*SetMousePointer			)(Int32 l);
	Bool						(*ShowBitmap1					)(const Filename *fn);
	Bool						(*ShowBitmap2					)(BaseBitmap *bm);
	void						(*StopAllThreads			)(void);
	void						(*StatusClear					)(void);
	void						(*StatusSetSpin				)(void);
	void						(*StatusSetBar				)(Int32 p);
	void						(*StatusSetText				)(const String *str);
	void						(*SpecialEventAdd			)(Int32 type, UInt p1, UInt p2);
	Bool						(*DrawViews						)(DRAWFLAGS flags, BaseDraw *bd);
	void						(*GetGlobalTexturePath)(Int32 i, Filename *fn);
	void						(*SetGlobalTexturePath)(Int32 i, const Filename *fn);
	void						(*FlushUnusedTextures	)(void);
	void						(*GetWorldContainer		)(BaseContainer *bc);
	void						(*ErrorStringDialog		)(CHECKVALUERANGE type, Float x, Float y, CHECKVALUEFORMAT is);

	void						(*InsertBaseDocument	)(BaseDocument *doc);
	void						(*SetActiveDocument		)(BaseDocument *doc);
	BaseDocument*		(*GetActiveDocument		)(void);
	BaseDocument*		(*GetFirstDocument		)(void);
	void						(*KillDocument				)(BaseDocument *doc);
	Bool						(*LoadFile						)(const Filename *name);
	Bool						(*SaveDocument				)(BaseDocument *doc, const Filename &name, SAVEDOCUMENTFLAGS saveflags, Int32 format);
	RENDERRESULT		(*RenderDocumentEx		)(BaseDocument *doc, ProgressHook *prog, void *private_data, BaseBitmap *bmp, const BaseContainer *rdata, RENDERFLAGS renderflags, BaseThread *th);
	Vector					(*GetColor						)(Int32 i);
	Bool						(*RegisterPlugin			)(Int32 api_version, PLUGINTYPE type, Int32 id, const String *str, void *data, Int32 datasize);
	void						(*GetSerialInfo				)(SERIALINFO type, String *s1, String *s2, String *s3, String *s4, String *s5, String *s6);
	VERSIONTYPE			(*GetVersionType			)(void);
	Bool						(*ReadPluginInfo			)(Int32 pluginid, Char *buffer, Int32 size);
	Bool						(*WritePluginInfo			)(Int32 pluginid, Char *buffer, Int32 size);

	void						(*EwDrawXORLine				)(EditorWindow *win, Int32 x1, Int32 y1, Int32 x2, Int32 y2);
	void						(*EwMouseDragStart		)(EditorWindow *win, Int32 button, Float mx, Float my, MOUSEDRAGFLAGS flag);
	MOUSEDRAGRESULT	(*EwMouseDrag					)(EditorWindow *win, Float *mx, Float *my, BaseContainer *channels);
	MOUSEDRAGRESULT	(*EwMouseDragEnd			)(EditorWindow *win);
	Bool						(*EwBfGetInputState		)(EditorWindow *win, Int32 askdevice, Int32 askchannel, BaseContainer *res);
	Bool						(*EwBfGetInputEvent		)(EditorWindow *win, Int32 askdevice, BaseContainer *res);

	Bool						(*RegistryAdd					)(Int32 sub_id, REGISTRYTYPE main_id, void *data);
	Bool						(*RegistryRemove			)(Int32 sub_id, REGISTRYTYPE main_id);
	Registry*				(*RegistryFind				)(Int32 sub_id, REGISTRYTYPE main_id);
	Registry*				(*RegistryGetLast			)(REGISTRYTYPE main_id);
	Registry*				(*RegistryGetFirst		)(REGISTRYTYPE main_id);
	Bool						(*RegistryGetAutoID		)(Int32 *id);
	Bool						(*RegistryGetData			)(Registry *reg, REGISTRYTYPE *main_id, Int32 *sub_id, void **data);

	void*						(*Alloc								)(Int size, Int32 line, const Char *file);
	BaseContainer*	(*GetWorldPluginData	)(Int32 id);
	Bool						(*SetWorldPluginData	)(Int32 id, const BaseContainer *bc, Bool add);
	Bool						(*SyncMessage					)(Int32 message, Int32 core_id, Int par1, Int par2);
	void						(*SetWorldContainer		)(const BaseContainer *bc);
	Bool						(*PluginMessage				)(Int32 id, void *data);

	BasePlugin*			(*FindPlugin										)(Int32 id, PLUGINTYPE type);
	BasePlugin*			(*GetFirstPlugin								)(void);
	void*						(BasePlugin::*GetPluginStructure)();
	Filename				(BasePlugin::*GetFilename				)(void);
	Int32						(BasePlugin::*GetID							)(void) const;
	Int32						(BasePlugin::*GetInfo						)(void) const;

	Bool						(*ChooseFont					)(BaseContainer *col);

	void						(*GeDebugBreak				)(Int32 line, const Char *file);
	void						(*GeDebugOut					)(const Char* s, ...);
	Bool						(*RenameDialog				)(String *str);
	Bool						(*OpenHTML						)(const String &webaddress);
	Bool						(*SendModelingCommand )(Int32 command, ModelingCommandData &data);

	void						(*EventAdd						)(EVENT flags);
	void						(*FindInManager				)(BaseList2D *bl);

	CUSTOMDATATYPEPLUGIN*		(*FindCustomDataTypePlugin		)(Int32 type);
	RESOURCEDATATYPEPLUGIN*	(*FindResourceDataTypePlugin	)(Int32 type);

	void						(*GeSleep							)(Int32 milliseconds);
	GeData					(*SendCoreMessage			)(Int32 coreid, const BaseContainer &msg, Int32 eventid);
	Bool						(*CheckIsRunning			)(CHECKISRUNNING type);
	BaseContainer*	(*GetWorldContainerInstance)(void);

	Bool						(*GenerateTexturePathEx	)(const Filename &docpath, const Filename &srcname, const Filename &suggestedpath, Filename *dstname);
	Bool						(*IsInSearchPath				)(const Filename &texfilename, const Filename &docpath);

	BaseContainer*	(*GetToolPluginData		)(BaseDocument *doc, Int32 id);
	Bool						(*IsMainThread				)(void);

	Filename				(*GetDefaultFilename	)(Int32 id);

	Bool						(*AddBackgroundHandler					)(BackgroundHandler *handler, void *tdata, Int32 typeclass, Int32 priority);
	Bool						(*RemoveBackgroundHandler				)(void *tdata, Int32 typeclass);
	void						(*StopBackgroundThreads					)(Int32 typeclass, BACKGROUNDHANDLERFLAGS flags);
	Bool						(*CheckBackgroundThreadsRunning	)(Int32 typeclass, Bool all);
	void						(*ProcessBackgroundThreads			)(Int32 typeclass);

	void						(*FlushTexture									)(const Filename *docpath, const String *name, const Filename &suggestedfolder);

	Bool						(*GetMovieInfo									)(const Filename *name, Int32 *frames, Float *fps);
	String					(*GetObjectName									)(Int32 type);
	String					(*GetTagName										)(Int32 type);
	Int32						(*GetObjectType									)(const String &name);
	Int32						(*GetTagType										)(const String &name);

	void						(*CopyToClipboard								)(const String &str);

	void*						(*AllocNC												)(Int size, Int32 line, const Char *file);
	BaseContainer*	(*GetToolData										)(BaseDocument *doc, Int32 pluginid);
	Bool						(*GeGetMemoryStat								)(BaseContainer &stat);
	Bool						(*PopupEditText									)(Int32 screenx, Int32 screeny, Int32 width, Int32 height, const String &changeme, Int32 flags, PopupEditTextCallback *func, void *userdata);

	Bool						(*EWScreen2Local								)(EditorWindow *win, Int32 *x, Int32 *y);
	Bool						(*EWLocal2Screen								)(EditorWindow *win, Int32 *x, Int32 *y);

	void						(*StartEditorRender							)(Bool active_only, Bool raybrush, Int32 x1, Int32 y1, Int32 x2, Int32 y2, BaseThread *bt, BaseDraw *bd, Bool newthread);

	GeData					(*StringToNumber								)(const String &text, Int32 format, Int32 fps, const LENGTHUNIT *unit);

	Bool						(*IsActiveToolEnabled						)();
	SYSTEMINFO			(*GetSystemInfo									)(void);
	Bool						(*PrivateSystemFunction01				)(void *par1);
	Bool						(*GetLanguage										)(Int32 index, String *extension, String *name, Bool *default_language);

	GeListHead*			(*GetScriptHead									)(Int32 type);
	Int32						(*GetDynamicScriptID						)(BaseList2D *bl);
	Float						(*GetToolScale									)(BaseDraw* bd, AtomArray* arr, Int32 all, Int32 mode);
	Bool						(*GetCommandLineArgs						)(C4DPL_CommandLineArgs &args);
	Bool						(*FilterPluginList							)(AtomArray &arr, PLUGINTYPE type, Bool sortbyname);

	Bool						(*LoadDocumentExEx							)(BaseDocument *doc, const Filename &name, SCENEFILTER loadflags, BaseThread *bt);
	void						(*FrameScene										)(BaseDocument *doc);
	IDENTIFYFILE		(*IdentifyFile									)(const Filename &name, UChar *probe, Int32 probesize, IDENTIFYFILE recognition, BasePlugin **bp);
	const Filename	(*GetC4DPath										)(Int32 whichpath);

	Bool						(*FMove													)(const Filename &source, const Filename &dest);

	Bool						(*HandleViewCommand							)(Int32 command_id, BaseDocument *doc, BaseDraw *bd, Int32 *value);

	Bool						(*AddUndoHandler								)(BaseDocument *doc, void *dat, UNDOTYPE type);

	String					(*GeGetDegreeChar								)();
	String					(*GeGetPercentChar							)();
	Bool						(*HandleCommand									)(Int32 command_id, Int32 *value);

	void						(*lSwap													)(void *adr, Int cnt);
	void						(*wSwap													)(void *adr, Int cnt);
	void						(*lIntel												)(void *adr, Int cnt);
	void						(*wIntel												)(void *adr, Int cnt);
	void						(*lMotor												)(void *adr, Int cnt);
	void						(*wMotor												)(void *adr, Int cnt);
	void						(*llSwap												)(void *adr, Int cnt);
	void						(*llIntel												)(void *adr, Int cnt);
	void						(*llMotor												)(void *adr, Int cnt);

	void*						(*GeCipher256Open								)(const UChar *key, Int32 klength, Bool stream);
	void						(*GeCipher256Close							)(void* h);

	NetworkIpConnection*		(*OpenWaitForIncomingEx				)(NetworkIpConnection* listener, BaseThread* connection, Int32* ferr);
	void										(*CloseConnectionEx						)(NetworkIpConnection* ipc);
	void										(*KillConnectionEx						)(NetworkIpConnection* ipc);
	Int											(*BytesInInputBufferEx				)(NetworkIpConnection* ipc);
	Int											(*RecvBytesEx									)(NetworkIpConnection* ipc, void* buf, Int size);
	Int											(*SendBytesEx									)(NetworkIpConnection* ipc, void* buf, Int size);
	void										(*GetHostAddrEx								)(NetworkIpConnection* ipc, Char* buf, Int32 bufsize);
	void										(*GetRemoteAddrEx							)(NetworkIpConnection* ipc, Char* buf, Int32 bufsize);

	Bool						(*RecordCommandEx								)(Int32 command_id, Int32 subid, const String &str);

	Bool						(*SendMailAvailable							)();
	Bool						(*SendMail											)(const String &t_subject, const String *t_to, const String *t_cc, const String *t_bcc, Filename *t_attachments, const String &t_body, Int32 flags);
	Bool						(*GetSystemEnvironmentVariable	)(const String &varname, String &result);
	Bool						(*CallHelpBrowser								)(const String &optype, const String &main, const String &group, const String &property);
	String					(*FormatNumber									)(const GeData &val, Int32 format, Int32 fps, Bool bUnit, LENGTHUNIT *unit);

	void						(*BuildGlobalTagPluginContainer		)(BaseContainer *plugincontainer, Int32 *id);
	Int32						(*ResolveGlobalTagPluginContainer	)(Int32 *id);
	Vector					(*GetGuiWorldColor								)(Int32 cid);

	Int32						(*GetShortcutCount							)();
	BaseContainer		(*GetShortcut										)(Int32 index);
	Bool						(*AddShortcut										)(const BaseContainer &bc);
	Bool						(*RemoveShortcut								)(Int32 index);
	Bool						(*LoadShortcutSet								)(const Filename &fn, Bool add);
	Bool						(*SaveShortcutSet								)(const Filename &fn);
	Int32						(*FindShortcutsFromID						)(Int32 pluginid, Int32 *indexarray, Int32 maxarrayelements);
	Int32						(*FindShortcuts									)(const BaseContainer &scut, Int32 *pluginidarray, Int32 maxarrayelements);
	void						(*SetViewColor									)(Int32 colid, const Vector &col);

	void						(*RemovePlugin									)(BasePlugin *plug);

	Bool						(*GetAllocSize									)(void *p, Int *out_size);
	void						(*InsertCreateObject						)(BaseDocument *doc, BaseObject *op, BaseObject *activeobj);

	void						(*GeCipher256Encrypt						)(void *h, UChar *mem, Int32 size);
	void						(*GeCipher256Decrypt						)(void *h, UChar *mem, Int32 size);

	NetworkIpConnection*		(*IpOpenListenerEx							)(UInt32 ipAddr, Int32 port, BaseThread* thread, Int32 timeout, Bool dontwait, Int32* ferr);
	NetworkIpConnection*		(*IpOpenOutgoingEx							)(Char* hostname, BaseThread* thread, Int32 initial_timeout, Int32 timeout, Bool dontwait, Int32* ferr);

	String					(*DateToString									)(const LocalFileTime &t, Bool date_only);
	Bool						(*ShowInFinder									)(const Filename &fn, Bool open);

	Bool						(*WriteLayout										)(const Filename &fn);
	Bool						(*WritePreferences							)(const Filename &fn);
	Bool						(*SaveProjectCopy								)(BaseDocument *t_doc, const Filename &directory, Bool allow_gui);

	Int32						(*ShowPopupMenu									)(CDialog *parent, Int32 screenx, Int32 screeny, const BaseContainer *bc, Int32 flags, Int32 *res_mainid);

	Bool						(*AskForAdministratorPrivileges	)(const String &msg, const String &caption, Bool bAllowSuperUser, void **token);
	void						(*EndAdministratorPrivileges		)();
	void						(*RestartApplication						)(const Utf16Char* param, Int32 exitcode, const Utf16Char** path);
	const Filename	(*GetStartupApplication					)(void);

	Bool						(*EWGlobal2Local								)(EditorWindow *win, Int32 *x, Int32 *y);
	Bool						(*EWLocal2Global								)(EditorWindow *win, Int32 *x, Int32 *y);

	Bool						(*RequestFileFromServer					)(const Filename &fn, Filename &res);
	Bool						(*ReadPluginReg									)(Int32 pluginid, Char *buffer, Int32 size);
	Bool						(*WritePluginReg								)(Int32 pluginid, Char *buffer, Int32 size);
	Bool						(*GeFGetDiskFreeSpace						)(const Filename &vol, UInt64 &freecaller, UInt64 &total, UInt64 &freespace);
	UInt32						(*GeFGetAttributes							)(const Filename *name);
	Bool						(*GeFSetAttributes							)(const Filename *name, UInt32 flags, UInt32 mask);

	void						(*BrowserLibraryPopup						)(Int32 mx, Int32 my, Int32 defw, Int32 defh, Int32 pluginwindowid, Int32 presettypeid, void *userdata, BrowserPopupCallback callback);
	Bool						(*GeExecuteProgramEx						)(const Filename &program, const String *args, Int32 argcnt, GeExecuteProgramExCallback callback, void *userdata);
	Float64					(*GeGetMilliSeconds							)(void);

	void*						(*ReallocNC											)(void *old_data, Int new_size, Int32 line, const Char *file);
	Bool						(*GeGetAllocatorStatistics			)(BaseContainer &stat, void *in_allocator);
	UInt						(*GeMemGetFreePhysicalMemoryEstimate)(void);
	void						(*CopyToClipboardB							)(BaseBitmap *map, Int32 ownerid);
	Bool						(*GetStringFromClipboard				)(String *txt);
	Bool						(*GetBitmapFromClipboard				)(BaseBitmap *map);
	CLIPBOARDTYPE		(*GetClipboardType							)(void);

	void						(*EndGlobalRenderThread					)(Bool external_only);
	Int32						(*GeDebugSetFloatingPointChecks	)(Int32 on);
	Int32						(*GetC4DClipboardOwner					)(void);
	void						(*GeCheckMem										)(void *memptr);

	Bool						(*GetFileTime										)(const Filename &name, Int32 mode, LocalFileTime *out);
	Bool						(*SetFileTime										)(const Filename &name, Int32 mode, const LocalFileTime *in);
	void						(*GetCurrentTime								)(LocalFileTime *out);

	void						(*GeUpdateUI										)();
	Float						(*CalculateTranslationScale			)(const UnitScaleData *src_unit, const UnitScaleData *dst_unit);
	Int32						(*CheckPythonColor							)(const String &txt);

	void							(*PrintNoCR											)(const String &str);
	const BaseBitmap*	(*GetCursorBitmap							)(Int32 type, Int32 &hotspotx, Int32 &hotspoty);
	Filename*					(*GetLocalFilename							)(void);

	Bool						(*LoadDocumentEx								)(BaseDocument *doc, const Filename &name, SCENEFILTER loadflags, BaseThread *bt, BaseDocument *srcdoc);
	Bool						(*CheckCommandShortcut					)(Int32 id, Int32 key, Int32 qual);
	BasePlugin*			(*CreatePluginEntry							)(const String &foldername, BasePlugin *bs);
	void						(*SetLocalHierarchy							)(BasePlugin *parent, BasePlugin *pred);

	Bool						(*RecordCommand									)(Int32 command_id, Int32 subid, const String &str, SCRIPTMODE mode);
	Bool						(*PyRecordCommand								)(Int32 command_id, Int32 subid, const String &str, SCRIPTMODE mode);

	void						(*PrintClean										)(const Char *buf);

	Bool						(*WatchFolder										)(const Filename &folder, GeFileMonitorCallback callback, void *userdata);
	Bool						(*DontWatchFolder								)(const Filename &folder, GeFileMonitorCallback callback, void *userdata);
	Bool						(*WatchFile											)(const Filename &file, GeFileMonitorCallback callback, void *userdata);
	Bool						(*DontWatchFile									)(const Filename &file, GeFileMonitorCallback callback, void *userdata);
	Bool						(*ShutdownThreads								)(Bool shutdown);

	void*						(*AllocTH												)(Int32 threadidx, Int size, Bool clear);
	void						(*FreeTH												)(Int32 threadidx, void *&ptr);

	Bool						(*GetScreenDimensions						)(Int32 x, Int32 y, Bool whole_screen, Int32 *sx1, Int32 *sy1, Int32 *sx2, Int32 *sy2);

	Int32						(*GetCOFFEEDictionaryID					)(Int32 num);
	String*					(*GetCOFFEEDictionaryName				)(Int32 num);
	Int32						(*GetCOFFEEDictionaryCount			)();
	Bool						(*GetCOFFEEDictionaryState			)();

	Int32						(*EwBfIsHotkeyDown							)(EditorWindow *win, Int32 id);

	void						(*ForceStopApplication					)(Bool value);

	Bool						(*SaveProject										)(BaseDocument *doc, SAVEPROJECT flags, Filename targetPath, maxon::BaseArray<AssetEntry>* assets, maxon::BaseArray<AssetEntry>* missingAssets);
	Bool						(*GetAllAssetsEx								)(BaseDocument *doc, Bool allowDialogs, maxon::BaseArray<AssetEntry>& assets, Filename& lastPath);

	RENDERRESULT		(*RenderDocument								)(BaseDocument *doc, WriteProgressHook *wprog, ProgressHook *prog, void *private_data, BaseBitmap *bmp, const BaseContainer *rdata, RENDERFLAGS renderflags, BaseThread *th, void *data);

	UInt32					(*GetCinemaInfo									)(CINEMAINFO info);
	void						(*SaveWorldPreferences					)();
	Bool						(*Assemble											)(const Filename &inputpath, const String &inputname, BaseContainer& rdata, WriteProgressHook* wprog, void* context, Bool assembleRegular, Bool assembleMultipass, BaseThread *bt, Int32 ifrom, Int32 ito, String *errorstring, Int32 streamstart, Int32 streamcnt, const maxon::BaseArray<String>& stereoimages, Bool clearimages);

	String					(*GetMacModel										)(const String& macmodel);

	Filename				(*FilterSetSuffix								)(const Filename &name, Int32 id);

	void						(*StatusNetClear					)(void);
	void						(*StatusSetNetLoad				)(STATUSNETSTATE status);
	void						(*StatusSetNetBar					)(Int32 p, const GeData& dat);
	void						(*StatusSetNetText				)(const String *str);

	Bool						(*LoadDocument						)(BaseDocument *doc, const Filename &name, SCENEFILTER loadflags, BaseThread *bt, BaseDocument *srcdoc, String* errString);
	Bool						(*GenerateTexturePath			)(const Filename &docpfad, const Filename &texturname, const Filename &suggestedfolder, Filename *filename, NetRenderService* client, BaseThread* bt);

	void						(*RenderExternal					)(BaseDocument* doc, Bool useNet);
	Bool						(*PVFinalizeImage					)(BaseBitmap* t_bmp, void* userdata);
	Filename				(*GenEndung								)(const Filename &bildname, Int32 bildformat, Int32 nameformat, Int32 bildnum, const String &streamname, String *middle, Bool clearsuffix, Bool stream_folders);

	void						(*SetExitCode							)(Int32 exitCode);
	Bool						(*GetAllAssets						)(BaseDocument *doc, Bool allowDialogs, Bool withCaches, maxon::BaseArray<AssetEntry>& assets, Filename& lastPath, Bool isNet);
	RENDERRESULT		(*RenderDocumentNet				)(BaseDocument *doc, WriteProgressHook *wprog, ProgressHook *prog, void *private_data, BaseBitmap *bmp, const BaseContainer *rdata, RENDERFLAGS renderflags, BaseThread *th, void *data, const maxon::BaseArray<Bool>* renderTask);
	void						(*OpenHelpBrowser)(const String &optype, const String &main, const String &group, const String &property);
	Bool						(*RegisterPluginHelpDelegate)(Int32, Bool (*)(const String &optype, const String &main, const String &group, const String &property));
	Bool						(*IteratePluginHelpDelegates)(const String &optype, const String &main, const String &group, const String &property);

	Filename				(*GetCurrentLayout)();

	Bool						(*IsMainThreadAndNoDrawThread)();
};

struct C4D_Link
{
	BaseLink*				(*Alloc								)(void);
	void						(*Free								)(BaseLink *link);
	BaseList2D*			(*GetLink							)(const BaseLink *link, const BaseDocument *doc, Int32 instanceof);
	void						(*SetLink							)(BaseLink *link, C4DAtomGoal *list);
	Bool						(*Read								)(BaseLink *link, HyperFile *hf);
	Bool						(*Write								)(const BaseLink *link, HyperFile *hf);
	BaseLink*				(*GetClone						)(const BaseLink *link, COPYFLAGS flags, AliasTrans *trn);
	Bool						(*CopyTo							)(const BaseLink *src, BaseLink *dst, COPYFLAGS flags, AliasTrans *trn);
	AliasTrans*			(*TrnAlloc						)(void);
	Bool						(*TrnInit							)(AliasTrans *trn, const BaseDocument *doc);
	void						(*TrnFree							)(AliasTrans *trn);
	void						(*TrnTranslate				)(AliasTrans *trn, Bool connect_oldgoals);
	BaseList2D*			(*ForceGetLink				)(const BaseLink *link);
	Bool						(*IsCacheLink					)(const BaseLink *link);
	C4DAtomGoal*		(*GetLinkAtom					)(const BaseLink *link, const BaseDocument *doc, Int32 instanceof);
	C4DAtomGoal*		(*ForceGetLinkAtom		)(const BaseLink *link);
	void						(*SetUpPointer				)(BaseLink *link, C4DAtom *t_up_pointer);
};

struct C4D_Neighbor
{
	EnumerateEdges*	(*Alloc								)(Int32 pcnt, const CPolygon *vadr, Int32 vcnt, BaseSelect *bs);
	void						(*Free								)(EnumerateEdges *nb);
	void						(*GetEdgePolys				)(EnumerateEdges *nb, Int32 a, Int32 b, Int32 *first, Int32 *second);
	void						(*GetPointPolys				)(EnumerateEdges *nb, Int32 pnt, Int32 **dadr, Int32 *dcnt);
	Int32						(*GetEdgeCount				)(EnumerateEdges *nb);
	PolyInfo*				(*GetPolyInfo					)(EnumerateEdges *nb, Int32 poly);
	Bool						(*GetNGons						)(EnumerateEdges *nb, PolygonObject* op, Int32 &ngoncnt, NgonNeighbor *&ngons);
	void						(*ResetAddress				)(EnumerateEdges *nb, const CPolygon *a_polyadr);
};

struct C4D_Painter
{
	void*						(*SendPainterCommand	)(Int32 command, BaseDocument *doc, PaintTexture *tex, const BaseContainer *bc);
	Bool						(*CallUVCommand				)(const Vector *padr, Int32 PointCount, const CPolygon *polys, Int32 lPolyCount, UVWStruct *uvw, BaseSelect *polyselection,
																					BaseSelect* pointselection, BaseObject*op, Int32 mode, Int32 cmdid, const BaseContainer &settings);

	TempUVHandle*		(*GetActiveUVSet			)(BaseDocument* doc, Int32 flags);
	void						(*FreeActiveUVSet			)(TempUVHandle *handle);

	Int32						(*UVSetGetMode				)(TempUVHandle *handle);
	const Vector*		(*UVSetGetPoint				)(TempUVHandle *handle);
	Int32						(*UVSetGetPointCount	)(TempUVHandle *handle);
	const CPolygon*	(*UVSetGetPoly				)(TempUVHandle *handle);
	Int32						(*UVSetGetPolyCount		)(TempUVHandle *handle);
	UVWStruct*			(*UVSetGetUVW					)(TempUVHandle *handle);
	BaseSelect*			(*UVSetGetPolySel			)(TempUVHandle *handle);
	BaseSelect*			(*UVSetGetPointSel		)(TempUVHandle *handle);
	BaseObject*			(*UVSetGetBaseObject	)(TempUVHandle *handle);

	Bool						(*UVSetSetUVW					)(TempUVHandle *handle, UVWStruct *uv);

	Bool						(*Private1						)(Int32 lCommand, AtomArray* pArray, BaseSelect **polyselection, BaseContainer& setttings, BaseThread* th);

	PaintTexture*		(*CreateNewTexture		)(const Filename &path, const BaseContainer &settings);
	Bool						(*GetTextureDefaults	)(Int32 channel, BaseContainer &settings);

	Bool						(*UVSetIsEditable			)(TempUVHandle *handle);

	Int32						(*IdentifyImage				)(const Filename &texpath);
	Bool						(*BPSetupWizardWithParameters)(BaseDocument *doc, const BaseContainer &settings, AtomArray &objects, AtomArray &material);

	Bool						(*CalculateTextureSize)(BaseDocument *doc, AtomArray &materials, TextureSize *&sizes);

	Int32						(*PB_GetBw)(PaintBitmap *bmp);
	Int32						(*PB_GetBh)(PaintBitmap *bmp);
	PaintLayer*			(*PB_GetLayerDownFirst)(PaintBitmap *tex);
	PaintLayer*			(*PB_GetLayerDownLast)(PaintBitmap *tex);
	PaintLayerBmp*	(*PT_AddLayerBmp)(PaintTexture *tex, PaintLayer *insertafter, PaintLayer *layerset, COLORMODE mode, Bool useundo, Bool activate);
	GeListHead*			(*PT_GetPaintTextureHead)();
	Bool						(*PLB_ImportFromBaseBitmap)(PaintLayerBmp *layer, BaseBitmap *bmp, Bool usealpha);
	Bool						(*PLB_ImportFromBaseBitmapAlpha)(PaintLayerBmp *layer, BaseBitmap *bmp, BaseBitmap *channel);
	Bool						(*PLB_GetPixelCnt)(PaintLayerBmp *layer, Int32 x, Int32 y, Int32 num, PIX *dst, COLORMODE dstmode, PIXELCNT flags);
	PaintTexture*		(*GetPaintTextureOfBaseChannel)(BaseDocument *doc, BaseChannel *bc);

	LayerSet*				(*LSL_Alloc)();
	void						(*LSL_Free)(LayerSet *layerset);
	Bool						(*LSL_Content)(const LayerSet *l);
	Bool						(*LSL_IsLayerEnabled)(const LayerSet *l, const String &name);
	Bool						(*LSL_FindLayerSet)(const LayerSet *l, const String &name);
	String					(*LSL_GetName)(const LayerSet *l);
	LAYERSETMODE		(*LSL_GetMode)(const LayerSet *l);
	void						(*LSL_SetMode)(LayerSet *l, LAYERSETMODE t_mode);
	void						(*LSL_RemoveLayer)(LayerSet *l, const String &layer);
	void						(*LSL_AddLayer)(LayerSet *l, const String &layer);
	void						(*LSL_FlushLayers)(LayerSet *l);
	Bool						(*LSL_operator_cmp)(const LayerSet *l, const LayerSet &layerset);
	void						(*LSL_CopyTo)(const LayerSet *l, LayerSet &dst);
	Bool						(*GetAllStrings_AddTexture)(const void *msgdata, const BaseContainer &d);

	PaintTexture*		(*PB_GetPaintTexture)(PaintBitmap *bmp);
	PaintBitmap*		(*PB_GetParent)(PaintBitmap *bmp);
	PaintLayer*			(*PB_GetAlphaFirst)(PaintBitmap *bmp);
	PaintLayer*			(*PB_GetAlphaLast)(PaintBitmap *bmp);
	PaintLayerBmp*	(*PB_AddAlphaChannel)(PaintBitmap *bmp, Int32 bitdepth, PaintLayer *prev, Bool undo, Bool activate);
	Bool						(*PB_AskApplyAlphaMask)(PaintBitmap *bmp);
	void						(*PB_ApplyAlphaMask)(PaintBitmap *bmp, Int32 x, Int32 y, Int32 num, PIX *bits, Int32 mode, Bool inverted, Int32 flags);
	PaintLayerMask*	(*PB_FindSelectionMask)(PaintBitmap *bmp, PaintBitmap **toplevel, Int32 *bitdepth);
	Int32						(*PB_GetColorMode)(PaintBitmap *bmp);
	UInt32					(*PB_GetDirty)(PaintBitmap *bmp, DIRTYFLAGS flags);
	void						(*PB_UpdateRefresh)(PaintBitmap *bmp, Int32 xmin, Int32 ymin, Int32 xmax, Int32 ymax, UInt32 flags);
	void						(*PB_UpdateRefreshAll)(PaintBitmap *bmp, UInt32 flags, Bool reallyall);
	Bool						(*PB_ReCalc)(PaintBitmap *bmpthis, BaseThread *thread, Int32 x1, Int32 y1, Int32 x2, Int32 y2, BaseBitmap *bmp, Int32 flags, UInt32 showbit);
	Bool						(*PB_ConvertBits)(Int32 num, const PIX *src, Int32 srcinc, COLORMODE srcmode, PIX *dst, Int32 dstinc, COLORMODE dstmode, Int32 dithery, Int32 ditherx);
	Bool						(*PLB_SetPixelCnt)(PaintLayerBmp *layer, Int32 x, Int32 y, Int32 num, const PIX *src, Int32 incsrc, COLORMODE srcmode, PIXELCNT flags);
	void						(*PLB_GetBoundingBox)(PaintLayerBmp *layer, Int32 &x1, Int32 &y1, Int32 &x2, Int32 &y2, Bool hasselectionpixels);
	PaintLayerFolder*(*PT_AddLayerFolder)(PaintTexture *tex, PaintLayer *insertafter, PaintLayer *insertunder, Bool useundo, Bool activate);
	void						(*PT_SetActiveLayer)(PaintTexture *tex, PaintLayer *layer, Bool activatetexture, Bool show);
	PaintLayer*			(*PT_GetActive)(PaintTexture *tex);
	void						(*PT_GetLinkLayers)(PaintTexture *tex, AtomArray &layers, Bool addfolders);
	Bool						(*PT_SetSelected_Texture)(PaintBitmap *bmp, PaintMaterial *preferred);
	PaintTexture*		(*PT_GetSelectedTexture)();
	PaintTexture*		(*PT_GetSelectedTexturePP)(PaintMaterial **ppmat);
	void						(*PM_EnableMaterial)(PaintMaterial *, BaseDocument *doc, Bool on, Bool suppressevent, Bool domaterialundo);
	PaintMaterial*	(*PM_GetActivePaintMaterial)(BaseDocument *doc, BaseMaterial **mat);
	PaintMaterial*	(*PM_GetPaintMaterialFromTexture)(PaintTexture *tex, Bool onlyeditable);
	PaintMaterial*	(*PM_GetPaintMaterial)(BaseDocument *dok, BaseMaterial *material, Int32 create);
	Bool						(*PM_UnloadPaintMaterial)(BaseDocument *doc, BaseMaterial *material, Bool forcesave);
	Bool						(*PT_SetColorMode)(PaintTexture *tex, COLORMODE newcolormode, Bool doundo);

	void						(*LSL_SetPreviewMode)(LayerSet *l, Int32 mode);
	Int32						(*LSL_GetPreviewMode)(const LayerSet *l);
	LayerSetHelper *(*LSH_Alloc)();
	void						(*LSH_Free)(LayerSetHelper *lsh);
	Bool						(*LSH_Init)(LayerSetHelper *lsh, const Filename &fn, const LayerSet *selection);
	Bool						(*LSH_EditLayerSet)(LayerSetHelper *lsh, const String &dialogtitle, LayerSet *layerset, LayerSet *layerset_a);

	Bool						(*CLL_CalculateResolution)(BaseDocument *doc, const Filename &filename, Int32 *xres, Int32 *yres);
	Bool						(*CLL_CalculateFilename)(BaseDocument *doc, Filename &fn, LayerSet *lsl);

	Bool						(*PL_GetShowBit)(PaintLayer *bmp, Bool hierarchy, UInt32 bit);
	Bool						(*PL_SetShowBit)(PaintLayer *bmp, Bool onoff, UInt32 bit);
	PaintTexture*		(*PT_CreateNewTextureDialog)(String &result, Filename &resultdirectory, Int32 channelid, BaseMaterial *bmat);
	void						(*PN_ActivateChannel)(Int32 channel, Bool multi, Bool enable);
	const Filename	(*PT_GetFilename)(PaintTexture *tex);

	Bool						(*LSH_MergeLayerSet)(LayerSetHelper *lsh, const LayerSet &selection, BaseBitmap *bmp, Bool preview);
	Bool						(*PM_AskNeedToSave)(BaseDocument *doc);
	Bool						(*PM_SaveDocument)(BaseDocument *doc, Bool& cancel);

	BaseSelect*			(*UVSetGetPolyHid)(TempUVHandle *handle);
	Bool						(*UVSetSetUVWFromTextureView)(TempUVHandle *handle, UVWStruct *uv, Bool ignoreHidden, Bool ignoreUnselected, Bool autoSelectAll, Bool registerUndo);

	Bool									(*PT_SetColorProfile)(PaintTexture* text, const ColorProfile &profile);
	const ColorProfile&		(*PT_GetColorProfile)(const PaintTexture* tex);
};

struct C4D_GLSL
{
	void						(GlString::*SDKInit1)();
	void						(GlString::*SDKInit2)(const char* pchString);
	void						(GlString::*SDKInit3)(const GlString& str);
	void						(GlString::*SDKInit4)(Int32 n);
	void						(GlString::*SDKInit5)(Float r, const char* pszFormat);
	void						(GlString::*SDKFree)();

	const GlString&	(GlString::*SDKAssign1)(const GlString &str);
	const GlString&	(GlString::*SDKAssign2)(const char* pszString);

	GlString				(*GlStringAdd1)(const GlString &str1, const GlString &str2);
	GlString				(*GlStringAdd2)(const GlString &str1, const char* str2);

	const GlString&	(GlString::*GlStringAdd3)(const GlString &str);
	const GlString&	(GlString::*GlStringAdd4)(const char* str);

	const char*			(GlString::*GetCString)() const;
	Int							(GlString::*GetLength)() const;
	Int32						(GlString::*Compare)(const GlString &s) const;
	Int32						(GlString::*Replace)(const GlString& strSearch, const GlString &strReplace, Int lStart, Bool bReplaceAll, Bool bOnlyWord);

	// GlProgramFactory
	GlProgramFactory*	(*GetFactory)(const BaseDraw* pBaseDraw, const C4DAtom* pObj, UInt64 ulIndex, GlProgramFactoryMessageCallback fnCallback, void* pIdentity, Int lIdentityLength,
		const GlLight* const* ppLights, Int32 lLightCount, UInt64 ulFlags,
		const GlVertexBufferAttributeInfo* const* ppBufferAttributeInfo, Int32 lBufferAttributeInfoCount,
		const GlVertexBufferVectorInfo* const* ppBufferVectorInfo, Int32 lBufferVectorInfoCount,
		GlFBAdditionalTextureInfo* pAdditionalTextures);
	void						(*RemoveReference)(const C4DAtom* pObj, UInt64 lIndex);
	void						(*RemoveTextureReferenceA)(const C4DAtom* pObj, Int32 lIndex);
	void						(*RemoveTextureReferenceB)(const Filename &fn);
	void*						(*IncreaseBufferSize)(GlGetIdentity* pIdentity, Int lNeededSize, Int32 lLine, const char* pszFile);
	UInt32					(GlProgramFactory::*InitEx)(Int32 lSubdivideCount);

	Bool						(GlProgramFactory::*BindToView)(const BaseDraw* pDraw);
	Bool						(GlProgramFactory::*CompilePrograms)();
	Bool						(GlProgramFactory::*BindPrograms)();
	Bool						(GlProgramFactory::*UnbindPrograms)();
	Bool						(GlProgramFactory::*DestroyPrograms)(Bool bChangeContext);
	void						(GlProgramFactory::*LockFactory)();
	void						(GlProgramFactory::*UnlockFactory)();
	void*						(GlProgramFactory::*GetPrivateData)(const void* pObj, Int32 lDataIndex, GlProgramFactoryAllocPrivate fnAlloc, GlProgramFactoryFreePrivate fnFree);
	void*						(GlProgramFactory::*GetDescriptionDataEx)(Int32 lObjIndex, Int32 lDataIndex, GlProgramFactoryAllocDescription fnAlloc, GlProgramFactoryFreeDescription fnFree);
	Bool						(GlProgramFactory::*IsProgram)(GlProgramType t);

	void						(GlProgramFactory::*InitSetParameters)();
	void						(GlProgramFactory::*SetScreenCoordinates)(BaseDraw* pBaseDraw);
	void						(GlProgramFactory::*AddErrorHandler)(GlProgramFactoryErrorHandler fn);
	Bool						(GlProgramFactory::*SetParameterMatrixTransform)(GlProgramParameter param);
	Bool						(GlProgramFactory::*SetParameterMatrix1)(GlProgramParameter param, const Matrix4d32 &m);
	Bool						(GlProgramFactory::*SetParameterMatrix2)(GlProgramParameter paramOffset, GlProgramParameter paramAxes, GlProgramParameter paramNormalTrans, const Matrix32 &m);
	Bool						(GlProgramFactory::*SetParameterMatrix3x3)(GlProgramParameter param, const Float32* r);
	Bool						(GlProgramFactory::*SetParameterMatrix4x4)(GlProgramParameter param, const Float32* r);
	Bool						(GlProgramFactory::*SetParameterVector1)(GlProgramParameter param, const Vector32 &v);
	Bool						(GlProgramFactory::*SetParameterVector2)(GlProgramParameter param, const Vector4d32 &v);
	Bool						(GlProgramFactory::*SetParameterVector3)(GlProgramParameter param, const Vector32 &v, Float32 w);
	Bool						(GlProgramFactory::*SetParameterColor1)(GlProgramParameter param, const Vector &v, Float rBrightness);
	Bool						(GlProgramFactory::*SetParameterColor2)(GlProgramParameter param, const Vector &v, Float rBrightness, Float32 rAlpha);
	Bool						(GlProgramFactory::*SetParameterColorReverse1)(GlProgramParameter param, const Vector &v, Float rBrightness);
	Bool						(GlProgramFactory::*SetParameterColorReverse2)(GlProgramParameter param, const Vector &v, Float rBrightness, Float32 rAlpha);
	Bool						(GlProgramFactory::*SetParameterReal)(GlProgramParameter param, Float32 r);
	Bool						(GlProgramFactory::*SetParameterReal2a)(GlProgramParameter param, Float32 a, Float32 b);
	Bool						(GlProgramFactory::*SetParameterReal2b)(GlProgramParameter param, const Float32* v);
	Bool						(GlProgramFactory::*SetParameterReal3a)(GlProgramParameter param, Float32 a, Float32 b, Float32 c);
	Bool						(GlProgramFactory::*SetParameterReal3b)(GlProgramParameter param, const Float32* v);
	Bool						(GlProgramFactory::*SetParameterReal4a)(GlProgramParameter param, Float32 a, Float32 b, Float32 c, Float32 d);
	Bool						(GlProgramFactory::*SetParameterReal4b)(GlProgramParameter param, const Float32* v);
	Bool						(GlProgramFactory::*SetParameterTexture)(GlProgramParameter param, Int32 lDimension, C4DGLuint nTexture);
	Bool						(GlProgramFactory::*SetParameterTextureCube)(GlProgramParameter param, C4DGLuint nTexture);
	Bool						(GlProgramFactory::*SetParameterTexture2D1)(GlProgramParameter param, const BaseBitmap* pBmp, Int32 lFlags, DRAW_ALPHA alphamode, C4DGLuint* pnHandle);
	Bool						(GlProgramFactory::*SetParameterTexture2D2)(GlProgramParameter param, const Filename &fn, Int32 lFrame, C4DAtom* pObj, Int32 lIndex, Int32 lFlags, DRAW_ALPHA alphamode, Int32 lMaxSize, const LayerSet* pLayerSet, GlTextureInfo* pInfo, C4DGLuint* pnHandle);
	Bool						(GlProgramFactory::*SetParameterTexture2D3)(GlProgramParameter param, const BaseBitmap* pBmp, UInt32 ulDirty, C4DAtom* pObj, Int32 lIndex, Int32 lFlags, DRAW_ALPHA alphamode, Int32 lMaxSize, GlTextureInfo* pInfo, C4DGLuint* pnHandle);
	Bool						(GlProgramFactory::*SetParameterTextureGradient)(GlProgramParameter param, const Gradient* pGradient, C4DAtom* pObj, Int32 lIndex, Int32 lFlags, C4DGLuint* pnHandle);
	Bool						(GlProgramFactory::*SetParameterTextureFunction)(GlProgramParameter param, C4DAtom* pObj, Int32 lIndex, Int32 lFlags, Int32 lDataType, GlProgramFactoryCreateTextureFunctionCallback fn, void* pData, Int lDataLen, Int32 lInParams, Int32 lOutParams, Int32 lCycle, Bool bInterpolate, Int32 lSizeX, Int32 lSizeY, Int32 lSizeZ, Bool bParallel, C4DGLuint* pnHandle);
	Bool						(GlProgramFactory::*SetParameterTextureRaw)(GlProgramParameter param, C4DAtom* pObj, Int32 lIndex, Int32 lFlags, Int32 lDataType, const void* pData, Int lDataLen, UInt32 ulDirty, Int32 lDimension, Int32 lComponents, Int32 lCycle, Bool bInterpolate, Int32 lSizeX, Int32 lSizeY, Int32 lSizeZ, C4DGLuint* pnHandle);
	Bool						(GlProgramFactory::*SetParameterTextureCubeMap)(GlProgramParameter param, C4DAtom* pObj, Int32 lIndex, Int32 lFlags, Int32 lDataType, GlProgramFactoryCreateTextureFunctionCallback fn, void* pData, Int lDataLen,	Int32 lOutParams, Int32 lCycle, Bool bInterpolate, Int32 lSize, Bool bParallel, C4DGLuint* pnHandle);
	Bool						(GlProgramFactory::*SetParameterInt)(GlProgramParameter param, int r);
	Bool						(GlProgramFactory::*SetParameterInt2a)(GlProgramParameter param, int a, int b);
	Bool						(GlProgramFactory::*SetParameterInt2b)(GlProgramParameter param, const int* v);
	Bool						(GlProgramFactory::*SetParameterInt3a)(GlProgramParameter param, int a, int b, int c);
	Bool						(GlProgramFactory::*SetParameterInt3b)(GlProgramParameter param, const int* v);
	Bool						(GlProgramFactory::*SetParameterInt4a)(GlProgramParameter param, int a, int b, int c, int d);
	Bool						(GlProgramFactory::*SetParameterInt4b)(GlProgramParameter param, const int* v);
	Bool						(GlProgramFactory::*SetParameterUint)(GlProgramParameter param, unsigned int r);
	Bool						(GlProgramFactory::*SetParameterUint2a)(GlProgramParameter param, unsigned int a, unsigned int b);
	Bool						(GlProgramFactory::*SetParameterUint2b)(GlProgramParameter param, const unsigned int* v);
	Bool						(GlProgramFactory::*SetParameterUint3a)(GlProgramParameter param, unsigned int a, unsigned int b, unsigned int c);
	Bool						(GlProgramFactory::*SetParameterUint3b)(GlProgramParameter param, const unsigned int* v);
	Bool						(GlProgramFactory::*SetParameterUint4a)(GlProgramParameter param, unsigned int a, unsigned int b, unsigned int c, unsigned int d);
	Bool						(GlProgramFactory::*SetParameterUint4b)(GlProgramParameter param, const unsigned int* v);
	Bool						(GlProgramFactory::*SetParameterRealArray)(GlProgramParameter param, Int32 lElements, const Float32 *r);
	Bool						(GlProgramFactory::*SetParameterTextureNormalizeCube)(GlProgramParameter param);
	Bool						(GlProgramFactory::*SetParameterTexture2DDepth)(GlProgramParameter param, C4DGLuint nTexture);
	Bool						(GlProgramFactory::*SetParameterTextureCubeDepth)(GlProgramParameter param, C4DGLuint nTexture);
	Bool						(GlProgramFactory::*SetLightParameters)(const GlLight* const* pLights, Int32 lLightCount, const Matrix4d32& mObject);

	Bool						(GlProgramFactory::*GetCgFXDescription)(BaseContainer* pbcDescription);
	Bool						(GlProgramFactory::*CompileCgFX)(const Filename& fn, UInt32 ulFlags);
	Bool						(GlProgramFactory::*BindCgFXPrograms)(Int32 lTechnique, Int32 lPass);

	void						(GlProgramFactory::*AddParametersEx)(UInt32 ulParameters, UInt32 ulFormat);
	UInt64					(GlProgramFactory::*GetParameters)() const;
	UInt32					(GlProgramFactory::*GetParameterFormatsEx)() const;
	GlString				(GlProgramFactory::*AddUniformParameter1)(GlProgramType t, GlUniformParamType type, const char* pszName);
	GlString				(GlProgramFactory::*AddUniformParameter2)(GlProgramType t, GlUniformParamType type, Int32 lCount, const char* pszName);
	Bool						(GlProgramFactory::*HeaderFinished)();
	Bool						(GlProgramFactory::*AddLightProjection)();
	void						(GlProgramFactory::*AddLine)(GlProgramType t, const GlString &strLine);
	void						(GlProgramFactory::*StartLightLoop)();
	Bool						(GlProgramFactory::*EndLightLoop)();
	GlString				(GlProgramFactory::*GetUniqueID)();
	Bool						(GlProgramFactory::*InitLightParameters)();
	Int32						(GlProgramFactory::*GetMaxLights)();
	const UChar*		(GlProgramFactory::*GetIdentity)() const;
	GlProgramParameter		(GlProgramFactory::*GetParameterHandle)(GlProgramType t, const char* pszName) const;
	GlString				(GlProgramFactory::*AddColorBlendFunction)(GlProgramType t, Int32 lBlendMode);
	GlString				(GlProgramFactory::*AddRGBToHSVFunction)(GlProgramType t);
	GlString				(GlProgramFactory::*AddHSVToRGBFunction)(GlProgramType t);
	GlString				(GlProgramFactory::*AddRGBToHSLFunction)(GlProgramType t);
	GlString				(GlProgramFactory::*AddHSLToRGBFunction)(GlProgramType t);
	Bool						(GlProgramFactory::*AddFunction)(GlProgramType t, const GlString &strFunction);
	const GlString&	(GlProgramFactory::*AddNoiseFunction)(GlProgramType t, Int32 lNoise, Int32 lFlags);
	Bool						(GlProgramFactory::*AddEncryptedBlock)(GlProgramType t, const char* pchData, Int lDataLength, const UChar* pchKey, Int32 lKeyLength);
	Bool						(GlProgramFactory::*EncryptBlock)(const GlString &strLine, const UChar* pchKey, Int32 lKeyLength, char *&pchData, Int &lDataLength, Bool bCStyle);
	void						(GlProgramFactory::*GetVectorInfo)(Int32 &lVectorCount, const GlVertexBufferVectorInfo* const* &ppVectorInfo) const;

	Bool						(*CacheTextureFn)(BaseDraw* pBaseDraw, const Filename &fn, Int32 lFrame, C4DAtom* pObj, Int32 lIndex, Int32 lFlags, DRAW_ALPHA alphamode, Int32 lMaxSize, GlProgramType progType, const LayerSet* pLayerSet, GlTextureInfo* pInfo, C4DGLuint* pnHandle);
	Bool						(*CacheTextureBmp)(BaseDraw* pBaseDraw, const BaseBitmap* pBmp, UInt32 ulDirty, C4DAtom* pObj, Int32 lIndex, Int32 lFlags, DRAW_ALPHA alphamode, Int32 lMaxSize, GlProgramType progType, GlTextureInfo* pInfo, C4DGLuint* pnHandle);
	UInt32					(*GetLanguageFeaturesEx)(Int32 lCompiler, Int32 lFlags);
	Bool						(*HasNoiseSupport)(GlProgramType t, Int32 lNoise, BaseDraw* pBaseDraw, Int32 lCompiler);
	Int32						(GlProgramFactory::*GetCompiler)();

	// GlFrameBuffer
	GlFrameBuffer*	(*GetFrameBuffer)(BaseDraw* pBaseDraw, UInt lID1, Int32 lID2, UINT nWidth, UINT nHeight, Int32 lColorTextureCount, Int32 lDepthTextureCount, Int32 lColorCubeCount, Int32 lDepthCubeCount, UInt32 ulFlags, Int32 lAAMode, GlFBAdditionalTextureInfo* pAdditionalTextures);
	void						(*RemoveObjectF)(BaseDraw* pBaseDraw, UInt lID1, Int32 lID2);
	GlFrameBuffer*	(*FindFrameBuffer)(BaseDraw* pBaseDraw, UInt lID1, Int32 lID2);

	void						(GlFrameBuffer::*PrepareForRenderingEx)(Int32 lTexture);
	void						(GlFrameBuffer::*SetInterpolationEx)(Int32 lInterpolate, Int32 lTexture);
	Bool						(GlFrameBuffer::*Activate)(BaseDraw* pBaseDraw);
	void						(GlFrameBuffer::*Deactivate)(BaseDraw* pBaseDraw);
	Bool						(GlFrameBuffer::*SetRenderTarget)(Int32 lTexture, Int32 lFlags);
	void						(GlFrameBuffer::*GetRatios)(Int32 lFlags, Float& rWidth, Float& rHeight);
	void						(GlFrameBuffer::*GetSize)(Int32 lFlags, UINT &nWidth, UINT &nHeight, Bool bFramesize);
	C4DGLuint				(GlFrameBuffer::*GetTexture)(Int32 lTexture, Int32 lFlags) const;
	Int32						(GlFrameBuffer::*SaveTextureToDisk)(BaseDraw* pBaseDraw, const Filename &fn, Int32 lTexture, Int32 lFlags);
	Bool						(GlFrameBuffer::*CopyToBitmap)(BaseDraw* pBaseDraw, BaseBitmap* pBmp, Int32 lTexture, Int32 lFlags);
	void						(GlFrameBuffer::*Clear1)();
	void						(GlFrameBuffer::*Clear2)(const Vector32 &vColor, Float32 rAlpha);
	Bool						(GlFrameBuffer::*DrawBufferEx)(Int32 lTexture, Int32 lFlags, Int32 lColorConversion, C4DGLint nConversionTexture, Float32 rAlpha, const Vector32 &vColor, Float32 xs1, Float32 ys1, Float32 xs2, Float32 ys2, Float32 xd1, Float32 yd1, Float32 xd2, Float32 yd2);
	Bool						(GlFrameBuffer::*IsNPOTBuffer)();
	Bool						(GlFrameBuffer::*CopyToBuffer)(void* pBuffer, Int lBufferSize, Int32 lTexture, Int32 lFlags) const;
	Bool						(GlFrameBuffer::*GetTextureData)(BaseDraw* pBaseDraw, Int32 x1, Int32 y1, Int32 x2, Int32 y2, void* pData, Int32 lTexture, Int32 lFlags) const;
	GlFBAdditionalTextureInfo*	(GlFrameBuffer::*GetAdditionalTexture)(Int32 lType, void* pBuffer) const;

	// GlVertexBuffer
	GlVertexBuffer*	(*GetVertexBuffer)(const BaseDraw* pBaseDraw, const C4DAtom* pObj, Int32 lIndex, void* pIdentity, Int lIdentityLen, UInt32 ulFlags);
	void						(*RemoveObjectV)(C4DAtom* pObj, Int32 lIndex);

	Bool						(GlVertexBuffer::*IsDirty)();
	void						(GlVertexBuffer::*SetDirty)(Bool bDirty);
	Bool						(*DrawSubBufferEx)(const BaseDraw* pBaseDraw, const GlVertexSubBufferData* pVertexSubBuffer, const GlVertexSubBufferData* pElementSubBuffer,
		Int32 lDrawinfoCount, const GlVertexBufferDrawSubbuffer* pDrawInfo,
		Int32 lVectorCount, const GlVertexBufferVectorInfo* const* ppVectorInfo,
		GlVertexBufferDrawElementCallback fnCallback, void* pCallbackData);
	GlVertexSubBufferData*	(GlVertexBuffer::*AllocSubBuffer)(const BaseDraw* pBaseDraw, GlVertexBufferSubBufferType type, Int lSize, const void* pData);
	GlVertexSubBufferData*	(GlVertexBuffer::*AllocIndexSubBuffer1)(const BaseDraw* pBaseDraw, Int32 lCount, UInt32* pulIndex, Int32 lMaxIndex);
	GlVertexSubBufferData*	(GlVertexBuffer::*AllocIndexSubBuffer2)(const BaseDraw* pBaseDraw, Int32 lCount, const UInt16* puwIndex);
	Bool						(GlVertexBuffer::*FlushAllSubBuffers)(const BaseDraw* pBaseDraw);
	Bool						(GlVertexBuffer::*FreeBuffers)(const BaseDraw* pBaseDraw, GlVertexBufferSubBufferType type);
	Bool						(GlVertexBuffer::*FreeBuffer)(const BaseDraw* pBaseDraw, GlVertexSubBufferData* pBuffer);
	Bool						(GlVertexBuffer::*MarkAllForDelete)();
	Bool						(GlVertexBuffer::*MarkBuffersForDelete)(GlVertexBufferSubBufferType type);
	Bool						(GlVertexBuffer::*MarkBufferForDelete)(GlVertexSubBufferData* pBuffer);
	Bool						(GlVertexBuffer::*DeleteMarkedBuffers)(const BaseDraw* pBaseDraw);
	Bool						(GlVertexBuffer::*SetSubBufferData)(const BaseDraw* pBaseDraw, GlVertexSubBufferData* pSubBuffer, Int lSize, const void* pData);
	Int32						(GlVertexBuffer::*GetSubBufferCount)() const;
	void*						(GlVertexBuffer::*MapBuffer)(const BaseDraw* pBaseDraw, GlVertexSubBufferData* pSubBuffer, GlVertexBufferAccessFlags flags);
	Bool						(GlVertexBuffer::*UnmapBuffer)(const BaseDraw* pBaseDraw, GlVertexSubBufferData* pSubBuffer);
	UInt64					(GlProgramFactory::*GetParameterFormats)() const;
	void*						(GlProgramFactory::*GetDescriptionData)(Int32 lObjIndex, Int32 lDataIndex, GlProgramFactoryAllocDescription fnAlloc, GlProgramFactoryFreeDescription fnFree, GlProgramFactoryReadDescription fnLoad, GlProgramFactoryWriteDescription fnWrite);
	Bool						(*WriteParameter)(GlWriteDescriptionData* pFile, GlProgramParameter param);
	Bool						(*ReadParameter)(GlReadDescriptionData* pFile, GlProgramParameter& param);
	Bool						(GlProgramFactory::*IsPrecompiled)() const;

	UInt64					(GlProgramFactory::*Init)(Int32 lSubdivideCount, Int32 lGeometryTypeIn, Int32 lGeometryTypeOut, Int32 lMaxOutVertices);
	void						(GlProgramFactory::*AddParameters)(UInt64 ulParameters, UInt64 ulFormat);
	void						(GlProgramFactory::*AddDepthCompareCondition)(GlProgramType t, const GlString &strPeelTexture);
	void						(GlFrameBuffer::*PrepareForRendering)(BaseDraw* pBaseDraw, Int32 lTexture);
	void						(GlFrameBuffer::*SetInterpolation)(BaseDraw* pBaseDraw, Int32 lInterpolate, Int32 lTexture, Int32 lFlags);
	Bool						(GlFrameBuffer::*DrawBuffer)(Int32 lTexture, Int32 lFlags, Bool bCopyAlpha, Int32 lColorConversion, C4DGLint nConversionTexture, Float32 rAlpha, const Vector32 &vColor, Float32 xs1, Float32 ys1, Float32 xs2, Float32 ys2, Float32 xd1, Float32 yd1, Float32 xd2, Float32 yd2);
	GlVertexSubBufferData*	(GlVertexBuffer::*GetSubBuffer)(Int32 n);
	Bool						(*DrawSubBuffer)(const BaseDraw* pBaseDraw, const GlVertexSubBufferData* pVertexSubBuffer, const GlVertexSubBufferData* pElementSubBuffer,
		Int32 lDrawinfoCount, const GlVertexBufferDrawSubbuffer* pDrawInfo,
		Int32 lVectorCount, const GlVertexBufferVectorInfo* const* ppVectorInfo, UInt32 flags,
		GlVertexBufferDrawElementCallback fnCallback, void* pCallbackData);
	Bool						(GlProgramFactory::*AddEmitVertex)();
	UInt32					(*GetLanguageFeatures)(BaseDraw* bd, Int32 lCompiler, Int32 lFlags);
};

struct C4D_Network
{
	// NetworkIpAddr
	Bool								(NetworkIpAddr::*Compare						)(const NetworkIpAddr &adr) const;
	Bool								(NetworkIpAddr::*IsValid1						)() const;
	String							(NetworkIpAddr::*GetString					)(Int32 port) const;
	int									(NetworkIpAddr::*GetNativeProtocol	)() const;
	Bool								(NetworkIpAddr::*Write							)(HyperFile *hf) const;
	Bool								(NetworkIpAddr::*Read								)(HyperFile *hf);
	PROTOCOL						(NetworkIpAddr::*GetProtocol				)() const;
	void								(NetworkIpAddr::*Flush							)();
	Bool								(NetworkIpAddr::*SetIPv4						)(UChar a, UChar b, UChar c, UChar d);
	Bool								(NetworkIpAddr::*SetIPv6						)(Int16 x1, Int16 x2, Int16 x3, Int16 x4, Int16 x5, Int16 x6, Int16 x7, Int16 x8);
	Bool								(NetworkIpAddr::*CopyTo							)(NetworkIpAddr &adr) const;
	Bool								(NetworkIpAddr::*GetIPv4						)(UChar& a, UChar& b, UChar& c, UChar& d) const;
	Bool								(NetworkIpAddr::*GetIPv6						)(Int16& x1, Int16& x2, Int16& x3, Int16& x4, Int16& x5, Int16& x6, Int16& x7, Int16& x8) const;
	Bool								(NetworkIpAddr::*IsPrivateAddress		)() const;

	// NetworkIpAddrPort
	Bool								(NetworkIpAddrPort::*WriteAP			)(HyperFile *hf) const;
	Bool								(NetworkIpAddrPort::*ReadAP				)(HyperFile *hf);
	Bool								(NetworkIpAddrPort::*IsValid2			)() const;
	String							(NetworkIpAddrPort::*GetStringAP	)(Bool getPort) const;
	void								(NetworkIpAddrPort::*SetPort			)(Int32 port);
	Int32								(NetworkIpAddrPort::*GetPort			)() const;

	// NetworkInterface
	String							(NetworkInterface::*GetInterfaceName)() const;
	Int									(NetworkInterface::*GetInterfaceIndex)() const;
	void								(NetworkInterface::*GetMacAddress)(maxon::BaseArray<UChar>& macAddress) const;
	String							(NetworkInterface::*GetDescription)() const;
	Int									(NetworkInterface::*GetCountAddress)() const;
	Bool								(NetworkInterface::*IsLoopback)() const;
	NetworkIpAddr				(NetworkInterface::*GetIpAddress)(Int i) const;
	NetworkIpAddr				(NetworkInterface::*GetBroadcastAddress)(Int i) const;
	NetworkIpAddr				(NetworkInterface::*GetSubnetMask)(Int i) const;
	NetworkInterface*		(NetworkInterface::*NetworkInterfaceGetClone)() const;
	Bool								(NetworkInterface::*NetworkInterfaceCopyTo)(NetworkInterface &networkInterface) const;
	Bool								(NetworkInterface::*Append)(const NetworkIpAddr& ipAddr, const NetworkIpAddr& broadcastAddress, const NetworkIpAddr& subnetMask);
	Bool								(NetworkInterface::*NetworkInterfaceWrite)(HyperFile* hf) const;
	Bool								(NetworkInterface::*NetworkInterfaceRead)(HyperFile* hf);
	BaseContainer				(NetworkInterface::*GetCustomData)() const;
	void								(NetworkInterface::*SetCustomData)(const BaseContainer& customData);
	NetworkInterface*		(*NetworkInterfaceAlloc)();
	void								(*NetworkInterfaceFree)(NetworkInterface*& p);

	// NetworkIpConnection
	Int64								(*NetworkIpConnectionGetTransferedBytes)(const NetworkIpConnection* self);
	NetworkIpAddrPort		(NetworkIpConnection::*GetRemoteAddr			)() const;
	NetworkIpAddrPort		(NetworkIpConnection::*GetHostAddr				)() const;

	NetworkIpConnection*				(*IpOpenListener						)(const NetworkIpAddrPort& adr, BaseThread* thread, Int timeout, Bool useNagleAlgorithm, Int* error);
	NetworkIpConnection*				(*IpOpenListenerString			)(const String& adr, BaseThread* thread, Int timeout, Bool useNagleAlgorithm, Int* error);
	NetworkIpConnection*				(*IpOpenOutgoing						)(const NetworkIpAddrPort& adr, BaseThread* thread, Int connectTimeout, Int sessionTimeout, Bool useNagleAlgorithm, Int* error);
	NetworkIpConnection*				(*IpOpenOutgoingString			)(const String& adr, BaseThread* thread, Int connectTimeout, Int sessionTimeout, Bool useNagleAlgorithm, Int* error);
	NetworkIpConnection*				(*IpWaitForIncoming					)(NetworkIpConnection* listener, BaseThread* connection, Int* error);
	void								(*IpCloseConnection					)(NetworkIpConnection* ipc);
	void								(*IpKillConnection					)(NetworkIpConnection* ipc);

	Int									(*IpBytesInInputBuffer			)(NetworkIpConnection* ipc);
	Int									(*IpReadBytes								)(NetworkIpConnection* ipc, void* buf, Int size);
	Int									(*IpSendBytes								)(NetworkIpConnection* ipc, const void* buf, Int size);

	ZeroConfBrowser*		(*StartZeroConfBrowser			)(const String& servicetype, ZeroConfBrowserCallback t_callback_found, ZeroConfBrowserResolvedCallback callback_txt, void *context, Bool thirdPartyInstance);
	void								(*StopZeroConfBrowser				)(ZeroConfBrowser* browser);
	ZeroConfService*		(*RegisterZeroConfService		)(String serviceName, const String& serviceType, Int lInterface, Int32 port, const String& domainName, Bool thirdPartyInstance);
	void								(*DeregisterZeroConfService	)(ZeroConfService* service);
	Bool								(*RemoveTXTRecord						)(ZeroConfService* service);
	Bool								(*SetTXTRecord							)(ZeroConfService* service, const String* keys, const String* values, Int cnt);

	String							(*GetHostname								)();
	Int									(*GetInterfaceIndex2				)(const String& interfaceName);
	NetworkInterface*		(*GetBestNetworkInterface		)(PROTOCOL protocol);
	Bool								(*GetAllNetworkInterfaces		)(maxon::BaseArray<NetworkInterface*>& networkInterfaces);
	Bool								(*GetIpAddress2							)(const String& address, NetworkIpAddr& a, Bool resolve, Bool forceResolve);
	Bool								(*GetIpAddress3							)(const String& address, NetworkIpAddrPort& a, Bool resolve, Bool forceResolve);
	RESOLVERESULT				(*ResolveHostname						)(const String& address, PROTOCOL protocol, maxon::BaseArray<NetworkIpAddr>& addrs, Bool firstMatch, Bool forceResolve);

	Bool								(*GetMacAddress2						)(maxon::BaseArray<UChar>& macAddress);
	Bool								(*WakeOnLan									)(const maxon::BaseArray<UChar>& macAddress, const NetworkIpAddr &broadcast);
	Bool								(*GetBonjourVersion					)(Int& versionNumber, Int& revisionNumber, Bool& isRunning);
	Bool								(*SplitAddress							)(String address, String *scheme, String *host, Int32 *port);
	String							(*GetHostname2							)(const NetworkIpAddr& ipAddr);

	void								(NetworkIpAddr::*SDKAlloc							)();
	void								(NetworkIpAddr::*SDKAlloc2						)(const NetworkIpAddr &adr);
	void								(NetworkIpAddr::*SDKFree							)();
	Bool								(NetworkIpAddr::*IsEmpty							)() const;
	void								(NetworkIpAddrPort::*SDKAllocPort			)();
	void								(NetworkIpAddrPort::*SDKAllocPort2		)(const NetworkIpAddr& adr, Int32 port);
	Bool								(NetworkIpAddrPort::*CompareAP				)(const NetworkIpAddrPort& adr) const;
	Bool								(NetworkIpAddrPort::*CopyTo2					)(NetworkIpAddrPort& dst) const;
	void								(NetworkIpAddrPort::*Flush2						)();
};

struct OperatingSystem
{
	Int32 version;

	C4D_General				*Ge;
	C4D_Shader				*Sh;
	C4D_HyperFile			*Hf;
	C4D_BaseContainer *Bc;
	C4D_String				*St;
	C4D_Bitmap				*Bm;
	C4D_MovieSaver		*Ms;
	C4D_BaseChannel		*Ba;
	C4D_Filename			*Fn;
	C4D_File					*Fl;
	C4D_BrowseFiles		*Bf;
	C4D_Dialog				*Cd;
	C4D_UserArea			*Cu;
	C4D_Parser				*Pr;
	C4D_Resource			*Lr;
	C4D_BaseList			*Bl;
	C4D_Tag						*Tg;
	C4D_Object				*Bo;
	C4D_Document			*Bd;
	C4D_Thread				*Bt;
	C4D_Material			*Mt;
	C4D_Texture				*Tx;
	C4D_BaseSelect		*Bs;
	C4D_BaseSound			*Bu;
	C4D_BaseDraw			*Br;
	C4D_BaseView			*Bv;
	C4D_Neighbor			*Nb;
	C4D_Pool					*Pl;
	C4D_BitmapFilter	*Fi;
	C4D_Painter				*Pa;
	C4D_Link					*Ln;
	C4D_GraphView			*Gv;
	C4D_GeData				*Gd;
	C4D_Atom					*At;
	C4D_Coffee				*Co;
	C4D_CAnimation		*CA;
	C4D_CrashHandler	CrashHandler;
	C4D_CreateOpenGLContext	CreateOpenGLContext;
	C4D_DeleteOpenGLContext	DeleteOpenGLContext;
	C4D_GLSL					*GL;
	C4D_Network				*Ne;
	C4D_Uuid					*Gu;
};

#ifndef __API_INTERN__
	#define C4DOS (*t_C4DOS)
	Int32 InitOS(void *p);
#endif

extern OperatingSystem C4DOS;

/// @endcond

#endif // OPERATINGSYSTEM_H__
