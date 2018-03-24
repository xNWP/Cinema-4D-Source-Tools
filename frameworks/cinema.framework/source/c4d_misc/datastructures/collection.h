#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(COLLECTION_H__)
#define COLLECTION_H__

#include "autoiterator.h"
#include "hashcode.h"

namespace maxon
{

/// @addtogroup group_maxondatastructures
/// @{


class CollectionOps
{
public:
	template <typename COLLECTION> static Bool Contains(COLLECTION& c, const typename COLLECTION::ValueType& v)
	{
		for (AutoIterator<COLLECTION> i(c); i; ++i)
		{
			if (*i == v)
			{
				return true;
			}
		}
		return false;
	}

	template <typename COLLECTION1, typename COLLECTION2> static Bool ContainsAll(const COLLECTION1& c1, const COLLECTION2& c2)
	{
		if (&c1 == &c2)
		{
			return true;
		}
		for (AutoIterator<const COLLECTION2> i(c2); i; ++i)
		{
			if (!COLLECTION1::Ops::Contains(c1, *i))
			{
				return false;
			}
		}
		return true;
	}

	template <typename COLLECTION1, typename COLLECTION2> static Bool AddAll(COLLECTION1& c1, const COLLECTION2& c2)
	{
		for (AutoIterator<const COLLECTION2> i(c2); i; ++i)
		{
			if (!COLLECTION1::Ops::Add(c1, *i))
			{
				return false;
			}
		}
		return true;
	}
};

class ArrayOps : public CollectionOps
{
public:
	template <typename COLLECTION> static Bool Add(COLLECTION& c, const typename COLLECTION::ValueType& v)
	{
		return c.Append(v);
	}

	template <typename COLLECTION1, typename COLLECTION2> static Bool IsEqual(const COLLECTION1& c1, const COLLECTION2& c2)
	{
		if (&c1 == &c2)
		{
			return true;
		}
		if (c1.GetCount() != c2.GetCount())
		{
			return false;
		}
		AutoIterator<const COLLECTION1> it1(c1);
		for (AutoIterator<const COLLECTION2> it2(c2); it1 && it2; ++it1, ++it2)
		{
			if (*it1 != *it2)
			{
				return false;
			}
		}
		return true;
	}
};

template <typename ELEMENTHASH = DefaultHash> class ArrayOpsWithHash : public ArrayOps
{
public:
	template <typename COLLECTION> static UInt GetHashCode(const COLLECTION& c)
	{
		UInt hash = 1;
		for (AutoIterator<const COLLECTION> i(c); i; ++i)
		{
			hash = 31 * hash + ELEMENTHASH::GetHashCode(*i);
		}
		return hash;
	}
};

class SetOps : public CollectionOps
{
public:
	template <typename COLLECTION> static Bool Add(COLLECTION& c, const typename COLLECTION::ValueType& v)
	{
		return c.Add(v);
	}

	template <typename COLLECTION> static Bool Contains(const COLLECTION& c, const typename COLLECTION::ValueType& v)
	{
		return c.Contains(v);
	}

	template <typename COLLECTION1, typename COLLECTION2> static Bool IsEqual(const COLLECTION1& c1, const COLLECTION2& c2)
	{
		if (&c1 == &c2)
		{
			return true;
		}
		if (c1.GetCount() != c2.GetCount())
		{
			return false;
		}
		for (AutoIterator<const COLLECTION2> i(c2); i; ++i)
		{
			if (!c1.Contains(*i))
			{
				return false;
			}
		}
		return true;
	}
};

template <typename ELEMENTHASH = DefaultHash> class SetOpsWithHash : public SetOps
{
public:
	template <typename COLLECTION> static UInt GetHashCode(const COLLECTION& c)
	{
		UInt hash = 0;
		for (AutoIterator<const COLLECTION> i(c); i; ++i)
		{
			hash += ELEMENTHASH::GetHashCode(*i);
		}
		return hash;
	}
};

class Collection
{
public:
	template <typename COLLECTION> static Bool Add(COLLECTION& c, const typename COLLECTION::ValueType& v)
	{
		return COLLECTION::Ops::Add(c, v);
	}

	template <typename COLLECTION> static Bool Contains(COLLECTION& c, const typename COLLECTION::ValueType& v)
	{
		return COLLECTION::Ops::Contains(c, v);
	}

	template <typename COLLECTION1, typename COLLECTION2> static Bool ContainsAll(const COLLECTION1& c1, const COLLECTION2& c2)
	{
		return COLLECTION1::Ops::ContainsAll(c1, c2);
	}

	template <typename COLLECTION1, typename COLLECTION2> static Bool AddAll(COLLECTION1& c1, const COLLECTION2& c2)
	{
		return COLLECTION1::Ops::AddAll(c1, c2);
	}

	template <typename COLLECTION1, typename COLLECTION2> static Bool IsEqual(const COLLECTION1& c1, const COLLECTION2& c2)
	{
		return COLLECTION1::Ops::IsEqual(c1, c2);
	}
};

template <typename COLLECTION> inline typename SFINAEHelper<Bool, typename COLLECTION::Ops>::Type operator ==(const COLLECTION& c1, const COLLECTION& c2)
{
	return COLLECTION::Ops::IsEqual(c1, c2);
}

template <typename COLLECTION> inline typename SFINAEHelper<Bool, typename COLLECTION::Ops>::Type operator !=(const COLLECTION& c1, const COLLECTION& c2)
{
	return !COLLECTION::Ops::IsEqual(c1, c2);
}


/// @}

} // maxon

#endif	// COLLECTION_H__
