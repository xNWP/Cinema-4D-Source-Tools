/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef LIB_BIRENDER_H__
#define LIB_BIRENDER_H__

#include "c4d_library.h"

#ifdef __API_INTERN__
#include "pluginobject.h"
#include "plugintag.h"
#include "pluginvideopost.h"
#else
#include "c4d_baseobject.h"
#include "c4d_basetag.h"
#include "c4d_videopost.h"
#endif

#include "c4d_raytrace.h"
#include "c4d_misc.h"

#define LIBRARY_BIRENDER	1029004

const Int32 MSG_BIRENDER_ADDMPBUFFER = 1031173;

class BiRenderObject;
class BiRenderVideoPost;

namespace birender
{
const UInt32 segmentMask = 0x7FFFFFFF;
const UInt32 segmentClosed = 0x80000000;

enum FLAG_STATE
{
	FLAG_STATE_0 = 0,
	FLAG_STATE_ADD = 1,
	FLAG_STATE_DEL = 2,
	FLAG_STATE_SET = 3,
} ENUM_END_LIST(FLAG_STATE);

enum SHADING_CALLBACK_FLAG
{
	SHADING_CALLBACK_FLAG_0 = 0,
	SHADING_CALLBACK_FLAG_INIT = (1 << 0),
	SHADING_CALLBACK_FLAG_EXIT = (1 << 1),
	SHADING_CALLBACK_FLAG_SHADER = (1 << 2),
	SHADING_CALLBACK_FLAG_THICKNESS = (1 << 3),
	SHADING_CALLBACK_FLAG_SHADOWS = (1 << 4)
} ENUM_END_FLAGS(SHADING_CALLBACK_FLAG);

enum RENDER_CALLBACK_FLAG
{
	RENDER_CALLBACK_FLAG_0 = 0,
	RENDER_CALLBACK_FLAG_DRAW = (1 << 0),
	RENDER_CALLBACK_FLAG_FIRST = (1 << 1),
	RENDER_CALLBACK_FLAG_CALCVOL = (1 << 2),
	RENDER_CALLBACK_FLAG_CALCVOL_EXIT = (1 << 3)
} ENUM_END_FLAGS(RENDER_CALLBACK_FLAG);

enum RENDER_CALLBACK_RETURN_FLAG
{
	RENDER_CALLBACK_RETURN_FLAG_0 = 0,
	RENDER_CALLBACK_RETURN_FLAG_EXIT = (1 << 0),
	RENDER_CALLBACK_RETURN_FLAG_SKIP_Z = (1 << 1),
	RENDER_CALLBACK_RETURN_FLAG_SKIP_SET = (1 << 2),
	RENDER_CALLBACK_RETURN_FLAG_SAMPLED = (1 << 3),
} ENUM_END_FLAGS(RENDER_CALLBACK_RETURN_FLAG);

enum OBJECT_FLAG
{
	OBJECT_FLAG_0 = 0,
	OBJECT_FLAG_NORMALS = (1 << 0),
	OBJECT_FLAG_WORLD_THICKNESS = (1 << 1),
	OBJECT_FLAG_CUSTOM_THICKNESS = (1 << 2),
	OBJECT_FLAG_CUSTOM_WORLD_THICKNESS = (1 << 3),
	OBJECT_FLAG_NO_SHADOWS = (1 << 4),
	OBJECT_FLAG_NO_REFRACTION = (1 << 5),
	OBJECT_FLAG_NO_REFLECTION = (1 << 6),
	OBJECT_FLAG_NO_PRECULL = (1 << 7),
	OBJECT_FLAG_REQUEST_SCREEN = (1 << 8),
	OBJECT_FLAG_REQUEST_WORLD = (1 << 9),
	OBJECT_FLAG_REQUEST_CAMERA = (1 << 10),
	OBJECT_FLAG_REQUEST_TANGENTS = (1 << 11),
	OBJECT_FLAG_VERTEX_COL_SAMPLING = (1 << 12),
	OBJECT_FLAG_SAMPLING_AA = (1 << 13),
	OBJECT_FLAG_RAYTRACED = (1 << 14),
	OBJECT_FLAG_MP_NO_DEPTH = (1 << 15)
} ENUM_END_FLAGS(OBJECT_FLAG);

enum COORD_SPACE
{
	COORD_SPACE_0 = 0,
	COORD_SPACE_LOCAL = 1,
	COORD_SPACE_WORLD,
	COORD_SPACE_CAMERA,
	COORD_SPACE_SCREEN,
	COORD_SPACE_CUSTOM
} ENUM_END_LIST(COORD_SPACE);

enum JOINT_TYPE
{
	JOINT_TYPE_0 = 0,
	JOINT_TYPE_BEVEL = 1,
	JOINT_TYPE_ROUND,
	JOINT_TYPE_MITER
} ENUM_END_LIST(JOINT_TYPE);

enum INTERPOLATION_TYPE
{
	INTERPOLATION_TYPE_0 = 0,
	INTERPOLATION_TYPE_LINEAR = 1
} ENUM_END_LIST(INTERPOLATION_TYPE);

enum CAP_TYPE
{
	CAP_TYPE_0 = 0,
	CAP_TYPE_ROUND = 1,
	CAP_TYPE_FLAT,
	CAP_TYPE_SQUARE,
	CAP_TYPE_LINEAR,
	CAP_TYPE_ARROW,
	CAP_TYPE_CUSTOM
} ENUM_END_LIST(CAP_TYPE);

enum RENDER_TYPE
{
	RENDER_TYPE_0 = 0,
	RENDER_TYPE_RASTER = 1,
	RENDER_TYPE_CONE,
	RENDER_TYPE_RAY,
	RENDER_TYPE_RASTER_TILES,
	RENDER_TYPE_RASTER_NO_MP,
} ENUM_END_LIST(RENDER_TYPE);

enum SHADOW_TYPE
{
	SHADOW_TYPE_0 = 0,
	SHADOW_TYPE_AUTO = 1,
	SHADOW_TYPE_SOFT,
	SHADOW_TYPE_HARD,
} ENUM_END_LIST(SHADOW_TYPE);

enum RENDER_FLAG
{
	RENDER_FLAG_0 = 0,
	RENDER_FLAG_RENDER_CALLBACK = (1 << 0),
	RENDER_FLAG_RENDER_ALPHA_ONLY = (1 << 1),
	RENDER_FLAG_RENDER_NO_TRACER = (1 << 2),
	RENDER_FLAG_RENDER_BLENDING = (1 << 3),
	RENDER_FLAG_RENDER_SHADOWS = (1 << 4),
	RENDER_FLAG_RENDER_ERROR = (1 << 5),
	RENDER_FLAG_RENDER_UNINIT = (1 << 6),
	RENDER_FLAG_RENDER_REFRACTION = (1 << 7),
	RENDER_FLAG_RENDER_REFLECTION = (1 << 8),
	RENDER_FLAG_RENDER_BUCKETS = (1 << 9),
	RENDER_FLAG_RENDER_READY = (1 << 10)
} ENUM_END_FLAGS(RENDER_FLAG);

enum BLEND_MODE
{
	BLEND_MODE_0 = 0,
	BLEND_MODE_AVERAGE = 1,
	BLEND_MODE_NORMAL,
	BLEND_MODE_MULTIPLY,
	BLEND_MODE_SCREEN,
	BLEND_MODE_DARKEN,
	BLEND_MODE_LIGHT,
	BLEND_MODE_DIFFERENCE,
	BLEND_MODE_NEGATIVE,
	BLEND_MODE_EXCLUSION,
	BLEND_MODE_OVERLAY,
	BLEND_MODE_HARDLIGHT,
	BLEND_MODE_SOFTLIGHT,
	BLEND_MODE_DODGE,
	BLEND_MODE_BURN,
	BLEND_MODE_REFLECT,
	BLEND_MODE_GLOW,
	BLEND_MODE_FREEZE,
	BLEND_MODE_HEAT,
	BLEND_MODE_ADD,
	BLEND_MODE_SUB,
	BLEND_MODE_STAMP,
	BLEND_MODE_XOR,
	BLEND_MODE_HUE,
	BLEND_MODE_SATURATION,
	BLEND_MODE_LUMINANCE,
	BLEND_MODE_RED,
	BLEND_MODE_GREEN,
	BLEND_MODE_BLUE,
	BLEND_MODE_OVERWRITE,
	BLEND_MODE_LEVR,
} ENUM_END_LIST(BLEND_MODE);

enum RENDERDATA_FLAG
{
	RENDERDATA_FLAG_0 = 0,
	RENDERDATA_FLAG_SCREEN = (1 << 0),
	RENDERDATA_FLAG_WORLD = (1 << 1),
	RENDERDATA_FLAG_CAMERA = (1 << 2),
	RENDERDATA_FLAG_LINE = (1 << 3),
	RENDERDATA_FLAG_TRACING = (1 << 4),
	RENDERDATA_FLAG_REDUCED = (1 << 5),
	RENDERDATA_FLAG_TANGENT = (1 << 6),
} ENUM_END_FLAGS(RENDERDATA_FLAG);

enum SETCURVE_FLAGS
{
	SETCURVE_FLAGS_0 = 0,
	SETCURVE_FLAGS_CLONE = (1 << 0),
	SETCURVE_FLAGS_OWN = (1 << 1)
} ENUM_END_FLAGS(SETCURVE_FLAGS);

enum MPBUFFER_FLAGS
{
	MPBUFFER_FLAGS_0 = 0,
	MPBUFFER_FLAGS_MUL = (1 << 0),
	MPBUFFER_FLAGS_DEPTH = (1 << 1),
	MPBUFFER_FLAGS_ALPHA = (1 << 2),
	MPBUFFER_FLAGS_INVERT = (1 << 3),
} ENUM_END_FLAGS(MPBUFFER_FLAGS);

class JointData
{
public:

	JointData()
	{
		m_Theta = 0.0;
		m_CosTheta = 0.0;
		m_BevelHeight = 0.0;
		m_MiterHeight = 0.0;
		_isJoint = false;
		_radius = 0.0;
		_worldRadius = 0.0;
	}

	Float m_Theta;
	Float m_CosTheta;
	Float32 m_BevelHeight, m_MiterHeight;

	Vector32 m_Normal, m_Axis;
	Vector32 m_LineNormal;

	Bool _isJoint;
	Float32 _radius;
	Float32 _worldRadius;
};

class LineData
{
public:

	LineData()
	{
		_screenLength = 0.0;
	}

	Vector32 GetNormal() const
	{
		return Vector32(_screenDirection.y, -_screenDirection.x , 0.0);
	}

	Vector32 _screenVertices[2];

	Vector32 _screenLine;
	Vector32 _screenDirection;

	Float32 _screenLength;

	Vector _cameraVertices[2];
	Vector32 _cameraNormal;
};

class Segment
{
public:

	Segment()
	{
		_count = 0;
	}

	explicit Segment(Int32 count, Bool closed = false)
	{
		Set(count, closed);
	}

	void Set(Int32 count, Bool closed = false)
	{
		_count = count;
		if (closed)
			_count |= segmentClosed;
	}
	UInt32 Get() { return _count; }

	Int32 GetCount() const { return _count & segmentMask; }
	Bool IsClosed() const  { return (_count & segmentClosed) != 0; }

private:

	UInt32 _count;
};

class LineRenderData
{
public:

	LineRenderData()
	{
		_object = nullptr;
		_lineRadius[0] = 0.0;
		_lineRadius[1] = 0.0;
		_thickness = 0.0;
		_worldThickness = 0.0;
		_curveIndex = NOTOK;
		_lineIndex = NOTOK;
		_vertexIndex = NOTOK;
		_baseIndex = NOTOK;
		_delta = 0.0;
		_curveDelta = 0.0;
		_lineCameraLen = 0.0;
		_deltaErr[0] = 0.0;
		_deltaErr[1] = 0.0;
		_prevLineCameraLen = 0.0;
		_nextLineCameraLen = 0.0;
		_jointData[0] = nullptr;
		_jointData[1] = nullptr;
		_lineData = nullptr;
		_toLineDist = 0.0;
		_lineID = (UInt32)-1;
		_flags = RENDERDATA_FLAG_0;
		_vertices = nullptr;
		_screenVertices = nullptr;
		_cameraVertices = nullptr;
		_tangents = nullptr;
	}

	RENDERDATA_FLAG _flags;
	BiRenderObject *_object;

	Float32 _delta;					// delta position along the line segment
	Float32 _curveDelta;			// delta position along the entire curve (0-1), based on vertex position only

	Segment _segmentCount;

	Int32 _curveIndex;
	Int32 _lineIndex;			// line vertex index within the current curve
	Int32 _vertexIndex;		// vertex index within the main vertices (all curves)
	Int32 _baseIndex;			// index of the curves first vertex

	UInt32 _lineID;

	// world space (only valid if _flags & RENDERDATA_FLAG_WORLD)

	Vector _rayPosition;
	Vector _rayDirection;

	Vector _worldPosition;				// ray to curve intersection point in world space
	Vector _worldNormal;					// ray to curve intersection normal in world space
	Vector _worldLinePosition;		// _linePoint in world coordinates
	Vector _worldRenderPosition;	// render position in world coordinates
	Float32 _worldThickness;				// radius of line at the rendering (intersection) point

	// camera space (only valid if _flags & RENDERDATA_FLAG_CAMERA)

	Vector	_vertexCamera[4];		// line vertices in camera space, [0]-[1] is the current line, [2] previous vertex (only if a joint), [3] next vertex (only if a joint)
	Vector _normalCamera[2];		// joint normal in camera space

	Vector _jointAxisCamera[2]; // joint Z axis

	Float		_lineRadius[2];			// line radius
	Float		_lineCameraLen;			// line length

	Vector	_lineCameraDn;			// direction vector for the line
	Vector	_lineCameraNormal;	// line normal

	Float		_deltaErr[2];				// pixel error radius

	Vector _prevLineCameraDn;		// previous lines direction
	Float _prevLineCameraLen;		// previous lines length

	Vector _nextLineCameraDn;		// next lines direction
	Float _nextLineCameraLen;		// next lines length

	// screen space (only valid if _flags & RENDERDATA_FLAG_SCREEN)

	Vector32 _renderPosition;		// rendering pixel coordinate
	Vector32 _linePoint;				// position on the line segment

	Float32 _thickness;
	Float32 _toLineDist;				// distance to the rendering line

	JointData* _jointData[2];	// can be nullptr, always check
	LineData* _lineData;			// can be nullptr, always check

	// line space (only valid if _flags & RENDERDATA_FLAG_LINE)

	Matrix	_lineMg, _lineMi;		// camera to/from line space

	Vector _rayLinePosition;		// ray within coord space of the line (_lineMg)
	Vector _rayLineDirection;		// ray within coord space of the line (_lineMg)

	//  curve data

	const Vector *_vertices;
	const Vector32 *_screenVertices;
	const Vector *_cameraVertices;
	const Vector *_tangents;	// only valid RENDERDATA_FLAG_TANGENT, may also be nullptr
};

class CallbackData
{
public:
	virtual void Flush() = 0;
};

class RenderCallbackLineData
{
public:
	Vector _p;

	Int32 _baseIndex;
	Int32 _vertexIndex;
	Int32 _lineIndex;
	Int32 _curveIndex;

	Segment _segmentCount;

	Float32 _pixelAlpha;
	Vector32 _pixelCol;
	Float32 _pixelZ;

	Vector32* _col;
	Float32* _alpha;
};

typedef void ShadingCallback(BiRenderObject *biObject, BiRenderVideoPost *bivp, VolumeData *volData, LineRenderData* lineData, Int32 cpuIndex, Vector32* col, Float32* alpha, Vector32 *mpData, SHADING_CALLBACK_FLAG flags, CallbackData* customData);
typedef RENDER_CALLBACK_RETURN_FLAG RenderCallback(BiRenderObject *biObject, BiRenderVideoPost *bivp, VolumeData *volData, RenderCallbackLineData *lineData, Int32 cpuIndex, RENDER_CALLBACK_FLAG flags, CallbackData* customData);

} // BIRENDER_END

class BiRenderObject
{
private:

	BiRenderObject();
	~BiRenderObject();

public:

	Int32 GetVertexCount();
	Vector *GetVertices();
	Int32 GetCurveCount();
	Bool SetCurveCount(Int32 curvecount, Int32 segmentcount, const birender::Segment *segments, const Vector *vertices, const Float32 *thickness, birender::SETCURVE_FLAGS flags);
	Int32 GetSegmentCount();
	birender::Segment *GetSegments();
	Float32 *GetThickness();

	birender::INTERPOLATION_TYPE GetInterpolation();
	void SetInterpolation(birender::INTERPOLATION_TYPE itype);

	birender::COORD_SPACE GetCoordSpace();
	Bool SetCoordSpace(birender::COORD_SPACE coord, BiRenderVideoPost *bipost);

	birender::JOINT_TYPE GetJointType();
	void SetJointType(birender::JOINT_TYPE jtype);
	void SetMiterLimit(Float theta);
	Float GetMiterLimit();

	birender::CAP_TYPE GetStartCapType();
	void SetStartCapType(birender::CAP_TYPE ctype);
	void SetStartCapSize(Float capw, Float caph);
	Vector GetStartCapSize();
	void SetStartCapCustom(BaseShader *shader);

	birender::CAP_TYPE GetEndCapType();
	void SetEndCapType(birender::CAP_TYPE ctype);
	void SetEndCapSize(Float capw, Float caph);
	Vector GetEndCapSize();
	void SetEndCapCustom(BaseShader *shader);

	void SetShadingCallback(birender::ShadingCallback* callback, birender::CallbackData* calldata);
	void SetRenderCallback(birender::RenderCallback* callback, birender::CallbackData* calldata);

	birender::OBJECT_FLAG GetFlags();
	void SetFlags(birender::OBJECT_FLAG flags, birender::FLAG_STATE state);

	birender::BLEND_MODE GetBlend();
	birender::BLEND_MODE GetSelfBlend();
	void SetBlend(birender::BLEND_MODE mode);
	void SetSelfBlend(birender::BLEND_MODE mode);

	void SetRayObject(const RayObject *rayObject);
	const RayObject *GetRayObject();

	void SetObject(BaseList2D *object);
	BaseList2D *GetObject(BaseDocument *doc);

	void Sample(birender::LineRenderData& lineData, VolumeData* voldata, BiRenderVideoPost* bipost, Vector32* pxCol, Float32* pxAlpha, Int32 cpuIndex);

	void SetOwner(Int32 id);
	Int32 GetOwner();
};

class BiRenderVideoPost : public BaseVideoPost
{
#ifndef __API_INTERN__
private:

	BiRenderVideoPost();
	~BiRenderVideoPost();

public:

	static BiRenderVideoPost *Alloc() { return (BiRenderVideoPost*)BaseVideoPost::Alloc(VPbirender); }
	static void Free(BiRenderVideoPost *&pPost) { BaseVideoPost *vp = pPost; BaseVideoPost::Free(vp); pPost = nullptr; }

#else
public:
#endif

	BiRenderObject *Append();

	Bool RemoveObject(Int32 index);
	void Flush();

	Int32 GetCount();
	BiRenderObject *GetObject(Int32 index);
	Float GetAAWidth();
	void SetAAWidth(Float aaw);
	birender::RENDER_TYPE GetRenderer();
	void SetRenderer(birender::RENDER_TYPE type);
	void SetShadow(birender::SHADOW_TYPE type, Float transDelta, Float distDelta, Int32 resolution, Int32 samples, Float aa);

	birender::RENDER_FLAG GetFlags();
	void SetFlags(birender::RENDER_FLAG flags, birender::FLAG_STATE state);

	Vector CalcShadow(const RayLight* light, VolumeData *volData, Int32 cpuIndex, const Vector &p, const Vector &n, const Vector &rayv, Float delta);

	Int32 AddBuffer(const String &name, birender::MPBUFFER_FLAGS flags, Int32 vpID);

	static BiRenderVideoPost *GetVideoPost(BaseDocument *doc);
	static BiRenderVideoPost *GetVideoPost(VolumeData *vd);

	void SetShadowState(Int32 cpuIndex, bool enabled);
};

struct BiRenderLib : public C4DLibrary
{
	BiRenderObject *(*bivpAppend)(BiRenderVideoPost *bivp);
	Bool (*bivpRemove)(BiRenderVideoPost *bivp, Int32 index);
	void (*bivpFlush)(BiRenderVideoPost *bivp);
	Int32 (*bivpGetCount)(BiRenderVideoPost *bivp);
	BiRenderObject *(*bivpGetObject)(BiRenderVideoPost *bivp, Int32 index);
	Float (*bivpGetAAWidth)(BiRenderVideoPost *bivp);
	void (*bivpSetAAWidth)(BiRenderVideoPost *bivp, Float aaw);
	birender::RENDER_TYPE (*bivpGetRenderer)(BiRenderVideoPost *bivp);
	void (*bivpSetRenderer)(BiRenderVideoPost *bivp, birender::RENDER_TYPE type);
	birender::RENDER_FLAG (*bivpGetFlags)(BiRenderVideoPost *bivp);
	void (*bivpSetFlags)(BiRenderVideoPost *bivp, birender::RENDER_FLAG flags, birender::FLAG_STATE state);
	Vector (*bivpCalcShadow)(BiRenderVideoPost *bivp, const RayLight* light, VolumeData *volData, Int32 cpuIndex, const Vector &p, const Vector &n, const Vector &rayv, Float delta);
	void (*bivpSetShadow)(BiRenderVideoPost *bivp, birender::SHADOW_TYPE type, Float transDelta, Float distDelta, Int32 resolution, Int32 samples, Float aa);
	Int32 (*bivpAddBuffer)(BiRenderVideoPost *bivp, const String &name, birender::MPBUFFER_FLAGS, Int32 vpID);

	Int32 (*biopGetVertexCount)(BiRenderObject *biobject);
	Vector *(*biopGetVertices)(BiRenderObject *biobject);
	Int32 (*biopGetCurveCount)(BiRenderObject *biobject);
	Bool (*biopSetCurveCount)(BiRenderObject *biobject, Int32 curvecount, Int32 segmentcount, const birender::Segment *segments, const Vector *vertices, const Float32 *thickness, birender::SETCURVE_FLAGS flags);
	Int32 (*biopGetSegmentCount)(BiRenderObject *biobject);
	birender::Segment *(*biopGetSegments)(BiRenderObject *biobject);
	birender::INTERPOLATION_TYPE (*biopGetInterpolation)(BiRenderObject *biobject);
	void (*biopSetInterpolation)(BiRenderObject *biobject, birender::INTERPOLATION_TYPE itype);
	birender::COORD_SPACE (*biopGetCoordSpace)(BiRenderObject *biobject);
	Bool (*biopSetCoordSpace)(BiRenderObject *biobject, birender::COORD_SPACE coord, BiRenderVideoPost *bipost);
	birender::JOINT_TYPE (*biopGetJointType)(BiRenderObject *biobject);
	void (*biopSetJointType)(BiRenderObject *biobject, birender::JOINT_TYPE jtype);
	birender::CAP_TYPE (*biopGetStartCapType)(BiRenderObject *biobject);
	void (*biopSetStartCapType)(BiRenderObject *biobject, birender::CAP_TYPE ctype);
	Float32 *(*biopGetThickness)(BiRenderObject *biobject);
	void (*biopSetMiterLimit)(BiRenderObject *biobject, Float theta);
	void (*biopSetStartCapSize)(BiRenderObject *biobject, Float capw, Float caph);
	Vector (*biopGetStartCapSize)(BiRenderObject *biobject);
	void (*biopSetShadingCallback)(BiRenderObject *biobject, birender::ShadingCallback* callback, birender::CallbackData* calldata);
	void (*biopSetRenderCallback)(BiRenderObject *biobject, birender::RenderCallback* callback, birender::CallbackData* calldata);
	birender::OBJECT_FLAG (*biopGetFlags)(BiRenderObject *biobject);
	void (*biopSetFlags)(BiRenderObject *biobject, birender::OBJECT_FLAG flags, birender::FLAG_STATE state);
	birender::BLEND_MODE (*biopGetBlend)(BiRenderObject *biobject);
	birender::BLEND_MODE (*biopGetSelfBlend)(BiRenderObject *biobject);
	void (*biopSetBlend)(BiRenderObject *biobject, birender::BLEND_MODE mode);
	void (*biopSetSelfBlend)(BiRenderObject *biobject, birender::BLEND_MODE mode);
	void (*biopSetRayObject)(BiRenderObject *biobject, const RayObject *rayObject);
	const RayObject* (*biopGetRayObject)(BiRenderObject *biobject);
	void (*biopSample)(BiRenderObject *biobject, birender::LineRenderData& lineData, VolumeData* voldata, BiRenderVideoPost* bipost, Vector32* pxCol, Float32* pxAlpha, Int32 cpuIndex);
	void (*biopSetObject)(BiRenderObject *biobject, BaseList2D *object);
	BaseList2D *(*biopGetObject)(BiRenderObject *biobject, BaseDocument *doc);
	birender::CAP_TYPE (*biopGetEndCapType)(BiRenderObject *biobject);
	void (*biopSetEndCapType)(BiRenderObject *biobject, birender::CAP_TYPE ctype);
	void (*biopSetEndCapSize)(BiRenderObject *biobject, Float capw, Float caph);
	Vector (*biopGetEndCapSize)(BiRenderObject *biobject);
	Float (*biopGetMiterLimit)(BiRenderObject *biobject);
	void (*biopSetStartCapCustom)(BiRenderObject *biobject, BaseShader *shader);
	void (*biopSetEndCapCustom)(BiRenderObject *biobject, BaseShader *shader);
	void (*biopSetOwner)(BiRenderObject *biobject, Int32 id);
	Int32 (*biopGetOwner)(BiRenderObject *biobject);

	void (*bivpSetShadowState)(BiRenderVideoPost *bivp, Int32 cpuIndex, bool enabled);
};

#endif // LIB_BIRENDER_H__
