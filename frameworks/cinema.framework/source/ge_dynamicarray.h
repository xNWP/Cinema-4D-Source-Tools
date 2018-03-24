/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef GE_DYNAMICARRAY_H__
#define GE_DYNAMICARRAY_H__

#ifdef __API_INTERN__
	#include "hyperfile.h"
	#include "lib_zipfile.h"
#else
	#include "ge_math.h"
	#include "c4d_file.h"
	#include "c4d_memory.h"
	#include "c4d_baselist.h"
	#include "c4d_general.h"
	#include "lib_zipfile.h"
#endif

#if defined MAXON_TARGET_LINUX
	#include <new>
#elif defined MAXON_TARGET_OSX
	#include <new>
#else
	#include <new.h>
#endif

#include <string.h>
#include "x4d_macros.h"

enum GeDynamicArrayType
{
	DATYPE_NONE			 = 0,
	DATYPE_CHAR			 = -1,
	DATYPE_UCHAR		 = -2,
	DATYPE_WORD			 = -3,
	DATYPE_UWORD		 = -4,
	DATYPE_LONG			 = -5,
	DATYPE_ULONG		 = -6,
	DATYPE_REAL			 = -7,
	DATYPE_LREAL		 = -8,
	DATYPE_BOOL			 = -9,
	DATYPE_TIME			 = -10,
	DATYPE_VECTOR		 = -11,
	DATYPE_LVECTOR	 = -12,
	DATYPE_MATRIX		 = -13,
	DATYPE_LMATRIX	 = -14,
	DATYPE_STRING		 = -15,
	DATYPE_FILENAME	 = -16,
	DATYPE_LLONG		 = -17,
	DATYPE_SREAL		 = -18,
	DATYPE_CONTAINER = -19,
	DATYPE_SVECTOR	 = -20,
	DATYPE_SMATRIX	 = -21
} ENUM_END_LIST(GeDynamicArrayType);

#if 0
	#define CHECKMEM(x) _GeCheck(x)
#else
	#define CHECKMEM(x)
#endif

class GeDynamicArrayFileData
{
public:
	explicit GeDynamicArrayFileData(GeDynamicArrayType type = DATYPE_NONE, Int32 offset = 0) : d_type(type), d_offset(offset) { }
	~GeDynamicArrayFileData() { }

	GeDynamicArrayType d_type;		// The type, e.g. DATYPE_CHAR
	Int32							 d_offset;	// The offset from the start of the structure
};

// GeDynamicArray file structure helper, arguments are s = Struct, m = Member, t = type
#define GeDynamicArrayFile(s, m, t) GeDynamicArrayFileData(t, offsetofI(s, m))

inline Bool GeDynamicArrayWriteable(Int32 type)
{
	switch (type)
	{
		case DATYPE_CHAR:
		case DATYPE_WORD:
		case DATYPE_LONG:
		case DATYPE_REAL:
		case DATYPE_LREAL:
		case DATYPE_SREAL:
		case DATYPE_LLONG:		return true;
		default:	break;
	}
	return false;
}

inline Int GeDynamicArrayStructSizeCheck(GeDynamicArrayFileData* list, Int count)
{
	if (!list)
		return 0;

	Int size = 0, i = 0;

	for (i = count - 1; i >= 0; --i)
	{
		switch (list[i].d_type)
		{
			default:
			case DATYPE_NONE: break;
			case DATYPE_CHAR: size			+= sizeof(Char); break;
			case DATYPE_UCHAR: size			+= sizeof(UChar); break;
			case DATYPE_WORD: size			+= sizeof(Int16); break;
			case DATYPE_UWORD: size			+= sizeof(UInt16); break;
			case DATYPE_LONG: size			+= sizeof(Int32); break;
			case DATYPE_ULONG: size			+= sizeof(UInt32); break;
			case DATYPE_REAL: size			+= sizeof(Float); break;
			case DATYPE_LREAL: size			+= sizeof(Float64); break;
			case DATYPE_BOOL: size			+= sizeof(Bool); break;
			case DATYPE_TIME: size			+= sizeof(BaseTime); break;
			case DATYPE_VECTOR: size		+= sizeof(Vector); break;
			case DATYPE_LVECTOR: size		+= sizeof(Vector64); break;
			case DATYPE_SVECTOR: size		+= sizeof(Vector32); break;
			case DATYPE_MATRIX: size		+= sizeof(Matrix); break;
			case DATYPE_LMATRIX: size		+= sizeof(Matrix64); break;
			case DATYPE_SMATRIX: size		+= sizeof(Matrix32); break;
			case DATYPE_STRING: size		+= sizeof(String); break;
			case DATYPE_FILENAME: size	+= sizeof(Filename); break;
			case DATYPE_LLONG: size			+= sizeof(Int64); break;
			case DATYPE_SREAL: size			+= sizeof(Float32); break;
			case DATYPE_CONTAINER: size += sizeof(BaseContainer); break;
		}
	}

	return size;
}


// Dynamic array template

//----------------------------------------------------------------------------------------
/// @note @markDeprecated Use maxon::BaseArray instead.
//----------------------------------------------------------------------------------------
template <class TYPE> class GeDynamicArray
{
protected:
	TYPE*	ptr;
	TYPE*	l_ptr;

	Int		l_cnt;
	Int		totcnt;
	Int		blocksize;
	Int		count;

public:
	GeDynamicArray();
	explicit GeDynamicArray(Int size);
	GeDynamicArray(Int size, Int block);
	GeDynamicArray(const GeDynamicArray<TYPE>& g);
	~GeDynamicArray();

	typedef void GeDynamicArrayCallback (Int index, TYPE * value, void* data);

	TYPE*					Release(void);
	void FreeArray(void);
	GeDynamicArray<TYPE>& operator =(const GeDynamicArray<TYPE>& t);

	// friend	Bool operator !(const GeDynamicArray<TYPE> &t) { return t.count == 0; }
	// operator TYPE * ()											{	return l_ptr;	}
	// TYPE * const *operator &()							{	return &l_ptr;	}

	Bool Content()								 { return l_ptr != nullptr; }
	TYPE* GetPtr()												 { return l_ptr; }

	TYPE& operator[] (Int32 i) const { DebugAssert(i >= 0 && i < count); return l_ptr[i];	}
	TYPE& operator[] (Int64 i) const { DebugAssert(i >= 0 && i < count); return l_ptr[i];	}
	Int	GetCount(void) const { return count; }
	void SetCount(Int c);
	Int	GetTotCount(void)	const	{ return totcnt - l_cnt; }
	void SetBlockSize(Int size);
	Int	GetBlockSize(void) const { return blocksize; }
	Bool ReadUsingFunction(HyperFile* hf, Int32 level);
	Bool WriteUsingFunction(HyperFile* hf);
	Bool Read(HyperFile* hf, GeDynamicArray<GeDynamicArrayFileData>& typelist);
	Bool Write(HyperFile* hf, GeDynamicArray<GeDynamicArrayFileData>& typelist);
	void DoToAll(GeDynamicArrayCallback* callback, void* data);
	void DoToSome(GeDynamicArrayCallback* callback, void* data, Int do_start, Int do_end);
	void DoToSearch(GeDynamicArrayCallback* callback, void* data, TYPE p);
	Bool ReScopeNC(Int cnt, Bool make_new = true);
	Bool ReScope(Int cnt);
	Bool ReSizeNC(Int cnt, Bool make_new = true);
	Bool ReSize(Int cnt);
	Bool ReSize(Int c_from, Int c_to);
	inline void	Fill(Int c_from, Int c_to, TYPE t);
	inline void	Fill(TYPE t);
	Bool Insert(TYPE p, Int index);
	Bool Insert(const TYPE* p, Int index, Int cnt);
	Bool MergeIn(GeDynamicArray<TYPE>& p, Int index);
	Bool InsertSpace(Int index, Int amount, Bool clear = true, Bool makenew = true);
	inline Bool	Push(TYPE p);
	Bool Remove(Int index, Int amount = 1);
	inline void	RemoveAll(TYPE p);
	TYPE Pop(void);
	inline Int Find(TYPE p);
	inline Int Find(TYPE p, Int index);
	void Shift(Int index, Int cnt);
	void ShiftBlock(Int b_from, Int b_to, Int amount);
	void Grab(TYPE* p, Int amount);
};

template <class TYPE> GeDynamicArray<TYPE>::GeDynamicArray(void)
{
	ptr = nullptr;
	blocksize = 4;
	FreeArray();
}

template <class TYPE> GeDynamicArray<TYPE>::GeDynamicArray(Int size)
{
	ptr = nullptr;
	blocksize = 4;
	FreeArray();
	ReScope(size);
}

template <class TYPE> GeDynamicArray<TYPE>::GeDynamicArray(Int size, Int block)
{
	ptr = nullptr;
	blocksize = block;
	FreeArray();
	ReScope(size);
}

template <class TYPE> GeDynamicArray<TYPE>::GeDynamicArray(const GeDynamicArray<TYPE>& g)
{
	ptr = nullptr;
	blocksize = g.blocksize;
	FreeArray();
	*this = g;
}


template <class TYPE> GeDynamicArray<TYPE>::~GeDynamicArray(void)
{
	FreeArray();
}

template <class TYPE> TYPE* GeDynamicArray<TYPE>::Release(void)
{
	CHECKMEM(ptr);
	memmove(ptr, l_ptr, sizeof(TYPE) * count);
	blocksize = 4;
	Int cnt = count;
	count += l_cnt;
	l_ptr	 = ptr;
	CHECKMEM(ptr);
	l_cnt = 0;
	ReSizeNC(cnt);
	TYPE* tmp = ptr;
	ptr = nullptr;
	l_ptr	 = nullptr;
	totcnt = 0;
	count	 = 0;
	l_cnt	 = 0;
	return tmp;
}

template <class TYPE> void GeDynamicArray<TYPE>::FreeArray(void)
{
	if (ptr)
	{
		Int		i = 0;
		TYPE* buf = l_ptr;

		CHECKMEM(ptr);

		for (i = 0; i < count; i++, buf++)
			buf->~TYPE();

		DeleteMem(ptr);
	}
	ptr = nullptr;
	l_ptr	 = nullptr;
	count	 = 0;
	totcnt = 0;
	l_cnt	 = 0;
}

template <class TYPE> GeDynamicArray<TYPE>& GeDynamicArray<TYPE>::operator =(const GeDynamicArray<TYPE>& t)
{
	CHECKMEM(ptr);

	if (t.blocksize != blocksize)
	{
		FreeArray();
		SetBlockSize(t.blocksize);
	}
	if (!ReScopeNC(t.count))
		return *this;

	Int	i = 0;

	TYPE* pbuf = l_ptr;
	TYPE* tbuf = t.l_ptr;
	for (i = 0; i < count; i++, pbuf++, tbuf++)
		*pbuf = *tbuf;

	CHECKMEM(ptr);

	return *this;
}

template <class TYPE> void GeDynamicArray<TYPE>::SetCount(Int c)
{
	DebugAssert(c >= 0 && c <= totcnt - l_cnt);
	if (c > totcnt - l_cnt)
		return;
	CHECKMEM(ptr);
	TYPE* buf = &l_ptr[c];
	for (Int i = c; i < count; i++, buf++)
		buf->~TYPE();
	count = c;
}

template <class TYPE> void GeDynamicArray<TYPE>::SetBlockSize(Int size)
{
	blocksize = size;
}

template <class TYPE> Bool GeDynamicArray<TYPE>::ReadUsingFunction(HyperFile* hf, Int32 level)
{
	Int32 dlevel = 0;
	if (!hf->ReadInt32(&dlevel))
		return false;

	if (dlevel >= 1)
	{
		FreeArray();

		Int64 p;
		if (!hf->ReadInt64(&p))
			return false;
		blocksize = Int(p);
		if (!hf->ReadInt64(&p))
			return false;
		if (!ReScope(Int(p)))
			return false;

		for (p = 0; p < count; p++)
		{
			if (!l_ptr[p].Read(hf, level))
				return false;
		}
	}

	return true;
}

template <class TYPE> Bool GeDynamicArray<TYPE>::WriteUsingFunction(HyperFile* hf)
{
	if (!hf->WriteInt32(1))
		return false;		// Level

	if (!hf->WriteInt64(Int64(blocksize)))
		return false;
	if (!hf->WriteInt64(Int64(count)))
		return false;

	Int i = 0;
	for (i = 0; i < count; i++)
	{
		if (!l_ptr[i].Write(hf))
			return false;
	}

	return true;
}

// Read array from hyperfile with list of types in order of how they appear in structures
template <class TYPE> Bool GeDynamicArray<TYPE>::Read(HyperFile* hf, GeDynamicArray<GeDynamicArrayFileData>& typelist)
{
	if (typelist.GetCount() == 0 || !hf)
		return false;

	Int64 r_count = 0, r_blocksize = 0;
	Int32 r_level = 0;
	Int		tsize = sizeof(TYPE);

	DebugAssert(GeDynamicArrayStructSizeCheck(typelist.GetPtr(), typelist.GetCount()) <= tsize);

	if (!hf->ReadInt32(&r_level))
		return false;
	if (r_level < 0)
	{
		r_level = -r_level;
		if (!hf->ReadInt64(&r_count))
			return false;
		if (!hf->ReadInt64(&r_blocksize))
			return false;
	}
	else
	{
		r_count = r_level;
		if (!hf->ReadInt32(&r_level))
			return false;
		r_blocksize = r_level;
		r_level = 0;
	}

	SetBlockSize(Int(r_blocksize));
	if (!ReScopeNC(Int(r_count)))
		return false;
	if (count == 0)
		return true;
	if (!tsize)
		return true;

	CHECKMEM(ptr);
	if (r_level > 0 && typelist.GetCount() == 1 && GeDynamicArrayWriteable(typelist[0].d_type))
	{
		// Write arrays when there's only one type being written
		Char* ttbuf = &((Char*)l_ptr)[typelist[0].d_offset];

		switch (typelist[0].d_type)
		{
			case DATYPE_CHAR:
				if (!hf->ReadArray((void*)ttbuf, HYPERFILEARRAY_CHAR, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_WORD:
				if (!hf->ReadArray((void*)ttbuf, HYPERFILEARRAY_WORD, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_LONG:
				if (!hf->ReadArray((void*)ttbuf, HYPERFILEARRAY_LONG, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_REAL:
				if (!hf->ReadArray((void*)ttbuf, HYPERFILEARRAY_REAL, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_SREAL:
				if (!hf->ReadArray((void*)ttbuf, HYPERFILEARRAY_SREAL, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_LREAL:
				if (!hf->ReadArray((void*)ttbuf, HYPERFILEARRAY_LREAL, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_LLONG:
				if (!hf->ReadArray((void*)ttbuf, HYPERFILEARRAY_LLONG, (Int32)tsize, (Int32)count))
					return false;
				break;
			default:	break;
		}
	}
	else
	{
		TYPE* tbuf = l_ptr;
		Int		i = 0, o = 0;
		Char* ttbuf = nullptr;
		for (i = 0; i < count; i++, tbuf++)
		{
			for (o = 0; o < typelist.GetCount(); o++)
			{
				ttbuf = &((Char*)tbuf)[typelist[o].d_offset];

				switch (typelist[o].d_type)
				{
					case DATYPE_CHAR:
						if (!hf->ReadChar(ttbuf))
							return false;
						break;
					case DATYPE_UCHAR:
						if (!hf->ReadUChar((UChar*) ttbuf))
							return false;
						break;
					case DATYPE_WORD:
						if (!hf->ReadInt16((Int16*) ttbuf))
							return false;
						break;
					case DATYPE_UWORD:
						if (!hf->ReadUInt16((UInt16*) ttbuf))
							return false;
						break;
					case DATYPE_LONG:
						if (!hf->ReadInt32((Int32*) ttbuf))
							return false;
						break;
					case DATYPE_ULONG:
						if (!hf->ReadUInt32((UInt32*) ttbuf))
							return false;
						break;
					case DATYPE_REAL:
						if (!hf->ReadFloat((Float*) ttbuf))
							return false;
						break;
					case DATYPE_LREAL:
						if (!hf->ReadFloat64((Float64*) ttbuf))
							return false;
						break;
					case DATYPE_SREAL:
						if (!hf->ReadFloat32((Float32*) ttbuf))
							return false;
						break;
					case DATYPE_BOOL:
						if (!hf->ReadBool((Bool*) ttbuf))
							return false;
						break;
					case DATYPE_TIME:
						if (!hf->ReadTime((BaseTime*) ttbuf))
							return false;
						break;
					case DATYPE_VECTOR:
						if (!hf->ReadVector((Vector*) ttbuf))
							return false;
						break;
					case DATYPE_SVECTOR:
						if (!hf->ReadVector32((Vector32*) ttbuf))
							return false;
						break;
					case DATYPE_LVECTOR:
						if (!hf->ReadVector64((Vector64*) ttbuf))
							return false;
						break;
					case DATYPE_MATRIX:
						if (!hf->ReadMatrix((Matrix*) ttbuf))
							return false;
						break;
					case DATYPE_SMATRIX:
						if (!hf->ReadMatrix32((Matrix32*) ttbuf))
							return false;
						break;
					case DATYPE_LMATRIX:
						if (!hf->ReadMatrix64((Matrix64*) ttbuf))
							return false;
						break;
					case DATYPE_STRING:
						if (!hf->ReadString((String*) ttbuf))
							return false;
						break;
					case DATYPE_FILENAME:
						if (!hf->ReadFilename((Filename*) ttbuf))
							return false;
						break;
					case DATYPE_LLONG:
						if (!hf->ReadInt64((Int64*) ttbuf))
							return false;
						break;
					case DATYPE_CONTAINER:
						if (!hf->ReadContainer((BaseContainer*) ttbuf, true))
							return false;
						break;
					default:	break;
				}
			}
		}
	}
	CHECKMEM(ptr);

	return true;
}

// Write array to hyperfile
template <class TYPE> Bool GeDynamicArray<TYPE>::Write(HyperFile* hf, GeDynamicArray<GeDynamicArrayFileData>& typelist)
{
	if (typelist.GetCount() == 0 || !hf)
		return false;

	Int64 r_count = Int64(count), r_blocksize = Int64(blocksize);
	Int		tsize = sizeof(TYPE);

	DebugAssert(GeDynamicArrayStructSizeCheck(typelist.GetPtr(), typelist.GetCount()) <= tsize);

	if (!hf->WriteInt32(-1))
		return false;		// Level
	if (!hf->WriteInt64(r_count))
		return false;
	if (!hf->WriteInt64(r_blocksize))
		return false;
	if (!ptr || count == 0)
		return true;

	if (!tsize)
		return true;

	CHECKMEM(ptr);

	if (typelist.GetCount() == 1 && GeDynamicArrayWriteable(typelist[0].d_type))
	{
		// Write arrays when there's only one type being written
		Char* ttbuf = &((Char*)l_ptr)[typelist[0].d_offset];

		switch (typelist[0].d_type)
		{
			case DATYPE_CHAR:
				if (!hf->WriteArray((void*)ttbuf, HYPERFILEARRAY_CHAR, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_WORD:
				if (!hf->WriteArray((void*)ttbuf, HYPERFILEARRAY_WORD, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_LONG:
				if (!hf->WriteArray((void*)ttbuf, HYPERFILEARRAY_LONG, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_REAL:
				if (!hf->WriteArray((void*)ttbuf, HYPERFILEARRAY_REAL, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_LREAL:
				if (!hf->WriteArray((void*)ttbuf, HYPERFILEARRAY_LREAL, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_SREAL:
				if (!hf->WriteArray((void*)ttbuf, HYPERFILEARRAY_SREAL, (Int32)tsize, (Int32)count))
					return false;
				break;
			case DATYPE_LLONG:
				if (!hf->WriteArray((void*)ttbuf, HYPERFILEARRAY_LLONG, (Int32)tsize, (Int32)count))
					return false;
				break;
			default:	break;
		}
	}
	else
	{
		Int		i = 0, o = 0;
		TYPE* tbuf	= l_ptr;
		Char* ttbuf = nullptr;
		for (i = 0; i < count; i++, tbuf++)
		{
			for (o = 0; o < typelist.GetCount(); o++)
			{
				ttbuf = &((Char*)tbuf)[typelist[o].d_offset];

				switch (typelist[o].d_type)
				{
					case DATYPE_CHAR:
						if (!hf->WriteChar(ttbuf[0]))
							return false;
						break;
					case DATYPE_UCHAR:
						if (!hf->WriteUChar(((UChar*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_WORD:
						if (!hf->WriteInt16(((Int16*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_UWORD:
						if (!hf->WriteUInt16(((UInt16*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_LONG:
						if (!hf->WriteInt32(((Int32*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_ULONG:
						if (!hf->WriteUInt32(((UInt32*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_REAL:
						if (!hf->WriteFloat(((Float*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_SREAL:
						if (!hf->WriteFloat32(((Float32*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_LREAL:
						if (!hf->WriteFloat64(((Float64*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_BOOL:
						if (!hf->WriteBool(((Bool*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_TIME:
						if (!hf->WriteTime(((BaseTime*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_VECTOR:
						if (!hf->WriteVector(((Vector*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_SVECTOR:
						if (!hf->WriteVector32(((Vector32*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_LVECTOR:
						if (!hf->WriteVector64(((Vector64*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_MATRIX:
						if (!hf->WriteMatrix(((Matrix*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_SMATRIX:
						if (!hf->WriteMatrix32(((Matrix32*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_LMATRIX:
						if (!hf->WriteMatrix64(((Matrix64*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_STRING:
						if (!hf->WriteString(((String*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_FILENAME:
						if (!hf->WriteFilename(((Filename*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_LLONG:
						if (!hf->WriteInt64(((Int64*) ttbuf)[0]))
							return false;
						break;
					case DATYPE_CONTAINER:
						if (!hf->WriteContainer(((BaseContainer*) ttbuf)[0]))
							return false;
						break;
					default:	break;
				}
			}
		}
	}

	CHECKMEM(ptr);

	return true;
}

// routine to execute code on all entries in ptr array
template <class TYPE> void GeDynamicArray<TYPE>::DoToAll(GeDynamicArrayCallback* callback, void* data)
{
	if (!ptr)
		return;

	CHECKMEM(ptr);

	Int		i = 0;
	TYPE* buf = l_ptr;
	for (i = 0; i < count; i++, buf++)
	{
		callback(i, buf, data);
	}
	CHECKMEM(ptr);

}

// routine to execute code on some entries in ptr array
template <class TYPE> void GeDynamicArray<TYPE>::DoToSome(GeDynamicArrayCallback* callback, void* data, Int do_start, Int do_end)
{
	if (!ptr)
		return;

	CHECKMEM(ptr);

	Int	dend = do_end;
	Int	dsta = do_start;
	if (dend < dsta)
		dend = do_start, dsta = do_end;
	if (dend > count)
		dend = count;
	if (dsta < 0)
		dsta = 0;

	TYPE* buf = &l_ptr[dsta];
	Int		i = 0;
	for (i = dsta; i < dend; i++, buf++)
	{
		callback(i, buf, data);
	}
	CHECKMEM(ptr);
}

// routine to execute code on entries that match TYPE p in ptr array
template <class TYPE> void GeDynamicArray<TYPE>::DoToSearch(GeDynamicArrayCallback* callback, void* data, TYPE p)
{
	if (!ptr)
		return;

	CHECKMEM(ptr);

	TYPE* buf = l_ptr;
	Int		i = 0;
	for (i = 0; i < count; i++, buf++)
	{
		if (*buf == p)
			callback(i, buf, data);
	}
	CHECKMEM(ptr);
}

// Resizes the array without retatining the data and without clearing the data
template <class TYPE> Bool GeDynamicArray<TYPE>::ReScopeNC(Int cnt, Bool make_new)
{
	if (cnt <= 0)
	{
		FreeArray();
		return true;
	}

	if (!blocksize)
	{
		CriticalStop();
		return false;
	}
	Int64	nsize = (((cnt + l_cnt - 1) / blocksize) + 1) * blocksize, i = 0;
	TYPE* buf = nullptr;

	CHECKMEM(ptr);

	if (count)
	{
		for (i = 0, buf = l_ptr; i < count; i++, buf++)
			buf->~TYPE();
	}

	if (nsize != totcnt && !(cnt > count && nsize < totcnt))
	{
		// Check against massive numbers
		Int64 tsize = nsize * Int64(sizeof(TYPE));
		if (tsize != Int(tsize) || tsize < nsize || tsize < cnt)
		{
			DebugAssert(false);	// To avoid people allocating more memory than is possible on the system
			return false;				//
		}

		if (!ptr)
			ptr = (TYPE*) maxon::DefaultAllocator::Alloc(tsize, MAXON_SOURCE_LOCATION);
		else
			ptr = (TYPE*) maxon::DefaultAllocator::Realloc(ptr, tsize, MAXON_SOURCE_LOCATION);

		if (!ptr)
			return false;

		l_ptr	 = &ptr[l_cnt];
		totcnt = (Int)nsize;
	}

	if (make_new)
	{
		for (i = 0, buf = l_ptr; i < cnt; i++, buf++)
			new(buf)TYPE;
	}

	count = cnt;

	CHECKMEM(ptr);

	return true;
}

// Resizes the array without retaining the data
template <class TYPE> Bool GeDynamicArray<TYPE>::ReScope(Int cnt)
{
	if (cnt <= 0)
	{
		FreeArray();
		return true;
	}

	if (!blocksize)
	{
		CriticalStop();
		return false;
	}
	Int64	nsize = (((cnt + l_cnt - 1) / blocksize) + 1) * blocksize, i = 0;
	TYPE* buf = nullptr;

	CHECKMEM(ptr);

	if (count)
	{
		for (i = 0, buf = l_ptr; i < count; i++, buf++)
			buf->~TYPE();
	}

	if (nsize != totcnt && !(cnt > count && nsize < totcnt))
	{
		// Check against massive numbers
		Int64 tsize = nsize * Int64(sizeof(TYPE));
		if (tsize != Int(tsize) || tsize < nsize || tsize < cnt)
		{
			DebugAssert(false);	// To avoid people allocating more memory than is possible on the system
			return false;				//
		}

		if (!ptr)
			ptr = (TYPE*) maxon::DefaultAllocator::Alloc(tsize, MAXON_SOURCE_LOCATION);
		else
			ptr = (TYPE*) maxon::DefaultAllocator::Realloc(ptr, tsize, MAXON_SOURCE_LOCATION);

		if (!ptr)
			return false;

		l_ptr = &ptr[l_cnt];

		totcnt = (Int)nsize;
	}

	maxon::ClearMemType(l_ptr, cnt);
	for (i = 0, buf = l_ptr; i < cnt; i++, buf++)
		new(buf)TYPE;

	count = cnt;
	CHECKMEM(ptr);
	return true;
}

// Resizes the array without clearing the memory used
template <class TYPE> Bool GeDynamicArray<TYPE>::ReSizeNC(Int cnt, Bool make_new)
{
	if (cnt == count)
		return true;

	if (cnt < count)
		return Remove(cnt, count - cnt);
	return InsertSpace(count, cnt - count, false, make_new);
}

template <class TYPE> Bool GeDynamicArray<TYPE>::ReSize(Int cnt)
{
	if (cnt == count)
		return true;

	if (cnt < count)
		return Remove(cnt, count - cnt);
	return InsertSpace(count, cnt - count, true);
}

// Reize the array down
template <class TYPE> Bool GeDynamicArray<TYPE>::ReSize(Int c_from, Int c_to)
{
	Int	t_from = VCut(c_from, 0, count), t_to = VCut(c_to + 1, 0, count);
	if (t_from == t_to)
		return ReSize(0);
	if (t_from > t_to)
	{
		Int	temp = t_from;
		t_from = t_to;
		t_to = temp;
	}

	Shift(t_from, -t_from);
	return ReSize(t_to - t_from);
}

// Fill the array with TYPE t between c_from and c_to
template <class TYPE> inline void GeDynamicArray<TYPE>::Fill(Int c_from, Int c_to, TYPE t)
{
	Int	t_from = VCut(c_from, 0, count), t_to = VCut(c_to + 1, 0, count);
	if (t_from == t_to)
		return;
	if (t_from > t_to)
	{
		Int	temp = t_from;
		t_from = t_to;
		t_to = temp;
	}

	TYPE* buf = nullptr;
	Int		i = 0;
	CHECKMEM(ptr);
	for (i = t_from, buf = &l_ptr[t_from]; i < t_to; i++, buf++)
		*buf = t;
	CHECKMEM(ptr);
}

// Fill the array with TYPE t
template <class TYPE> inline void GeDynamicArray<TYPE>::Fill(TYPE t)
{
	TYPE* buf = l_ptr;
	Int		i = 0;
	CHECKMEM(ptr);
	for (i = 0; i < count; i++, buf++)
		*buf = t;
	CHECKMEM(ptr);
}

// Add value to the array at index
// and shifts array up
template <class TYPE> Bool GeDynamicArray<TYPE>::Insert(TYPE p, Int index)
{
	if (index < 0)
		return false;
	CHECKMEM(ptr);
	if (!InsertSpace(index, 1, true))
		return false;
	l_ptr[index] = p;
	CHECKMEM(ptr);
	return true;
}

// Inserts (copies) an existing array into this one
template <class TYPE> Bool GeDynamicArray<TYPE>::Insert(const TYPE* p, Int index, Int cnt)
{
	if (cnt <= 0)
		return true;
	if (index < 0 || index > count || !p)
		return false;
	CHECKMEM(ptr);
	if (!InsertSpace(index, cnt, true))
		return false;
	Int					i = 0;
	TYPE*				buf	 = &l_ptr[index];
	const TYPE* pbuf = p;
	for (i = 0; i < cnt; i++, pbuf++, buf++)
		(*buf) = (*pbuf);
	CHECKMEM(ptr);
	return true;
}

// Merges an existing dynamic array into this one, this array becomes the owner
template <class TYPE> Bool GeDynamicArray<TYPE>::MergeIn(GeDynamicArray<TYPE>& p, Int index)
{
	if (p.GetCount() <= 0)
		return true;
	if (index < 0 || index > count)
		return false;
	CHECKMEM(ptr);
	if (!InsertSpace(index, p.GetCount(), false, false))
		return false;
	Int		cnt	 = p.GetCount();
	TYPE* data = p.Release();
	if (!data)
		return false;
	CopyMemType(data, &l_ptr[index], cnt);
	DeleteMem(data);
	CHECKMEM(ptr);
	return true;
}

// Inserts a gap in the array
template <class TYPE> Bool GeDynamicArray<TYPE>::InsertSpace(Int index, Int amount, Bool clear, Bool makenew)
{
	if (index < 0)
		return false;
	if (amount <= 0)
		return true;

	CHECKMEM(ptr);

	Int	cnt = ((count > index) ? count : index) + amount;

	if (!blocksize)
	{
		CriticalStop();
		return false;
	}

	if (index < (count >> 1))	// Insert space low
	{
		l_cnt -= amount;
		if (l_cnt < 0)	// resize it's larger
		{
			Int64 nadd = (((-l_cnt - 1) / blocksize) + 1) * blocksize;

			// Check against massive numbers
			Int64 tsize = (Int64(totcnt) + nadd) * Int64(sizeof(TYPE));
			if (tsize != Int(tsize) || tsize < (nadd + totcnt) || tsize < amount)
			{
				DebugAssert(false);	// To avoid people allocating more memory than is possible on the system
				return false;				//
			}

			totcnt += (Int)nadd;
			l_cnt	 += (Int)nadd;

			if (!ptr)
				ptr = (TYPE*) maxon::DefaultAllocator::Alloc(tsize, MAXON_SOURCE_LOCATION);
			else
				ptr = (TYPE*) maxon::DefaultAllocator::Realloc(ptr, tsize, MAXON_SOURCE_LOCATION);

			if (!ptr)
				return false;

			l_ptr = &ptr[l_cnt];

			if (index > 0)
			{
				memmove(&l_ptr[index + amount], &l_ptr[(amount - nadd) + index], sizeof(TYPE) * (count - index));
				memmove(l_ptr, &l_ptr[amount - nadd], sizeof(TYPE) * index);
			}
			else
			{
				memmove(&l_ptr[amount], &l_ptr[amount - nadd], sizeof(TYPE) * count);
			}
		}
		else	// just shift space in
		{
			if (index > 0)
				memmove(&ptr[l_cnt], l_ptr, sizeof(TYPE) * index);
			l_ptr = &ptr[l_cnt];
		}
	}
	else	// Insert space high
	{
		Int64	nsize = (((cnt + l_cnt - 1) / blocksize) + 1) * blocksize;

		if (nsize > totcnt)	// Resize it's larger
		{
			// Check against massive numbers
			Int64 tsize = nsize * Int64(sizeof(TYPE));
			if (tsize != Int(tsize) || tsize < nsize || tsize < amount)
			{
				DebugAssert(false);	// To avoid people allocating more memory than is possible on the system
				return false;
			}

			if (!ptr)
				ptr = (TYPE*) maxon::DefaultAllocator::Alloc(tsize, MAXON_SOURCE_LOCATION);
			else
				ptr = (TYPE*) maxon::DefaultAllocator::Realloc(ptr, tsize, MAXON_SOURCE_LOCATION);

			if (!ptr)
				return false;

			l_ptr = &ptr[l_cnt];

			totcnt = (Int)nsize;
		}

		// Shift space in
		if (index < count)
		{
			memmove(&(l_ptr[index + amount]), &(l_ptr[index]), sizeof(TYPE) * (count - index));
		}
	}

	Int		i = 0;
	TYPE* buf = nullptr;

	if (clear)
	{
		if (count < index)	// Clear space up till index
			memset(&l_ptr[count], 0, size_t((index - count) * sizeof(TYPE)));

		// Clear space from index over amount
		memset(&l_ptr[index], 0, size_t(amount * sizeof(TYPE)));
	}

	if (makenew)
	{
		if (count < index)	// Placement new from end of array to index
			for (i = count, buf = &l_ptr[count]; i < index; i++, buf++)
				new(buf)TYPE;

		// Placement new over amount
		for (i = 0, buf = &l_ptr[index]; i < amount; i++, buf++)
			new(buf)TYPE;
	}

	count = cnt;
	CHECKMEM(ptr);
	return true;
}

// Add value to the end of the array
template <class TYPE> Bool GeDynamicArray<TYPE>::Push(TYPE p)
{
	return Insert(p, count);
}

// Remove value from the array at index
// and shifts array down
template <class TYPE> Bool GeDynamicArray<TYPE>::Remove(Int index, Int amount)
{
	if (amount <= 0)
		return true;
	if (index < 0 || index >= count || !ptr)
		return false;
	if (!blocksize)
	{
		CriticalStop();
		return false;
	}

	if (index <= 0 && amount >= count)
	{
		FreeArray();
		return true;
	}

	Int		top = VMin(index + amount, count), amt = top - index;
	Int		i = 0;
	TYPE* buf = nullptr;

	CHECKMEM(ptr);

	for (i = 0, buf = &l_ptr[index]; i < amt; i++, buf++)
		buf->~TYPE();

	if (index < (count >> 1))
	{
		l_cnt += amt;

		if (index > 0)
			memmove(&l_ptr[amt], l_ptr, sizeof(TYPE) * index);	// shift l_ptr up

		l_ptr = &ptr[l_cnt];

		if (l_cnt >= blocksize)
		{
			Int nsub = (l_cnt / blocksize) * blocksize;

			totcnt -= nsub;
			l_cnt	 -= nsub;

			memmove(&l_ptr[-nsub], l_ptr, sizeof(TYPE) * (count - amt));	// Shift down

			ptr = (TYPE*) maxon::DefaultAllocator::Realloc(ptr, totcnt * SIZEOF(TYPE), MAXON_SOURCE_LOCATION);
			if (!ptr)
				return false;

			l_ptr = &ptr[l_cnt];
		}
	}
	else
	{
		Int	nsize = ((((count + l_cnt - 1) - amt) / blocksize) + 1) * blocksize;

		if (index < count - 1)
			memmove(&(l_ptr[index]), &(l_ptr[index + amt]), sizeof(TYPE) * (count - (index + amt)));

		if (nsize < totcnt)
		{
			ptr = (TYPE*) maxon::DefaultAllocator::Realloc(ptr, nsize * SIZEOF(TYPE), MAXON_SOURCE_LOCATION);
			if (!ptr)
				return false;

			l_ptr = &ptr[l_cnt];

			totcnt = nsize;
		}
	}
	count -= amt;
	CHECKMEM(ptr);
	return true;
}

// Removes all that match p from the array
template <class TYPE> inline void GeDynamicArray<TYPE>::RemoveAll(TYPE p)
{
	Int	index = 0;
	while (true)
	{
		index = Find(p, index);
		if (index == NOTOK)
			break;
		Remove(index);
	}
}

// Remove value from the end of the array
template <class TYPE> TYPE GeDynamicArray<TYPE>::Pop(void)
{
	if (count <= 0)
		return TYPE();
	TYPE result = l_ptr[count - 1];
	Remove(count - 1);
	return result;
}

// Find the index of type that matches type p
template <class TYPE> inline Int GeDynamicArray<TYPE>::Find(TYPE p)
{
	return Find(p, 0);
}

// Try to find an object from index onwards that matches type p
template <class TYPE> inline Int GeDynamicArray<TYPE>::Find(TYPE p, Int index)
{
	if (index >= count || !ptr)
		return NOTOK;

	CHECKMEM(ptr);
	TYPE* buf = &l_ptr[index];
	Int		i = 0;
	for (i = index; i < count; i++, buf++)
	{
		if (*buf == p)
			return i;
	}
	CHECKMEM(ptr);
	return NOTOK;
}

// Shift array down or up from index value
// negative to move down, positive to move up
template <class TYPE> void GeDynamicArray<TYPE>::Shift(Int index, Int cnt)
{
	ShiftBlock(index, count, cnt);
}

// Shift a block of the array up or down
// negative to move down, positive to move up
template <class TYPE> void GeDynamicArray<TYPE>::ShiftBlock(Int b_from, Int b_to, Int amount)
{
	Int block_start = VMin(b_from, b_to);
	Int block_end = VMax(b_from, b_to);
	if (amount == 0 || block_start == block_end || block_start < 0 || block_end > count)
		return;

	CHECKMEM(ptr);
	TYPE* buf = nullptr;
	Int		i = 0;
	if (amount > 0)
	{
		Int	istart = block_start;
		Int	iend = block_end - amount;

		if (iend < istart)
			iend = istart;

		Int m_min = VMin(count, VMax(block_end, istart + amount));
		Int m_max = VMin(count, block_end + amount);

		for (i = m_min, buf = &l_ptr[m_min]; i < m_max; i++, buf++)
			buf->~TYPE();

		m_min = VMin(count, istart + amount);

		if (m_max - m_min > 0)
			memmove(&(l_ptr[m_min]), &(l_ptr[istart]), sizeof(TYPE) * (m_max - m_min));

		iend = VMin(istart + amount, block_end);

		maxon::ClearMemType(&l_ptr[istart], (iend - istart));
		for (i = istart, buf = &l_ptr[istart]; i < iend; i++, buf++)
			new(buf)TYPE;
	}
	else
	{
		Int	istart = block_start;
		Int	iend = block_end;

		Int	m_shift = 0;
		Int	m_end = VMax(0, iend + amount), m_max = VMin(m_end, istart);
		Int	m_to	= istart + amount;
		if (m_to < 0)
		{
			m_to = 0;
			m_shift = -(istart + amount);
		}

		for (i = m_to, buf = &l_ptr[m_to]; i < m_max; i++, buf++)
			buf->~TYPE();

		if (m_end - m_to > 0)
			memmove(&(l_ptr[m_to]), &(l_ptr[istart + m_shift]), sizeof(TYPE) * (m_end - m_to));

		istart = VMax(block_start, m_end);

		maxon::ClearMemType(&l_ptr[istart], (iend - istart));
		for (i = istart, buf = &l_ptr[istart]; i < iend; i++, buf++)
			new(buf)TYPE;
	}
	CHECKMEM(ptr);
}

// Dynamic Array takes control of a datablock given to it
template <class TYPE> void GeDynamicArray<TYPE>::Grab(TYPE* p, Int amount)
{
	CHECKMEM(ptr);
	FreeArray();
	ptr = l_ptr = p;
	l_cnt = 0;
	if (ptr)
		totcnt = count = amount;
	else
		totcnt = count = 0;
	CHECKMEM(ptr);
}

// Safe Variant, this can be accessed via [] safely and will never get out of bounds

//----------------------------------------------------------------------------------------
/// @markDeprecated Use maxon::BaseArray instead.
//----------------------------------------------------------------------------------------
template <class TYPE> class GeSafeDynamicArray : public GeDynamicArray<TYPE>
{
	INSTANCEOF(GeSafeDynamicArray<TYPE>, GeDynamicArray<TYPE>)

public:
	GeSafeDynamicArray()
	{
		this->ptr = nullptr;
		this->blocksize = 4;
		this->FreeArray();
	}

	explicit GeSafeDynamicArray(Int size)
	{
		this->ptr = nullptr;
		this->blocksize = 4;
		this->FreeArray();
		this->ReScope(size);
	}

	GeSafeDynamicArray(Int size, Int block)
	{
		this->ptr = nullptr;
		this->blocksize = block;
		this->FreeArray();
		this->ReScope(size);
	}

	~GeSafeDynamicArray(void)
	{
		this->FreeArray();
	}

	GeSafeDynamicArray<TYPE>& operator =(const GeSafeDynamicArray<TYPE>& t)
	{
		this->FreeArray();

		this->SetBlockSize(t.GetBlockSize());
		this->ReScopeNC(t.count);

		CHECKMEM(ptr);

		Int		i = 0;
		TYPE* buf = this->l_ptr, *buf2 = t.l_ptr;
		for (i = 0; i < this->count; i++, buf++, buf2++)
			(*buf) = (*buf2);

		CHECKMEM(ptr);
		return *this;
	}

	TYPE& operator[](Int32 i) const
	{
		CHECKMEM(ptr);
		if (this->count == 0)
		{
			((GeDynamicArray<TYPE>*) this)->ReScope(1);
			return this->l_ptr[0];
		}
		if (i < 0)
			return this->l_ptr[0];
		if (i >= this->count)
			return this->l_ptr[this->count - 1];
		return this->l_ptr[i];
	}
	TYPE& operator[](Int64 i) const
	{
		CHECKMEM(ptr);
		if (this->count == 0)
		{
			((GeDynamicArray<TYPE>*) this)->ReScope(1);
			return this->l_ptr[0];
		}
		if (i < 0)
			return this->l_ptr[0];
		if (i >= this->count)
			return this->l_ptr[this->count - 1];
		return this->l_ptr[i];
	}
};



#define DEFAULT_ADR_BLOCK_SIZE 16

// Automatic variant, this will resize based on the index you specify in array[index]

//----------------------------------------------------------------------------------------
/// @markDeprecated Use maxon::BaseArray instead.
//----------------------------------------------------------------------------------------
template <class TYPE> class GeAutoDynamicArray : public GeDynamicArray<TYPE>
{
	INSTANCEOF(GeAutoDynamicArray<TYPE>, GeDynamicArray<TYPE>)

public:
	GeAutoDynamicArray()
	{
		this->ptr = nullptr;
		this->blocksize = DEFAULT_ADR_BLOCK_SIZE;
		this->FreeArray();
	}

	explicit GeAutoDynamicArray(Int size)
	{
		this->ptr = nullptr;
		this->blocksize = DEFAULT_ADR_BLOCK_SIZE;
		this->FreeArray();
		this->ReScope(size);
	}

	GeAutoDynamicArray(Int size, Int block)
	{
		this->ptr = nullptr;
		this->blocksize = block;
		this->FreeArray();
		this->ReScope(size);
	}
	~GeAutoDynamicArray(void)
	{
		this->FreeArray();
	}

	GeAutoDynamicArray<TYPE>& operator =(const GeAutoDynamicArray<TYPE>& t)
	{
		this->FreeArray();
		this->SetBlockSize(t.GetBlockSize());
		this->ReScopeNC(t.count);

		CHECKMEM(ptr);
		Int		i = 0;
		TYPE* buf = this->l_ptr, *buf2 = t.l_ptr;
		for (i = 0; i < this->count; i++, buf++, buf2++)
			(*buf) = (*buf2);
		CHECKMEM(ptr);
		return *this;
	}

	TYPE& operator[](Int32 i) const
	{
		CHECKMEM(ptr);
		if (this->count == 0)
		{
			((GeDynamicArray<TYPE>*) this)->ReScope(1);
		}
		if (i < 0)
			return this->l_ptr[0];
		if (i >= this->count)
		{
			((GeDynamicArray<TYPE>*) this)->ReSize(i + 1);
		}
		return this->l_ptr[i];
	}
	TYPE& operator[](Int64 i) const
	{
		CHECKMEM(ptr);
		if (this->count == 0)
		{
			((GeDynamicArray<TYPE>*) this)->ReScope(1);
		}
		if (i < 0)
			return this->l_ptr[0];
		if (i >= this->count)
		{
			((GeDynamicArray<TYPE>*) this)->ReSize(i + 1);
		}
		return this->l_ptr[i];
	}
};
#endif // GE_DYNAMICARRAY_H__


