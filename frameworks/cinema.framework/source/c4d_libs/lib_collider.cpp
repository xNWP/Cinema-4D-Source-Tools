#include "lib_collider.h"


#define LIBID			LIB_COLLIDERCACHE
#define LIB				ColliderCacheLib

static LIB *library_cache = nullptr;


static LIB *CheckLibCache(Int32 offset)
{
	return (LIB*)CheckLib(LIBID, offset, (C4DLibrary**)&library_cache);
}

GeColliderCache::GeColliderCache()
{
}

GeColliderCache* GeColliderCache::Alloc()
{
	LIB *lib = CheckLibCache(LIBOFFSET(LIB, Alloc)); if (!lib || !lib->Alloc) return nullptr;
	return lib->Alloc();
}

void GeColliderCache::Free(GeColliderCache *&data)
{
	LIB *lib = CheckLibCache(LIBOFFSET(LIB, Free)); if (!lib || !lib->Free) return;
	lib->Free(data);
}

Bool GeColliderCache::CopyTo(GeColliderCache *dest)
{
	LIB *lib = CheckLibCache(LIBOFFSET(LIB, CopyTo)); if (!lib || !lib->CopyTo) return false;
	return (this->*lib->CopyTo)(dest);
}

Int32 GeColliderCache::BeginInput(Int32 cnt_tris)
{
	LIB *lib = CheckLibCache(LIBOFFSET(LIB, BeginInput)); if (!lib || !lib->BeginInput) return false;
	return (this->*lib->BeginInput)(cnt_tris);
}

Int32 GeColliderCache::AddTriangle(const Vector& p1, const Vector& p2, const Vector& p3, Int32 id)
{
	LIB *lib = CheckLibCache(LIBOFFSET(LIB, AddTriangle)); if (!lib || !lib->AddTriangle) return false;
	return (this->*lib->AddTriangle)(p1, p2, p3, id);
}

Int32 GeColliderCache::EndInput()
{
	LIB *lib = CheckLibCache(LIBOFFSET(LIB, EndInput)); if (!lib || !lib->EndInput) return false;
	return (this->*lib->EndInput)();
}



//////////////////////////////////////////////////////


#undef LIBID
#undef LIB

#define LIBID			LIB_COLLIDERENGINE
#define LIB				ColliderEngineLib

static LIB *library_engine = nullptr;


static LIB *CheckLibEngine(Int32 offset)
{
	return (LIB*)CheckLib(LIBID, offset, (C4DLibrary**)&library_engine);
}

GeColliderEngine::GeColliderEngine()
{
}

GeColliderEngine* GeColliderEngine::Alloc()
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, Alloc)); if (!lib || !lib->Alloc) return nullptr;
	return lib->Alloc();
}

void GeColliderEngine::Free(GeColliderEngine *&data)
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, Free)); if (!lib || !lib->Free) return;
	lib->Free(data);
}

Int32 GeColliderEngine::DoCollide(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Int32 flag)
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, DoCollide)); if (!lib || !lib->DoCollide) return false;
	return (this->*lib->DoCollide)(M1, o1, M2, o2, flag);
}

Int32 GeColliderEngine::DoPolyPairs(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Float tolerance)
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, DoPolyPairs)); if (!lib || !lib->DoPolyPairs) return false;
	return (this->*lib->DoPolyPairs)(M1, o1, M2, o2, tolerance);
}

Int32 GeColliderEngine::DoTolerance(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Float tolerance)
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, DoTolerance)); if (!lib || !lib->DoTolerance) return false;
	return (this->*lib->DoTolerance)(M1, o1, M2, o2, tolerance);
}

Int32 GeColliderEngine::DoDistance(const Matrix& M1, GeColliderCache *o1, const Matrix& M2, GeColliderCache *o2, Float rel_err, Float abs_err)
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, DoDistance)); if (!lib || !lib->DoDistance) return false;
	return (this->*lib->DoDistance)(M1, o1, M2, o2, rel_err, abs_err);
}

Int32 GeColliderEngine::DoRayCollide(GeColliderCache *o1, const Vector &ray_p, const Vector &ray_dir, Float ray_length)
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, DoRayCollide)); if (!lib || !lib->DoRayCollide) return false;
	return (this->*lib->DoRayCollide)(o1, ray_p, ray_dir, ray_length);
}

void GeColliderEngine::FreePairsList()
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, FreePairsList)); if (!lib || !lib->FreePairsList) return;
	(this->*lib->FreePairsList)();
}

Int32 GeColliderEngine::GetNumPairs()
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, GetNumPairs)); if (!lib || !lib->GetNumPairs) return false;
	return (this->*lib->GetNumPairs)();
}

Int32 GeColliderEngine::GetId1(Int32 k)
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, GetId1)); if (!lib || !lib->GetId1) return false;
	return (this->*lib->GetId1)(k);
}

Int32 GeColliderEngine::GetId2(Int32 k)
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, GetId2)); if (!lib || !lib->GetId2) return false;
	return (this->*lib->GetId2)(k);
}

Bool GeColliderEngine::IsCloser()
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, IsCloser)); if (!lib || !lib->IsCloser) return false;
	return (this->*lib->IsCloser)();
}

Float GeColliderEngine::GetDistance()
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, GetDistance)); if (!lib || !lib->GetDistance) return false;
	return (this->*lib->GetDistance)();
}

static Vector dummy;

const Vector& GeColliderEngine::GetP1()
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, GetP1)); if (!lib || !lib->GetP1) return dummy;
	return (this->*lib->GetP1)();
}

const Vector& GeColliderEngine::GetP2()
{
	LIB *lib = CheckLibEngine(LIBOFFSET(LIB, GetP2)); if (!lib || !lib->GetP2) return dummy;
	return (this->*lib->GetP2)();
}


//////////////////////////////////////////////////////


#undef LIBID
#undef LIB

#define LIBID			LIB_RAYCOLLIDER
#define LIB				RayColliderLib

static LIB *library_ray = nullptr;


static LIB *CheckLibRay(Int32 offset)
{
	return (LIB*)CheckLib(LIBID, offset, (C4DLibrary**)&library_ray);
}

GeRayCollider::GeRayCollider()
{
}

GeRayCollider* GeRayCollider::Alloc()
{
	LIB *lib = CheckLibRay(LIBOFFSET(LIB, Alloc)); if (!lib || !lib->Alloc) return nullptr;
	return lib->Alloc();
}

void GeRayCollider::Free(GeRayCollider *&data)
{
	LIB *lib = CheckLibRay(LIBOFFSET(LIB, Free)); if (!lib || !lib->Free) return;
	lib->Free(data);
}
Bool GeRayCollider::Init(BaseObject *object, Bool force)
{
	LIB *lib = CheckLibRay(LIBOFFSET(LIB, Init)); if (!lib || !lib->Init) return false;
	return (this->*lib->Init)(object, force);
}

Bool GeRayCollider::Intersect(const Vector &ray_p, const Vector &ray_dir, Float ray_length, Bool only_test)
{
	LIB *lib = CheckLibRay(LIBOFFSET(LIB, Intersect)); if (!lib || !lib->Intersect) return false;
	return (this->*lib->Intersect)(ray_p, ray_dir, ray_length, only_test);
}

Int32 GeRayCollider::GetIntersectionCount()
{
	LIB *lib = CheckLibRay(LIBOFFSET(LIB, GetIntersectionCount)); if (!lib || !lib->GetIntersectionCount) return 0;
	return (this->*lib->GetIntersectionCount)();
}

Bool GeRayCollider::GetIntersection(Int32 n, GeRayColResult *result)
{
	LIB *lib = CheckLibRay(LIBOFFSET(LIB, GetIntersection)); if (!lib || !lib->GetIntersection) return false;
	return (this->*lib->GetIntersection)(n, result);
}

Bool GeRayCollider::GetNearestIntersection(GeRayColResult *result)
{
	LIB *lib = CheckLibRay(LIBOFFSET(LIB, GetNearestIntersection)); if (!lib || !lib->GetNearestIntersection) return false;
	return (this->*lib->GetNearestIntersection)(result);
}
