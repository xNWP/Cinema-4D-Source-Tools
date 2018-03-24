#ifdef USE_API_MAXON

	#error "Please check your project include paths or your relative include path."

#elif !defined(C4DMISC_AUTOITERATOR_H__)
#define C4DMISC_AUTOITERATOR_H__

#include "../general.h"

namespace maxon
{

/// @addtogroup group_maxondatastructures
/// @{

//----------------------------------------------------------------------------------------
///	Iterator helper template.
/// @tparam C											Class with an valid Iterator.
/// This templates simplifies cases like iterating over a whole array or list. Typical
/// usage is:
///
/// @code
/// for (AutoIterator<ARRAYTYPE> it(array); it; it++)
/// {
///    // ... do something with *it or it->
/// }
/// @endcode
///
/// When iterating from the last to the first element you have to take into account that
/// End() is one after the last element. Therefore you have to write:
///
/// @code
/// for (AutoIterator<ARRAYTYPE> it(array.End(), array.Begin()); it; )
/// {
///		--it;
///   // ... do something with *it or it->
/// }
/// @endcode
///
/// Other than that the AutoIterator behaves like the iterator it encapsulates and you
/// can do all sorts of iterator arithmetic that the base iterator supports, e.g.
/// @code
/// it++;								// go to the next element
/// it--;								// go to the previous element
/// it += 5;						// advance by 5 elements
/// it -= 3;						// go back 3 elements
/// cnt = itB - itA;		// number of elements from itA to itB
/// *it = value;				// assign value to the elements referenced by the iterator
/// value = *it;				// get value of the element referenced by the iterator
/// @endcode
//----------------------------------------------------------------------------------------
template <typename C> class AutoIterator
{
	typedef typename Select<std::is_const<C>::value, typename C::ConstIterator, typename C::Iterator>::Type Iterator;
	Iterator _it;
	const Iterator _end;

public:
	/// This marker indicates that an AutoIterator supports the protocol of the FOREACH macro.
	typedef Int ForEachIteratorMarker;

	/// Use this constructor if you want to iterate over all elements.
	/// Please note that the end iterator of the AutoArray is a constant. When you modify an array
	/// (via Insert(), Append() or Erase()) the value of its End() iterator will most likely change
	/// and trying to iterate over such an array with an AutoIterator while modifying it would crash.
	explicit AutoIterator(C& container) : _it(container.Begin()), _end(container.End())
	{
	}

	/// use this constructor if you want to iterate from s until e (excluding e)
	explicit AutoIterator(const Iterator& s, const Iterator& e) : _it(s), _end(e)
	{
	}

	explicit AutoIterator(C& container, Int s, Int e = InvalidArrayIndex) : _it(container.Begin() + s), _end(e == InvalidArrayIndex ? container.End() : container.Begin() + e)
	{
	}

	AutoIterator(const AutoIterator& src) : _it(src._it), _end(src._end)
	{
	}

	AutoIterator& operator =(const AutoIterator& src)
	{
		if (this != &src)
		{
			_it = src._it;
			_end = src._end;
		}
		return *this;
	}

	//----------------------------------------------------------------------------------------
	/// Operator that returns false when the end of the array has been reached.
	/// operator bool() would be ambiguous because it can be used for integer arithmetic.
	/// For C++0x we use explicit bool to avoid that implicit conversion, for older
	/// compilers void* is returned because you can't do arithmetic with it.
	/// @return												False when the end of the array has been reached.
	//----------------------------------------------------------------------------------------
	C4D_MISC_OPERATOR_BOOL() const
	{
		return C4D_MISC_OPERATOR_BOOL_TYPE(_it != _end);
	}
	Bool HasValue() const
	{
		return _it != _end;
	}

	typename Iterator::ValueType* GetPtr() const
	{
		return _it.GetPtr();
	}
	typename Iterator::ValueType& operator *() const
	{
		return *_it;
	}
	typename Iterator::ValueType* operator ->() const
	{
		return _it.operator ->();
	}

	Bool operator ==(const AutoIterator& b) const
	{
		return _it == b._it;
	}
	Bool operator !=(const AutoIterator& b) const
	{
		return _it != b._it;
	}
	Bool operator >=(const AutoIterator& b) const
	{
		return _it >= b._it;
	}
	Bool operator <=(const AutoIterator& b) const
	{
		return _it <= b._it;
	}
	Bool operator <(const AutoIterator& b) const
	{
		return _it < b._it;
	}
	Bool operator >(const AutoIterator& b) const
	{
		return _it > b._it;
	}

	AutoIterator& operator ++()																// prefix operator ++ (increment and fetch)
	{
		++_it;
		return *this;
	}
	const AutoIterator operator ++(int)												// postfix operator ++ (fetch and increment)
	{
		Iterator tmp = _it;
		++_it;
		return AutoIterator(tmp, _end);													// use RVO
	}
	AutoIterator& operator +=(Int i)													// operator +=
	{
		_it += i;
		return *this;
	}
	AutoIterator& operator --()																// prefix operator -- (decrement and fetch)
	{
		--_it;
		return *this;
	}
	const AutoIterator operator --(int)												// postfix operator -- (fetch and decrement)
	{
		Iterator tmp = _it;
		--_it;
		return AutoIterator(tmp, _end);													// use RVO
	}
	AutoIterator& operator -=(Int i)													// operator -=
	{
		_it -= i;
		return *this;
	}
	AutoIterator operator +(Int i) const											// + operator
	{
		return AutoIterator(_it + i, _end);											// use RVO
	}
	AutoIterator operator -(Int i) const
	{
		return AutoIterator(_it - i, _end);											// use RVO
	}
	Int operator -(const AutoIterator& b) const
	{
		return _it - b._it;
	}
	Int operator -(const Iterator& b) const
	{
		return _it - b;
	}

	operator Iterator() const
	{
		return _it;
	}

};



template <typename T, Bool IS_FOR_EACH_ITERATOR> class GetForEachIterator;

template <typename T> class GetForEachIterator<T, false>
{
public:
	static AutoIterator<T> Get(T& iterable)
	{
		return AutoIterator<T>(iterable);
	}

	static AutoIterator<const T> Get(const T& iterable)
	{
		return AutoIterator<const T>(iterable);
	}
};

template <typename T> class GetForEachIterator<T, true>
{
public:
	static T Get(T iterator)
	{
		return iterator;
	}
};

template <typename T> FalseType IsForEachIteratorType(...);
template <typename T> typename SFINAEHelper<TrueType, typename T::ForEachIteratorMarker>::Type IsForEachIteratorType(Int);

/// @}

} // namespace maxon

#endif	// AUTOITERATOR_H__
