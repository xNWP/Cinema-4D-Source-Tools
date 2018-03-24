/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef C4D_MEMORY_MP_H__
#define C4D_MEMORY_MP_H__

// Use to enable VTune API functions
// #define _USE_VTUNE_

#include "c4d_thread.h"
#include "c4d_misc.h"
#ifdef USE_API_MAXON
	#include "maxon/basearray.h"
#endif

//----------------------------------------------------------------------------------------
/// Advanced multi-threading array class.
/// @see <i>menutest.cpp</i> SDK example.
/// @warning Array types are not allowed: e.g. MPAlloc<<tt>Char</tt>> is fine, MPAlloc<<tt>Char</tt>[@em 1000]> will not work.
//----------------------------------------------------------------------------------------
template <class TYPE> class MPAlloc
{
	maxon::BaseArray<TYPE*> ptr;
	MPAlloc(const MPAlloc&);

public:
	//----------------------------------------------------------------------------------------
	/// Constructor.
	//----------------------------------------------------------------------------------------
	MPAlloc()
	{
	}

	//----------------------------------------------------------------------------------------
	/// Destructor.
	//----------------------------------------------------------------------------------------
	~MPAlloc()
	{
		Free();
	}

	//----------------------------------------------------------------------------------------
	/// Initializes the array with a number of threads.
	/// @param[in] maxthreads					The number of threads: @em 1 <= @formatParam{maxthreads} <= GeGetCurrentThreadCount()\n
	///																It does not need to match the actual GeGetCurrentThreadCount() on the machine. However for best speed GeGetCurrentThreadCount() should be used.
	/// @return												@trueIfOtherwiseFalse{successful}
	//----------------------------------------------------------------------------------------
	Bool Init(Int32 maxthreads)
	{
		Free();

		if (!ptr.Resize(maxthreads))
			return false;

		Int32 i;
		for (i = 0; i < maxthreads; i++)
		{
			Char* p = (Char*)C4DOS.Ge->AllocTH(i/*passthreadnum*/, sizeof(TYPE), true);
			if (!p)
			{
				Free();
				return false;
			}
			TYPE* res = new(p)TYPE;
			if (res != (TYPE*)p)
			{
				// must never happen!
				// it's not allowed to use array types for MPAlloc<>, e.g. MPAlloc<Char> is fine, MPAlloc<Char[1000]> will not work
				// the reason is that the compiler adds the arraysize in front of the memory block. the destructor is also not called
				CriticalStop();
				Free();
				return false;
			}
			ptr[i] = res;
		}
		return true;
	}

	//----------------------------------------------------------------------------------------
	/// Clears the array and frees the pointers.
	//----------------------------------------------------------------------------------------
	void Free()
	{
		Int32 i;
		for (i = 0; i < ptr.GetCount(); i++)
		{
			if (!ptr[i])
				continue;
			ptr[i]->~TYPE();
			void* dat = ptr[i];
			C4DOS.Ge->FreeTH(i, dat);
			ptr[i] = nullptr;
		}
		ptr.Flush();
	}

	//----------------------------------------------------------------------------------------
	/// Read-only array access operator.
	/// @param[in] i									The element index.
	/// @return												The element at @formatParam{i}.
	//----------------------------------------------------------------------------------------
	const TYPE& operator [](Int32 i) const { return *ptr[i]; }

	//----------------------------------------------------------------------------------------
	/// Array access operator.
	/// @param[in] i									The element index.
	/// @return												The element at @formatParam{i}.
	//----------------------------------------------------------------------------------------
	TYPE& operator [](Int32 i) { return *ptr[i]; }

	//----------------------------------------------------------------------------------------
	/// Assignment operator.
	/// @param[in] src								The source array.
	/// @return												The assigned array.
	//----------------------------------------------------------------------------------------
	MPAlloc& operator =(const MPAlloc& src)
	{
		Free();
		if (!Init(src.ptr.GetCount()))
			return *this;

		Int32 i, cnt = LMin(ptr.GetCount(), src.ptr.GetCount());
		for (i = 0; i < cnt; i++)
		{
			if (ptr[i] && src.ptr[i])
				*ptr[i] = *src.ptr[i];
		}
		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// Retrieves the array size.
	/// @return												The array size (number of elements).
	//----------------------------------------------------------------------------------------
	Int32 GetCount() const { return (Int32)ptr.GetCount(); }
};

#endif // C4D_MEMORY_MP_H__
