#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(C4DMISC_DEFAULTALLOCATOR_H__)

#define C4DMISC_DEFAULTALLOCATOR_H__

#include "../general.h"
#include <stdlib.h>

namespace maxon
{

// Can't include c4d_memory.h because this would create a circular dependency to operatingsystem.h, therefore use the following helpers
void* _DefaultAllocNC(Int size, Int32 line, const Char* file);
void* _DefaultAlloc(Int size, Int32 line, const Char* file);
void*	_DefaultReallocNC(void* data, Int size, Int32 line, const Char* file);
void _DefaultFree(void** data_ptr);

//----------------------------------------------------------------------------------------
/// Default implementation of an allocator.
/// An allocator is used by arrays, lists and other data structurs to allocate and release
/// memory. By default this implementation of an allocator is used.
///
/// There might be rare cases when you need a special memory alignment, a different resize
/// strategy or have to use a special memory area (stack, shared memory, ...). This can be
/// done by writing a custom allocator and specifying it as parameter upon array construction.
/// A custom allocator must implement the ComputeArraySize(), Alloc(), AllocClear(), Realloc()
/// and Free() methods, but it doesn't (and usually shouldn't) inherit from DefaultAllocator.
/// The allocator methods don't have to be static if your allocator requires member
/// variables, but the DefaultAllocator doesn't and therefore uses static methods for
/// better performance.
///
/// Please note that an allocator is copied upon array construction - it would be
/// a bad idea if your custom allocator object would consist of more than a few variables.
///
/// THREADSAFE
//----------------------------------------------------------------------------------------
class DefaultAllocator
{
public:
	//----------------------------------------------------------------------------------------
	/// Computes the new size for a growing array.
	/// @param[in] current_size				Current number of elements.
	/// @param[in] increment					Number of elements to be added (>= 1)
	/// @param[in] min_chunk_size			The minimum number of elements upon array creation.
	/// THREADSAFE.
	/// @return												New number of elements.
	//----------------------------------------------------------------------------------------
	static Int ComputeArraySize(Int current_size, Int increment, Int min_chunk_size)
	{
		Int new_size	= (current_size + increment) * 3 / 2;	// increase required size by 50 % for future allocations
		Int remainder = new_size % min_chunk_size;
		if (remainder || new_size == 0)
			new_size += min_chunk_size - remainder;

		return new_size;
	}

	//----------------------------------------------------------------------------------------
	/// Allocates a memory block.
	/// The memory is not cleared, it may contain a certain byte pattern in debug mode.
	/// @param[in] s									Block size in bytes (values < 0 will return nullptr)
	/// @param[in] allocLocation			Pass MAXON_SOURCE_LOCATION to add the current source line and file.
	/// THREADSAFE.
	/// @return												Memory block address or nullptr.
	//----------------------------------------------------------------------------------------
	static inline void* Alloc(Int32 s, MAXON_SOURCE_LOCATION_DECLARATION)
	{
		return _DefaultAllocNC((Int)s, (Int32)MAXON_SOURCE_LOCATION_FORWARD.GetLine(), MAXON_SOURCE_LOCATION_FORWARD.GetFile());
	}

	//----------------------------------------------------------------------------------------
	/// Allocates a memory block.
	/// The memory is not cleared, it may contain a certain byte pattern in debug mode.
	/// @param[in] s									Block size in bytes (values < 0 will return nullptr)
	/// @param[in] allocLocation			Pass MAXON_SOURCE_LOCATION to add the current source line and file.
	/// THREADSAFE.
	/// @return												Memory block address or nullptr.
	//----------------------------------------------------------------------------------------
	static inline void* Alloc(Int64 s, MAXON_SOURCE_LOCATION_DECLARATION)
	{
		if (s != Int(s)) { DebugStop(); return nullptr; }
		return _DefaultAllocNC((Int)s, (Int32)MAXON_SOURCE_LOCATION_FORWARD.GetLine(), MAXON_SOURCE_LOCATION_FORWARD.GetFile());
	}

	//----------------------------------------------------------------------------------------
	/// Allocates a memory block and clears it.
	/// @param[in] s									Block size in bytes (values < 0 will return nullptr)
	/// @param[in] allocLocation			Pass MAXON_SOURCE_LOCATION to add the current source line and file.
	/// THREADSAFE.
	/// @return												Memory block address or nullptr.
	//----------------------------------------------------------------------------------------
	static inline void* AllocClear(Int32 s, MAXON_SOURCE_LOCATION_DECLARATION)
	{
		return _DefaultAlloc((Int)s, (Int32)MAXON_SOURCE_LOCATION_FORWARD.GetLine(), MAXON_SOURCE_LOCATION_FORWARD.GetFile());
	}

	//----------------------------------------------------------------------------------------
	/// Allocates a memory block and clears it.
	/// @param[in] s									Block size in bytes (values < 0 will return nullptr)
	/// @param[in] allocLocation			Pass MAXON_SOURCE_LOCATION to add the current source line and file.
	/// THREADSAFE.
	/// @return												Memory block address or nullptr.
	//----------------------------------------------------------------------------------------
	static inline void* AllocClear(Int64 s, MAXON_SOURCE_LOCATION_DECLARATION)
	{
		if (s != Int(s)) { DebugStop(); return nullptr; }
		return _DefaultAlloc((Int)s, (Int32)MAXON_SOURCE_LOCATION_FORWARD.GetLine(), MAXON_SOURCE_LOCATION_FORWARD.GetFile());
	}

	//----------------------------------------------------------------------------------------
	/// Resizes a memory block.
	/// The additional memory is not cleared, it may contain a certain byte pattern in debug mode.
	/// @param[in] p									Current memory block (can be nullptr)
	/// @param[in] n									New block size in bytes (values < 0 will return nullptr)
	/// @param[in] allocLocation			Pass MAXON_SOURCE_LOCATION to add the current source line and file.
	/// THREADSAFE.
	/// @return												Memory block address or nullptr if resize is not possible (p is still valid in this case)
	//----------------------------------------------------------------------------------------
	static inline void* Realloc(void* p, Int n, MAXON_SOURCE_LOCATION_DECLARATION)
	{
		return _DefaultReallocNC(p, (Int)n, (Int32)MAXON_SOURCE_LOCATION_FORWARD.GetLine(), MAXON_SOURCE_LOCATION_FORWARD.GetFile());
	}

	//----------------------------------------------------------------------------------------
	/// Frees a memory block.
	/// @param[in,out] p							Memory block address (can be nullptr, will be nullptr after return)
	/// THREADSAFE
	//----------------------------------------------------------------------------------------
	template<class T> static inline void  Free(T*& p)
	{
		void*	tmp = (void*) p;
		_DefaultFree(&tmp);
		p = nullptr;
	}
};

//----------------------------------------------------------------------------------------
/// Creates an object with constructor parameters (using new or T::Alloc, depending on the type). This does not throw any kind of
/// exception, it returns null if the allocation fails.
/// Usage: MyType* x = NewObj(MyType, optional constructor parameters);
/// @param[in] T									Type of object.
/// @param[in] ...								Additional constructor parameters.
/// THREADSAFE.
/// @return												Pointer to object (null if allocation failed)
//----------------------------------------------------------------------------------------
#define NewObj(T, ...)  MAXON_SAFE_PLACEMENT_NEW(maxon::DefaultAllocator::Alloc(SIZEOF(T), MAXON_SOURCE_LOCATION)) T(__VA_ARGS__)

#define NewObjClear(T, ...) MAXON_SAFE_PLACEMENT_NEW(maxon::DefaultAllocator::AllocClear(SIZEOF(T), MAXON_SOURCE_LOCATION)) T(__VA_ARGS__)

#ifdef _MSC_VER
	#define ALLOC_TYPENAME
#else
	#define ALLOC_TYPENAME	typename
#endif

//----------------------------------------------------------------------------------------
/// Deletes an object. This expects a pointer as argument, the object is deleted using the destructor or T::Free,
/// depending on the type of the object.
/// THREADSAFE.
/// @param[in,out] obj						Object pointer (can be nullptr, will be nullptr after return)
//----------------------------------------------------------------------------------------
// originally we used auto*& objectToDelete, but that doesn't work as the Intel Compiler has a bug that shows lots of warnings and MSVC has a bug where it doesn't link anymore
#define DeleteObj(obj) \
	do { \
		ALLOC_TYPENAME std::remove_reference<decltype(obj)>::type* objectToDelete = &(obj); \
		if (*objectToDelete) { \
			typedef ALLOC_TYPENAME std::remove_pointer<ALLOC_TYPENAME std::remove_pointer<decltype(objectToDelete)>::type>::type CtorType; \
			((CtorType*) (*objectToDelete))->~CtorType(); \
			maxon::DefaultAllocator::Free(*objectToDelete); \
			*objectToDelete = nullptr; \
		} \
	} while (false) // while ensures that the user needs to set a semicolon after DeleteObj

//----------------------------------------------------------------------------------------
/// Deletes an object. This calls the destructor and frees memory afterwards.
/// Normally you should use DeleteObj(). This variant should be used only in the rare case
/// when the object pointer is a constant so that it can't be set to nullptr.
/// @param[in] o									Object pointer (can be nullptr)
/// THREADSAFE
//----------------------------------------------------------------------------------------
template <typename T> inline void DeleteConstPtrObj(T* o)
{
	if (o)
	{
		o->~T();
		DefaultAllocator::Free(o);
	}
}

//----------------------------------------------------------------------------------------
/// Allocates raw memory: no constructors are called!
/// @param[in] T									Type of item (e.g. Char, Float)
/// @param[in] cnt								Number of items.
/// THREADSAFE.
/// @return												Pointer to memory block or nullptr.
//----------------------------------------------------------------------------------------
#define NewMem(T, cnt) ((T*) maxon::DefaultAllocator::Alloc((maxon::Int64)SIZEOF(T) * (maxon::Int64)(cnt), MAXON_SOURCE_LOCATION))

//----------------------------------------------------------------------------------------
/// Allocates raw memory and clears it: no constructors are called!
/// @param[in] T									Type of item (e.g. Char, Float)
/// @param[in] cnt								Number of items.
/// THREADSAFE.
/// @return												Pointer to memory block or nullptr.
//----------------------------------------------------------------------------------------
#define NewMemClear(T, cnt) ((T*) maxon::DefaultAllocator::AllocClear((maxon::Int64)SIZEOF(T) * (maxon::Int64)(cnt), MAXON_SOURCE_LOCATION))

//----------------------------------------------------------------------------------------
/// Resizes a raw memory block: no constructors are called!
/// @param[in] p									Previous memory block (can be nullptr)
/// @param[in] cnt								New number of items (size of the memory block is n * sizeof(T))
/// THREADSAFE.
/// @return												Pointer to memory block or nullptr.
//----------------------------------------------------------------------------------------
template <typename T> inline T* _ReallocMem(T* p, Int cnt, MAXON_SOURCE_LOCATION_DECLARATION)
{
	Int64	size = SIZEOF(T) * Int64(cnt);

#ifndef MAXON_TARGET_64BIT
	if (size > maxon::LIMIT<Int32>::MAX)											// overflow?
	{
		DebugStop();
		return nullptr;
	}
#endif

	return (T*) DefaultAllocator::Realloc(p, Int(size), MAXON_SOURCE_LOCATION_FORWARD);
}

//----------------------------------------------------------------------------------------
/// Resizes a raw memory block: no constructors are called!
/// @param[in] p									Previous memory block (can be nullptr)
/// @param[in] cnt								New number of items (size of the memory block is n * sizeof(T))
/// THREADSAFE.
/// @return												Pointer to memory block or nullptr.
//----------------------------------------------------------------------------------------
#define ReallocMem(p, cnt) _ReallocMem(p, cnt, MAXON_SOURCE_LOCATION)

//----------------------------------------------------------------------------------------
/// Frees a raw memory block: no destructors are called!
/// @param[in] p									Memory block (can be nullptr, will be nullptr after return)
/// THREADSAFE
//----------------------------------------------------------------------------------------
#define DeleteMem(p) (maxon::DefaultAllocator::Free(p))

//----------------------------------------------------------------------------------------
/// Clears memory of a datatype with pattern, if size >0.
/// THREADSAFE.
/// @param[out] data_ptr					Address of the datatype.
/// @param[in] cnt								Number of elements t be filled with pattern (>1 e.g. for arrays), can be 0.
/// @param[in] value							(optional) fill value.
//----------------------------------------------------------------------------------------
template <typename T> inline void ClearMemType(T* data_ptr, Int cnt, UChar value = 0)
{
	::memset(data_ptr, value, size_t(cnt * sizeof(T)));
}

} // namespace maxon

#endif
