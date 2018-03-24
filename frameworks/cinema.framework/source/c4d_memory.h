/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_MEMORY_H__
#define C4D_MEMORY_H__

#ifdef __API_INTERN__
	#include "ge_memory.h"
#else

#include <new>
#if defined MAXON_TARGET_LINUX
	#include <stddef.h>
#endif

#include <string.h>
#include <stdlib.h>
#include "c4d_plugin.h"
#include "operatingsystem.h"
#include "ge_autoptr.h"

namespace maxon
{
void* GeNewMem(std::size_t s, int line, const char* file, bool clear);	// noexcept
void GeDeleteMem(void* p);																							// noexcept
}

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
void _GeCheck(void* memptr);		// Only for debug purposes

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
void _GeCheckAllMemory();		// Only for debug purposes

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
void _GeFree(void** Daten);

//----------------------------------------------------------------------------------------
/// Gets the size of memory blocks allocated by @C4D.
/// @param[in] p									Address of the memory block. @callerOwnsPointed{memory}
/// @param[out] out_size					Assigned the memory block size.
/// @return												@trueIfOtherwiseFalse{memory block size was retrieved}
//----------------------------------------------------------------------------------------
Bool GeGetAllocSize(void* p, Int* out_size);

//----------------------------------------------------------------------------------------
/// Checks if a memory block was allocated by @C4D or not.\n
/// @note Some linked libraries call new/delete during startup, before the @C4D OS is initialized.\n
/// This is a mess, because later calls to new will allocate through @C4D's memory routines.\n
/// Works for allocations done by @c new and NewMemClear().
/// @param[in] p									Address of the memory block. @callerOwnsPointed{memory}
/// @return												@trueIfOtherwiseFalse{memory block was allocated by @C4D}
//----------------------------------------------------------------------------------------
Bool IsAlienMem(void* p);

//----------------------------------------------------------------------------------------
/// @markPrivate
//----------------------------------------------------------------------------------------
Bool GeGetAllocatorStatistics(BaseContainer& stat, void* allocator = nullptr);
/// @addtogroup C4D_ALLOCATOR
/// @ingroup group_containerid
/// @markPrivate
/// @{
#define C4D_ALLOCATOR_STAT_CNT				1	// Int32
#define C4D_ALLOCATOR_STAT_TOTAL_USED	2	// Int64
#define C4D_ALLOCATOR_STAT_TOTAL_FREE	3	// Int64
#define C4D_ALLOCATOR_INFO_CONTAINER	4	// BaseContainer
#define C4D_ALLOCATOR_INFO_SLOT_SIZE	1	// Int32
#define C4D_ALLOCATOR_INFO_SLOT_USED	2	// Int64
#define C4D_ALLOCATOR_INFO_SLOT_FREE	3	// Int64
/// @}

//----------------------------------------------------------------------------------------
/// Gets estimated free physical memory.
/// @return												Estimated free physical memory.
//----------------------------------------------------------------------------------------
UInt GeMemGetFreePhysicalMemoryEstimate(void);

#define _GeAlloc(s, l, f)				 (C4DOS.Ge->Alloc((s), (l), (f)))
#define _GeAllocNC(s, l, f)			 (C4DOS.Ge->AllocNC((s), (l), (f)))
#define _GeReallocNC(p, s, l, f) (C4DOS.Ge->ReallocNC((p), (s), (l), (f)))

#ifdef USE_API_MAXON
	#include "maxon/defaultallocator.h"
#else
	#include "c4d_misc/memory/defaultallocator.h"
#endif

#ifdef MAXON_TARGET_64BIT
	#define __C4D_MEM_ALIGNMENT_MASK__ 15	///< Memory returned by NewMem() is guaranteed to be at least aligned to a @em 16 byte boundary
#else
	#define __C4D_MEM_ALIGNMENT_MASK__ 7	///< Memory returned by NewMem() is guaranteed to be at least aligned to a @em 8 byte boundary
#endif

#ifndef C4D_ALIGN
	#if defined MAXON_TARGET_WINDOWS
		#define C4D_ALIGN(_x_, _a_) __declspec(align(_a_)) _x_
	#else
		#define C4D_ALIGN(_x_, _a_) _x_ __attribute__((aligned(_a_)))
	#endif
#endif

//----------------------------------------------------------------------------------------
/// Clears a block of memory.
/// @param[in] d									Address of the memory block to clear. @callerOwnsPointed{memory}
/// @param[in] size								Size in bytes of the block of memory to clear.
/// @param[in] value							Value to clear the memory block with. Default to @em 0.
//----------------------------------------------------------------------------------------
inline void ClearMem(void* d, Int size, Int32 value = 0)
{
	memset(d, value & 0xFF, size);
}

//----------------------------------------------------------------------------------------
/// Copies a block of memory.
/// @warning Parameters order is the opposite of @c memcpy()
/// @see MemCopy()
/// @param[in] s									Address of the source block of memory. @callerOwnsPointed{memory}
/// @param[out] d									Address of the destination block of memory. @callerOwnsPointed{memory}
/// @param[in] size								Size in bytes of the block of memory to copy.
//----------------------------------------------------------------------------------------
inline void CopyMem(const void* s, void* d, Int size)
{
	if (s && d && size > 0)
		memcpy(d, s, size);
	else
		DebugStop();
}

//----------------------------------------------------------------------------------------
/// Copies a block of memory.
/// @param[out] d									Address of the destination block of memory. @callerOwnsPointed{memory}
/// @param[in] s									Address of the source block of memory. @callerOwnsPointed{memory}
/// @param[in] size								Size in bytes of the block of memory to copy.
//----------------------------------------------------------------------------------------
inline void MemCopy(void* d, const void* s, Int size)
{
	if (s && d && size > 0)
		memcpy(d, s, size);
	else
		DebugStop();
}

//----------------------------------------------------------------------------------------
/// @markInternal
//----------------------------------------------------------------------------------------
template <class T, class U> inline void FillMemTypeTemplate(T* data_ptr, Int size, const U* check_type, Int32 value)
{
#ifdef MAXON_TARGET_DEBUG
	if (check_type != data_ptr) // This will cause a compile time error if the types are different
		return;
#endif

	memset(data_ptr, value, size);
}

//----------------------------------------------------------------------------------------
/// Fills a block of memory of the specified type.
/// @param[in] t									Data type (e.g. Char, Float).
/// @param[out] d									Address of the block of memory to fill. @callerOwnsPointed{memory}
/// @param[in] x									Size of the memory block to fill.
/// @param[in] v									Value to fill the memory block with.
//----------------------------------------------------------------------------------------
#define FillMemType(t, d, x, v) FillMemTypeTemplate(d, sizeof(t) * (x), ((t*) d), v)

//----------------------------------------------------------------------------------------
/// Clears a block of memory.\n
/// THREADSAFE.
/// @param[out] data_ptr					Address of the block of memory to clear. @callerOwnsPointed{memory}
/// @param[in] cnt								Number of elements to be filled with pattern (> @em 1 e.g. for arrays), can be @em 0.
//----------------------------------------------------------------------------------------
template <typename T> inline void ClearMemType(T* data_ptr, Int cnt)
{
	memset(data_ptr, 0, size_t(cnt * sizeof(T)));
}

//----------------------------------------------------------------------------------------
/// Copies a block of memory to another of the same kind.\n
/// THREADSAFE
/// @warning Source and destination must not overlap.
/// @param[in] src_ptr						Address of the source block of memory to copy. @callerOwnsPointed{memory}
/// @param[out] dst_ptr						Address of the destination block of memory to copy to. @callerOwnsPointed{memory}
/// @param[in] cnt								Number of elements to be copied (> @em 1 e.g. for arrays), can be @em 0.
//----------------------------------------------------------------------------------------
template <typename T> inline void CopyMemType(const T* src_ptr, T* dst_ptr, Int cnt)
{
	memcpy(dst_ptr, src_ptr, size_t(cnt * sizeof(T)));
}

//----------------------------------------------------------------------------------------
/// @markDeprecated and will be removed.\n
/// Substitute for @c bNew T[cnt]. Does not require us to intercept operator @c new[]/@c delete[].
/// But it is more cumbersome no faster and less secure than using a @link maxon::BaseArray BaseArray@endlink.
//----------------------------------------------------------------------------------------
template <typename T> inline T* bNewDeprecatedUseArraysInstead(Int cnt)
{
	void* mem = _GeAlloc((__C4D_MEM_ALIGNMENT_MASK__ + 1) + (sizeof(T) * cnt), __LINE__, __FILE__);
	if (mem)
	{
		*(Int*) mem = cnt;

		T* data = (T*) (UInt(mem) + (__C4D_MEM_ALIGNMENT_MASK__ + 1));
		mem = (void*) data;

		for (Int i = 0; i < cnt; i++)
			new (&data[i]) T;
	}
	return (T*) mem;
}

//----------------------------------------------------------------------------------------
/// @markDeprecated and will be removed.
/// @see bNewDeprecatedUseArraysInstead
//----------------------------------------------------------------------------------------
template <typename T> inline void bDelete(T*& v)
{
	if (v)
	{
		void* data = (void*) (UInt(v) - (__C4D_MEM_ALIGNMENT_MASK__ + 1));
		Int cnt = *(Int*) data;

		for (Int i = 0; i < cnt; i++)
			v[i].~T();

		_GeFree((void**)&data);
		v = nullptr;
	}
}


#define MEMORYPOOL_DEFAULT_BLOCKSIZE 0x80000

//----------------------------------------------------------------------------------------
/// @markDeprecated
//----------------------------------------------------------------------------------------
class DeprecatedMemoryPool
{
private:
	DeprecatedMemoryPool();
	~DeprecatedMemoryPool();

public:
	static DeprecatedMemoryPool* Alloc(Int block_size) { return C4DOS.Pl->Alloc(block_size); }
	static DeprecatedMemoryPool* Alloc() { return C4DOS.Pl->Alloc(MEMORYPOOL_DEFAULT_BLOCKSIZE); }
	static void Free(DeprecatedMemoryPool*& pool)
	{
		if (pool)
			C4DOS.Pl->Free(pool);
		pool = nullptr;
	}

	void* MemAlloc(Int size, Bool clear = true) { return C4DOS.Pl->AllocElement(this, size, clear); }
	void MemFree(void* mem, Int size) { C4DOS.Pl->FreeElement(this, mem, size); }
	void* MemAllocS(Int size, Bool clear = true) { return C4DOS.Pl->AllocElementS(this, size, clear); }
	void MemFreeS(void* mem) { C4DOS.Pl->FreeElementS(this, mem); }
	void* MemReAllocS(void* old, Int size, Bool clear = true) { return C4DOS.Pl->ReAllocElementS(this, old, size, clear); }
};

#endif

#endif // C4D_MEMORY_H__
